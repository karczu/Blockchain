/*
 * Block.cpp
 *
 *  Created on: Nov 18, 2020
 *      Author: oski
 */


#include <stdio.h>
#include <string>

#include "Block.h"
#include "TransactionData.h"

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

//generate hash for current block
//includes PREVIOUS HASH!!!
size_t Block::generateHash(){
	//create string of data
	std::string dataToHash = std::to_string(data.amount) + data.receiverKey + data.senderKey + std::to_string(data.timestamp);

	std::hash<std::string> dataHash;
	std::hash<size_t> prevHash;
	std::hash<size_t> finalHash;

	return finalHash(dataHash(dataToHash)+prevHash(previousHash));
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

