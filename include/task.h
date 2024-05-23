#ifndef GRAPH_INCLUDE_TASK_H
#define GRAPH_INCLUDE_TASK_H

#include "../include/graph.h"


template<typename Vertex, typename Distance>
Vertex Graph<Vertex, Distance>::find_warehouse_location() {
    Vertex best_location;
    Distance min_total_distance =INFIN;
    bool is_achievable = false;

    for (const auto& v : vertices()) {
        Distance total_distance = 0;
        for (const auto& other_v : vertices()) {
            if (v != other_v) {
                auto path = shortest_path(v, other_v);
                Distance distance = 0;
                if (!path.empty())
                    is_achievable = true;
                for (const auto& edge : path) {
                    distance += edge.distance;
                }
                total_distance = std::max(total_distance, distance);
            }
            if (!is_achievable)
                total_distance = INFIN;
        }

        if (total_distance < min_total_distance) {
            min_total_distance = total_distance;
            best_location = v;
        }
    }

    return best_location;
}
#endif