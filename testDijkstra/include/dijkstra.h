#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#define MAX_VERNUM 20        // 最大顶点数
#define MAX_VALUE 99999      // 最大权值
using namespace std;

// 顶点
struct Node
{
    string path;                         // 路径
    string nodeName;                     // 节点名字
    vector<string> next_node;            // 从起点开始到终点所经过的节点，不包括起点
    int value;                           // 路径权值
    bool visit;                          // 是否访问过

    Node() 
    {
        visit = false;
        value = 0;
        nodeName = "";
        next_node.clear();
        path = "";
    }

};

class Dijkstra 
{
public:
    Dijkstra();
    ~Dijkstra();

    void creatGraph();                                  // 创建图
    void dijkstraCpt(string from);                      // dijkstra算法求解最短路径
    void displayTable(string from);                     // 输出路由表

    void modifyEdge(string from, string to, int value); // 修改边
    void addNode(string node_name);                     // 添加顶点
    void deleteNode(string rl);                         // 删除顶点

private:
    int verNum_;                                        // 图的顶点个数
    int **adjMatrix_;                                   // 邻接矩阵
    Node *node_;                                        // 记录各个顶点最短路径的信息            
};

#endif // DIJKSTRA_H