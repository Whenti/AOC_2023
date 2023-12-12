// AUTHOR: Quentin Lévêque
#ifndef READ_HPP
#define READ_HPP
#include <bits/stdc++.h>

#define FALSE_TYPE(is_type) template <typename T> struct is_type: std::false_type{};
FALSE_TYPE(is_std_vector);template<typename T>struct is_std_vector<std::vector<T>>:std::true_type{};
FALSE_TYPE(is_std_queue);template<typename T>struct is_std_queue<std::queue<T>>:std::true_type{};
FALSE_TYPE(is_std_stack);template<typename T>struct is_std_stack<std::stack<T>>:std::true_type{};
FALSE_TYPE(is_std_tuple);template<typename...T>struct is_std_tuple<std::tuple<T...>>:std::true_type{};
FALSE_TYPE(is_std_array);template<typename T,size_t N>struct is_std_array<std::array<T,N>>:std::true_type{};
FALSE_TYPE(is_std_pair);template<typename T1,typename T2>struct is_std_pair<std::pair<T1,T2>>:std::true_type{};
FALSE_TYPE(is_std_map);template<typename T1,typename T2>struct is_std_map<std::map<T1,T2>>:std::true_type{};
template <typename T> void generic_push(std::stack<T> & v, T x) { v.push(x); }
template <typename T> void generic_push(std::queue<T> & v, T x) { v.push(x); }
template <typename T> void generic_push(std::vector<T> & v, T x) { v.push_back(x); }

template <typename T = std::string> T read(std::istream &p) {
  T ret;
  if constexpr (is_std_array<T>::value) {
    for (auto &x : ret)
      x = read<typename T::value_type>(p);
  } else if constexpr (is_std_pair<T>::value) {
    ret = std::make_pair(read<typename T::first_type>(p),
                         read<typename T::second_type>(p));
  } else if constexpr (is_std_tuple<T>::value) {
    ret = std::apply(
        [&p](auto &&...args) {
          return std::make_tuple(read<std::decay_t<decltype(args)>>(p)...);
        },
        ret);
  } else if constexpr (is_std_map<T>::value) {
    auto key = read<typename T::key_type>(p);
    while (!p.fail()) {
      ret[key] = read<typename T::mapped_type>(p);
      key = read<typename T::key_type>(p);
    }
  } else if constexpr (is_std_vector<T>::value || is_std_stack<T>::value ||
                       is_std_queue<T>::value) {
    typename T::value_type x = read<typename T::value_type>(p);
    while (!p.fail()) {
      generic_push(ret, x);
      x = read<typename T::value_type>(p);
    }
  } else
    p >> ret;
  return ret;
}

template <typename A, typename B> std::pair<A, B> read(std::istream &p) {
  return std::make_pair(read<A>(p), read<B>(p));
}

template <typename A, typename B, typename C, typename... T>
std::tuple<A, B, C, T...> read(std::istream &p) {
  return std::tuple_cat(std::make_tuple(read<A>(p), read<B>(p), read<C>(p)),
                        std::tuple<T...>(read<T>(p)...));
}

template <typename... T> auto read() { return read<T...>(std::cin); }

template <typename... T> auto read(char *c) {
  std::string s(c);
  return read<T...>(s);
}

template <typename... T> auto read(std::string s) {
  std::istringstream iss(s);
  return read<T...>(iss);
}

std::string readline(std::istream &p = std::cin) {
  std::string x;
  std::getline(p, x);
  return x;
}

std::vector<std::string> readall(std::istream &p = std::cin) {
  std::vector<std::string> v;
  while (!p.fail())
    v.push_back(readline(p));
  v.pop_back();
  return v;
}

#endif // READ_H
