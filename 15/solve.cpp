#include "read.hpp"
#include "utils.hpp"
using namespace std;

int HASH(string const& s) {
  int current = 0;
  for(char c: s) current = ((current + c) * 17) % 256;
  return current;
}

int main() {
  vector<string> sequences = split(join(read_all()), ',');

  // part 1
  int ans1 = accumulate(it(sequences), 0, lambda(x, y, x += HASH(y)));
  cout << ans1 << endl;

  // part 2
  array<map<string, array<int, 2>>, 256> boxes;
  for(auto [i, seq]: enumerate(sequences)) {
    if(seq.back() == '-') {
      seq.pop_back();
      boxes[HASH(seq)].erase(seq);
    } else {
      int num = seq.back() - '0';
      seq.pop_back();
      seq.pop_back();
      auto& box = boxes[HASH(seq)];
      if(box.contains(seq)) box[seq] = {num, box[seq][1]};
      else box[seq] = {num, int(i)};
    }
  }

  int ans2 = 0;
  for(auto [i, box]: enumerate(boxes)) {
    vector<array<int, 2>> v;
    for(auto const& p: box) v.push_back(p.second);
    order(it(v), lambda(x[1]));
    for(auto [j, p]: enumerate(v)) ans2 += (i + 1) * (j + 1) * p[0];
  }
  cout << ans2 << endl;
}
