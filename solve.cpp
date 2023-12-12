#include "utils/print.hpp"
#include "utils/read.hpp"
#include "utils/utils.hpp"

using namespace std;

int main() {
  const int n = 3, m=n*3;
  // int a[n][m];
  array<array<int, m>, n> a;
  for(auto i: range(3)) {
    for(auto j: range(3)) {
      a[i][j] = i +j;
      cout << a[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}
