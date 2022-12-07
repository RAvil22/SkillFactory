#include "container.h"

using namespace std;

 
Container::Container() : _size{ 0 } {
    this->_values = nullptr;
}

Container::Container(const int s) : _size{ s } {
    if (_size < 0) { throw ImpossibleSize(this->_size); }

    if (this->_size) { this->_values = new int[_size]; }
    else { this->_values = nullptr; }
}

Container::Container(const Container& other) {
    if (this != &other) {
        if (this->_size) { delete[] this->_values; }
        this->_size = other._size;
        this->_values = new int[this->_size];
        for (int i{ 0 }; i < other._size; ++i) {
            this->_values[i] = other._values[i];
        }
    }
}

int& Container::operator[](const int pos) {
    if (pos >= this->_size) { throw OutOfRange(this->_size - 1, pos); }
    else if (pos < 0) { throw OutOfRange(0, pos); }
    else {
        return this->_values[pos];
    }
}

int Container::cSize() {
    return this->_size;
}

Container& Container::cCopy(const Container& other, int s, int e) {
    if (s < 0) { throw OutOfRange(0, s); }
    else if (e >= other._size) { throw OutOfRange(other._size - 1, e); }
    if (e - s >= this->_size) { throw OutOfRange(this->_size - 1, e); }
    for (int i{ 0 }; i < e - s + 1; ++i) {
        this->_values[i] = other._values[s + i];
    }
    return *this;
}

Container& Container::inputBack(const int newVal, const int num, const int pos) {
    if (num < 0) { throw NegativeNumberOfInput(num); }
    else if (num == 0) { return *this; }

    if (!(this->_size)) {
        this->_size += num;
        this->_values = new int[this->_size];
        for (int i{ 0 }; i < this->_size; ++i) {
            this->_values[i] = newVal;
        }
        return *this;
    }

    if (pos >= this->_size) { throw OutOfRange(this->_size - 1, pos); }
    else if (pos < 0) { throw OutOfRange(0, pos); }

    if (pos == this->_size - 1) {
        int* newValues = new int[this->_size + num];
        for (int i{ 0 }; i < this->_size; ++i) {
            newValues[i] = this->_values[i];
        }
        for (int i{ this->_size }; this->_size + num; ++i) {
            newValues[i] = newVal;
        }
        this->_size += num;
        delete[] this->_values;
        this->_values = new int[this->_size];
        for (int i{ 0 }; i < this->_size; ++i) {
            this->_values[i] = newValues[i];
        }
        delete[] newValues;
        return *this;
    }

    this->_size += num;
    int* newValues;
    newValues = new int[this->_size];

    for (int i{ 0 }; i < _size; ++i) {
        if (i < pos) {
            newValues[i] = _values[i];
        }
        else if (i == pos) {
            newValues[i] = _values[i];
            for (int j{ 1 }; j <= num; ++j) { newValues[i + j] = newVal; }
            i += num;
        }
        else if (i > pos) {
            newValues[i] = _values[i - num];
        }
    }
    delete[] this->_values;

    this->_values = new int[this->_size];
    for (int i{ 0 }; i < this->_size; ++i) {
        this->_values[i] = newValues[i];
    }
    delete[] newValues;
    return *this;
}

 
Container& Container::inputForward(const int newVal, const int num, const int pos) {
    if (num < 0) { throw NegativeNumberOfInput(num); }
    else if (num == 0) { return *this; }

    if (!(this->_size)) {
        this->_size += num;
        this->_values = new int[this->_size];
        for (int i{ 0 }; i < this->_size; ++i) {
            this->_values[i] = newVal;
        }
        return *this;
    }

    if (pos >= this->_size) { throw OutOfRange(this->_size - 1, pos); }
    else if (pos < 0) { throw OutOfRange(0, pos); }

    if (pos == 0) {
        this->_size += num;
        int* newValues = new int[this->_size];
        for (int i{ 0 }; i < num; ++i) { newValues[i] = newVal; }
        for (int i{ num }; i < this->_size; i++) { newValues[i] = this->_values[i - num]; }
        delete[] this->_values;
        this->_values = new int[this->_size];
        for (int i{ 0 }; i < this->_size; ++i) { this->_values[i] = newValues[i]; }
        delete[] newValues;
        return *this;
    }

    this->_size += num;
    int* newValues;
    newValues = new int[this->_size];
    int pos1{ pos };
    --pos1;
    for (int i{ 0 }; i < _size; ++i) {
        if (i < pos1) {
            newValues[i] = _values[i];
        }
        else if (i == pos1) {
            newValues[i] = _values[i];
            for (int j{ 1 }; j <= num; ++j) { newValues[i + j] = newVal; }
            i += num;
        }
        else if (i > pos1) {
            newValues[i] = _values[i - num];
        }
    }
    delete[] this->_values;

    this->_values = new int[this->_size];
    for (int i{ 0 }; i < this->_size; ++i) {
        this->_values[i] = newValues[i];
    }
    delete[] newValues;
    return *this;

}

 
Container& Container::pushBack(const int newVal) {
    int* newValues = new int[this->_size + 1];
    for (int i{ 0 }; i < this->_size; ++i) { newValues[i] = this->_values[i]; }
    newValues[this->_size] = newVal;
    delete[] this->_values;
    this->_size += 1;
    this->_values = new int[this->_size];
    for (int i{ 0 }; i < this->_size; ++i) { this->_values[i] = newValues[i]; }
    delete[] newValues;
    return *this;
}

 
Container& Container::pushForward(const int newVal) {
    int* newValues = new int[this->_size + 1];
    newValues[0] = newVal;
    for (int i{ 0 }; i < this->_size; ++i) { newValues[i + 1] = this->_values[i]; }
    delete[] this->_values;
    this->_size += 1;
    this->_values = new int[this->_size];
    for (int i{ 0 }; i < this->_size; ++i) { this->_values[i] = newValues[i]; }
    delete[] newValues;
    return *this;
}

 
Container& Container::cResize(int newSize) {
    if (newSize < 0) { throw ImpossibleSize(newSize); }
    if (newSize == 0 && this->_size != 0) {
        this->_size = 0;
        delete[] this->_values;
        return *this;
    }
    if (newSize == this->_size) { return *this; }

    int* newValues = new int[newSize];
    if (this->_size > newSize) {
        for (int i{ 0 }; i < newSize; ++i) { newValues[i] = this->_values[i]; }
        delete[] this->_values;
        this->_size = newSize;
        this->_values = new int[this->_size];
        for (int i{ 0 }; i < this->_size; ++i) { this->_values[i] = newValues[i]; }
        delete[] newValues;
    }
    else {
        for (int i{ 0 }; i < this->_size; ++i) { newValues[i] = this->_values[i]; }
        delete[] this->_values;
        this->_values = new int[newSize];
        for (int i{ 0 }; i < this->_size; ++i) { this->_values[i] = newValues[i]; }
        for (int i{ this->_size }; i < newSize; i++) { this->_values[i] = 0; }
        this->_size = newSize;
        delete[] newValues;
    }
    return *this;
}

 
Container& Container::cRemoveItem(const int pos) {
    if (pos < 0 || pos >= this->_size) { throw OutOfRange(this->_size - 1, pos); }
    int* newValues = new int[this->_size - 1];
    int j{ 0 };
    for (int i{ 0 }; i < this->_size; ++i) {
        if (i != pos) { newValues[j] = this->_values[i]; ++j; }
    }
    this->_size -= 1;
    delete this->_values;
    this->_values = new int[this->_size];
    for (int i{ 0 }; i < this->_size; ++i) { this->_values[i] = newValues[i]; }
    delete[] newValues;
    return *this;
}

 
int Container::cFind(const int val) {
    int fail{ -1 };
    for (int i{ 0 }; i < this->_size; ++i) { if (this->_values[i] == val) { return i; } }
    return fail;
}

 
int Container::crFind(const int val) {
    int fail{ -1 };
    for (int i{ this->_size - 1 }; i >= 0; --i) { if (this->_values[i] == val) { return i; } }
    return fail;
}