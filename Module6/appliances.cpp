#include "appliances.h"

using namespace std;

MicrowaveOven::MicrowaveOven(unsigned int power, unsigned int weight) : Appliance(weight), _power(power) {}

void MicrowaveOven::showSpec() {
	cout << "Microwave" << endl;
	cout << "Power: " << this->_power << endl;
	cout << "Weight: " << this->_weight << endl;

}

CoffeeMachine::CoffeeMachine(string cap, unsigned int weight) : Appliance(weight), _capucñinator(cap) {}

void CoffeeMachine::showSpec() {
	cout << "Coffee" << endl;
	cout << "Capuccinator type: " << this->_capucñinator << endl;
	cout << "Weight: " << this->_weight << endl;
}

VacuumCleaner::VacuumCleaner(unsigned int power, unsigned int weight) : Appliance(weight), _power(power) {}

void VacuumCleaner::showSpec() {
	cout << "Vacuum" << endl;
	cout << "Power: " << this->_power << endl;
	cout << "Weight: " << this->_weight << endl;
}