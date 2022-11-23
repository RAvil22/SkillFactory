#include <iostream>
#include <string>
#include "vending.h"

using namespace std;


int main()
{
    Snack* twix = new Snack("Twix");
    Snack* mars = new Snack("Mars");
    Snack* picnic = new Snack("Picnic");
    Snack* peanuts = new Snack();
    Snack* lays = new Snack("Lays");
    SnackSlot* slot1 = new SnackSlot(20);
    SnackSlot* slot2 = new SnackSlot(20);
    SnackSlot* slot3 = new SnackSlot(20);
    SnackSlot* slot4 = new SnackSlot(20);
    SnackSlot* slot5 = new SnackSlot(5);

    slot1->addSnacks(twix, 20);
    slot2->addSnacks(mars, 20);
    slot3->addSnacks(picnic, 20);
    slot4->addSnacks(peanuts, 20);
    slot5->addSnacks(lays, 5);

    SnackVendingMachine* Brendan = new SnackVendingMachine(5, "Silverhand");
    Brendan->service("Silverhand");
    Brendan->addSlot(slot1);
    Brendan->addSlot(slot2);
    Brendan->addSlot(slot3);
    Brendan->addSlot(slot4);
    Brendan->addSlot(slot5);
    Brendan->removeSlot(2);
    cout << "Number of slots " << Brendan->getNumberOfSlots() << endl;
    cout << Brendan->showAvaliableSnacks() << endl;
    Brendan->insertSlot(slot3, 2);
    cout << "Number of slots " << Brendan->getNumberOfSlots() << endl;
    cout << Brendan->showAvaliableSnacks() << endl;
    Brendan->service("Silverhand");

    string choise;
    while (1) {
        cout << "Would you like something to eat?" << endl;
        cout << Brendan->showAvaliableSnacks() << endl;
        cout << "Please, make your choise and enter the number of desirable snack." << endl;
        cin >> choise;
        if (choise == "service") {
            Brendan->service("Silverhand");
            /*Some actions...*/
            Brendan->service("Silverhand");
        }
        int s{ stoi(choise) };
        if (s > 0 && s < (Brendan->getSize())) {
            Brendan->sellSnack(s);
        }
        cout << endl;
    }

    delete Brendan;
    delete slot1;
    delete slot2;

    return 0;
}








