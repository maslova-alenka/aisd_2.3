#ifndef GRAPH_INCLUDE_GRAPH_H
#define GRAPH_INCLUDE_GRAPH_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>
#include <set>

#define EPSILON 1e-10
#define INFINITY 1e9


template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from;
        Vertex to;
        Distance distance;
    };

private:
    std::vector<Vertex> _vertices;
    std::unordered_map<Vertex, std::vector<Edge>> _edges;

public:

    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex& v) const {
        return std::find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
    }

    void add_vertex(const Vertex& v) {
        if (has_vertex(v)) 
            throw std::invalid_argument("add_vertex");
        _vertices.push_back(v);
        _edges[v] = { };
    }

    bool remove_vertex(const Vertex& v) {
        auto it = std::find(_vertices.begin(), _vertices.end(), v);
        if (it == _vertices.end())
            return false;
        _vertices.erase(it);
        _edges.erase(v);
        for (auto& vertex : _vertices) {
            auto& edges = _edges.at(vertex);
            edges.erase(std::remove_if(edges.begin(), edges.end(), [v](const Edge& edge) {return edge.to == v; }), edges.end());
        }
        return true;
    }

    std::vector<Vertex> vertices() const {
        return _vertices;
    }


    //проверка-добавление-удаление ребер
    void add_edge(const Vertex& from, const Vertex& to,const Distance& d) {
        if (!has_vertex(from) || !has_vertex(to))
            return;
        _edges[from].push_back({ from, to, d });
    }

    bool remove_edge(const Vertex& from, const Vertex& to) {
        if (!has_edge(from, to)) return false;
        auto& edges = _edges.at(from);

        edges.erase(std::remove_if(edges.begin(), edges.end(), [&](const Edge& e) { return (e.from == from) && (e.to == to); }), edges.end());

        return false;
    }

    bool remove_edge(const Edge& e) {
        if (!has_edge(e)) return false;
        auto& edges = _edges.at(e.from);

        edges.erase(std::remove_if(edges.begin(), edges.end(), [e](const Edge& edge)
            { return (e.from == edge.from) && (e.to == edge.to) && (e.distance == edge.distance); }), edges.end());

        return true;
    }

    bool has_edge(const Vertex& from, const Vertex& to) const {
        for (const auto& edges : _edges) {
            for (const auto& edge : edges.second) {
                if (edge.from == from && edge.to == to) {
                    return true;
                }
            }
        }
        return false;
    }

    bool has_edge(const Edge& e) const {
        auto& edges = _edges.at(e.from);
        for (const auto& edge : edges)
            if (edge.to == e.to && abs(edge.distance - e.distance) < EPSILON)
                return true;
        return false;
    }

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex) {
        if (!has_vertex(vertex))
            throw std::invalid_argument("vertex is not found");
        return _edges[vertex];
    }

    size_t order() const {
        return _vertices.size();
    }

    size_t degree(const Vertex& v) const {
        size_t count = 0;
        for (const auto& edges : _edges) {
            for (const auto& edge : edges.second) {
                if (edge.from == v || edge.to == v) {
                    count++;
                }
            }
        }
        return count;
    } //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& start, const Vertex& end) const {
        if (!has_vertex(start) || !has_vertex(end)) throw std::invalid_argument("error in shortest_path");

        std::unordered_map<Vertex, Distance> distance;
        std::unordered_map<Vertex, Vertex> predecessors;

        for (const Vertex& vertex : _vertices) {
            distance[vertex] = INFINITY;
        }
        distance[start] = 0;

        for (size_t i = 0; i < _vertices.size(); ++i) {
            for (const auto& [from, edges] : _edges) {
                for (const auto& edge : edges) {
                    if (distance[from] + edge.distance < distance[edge.to]) {
                        distance[edge.to] = distance[from] + edge.distance;
                        predecessors[edge.to] = edge.from;
                    }
                }
            }
        }
        for (const auto& [from, edges] : _edges) {
            for (const auto& edge : edges) {
                if (distance[from] + edge.distance < distance[edge.to])
                    throw std::runtime_error("Negative cycle detected");
            }
        }
        std::vector<Edge> result;
        Vertex current = end;
        while (current != start) {
            auto it = std::find_if(_edges.at(predecessors[current]).begin(), _edges.at(predecessors[current]).end(), [&](const Edge& e) { return e.to == current; });
            result.push_back(*it);
            current = predecessors[current];
        }
        std::reverse(result.begin(), result.end());

        return result;
    }



    //void print() const {
    //    for (auto& v : _vertices) {
    //        std::cout << v << " : ";
    //        for (auto& e : _edges.at(v)) {
    //            std::cout << "(" << e.to << ", " << e.distance << "),  ";
    //        }
    //        std::cout << std::endl;
    //    }
    //}

  

    void print_edges() const {
        std::cout << "Edges: " << std::endl;
        for (const Vertex& vertex : _vertices) {
            for (const Edge& edge : _edges.at(vertex)) {
                std::cout << edge.from << " -> " << edge.to << "(" << edge.distance << ")" << std::endl;
            }
        }
    }

    //обход
    void walk(const Vertex& start_vertex, std::function<void(const Vertex&)> action) const {
        if (!has_vertex(start_vertex))
            throw std::invalid_argument("start_vertex not found");

        std::vector<Vertex> visited;
        std::vector<size_t> dist(_vertices.size(), false);
        std::stack<Vertex> stack;

        dist[start_vertex] = true;
        stack.push(start_vertex);
        action(start_vertex);
        visited.push_back(start_vertex);

        while (!stack.empty()) {
            Vertex current = stack.top();
            stack.pop();

            for (const auto& edge : _edges.at(current)) {
                size_t index = std::find(_vertices.begin(), _vertices.end(), edge.to) - _vertices.begin();
                if (std::find(visited.begin(), visited.end(), edge.to) == visited.end()) {
                    stack.push(edge.to);
                    visited.push_back(edge.to);
                    dist[index] = dist[std::find(_vertices.begin(), _vertices.end(), current) - _vertices.begin()] + 1;
                    action(edge.to);
                }
            }
        }
    }
};


#endif