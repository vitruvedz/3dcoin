// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_V014_BLOCKS_H
#define BITCOIN_V014_BLOCKS_H

#include "primitives/transaction.h"
#include "serialize.h"
#include "uint256.h"


class CBlocksHeader
{
public:
    // header
    int32_t nVersion;
    uint256 hashPrevBlock;
    uint256 hashTxRoot;
    uint256 hashObjRoot;
    uint256 hashDpsRoot;
    uint32_t nTime;
    uint32_t nBits;

    CBlocksHeader()
    {
        SetNull();
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(this->nVersion);
        nVersion = this->nVersion;
        READWRITE(hashPrevBlock);
        READWRITE(hashTxRoot);
        READWRITE(hashObjRoot);
        READWRITE(hashDpsRoot);
        READWRITE(nTime);
        READWRITE(nBits);
    }

    void SetNull()
    {
        nVersion = 0;
        hashPrevBlock.SetNull();
        hashTxRoot.SetNull();
        hashObjRoot.SetNull();
        hashDpsRoot.SetNull();
        nTime = 0;
        nBits = 0;
    }

    bool IsNull() const
    {
        return (nBits == 0);
    }

    uint256 GetHash() const;

    int64_t GetBlockTime() const
    {
        return (int64_t)nTime;
    }
};


class CBlocks : public CBlocksHeader
{
public:
    // network and disk
    std::vector<CTransaction> vtx;
    std::vector<CTransaction> vobj; //Districts objects
    std::vector<CTransaction> vdps; // Dapps transactions
    // memory only
    mutable CTxOut txoutMasternode; // masternode payment
    mutable CTxOut txoutPrimenode; // primenode payment
    mutable CTxOut txoutPulsenode; // pulsenode payment
    mutable bool fChecked;

    CBlocks()
    {
        SetNull();
    }

    CBlocks(const CBlocksHeader &header)
    {
        SetNull();
        *((CBlocksHeader*)this) = header;
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(*(CBlocksHeader*)this);
        READWRITE(vtx);
        READWRITE(vobj);
        READWRITE(vdps);
    }

    void SetNull()
    {
        CBlocksHeader::SetNull();
        vtx.clear();
        vobj.clear();
        vdps.clear();
        txoutMasternode = CTxOut();
        txoutPrimenode = CTxOut();
        txoutPulsenode = CTxOut();
        fChecked = false;
    }

    CBlocksHeader GetBlocksHeader() const
    {
        CBlocksHeader blocks;
        blocks.nVersion       = nVersion;
        blocks.hashPrevBlock  = hashPrevBlock;
        blocks.hashTxRoot = hashTxRoot;
        blocks.hashObjRoot = hashObjRoot;
        blocks.hashDpsRoot = hashDpsRoot;
        blocks.nTime          = nTime;
        blocks.nBits          = nBits;
        return blocks;
    }

    std::string ToString() const;
};


struct CBlocksLocator
{
    std::vector<uint256> vHave;

    CBlocksLocator() {}

    CBlocksLocator(const std::vector<uint256>& vHaveIn)
    {
        vHave = vHaveIn;
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        if (!(nType & SER_GETHASH))
            READWRITE(nVersion);
        READWRITE(vHave);
    }

    void SetNull()
    {
        vHave.clear();
    }

    bool IsNull() const
    {
        return vHave.empty();
    }
};

#endif // BITCOIN_V014_BLOCKS_H
