#include<iostream>
#include<utility>
#include<vector>

#include<boost/graph/adjacency_list.hpp>

#include<boost/algorithm/string/classification.hpp>
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string/trim.hpp>

using namespace boost;

int main(){
  typedef adjacency_list<vecS,
                         vecS,
                         directedS,
                         property<vertex_name_t, std::string> >  Graph;
  typedef graph_traits<Graph>::vertex_descriptor                 Vertex;
  typedef std::pair<graph_traits<Graph>::edge_descriptor, bool>  Edge;

  Graph g(0);

  property_map<Graph, vertex_name_t>::type vertex_words = get(vertex_name, g);
  std::map<std::string, Vertex> word_map; //use to quickly find vertices

  //get input and split on space
  std::string input;
  std::getline(std::cin, input);
  std::vector<std::string> words;
  split(words, input, is_space());

  for(auto s : words){
    trim_if(s, is_punct()); //remove grammatical marks
    if(word_map.find(s) == word_map.end() && !s.empty()) { //currenty no vertex for word s
      //add vertex to graph, add string property, add string=>vertex to word_map
      Vertex v = add_vertex(g);
      vertex_words[v] = s;
      word_map.emplace(s, v);
    }
  }

  std::cout << num_vertices(g) << " " << num_edges(g) << std::endl;

  return 0;
}
