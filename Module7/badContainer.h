#pragma once
#include <exception>

using  namespace std;

class ImpossibleSize : public exception{
    int _size;
public:
    ImpossibleSize(int s) : _size{s} {}
    virtual const char* what() const noexcept override {return "Error! Size cannot be negative!";}
};

class OutOfRange : public exception{
    int _border;
    int _pos;
public:
    OutOfRange(int b, int p) : _border{b}, _pos{p} {}
    virtual const char* what() const noexcept override {return "Error! Out of range!";};
};

class NegativeNumberOfInput : public exception{
    int _number;
public:
    NegativeNumberOfInput(int num) : _number{num} {}
    virtual const char* what() const noexcept override {return "Error! Impossible to input negative number of values!";}
};
