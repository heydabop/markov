#include<iostream>
#include<utility>
#include<vector>
#include<random>

#include<boost/graph/adjacency_list.hpp>

#include<boost/algorithm/string/classification.hpp>
#include<boost/algorithm/string/split.hpp>
#include<boost/algorithm/string/trim.hpp>

using namespace boost;

int main(int argc, char** argv){
  typedef adjacency_list<vecS,
                         vecS,
                         directedS,
                         property<vertex_name_t, std::string> >  Graph;
  typedef graph_traits<Graph>::vertex_descriptor                 Vertex;
  typedef std::pair<graph_traits<Graph>::edge_descriptor, bool>  Edge;

  long sentences = 1;
  if(argc == 2){
    sentences = strtol(argv[1], NULL, 10);
    if(sentences < 1){
      std::cerr << "The number of sentences to be generated must be positive.\n";
    }
  }

  Graph g(0);

  property_map<Graph, vertex_name_t>::type vertex_words = get(vertex_name, g);
  std::map<std::string, Vertex> word_map; //use to quickly find vertices

  //make starting vertex
  Vertex v_start = add_vertex(g);
  vertex_words[v_start] = "_";
  word_map.emplace("_", v_start);

  //make vertices for periods and exclamation marks
  Vertex v_period = add_vertex(g);
  vertex_words[v_period] = ".";
  word_map.emplace(".", v_period);
  Vertex v_excl = add_vertex(g);
  vertex_words[v_excl] = "!";
  word_map.emplace("!", v_excl);
  Vertex v_ques = add_vertex(g);
  vertex_words[v_ques] = "?";
  word_map.emplace("?", v_ques);

  //get input and split on space
  std::string input;
  while(std::getline(std::cin, input)){
    std::vector<std::string> words;
    split(words, input, is_space());

    /*for(auto s : words){
      std::cout << s << " ";
    }
    std::cout << std::endl;*/

    bool first = true; //true if s is first word in line
    Vertex prev = graph_traits<Graph>::null_vertex(); //previous Vertex added to graph
    for(auto s : words){

      char c = 0;
      //remember if word is end of sentence
      if(s.back() == '.'){
        c = '.';
      } else if (s.back() == '!'){
        c = '!';
      } else if (s.back() == '?'){
        c = '?';
      }

      trim_if(s, is_punct()); //remove grammatical marks
      if(!s.empty()){ //do nothing if s is empty
        //std::cout << s << " ";
        if(word_map.find(s) == word_map.end()) { //currenty no vertex for word s
          //add vertex to graph, add string property, add string=>vertex to word_map
          Vertex v = add_vertex(g);
          vertex_words[v] = s;
          word_map.emplace(s, v);
        }
        //std::cout << "\"" << s << "\"" << std::endl;
        Vertex v = word_map.find(s)->second;

        //add edge for previous word to s
        if(first){
          add_edge(v_start, v, g);
        } else {
          add_edge(prev, v, g);
        }
        first = false;
        prev = v;

        if(c == '.'){
          add_edge(v, v_period, g); //edge from word to period
          //std::cout << ". ";
          first = true; //next word is the first in a sentence
        } else if (c == '!'){
          add_edge(v, v_excl, g); //edge from word to exclamation mark
          //std::cout << "! ";
          first = true;
        } else if (c == '?'){
          add_edge(v, v_ques, g);
          //std::cout << "? ";
          first = true;
        }
      }
    }
    //std::cout << "done" << std::endl << std::endl;
  }
  //std::cout << std::endl;

#ifdef GRAPHVIZ
  //output all edges
  Vertex v = graph_traits<Graph>::null_vertex();
  Vertex u = graph_traits<Graph>::null_vertex();
  typedef graph_traits<Graph>::edge_iterator  edge_iter;
  std::pair<edge_iter, edge_iter> ep;
  edge_iter ei, ei_end;
  for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei){
    std::cout << "\"" << vertex_words[source(*ei, g)] << "\" -> \"" << vertex_words[target(*ei, g)] << "\";" << std::endl;
  }
#endif

  std::cout << num_vertices(g) << " " << num_edges(g) << std::endl << std::endl;

  for(long i = 0; i < sentences; ++i){
    Vertex current = v_start;
    boost::graph_traits<Graph>::degree_size_type d = 0;
    while((d = out_degree(current, g)) != 0){
      //this is probably really slow
      std::random_device rand;
      std::mt19937 gen(rand());
      std::uniform_int_distribution<> dis(0, d-1);

      int i = dis(gen);

      //std::cout << d << " " << i << std::endl;

      graph_traits<Graph>::out_edge_iterator oet = out_edges(current, g).first;
      current = target(*(oet + i), g);
      std::cout << vertex_words[current] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
