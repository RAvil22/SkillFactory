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
	cout << "�� ᪫��� ��室���� " << size << " ���஭�� ���ன��." << endl;
	cout << "��� ��ᬮ�� 堪�����⨪ ������: " << endl;
	cout << "1 - ���, 2 - ������� ⥫�䮭, 3 - ᬠ��䮭, 4 - �����, "
		"5 - ���஢������� ����, 6 - ��䥬�設�, 7 - �뫥��, 8 - ஡��-�뫥�� " << endl;
	cout << "��� ��室� ������ 0" << endl;
	int choise{ 0 };
	while (open) {
		cin >> choise;
		if (cin.fail()) { 
			//cout << "�����४�� ����" << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
		}
		if (choise < 0 || choise > 8) { cout << "�����४�� ����" << endl; }
		else if (!choise) { break; }
		else { warehouse[choise - 1]->showSpec(); }
	}

	return 0;
}