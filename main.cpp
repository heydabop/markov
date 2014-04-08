#include<iostream>
#include<boost/graph/adjacency_list.hpp>

using namespace boost;

int main(){
  typedef adjacency_list<vecS,
                         setS, //lots of searching for vertices, this may help?
                         directedS,
                         property<vertex_name_t, std::string> >  Graph;

  Graph g(0);
  add_vertex(g);
  std::cout << num_vertices(g) << std::endl;

  return 0;
}
