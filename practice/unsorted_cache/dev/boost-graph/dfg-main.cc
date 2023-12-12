#include "DFG.hpp"

int main() {
    DFG graph{};
    auto nd = Node{1, 1, {2,3}};
    graph.addNode(nd);
    save_dot_file("graph.dot", graph.graph());
}