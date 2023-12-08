// AUTHOR: Quentin Lévêque
#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>

// MISC

// lambda
#define GET_MACRO(_1, _2, NAME, ...) NAME
#define lambda(...) GET_MACRO(__VA_ARGS__, lambda2, lambda1)(__VA_ARGS__)
#define lambda1(param) [&] (auto param) -> auto
#define lambda2(param, ret) [&] (auto param) -> auto {return ret;}

// enumerate
template <typename T,
          typename TIter = decltype(std::begin(std::declval<T>())),
          typename = decltype(std::end(std::declval<T>()))>
constexpr auto enumerate(T && iterable)
{
    struct iterator
    {
        size_t i;
        TIter iter;
        bool operator != (const iterator & other) const { return iter != other.iter; }
        void operator ++ () { ++i; ++iter; }
        auto operator * () const { return std::tie(i, *iter); }
    };
    struct iterable_wrapper
    {
        T iterable;
        auto begin() { return iterator{ 0, std::begin(iterable) }; }
        auto end() { return iterator{ 0, std::end(iterable) }; }
    };
    return iterable_wrapper{ std::forward<T>(iterable) };
}

// STRINGS

// split
std::vector<std::string> split(std::string const& str, char const& c) {
  std::istringstream iss(str);
  std::string el;
  std::vector<std::string> ret(0);
  while (std::getline(iss, el, c)) {
      ret.push_back(el);
  }
  return ret;
}

// join
std::string join(std::vector<std::string> const& v, char const& c) {
  std::ostringstream oss;
  for (const auto& x : v) {
      if (&x != &v[0]) oss << c;
      oss << x;
  }
  return oss.str();
}

// replace
void replace(std::string& s, std::string from, std::string to){
  for(char const& c: from) {
    size_t p;
    while ((p = s.find(c)) != std::string::npos) s.replace(p, 1, to);
  }
}

// padding
template <typename T> std::string padded(T const& x, char c, size_t n) {
  std::ostringstream oss;
  oss << std::setw(n) << std::setfill(c) << x;
  return oss.str();
}

// COLLECTIONS

// one
template <typename T, typename F> bool one(const T& v, F f) {
  for(auto& x: v) if(f(x)) return true;
  return false;
}

// all
template <typename T, typename F> bool all(const T& v, F f) {
  for(auto& x: v) if(!f(x)) return false;
  return true;
}

// max
template <typename T> typename T::value_type max(const T& v) {
  typename T::value_type max = v[0];
  for (const auto& x : v) max = std::max(max, x); return max;
}
template <typename T, size_t N> T max(const T (&v)[N]) {
  T max = v[0];
  for (const auto& x : v) max = std::max(max, x); return max;
}

// min
template <typename T> typename T::value_type min(const T& v) {
  typename T::value_type min = v[0];
  for (const auto& x : v) min = std::min(min, x); return min;
}
template <typename T, size_t N> T min(const T (&v)[N]) {
  T min = v[0];
  for (const auto& x : v) min = std::min(min, x); return min;
}

// sum
template <typename T> typename T::value_type sum(const T& v) {
  typename T::value_type s = 0;
  for(auto& x: v) s += x; return s;
}
template <typename T, size_t N> T sum(const T (&v)[N]) {
  T s = 0;
  for(auto& x: v) s += x; return s;
}

// product
template <typename T> typename T::value_type product(const T& v) {
  typename T::value_type s = 1;
  for(auto& x: v) s *= x; return s;
}
template <typename T, size_t N> T product(const T (&v)[N]) {
  T s = 1;
  for(auto& x: v) s *= x; return s;
}

// index
template <typename T, typename H> int index(const T& v, H const& x) {
  for(auto [i, el]: enumerate(v)) if(el == x) return i;
  return -1;
}

// count
template <typename T, typename H> size_t count(const T& v, H const& x) {
  size_t counter = 0;
  for(auto& el: v) if(el == x) ++counter;
  return counter;
}

// sort vector
template <typename T> void sort(std::vector<T> & v) { std::sort(v.begin(), v.end()); }
template <typename T, typename F> void sort(std::vector<T> & v, F const& f) {
  auto customF = [&f] (T a, T b) -> bool { return f(a) < f(b); };
  std::sort(v.begin(), v.end(), customF);
}

// sort c-style array
template <typename T, size_t N> void sort(T (&v)[N]) { std::sort(v, v+N); }
template <typename T, typename F, size_t N> void sort(T (&v)[N], F const& f) {
  auto customF = [&f] (T a, T b) -> bool { return f(a) < f(b); };
  std::sort(v, v+N, customF);
}

// READLINE

// generic line reader
template<typename T> bool readline(T& x) {
  return bool(std::getline(std::cin, x));
}

// empty line reader
bool readline() {
  std::string x;
  return readline(x);
}

// READ

// generic reader
template<typename T> bool read(T& x) {
  return bool(std::cin >> x);
}

// empty reader
bool read() {
  std::string x;
  return read(x);
}

// generic multi reader
template<typename H, typename... T> bool read(H& h, T&... t) {
  if (!read(h)) return false;
  return read(t...);
}

// vector reader
template<typename T> bool read(std::vector<T>& v) {
  if(v.size() == 0){
    std::string str;
    std::getline(std::cin, str);
    std::istringstream iss(str);
    T x;
    while (iss >> x) v.push_back(x);
  } else for (auto& a: v) if (!read(a)) return false;
  return true;
}

// c-style array reader
template <typename T, size_t N> bool read(T (&v)[N]) {
  for (auto& x: v) if (!read(x)) return false;
  return true;
}

// PRINT

// generic writer
template<typename T> void write(const T& h) { 
  std::cout << h;
}

// c-style string writer
void write(const char* s) { 
  std::cout << s;
}

// bool writer
void write(bool const& b) {
  std::cout << (b ? "true" : "false" );
}

// pair writer
template<typename H, typename T> void write(std::pair<H, T> const& p) {
  std::cout << '(' << p.first << ", " << p.second << ")";
}

// tuple writer
namespace tuple_writer{
  template<std::size_t...> struct seq{};
  template<std::size_t N, std::size_t... Is> struct gen_seq : gen_seq<N-1, N-1, Is...>{};
  template<std::size_t... Is> struct gen_seq<0, Is...> : seq<Is...>{};
  template<class Ch, class Tr, class Tuple, std::size_t... Is>
  void print_tuple(std::basic_ostream<Ch,Tr>& os, Tuple const& t, seq<Is...>){
    using swallow = int[]; (void)swallow{0, (void(os << (Is == 0? "" : ", ") << std::get<Is>(t)), 0)...};
  }
}
template<class Ch, class Tr, class... Args>
auto operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) -> std::basic_ostream<Ch, Tr>& {
  os << "("; tuple_writer::print_tuple(os, t, tuple_writer::gen_seq<sizeof...(Args)>()); return os << ")";
}

// vector writer
template<typename H> void write(const std::vector<H>& v) { 
  for (auto [i, x]: enumerate(v)) {
    if (i > 0) std::cout << ", ";
    write(x);
  } 
}

// c-style array writer
template <typename T, size_t N> void write(const T (&v)[N]) {
  for (size_t i(0); i<N; ++i) {
    if (i > 0) std::cout << ", ";
    write(v[i]);
  } 
}

// vector vector writer
template<typename H> void write(const std::vector<std::vector<H>>& v) {
  for (const auto& x : v) {
    if (&x != &v[0]) std::cout << std::endl;
    write(x);
  }
}

// c-style array array writer
template <typename T, size_t N, size_t M> void write(const T (&v)[N][M]) {
  for (size_t i(0); i<N; ++i) {
    if (i > 0) std::cout << std::endl;
    write(v[i]);
  } 
}

// map writer
template<typename H, typename T> void write(const std::map<H, T>& m) { 
  typename std::map<H, T>::const_iterator i;
    for (i = m.begin(); i != m.end(); ++i) {
      if (i != m.begin()) std::cout << std::endl;
      write(i->first, ":", i->second);
    }
}

// print
void print() { std::cout << std::endl; }
template<typename H, typename... T> void print(const H& h, const T&... t) { 
  write(h);
  if(sizeof...(t)) write(' ');
  print(t...);
}

// MATH

// gcd
long long unsigned int gcd(long long unsigned int const& a, long long unsigned int const& b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
template <typename T> long long unsigned int gdc(const T& v) {
  long long unsigned int a = v[0];
  for (auto const& x : v) a = gdc(a, x); return a;

}
template <typename T, size_t N> T gdc(const T (&v)[N]) {
  long long unsigned int a = v[0];
  for (auto const& x : v) a = gdc(a, x); return a;
}

// lcm
long long unsigned int lcm(long long unsigned int const& a, long long unsigned int const& b) {
  return (a * b) / gcd(a, b);
}
template <typename T> long long unsigned int lcm(const T& v) {
  long long unsigned int a = v[0];
  for (auto const& x : v) a = lcm(a, x); return a;

}
template <typename T, size_t N> T lcm(const T (&v)[N]) {
  long long unsigned int a = v[0];
  for (auto const& x : v) a = lcm(a, x); return a;
}
#endif // UTILS_H
