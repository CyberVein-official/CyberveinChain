# CyberVeinChain
CyberVein: http://cybervein.org/

# 项目代码架构
## libp2p
底层通信协议代码库，包括p2p网络连接、会话管理、异常处理等底层网络相关的代码组件
## libutil
公共代码库，项目常用的公共代码库，包括加密解密、签名验签处理等等
## libdevcore
核心服务库，区块链核心库，包括块链数据结构定义、内存池管理、队列管理等等
## libdevcrypto
加密算法库
## cv
cybervein核心服务，区块链节点启动时的核心库，主要入口
## cvvm
cybervein virtual machine，基于EVM改造，执行智能合约的虚拟机
## cvdb
cybervein database，区块链节点的数据库服务
## cvpoc
cybervein proof of contribution，共识算法
## cvsample
cybervein samples，例子程序
## cvapi
cybervein api，接口程序
