/*
Using Boost graph: sudo apt install libboost-all-dev
g++ boost_graph.cc && ./a.out && cat graph.dot
*/
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/range/counting_range.hpp>
#include <iostream>
#include <utility>
#include <vector>

struct VertexProperties {
    static long g_id;
    long id{++g_id};
    std::string label{'?'};
};

long VertexProperties::g_id = -1;

struct EdgeProperties {
    double weight{0.};
};

template <typename Vp, typename Ep>
using CompelxGraph = boost::adjacency_list<boost::vecS, boost::vecS,
                                           boost::bidirectionalS, Vp, Ep>;

using vertexIt = boost::graph_traits<
    CompelxGraph<VertexProperties, EdgeProperties>>::vertex_iterator;
using IndexMap =
    boost::property_map<CompelxGraph<VertexProperties, EdgeProperties>,
                        boost::vertex_index_t>::type;

template <typename G> void save_dot_file(std::string const &fname, G &graph) {
    std::ofstream ofs(fname);
    if (!ofs.is_open()) {
        std::cerr << __func__ << "Cannot open " << fname << '\n';
    }
    boost::dynamic_properties dp;
    dp.property("node_id", boost::get(&G::vertex_property_type::id, graph));
    dp.property("label", boost::get(&G::vertex_property_type::label, graph));
    dp.property("weight", boost::get(&G::edge_property_type::weight, graph));

    write_graphviz_dp(ofs, graph, dp);
}

int main() {

    CompelxGraph<VertexProperties, EdgeProperties> g{};
    for (auto &&i : boost::counting_range(1, 10)) {
        boost::add_vertex(g);
    }

    boost::add_edge(0, 1, g);
    boost::add_edge(0, 2, g);
    boost::add_edge(0, 3, g);
    boost::add_edge(0, 4, g);
    boost::add_edge(0, 5, g);
    boost::add_edge(0, 6, g);
    boost::add_edge(0, 7, g);
    boost::add_edge(0, 8, g);

#if 0
    vertexIt vit, vend;
    IndexMap map{get(boost::vertex_index, g)};
    for (boost::tie(vit, vend) = boost::vertices(g); vit != vend; ++vit) {
        const auto &v = map[*vit];
        std::cout << v << std::endl;
    }
#endif

    save_dot_file("graph.dot", g);
}
