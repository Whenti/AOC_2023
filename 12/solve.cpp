#include "read.hpp"
#include "utils.hpp"
using namespace std;

typedef tuple<int, int, int> config;

ll solve(
    string const& s,
    vector<int> const& numbers,
    map<config, ll> & m,
    config t = make_tuple(0,0,0))
{
  if(m.contains(t)) return m[t];

  auto [count, i, idx] = t;
  if(i == s.size()) {
    if (idx == numbers.size() && count == 0) return 1;
    if (idx == numbers.size() - 1 && count == numbers.back()) return 1;
    return 0;
  }

  switch (s[i]) {
    case '#':
      if (++count > numbers[idx]) return 0;
      t = make_tuple(count, ++i, idx);
      return m[t] = solve(s, numbers, m, t);
    case '.':
      if(count) {
        if (numbers[idx] != count) return 0;
        t = make_tuple(0, ++i, ++idx);
        return m[t] = solve(s, numbers, m, t);
      }
      t = make_tuple(count, ++i, idx);
      return m[t] = solve(s, numbers, m, t);
    case '?':
      string s1 = s, s2 = s;
      s1[i] = '.';
      s2[i] = '#';
      return solve(s1, numbers, m, t) + solve(s2, numbers, m, t);
  }
}

int main() {
  ll ans1 = 0, ans2 = 0;
  map<config, ll> m;

  while(true) {
    string s = read();
    if(cin.fail()) break;
    auto numbers = read<vector<int>>(replaced(read(), ",", " "));

    // part1
    m.clear();
    ans1+=solve(s, numbers, m);

    // part2
    string multi_s = join(vector<string>(5, s), "?");
    vector<int> multi_numbers(0);
    for(auto i: range(5)) multi_numbers.insert(multi_numbers.end(), it(numbers));
    m.clear();
    ans2 += solve(multi_s, multi_numbers, m);
  }

  cout << ans1 << endl;
  cout << ans2 << endl;
}
