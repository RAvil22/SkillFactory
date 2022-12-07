#pragma once
#include <iostream>
#include"badContainer.h"


class Container{
private:
    int _size; // Размер контейнера
    int* _values; // Указатель на элементы контейнера
public:
    Container(); // Конструктор по умолчанию
    Container(const int s); // Параметризованный конструктор
    Container(const Container& other); // Контейнер копирования
    int& operator[](const int); // Обращение к указанному элементу массива
    int cSize(); // Возврат размера контейнера
    Container& cCopy(const Container& other, int, int); // Копирование элементов указанного контейнера с начального по конечный индекс включительно
    Container& inputBack(const int, const int num, const int pos);  // Добавление указанного числа элементов после указанного индекса
    Container& inputForward(const int, const int num , const int pos); // Добавление указанного числа элементов перед указанным индексом
    Container& pushBack(const int); // Добавление одного элемента в конец контейнера
    Container& pushForward(const int); // Добавление одного элемента в начало контейнера
    Container& cResize(const int); // Переопределение размера контейнера
    Container& cRemoveItem(const int); // Удаление элемента контейнера по указанному индексу
    int cFind(const int); // Поиск слева, возврат индекса первого совпадения
    int crFind(const int); // Поиск справа, возврат индекса первого совпадения
};

