#pragma once
#include <exception>
#include <string>

using namespace std;

class NoOpen : public exception{
public:
NoOpen(string fileName) : exception(), fileName_{fileName} {}
virtual const char* what() const noexcept override {
	string temp{ "ERROR: file " + this->fileName_ + " cannot be opened!" };
    return temp.c_str();
}
private:
string fileName_;
};

class WrongOpen : public exception{
public:
WrongOpen(string fileName) : exception(), fileName_{fileName} {}
virtual const char* what() const noexcept override {
    string temp{ "ERROR: file " + this->fileName_ + " should not be opened!" };
    return temp.c_str();
}
private:
string fileName_;
};

class NoChatType : public exception {
public:
    NoChatType(unsigned int type) : exception(), chatType_{ type } {}
    virtual const char* what() const noexcept override {
        string temp{ "ERROR: Message type " + std::to_string(this->chatType_) + " does not exist!" };
        return temp.c_str();
    }
private:
    unsigned int chatType_;
};


