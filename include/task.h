#ifndef GRAPH_INCLUDE_TASK_H
#define GRAPH_INCLUDE_TASK_H
//
#include "../include/graph.h"
//
////template<typename Vertex, typename Distance = double>
////Vertex find_warehouse_location(Graph<Vertex, Distance>& g) {
////    if (g.vertices().empty()) {
////        throw std::out_of_range("Graph has no vertices");
////    }
////
////    Vertex warehouse_location;
////    Distance min_average_distance = INFINITY;
////
////    for (const auto& vertex : g.vertices()) {
////        Distance average_dist = average_distance(g, vertex);
////        if (average_dist < min_average_distance) {
////            min_average_distance = average_dist;
////            warehouse_location = vertex;
////        }
////    }
////
////    return warehouse_location;
////}
////
////template<typename Vertex, typename Distance = double>
////Distance average_distance(Graph<Vertex, Distance>& g, const Vertex& v) {
////    Distance total_distance = 0;
////    size_t count = 0;
////
////    for (const auto& other_vertex : g.vertices()) {
////        if (other_vertex != v) {
////            std::vector<typename Graph<Vertex, Distance>::Edge> path = g.shortest_path(other_vertex, v);
////            Distance path_distance = 0;
////            for (const auto& edge : path) {
////                path_distance += edge.distance;
////            }
////            total_distance += path_distance;
////            count++;
////        }
////    }
////
////    //return total_distance;
////    return total_distance / static_cast<Distance>(count);
////}
//
////template<typename Vertex, typename Distance = double>
////Vertex find_warehouse_location(Graph<Vertex, Distance>& graph) {
////    std::vector<Vertex> vertices = graph.vertices();
////    Distance min_avg_distance = INFINITY;
////    Vertex optimal_warehouse;
////
////    for (const Vertex& vertex : vertices) {
////        Distance total_distance = 0;
////        size_t num_vertices = vertices.size();
////
////        for (const Vertex& dest : vertices) {
////            if (vertex != dest) {
////                std::vector<typename Graph<Vertex, Distance>::Edge> shortest_path = graph.shortest_path(vertex, dest);
////                Distance path_distance = 0;
////
////                for (const auto& edge : shortest_path) {
////                    path_distance += edge.distance;
////                }
////
////                total_distance += path_distance;
////            }
////        }
////
////        Distance avg_distance = total_distance / (num_vertices - 1);
////
////        if (avg_distance < min_avg_distance) {
////            min_avg_distance = avg_distance;
////            optimal_warehouse = vertex;
////        }
////    }
////
////    return optimal_warehouse;
////}
// 
// 
//template<typename Vertex, typename Distance>
//Vertex Graph<Vertex, Distance>::find_warehouse_location(Graph<Vertex, Distance>& g) {
//    Vertex optimal_warehouse;
//    Distance min_avg_distance = INFIN;
//
//    for (const auto& vertex : _vertices) {
//        Distance total_distance = 0;
//        size_t count = 0;
//        bool is_achievable = false;
//
//        for (const auto& other_vertex : _vertices) {
//            std::vector<typename Graph<Vertex, Distance>::Edge> path = g.shortest_path(other_vertex, vertex);
//            Distance path_distance = 0;
//            if (!path.empty())
//                is_achievable = true;
//
//            for (const auto& edge : path) {
//                path_distance += edge.distance;
//            }
//
//            total_distance = std::max(total_distance, path_distance);
//        }
//
//        if (!is_achievable)
//            total_distance = INFIN;
//
//        if (total_distance < min_avg_distance) {
//            min_avg_distance = total_distance;
//            optimal_warehouse = vertex;
//        }
//    }
//
//    return optimal_warehouse;
//}


template<typename Vertex, typename Distance>
Vertex Graph<Vertex, Distance>::find_warehouse_location(Graph<Vertex, Distance>& g) {
    if (g._vertices.empty()) {
        return {};
    }

    Distance min_eccentricity = std::numeric_limits<Distance>::max();
    Vertex center;

    std::unordered_map<Vertex, std::vector<Distance>> distances;
    for (const Vertex& start : g._vertices) {
        distances[start] = std::vector<Distance>(g._vertices.size(), std::numeric_limits<Distance>::max());
        auto path = g.shortest_path(start, start);
        distances[start][std::distance(g._vertices.begin(), std::find(g._vertices.begin(), g._vertices.end(), start))] = 0;
        for (const auto& edge : path) {
            size_t index = std::distance(g._vertices.begin(), std::find(g._vertices.begin(), g._vertices.end(), edge.to));
            if (index < g._vertices.size()) {
                distances[start][index] = edge.distance;
            }
        }
    }

    for (const Vertex& start : g._vertices) {
        Distance max_distance = 0;
        bool is_achievable = false;
        for (size_t i = 0; i < g._vertices.size(); ++i) {
            if (distances[start][i] != std::numeric_limits<Distance>::max()) {
                is_achievable = true;
                max_distance = std::max(max_distance, distances[start][i]);
            }
        }

        if (!is_achievable)
            max_distance = std::numeric_limits<Distance>::max();

        if (max_distance < min_eccentricity) {
            min_eccentricity = max_distance;
            center = start;
        }
    }

    return center;
}

//Vertex center;
//Distance min_eccentricity = INF;
//for (const auto& vertex : graph.vertices()) {
//    Distance max_distance = 0;
//    bool is_achievable = false;
//    for (const auto& other_vertex : graph.vertices()) {
//        std::vector<typename Graph<Vertex, Distance>::Edge> path = graph.shortest_path(other_vertex, vertex);
//        Distance distance = 0;
//        if (!path.empty())
//            is_achievable = true;
//        for (const auto& edge : path)
//            distance += edge.distance;
//        max_distance = std::max(max_distance, distance);
//    }
//
//    if (!is_achievable)
//        max_distance = INF;
//
//    if (max_distance < min_eccentricity) {
//        min_eccentricity = max_distance;
//        center = vertex;
//    }
//}
//
//return center;
//}

//template<typename Vertex, typename Distance>
//Vertex Graph<Vertex, Distance>::find_warehouse_location() {
//    Vertex farthest_vertex;
//    Distance max_avg_distance = 0;
//
//    for (const auto& vertex : _vertices) {
//        Distance avg_distance = 0;
//        size_t num_neighbors = 0;
//        for (const auto& edge : exiting_edges(vertex)) {
//            avg_distance += length_shortest_path(vertex, edge.to);
//            num_neighbors++;
//        }
//        if (num_neighbors > 0) {
//            avg_distance /= num_neighbors;
//        }
//
//
//        if (avg_distance > max_avg_distance) {
//            max_avg_distance = avg_distance;
//            farthest_vertex = vertex;
//        }
//    }
//
//    return farthest_vertex;
//}


//}
//
//
//
//
//
//
#endif