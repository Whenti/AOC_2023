#include "read.hpp"
#include "utils.hpp"
using namespace std;

typedef array<int, 2> pos;
typedef array<int, 2> dir;
const dir UP = {-1, 0}, RIGHT = {0, 1}, DOWN = {1, 0}, LEFT = {0, -1};

void visit(vector<string> const &m, pos position, dir direction, map<pos, set<dir>>& mem) {
  position = {position[0] + direction[0], position[1] + direction[1]};
  bool visited = mem.contains(position) && mem[position].contains(direction);
  int px = position[0], py = position[1];
  if(visited || px < 0 || py < 0 || px >= m.size() || py >= m[0].size()) return;
  mem[position].insert(direction);
  if(m[px][py] == '|' && (direction == LEFT || direction == RIGHT)) {
    visit(m, position, UP, mem);
    visit(m, position, DOWN, mem);
  } else if(m[px][py] == '-' && (direction == UP || direction == DOWN)) {
    visit(m, position, RIGHT, mem);
    visit(m, position, LEFT, mem);
  } else if(m[px][py]=='/') visit(m, position, {-direction[1], -direction[0]}, mem);
  else if(m[px][py]=='\\') visit(m, position, {direction[1], direction[0]}, mem);
  else visit(m, position, direction, mem);
}

vector<pair<dir, pos>> directions_and_positions(int N) {
  vector<pair<dir, pos>> ret;
  for(int i(0); i<N; ++i) {
    ret.push_back(make_pair(DOWN, pos({-1, i})));
    ret.push_back(make_pair(UP, pos({N, i})));
    ret.push_back(make_pair(RIGHT, pos({i, -1})));
    ret.push_back(make_pair(LEFT, pos({i, N})));
  }
  return ret;
}

int main() {
  // part 1
  vector<string> m = read_all();
  map<pos, set<dir>> mem;
  visit(m, {0, -1}, {0, 1}, mem);
  cout << mem.size() << endl;

  // part 2
  size_t ans2 = 0;
  for(auto [direction, position]: directions_and_positions(m.size())) {
    mem.clear();
    visit(m, position, direction, mem);
    ans2 = max(ans2, mem.size());
  }
  cout << ans2 << endl;
}
