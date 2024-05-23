#include <iostream>
#include "../include/graph.h"
#include "../include/task.h"


int main() {
    // Create a graph with integer vertices
    Graph<int, int> graph;
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_vertex(5);

    graph.add_edge(2, 5, 2);
    graph.add_edge(1, 5, 8);
    graph.add_edge(1, 3, 1);
    graph.add_edge(3, 5, 10);
    graph.add_edge(3, 4, 3);
    graph.add_edge(3, 2, 1);
    graph.add_edge(2, 3, 7);
    graph.add_edge(4, 5, 9);
    graph.add_edge(5, 1, 5);

    std::cout << "Graph:\n";
    graph.print_edges();

    std::cout << "The degree of the vertex 4: " << graph.degree(4) << std::endl;
    std::cout << "The order of the graph: " << graph.order() << std::endl;

    std::cout << "Vertices: ";
    for (const auto& v : graph.vertices()) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
    std::cout << "Graph traversal: ";
    graph.walk(1, [](const int vertex) {std::cout << vertex << " "; });
    
    std::cout << std::endl;
    auto path = graph.shortest_path(1, 5);
    std::cout << "Shortest path from 1 to 5: ";
    for (const auto& edge : path) {
        std::cout << edge.from << " -> " << edge.to << " (" << edge.distance << ") ";
    }

    std::cout << std::endl;
    std::cout << "Center: " << graph.find_warehouse_location() << std::endl;

    std::cout << "An edge 3->2 is present in graph: " << graph.has_edge(3, 2) << std::endl;
    std::cout << "An vertex 1 is present in graph: " << graph.has_vertex(1) << std::endl;
    graph.remove_edge(3, 2);
    graph.remove_vertex(1);
    graph.remove_vertex(2);

    graph.print_edges();

    std::cout << "An edge 3->2 is present in graph: " << graph.has_edge(3, 2) << std::endl;
    std::cout << "An vertex 1 is present in graph: " << graph.has_vertex(1) << std::endl;


    return 0;
}