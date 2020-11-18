/*
 * Blockchain.cpp
 *
 *  Created on: Nov 18, 2020
 *      Author: oski
 */

#include <stdio.h>
#include <ctime>
#include <string>

#include "Block.h"
#include "Blockchain.h"

#include <vector>



class Block{
private:
	int index;
	size_t blockHash;
	size_t previousHash;
	size_t generateHash();


public:
	Block(int idx, TransactionData d, size_t prevHash);

	//get original hash
	size_t getHash();
	//get previous hash
	size_t getPreviousHash();
	//transaction data
	TransactionData data;
	//validate hash
	bool isHashValid();
	int getIndex();

};

//constructor
Block::Block(int idx, TransactionData d, size_t prevHash){
	index = idx;
	data = d;
	previousHash = prevHash;
	blockHash = generateHash();
}

int Block::getIndex()
{
    return index;
}

//private fct
size_t Block::generateHash(){
	std::hash<std::string> hash1;
	std::hash<size_t> hash2;
	std::hash<size_t> finalHash;

	std::string toHash = std::to_string(data.amount) + data.receiverKey + data.senderKey + std::to_string(data.timestamp);

	return finalHash(hash1(toHash)+hash2(previousHash));
}

//public fct
size_t Block::getHash(){
	return blockHash;
}
size_t Block::getPreviousHash(){
	return previousHash;
}
bool Block::isHashValid(){
	return generateHash() == blockHash;
}




//constructor
Blockchain::Blockchain(){
	Block genesis = createGenesisBlock();
	chain.push_back(genesis);
}

Block Blockchain::createGenesisBlock(){
	time_t current_time;
	TransactionData d;
	d.amount = 0;
	d.receiverKey = "None";
	d.senderKey = "None";
	d.timestamp = time(&current_time);

	std::hash<int> hash1;
	Block genesis(0, d, hash1(0));
	return genesis;
}

Block *Blockchain::getLatestBlock(){
	return &chain.back();
}

void Blockchain::addBlock(TransactionData d){
	int index = (int)chain.size() -1;
	Block newBlock(index, d, getLatestBlock()->getHash());
	chain.push_back(newBlock);
}

int Blockchain::numberOfBlocks(){
	return (int)chain.size();
}

void Blockchain::printChain() {
    std::vector<Block>::iterator it;

    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        printf("\n\nBlock ===================================");
        printf("\nIndex: %d", currentBlock.getIndex());
        printf("\nAmount: %f", currentBlock.data.amount);
        printf("\nSenderKey: %s", currentBlock.data.senderKey.c_str());
        printf("\nReceiverKey: %s", currentBlock.data.receiverKey.c_str());
        printf("\nTimestamp: %ld", currentBlock.data.timestamp);
        printf("\nHash: %zu", currentBlock.getHash());
        printf("\nPrevious Hash: %zu", currentBlock.getPreviousHash());
        printf("\nIs Block Valid?: %d", currentBlock.isHashValid());
    }
}


bool Blockchain::isChainValid(){
	std::vector<Block>::iterator i;
	int chainLen = (int)chain.size();

	for (i = chain.begin(); i != chain.end(); ++i){
		Block currentBlock = *i;
		if (!currentBlock.isHashValid()){
			return false;
		}

		if(chainLen>1){
			Block previousBlock = *(i-1);
			if (currentBlock.getPreviousHash() != previousBlock.getHash()){
				return false;
			}
		}
	}
	return true;
}





