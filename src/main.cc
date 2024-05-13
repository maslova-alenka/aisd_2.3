#include "../include/graph.h"

int main() {
    Graph<int, double> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(1, 2, 5.0);

    std::vector<int> vertices = graph.vertices();
    for (const auto& vertex : vertices) {
        std::cout << "Vertex: " << vertex << std::endl;
    }

    return 0;
}