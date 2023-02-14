#include "autorization.h"
#include <QApplication>
using namespace std;

int main(int argc, char** argv){
    QApplication a(argc, argv);
    Autorization aut;
    aut.show();
    return a.exec();
}


