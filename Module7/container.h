#pragma once
#include <iostream>
#include"badContainer.h"


class Container{
private:
    int _size; // ������ ����������
    int* _values; // ��������� �� �������� ����������
public:
    Container(); // ����������� �� ���������
    Container(const int s); // ����������������� �����������
    Container(const Container& other); // ��������� �����������
    int& operator[](const int); // ��������� � ���������� �������� �������
    int cSize(); // ������� ������� ����������
    Container& cCopy(const Container& other, int, int); // ����������� ��������� ���������� ���������� � ���������� �� �������� ������ ������������
    Container& inputBack(const int, const int num, const int pos);  // ���������� ���������� ����� ��������� ����� ���������� �������
    Container& inputForward(const int, const int num , const int pos); // ���������� ���������� ����� ��������� ����� ��������� ��������
    Container& pushBack(const int); // ���������� ������ �������� � ����� ����������
    Container& pushForward(const int); // ���������� ������ �������� � ������ ����������
    Container& cResize(const int); // ��������������� ������� ����������
    Container& cRemoveItem(const int); // �������� �������� ���������� �� ���������� �������
    int cFind(const int); // ����� �����, ������� ������� ������� ����������
    int crFind(const int); // ����� ������, ������� ������� ������� ����������
};

