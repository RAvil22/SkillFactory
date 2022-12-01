#include "devices.h"

using namespace std;

WearableElectronics::WearableElectronics(unsigned int bl, string type) : Device(bl), _deviceType(type) {}

void WearableElectronics::showSpec() {
	cout << "Wearable" << endl;
	cout << "Battery life time: " << this->_batteryLife << endl;
	cout << "Device type: " << this->_deviceType << endl;
}

MobilePhone::MobilePhone(unsigned int bl, unsigned int generation) : Device(bl), _generation(generation) {}

void MobilePhone::showSpec() {
	cout << "Mobile" << endl;
	cout << "Battery life time: " << this->_batteryLife << endl;
	cout << "Mobile network generation: " << this->_generation << endl;
}

Smartphone::Smartphone(unsigned int bl, unsigned int generation, float freq, float memsize) :
	MobilePhone(_batteryLife = bl, _generation = generation),
	Computer(_freqCPU = freq, _memorySize = memsize) {}

void Smartphone::showSpec() {
	cout << "Smartphone" << endl;
	cout << "Battery life time: " << this->_batteryLife << endl;
	cout << "Mobile network generation: " << this->_generation << endl;
	cout << "CPU requency: " << this->_freqCPU << endl;
	cout << "Flash memory size: " << this->_memorySize << endl;
}

Notebook::Notebook(float diagonal, float freq, float memsize, unsigned int bl) : Computer(_freqCPU = freq, _memorySize = memsize),
Device(bl), _diagonal{diagonal} {}

void Notebook::showSpec() {
	cout << "Notebook" << endl;
	cout << "Battery life time: " << this->_batteryLife << endl;
	cout << "Screen diagonal: " << this->_diagonal << endl;
	cout << "CPU requency: " << this->_freqCPU << endl;
	cout << "Flash memory size: " << this->_memorySize << endl;
}
