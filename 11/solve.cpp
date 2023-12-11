#include "utils.hpp"
#include "read.hpp"
using namespace std;

int main() {
  auto map = readall();

  vector<int> v_sums(0);
  vector<int> h_sums(0);
  vector<pair<int, int>> positions(0);

  int sum = 0;
  vector<bool> cols(map[0].size(), true);
  for(auto i: range(map.size())) {
    bool line = true;
    for(auto j: range(map[0].size())) {
      if (map[i][j] == '#') {
        cols[j] = false;
        line = false;
        positions.push_back(make_pair(i,j));
      }
    }
    if(line) sum += 1;
    v_sums.push_back(sum);
  }
  sum = 0;
  for(auto col: cols) {
    if(col) sum += 1;
    h_sums.push_back(sum);
  }

  ll ans1 = 0, ans2 = 0, manhattan, exp;

  for(auto i: range(positions.size())) {
    for(auto j: range(i + 1, positions.size())) {
        int x1=positions[i].first, y1=positions[i].second, x2=positions[j].first, y2=positions[j].second;
        manhattan = abs(x1 - x2) + abs(y1 - y2);
        exp = abs(v_sums[x1] - v_sums[x2]) + abs(h_sums[y1] - h_sums[y2]);
        ans1 +=  manhattan + exp;
        ans2 += manhattan + (1000000 - 1) * exp;
    }
  }

  cout << ans1 << endl;
  cout << ans2 << endl;

  return 0;
}
