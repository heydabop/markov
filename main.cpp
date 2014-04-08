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

  //make vertex for period
  Vertex v_end = add_vertex(g);
  vertex_words[v_end] = ".";
  word_map.emplace(".", v_end);

  //get input and split on space
  std::string input;
  while(std::getline(std::cin, input)){
    std::vector<std::string> words;
    split(words, input, is_space());

    bool first = true; //true if s is first word in line
    Vertex prev; //previous Vertex added to graph
    for(auto s : words){

      bool end = false;
      if(s.back() == '.'){
        end = true;
      }

      trim_if(s, is_punct()); //remove grammatical marks
      Vertex v;
      if(word_map.find(s) == word_map.end() && !s.empty()) { //currenty no vertex for word s
        //add vertex to graph, add string property, add string=>vertex to word_map
        v = add_vertex(g);
        vertex_words[v] = s;
        word_map.emplace(s, v);
      }

      //add edge for previous word to s
      if(!first){
        add_edge(prev, v, g);
      }
      first = false;
      prev = v;

      if(end){
        add_edge(v, v_end, g);
      }
    }
  }

  std::cout << num_vertices(g) << " " << num_edges(g) << std::endl;

  

  return 0;
}
