#pragma once
#include <cmath>
#include <iterator>
#include <memory>

namespace gf {
  template <typename T>
  inline std::reverse_iterator<T*> rbegin(T* v)
  {
    return std::reverse_iterator<T*>(v);
  }

  template <typename T>
  inline std::reverse_iterator<T*> rend(T* v)
  {
    return std::reverse_iterator<T*>(v);
  }

  template <int Base>
  inline
  std::pair<size_t, std::unique_ptr<unsigned char[]>>
  calcBaseAdic(size_t num)
  {
    const size_t digit = std::log(num) / std::log(Base) + 1;
    std::unique_ptr<unsigned char[]> data(new unsigned char[digit]);
    for (size_t i = 0; i < digit; ++i) {
      data[i] = num % Base;
      num = static_cast<size_t>(num / Base);
    }
    return std::make_pair(digit, std::move(data));
  }
} // namespace gf
