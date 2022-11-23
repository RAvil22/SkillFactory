#pragma once
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

class Snack {
    time_t made; //3374773200 10 Dec 2076
    time_t shelfLife; //3406309200 10 Dec 2077
    string name;
public:
    Snack(void);
    Snack(const string);
    Snack(const Snack& other);
    string getSnackName(void);
    Snack& operator=(const Snack other);
};

class SnackSlot {
    
    unsigned int _numberOfSnacks;
    unsigned int _slotSize;
    Snack** _ptrSnackSlot;
public:
    
    SnackSlot(void);
    SnackSlot(unsigned int);
    SnackSlot(const SnackSlot&);
    ~SnackSlot(void) = default;
    unsigned int getSnackSlotSize(void);
    bool addSnack(Snack*);
    bool addSnacks(Snack*, unsigned int);
    bool removeSnack(void);
    unsigned int getNumberOfSnacks();
    string showSnacks(void);
    string showSnack(void);
};

class SnackVendingMachine {
    bool autorizedAccess;
    bool openingStatus;
    unsigned int filledSlots; //Количество установленных слотов
    unsigned int machineSize; //Количество гнезд под слоты
    float profit;
    string _password;
    SnackSlot** _ptrSnackVendingMachine;
    float* buyingPrices;
    float* sellingPrices;
    float discount;
    time_t present;
public:
    bool machineIntegrity{ true };
public:
    SnackVendingMachine(unsigned int, string);
    ~SnackVendingMachine(void) = default;
    bool setBuyingPrice(float, unsigned int);
    bool setSellingPrice(float, unsigned int);
    float getBuyingPrice(unsigned int);
    float getSellingPrice(unsigned int);
    bool addSlot(SnackSlot*);
    bool insertSlot(SnackSlot*, unsigned int);
    bool removeSlot(unsigned int);
    bool service(string);
    unsigned int getEmptySlotsCount(void);
    string showAvaliableSnacks(void);
    bool sellSnack(unsigned int);
    unsigned int getNumberOfSlots();
    unsigned int getSize();
};
