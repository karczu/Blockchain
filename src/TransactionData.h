/*
 * TransactionData.h
 *
 *  Created on: Nov 18, 2020
 *      Author: oski
 */

#ifndef TRANSACTIONDATA_H_
#define TRANSACTIONDATA_H_

struct TransactionData{
	double amount;
	std::string senderKey;
	std::string receiverKey;
	time_t timestamp;

    TransactionData(){};

    TransactionData(double amt, std::string sender, std::string receiver, time_t time)
    {
        amount = amt;
        senderKey = sender;
        receiverKey = receiver;
        timestamp = time;
    };

};



#endif /* TRANSACTIONDATA_H_ */
