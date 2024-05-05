#ifndef GRAPH_INCLUDE_GRAPH_H
#define GRAPH_INCLUDE_GRAPH_H

#include <algorithm>
#include <functional>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>

template<typename Vertex, typename Distance = double>
class Graph {
private:
    std::vector<Vertex> _vertices;
    std::unordered_map<Vertex, std::vector<Edge>> _edges;
public:
    struct Edge {
        Vertex to;
        Vertex from;
        Distance distance;
    }


    //проверка-добавление-удаление вершин
    bool has_vertex(const Vertex& v) const {
        return std::find(_vertices.begin(), _vertices.end(), v) != _vertices.end();
    }

    void add_vertex(const Vertex& v) {
        auto it = std::find(_vertices.begin(), _vertices.end(), v);
        if (it != _vertices.end())
            return false;
        _vertices.push_back(v);
        _edges[v] = {};
        return true;
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
        if (!has_vertex(from))
            add_vertex(from);
        if (!has_vertex(to))
            add_vertex(to);
        if (!has_edge(from, to)) 
            _edges[from].push_back(Edge{ from, to, d });
    }

    bool remove_edge(const Vertex& from, const Vertex& to);
    bool remove_edge(const Edge& e)//c учетом расстояния

    bool has_edge(const Vertex& from, const Vertex& to) const {
        if (std::find(_vertices.begin(), _vertices.end(), from) == _vertices.end())
            return false;
        if (std::find(_vertices.begin(), _vertices.end(), to) == _vertices.end())
            return false;
        for (const Edge& edge : _edges.at(from))
            if (edge.to == to)
                return true;
        return false;
    }

    bool has_edge(const Edge& e) const {
        if (std::find(_vertices.begin(), _vertices.end(), e.from) == _vertices.end())
            return false;
        if (std::find(_vertices.begin(), _vertices.end(), e.to) == _vertices.end())
            return false;
        for (const Edge& edge : _edges.at(e.from))
            if (edge.to == e.to && abs(edge.distance - e.distance) < EPSILON)
                return true;
        return false;
    } //c учетом расстояния в Edge

    //получение всех ребер, выходящих из вершины
    std::vector<Edge> edges(const Vertex& vertex);

    size_t order() const; //порядок 
    size_t degree(const Vertex& v) const; //степень вершины


    //поиск кратчайшего пути
    std::vector<Edge> shortest_path(const Vertex& from,
        const Vertex& to) const;
    //обход
    std::vector<Vertex>  walk(const Vertex& start_vertex)const;
};


#endif