//============================================================================
// Name        : main.cpp
// Author      : oski
// Version     : 0.0.1
// Copyright   : no
// Description : blockchain project
//============================================================================

#include <iostream>
#include <ctime>
#include <vector>

#include "TransactionData.h"
#include "Block.h"
#include "Blockchain.h"

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


