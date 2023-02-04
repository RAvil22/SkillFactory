#include <iostream>

using namespace std;

bool IsKPeriodic(char arr[], const int arrSize, int k);

int main(){
    const int size{ 18 };
    char arrrgh[size] = { 'A', 'r', 'r', 'r', 'g', 'h', 'A', 'r', 'r', 'r', 'g', 'h', 'A', 'r', 'r', 'r', 'g', 'h' };
    cout << IsKPeriodic(arrrgh, size, 3) << endl;
    return 0;
}

/*Пространственная сложность алгоритма const*/
/*Временная сложность алгоритма N*/
bool IsKPeriodic(char arr[], const int arrSize, int k) {
    if (arrSize % k)return false;//1
    const int subArLen{ arrSize / k };//1

    for (int i{ 1 }; i < k; ++i) {//k
        for (int j{ i * subArLen }; j < (i + 1) * subArLen; ++j) {//subArrLen subArLen = arrSize/k
            if (arr[j] != arr[j-i*subArLen])return false;//1
        }
    }
    return true;
}


