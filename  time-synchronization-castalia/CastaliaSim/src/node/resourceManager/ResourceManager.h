/*******************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2010                            *
 *  Developed at the ATP lab, Networked Systems research theme                 *
 *  Author(s): Athanassios Boulis, Dimosthenis Pediaditakis, Yuriy Tselishchev *
 *  This file is distributed under the terms in the attached LICENSE file.     *
 *  If you do not find this file, copies can be found by writing to:           *
 *                                                                             *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia                *
 *      Attention:  License Inquiry.                                           *
 *                                                                             *  
 *******************************************************************************/

#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <map>
#include "CastaliaModule.h"
#include "ResourceManagerMessage_m.h"

using namespace std;

enum ResoruceManagerTimers {
	PERIODIC_ENERGY_CALCULATION = 1,
};

class ResourceManager: public CastaliaModule {
 private:
	// parameters and variables
	/*--- The .ned file's parameters ---*/
	double sigmaCPUClockDrift;
	double cpuClockDrift;
	double initialEnergy;
	double ramSize;
	double baselineNodePower;
	double currentNodePower;
	simtime_t timeOfLastCalculation;
	double periodicEnergyCalculationInterval;
	simtime_t lastDriftCompensationTime;
	simtime_t driftCompensationAdjust;
	simtime_t driftAdjust;
	double lastDrift;
	simtime_t offset;
	double driftSampleTime;
	simtime_t lastUpdateDrift;
	double driftCompensation;

	/*--- Custom class parameters ---*/
	double remainingEnergy;
	double totalRamData;

	map<int,double> storedPowerConsumptions;

	cMessage *energyMsg;
	bool disabled;

 protected:
	virtual void initialize();
	virtual void handleMessage(cMessage * msg);
	virtual void finishSpecific();
	void calculateEnergySpent();

 public:
	double getCPUClockDrift(void);
	simtime_t getOffset();
	void setOffset(simtime_t new_offset);
	double getDriftCompensation();
	void setDriftCompensation(double new_driftCompensation);
	double getDriftSampleTime();
	void updateDrift(double new_drift, simtime_t updateDriftTime);
	simtime_t getDriftAdjust();
	simtime_t getDriftCompensationAdjust();
	void DriftCompensationAdjust(simtime_t new_time);
	void consumeEnergy(double amount);
	double getSpentEnergy(void);
	void destroyNode(void);
	int RamStore(int numBytes);
	void RamFree(int numBytes);
};

#endif				// _RESOURCEGENERICMANAGER_H_