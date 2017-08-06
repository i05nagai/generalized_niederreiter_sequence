#pragma once
#include <cassert>
#include <iostream>

namespace gns {
template <int Base>
class GaloisField {
public:
  explicit GaloisField()
  : value_(0)
  {
  }

  GaloisField(const unsigned int other)
  : value_(other)
  {
    assert(other < Base);
  }

  GaloisField(const GaloisField<Base>& other)
  : value_(other.value_)
  {
    assert(value_ < Base);
  }

  GaloisField<Base>&
  operator =(const GaloisField<Base>& other)
  {
    value_ = other.value_;
    assert(value_ < Base);
    return *this;
  }

  bool operator==(const GaloisField<Base>& other)
  {
    return value_ == other.value();
  }

  bool operator==(const GaloisField<Base>& other) const
  {
    return value_ == other.value();
  }

  bool operator!=(const GaloisField<Base>& other)
  {
    return !(*this == other);
  }

  bool operator!=(const GaloisField<Base>& other) const
  {
    return !(*this == other);
  }

  unsigned int value() const
  {
    //assert(value_ < Base);
    return value_;
  }
private:
  unsigned int value_;
};
} // namespace gns

