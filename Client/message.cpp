/*
#include <iostream>
#include <fstream>
using namespace std;

// Клас, описывающий книгу
class BOOK
{
private:
  // Внутренние поля
  string author; // автор
  string title; // название книги
  int year; // год издания
  float price; // стоимость

public:
  // Конструктор
  BOOK(string _author, string _title, int _year, float _price)
  {
    author = _author;
    title = _title;
    year = _year;
    price = _price;
  }

  // Методы чтения данных
  string Author() { return author; }
  string Title() { return title; }
  int Year() { return year; }
  float Price() { return price; }

  // Метод, выводящий значения полей (внутреннее состояние объекта)
  void Print(string msg)
  {
    cout << msg << endl;
    cout << "Author = " << author << endl;
    cout << "Title = " << title << endl;
    cout << "Year = " << year << endl;
    cout << "Price = " << price << endl;
    cout << "-----------------------------" << endl;
  }

  // Методы записи/чтения текущих данных (сериализации)
  bool SaveToFile(const char* filename)
  {
    // 1. Создать экземпляр класса ofstream
    ofstream outF(filename, ios::out | ios::binary);

    // 2. Проверка, создан ли файл,
    //    если не создан то выход с кодом false
    if (!outF.is_open()) return false;

    // 3. Записать данные полей
    // 3.1. Поле author типа string
    // 3.1.1. Определить длину строки типа string
    int len = author.length();

    // 3.1.2. Записать длину строки author
    outF.write((char*)&len, sizeof(int));

    // 3.1.3. Записать каждый символ строки в цикле
    for (int i = 0; i < author.length(); i++)
      outF.write((char*)&author[i], sizeof(author[i]));

    // 3.2. Поле title типа string
    // 3.2.1. Получить длину строки
    len = title.length();

    // 3.2.2. Записать длину строки title
    outF.write((char*)&len, sizeof(int));

    // 3.2.3. Записать посимвольно строку
    for (int i = 0; i < title.length(); i++)
      outF.write((char*)&title[i], sizeof(title[i]));

    // 3.3. Поле year типа int
    outF.write((char*)&year, sizeof(int));

    // 3.4. Поле price типа float
    outF.write((char*)&price, sizeof(float));

    // 4. Закрыть файл
    outF.close();

    // 5. Код возврата
    return true;
  }

  // Чтение массива из файла и запись в текущий экземпляр
  bool ReadFromFile(const char* filename)
  {
    // 1. Создать экземпляр класса ifstream
    ifstream inF(filename, ios::in | ios::binary);

    // 2. Проверка, открыт ли файл успешно
    if (!inF.is_open()) return false;

    // 3. Чтение полей объекта
    // 3.1. Поле author
    // 3.1.1. Считать количество элементов в поле author
    int len;
    inF.read((char*)&len, sizeof(int));

    // 3.1.2. Считать строку в цикле
    char c;
    author = "";
    for (int i = 0; i < len; i++)
    {
      inF.read((char*)&c, sizeof(c));
      author += c;
    }

    // 3.2. Поле title типа string
    // 3.2.1. Получить длину строки
    inF.read((char*)&len, sizeof(int));

    // 3.2.2. Считать строку в цикле
    title = "";
    for (int i = 0; i < len; i++)
    {
      inF.read((char*)&c, sizeof(c));
      title += c;
    }

    // 3.3. Поле year типа int
    inF.read((char*)&year, sizeof(int));

    // 3.4. Поле price типа float
    inF.read((char*)&price, sizeof(float));

    // Закрыть файл
    inF.close();

    // Код возврата
    return true;
  }
};

void main()
{
  // 1. Создать объект типа BOOK
  BOOK obj1("Author", "Title", 2000, 2.55);

  // 2. Сохранить объект obj1
  obj1.Print("obj1");

  // 3. Записать в файл obj1 => "obj1.bin"
  obj1.SaveToFile("obj1.bin");

  // 4. Создать другой объект типа BOOK
  BOOK obj2("--", "--", 3000, 10.88);
  obj2.Print("obj2");

  // 5. Считать данные из файла obj1.bin в объект obj2
  // "obj1.bin" => obj2
  obj2.ReadFromFile("obj1.bin");

  // 6. Вывести прочитанный объект
  obj2.Print("obj2 <= obj1.bin");
}

*/
