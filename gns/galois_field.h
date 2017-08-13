#pragma once
#include <cassert>
#include <iostream>

namespace gns {
template <int Base>
class GaloisField {
 public:
  /**
   * @brief
   */
  explicit GaloisField() : value_(0) {}
  /**
   * @brief
   *
   * @param other
   */
  GaloisField(const unsigned int other) : value_(other) {
    assert(other < Base);
  }
  /**
   * @brief
   *
   * @param other
   */
  GaloisField(const GaloisField<Base>& other) : value_(other.value_) {
    assert(value_ < Base);
  }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  GaloisField<Base>& operator=(const GaloisField<Base>& other) {
    value_ = other.value_;
    assert(value_ < Base);
    return *this;
  }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  bool operator==(const GaloisField<Base>& other) {
    return value_ == other.value();
  }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  bool operator==(const GaloisField<Base>& other) const {
    return value_ == other.value();
  }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  bool operator!=(const GaloisField<Base>& other) { return !(*this == other); }
  /**
   * @brief
   *
   * @param other
   *
   * @return
   */
  bool operator!=(const GaloisField<Base>& other) const {
    return !(*this == other);
  }
  /**
   * @brief
   *
   * @return
   */
  unsigned int value() const {
    // assert(value_ < Base);
    return value_;
  }

 private:
  /**
   * @brief
   */
  unsigned int value_;
};
}  // namespace gns
