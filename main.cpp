#include<iostream>
#include<boost/graph/adjacency_list.hpp>

using namespace std;

int main(){
  typedef boost::adjacency_list<boost::vecS,
                                boost::setS,
                                boost::directedS>  Graph;

  Graph g();

  return 0;
}
