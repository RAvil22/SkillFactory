#include "graph.h"
#include "task.h"

using namespace std;

void cifr(Graph& g) {
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);
    g.addVertex(8);

    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(0,3);

    g.addEdge(1,4);

    g.addEdge(2,5);

    g.addEdge(3,6);
    g.addEdge(3,7);
    g.addEdge(3,8);

    g.addEdge(4,3);

    g.addEdge(5,3);
    g.addEdge(5,8);

    g.addEdge(6,7);
    g.addEdge(6,8);
}

void cifr1(Graph& g) {
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);
    g.addVertex(6);
    g.addVertex(7);
    g.addVertex(8);
    g.addVertex(9);
    g.addVertex(10);
    g.addVertex(11);
    g.addVertex(12);
    g.addVertex(13);
    g.addVertex(14);
    g.addVertex(15);
    g.addVertex(16);
    g.addVertex(17);
    g.addVertex(18);
    g.addVertex(19);
    g.addVertex(20);
    g.addVertex(21);
    g.addVertex(22);
    g.addVertex(23);
    g.addVertex(24);
    g.addVertex(25);
    g.addVertex(26);

    g.addEdge(0,1);
    g.addEdge(0,11);
    g.addEdge(0,12);
    g.addEdge(0,18);

    g.addEdge(1,0);
    g.addEdge(1,2);
    g.addEdge(1,3);

    g.addEdge(2,1);
    g.addEdge(2,3);
    g.addEdge(2,4);
    g.addEdge(2,5);

    g.addEdge(3,1);
    g.addEdge(3,2);
    g.addEdge(3,4);
    g.addEdge(3,6);

    g.addEdge(4,2);
    g.addEdge(4,3);
    g.addEdge(4,6);
    g.addEdge(4,7);

    g.addEdge(5,2);
    g.addEdge(5,6);
    g.addEdge(5,7);
    g.addEdge(5,9);

    g.addEdge(6,3);
    g.addEdge(6,4);
    g.addEdge(6,5);
    g.addEdge(6,7);

    g.addEdge(7,4);
    g.addEdge(7,5);
    g.addEdge(7,6);

    g.addEdge(8,5);
    g.addEdge(8,9);
    g.addEdge(8,10);
    g.addEdge(8,26);

    g.addEdge(9,5);
    g.addEdge(9,8);
    g.addEdge(9,10);
    g.addEdge(8,26);

    g.addEdge(10,8);
    g.addEdge(10,9);
    g.addEdge(10,26);

    g.addEdge(11,0);
    g.addEdge(11,12);
    g.addEdge(11,13);
    g.addEdge(11,14);

    g.addEdge(12,0);
    g.addEdge(12,11);
    g.addEdge(12,14);

    g.addEdge(13,11);
    g.addEdge(13,14);
    g.addEdge(13,15);

    g.addEdge(14,11);
    g.addEdge(14,12);
    g.addEdge(14,13);
    g.addEdge(14,15);

    g.addEdge(15,13);
    g.addEdge(15,14);
    g.addEdge(15,16);
    g.addEdge(15,17);

    g.addEdge(16,15);
    g.addEdge(16,17);
    g.addEdge(16,26);

    g.addEdge(18,0);
    g.addEdge(18,19);
    g.addEdge(18,20);
    g.addEdge(18,21);

    g.addEdge(19,18);
    g.addEdge(19,20);
    g.addEdge(19,21);

    g.addEdge(20,18);
    g.addEdge(20,19);
    g.addEdge(20,21);

    g.addEdge(21,18);
    g.addEdge(21,19);
    g.addEdge(21,20);
    g.addEdge(21,22);
    g.addEdge(21,23);
    g.addEdge(21,24);

    g.addEdge(22,21);
    g.addEdge(22,23);
    g.addEdge(22,25);

    g.addEdge(23,21);
    g.addEdge(23,22);
    g.addEdge(23,24);
    g.addEdge(23,25);

    g.addEdge(24,21);
    g.addEdge(24,23);
    g.addEdge(24,25);

    g.addEdge(25,22);
    g.addEdge(25,23);
    g.addEdge(25,24);
    g.addEdge(25,26);

    g.addEdge(26,8);
    g.addEdge(26,9);
    g.addEdge(26,10);
    g.addEdge(26,16);
    g.addEdge(26,17);
    g.addEdge(26,25);
}

void Graph::delVertex(int vnumber) {
    --vertexCount;
    vertexes[vnumber] = 0;
    for(int i{0}; i < SIZE; ++i){
        matrix[vnumber][i] = 0;
        matrix[i][vnumber] = 0;
    }
}

void Graph::delEdge(int v1, int v2) {
   matrix[v1][v2] = 0;
   matrix[v2][v1] = 0;
}

void Graph::depth(int start)
{
    bool visited[SIZE]; // список посещенных вершин
    for(int i =0; i<SIZE; i++)
        visited[i] = false; // инициализируем как непосещенные
    depthInner(start, visited); // запуск алгоритма

    std::cout << std::endl;
}

void Graph::depthInner(int current, bool visited[])
{
    std::cout << "v" << current << " -> "; // вывод текущей
    visited[current]= true; // помечаем как посещенную
    for(int i=0; i<SIZE; i++){
        if(edgeExists(current,i) && !visited[i])
            depthInner(i, visited); // если существует ребро и вершина не посещалась, то пройдем по нему в смежную вершину
    }
}

void Graph::depthLimited(int start, int depth)
{
    if(depth >= 0){++depth;}
    bool visited[SIZE]; // список посещенных вершин
    for(int i =0; i<SIZE; i++)
        visited[i] = false; // инициализируем как непосещенные
    int currDepth{0};
    depthInnerMod1(start, visited, currDepth, depth); // запуск алгоритма

    std::cout << std::endl;
}

void Graph::depthInnerMod1(int current, bool visited[], int currDepth, int depth){
    /*Текущая вершина объявляется посещенной*/
    if(currDepth == depth)return;
    else{
        ++currDepth;
        std::cout << "v" << current << " -> "; // вывод текущей
        visited[current]= true; // помечаем как посещенную
        for(int i=0; i<SIZE; i++){
            if(edgeExists(current,i) && !visited[i])
            depthInnerMod1(i, visited, currDepth, depth); // если существует ребро и вершина не посещалась, то пройдем по нему в смежную вершину
        }
    }

    /*Проверка всех возможных вершин на смежность с текущей*/

}

int Graph::findPathCount(int start, int finish) {
    /*Счетчик возможных путей*/
    int paths{0};
    /*Инициализация счетчика посещенных вершин*/
    bool visited[SIZE];
    for(int i =0; i<SIZE; i++)
        visited[i] = false;
    /*Обход по массиву от исходной до конечной вершины*/
    depthInnerMod(start, finish, visited, paths);

    return paths;
}

void Graph::depthInnerMod(int current, int finish, bool visited[], int& paths){
    if(current == finish){++paths;return;}
    else{
        //std::cout << "v" << current << " -> "; // вывод текущей
        visited[current]= true; // помечаем как посещенную
        for(int i=0; i<SIZE; i++){
        if(edgeExists(current,i) && !visited[i])
        depthInnerMod(i, finish, visited, paths); // если существует ребро и вершина не посещалась, то пройдем по нему в смежную вершину
        }
    }
}

void Graph::width(int start){
    //Очередь вершин для обработки
    int queueToVisit[SIZE] = {0};
    //Счетчик количества вершин для обработки
    int queueCount{0};
    //Счетчик уровней обхода
    int counter{0};
    //Массив обработанности вершин
    bool visited[SIZE] = {false};

    //Ввод в очередь обработки стартовой вершины, инкрементирование счетчика обрабатываемых вершин
    queueToVisit[queueCount++] = start;
    //Цикл прохода вершин

    while(queueCount){
        //Переменная  текущей вершины
        int current = queueToVisit[0];

        //Удаление из очереди текущей вершины, смещение очереди
        queueCount--;
        for(int i=0; i<queueCount; ++i){queueToVisit[i] = queueToVisit[i+1];}
        //Отметка текущей  вершины как обработанной
        visited[current] = true;
        std::cout << "v" << current << " ";

        // поиск смежных вершин и добавление их в очередь

        //Цикл проходит по всем вершинам графа
        for(int i{0}; i < SIZE; ++i){
            //Переменная проверяет, есть ли в очереди рассматриваемая в итерации текущего цикла вершина
            bool alreadyAdded{false};
            //Проверка, есть ли в очереди i-ая вершина
            for(int j{0}; j < queueCount; ++j){
                if(queueToVisit[j] == i){alreadyAdded = true; break;}
            }
            //Если вершина еще не добавлена в очередь, не обработана и существует ребро между текущей вершиной и i-ой
            if(!alreadyAdded && edgeExists(current,i) && !visited[i]){
                //Добавить i-ую вершину в очередь обработки, дать приращение счетчику обработки
                queueToVisit[queueCount++] = i;
            }
        }
        ++counter;//Какое условие?
        std::cout << counter << std::endl;
    }

    std::cout << std::endl;
}
