#pragma once
#include "gns/galois_field.h"

namespace gns {
template <int Base>
class Matrix {
  // private typedef
 private:
  // public typedef
 public:
  typedef GaloisField<Base> value_type;
  // public function
 public:
  Matrix(const size_t row_size, const size_t col_size)
      : row_size_(row_size),
        col_size_(col_size),
        data_(new value_type[row_size * col_size]) {}

  ~Matrix() {}

  inline value_type& operator()(const size_t row, const size_t col) {
    return data_[col_size_ * row + col];
  }

  inline const value_type& operator()(const size_t row,
                                      const size_t col) const {
    return data_[col_size_ * row + col];
  }

  inline size_t RowSize() const { return row_size_; }

  inline size_t ColSize() const { return col_size_; }

  // private function
 private:
  // private members
 private:
  size_t row_size_;
  size_t col_size_;
  std::unique_ptr<GaloisField<Base>[]> data_;
};
}  // namespace gns
