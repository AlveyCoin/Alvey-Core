What is Alvey Chain ?


 Alvey is a decentralised blockchain with a proof-of-stake consensus model, meaning that the author of the subsequent block is selected at random based on how much cryptocurrency they have in their wallet and how mature that wallet is, continuously rotating addresses to ensure decentralisation and network participation. Blocks are usually built or minted rather than mined; there are also block rewards in addition to transaction fees, thus, builders receive a percentage of "interest" on the amount of funds they bet. This allows the chain to achieve high levels of security without excessive energy consumption, since to participate as an applicable active node for staking, is enough to have a Raspberry-Pi, laptop or 64-bit desktop PC which do not have such a high consumption compared to Proof of Work string mining rigs. Alvey supports the Bitcoin and Ethereum ecosystems. We use a pragmatic design approach to integrate metaverse and VR within the blockchain, allowing continuous development of real-world applications.. 

For more general information about AlveyCoin as well as links to join our community, go to https://alveychain.com

Welcome to the AlveyCoin Main Network. This is the main network where the tokens hold value and should be guarded very carefully. If you are testing the network, or developing unstable software on AlveyCoin, we highly recommend using the testnet.



AlveyChain Documentation and Usage Resources
---------------

These are some resources that might be helpful in understanding AlveyCoin.

Basic usage resources:


* [AlveyCoin-Qt Wallet Tutorial](https://github.com/AlveyCoin/documents/tree/master/en/AlveyCoin-Wallet-Tutorial#alvey-qt-wallet-tutorial)
* [AlveyCoin staking tutorial](https://github.com/AlveyCoin/documents/tree/master/en/How-to-Stake-with-AlveyCoin)
* [AlveyCoin tutorial on Raspberry Pi](https://github.com/AlveyCoin/documents/tree/master/en/AlveyCoin-on-Raspberry-Pi)
* [Running AlveyCoin on Amazon AWS using AlveyCoin AMI](https://github.com/AlveyCoin/documents/tree/master/en/AlveyCoin-AWS)
* [Encrypting and unlocking wallet](https://github.com/AlveyCoin/documents/tree/master/en/Encrypt-and-Unlock-AlveyCoin-Wallet)
* [Testnet guide](https://github.com/AlveyCoin/documents/blob/master/en/Testnet-User-Guide.md)
* [Block explorer](https://alveyscan.com), [Older explorer](https://alveyscan.com)


Development resources:

* [AlveyCoin Book - A Developer's Guide To ALV](http://book.alvey.site/en/)
* [AlveyCoin contract usage](https://docs.alvey.site/en/ARC20-Token-Introduce.html)
* [Deploying a custom token to AlveyCoin](https://blog.alveychain.com/alvey-custom-token-walkthrough-467d725fa27d)
* [AlveyCoinJS document](https://alveyproject.github.io/alveyjs-doc/)
* [Smart contract ICO example](http://book.alvey.site/en/part3/ico.htm)
* [Early example faucet contract](http://earlz.net/view/2017/06/30/2144/the-alvey-sparknet-faucet)

General Info about AlveyCoin:

* [CIRCLERESEARCH AlveyCoin Primer](https://www.circle.com/marketing/pdfs/research/circle-research-alvey.pdf)
* [AlveyCoin's PoS vs CASPER](https://www.reddit.com/r/AlveyCoin/comments/788oa5/alveys_pos_vs_casper_and_the_nothingatstake_problem/)
* [Technical article explaining AlveyCoin's PoS model in depth](http://earlz.net/view/2017/07/27/1904/the-missing-explanation-of-proof-of-stake-version)


Developer's Tools
-----------------

* Smart contract deployment tool
  * https://github.com/AlveyCoin/solar
* DApp JavaScript Library
  * https://github.com/AlveyCoin/Alvey-Corejs
* A toolkit for building alvey light wallets
  * https://github.com/AlveyCoin/Alvey-Corejs-wallet
* CORS alveyd RPC proxy for DApp
  * https://github.com/AlveyCoin/Alvey-Coreportal
* Docker images for running alvey services
  * https://github.com/AlveyCoin/Alvey-Core-docker
* alvey.info API that powers the block explorer and the ALV Web wallet
  * https://github.com/AlveyCoin/Alvey-Coreinfo-api#alveyinfo-api-documentation


What is AlveyCoin Core?
------------------

AlveyCoin Core is our primary mainnet wallet. It implements a full node and is capable of storing, validating, and distributing all history of the AlveyCoin network. AlveyCoin Core is considered the reference implementation for the AlveyCoin network. 

AlveyCoin Core currently implements the following:

* Sending/Receiving ALV coins
* Sending/Receiving ARC20 tokens on the AlveyCoin network
* Staking and creating blocks for the AlveyCoin network
* Creating and interacting with smart contracts
* Running a full node for distributing the blockchain to other users
* "Prune" mode, which minimizes disk usage
* Regtest mode, which enables developers to very quickly build their own private AlveyCoin network for Dapp testing
* Testnet mode, using the public AlveyCoin Testnet, with faucet available
* Compatibility with the Bitcoin Core set of RPC commands and APIs
* Full SegWit capability with p2sh-segwit (legacy) and bech32 (native) addresses

Alternative Wallets
-------------------

AlveyCoin Core uses a full node model, and thus requires downloading the entire blockchain. If you do not need the entire blockchain, and do not intend on developing smart contracts, it may be more ideal to use an alternative wallet such as one of our light wallets that can be synchronized in a matter of seconds. 

### AlveyCoin Web Wallet

A browser wallet that supports the Ledger hardware wallet, offline cold wallet, and restoration from mobile wallets.

Web site 

User documentation https://github.com/AlveyCoin/documents/tree/master/en/ALV-WebWallet-usage

### Alvey Coin Core (A.C.C)

A light wallet that supports the Ledger and Trezor hardware wallets and is based on the well-known Electrum wallet software. 

Download: https://github.com/AlveyCoin/

### iOS and Android Wallets

These wallets run on mobile devices and synchronize quickly. (Soon...) 

Android Download: 

iOS Download: (Soon..)

### Ledger Chrome Wallet

This light wallet runs in your Chrome browser as a browser extension. This wallet requires a Ledger device to use. (Soon...)

How to install: https://ledger.zendesk.com


### Community Resources

Make sure to check out these resources as well for more information and to keep up to date with all the latest news about AlveyCoin. At least 1 developer is always around, so if you're developing on AlveyCoin and need help, we'd love to welcome you to our community.

*	AlveyChain on Twitter https://twitter.com/AlveyChain
*	AlveyChain Telegram Group https://t.me/alveychain, other languages soon will be available
*	AlveyChain Website https://alveychain.com
*	AlveyChain Oculus https://www.oculus.com/deeplink/?action=view&path=%2Fprofile%2F105412678873935&utm_medium=share&utm_source=oculus
*	AlveyChain Press https://forum.alveychain.com

### AlveyCoin Smart Contract Limitations

*	EVM smart contracts cannot receive coins from or send coins to any address type other than pay-to-pubkeyhash (starts with Q) addresses. This is due to a limitation in the EVM
*	Contracts are not allowed to create contracts with an initial endowment of coins. The contract must first be created, and then be sent coins in a separate transaction. Humans are also not allowed to create contracts with an initial endowment of coins.
*	Although all of the infrastructure is present, AlveyCoin Core does not currently parse Solidity event data. You must parse this yourself using either searchlogs or -record-log-opcodes features.
*	It is not possible to send a contract coins without also executing the contract. This is also the case of Ethereum. This was promised in earlier discussions and technically does work, but due to lack of time for testing this feature was disabled. We hope to reenable this feature with release of the x86 virtual machine in 2020.
*	In AlveyCoin there can be multiple addresses used to create a proof-of-stake block. However, the EVM can only see the first output using the coinbase operation in Solidity (this address is also the one registered for the continuous staker rewards after 500 blocks).

----------

# Building Alvey Coin Core

### Validate and Reproduce Binaries

AlveyCoin uses a tool called Gitian to make reproducible builds that can be verified by anyone. Instructions on setting up a Gitian VM and building AlveyCoin are provided in [Gitan Building](https://github.com/AlveyCoin/Alvey-Core/blob/master/doc/gitian-building.md)

### Build on Ubuntu

This is a quick start script for compiling AlveyCoin on Ubuntu


    sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils git cmake libboost-all-dev libgmp3-dev
    sudo apt-get install software-properties-common
    sudo add-apt-repository ppa:bitcoin/bitcoin
    sudo apt-get update
    sudo apt-get install libdb4.8-dev libdb4.8++-dev

    # If you want to build the Qt GUI:
    sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler qrencode

    git clone https://github.com/AlveyCoin/Alvey-Core --recursive
    cd alvey

    # Note autogen will prompt to install some more dependencies if needed
    ./autogen.sh
    ./configure 
    make -j2
    
### Build on CentOS

Here is a brief description for compiling AlveyCoin on CentOS, for more details please refer to [the specific document](https://github.com/AlveyCoin/Alvey-Core/blob/master/doc/build-unix.md)

    # Compiling boost manually
    sudo yum install python-devel bzip2-devel
    git clone https://github.com/boostorg/boost.git
    cd boost
    git checkout boost-1.66.0
    git submodule update --init --recursive
    ./bootstrap.sh --prefix=/usr --libdir=/usr/lib64
    ./b2 headers
    sudo ./b2 -j4 install
    
    # Installing Dependencies for AlveyCoin
    sudo yum install epel-release
    sudo yum install libtool libdb4-cxx-devel openssl-devel libevent-devel gmp-devel
    
    # If you want to build the Qt GUI:
    sudo yum install qt5-qttools-devel protobuf-devel qrencode-devel
    
    # Building AlveyCoin
    git clone --recursive https://github.com/AlveyCoin/Alvey-Core.git
    cd alvey
    ./autogen.sh
    ./configure
    make -j4

### Build on Mac OS

The commands in this guide should be executed in a Terminal application.
The built-in one is located in `/Applications/Utilities/Terminal.app`.

#### Preparation

Install the Mac OS command line tools:

`xcode-select --install`

When the popup appears, click `Install`.

Then install [Homebrew](https://brew.sh).

#### Dependencies

    brew install cmake automake berkeley-db4 libtool boost miniupnpc openssl pkg-config protobuf qt5 libevent imagemagick librsvg qrencode gmp

NOTE: Building with Qt4 is still supported, however, could result in a broken UI. Building with Qt5 is recommended.

#### Build AlveyCoin Core

1. Clone the alvey source code and cd into `alvey`

        git clone --recursive https://github.com/AlveyCoin/Alvey-Core.git
        cd alvey

2.  Build alvey-core:

    Configure and build the headless alvey binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing `--without-gui` to configure.

        ./autogen.sh
        ./configure
        make

3.  It is recommended to build and run the unit tests:

        make check

### Run

Then you can either run the command-line daemon using `src/alveyd` and `src/alvey-cli`, or you can run the Qt GUI using `src/qt/alvey-qt`

License
-------

AlveyCoin is GPLv3 licensed.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/AlveyCoin/Alvey-Core/tags) are created
regularly to indicate new official, stable release versions of AlveyCoin.

The contribution workflow is described in [CONTRIBUTING.md](https://github.com/AlveyCoin/Alvey-Core/blob/master/CONTRIBUTING.md)
and useful hints for developers can be found in [doc/developer-notes.md](doc/developer-notes.md).

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and macOS, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

