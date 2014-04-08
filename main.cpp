#include<iostream>
#include<utility>
#include<boost/graph/adjacency_list.hpp>

using namespace boost;

int main(){
  typedef adjacency_list<vecS,
                         setS, //lots of searching for vertices, this may help?
                         directedS,
                         property<vertex_name_t, std::string> >  Graph;
  typedef graph_traits<Graph>::vertex_descriptor                 Vertex;
  typedef std::pair<graph_traits<Graph>::edge_descriptor, bool>  Edge;

  Graph g(0);
  Vertex u = add_vertex(g);
  Vertex v = add_vertex(g);
  Edge e = add_edge(u, v, g);
  std::cout << num_vertices(g) << " " << num_edges(g) << std::endl;

  return 0;
}
