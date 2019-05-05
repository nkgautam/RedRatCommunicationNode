#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <list>
#include <iterator>
#include "Block.h"
using namespace std;

class Blockchain
{
    public:
        Blockchain();
        virtual ~Blockchain();
    protected:
    private:
    list <Block> m_chain;
    Block CreateGenesisBlock();
};

#endif // BLOCKCHAIN_H
