#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>
#include <fstream>

using index_t = std::uint64_t;
using var_t = std::uint64_t;
using op_t = std::uint64_t;

template <typename G> boost::dynamic_properties get_dot_dp(G &graph) {
    boost::dynamic_properties dp;
    dp.property("node_id", boost::get(&G::vertex_property_type::id, graph));
    dp.property("label", boost::get(&G::vertex_property_type::label, graph));
    dp.property("weight", boost::get(&G::edge_property_type::weight, graph));
    return dp;
}

struct VertexProperties {
    VertexProperties() = default;
    VertexProperties(var_t nameArg, op_t typeArg)
        : name(nameArg), type(typeArg) {}
    VertexProperties(var_t nameArg, op_t typeArg, const std::string labelArg)
        : name(nameArg), type(typeArg), label(labelArg) {}
    var_t name{};
    op_t type{};
    std::string label{'?'};
    long id{++g_id};
    static long g_id;
};
long VertexProperties::g_id = -1;

struct EdgeProperties {
    EdgeProperties(op_t typeArg) : type(typeArg) {}
    enum Ops {
        DEFAULT,
    };
    double weight{0.};
    op_t type{};
    std::string label{'?'};
};

template <typename Vp = VertexProperties, typename Ep = EdgeProperties>
using Graph = boost::adjacency_list<boost::vecS, boost::vecS,
                                    boost::bidirectionalS, Vp, Ep>;

template <> boost::dynamic_properties get_dot_dp<Graph<>>(Graph<> &graph) {
    boost::dynamic_properties dp;
    dp.property("node_id",
                boost::get(&Graph<>::vertex_property_type::id, graph));
    dp.property("label",
                boost::get(&Graph<>::vertex_property_type::label, graph));
    dp.property("dependency",
                boost::get(&Graph<>::edge_property_type::type, graph));
    return dp;
}

template <typename G> void save_dot_file(std::string const &fname, G &graph) {
    std::ofstream ofs(fname);
    if (!ofs.is_open()) {
        std::cerr << __func__ << "Cannot open " << fname << '\n';
    }
    write_graphviz_dp(ofs, graph, get_dot_dp<G>(graph));
    ofs.close();
}

struct Node {
    enum Ops {
        INIT,
    };
    var_t dst{};
    op_t operation{};
    std::vector<var_t> srcs{};
};

class DFG {
  public:
    // void addProducer(const var_t&, index_t);
    // void addConsumer(const var_t&, index_t);
    void addNode(const Node &);
    Graph<> &graph() { return m_g; };
    // void clear();

  private:
    Graph<> m_g{};
    std::map<var_t, index_t> m_lastVarNodes{};
};

void DFG::addNode(const Node &nd) {
    VertexProperties v(nd.dst, nd.operation);
    auto cur = boost::add_vertex(v, m_g);
    for (auto &&src : nd.srcs) {
        Graph<>::vertex_descriptor input{};
        if (m_lastVarNodes.find(src) == m_lastVarNodes.cend()) {
            input = boost::add_vertex(VertexProperties{src, Node::INIT}, m_g);
        } else {
            input = m_lastVarNodes[src];
        }
        m_lastVarNodes[src] = input;
        boost::add_edge(input, cur, EdgeProperties{EdgeProperties::DEFAULT},
                        m_g);
    }
}
