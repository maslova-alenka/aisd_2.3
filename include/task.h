#ifndef GRAPH_INCLUDE_TASK_H
#define GRAPH_INCLUDE_TASK_H

#include "../include/graph.h"

template<typename Vertex, typename Distance = double>
Vertex find_warehouse_location(Graph<Vertex, Distance>& g) {
    Vertex warehouse_location;
    Distance min_average_distance = INFINITY;

    for (const auto& vertex : g.vertices()) {
        Distance average_dist = average_distance(g, vertex);
        if (average_dist < min_average_distance) {
            min_average_distance = average_dist;
            warehouse_location = vertex;
        }
    }

    return warehouse_location;
}

template<typename Vertex, typename Distance = double>
Distance average_distance(Graph<Vertex, Distance>& g, const Vertex& v) {
    Distance total_distance = 0;
    size_t count = 0;

    for (const auto& other_vertex : g.vertices()) {
        if (other_vertex != v) {
            std::vector<typename Graph<Vertex, Distance>::Edge> path = g.shortest_path(v, other_vertex);
            Distance path_distance = 0;
            for (const auto& edge : path) {
                path_distance += edge.distance;
            }
            total_distance += std::max(path_distance, total_distance);
        }
    }

    return total_distance;
}


#endif