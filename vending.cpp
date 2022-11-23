#include "vending.h"

using namespace std;

Snack::Snack(const string name){
    if(name.size()){this->name = name;}
    else {this->name = "noname";}
    this->made = 3374773200;
    this->shelfLife = 3406309200;
}

Snack::Snack(void) : name{"noname"}, made{3374773200}, shelfLife{3406309200} {}

Snack::Snack(const Snack& other){
    if (this != &other)
    {
        name = other.name;
        made = other.made;
        shelfLife = other.shelfLife;
    }
}

Snack& Snack::operator=(const Snack other) {
        if (this != &other)
        {
            name = other.name;
            made = other.made;
            shelfLife = other.shelfLife;
        }
        return *this;
 }

string Snack::getSnackName(void){
    return this->name;
}

SnackSlot::SnackSlot(void):_slotSize{10}, _numberOfSnacks{0} {
    this->_ptrSnackSlot = new Snack*[_slotSize];
}

SnackSlot::SnackSlot(unsigned int slotSize){
    this->_slotSize = slotSize;
	this->_ptrSnackSlot = new Snack*[_slotSize];
    this->_numberOfSnacks = 0;
}

bool SnackSlot::addSnack(Snack* snack) {
    if (this->_numberOfSnacks < this->_slotSize) {
        this->_ptrSnackSlot[_numberOfSnacks] = snack;
        ++_numberOfSnacks;
        return true;
    }
    else { return false; }
}

bool SnackSlot::addSnacks(Snack* snack, unsigned int add) {
    if (this->_numberOfSnacks + add <= _slotSize) {
        unsigned int limit = add + this->_numberOfSnacks;
        for (unsigned int i{ this->_numberOfSnacks }; i < limit; ++i) {
            this->_ptrSnackSlot[i] = snack;
            _numberOfSnacks += 1;
        }
        return true;
    }
    else { return false; }
}

bool SnackSlot::removeSnack(void) {
    if (_numberOfSnacks > 0) {
        this->_numberOfSnacks -= 1;
        this->_ptrSnackSlot[_numberOfSnacks] = nullptr;
        return true;
    }
    else { return false; }
}

SnackSlot::SnackSlot(const SnackSlot& other) {
    if (this != &other) {
        this->_numberOfSnacks = other._numberOfSnacks;
        this->_ptrSnackSlot = other._ptrSnackSlot;
    }
}

unsigned int SnackSlot::getSnackSlotSize(void){
    return this->_slotSize;
}

string SnackSlot::showSnacks(void) {
    string result{"Slot consists: "};
    for (unsigned int i{0}; i < this->_numberOfSnacks; ++i) {
        result += this->_ptrSnackSlot[i]->getSnackName();
        result += " ";
    }
    return result;
}

string SnackSlot::showSnack(void) {
    string result;
    if (this->_ptrSnackSlot[0] != nullptr) {
        result = this->_ptrSnackSlot[0]->getSnackName();
    }
    return result;
}

unsigned int SnackSlot::getNumberOfSnacks() {
    return this->_numberOfSnacks;
}



SnackVendingMachine::SnackVendingMachine(unsigned int size, string password) : autorizedAccess{ false }, openingStatus{false},
filledSlots{ 0 }, machineSize{ size }, _password{ password }, discount{ 0 }, present{0} {
    this->_ptrSnackVendingMachine = new SnackSlot*[machineSize];
    for (unsigned int i{ 0 }; i < this->machineSize; ++i) {
        this->_ptrSnackVendingMachine[i] = nullptr;
    }
    this->buyingPrices = new float[machineSize];
    this->sellingPrices = new float[machineSize];
    for (unsigned int i{ 0 }; i < machineSize; i++) {
        buyingPrices[i] = 0.25;
        sellingPrices[i] = 2.0;
    }
}

bool SnackVendingMachine::service(string password) {
    if (password == this->_password) {
        if (!(this->autorizedAccess)) {
            this->autorizedAccess = true;
            this->openingStatus = true;
            //cout << "Доступ к содержимому открыт." << endl;
            cout << "Access granted." << endl;
        }
        else {
            this->openingStatus = false;
            this->autorizedAccess = false;
            //cout << "Доступ к содержимому закрыт." << endl;
            cout << "Access closed." << endl;
        }
    }
    else { return false; }
}

bool SnackVendingMachine::addSlot(SnackSlot* slot) {
    if (this->autorizedAccess) {
        if (this->filledSlots < this->machineSize) {
            this->_ptrSnackVendingMachine[this->filledSlots] = slot;
            this->filledSlots += 1;
            return true;
        }
        else { return false; }
    }
    else { return false; }
}

bool SnackVendingMachine::insertSlot(SnackSlot* slot, unsigned int position) {
    if (this->autorizedAccess) {
        if (position < this->machineSize && this->_ptrSnackVendingMachine[position] == nullptr) {
            this->filledSlots += 1;
            this->_ptrSnackVendingMachine[position] = slot;
        }
        else { return false; }
    }
    else { return false; }
}

bool SnackVendingMachine::removeSlot(unsigned int number) {
    if (this->autorizedAccess) {
        if (number <= this->filledSlots && this->filledSlots > 0) {
            this->_ptrSnackVendingMachine[number] = nullptr;
            this->filledSlots -= 1;
            return true;
        }
    }
    else { return false; }
}

string SnackVendingMachine::showAvaliableSnacks(void) {
    string result{"I can offer you this:\n"};
    for (unsigned int i{ 0 }; i < this->machineSize; i++) {
           if(_ptrSnackVendingMachine[i] != nullptr){
                result += to_string(i) + ". " + (this->_ptrSnackVendingMachine[i]->showSnack()) + " " +
            to_string(this->getSellingPrice(i)*(1-this->discount)) + "\$\n";
            auto point{result.rfind('.')}; //Выкинуть лишние нули
            result.erase(point+2, 4);
        }
    }
    return result;
}

bool SnackVendingMachine::sellSnack(unsigned int slotNum) {
    if(this->_ptrSnackVendingMachine[slotNum] != nullptr){
       if (this->_ptrSnackVendingMachine[slotNum]->getNumberOfSnacks()) {
        this->_ptrSnackVendingMachine[slotNum]->removeSnack();
        if (this->profit > (getSellingPrice(slotNum) - getBuyingPrice(slotNum)) * 20
            && time(NULL)-this->present > 28800) {
            cout << "Know what? Take it free. It is my gift for such adorable person!" << endl;
            return true;
        }
        this->profit += this->getSellingPrice(slotNum) * (1 - discount);
        this->discount = 0;
        return true;
    }
    else {
        cout << "Sorry, i do not have any of this! Please, take a discount as my apologize." << endl;
        this->discount = 0.05;
        return false;
    }
    }
}

unsigned int SnackVendingMachine::getSize() {
    return this->machineSize;
}

unsigned int SnackVendingMachine::getNumberOfSlots() {
    return this->filledSlots;
}

float SnackVendingMachine::getBuyingPrice(unsigned int item) {
    return this->buyingPrices[item];
}

float SnackVendingMachine::getSellingPrice(unsigned int item) {
    return this->sellingPrices[item];
}

bool SnackVendingMachine::setBuyingPrice(float price, unsigned int item) {
    if (price > 0 && this->autorizedAccess == true) {
        this->buyingPrices[item] = price;
        return true;
    }
    else { return false; }
}

bool SnackVendingMachine::setSellingPrice(float price, unsigned int item) {
    if (price > 0 && this->autorizedAccess == true) {
        this->sellingPrices[item] = price;
        return true;
    }
    else { return false; }
}
