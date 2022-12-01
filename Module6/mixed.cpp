#include "mixed.h"

using namespace std;

RobotVacuumCleaner::RobotVacuumCleaner(float freq, float size, unsigned int bl, unsigned int weight, unsigned int power) :
	Computer(_freqCPU = freq, _memorySize = size), Device(bl), VacuumCleaner(_weight = weight, _power = power) {}

void RobotVacuumCleaner::showSpec() {
	cout << "Robot" << endl;
	cout << "Battery life: " << this->_batteryLife << endl;
	cout << "CPU requency: " << this->_freqCPU << endl;
	cout << "Flash memory size: " << this->_memorySize << endl;
	cout << "Power: " << this->_power << endl;
	cout << "Weight: " << this->_weight << endl;
}