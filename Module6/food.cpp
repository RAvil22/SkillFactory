#include "food.h"

/*void IFood::show() {
	cout << "Food item" << endl;
}*/

Fruit::Fruit(int sugar) : _sugar(sugar) {}

void Fruit::show() {
    cout << "Basic Fruit sugar: " << _sugar << endl;
}

Vegetable::Vegetable(int salt) : _salt(salt) {}

void Vegetable::show() { 
	cout << "Basic Vegetable, salt: " << _salt << endl;
}

Apple::Apple(int sugar, string color) : Fruit(sugar), _color{color} {}

void Apple::show() {
	cout << _sugar << endl;
	cout << _color << endl;
}

Banana::Banana(int sugar, int ripeness) : Fruit(sugar), _ripeness(ripeness) {}

void Banana::show() {
	cout << _sugar << endl;
	cout << _ripeness << endl;
}

Potato::Potato(int salt, int starch) : Vegetable(salt), _starch(starch) {}

void Potato::show() {
	cout << _salt << endl;
	cout << _starch << endl;
}

Tomato::Tomato(int salt, string shape) : Vegetable(salt), _shape(shape) {}

void Tomato::show() {
	cout << _salt << endl;
	cout << _shape << endl;
}

Avocado::Avocado(int sugar, int salt) : Fruit(sugar), Vegetable(salt) {}

void Avocado::show() {
	cout << _sugar << endl;
	cout << _salt << endl;
}