#pragma once
#include "electronics.h"

using namespace std;

class WearableElectronics : public Device {
protected:
	string _deviceType;
public:
	WearableElectronics(unsigned int, string);
	virtual ~WearableElectronics() = default;
	virtual void showSpec() override;
}; // электронные часы, наушники. 

class MobilePhone : public Device {
protected:
	unsigned int _generation;
public:
	MobilePhone(unsigned int, unsigned int);
	virtual ~MobilePhone() = default;
	virtual void showSpec() override;
};

class Smartphone : public MobilePhone, Computer {
public:
	Smartphone(unsigned int, unsigned int, float, float);
	virtual ~Smartphone() = default;
	virtual void showSpec() override;
};

class Notebook : public Computer, Device {
protected:
	float _diagonal;
public:
	Notebook(float, float, float, unsigned int);
	virtual ~Notebook() = default;
	virtual void showSpec() override;
};


