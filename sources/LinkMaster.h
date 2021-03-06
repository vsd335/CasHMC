/*********************************************************************************
*  CasHMC v1.2 - 2016.09.27
*  A Cycle-accurate Simulator for Hybrid Memory Cube
*
*  Copyright (c) 2016, Dong-Ik Jeon
*                      Ki-Seok Chung
*                      Hanyang University
*                      estwings57 [at] gmail [dot] com
*  All rights reserved.
*********************************************************************************/

#ifndef LINKMASTER_H
#define LINKMASTER_H

//LinkMaster.h

#include <vector>		//vector
#include <math.h>		//pow()

#include "SingleVectorObject.h"
#include "SimConfig.h"
#include "TranStatistic.h"
#include "Link.h"
#include "LinkSlave.h"

using namespace std;

namespace CasHMC
{
	
int FindAvailableLink(int &link, vector<LinkMaster *> &LM);
	
class LinkMaster : public SingleVectorObject<Packet>
{
public:
	//
	//Functions
	//
	LinkMaster(ofstream &debugOut_, ofstream &stateOut_, unsigned id, bool down);
	virtual ~LinkMaster();
	void CallbackReceive(Packet *packet, bool chkReceive);
	void UpdateRetryPointer(Packet *packet);
	void ReturnRetryPointer(Packet *packet);
	void UpdateToken(Packet *packet);
	void ReturnTocken(Packet *packet);
	void StartRetry(Packet *packet);
	void LinkRetry(Packet *packet);
	void FinishRetry();
	void Update();
	void CRCCountdown(int writeP, Packet *packet);
	void UpdateField(int nextWriteP, Packet *packet);
	void PrintState();

	//
	//Fields
	//
	unsigned linkMasterID;
	unsigned tokenCount;
	unsigned lastestRRP;
	Link *linkP;
	LinkSlave *localLinkSlave;
	vector<Packet *> backupBuffers;
	
	int masterSEQ;
	int countdownCRC;
	bool startCRC;
	
	Packet *retryStartPacket;
	bool readyStartRetry;
	bool startRetryTimer;
	unsigned retryTimer;
	unsigned retryAttempts;
	unsigned retBufReadP;
	unsigned retBufWriteP;
	vector<Packet *> retryBuffers;
};

}

#endif