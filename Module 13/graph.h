#pragma once

#define SIZE 50


class Graph {
    public:
        Graph();
        // ���������� �������
        void addVertex(int vnumber);
        // ���������� �����
        void addEdge(int v1, int v2, int weight = 1);
        // �������� �������
        void delVertex(int vnumber);
        // �������� �����
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

        int matrix[SIZE][SIZE]; // ������� ���������

        int vertexes[SIZE]; // ��������� ������
        int vertexCount; // ���������� ����������� ������
};
