#include "dijkstra.h"

int g_nodeNum = 5;   // 顶点数量
int g_edgeNum = 8;   // 边的数量
int g_edge[8][3] = { // 边的集合
    // 起点、终点、权值
    {1, 2, 2},
    {1, 3, 5},
    {2, 3, 2},
    {2, 4, 6},
    {3, 4, 7},
    {3, 5, 1},
    {4, 3, 2},
    {4, 5, 4}
};

Dijkstra::Dijkstra() 
{

}

Dijkstra::~Dijkstra()
{
    delete[] node_;                 // 释放一维数组node内存
    for (int i = 0; i < MAX_VERNUM; i++) {
        delete this->adjMatrix_[i];
    }
    delete adjMatrix_;
} 

// 创建图
void Dijkstra::creatGraph() 
{
    verNum_ = g_nodeNum;                                 // 初始化顶点数和边数
    node_ = new Node[MAX_VERNUM];                        // 保留顶点信息
    adjMatrix_ = new int* [MAX_VERNUM];                  // 数组一维长度为MAX_VERNUM
    for (int i = 0; i < MAX_VERNUM; i++) {
        adjMatrix_[i] = new int[MAX_VERNUM];             // 数组二维长度为MAX_VERNUM
        for (int k = 0; k < MAX_VERNUM; k++) {
            adjMatrix_[i][k] = MAX_VALUE;                // 邻接矩阵初始化为无穷大 
        }
    }


    for (int i = 0; i < g_edgeNum; i++) {
        //对邻接矩阵对应上的点赋值
        adjMatrix_[g_edge[i][0] - 1][g_edge[i][1] - 1] = g_edge[i][2];
    }

    for (int i = 0; i < this->verNum_; i++) { // 初始化node数组的编号
        node_[i].nodeName = "r" + to_string(i+1);
    }
}

void Dijkstra::dijkstraCpt(string from) {
    int f, i, j ,k;
    for (f = 0; f < this->verNum_; f++) {
        if(from.compare(node_[f].nodeName) == 0) {
            break;
        }
    }
    for (i = 0; i < this->verNum_; i++) { //初始化node数组
        node_[i].path = from + "-->" + node_[i].nodeName;
        node_[i].next_node.clear();
        node_[i].next_node.push_back(node_[i].nodeName);
        node_[i].value = adjMatrix_[f][i];
        node_[i].visit = false;
    }

    node_[f].value = 0; //设置起点到起点的路径为0
    node_[f].visit = true;

    for (i = 1; i < this->verNum_; i++) { //计算剩余的顶点的最短路径
        int temp = 0;                     //temp用于保存当前node数组中最小的那个下标
        int min = MAX_VALUE;              //min记录的当前的最小值

        for (j = 0; j < this->verNum_; j++) {
            if (!node_[j].visit && node_[j].value < min) {
                min = node_[j].value;
                temp = j;
            }
        }

        node_[temp].visit = true;         //把temp对应的顶点加入到已经找到的最短路径的集合中

        for (k = 0; k < this->verNum_; k++) {
            //起点到T的最短路径 + T到T的邻接顶点P的权值  < 当前记录起点到P的最短路径
            if(!node_[k].visit && adjMatrix_[temp][k] != MAX_VALUE && (node_[temp].value + adjMatrix_[temp][k] < node_[k].value)){
                node_[k].path = node_[temp].path + "-->" + node_[k].nodeName;
                node_[k].next_node = node_[temp].next_node;
                node_[k].next_node.push_back(node_[k].nodeName);
                node_[k].value = node_[temp].value + adjMatrix_[temp][k];
            }

        }

    }

    displayTable(from);

}


void Dijkstra::dijkstraCpt(string from, string to) {
    int f, i, j, k, t;
    for (f = 0; f < this->verNum_; f++) {
        if (from.compare(node_[f].nodeName) == 0) {
            break;
        }
    }

    for (t = 0; t < this->verNum_; t++) {
        if (to.compare(node_[t].nodeName) == 0) {
            break;
        }
    }

    // 初始化node节点

    for (i = 0; i < this->verNum_; i++) {
        node_[i].path = from + "-->" + node_[i].nodeName;
        node_[i].next_node.clear();
        node_[i].next_node.push_back(node_[i].nodeName);
        node_[i].value = adjMatrix_[f][i];
        node_[i].visit = false;
    }

    node_[f].value = 0;                // 设置起点到起点的路径为0；
    node_[f].visit = true;

    if (from == to) {
        displayTable(from, to);
        return;
    }

    for (i = 1; i < this->verNum_; i++) { //计算剩余的顶点的最短路径
        int temp = 0;                     //temp用于保存当前node数组中最小的那个下标
        int min = MAX_VALUE;              //min记录的当前的最小值

        for (j = 0; j < this->verNum_; j++) {
            if (!node_[j].visit && node_[j].value < min) {
                min = node_[j].value;
                temp = j;
            }
        }

        node_[temp].visit = true;         //把temp对应的顶点加入到已经找到的最短路径的集合中

        if (node_[temp].nodeName == to) {
            displayTable(from, to);
            return;
        }

        for (k = 0; k < this->verNum_; k++) {
            //起点到T的最短路径 + T到T的邻接顶点P的权值  < 当前记录起点到P的最短路径
            if(!node_[k].visit && adjMatrix_[temp][k] != MAX_VALUE && (node_[temp].value + adjMatrix_[temp][k] < node_[k].value)){
                node_[k].path = node_[temp].path + "-->" + node_[k].nodeName;
                node_[k].next_node = node_[temp].next_node;
                node_[k].next_node.push_back(node_[k].nodeName);
                node_[k].value = node_[temp].value + adjMatrix_[temp][k];
            }
        }
    }
}

//输出路由表
void Dijkstra::displayTable(string from)
{
    int i;
    bool flag = false;
    for (int i = 0; i < this->verNum_; i++) {
        if (from.compare(node_[i].nodeName) == 0) {
            flag = true;
        }
    }
    if (flag == false) {
        std::cout << "can not found node" << std::endl;
    } else {
        std::cout << "size: " << node_[1].next_node.size() << std::endl;
        for (i = 0; i < this->verNum_; i++) 
        {
            std::cout << from;
            // std::cout << "dest: " <<  node_[i].nodeName << " ";
            for (int j = 0; j < node_[i].next_node.size(); j++) {
                std::cout << "-->" <<node_[i].next_node[j];
            }
            std::cout << std::endl;
        }
    }
}


void Dijkstra::displayTable(string from, string to)         // 输出起终点路由表
{
    int i, f, t;
    bool from_flag = false;
    bool to_flag = false;
    for (int i = 0; i < this->verNum_; i++) {
        if (from.compare(node_[i].nodeName) == 0) {
            from_flag = true;
            f = i;
        }
        if (to.compare(node_[i].nodeName) == 0) {
            to_flag = true;
            t = i;
        }
    }
    if (from_flag == false || to_flag == false) {
        std::cout << "can not found node" << std::endl;
    }else {
        std::cout << from;
        for (int j = 0; j < node_[t].next_node.size(); j++) {
            std::cout << "-->" <<node_[t].next_node[j];
        }
        std::cout << std::endl;  
    }
}





