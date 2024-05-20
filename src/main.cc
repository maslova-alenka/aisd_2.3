#include <iostream>
#include "../include/graph.h"
#include "../include/task.h"


int main() {
    // Create a graph with integer vertices
   /* Graph<int> graph;
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
    graph.add_edge(5, 4, 5);*/

    Graph<int, int> graph;

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_vertex(5);
    graph.add_vertex(6);

    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 3, 2);
    graph.add_edge(3, 4, 1);
    graph.add_edge(4, 5, 3);
    graph.add_edge(5, 6, 1);
    graph.add_edge(6, 1, 2);
    graph.add_edge(1, 3, 3);
    graph.add_edge(3, 5, 2);
    graph.add_edge(5, 1, 1);

    int center = graph.find_warehouse_location(graph);
    std::cout << "Center: " << center << std::endl;

    std::cout << "Graph:\n";
    //graph.print();
    graph.print_edges();

    std::cout << "The degree of the vertex 4: " << graph.degree(4) << std::endl;
    std::cout << "The order of the graph: " << graph.order() << std::endl;

    /*std::cout << "Vertices: ";
    for (const auto& v : graph.vertices()) {
        std::cout << v << " ";
    }*/
    std::cout << "\nGraph traversal: ";
    graph.walk(1, [](const int vertex) {std::cout << vertex << " "; });
    std::cout << std::endl;

    auto exiting_edges = graph.exiting_edges(1);
    for (const auto& edge : exiting_edges) {
        std::cout << "Edge from " << edge.from << " to " << edge.to << " with distance " << edge.distance << std::endl;
    }


    auto path = graph.shortest_path(1, 4);
    std::cout << "Shortest path from 1 to 2: ";
    for (const auto& edge : path) {
        std::cout << edge.from << " -> " << edge.to << " (" << edge.distance << ") ";
    }

    std::cout <<"lenght " << graph.length_shortest_path(1, 2) << std::endl;

    std::cout << "Center: " << graph.find_warehouse_location(graph) << std::endl;

    std::cout << "An edge 5->4 is present in graph: " << graph.has_edge(5, 4) << std::endl;
    std::cout << "An vertex 1 is present in graph: " << graph.has_vertex(1) << std::endl;
    graph.remove_edge(5, 4);
    graph.remove_vertex(1);
    graph.remove_vertex(4);

    graph.print_edges();

   // graph.print();

    std::cout << "An edge 5->4 is present in graph: " << graph.has_edge(5, 4) << std::endl;
    std::cout << "An vertex 1 is present in graph: " << graph.has_vertex(1) << std::endl;

   /* int warehouse_location =find_warehouse_location(graph);
    std::cout << "Warehouse location: " << warehouse_location << std::endl;*/

    //std::cout << "Center: " << find_warehouse_location(graph) << std::endl;


   /* Graph<int> g;
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(4);
    g.add_vertex(5);

    g.add_edge(1, 4, 1.0);
    g.add_edge(4, 3, 1.0);
    g.add_edge(3, 5, 1.0);
    g.add_edge(5, 2, 1.0);

    g.walk(1, [](const int vertex) {std::cout << vertex << " "; });*/

    // Find the shortest path
    //std::cout << "\nShortest path from 1 to 5: ";
    //auto path = g.shortest_path(1, 5);
    //for (const auto& vertex : path) {
    //    std::cout << vertex << " ";
    //}
    //std::cout << std::endl;

    //auto path = g.shortest_path(1, 2);
    //std::cout << "Shortest path from 1 to 2: ";
    //for (const auto& edge : path) {
    //    std::cout << edge.from << " -> " << edge.to << " (" << edge.distance << ") ";
    //}

    return 0;
}