

#include "RLPXSocketIO.h"

#include <algorithm>
using namespace std;
using namespace dev;
using namespace dev::p2p;

uint32_t const RLPXSocketIO::MinFrameSize = h128::size * 3; // header + block + mac
uint32_t const RLPXSocketIO::MaxPacketSize = 1 << 24;
uint16_t const RLPXSocketIO::DefaultInitialCapacity = 8 << 8;

RLPXSocketIO::RLPXSocketIO(unsigned _protCount, RLPXFrameCoder& _coder, bi::tcp::socket& _socket, bool _flowControl, size_t _initialCapacity):
	m_flowControl(_flowControl),
	m_coder(_coder),
	m_socket(_socket),
	m_writers(writers(_protCount)),
	m_egressCapacity(m_flowControl ? _initialCapacity : MaxPacketSize * m_writers.size())
{}

vector<RLPXFrameWriter> RLPXSocketIO::writers(unsigned _capacity)
{
	vector<RLPXFrameWriter> ret;
	for (unsigned i = 0; i < _capacity; i++)
		ret.push_back(RLPXFrameWriter(i));
	return ret;
}

void RLPXSocketIO::send(unsigned _protocolType, unsigned _type, RLPStream& _payload)
{
	if (!m_socket.is_open())
		return; // TCPSocketNotOpen
	m_writers.at(_protocolType).enque(_type, _payload);
	bool wasEmtpy = false;
	DEV_GUARDED(x_queued)
		wasEmtpy = (++m_queued == 1);
	if (wasEmtpy)
		doWrite();
}

void RLPXSocketIO::doWrite()
{
	m_toSend.clear();

	size_t capacity = 0;
	DEV_GUARDED(x_queued)
		capacity = min(m_egressCapacity, MaxPacketSize);

	size_t active = 0;
	for (auto const& w: m_writers)
		if (w.size())
			active += 1;
	size_t dequed = 0;
	size_t protFrameSize = capacity / active;
	if (protFrameSize >= MinFrameSize)
		for (auto& w: m_writers)
			dequed += w.mux(m_coder, protFrameSize, m_toSend);

	if (dequed)
		write(dequed);
	else
		deferWrite();
}

void RLPXSocketIO::deferWrite()
{
	auto self(shared_from_this());
	m_congestion.reset(new ba::deadline_timer(m_socket.get_io_service()));
	m_congestion->expires_from_now(boost::posix_time::milliseconds(50));
	m_congestion->async_wait([=](boost::system::error_code const& _ec) { m_congestion.reset(); if (!_ec) doWrite(); });
}

void RLPXSocketIO::write(size_t _dequed)
{
	auto self(shared_from_this());
	if (m_toSend.empty())
		return;

	ba::async_write(m_socket, ba::buffer(m_toSend[0]), [this, self, _dequed](boost::system::error_code ec, size_t written)
	{
		if (ec)
			return; // TCPSocketWriteError

		bool reschedule = false;
		DEV_GUARDED(x_queued)
		{
			if (m_flowControl)
				m_egressCapacity -= written;
			m_queued -= _dequed;
			reschedule = m_queued > 0;
		}
		if (reschedule)
			doWrite();
	});
}
