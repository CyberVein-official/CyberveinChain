# CyberVeinChain
Official C++ implementation of CyberVein project - <http://cybervein.org>

Welcome to the CyberVein source code repository!

Currently development is on very initial stage. Main modules of repository are p2p network protocol, simple wallet, account management and consensus algorithm.

There is no testnet running currently.

## Supported Operating Systems
Centos 7


## Code architecture / 项目代码架构
### cv
Cybervein core service, main module to start blockchain node.
Cybervein核心服务，区块链节点启动时的核心库，主要入口
### cvpoc
Cybervein proof of contribution, Consensus algorithm. (Not implemented, currently using Practical Byzantine Fault Tolerance).
Cybervein proof of contribution，共识算法
### cvvm
Cybervein virtual machine, cvvm is capable of running smart contracts.
Cybervein virtual machine，基于EVM改造，执行智能合约的虚拟机
### libdevcore
Core blockchain service library, blockchain data structure definition, memory pool management, queue management.
核心服务库，区块链核心库，包括块链数据结构定义、内存池管理、队列管理等等
### libdevcrypto
Encryption algorithm library.
加密算法库
### libp2p
P2P communication protocol, communication management and exception handling.
底层通信协议代码库，包括p2p网络连接、会话管理、异常处理等底层网络相关的代码组件

