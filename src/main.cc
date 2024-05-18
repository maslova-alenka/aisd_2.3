#include <iostream>
#include "../include/graph.h"

int main() {
    // Create a graph with integer vertices
    Graph<int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_vertex(5);

    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 3, 2);
    graph.add_edge(3, 4, 2);
    graph.add_edge(4, 2, 1);
    graph.add_edge(4, 3, 3);
    graph.add_edge(3, 5, 4);
    graph.add_edge(1, 3, 1);
    graph.add_edge(5, 4, 5);

    std::cout << "Graph:\n";
    graph.print();

    std::cout << "Vertices: ";
    for (const auto& v : graph.vertices()) {
        std::cout << v << " ";
    }
    std::cout << "\nGraph traversal: ";
    graph.walk(1, [](const int vertex) {std::cout << vertex << " "; });
    std::cout << std::endl;

    Graph<int> g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(4);
    g.add_vertex(5);

    g.add_edge(1, 2, 1);
    g.add_edge(2, 3, 2);
    g.add_edge(3, 4, 2);
    g.add_edge(4, 2, 1);
    g.add_edge(4, 3, 3);
    g.add_edge(3, 5, 4);
    g.add_edge(1, 3, 1);
    g.add_edge(5, 4, 5);

    g.walk(1, [](const int vertex) {std::cout << vertex << " "; });

    //// Find the shortest path
    //std::cout << "\nShortest path from 1 to 5: ";
    //auto path = g.shortest_path(1, 5);
    //for (const auto& vertex : path) {
    //    printVertex;
    //}
    //std::cout << std::endl;

    return 0;
}