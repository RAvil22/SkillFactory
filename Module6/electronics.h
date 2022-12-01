#pragma once
#include <iostream>

class IElectronics {
public:
	virtual void showSpec() = 0;
	virtual ~IElectronics() = default;
};

class Computer : public virtual IElectronics {
protected:
	float _freqCPU;
	float _memorySize;
public:
	Computer(float, float);
	virtual ~Computer() = default;
	virtual void showSpec() override;
};

/*Носимая электроника*/
class Device : public virtual IElectronics {
protected:
	unsigned int _batteryLife;
public:
	Device(unsigned int);
	virtual ~Device() = default;
	virtual void showSpec() override;
};

/*Бытовая техника*/
class Appliance : public virtual IElectronics {
protected:
	unsigned int _weight;
public:
	Appliance(unsigned int);
	virtual void showSpec() override;
};
