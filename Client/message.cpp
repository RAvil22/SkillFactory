/*
#include <iostream>
#include <fstream>
using namespace std;

// ����, ����������� �����
class BOOK
{
private:
  // ���������� ����
  string author; // �����
  string title; // �������� �����
  int year; // ��� �������
  float price; // ���������

public:
  // �����������
  BOOK(string _author, string _title, int _year, float _price)
  {
    author = _author;
    title = _title;
    year = _year;
    price = _price;
  }

  // ������ ������ ������
  string Author() { return author; }
  string Title() { return title; }
  int Year() { return year; }
  float Price() { return price; }

  // �����, ��������� �������� ����� (���������� ��������� �������)
  void Print(string msg)
  {
    cout << msg << endl;
    cout << "Author = " << author << endl;
    cout << "Title = " << title << endl;
    cout << "Year = " << year << endl;
    cout << "Price = " << price << endl;
    cout << "-----------------------------" << endl;
  }

  // ������ ������/������ ������� ������ (������������)
  bool SaveToFile(const char* filename)
  {
    // 1. ������� ��������� ������ ofstream
    ofstream outF(filename, ios::out | ios::binary);

    // 2. ��������, ������ �� ����,
    //    ���� �� ������ �� ����� � ����� false
    if (!outF.is_open()) return false;

    // 3. �������� ������ �����
    // 3.1. ���� author ���� string
    // 3.1.1. ���������� ����� ������ ���� string
    int len = author.length();

    // 3.1.2. �������� ����� ������ author
    outF.write((char*)&len, sizeof(int));

    // 3.1.3. �������� ������ ������ ������ � �����
    for (int i = 0; i < author.length(); i++)
      outF.write((char*)&author[i], sizeof(author[i]));

    // 3.2. ���� title ���� string
    // 3.2.1. �������� ����� ������
    len = title.length();

    // 3.2.2. �������� ����� ������ title
    outF.write((char*)&len, sizeof(int));

    // 3.2.3. �������� ����������� ������
    for (int i = 0; i < title.length(); i++)
      outF.write((char*)&title[i], sizeof(title[i]));

    // 3.3. ���� year ���� int
    outF.write((char*)&year, sizeof(int));

    // 3.4. ���� price ���� float
    outF.write((char*)&price, sizeof(float));

    // 4. ������� ����
    outF.close();

    // 5. ��� ��������
    return true;
  }

  // ������ ������� �� ����� � ������ � ������� ���������
  bool ReadFromFile(const char* filename)
  {
    // 1. ������� ��������� ������ ifstream
    ifstream inF(filename, ios::in | ios::binary);

    // 2. ��������, ������ �� ���� �������
    if (!inF.is_open()) return false;

    // 3. ������ ����� �������
    // 3.1. ���� author
    // 3.1.1. ������� ���������� ��������� � ���� author
    int len;
    inF.read((char*)&len, sizeof(int));

    // 3.1.2. ������� ������ � �����
    char c;
    author = "";
    for (int i = 0; i < len; i++)
    {
      inF.read((char*)&c, sizeof(c));
      author += c;
    }

    // 3.2. ���� title ���� string
    // 3.2.1. �������� ����� ������
    inF.read((char*)&len, sizeof(int));

    // 3.2.2. ������� ������ � �����
    title = "";
    for (int i = 0; i < len; i++)
    {
      inF.read((char*)&c, sizeof(c));
      title += c;
    }

    // 3.3. ���� year ���� int
    inF.read((char*)&year, sizeof(int));

    // 3.4. ���� price ���� float
    inF.read((char*)&price, sizeof(float));

    // ������� ����
    inF.close();

    // ��� ��������
    return true;
  }
};

void main()
{
  // 1. ������� ������ ���� BOOK
  BOOK obj1("Author", "Title", 2000, 2.55);

  // 2. ��������� ������ obj1
  obj1.Print("obj1");

  // 3. �������� � ���� obj1 => "obj1.bin"
  obj1.SaveToFile("obj1.bin");

  // 4. ������� ������ ������ ���� BOOK
  BOOK obj2("--", "--", 3000, 10.88);
  obj2.Print("obj2");

  // 5. ������� ������ �� ����� obj1.bin � ������ obj2
  // "obj1.bin" => obj2
  obj2.ReadFromFile("obj1.bin");

  // 6. ������� ����������� ������
  obj2.Print("obj2 <= obj1.bin");
}

*/
