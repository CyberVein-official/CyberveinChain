

#pragma once

#include <array>
#include <libdevcore/Common.h>
#include <libdevcore/RLP.h>
#include <libcvvm/ExtVMFace.h>

namespace dev
{

namespace eth
{

class TransactionReceipt
{
public:
	TransactionReceipt(bytesConstRef _rlp);
	TransactionReceipt(h256 _root, u256 _gasUsed, LogEntries const& _log, Address const& _contractAddress = Address());

	h256 const& stateRoot() const { return m_stateRoot; }
	u256 const& gasUsed() const { return m_gasUsed; }
	Address const& contractAddress() const { return m_contractAddress; }
	LogBloom const& bloom() const { return m_bloom; }
	LogEntries const& log() const { return m_log; }

	void streamRLP(RLPStream& _s) const;

	bytes rlp() const { RLPStream s; streamRLP(s); return s.out(); }

private:
	h256 m_stateRoot;
	u256 m_gasUsed;
	Address m_contractAddress; 
	LogBloom m_bloom;
	LogEntries m_log;
};

using TransactionReceipts = std::vector<TransactionReceipt>;

std::ostream& operator<<(std::ostream& _out, eth::TransactionReceipt const& _r);

class LocalisedTransactionReceipt: public TransactionReceipt
{
public:
	LocalisedTransactionReceipt(
		TransactionReceipt const& _t,
		h256 const& _hash,
		h256 const& _blockHash,
		BlockNumber _blockNumber,
		unsigned _transactionIndex
	):
		TransactionReceipt(_t),
		m_hash(_hash),
		m_blockHash(_blockHash),
		m_blockNumber(_blockNumber),
		m_transactionIndex(_transactionIndex)
	{
		LogEntries entries = log();
		for (unsigned i = 0; i < entries.size(); i++)
			m_localisedLogs.push_back(LocalisedLogEntry(
				entries[i],
				m_blockHash,
				m_blockNumber,
				m_hash,
				m_transactionIndex,
				i
			));
	}

	h256 const& hash() const { return m_hash; }
	h256 const& blockHash() const { return m_blockHash; }
	BlockNumber blockNumber() const { return m_blockNumber; }
	unsigned transactionIndex() const { return m_transactionIndex; }
	LocalisedLogEntries const& localisedLogs() const { return m_localisedLogs; };

private:
	h256 m_hash;
	h256 m_blockHash;
	BlockNumber m_blockNumber;
	unsigned m_transactionIndex = 0;
	LocalisedLogEntries m_localisedLogs;
};

}
}
