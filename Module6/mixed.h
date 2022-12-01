#pragma once
#include "devices.h"
#include"appliances.h"

using namespace std;

class RobotVacuumCleaner : public Computer, Device, VacuumCleaner {
public:
	RobotVacuumCleaner(float, float, unsigned int, unsigned int, unsigned int);
	~RobotVacuumCleaner() = default;
	virtual void showSpec() override;
};