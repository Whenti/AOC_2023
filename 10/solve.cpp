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
const v2int UP = make_pair(-1, 0), DOWN = -UP, LEFT = make_pair(0, -1), RIGHT = -LEFT;
const array<v2int, 4> DIRECTIONS = {UP, RIGHT, DOWN, LEFT};

const map<char, pair<v2int, v2int>> MAP = {
  make_pair('|', make_pair(UP, DOWN)),
  make_pair('-', make_pair(LEFT, RIGHT)),
  make_pair('L', make_pair(UP, RIGHT)),
  make_pair('J', make_pair(UP, LEFT)),
  make_pair('7', make_pair(LEFT, DOWN)),
  make_pair('F', make_pair(DOWN, RIGHT))
};

bool is_out(vector<string> const& maze, v2int pos){
  const auto [x, y] = pos;
  return x<0 or y<0 or x>=maze.size() or y>=maze[x].size();
}

int main() {
  vector<string> maze = readall();
  v2int pos = make_pair(-1, -1);
  for (size_t x(0); pos.second == -1; ++x) pos = make_pair(x, index(it(maze[x]), 'S'));

  map<v2int,set<v2int>> route;

  v2int dir;
  for(auto d: DIRECTIONS) {
    v2int new_pos = pos + d;
    if (is_out(maze, new_pos)) continue;
    char c = maze[new_pos.first][new_pos.second];
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

  // part 1
  cout << route.size()/2 << endl;

  // part 2
  vector<vector<bool>> look_right(maze.size(), vector<bool>(maze[0].size(), false));
  vector<vector<bool>> look_left=look_right;

  vector<int> dir_to_look_at = {1, -1};
  for(auto [pos, directions]: route) {
    for (auto dir: directions) {
      for (auto it = dir_to_look_at.begin(); it != dir_to_look_at.end();) {
        auto& look_at = *it == 1 ? look_right : look_left;
        v2int d = DIRECTIONS[(index(it(DIRECTIONS), dir) + *it)%4];
        v2int explore = pos + d;
        while(!is_out(maze, explore) and !route.contains(explore)) {
          look_at[explore.first][explore.second] = true;
          explore = explore+d;
        }
        if(is_out(maze, explore)) it = dir_to_look_at.erase(it);
        else ++it;
      }
    }
  }
  auto& inner = (index(it(dir_to_look_at), 1) != -1) ? look_right : look_left;
  cout << accumulate(it(inner), 0, lambda(x, y, x += std::count(it(y), true))) << endl;

  return 0;
}
