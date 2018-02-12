//
// Created by Okada, Takahiro on 2018/02/05.
//

#ifndef SMARTOUTLET_CONTRACT_H
#define SMARTOUTLET_CONTRACT_H

#include "Arduino.h"
#include "Log.h"
#include "Web3.h"

class Contract {

public:
    typedef struct {
        char from[80];
        char to[80];
        char gasPrice[20];
        long gas;
    } Options;
    Options options;

public:
    Contract(Web3* _web3, const char* address);
    void setPrivateKey(uint8_t* key);
    void SetupContractData(char *out, const char *func, ...);
    void Call(char* param);
    void SetupTransaction(uint32_t nonceVal, uint32_t gasPriceVal, uint32_t  gasLimitVal,
                                    uint8_t* toStr, uint8_t* valueStr, uint8_t* dataStr);

private:
    Log Debug;
    #define LOG(x) Debug.println(x)

    Web3* web3;
    const char * contractAddress;
    uint8_t * privateKey;

private:
    void GenerateContractBytes(const char *func, char *out);
    void GenerateBytesForInt(char *output, int32_t value);
    void GenerateBytesForUint(char *output, uint32_t value);
    void GenerateBytesForAddress(char *output, char *value);
    void GenerateBytesForString(char *output, char *value);
    void GenerateBytesForBytes(char *output, char* value, int len);

    void SetupTransactionImpl1(uint8_t* signature, uint32_t nonceVal, uint32_t gasPriceVal, uint32_t  gasLimitVal,
                                         uint8_t* toStr, uint8_t* valueStr, uint8_t* dataStr);
    void SetupTransactionImpl2(uint32_t nonceVal, uint32_t gasPriceVal, uint32_t  gasLimitVal,
                                         uint8_t* toStr, uint8_t* valueStr, uint8_t* dataStr, uint8_t* signature);
    uint32_t RlpEncode(uint8_t* encoded,
                       uint32_t nonceVal, uint32_t gasPriceVal, uint32_t  gasLimitVal,
                       uint8_t* toStr, uint8_t* valueStr, uint8_t* dataStr);
    uint32_t RlpEncodeForRawTransaction(uint8_t* encoded,
                                        uint32_t nonceVal, uint32_t gasPriceVal, uint32_t  gasLimitVal,
                                        uint8_t* toStr, uint8_t* valueStr, uint8_t* dataStr, uint8_t* sig);
    void Sign(uint8_t* hash, uint8_t* sig);
};


#endif //SMARTOUTLET_CONTRACT_H