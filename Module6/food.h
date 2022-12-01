#pragma once
#include <iostream>
using namespace std;

class IFood {
public:
    virtual void show() = 0 { cout << "Food item" << endl; };
	virtual ~IFood() = default;
};


class Fruit : virtual public IFood
{
public:
    Fruit(int);
    void show();
protected:
    int _sugar;
};

class Vegetable : virtual public IFood
{
public:
    Vegetable(int salt);
    void show();
protected:
    int _salt;
};

class Apple : public Fruit {
private:
    string _color;
public:
    Apple(int, string);
    void show() override;
};

class Banana : public Fruit {
private:
    int _ripeness;
public:
    Banana(int, int);
    void show() override;
};

class Potato : public Vegetable {
private:
    int _starch;
public:
    Potato(int, int);
    void show() override;
};

class Tomato : public Vegetable {
private:
    string _shape;
public:
    Tomato(int, string);
    void show() override;
};

class Avocado final : public Fruit, Vegetable
{
public:
    Avocado(int sugar, int salt);
    void show() override;
};