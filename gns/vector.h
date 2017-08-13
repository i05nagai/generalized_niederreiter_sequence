#pragma once
#include "gns/galois_field.h"

namespace gns {
template <int Base>
class Vector {
  // private typedef
 private:
  // public typedef
 public:
  typedef GaloisField<Base> value_type;
  // public function
 public:
  Vector(const size_t size) : size_(size), data_(new value_type[size]) {}

  ~Vector() {}

  inline value_type& operator()(const size_t index) {
    assert(index < size_);
    return data_[index];
  }

  inline const value_type& operator()(const size_t index) const {
    assert(index < size_);
    return data_[index];
  }

  inline size_t Size() const { return size_; }

  // private function
 private:
  // private members
 private:
  size_t size_;
  std::unique_ptr<value_type[]> data_;
};
}  // namespace gns
