#include "utils.hpp"
#include "read.hpp"
using namespace std;

typedef pair<int, int> v2int;

v2int operator+(v2int const& d1, v2int const& d2) {
  return make_pair(d1.first + d2.first, d1.second + d2.second);
}
v2int operator-(v2int const& d) {
  return make_pair(- d.first, - d.second);
}
const v2int NONE=make_pair(0, 0), UP = make_pair(-1, 0), DOWN = -UP, LEFT = make_pair(0, -1), RIGHT = -LEFT;
const array<v2int, 4> DIRECTIONS = {UP, RIGHT, DOWN, LEFT};

const map<char, pair<v2int, v2int>> MAP = {
  make_pair('|', make_pair(UP, DOWN)),
  make_pair('-', make_pair(LEFT, RIGHT)),
  make_pair('L', make_pair(UP, RIGHT)),
  make_pair('J', make_pair(UP, LEFT)),
  make_pair('7', make_pair(LEFT, DOWN)),
  make_pair('F', make_pair(DOWN, RIGHT))
};

int main() {
  vector<string> maze = readall();
  v2int pos = make_pair(-1, -1);
  for (size_t x(0); pos.second == -1; ++x) pos = make_pair(x, index(it(maze[x]), 'S'));

  // part 1
  map<v2int,set<v2int>> route;
  v2int dir = NONE;
  for(auto d: DIRECTIONS) {
    v2int npos = pos + d;
    if (npos.first<0 or npos.second<0 or npos.first>=maze.size() or npos.second>=maze[0].size())
      continue;
    char c = maze[npos.first][npos.second];
    if ( c != '.' && (MAP.at(c).first == -d || MAP.at(c).second == -d)) {
      dir = d;
      break;
    }
  }
  route[pos].insert(dir);
  pos = pos+dir;
  route[pos].insert(dir);

  char c = maze[pos.first][pos.second];
  while (c != 'S') {
    pair<v2int, v2int> p = MAP.at(c);
    dir = p.first == -dir ? p.second : p.first;
    route[pos].insert(dir);
    pos = pos + dir;
    route[pos].insert(dir);
    c = maze[pos.first][pos.second];
  }
  cout << route.size()/2 << endl;

  // part 2
  // initially solved with a bruteforce method but this is much more elegant
  // https://www.reddit.com/r/adventofcode/comments/18eza5g/2023_day_10_animated_visualization/
  int count = 0;
  dir = NONE;
  for(auto i: range(maze.size())) {
    bool inside = false;
    for(auto j: range(maze[i].size())) {
      v2int pos = make_pair(i, j);
      if(route.contains(pos)){
        if (dir == NONE) dir = route[pos].contains(DOWN) ? DOWN : UP;
        if (route[pos].contains(dir)) inside = true;
        else if (route[pos].contains(-dir)) inside = false;
      }
      else if (inside) ++count;
    }
  }
  cout << count << endl;

  return 0;
}
