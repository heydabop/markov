#include<boost/algorithm/string/classification.hpp>
#include<boost/algorithm/string/split.hpp>

#include<iostream>
//#include<string>
#include<vector>

using namespace std;

int main(){
  string input;
  getline(cin, input);
  vector<string> strs;
  boost::split(strs, input, boost::is_any_of(" "));

  for(auto s : strs){
    cout << s << endl;
  }

  return 0;
}
