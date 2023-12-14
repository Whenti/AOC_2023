#include "read.hpp"
#include "utils.hpp"
using namespace std;

vector<string>& T(vector<string>& m) {
  for(int i: range(m.size()))
    for(int j: range(i + 1, m[0].size()))
      swap(m[i][j], m[j][i]);
  return m;
}

vector<string>& R(vector<string>& m) {
  for(int i: range(m.size())) reverse(it(m[i]));
  return m;
}

vector<string>& tilt_west(vector<string>& m) {
  for(string &row: m){
    int n = row.size(), count = 0, from = 0;
    for(int col: range(n + 1)) {
      if(col == n || row[col] == '#') {
        for(auto i: range(from, from + count)) row[i] = 'O';
        count = 0;
        from = col + 1;
      } else {
        if(row[col] == 'O') ++count;
        row[col] = '.';
      }
    }
  }
  return m;
}
vector<string>& tilt_north(vector<string>& m) { return T(tilt_west(T(m))); }
vector<string>& tilt_east(vector<string>& m) { return R(tilt_west(R(m))); }
vector<string>& tilt_south(vector<string>& m) { return T(tilt_east(T(m))); }

int points(vector<string> const& m) {
  int n = m.size(), ans = 0;
  for(auto i: range(n)) ans+=(n - i) * count_if(it(m[i]), lambda(x=='O'));
  return ans;
}

int main() {
  int ans1 = 0;
  int ans2 = 0;

  // part 1
  vector<string> m = read_all();
  ans1 = points(tilt_north(m));

  // part 2
  map<string, ll> states;
  auto cycle = {tilt_north, tilt_west, tilt_south, tilt_east};

  string hash = join(m, "");
  states[hash] = 0;
  ll idx = 0, N = 1000000000;
  while(idx++ < N) {
    for (auto const& f : cycle) f(m);
    hash = join(m, "");
    if(states.contains(hash)){
      int delta = idx - states[hash];
      while(idx + delta < N) idx += delta;
    }
    else states[hash] = idx;
  }
  ans2 = points(m);

  cout << ans1 << endl;
  cout << ans2 << endl;
}
