/*
 * Blockchain.h
 *
 *  Created on: Nov 18, 2020
 *      Author: oski
 */

#ifndef BLOCKCHAIN_H_
#define BLOCKCHAIN_H_

#include <vector>

class Blockchain{
private:
	Block createGenesisBlock();
	std::vector<Block> chain;

public:
	Blockchain();

	//public fct
	std::vector<Block> getChain();
	void addBlock(TransactionData data);
	bool isChainValid();
	int numberOfBlocks();
	void printChain();

	//only for demo usage
	Block *getLatestBlock();

};



#endif /* BLOCKCHAIN_H_ */
