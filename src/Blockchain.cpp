//============================================================================
// Name        : Blockchain.cpp
// Author      : oski
// Version     :
// Copyright   : yes no
// Description : blockchain project
//============================================================================

#include <iostream>
#include <ctime>
#include <vector>


struct TransactionData{
	double amount;
	std::string senderKey;
	std::string receiverKey;
	time_t timestamp;
};

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


class Blockchain{
private:
	Block createGenesisBlock();

public:
	Blockchain();

	//public chain
	std::vector<Block> chain;

	//public fct
	void addBlock(TransactionData data);
	bool isChainValid();
	int numberOfBlocks();
	void printChain();

	//only for demo
	Block *getLatestBlock();

};

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




int main() {
	Blockchain OskiCoin;
	std::cout<< OskiCoin.numberOfBlocks()<<std::endl;
	std::cout<< OskiCoin.getLatestBlock()->getHash()<<std::endl;

	TransactionData data1;
	time_t data1Time;
	data1.amount = 1.5;
	data1.receiverKey = "Joe";
	data1.senderKey = "Sally";
	data1.timestamp = time(&data1Time);

	OskiCoin.addBlock(data1);
	std::cout<< OskiCoin.numberOfBlocks()<<std::endl;
	std::cout<< OskiCoin.getLatestBlock()->getHash()<<std::endl;

	TransactionData data2;
	time_t data2Time;
	data2.amount = 0.0013;
	data2.receiverKey = "Joel";
	data2.senderKey = "Max";
	data2.timestamp = time(&data2Time);

	OskiCoin.addBlock(data2);



	std::cout<< OskiCoin.numberOfBlocks()<<std::endl;
	std::cout<< OskiCoin.getLatestBlock()->getHash()<<std::endl;
	OskiCoin.printChain();


}
