#include"container.h"


using namespace std;

int main(int argc, char** argv){
    try{
        Container cont1{5};
        cout << "Container 1 size " << cont1.cSize() << endl;
        for(int i{1}; i <= cont1.cSize(); i++){cont1[i-1] = i*2;}
        cout << "Container 1 elements ";
        for(int i{0}; i < cont1.cSize(); i++){cout << cont1[i] << " ";}
        cout << endl;

        cont1.cResize(10);
        cout << "New container 1 size " << cont1.cSize() << endl;
        cout << "Container 1 elements ";
        for (int i{ 0 }; i < cont1.cSize(); i++) { cout << cont1[i] << " "; }
        cout << endl;

        cont1.inputBack(5, 4, 2);
        cout << "New container 1 elements ";
        for (int i{ 0 }; i < cont1.cSize(); i++) { cout << cont1[i] << " "; }
        cout << endl;

        cont1.inputForward(9, 5, 6);
        cout << "New container 1 elements ";
        for (int i{ 0 }; i < cont1.cSize(); i++) { cout << cont1[i] << " "; }
        cout << endl;
        
        cont1.pushBack(5);
        cout << "New container 1 elements ";
        for (int i{ 0 }; i < cont1.cSize(); i++) { cout << cont1[i] << " "; }
        cout << endl;

        cont1.pushForward(21);
        cout << "New container 1 size " << cont1.cSize() << endl;
        cout << "New container 1 elements ";
        for (int i{ 0 }; i < cont1.cSize(); i++) { cout << cont1[i] << " "; }
        cout << endl;

        Container cont2 = cont1;
        cout << "Container 2 size " << cont2.cSize() << endl;
        cout << "Container 2 elements ";
        for (int i{ 0 }; i < cont2.cSize(); i++) { cout << cont1[i] << " "; }
        cout << endl;
        
        cout << "First found index from left " << cont2.cFind(5) << endl;
        cout << "First found index from right " << cont2.crFind(5) << endl;
        
        cont2.cResize(5);
        cout << "Container 2 elements ";
        for (int i{ 0 }; i < cont2.cSize(); i++) { cout << cont1[i] << " "; }
        cout << endl;

        Container cont3(5);
        cont3[0] = 82;
        cont3[1] = 97;
        cont3[2] = 118;
        cont3[3] = 105;
        cont3[4] = 108;
        for (int i{ 0 }; i < cont3.cSize(); ++i) {
            cout << cont3[i] << " ";
        }
        cout << endl;

        cont3.cRemoveItem(3);
        for (int i{ 0 }; i < cont3.cSize(); ++i) {
            cout << cont3[i] << " ";
        }
        cout << endl;
    }
    catch(bad_alloc& b){cout << b.what() << endl;}
    catch(const exception& e){cout << e.what() << endl;}
    catch(...){cout << "Unqualified error!" << endl;}

    return 0;
}


