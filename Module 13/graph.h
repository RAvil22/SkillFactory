#pragma once

#define SIZE 50


class Graph {
    public:
        Graph();
        // добавление вершины
        void addVertex(int vnumber);
        // добавление ребра
        void addEdge(int v1, int v2, int weight = 1);
        // удаление вершины
        void delVertex(int vnumber);
        // удаление ребра
        void delEdge(int v1, int v2);
        void depth(int start);
        void depthLimited(int start, int depth);
        void width(int start);
        void widthMod(int start, int depth);
        int findPathCount(int from, int to);
    private:

        void depthInner(int current, bool visited[]);
        void depthInnerMod(int current, int finish, bool visited[], int& p);
        void depthInnerMod1(int current, bool visited[], int currDepth, int depth);
        bool edgeExists(int v1, int v2);
        bool vertexExists(int v);

        int matrix[SIZE][SIZE]; // матрица смежности

        int vertexes[SIZE]; // хранилище вершин
        int vertexCount; // количество добавленных вершин
};
