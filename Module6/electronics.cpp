#include "electronics.h"
using namespace std;

Device::Device(unsigned int bL) : _batteryLife{ bL } {}

void Device::showSpec() {
	cout << "Battery life time: " << this->_batteryLife << endl;
}

Appliance::Appliance(unsigned int weight) : _weight{weight} {}

void Appliance::showSpec() {
	cout << "Weight: " << this->_weight << endl;
}

Computer::Computer(float freq, float size) : _freqCPU{ freq }, _memorySize{size} {}

void Computer::showSpec() {
	cout << "CPU requency: " << this->_freqCPU << endl;
	cout << "Flash memory size: " << this->_memorySize << endl;
}