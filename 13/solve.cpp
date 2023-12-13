#include "read.hpp"
#include "utils.hpp"
using namespace std;

vector<string> transpose(vector<string> const& island) {
  vector<string> ret;
  for(int i: range(island[0].size())) {
    ret.push_back("");
    for(int j: range(island.size())) ret.back() += island[j][i];
  }
  return ret;
}

int dist(string const& s1, string const& s2) {
  return count_if(it(range(s1.size())), lambda(s1[x] != s2[x]));
}

int find_reflection(vector<string> const& island, bool smudge) {
  for(auto i: range(1, island.size())) {
    bool s = smudge;
    bool reflec = true;
    for(int j(1); i-j >= 0 && i+j-1 < island.size(); ++j) {
      if(island[i-j] != island[i+j-1]) {
        if(dist(island[i-j], island[i+j-1]) == 1 && s) s = false;
        else {
          reflec = false; 
          break;
        }
      }
    }
    if(reflec && !s) return i;
  }
  return 0;
}

int solve(vector<string> const& island, bool smudge) {
  int ret = 100 * find_reflection(island, smudge);
  return ret ? ret : find_reflection(transpose(island), smudge);
}

int main() {
  int ans1 = 0;
  int ans2 = 0;
  while(!cin.fail()) {
    vector<string> island = read_paragraph();
    ans1 += solve(island, false);
    ans2 += solve(island, true);
  }
  cout << ans1 << endl;
  cout << ans2 << endl;
}
