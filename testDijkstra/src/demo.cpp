// 参考链接
// https://blog.csdn.net/weixin_40355471/article/details/130655729

#include <iostream>
#include "dijkstra.h"


int main() {
    Dijkstra mDijkstra;
    mDijkstra.creatGraph();
    mDijkstra.dijkstraCpt("r1");
    std::cout << "********************" << std::endl;
    mDijkstra.dijkstraCpt("r1", "r5");
}