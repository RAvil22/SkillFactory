#pragma once
#include "electronics.h"

using namespace std;

class MicrowaveOven : public Appliance {
protected:
	unsigned int _power;
public:
	MicrowaveOven(unsigned int, unsigned int);
	virtual ~MicrowaveOven() = default;
	virtual void showSpec() override;
};

class CoffeeMachine : public Appliance {
protected:
	string _capucñinator;
public:
	CoffeeMachine(string, unsigned int);
	virtual ~CoffeeMachine() = default;
	virtual void showSpec() override;
};

class VacuumCleaner : public Appliance {
protected:
	unsigned int _power;
public:
	VacuumCleaner(unsigned int, unsigned int);
	~VacuumCleaner() = default;
	virtual void showSpec() override;
};