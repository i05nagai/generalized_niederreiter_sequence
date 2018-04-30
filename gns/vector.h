#pragma once
#include <algorithm>
#include <memory>
#include "gns/galois_field.h"
#include "gns/galois_field_operator.h"

namespace gns {
template <int Base>
class Vector {
  // private typedef
 private:
  // public typedef
 public:
  typedef GaloisField<Base> value_type;
  typedef GaloisField<Base>* iterator;
  typedef const GaloisField<Base>* const_iterator;
  // public function
 public:
  /**
   * @brief
   */
  Vector() : size_(0), data_(nullptr) {}
  /**
   * @brief
   *
   * @param size
   */
  Vector(const size_t size) : size_(size), data_(new value_type[size]) {}
  /**
   * @brief
   *
   * @param size
   * @param data
   */
  Vector(const size_t size, std::unique_ptr<value_type[]>&& data)
      : size_(size), data_(std::move(data)) {}
  /**
   * @brief
   *
   * @param data
   */
  Vector(std::initializer_list<unsigned char> data) : Vector(data.size()) {
    std::copy(data.begin(), data.end(), data_.get());
  }
  /**
   * @brief
   *
   * @param other
   */
  Vector(Vector<Base>&& other)
      : size_(other.size_), data_(std::move(other.data_)) {}
  /**
   * @brief
   *
   * @param other
   */
  Vector(const Vector<Base>& other)
      : size_(other.size_), data_(new value_type[size_]) {
    std::copy(data_.get(), data_.get() + size_, other.data_.get());
  }

  ~Vector() {}

  inline Vector<Base>& operator=(Vector<Base>&& other) {
    size_ = other.size;
    data_ = std::move(other.data_);
    return *this;
  }

  inline Vector<Base>& operator=(const Vector<Base>& other) {
    size_ = other.size;
    data_ = std::unique_ptr<value_type[]>(new value_type[size_]);
    std::copy(data_.get(), data_.get() + size_, other.data_.get());
    return *this;
  }

  inline bool operator==(const Vector<Base>& other) const {
    return size_ == other.size_ &&
           std::equal(data_.get(), data_.get() + size_, other.data_.get());
  }

  inline bool operator!=(const Vector<Base>& other) const {
    return !(*this == other);
  }

  inline value_type& operator[](const size_t index) {
    assert(index < size_);
    return data_[index];
  }

  inline const value_type& operator[](const size_t index) const {
    assert(index < size_);
    return data_[index];
  }

  inline value_type& operator()(const size_t index) {
    assert(index < size_);
    return data_[index];
  }

  inline const value_type& operator()(const size_t index) const {
    assert(index < size_);
    return data_[index];
  }

  inline size_t Size() const { return size_; }

  inline iterator begin() { return data_.get(); }

  inline const_iterator begin() const { return data_.get(); }

  inline iterator end() { return data_.get() + size_; }

  inline const_iterator end() const { return data_.get() + size_; }

  // private function
 private:
  // private members
 private:
  size_t size_;
  std::unique_ptr<value_type[]> data_;
};

template <int Base>
std::ostream& operator<<(std::ostream& os, const Vector<Base>& vector) {
  for (size_t row = 0; row < vector.Size(); ++row) {
    os << vector(row) << " ";
  }
  os << std::endl;
  return os;
}
}  // namespace gns
