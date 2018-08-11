# XMRig NVIDIA



XMRig is high performance Monero (XMR) NVIDIA miner, with the official full Windows support.
XMRig是一款高性能的windows挖矿软件


* This is the **NVIDIA GPU** mining version, there is also a [CPU version](https://github.com/global-blockchain/xmrig) 


:warning: Suggested values for GPU auto configuration can be not optimal or not working, you may need tweak your threads options. Please feel free open an [issue](https://github.com/global-blockchain/xmrig-nvidia/issues) if auto configuration suggest wrong values.
:注意:默认的配置可能并不适合你的机器，甚至无法工作。请调整现成数量。可以随时自github上提问咨询：[issue](https://github.com/global-blockchain/xmrig-nvidia)



#### Table of contents
* [Features](#features)
* [Download](#download)
* [Usage](#usage)
* [Build](https://github.com/global-blockchain/xmrig-nvidia/wiki/Build)
* [Donations](#donations)
* [Release checksums](#release-checksums)
* [Contacts](#contacts)
#### 目录
* [特色](#features)
* [下载](#download)
* [用法](#usage)
* [编译安装]()
* [捐赠](#donations)
* [Release checksums](#release-checksums)
* [联系我们](#contacts)
## 特色
* 高性能
* 支持windows系统 
* 支持动态切换挖矿服务器，一台服务器掉线，自动重连到另一台
* 支持AEON挖矿
* 自动配置
* GPU健康监控（时钟 功耗 温度 挖矿速度）
* 支持Nice Hash
* 完全开源

## 下载
* 可执行文件: https://github.com/global-blockchain/xmrig-nvidia/releases
* Git tree: https://github.com/global-blockchain/xmrig-nvidia.git
  * Clone with `git clone https://github.com/global-blockchain/xmrig-nvidia.git`  :hammer: [Build instructions](https://github.com/global-blockchain/xmrig-nvidia/wiki/Build).

## 使用方法

### 命令行选项
```
  -a, --algo=ALGO           cryptonight (default) or cryptonight-lite
  -o, --url=URL             URL of mining server
  -O, --userpass=U:P        username:password pair for mining server
  -u, --user=USERNAME       username for mining server
  -p, --pass=PASSWORD       password for mining server
  -k, --keepalive           send keepalived for prevent timeout (need pool support)
  -r, --retries=N           number of times to retry before switch to backup server (default: 5)
  -R, --retry-pause=N       time to pause between retries (default: 5)
      --cuda-devices=N      List of CUDA devices to use.
      --cuda-launch=TxB     List of launch config for the CryptoNight kernel
      --cuda-max-threads=N  limit maximum count of GPU threads in automatic mode
      --cuda-bfactor=[0-12] run CryptoNight core kernel in smaller pieces
      --cuda-bsleep=N       insert a delay of N microseconds between kernel launches
      --cuda-affinity=N     affine GPU threads to a CPU
      --no-color            disable colored output
      --donate-level=N      donate level, default 5% (5 minutes in 100 minutes)
      --user-agent          set custom user-agent string for pool
  -B, --background          run the miner in the background
  -c, --config=FILE         load a JSON-format configuration file
  -l, --log-file=FILE       log all output to a file
  -S, --syslog              use system log for output messages
      --nicehash            enable nicehash support
      --print-time=N        print hashrate report every N seconds
      --api-port=N          port for the miner API
      --api-access-token=T  access token for API
      --api-worker-id=ID    custom worker-id for API
  -h, --help                display this help and exit
  -V, --version             output version information and exit
```

## 捐赠
Default donation 5% (5 minutes in 100 minutes) can be reduced to 1% via command line option `--donate-level`.
默认捐赠是5%（没100分钟挖矿捐赠出5分钟),可以通过命令行选项`--donate-level` 将捐赠额度修改为1%

* XMR: `48PbYAxS8rj6B3u94zZwfwPZ7Y777zztQHrDGSvDaheu4LG6Y1e5L7QbUt28z4ZGETi5bSLeUCerx4cEnyFSidSQ9o1mJDG`
* ETH: `0x749Eaf7029988a6060Fdb2B1741852A92a45F378`

## Release checksums


## Contacts
* admin@imonero.org
