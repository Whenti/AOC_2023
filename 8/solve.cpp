#include "utils.h"
using namespace std;

int main() {
  string path, from, to;
  read(path);
  readline();
  map<string, pair<string, string>> m;
  vector<string> start_nodes;
  while(read(from)) {
    if(from[from.size() - 1] == 'A') start_nodes.push_back(from);
    readline(to);
    replace(to, " =()", "");
    replace(to, ",", " ");
    vector<string> temp = split(to, ' ');
    m[from] = make_pair(temp[0], temp[1]);
  }
  // part 1
  string current = "AAA";
  size_t cursor = 0, idx = 0;
  while (current != "ZZZ") {
    current = path[cursor] == 'L' ? m[current].first : m[current].second;
    if(++cursor >= path.size()) cursor = 0;
    idx++;
  }
  print("part 1:", idx);

  //part 2
  vector<string> currents;
  for(string const& start_node: start_nodes) currents.push_back(start_node);
  vector<int> steps;
  for(string const& start_node: start_nodes) {
    string current = start_node;
    size_t cursor = 0, idx = 0;
    while(current[current.size() -1 ] != 'Z') {
      current = path[cursor] == 'L' ? m[current].first : m[current].second;
      if(++cursor >= path.size()) cursor = 0;
      idx++;
    }
    steps.push_back(idx);
  }
  print("part 2:", lcm(steps));
  return 0;
}
