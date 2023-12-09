#include <bits/stdc++.h>
#define ll long long

using namespace std;

ll gcd(ll const& a, ll const& b) { if (b == 0) return a; return gcd(b, a % b); }
ll lcm(ll const& a, ll const& b) { return (a * b) / gcd(a, b); }
ll lcm(vector<int> const& v) {
  ll a = v[0];
  for (auto const& x : v) a = lcm(a, x);
  return a;
}
template<typename T> bool readline(T& x) { return bool(getline(cin, x)); }
bool readline() { std::string x; return readline(x); }

template<typename T> bool read(T& x) { return bool(cin >> x); }

vector<string> split(string const& str, char const& c) {
  istringstream iss(str);
  string el;
  vector<string> ret(0);
  while (getline(iss, el, c)) ret.push_back(el);
  return ret;
}

void replace(string& s, string from, string to){
  for(char const& c: from) {
    size_t p;
    while ((p = s.find(c)) != string::npos) s.replace(p, 1, to);
  }
}

int main() {
  string path, from, to;
  read(path);
  readline();
  map<string, pair<string, string>> m;
  vector<string> start_nodes;
  while (read(from)) {
    if (from.back() == 'A') start_nodes.push_back(from);
    readline(to);
    replace(to, " =()", "");
    vector<string> temp = split(to, ',');
    m[from] = make_pair(temp[0], temp[1]);
  }
  // part 1
  string current = "AAA";
  size_t cursor = 0, idx = 0;
  while (current != "ZZZ") {
    current = path[cursor] == 'L' ? m[current].first : m[current].second;
    if (++cursor >= path.size()) cursor = 0;
    idx++;
  }
  cout << "part 1: " << idx << endl;

  // part 2
  vector<int> steps;
  for (string const &start_node : start_nodes) {
    string current = start_node;
    size_t cursor = 0, idx = 0;
    while (current.back() != 'Z') {
      current = path[cursor] == 'L' ? m[current].first : m[current].second;
      if (++cursor >= path.size()) cursor = 0;
      idx++;
    }
    steps.push_back(idx);
  }
  cout << "part 2: " << lcm(steps) << endl;
  return 0;
}
