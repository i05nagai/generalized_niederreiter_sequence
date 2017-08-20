#pragma once
#include <cassert>
#include <cmath>
#include <iterator>
#include <memory>
#include <vector>
#include "gns/galois_field.h"
#include "gns/vector.h"

namespace gns {
template <typename T>
inline std::reverse_iterator<T*> rbegin(T* v) {
  return std::reverse_iterator<T*>(v);
}

template <typename T>
inline std::reverse_iterator<T*> rend(T* v) {
  return std::reverse_iterator<T*>(v);
}

template <int Base>
inline std::pair<size_t, std::unique_ptr<GaloisField<Base>[]>>
CalculateBaseAdic(size_t num) {
  assert(num > 0);

  const size_t digit = std::log(num) / std::log(Base) + 1;
  std::unique_ptr<GaloisField<Base>[]> data(new GaloisField<Base>[digit]);
  for (size_t i = 0; i < digit; ++i) {
    data[i] = num % Base;
    num = static_cast<size_t>(num / Base);
  }
  return std::make_pair(digit, std::move(data));
}

template <int Base>
inline double BaseAdicToDouble(const Vector<Base>& base_adic) {
  double point = 0.0;
  double divisor = Base;
  for (size_t i = 0; i < base_adic.Size(); ++i) {
    point += base_adic[i].value() / divisor;
    divisor *= static_cast<double>(Base);
  }
  return point;
}
}  // namespace gns
