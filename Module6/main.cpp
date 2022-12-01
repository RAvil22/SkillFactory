#include "devices.h"
#include "appliances.h"
#include "mixed.h"

using namespace std;

int main(int argc, char* argv[]) {
	const int size{ 8 };
	IElectronics* warehouse[size];
	warehouse[0] = new WearableElectronics(4380, "Clocks");
	warehouse[1] = new MobilePhone(96, 4);
	warehouse[2] = new Smartphone(48, 4, 2.5, 0.128);
	warehouse[3] = new Notebook(15.6, 3.0, 1.0, 6);
	warehouse[4] = new MicrowaveOven(600, 5);
	warehouse[5] = new CoffeeMachine("Auto", 6);
	warehouse[6] = new VacuumCleaner(800, 3);
	warehouse[7] = new RobotVacuumCleaner(0.6, 0.05, 4, 2, 600);

	
	bool open{true};
	cout << "На складе находится " << size << " электроных устройств." << endl;
	cout << "Для просмотра хакартеристик введите: " << endl;
	cout << "1 - часы, 2 - мобильный телефон, 3 - смартфон, 4 - ноутбук, "
		"5 - микроволновая печь, 6 - кофемашина, 7 - пылесос, 8 - робот-пылесос " << endl;
	cout << "Для выхода введите 0" << endl;
	int choise{ 0 };
	while (open) {
		cin >> choise;
		if (cin.fail()) { 
			//cout << "Некорректный ввод" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
		}
		if (choise < 0 || choise > 8) { cout << "Некорректный ввод" << endl; }
		else if (!choise) { break; }
		else { warehouse[choise - 1]->showSpec(); }
	}

	return 0;
}