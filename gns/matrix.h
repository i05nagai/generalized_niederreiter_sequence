#pragma once
#include <algorithm>
#include <memory>
#include "gns/galois_field.h"
#include "gns/galois_field_operator.h"

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
  /**
   * @brief
   */
  explicit Matrix() : row_size_(0), col_size_(0), data_(nullptr) {}
  /**
   * @brief
   *
   * @param row_size
   * @param col_size
   */
  Matrix(const size_t row_size, const size_t col_size)
      : row_size_(row_size),
        col_size_(col_size),
        data_(new value_type[row_size * col_size]) {}
  /**
   * @brief
   *
   * @param row_size
   * @param col_size
   * @param data
   */
  Matrix(const size_t row_size, const size_t col_size,
         std::unique_ptr<value_type[]> data)
      : row_size_(row_size), col_size_(col_size), data_(std::move(data)) {}
  /**
   * @brief
   *
   * @param other
   */
  Matrix(const Matrix<Base>& other)
      : row_size_(other.row_size_),
        col_size_(other.col_size_),
        data_(new value_type[row_size_ * col_size_]) {
    const size_t size = row_size_ * col_size_;
    std::copy(other.data_.get(), other.data_.get() + size, data_.get());
  }
  /**
   * @brief
   *
   * @param other
   */
  Matrix(Matrix<Base>&& other)
      : row_size_(other.row_size_),
        col_size_(other.col_size_),
        data_(std::move(other.data_)) {
    other.data_ = nullptr;
  }
  /**
   * @brief
   */
  ~Matrix() {}
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  inline Matrix<Base>& operator=(const Matrix<Base>& other) {
    row_size_ = other.row_size_;
    col_size_ = other.col_size_;
    const size_t size = row_size_ * col_size_;
    data_ = std::unique_ptr<value_type[]>(new value_type[size]);
    std::copy(data_.get(), data_.get() + size, other.data_.get());
    return *this;
  }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  inline Matrix<Base>& operator=(Matrix<Base>&& other) {
    row_size_ = other.row_size_;
    col_size_ = other.col_size_;
    data_ = std::move(other.data_);
    other.data_ = nullptr;
    return *this;
  }

  inline bool operator==(const Matrix<Base>& other) const {
    const size_t size = row_size_ * col_size_;
    return row_size_ == other.row_size_ && col_size_ == other.col_size_ &&
           std::equal(data_.get(), data_.get() + size, other.data_.get());
  }

  inline bool operator!=(const Matrix<Base>& other) const {
    return !(*this == other);
  }

  inline value_type& operator()(const size_t row, const size_t col) {
    assert(row < row_size_);
    assert(col < col_size_);
    return data_[col_size_ * row + col];
  }

  inline const value_type& operator()(const size_t row,
                                      const size_t col) const {
    assert(row < row_size_);
    assert(col < col_size_);
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

template <int Base>
std::ostream& operator<<(std::ostream& os, const Matrix<Base>& matrix) {
  for (size_t row = 0; row < matrix.RowSize(); ++row) {
    for (size_t col = 0; col < matrix.ColSize(); ++col) {
      os << matrix(row, col) << " ";
    }
    os << std::endl;
  }
  return os;
}
}  // namespace gns
