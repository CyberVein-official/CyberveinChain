
#pragma once

#include <memory>
#include <iostream>
#include <jsonrpccpp/server.h>
#include <jsonrpccpp/common/exception.h>
#include <libdevcrypto/Common.h>
#include <libcv/Client.h>
#include "SessionManager.h"
#include "EthFace.h"


namespace dev
{
class NetworkFace;
class KeyPair;
namespace eth
{
class AccountHolder;
struct TransactionSkeleton;
class Interface;
}
namespace shh
{
class Interface;
}

extern const unsigned SensibleHttpThreads;
extern const unsigned SensibleHttpPort;

}

namespace dev
{

namespace rpc
{

/**
 * @brief JSON-RPC api implementation
 */
class Eth: public dev::rpc::EthFace
{
public:
	Eth(eth::Interface& _eth, eth::AccountHolder& _ethAccounts, Address& _god);

	virtual RPCModules implementedModules() const override
	{
		return RPCModules{RPCModule{"eth", "1.0"}};
	}

	eth::AccountHolder const& ethAccounts() const { return m_ethAccounts; }

	virtual std::string eth_protocolVersion() override;
	virtual std::string eth_hashrate() override;
	virtual std::string eth_coinbase() override;
	virtual bool eth_mining() override;
	virtual std::string eth_gasPrice() override;
	virtual Json::Value eth_accounts() override;
	virtual std::string eth_blockNumber()override;
	virtual std::string eth_pbftView()override;
    virtual Json::Value eth_getProofMerkle(string const& _blockHash, string const& _transactionIndex)override;
	virtual std::string eth_getBalance(std::string const& _address, std::string const& _blockNumber) override;
	virtual std::string eth_getStorageAt(std::string const& _address, std::string const& _position, std::string const& _blockNumber) override;
	virtual std::string eth_getStorageRoot(std::string const& _address, std::string const& _blockNumber) override;
	virtual std::string eth_getTransactionCount(std::string const& _address, std::string const& _blockNumber) override;
	//virtual std::string eth_pendingTransactions() override;
	virtual Json::Value eth_pendingTransactions() override;
	virtual Json::Value eth_getBlockTransactionCountByHash(std::string const& _blockHash) override;
	virtual Json::Value eth_getBlockTransactionCountByNumber(std::string const& _blockNumber) override;
	virtual Json::Value eth_getUncleCountByBlockHash(std::string const& _blockHash) override;
	virtual Json::Value eth_getUncleCountByBlockNumber(std::string const& _blockNumber) override;
	virtual std::string eth_getCode(std::string const& _address, std::string const& _blockNumber) override;
	virtual std::string eth_sendTransaction(Json::Value const& _json) override;
	virtual std::string eth_call(Json::Value const& _json, std::string const& _blockNumber) override;


	virtual std::string eth_estimateGas(Json::Value const& _json) override;
	virtual bool eth_flush() override;
	virtual Json::Value eth_getBlockByHash(std::string const& _blockHash, bool _includeTransactions) override;
	virtual Json::Value eth_getBlockByNumber(std::string const& _blockNumber, bool _includeTransactions) override;
	virtual Json::Value eth_getTransactionByHash(std::string const& _transactionHash) override;
	virtual Json::Value eth_getTransactionByBlockHashAndIndex(std::string const& _blockHash, std::string const& _transactionIndex) override;
	virtual Json::Value eth_getTransactionByBlockNumberAndIndex(std::string const& _blockNumber, std::string const& _transactionIndex) override;
	virtual Json::Value eth_getTransactionReceipt(std::string const& _transactionHash) override;
	virtual Json::Value eth_getUncleByBlockHashAndIndex(std::string const& _blockHash, std::string const& _uncleIndex) override;
	virtual Json::Value eth_getUncleByBlockNumberAndIndex(std::string const& _blockNumber, std::string const& _uncleIndex) override;
	virtual std::string eth_newFilter(Json::Value const& _json) override;
	virtual std::string eth_newFilterEx(Json::Value const& _json) override;
	virtual std::string eth_newBlockFilter() override;
	virtual std::string eth_newPendingTransactionFilter() override;
	virtual bool eth_uninstallFilter(std::string const& _filterId) override;
	virtual Json::Value eth_getFilterChanges(std::string const& _filterId) override;
	virtual Json::Value eth_getFilterChangesEx(std::string const& _filterId) override;
	virtual Json::Value eth_getFilterLogs(std::string const& _filterId) override;
	virtual Json::Value eth_getFilterLogsEx(std::string const& _filterId) override;
	virtual Json::Value eth_getLogs(Json::Value const& _json) override;
	virtual Json::Value eth_getLogsEx(Json::Value const& _json) override;
	virtual Json::Value eth_getWork() override;
	virtual bool eth_submitWork(std::string const& _nonce, std::string const&, std::string const& _mixHash) override;
	virtual bool eth_submitHashrate(std::string const& _hashes, std::string const& _id) override;
	virtual std::string eth_register(std::string const& _address) override;
	virtual bool eth_unregister(std::string const& _accountId) override;
	virtual Json::Value eth_fetchQueuedTransactions(std::string const& _accountId) override;
	virtual std::string eth_signTransaction(Json::Value const& _transaction) override;
	virtual Json::Value eth_inspectTransaction(std::string const& _rlp) override;
	virtual std::string eth_sendRawTransaction(std::string const& _rlp) override;
	virtual bool eth_notePassword(std::string const&) override { return false; }
	virtual Json::Value eth_syncing() override;

	void setTransactionDefaults(eth::TransactionSkeleton& _t);

	virtual std::string eth_unverifiedBlockQueueSize()override;
	virtual std::string eth_verifiedBlockQueueSize()override;

	virtual std::string eth_unverifiedTransactionsQueueSize()override;
	virtual std::string eth_verifiedTransactionsQueueSize()override;

	//bool isDefaultCall(const TransactionSkeleton &t, CnsParams &params, const Json::Value &_json);
	//bool isOldCNSCall(const TransactionSkeleton &t, CnsParams &params ,const Json::Value &_json);
	//bool isNewCNSCall(const TransactionSkeleton &t);

	//void eth_sendTransactionOldCNSSetParams(TransactionSkeleton &t);
	//void eth_sendTransactionNewCNSSetParams(TransactionSkeleton &t);

	//std::string eth_callDefault(TransactionSkeleton &t, std::string const& _blockNumber);
	//std::string eth_callOldCNS(TransactionSkeleton &t,const CnsParams &params,std::string const& _blockNumber);
	//std::string eth_callNewCNS(TransactionSkeleton &t, std::string const& _blockNumber);

	//CNS
	//virtual std::string eth_getCodeCNS(std::string const& strContractName, std::string const& _blockNumber) override;
	//virtual std::string eth_getBalanceCNS(std::string const& strContractName, std::string const& _blockNumber) override;
	//virtual std::string eth_getStorageAtCNS(std::string const& strContractName, std::string const& _position, std::string const& _blockNumber) override;
	//virtual std::string eth_getTransactionCountCNS(std::string const& strContractName, std::string const& _blockNumber) override;

protected:

	eth::Interface* client() { return &m_eth; }

	eth::Interface& m_eth;
	eth::AccountHolder& m_ethAccounts;

	Address& m_god;

};

}
} //namespace dev
