// AUTHOR: Quentin Lévêque
#ifndef UTILS_HPP
#define UTILS_HPP
#include <bits/stdc++.h>

// DEFINES
#define LAMBDA_2(x, a) [&] (auto x) -> auto {return a;}
#define LAMBDA_1(a) LAMBDA_2(x, a)
#define LAMBDA_3(x, y, a) [&] (auto x, auto y) -> auto {return a;}
#define RANGE_2(a, b) std::views::iota((long int)a, (long int)b)
#define RANGE_1(a) RANGE_2(0, a)
#define RANGE_3(a, b, c) RANGE_2(a,b)|views::filter(LAMBDA_1((x-a)%c==0))
#define GET_MACRO_3(_1, _2, _3, NAME, ...) NAME

#define ll long long
#define it(x) std::begin(x), std::end(x)
#define lambda(...) GET_MACRO_3(__VA_ARGS__, LAMBDA_3, LAMBDA_2, LAMBDA_1)(__VA_ARGS__)
#define range(...) GET_MACRO_3(__VA_ARGS__, RANGE_3, RANGE_2, RANGE_1)(__VA_ARGS__)

// MATH
ll gcd(ll const &a, ll const &b) { return (b == 0) ? a : gcd(b, a % b); }

ll lcm(ll const &a, ll const &b) { return (a * b) / gcd(a, b); }

// COLLECTIONS
template <typename T, typename H> int index(T begin, T end, H const &x) {
  auto itr = std::find(begin, end, x);
  if (itr != end)
    return std::distance(begin, itr);
  return -1;
}

template <typename T, typename F> void sort(T begin, T end, F const &f) {
  std::sort(begin, end, [&f](auto a, auto b) -> bool { return f(a) < f(b); });
}

// STRINGS
std::vector<std::string> split(std::string const &str, char const &c) {
  std::istringstream iss(str);
  std::string el;
  std::vector<std::string> ret(0);
  while (std::getline(iss, el, c))
    ret.push_back(el);
  return ret;
}

std::string join(std::vector<std::string> const &str, std::string const &c) {
  std::ostringstream oss;
  for (const auto &x : str) {
    if (&x != &str[0])
      oss << c;
    oss << x;
  }
  return oss.str();
}

template <typename T> std::string padded(T const &x, char c, size_t n) {
  std::ostringstream oss;
  oss << std::setw(n) << std::setfill(c) << x;
  return oss.str();
}

std::string replaced(std::string s, std::string from, std::string to) {
  for (char const &c : from) {
    size_t p;
    while ((p = s.find(c)) != std::string::npos)
      s.replace(p, 1, to);
  }
  return s;
}

// ENUMERATE: c++23, not yet implemented by clang++... :(
template <typename T, typename TIter = decltype(std::begin(std::declval<T>())),
          typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerate(T &&it) {
  struct iterator {
    size_t i; TIter j;
    bool operator!=(const iterator &o) const { return j != o.j; }
    void operator++() { ++i; ++j; }
    auto operator*() const { return std::tie(i, *j); }
  };
  struct iterable_wrapper {
    T it;
    auto begin() { return iterator{0, std::begin(it)}; }
    auto end() { return iterator{0, std::end(it)}; }
  };
  return iterable_wrapper{std::forward<T>(it)};
}

#endif // UTILS_H
