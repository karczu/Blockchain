/*
 * Block.h
 *
 *  Created on: Nov 18, 2020
 *      Author: oski
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "TransactionData.h"

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
	//Should be as private member with a getter eg "getData()" - left public just for demo
	TransactionData data;
	//validate hash
	bool isHashValid();
	//get index
	int getIndex();

};


#endif /* BLOCK_H_ */
