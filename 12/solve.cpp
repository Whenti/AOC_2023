#include "read.hpp"
#include "utils.hpp"
using namespace std;

typedef tuple<int, int, int> config;

ll solve(string const &s, vector<int> const &nums, map<config, ll> &m, config t) {
  if (m.contains(t))
    return m[t];
  auto [count, i, idx] = t;

  if(i == s.size())
    return (idx == nums.size() && count == 0) ? 1 : 0;

  if (s[i] == '#' && ++count > nums[idx]) return 0;
  else if (s[i] == '.' && count) {
    if (nums[idx++] != count) return 0;
    count = 0;
  }
  else if (s[i] == '?') {
    string s1 = s, s2 = s;
    s1[i] = '.';
    s2[i] = '#';
    return solve(s1, nums, m, t) + solve(s2, nums, m, t);
  }
  t = make_tuple(count, ++i, idx);
  return m[t] = solve(s, nums, m, t);
}

int main() {
  ll ans1 = 0, ans2 = 0;
  map<config, ll> m;

  while(true) {
    string s = read();
    auto nums = read<vector<int>>(replaced(read(), ",", " "));
    if(cin.fail()) break;

    // part1
    m.clear();
    ans1+=solve(s + ".", nums, m, make_tuple(0,0,0));

    // part2
    string multi_s = join(vector<string>(5, s), "?");
    vector<int> multi_numbers(0);
    for(auto i: range(5)) multi_numbers.insert(multi_numbers.end(), it(nums));
    m.clear();
    ans2 += solve(multi_s + ".", multi_numbers, m, make_tuple(0,0,0));
  }

  cout << ans1 << endl;
  cout << ans2 << endl;
}
