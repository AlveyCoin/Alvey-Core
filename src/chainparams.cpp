// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <consensus/consensus.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <util/convert.h>
#include <versionbitsinfo.h>

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

///////////////////////////////////////////// // alvey
#include <libdevcore/SHA3.h>
#include <libdevcore/RLP.h>
#include "arith_uint256.h"
/////////////////////////////////////////////

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 00 << 488804799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    genesis.hashStateRoot = uint256(h256Touint(dev::h256("e965ffd002cd6ad0e2dc402b8044de833e06b23127ea8c3d80aec91410771495"))); // alvey
    genesis.hashUTXORoot = uint256(h256Touint(dev::sha3(dev::rlp("")))); // alvey
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "April 18, 2022 Kenya dominates the 2022 Boston Marathon";
    const CScript genesisOutputScript = CScript() << ParseHex("040d61d8653448c98731ee5fffd303c15e71ec2057b77f11ab3601979728cdaff2d68afbba14e4fa0bc44f2072b0b23ef63717f8cdfbe58dcd33f32b6afe98741a") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = CBaseChainParams::MAIN;
        consensus.nSubsidyHalvingInterval = 985500; // alvey halving every 4 years
        consensus.BIP16Exception = uint256S("0x000000001421468e58e0e1fd8ce030ccb49c950f0d342896f693f445b4abbc8b");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x000000001421468e58e0e1fd8ce030ccb49c950f0d342896f693f445b4abbc8b");
        consensus.BIP65Height = 0; // 000000000000000004c2b624ed5d7756c508d90fd0da2c7c679febfa6c4735f0
        consensus.BIP66Height = 0; // 00000000000000000379eaa19dce8c9b722d46ae6a57c2f1a988119488b50931
        consensus.CSVHeight = 6048; // 000000000000000004a1b34462cb8aeebd5799177f7a29cf28f2d1961716b5b5
        consensus.SegwitHeight = 6048; // 0000000000000000001c8018d9cb3b742ef25114f27563e3fc4a1902167f9893
        consensus.MinBIP9WarningHeight = 8064; // segwit activation height + miner confirmation window
        consensus.QIP5Height = 466600;
        consensus.QIP6Height = 466600;
        consensus.QIP7Height = 466600;
        consensus.QIP9Height = 466600;
        consensus.nOfflineStakeHeight = 680000;
        consensus.nReduceBlocktimeHeight = 845000;
        consensus.nMuirGlacierHeight = 845000;
        consensus.powLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.QIP9PosLimit = uint256S("0000000000001fffffffffffffffffffffffffffffffffffffffffffffffffff"); // The new POS-limit activated after QIP9
        consensus.RBTPosLimit = uint256S("0000000000003fffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 16 * 60; // 16 minutes
        consensus.nPowTargetTimespanV2 = 4000;
        consensus.nRBTPowTargetTimespan = 1000;
        consensus.nPowTargetSpacing = 2 * 64;
        consensus.nRBTPowTargetSpacing = 32;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = true;
        consensus.fPoSNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000100510051"); // alvey

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0000213497fb498607f4712b19e6a35967d7692caf3857e39e95fe41445fe9dd"); // 80

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0xa6;
        pchMessageStart[3] = 0xd3;
        nDefaultPort = 3888;
        nPruneAfterHeight = 100000;
        m_assumed_blockchain_size = 14;
        m_assumed_chain_state_size = 1;

        genesis = CreateGenesisBlock(1650823922, 4125296769, 0x1d00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000000001421468e58e0e1fd8ce030ccb49c950f0d342896f693f445b4abbc8b"));
        assert(genesis.hashMerkleRoot == uint256S("0x6d61616ae968ecdaf3c4d81c2956ee78132e515ea51f9dcd85df2c2cc7b780b6"));

        // Note that of those which support the service bits prefix, most only support a subset of
        // possible options.
        // This is fine at runtime as we'll fall back to using them as a oneshot if they don't support the
        // service bits we want, but we should get them updated to support all service bits wanted by any
        // release ASAP to avoid it where possible.
        //vSeeds.emplace_back("alvey3.dynu.net"); // AlveyCoin mainnet
        //vSeeds.emplace_back("alvey5.dynu.net"); // AlveyCoin mainnet
        //vSeeds.emplace_back("alvey6.dynu.net"); // AlveyCoin mainnet
        //vSeeds.emplace_back("alvey7.dynu.net"); // AlveyCoin mainnet

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,23);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,50);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,128);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "qc";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        m_is_test_chain = false;
        m_is_mockable_chain = false;
        fHasHardwareWalletSupport = true;

        checkpointData = {
            {
                { 0, uint256S("000000001421468e58e0e1fd8ce030ccb49c950f0d342896f693f445b4abbc8b")},
                { 80, uint256S("0000213497fb498607f4712b19e6a35967d7692caf3857e39e95fe41445fe9dd")},
                { 160, uint256S("0000500d44eb0a72807e4d1215692c3dd369c54ca14a57bea1bade256bcf098d")},
                { 250, uint256S("0000918268d7fc28859dc853121a8ae0c729fc910a978ac194f8fa3bd94f9a2f")},
                { 320, uint256S("0000139ba53f20660223fc0e3dde40d3d474d55f58d27f5f1534fbe1d3f63c92")},
                { 420, uint256S("0000f02e4f98c84eea5057cf477e302ebe4d8d6b2606f0a447187dd6c443ad11")},
                { 500, uint256S("0000655ba9019f81840bfd57fe9edc83526b4319ea31b2a9479fc7ae55162de3")},
                { 550, uint256S("0000dbd24b8a4934a5c20f24f7c158d58c62e3799b3d2ae47519b710ac0aace7")},
                { 600, uint256S("00002afe40b2570b70267549721f7e585ec2519b796aa526c0220cd134dfb921")},

                
                
                
            }
        };

        chainTxData = ChainTxData{
            // Data as of block 87ee4ec601b335d411e01378936e21044b1a47a3d989feaaaed0e8eaa2929e4b (height 1407838)
            1653080812, // * UNIX timestamp of last known number of transactions
            0, // * total number of transactions between genesis and that timestamp
            //   (the tx=... number in the SetBestChain debug.log lines)
            0.0842613440826197 // * estimated number of transactions per second after that timestamp
        };

        consensus.nBlocktimeDownscaleFactor = 4;
        consensus.nCoinbaseMaturity = 500;
        consensus.nRBTCoinbaseMaturity = consensus.nBlocktimeDownscaleFactor*500;
        consensus.nSubsidyHalvingIntervalV2 = consensus.nBlocktimeDownscaleFactor*985500; // alvey halving every 4 years (nSubsidyHalvingInterval * nBlocktimeDownscaleFactor)

        consensus.nLastPOWBlock = 5000;
        consensus.nLastBigReward = 5000;
        consensus.nMPoSRewardRecipients = 10;
        consensus.nFirstMPoSBlock = consensus.nLastPOWBlock + 
                                    consensus.nMPoSRewardRecipients + 
                                    consensus.nCoinbaseMaturity;
        consensus.nLastMPoSBlock = 679999;


        consensus.nFixUTXOCacheHFHeight = 100000;
        consensus.nEnableHeaderSignatureHeight = 399100;
        consensus.nCheckpointSpan = consensus.nCoinbaseMaturity;
        consensus.nRBTCheckpointSpan = consensus.nRBTCoinbaseMaturity;
        consensus.delegationsAddress = uint160(ParseHex("0000000000000000000000000000000000000086")); // Delegations contract for offline staking
        consensus.nStakeTimestampMask = 15;
        consensus.nRBTStakeTimestampMask = 3;
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = CBaseChainParams::TESTNET;
        consensus.nSubsidyHalvingInterval = 985500; // alvey halving every 4 years
        consensus.BIP16Exception = uint256S("0x00000000f7c801bd0bd578ab93bc9bab0913a15a9a2fc0b1b66858c32b55886c");
        consensus.BIP34Height = 0;
        consensus.BIP34Hash = uint256S("0x00000000f7c801bd0bd578ab93bc9bab0913a15a9a2fc0b1b66858c32b55886c");
        consensus.BIP65Height = 0; // 00000000007f6655f22f98e72ed80d8b06dc761d5da09df0fa1dc4be4f861eb6
        consensus.BIP66Height = 0; // 000000002104c8c45e99a8853285a3b592602a3ccde2b832481da85e9e4ba182
        consensus.CSVHeight = 6048; // 00000000025e930139bac5c6c31a403776da130831ab85be56578f3fa75369bb
        consensus.SegwitHeight = 6048; // 00000000002b980fcd729daaa248fd9316a5200e9b367f4ff2c42453e84201ca
        consensus.MinBIP9WarningHeight = 8064; // segwit activation height + miner confirmation window
        consensus.QIP5Height = 446320;
        consensus.QIP6Height = 446320;
        consensus.QIP7Height = 446320;
        consensus.QIP9Height = 446320;
        consensus.nOfflineStakeHeight = 625000;
        consensus.nReduceBlocktimeHeight = 806600;
        consensus.nMuirGlacierHeight = 806600;
        consensus.powLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.QIP9PosLimit = uint256S("0000000000001fffffffffffffffffffffffffffffffffffffffffffffffffff"); // The new POS-limit activated after QIP9
        consensus.RBTPosLimit = uint256S("0000000000003fffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 16 * 60; // 16 minutes
        consensus.nPowTargetTimespanV2 = 4000;
        consensus.nRBTPowTargetTimespan = 1000;
        consensus.nPowTargetSpacing = 2 * 64;
        consensus.nRBTPowTargetSpacing = 32;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = true;
        consensus.fPoSNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00"); // alvey

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00"); // 1405000

        pchMessageStart[0] = 0x0d;
        pchMessageStart[1] = 0x22;
        pchMessageStart[2] = 0x15;
        pchMessageStart[3] = 0x06;
        nDefaultPort = 13888;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 6;
        m_assumed_chain_state_size = 1;

        genesis = CreateGenesisBlock(1650835094, 1783339903, 0x1d00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();


        assert(consensus.hashGenesisBlock == uint256S("0x00000000f7c801bd0bd578ab93bc9bab0913a15a9a2fc0b1b66858c32b55886c"));
        assert(genesis.hashMerkleRoot == uint256S("0x6d61616ae968ecdaf3c4d81c2956ee78132e515ea51f9dcd85df2c2cc7b780b6"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        // vSeeds.emplace_back("alvey4.dynu.net"); // AlveyCoin testnet

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,88);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,110);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tq";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;
        fHasHardwareWalletSupport = true;

        checkpointData = {
            {
                {0, uint256S("00000000f7c801bd0bd578ab93bc9bab0913a15a9a2fc0b1b66858c32b55886c")},
                
            }
        };

        chainTxData = ChainTxData{
            // Data as of block eac806357d6afadecc7fcbc79256e51b170187bbe4497c5192b023bd0b422a48 (height 1457136)
            1650835094,
            0,
            0.06376731417354913
        };

        consensus.nBlocktimeDownscaleFactor = 4;
        consensus.nCoinbaseMaturity = 500;
        consensus.nRBTCoinbaseMaturity = consensus.nBlocktimeDownscaleFactor*500;
        consensus.nSubsidyHalvingIntervalV2 = consensus.nBlocktimeDownscaleFactor*985500; // alvey halving every 4 years (nSubsidyHalvingInterval * nBlocktimeDownscaleFactor)

        consensus.nLastPOWBlock = 5000;
        consensus.nLastBigReward = 5000;
        consensus.nMPoSRewardRecipients = 10;
        consensus.nFirstMPoSBlock = consensus.nLastPOWBlock + 
                                    consensus.nMPoSRewardRecipients + 
                                    consensus.nCoinbaseMaturity;
        consensus.nLastMPoSBlock = 624999;

        consensus.nFixUTXOCacheHFHeight = 84500;
        consensus.nEnableHeaderSignatureHeight = 391993;
        consensus.nCheckpointSpan = consensus.nCoinbaseMaturity;
        consensus.nRBTCheckpointSpan = consensus.nRBTCoinbaseMaturity;
        consensus.delegationsAddress = uint160(ParseHex("0000000000000000000000000000000000000086")); // Delegations contract for offline staking
        consensus.nStakeTimestampMask = 15;
        consensus.nRBTStakeTimestampMask = 3;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID =  CBaseChainParams::REGTEST;
        consensus.nSubsidyHalvingInterval = 985500;
        consensus.BIP16Exception = uint256S("0x0000ea73a54d692110e5edd92d9675f9e7b1977ec89417a8b32543ed16e8ec54");
        consensus.BIP34Height = 0; // BIP34 activated on regtest (Used in functional tests)
        consensus.BIP34Hash = uint256S("0x0000ea73a54d692110e5edd92d9675f9e7b1977ec89417a8b32543ed16e8ec54");
        consensus.BIP65Height = 0; // BIP65 activated on regtest (Used in functional tests)
        consensus.BIP66Height = 0; // BIP66 activated on regtest (Used in functional tests)
        consensus.CSVHeight = 432; // CSV activated on regtest (Used in rpc activation tests)
        consensus.SegwitHeight = 0; // SEGWIT is always activated on regtest unless overridden
        consensus.MinBIP9WarningHeight = 0;
        consensus.QIP5Height = 0;
        consensus.QIP6Height = 0;
        consensus.QIP7Height = 0;
        consensus.QIP9Height = 0;
        consensus.nOfflineStakeHeight = 1;
        consensus.nReduceBlocktimeHeight = 0;
        consensus.nMuirGlacierHeight = 0;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.QIP9PosLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff"); // The new POS-limit activated after QIP9
        consensus.RBTPosLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 16 * 60; // 16 minutes (960 = 832 + 128; multiplier is 832)
        consensus.nPowTargetTimespanV2 = 4000;
        consensus.nRBTPowTargetTimespan = 1000;
        consensus.nPowTargetSpacing = 2 * 64;
        consensus.nRBTPowTargetSpacing = 32;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.fPoSNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfd;
        pchMessageStart[1] = 0xdd;
        pchMessageStart[2] = 0xc6;
        pchMessageStart[3] = 0xe1;
        nDefaultPort = 23888;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);

        genesis = CreateGenesisBlock(1650840393, 76392, 0x1f00ffff, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000ea73a54d692110e5edd92d9675f9e7b1977ec89417a8b32543ed16e8ec54"));
        assert(genesis.hashMerkleRoot == uint256S("0x6d61616ae968ecdaf3c4d81c2956ee78132e515ea51f9dcd85df2c2cc7b780b6"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        fMineBlocksOnDemand = true;
        m_is_test_chain = true;
        m_is_mockable_chain = true;
        fHasHardwareWalletSupport = true;

        checkpointData = {
            {
                {0, uint256S("0000ea73a54d692110e5edd92d9675f9e7b1977ec89417a8b32543ed16e8ec54")},
            }
        };

        chainTxData = ChainTxData{
            1650840393,
            0,
            0
        };

        consensus.nBlocktimeDownscaleFactor = 4;
        consensus.nCoinbaseMaturity = 500;
        consensus.nRBTCoinbaseMaturity = consensus.nBlocktimeDownscaleFactor*500;
        consensus.nSubsidyHalvingIntervalV2 = consensus.nBlocktimeDownscaleFactor*985500; // alvey halving every 4 years (nSubsidyHalvingInterval * nBlocktimeDownscaleFactor)

        consensus.nLastPOWBlock = 0x7fffffff;
        consensus.nLastBigReward = 5000;
        consensus.nMPoSRewardRecipients = 10;
        consensus.nFirstMPoSBlock = 5000;
        consensus.nLastMPoSBlock = 0;

        consensus.nFixUTXOCacheHFHeight=0;
        consensus.nEnableHeaderSignatureHeight = 0;

        consensus.nCheckpointSpan = consensus.nCoinbaseMaturity;
        consensus.nRBTCheckpointSpan = consensus.nRBTCoinbaseMaturity;
        consensus.delegationsAddress = uint160(ParseHex("0000000000000000000000000000000000000086")); // Delegations contract for offline staking
        consensus.nStakeTimestampMask = 15;
        consensus.nRBTStakeTimestampMask = 3;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,88);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,110);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "qcrt";
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (gArgs.IsArgSet("-segwitheight")) {
        int64_t height = gArgs.GetArg("-segwitheight", consensus.SegwitHeight);
        if (height < -1 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range. Use -1 to disable segwit.", height));
        } else if (height == -1) {
            LogPrintf("Segwit disabled for testing\n");
            height = std::numeric_limits<int>::max();
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

/**
 * Regression network parameters overwrites for unit testing
 */
class CUnitTestParams : public CRegTestParams
{
public:
    explicit CUnitTestParams(const ArgsManager& args)
    : CRegTestParams(args)
    {
        // Activate the the BIPs for regtest as in Bitcoin
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = consensus.nBlocktimeDownscaleFactor*500 + 851; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = consensus.nBlocktimeDownscaleFactor*500 + 751; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.QIP6Height = consensus.nBlocktimeDownscaleFactor*500 + 500;
        consensus.QIP7Height = 0; // QIP7 activated on regtest

        // ALV have 500 blocks of maturity, increased values for regtest in unit tests in order to correspond with it
        consensus.nSubsidyHalvingInterval = 750;
        consensus.nSubsidyHalvingIntervalV2 = consensus.nBlocktimeDownscaleFactor*750;
        consensus.nRuleChangeActivationThreshold = consensus.nBlocktimeDownscaleFactor*558; // 75% for testchains
        consensus.nMinerConfirmationWindow = consensus.nBlocktimeDownscaleFactor*744; // Faster than normal for regtest (744 instead of 2016)

        consensus.nBlocktimeDownscaleFactor = 4;
        consensus.nCoinbaseMaturity = 500;
        consensus.nRBTCoinbaseMaturity = consensus.nBlocktimeDownscaleFactor*500;

        consensus.nCheckpointSpan = consensus.nCoinbaseMaturity*2; // Increase the check point span for the reorganization tests from 500 to 1000
        consensus.nRBTCheckpointSpan = consensus.nRBTCoinbaseMaturity*2; // Increase the check point span for the reorganization tests from 500 to 1000
    }
};

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    else if (chain == CBaseChainParams::UNITTEST)
        return std::unique_ptr<CChainParams>(new CUnitTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

std::string CChainParams::EVMGenesisInfo() const
{
    std::string genesisInfo = dev::eth::genesisInfo(GetEVMNetwork());
    ReplaceInt(consensus.QIP7Height,         "QIP7_STARTING_BLOCK", genesisInfo);
    ReplaceInt(consensus.QIP6Height,         "QIP6_STARTING_BLOCK", genesisInfo);
    ReplaceInt(consensus.nMuirGlacierHeight, "MUIR_STARTING_BLOCK", genesisInfo);
    return genesisInfo;
}

std::string CChainParams::EVMGenesisInfo(int nHeight) const
{
    std::string genesisInfo = dev::eth::genesisInfo(GetEVMNetwork());
    ReplaceInt(nHeight, "QIP7_STARTING_BLOCK", genesisInfo);
    ReplaceInt(nHeight, "QIP6_STARTING_BLOCK", genesisInfo);
    ReplaceInt(nHeight, "MUIR_STARTING_BLOCK", genesisInfo);
    return genesisInfo;
}

dev::eth::Network CChainParams::GetEVMNetwork() const
{
    return dev::eth::Network::alveyMainNetwork;
}

void CChainParams::UpdateOpSenderBlockHeight(int nHeight)
{
    consensus.QIP5Height = nHeight;
}

void UpdateOpSenderBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateOpSenderBlockHeight(nHeight);
}

void CChainParams::UpdateBtcEcrecoverBlockHeight(int nHeight)
{
    consensus.QIP6Height = nHeight;
}

void UpdateBtcEcrecoverBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateBtcEcrecoverBlockHeight(nHeight);
}

void CChainParams::UpdateConstantinopleBlockHeight(int nHeight)
{
    consensus.QIP7Height = nHeight;
}

void UpdateConstantinopleBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateConstantinopleBlockHeight(nHeight);
}

void CChainParams::UpdateDifficultyChangeBlockHeight(int nHeight)
{
    consensus.nSubsidyHalvingInterval = 985500; // alvey halving every 4 years
    consensus.nSubsidyHalvingIntervalV2 = consensus.nBlocktimeDownscaleFactor*985500; // alvey halving every 4 years (nSubsidyHalvingInterval * nBlocktimeDownscaleFactor)
    consensus.posLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
    consensus.QIP9PosLimit = uint256S("0000000000001fffffffffffffffffffffffffffffffffffffffffffffffffff");
    consensus.RBTPosLimit = uint256S("0000000000003fffffffffffffffffffffffffffffffffffffffffffffffffff");
    consensus.QIP9Height = nHeight;
    consensus.fPowAllowMinDifficultyBlocks = false;
    consensus.fPowNoRetargeting = true;
    consensus.fPoSNoRetargeting = false;
    consensus.nLastPOWBlock = 5000;
    consensus.nMPoSRewardRecipients = 10;
    consensus.nFirstMPoSBlock = consensus.nLastPOWBlock + 
                                consensus.nMPoSRewardRecipients + 
                                consensus.nCoinbaseMaturity;
    consensus.nLastMPoSBlock = 0;
}

void UpdateDifficultyChangeBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateDifficultyChangeBlockHeight(nHeight);
}

void CChainParams::UpdateOfflineStakingBlockHeight(int nHeight)
{
    consensus.nOfflineStakeHeight = nHeight;
}

void UpdateOfflineStakingBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateOfflineStakingBlockHeight(nHeight);
}

void CChainParams::UpdateDelegationsAddress(const uint160& address)
{
    consensus.delegationsAddress = address;
}

void UpdateDelegationsAddress(const uint160& address)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateDelegationsAddress(address);
}

void CChainParams::UpdateLastMPoSBlockHeight(int nHeight)
{
    consensus.nLastMPoSBlock = nHeight;
}

void UpdateLastMPoSBlockHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateLastMPoSBlockHeight(nHeight);
}

void CChainParams::UpdateReduceBlocktimeHeight(int nHeight)
{
    consensus.nReduceBlocktimeHeight = nHeight;
}

void UpdateReduceBlocktimeHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateReduceBlocktimeHeight(nHeight);
}

void CChainParams::UpdatePowAllowMinDifficultyBlocks(bool fValue)
{
    consensus.fPowAllowMinDifficultyBlocks = fValue;
}

void UpdatePowAllowMinDifficultyBlocks(bool fValuet)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdatePowAllowMinDifficultyBlocks(fValuet);
}

void CChainParams::UpdatePowNoRetargeting(bool fValue)
{
    consensus.fPowNoRetargeting = fValue;
}

void UpdatePowNoRetargeting(bool fValuet)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdatePowNoRetargeting(fValuet);
}

void CChainParams::UpdatePoSNoRetargeting(bool fValue)
{
    consensus.fPoSNoRetargeting = fValue;
}

void UpdatePoSNoRetargeting(bool fValuet)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdatePoSNoRetargeting(fValuet);
}

void CChainParams::UpdateMuirGlacierHeight(int nHeight)
{
    consensus.nMuirGlacierHeight = nHeight;
}

void UpdateMuirGlacierHeight(int nHeight)
{
    const_cast<CChainParams*>(globalChainParams.get())->UpdateMuirGlacierHeight(nHeight);
}
