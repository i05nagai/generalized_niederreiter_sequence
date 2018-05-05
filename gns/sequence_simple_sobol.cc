#include "gns/parameters/joe_kuo_d6_21201_irreducible.h"
#include "gns/parameters/joe_kuo_d6_21201_initial_number.h"
#include "gns/sequence_simple_sobol.h"
#include "gns/util.h"

namespace gns {
SimpleSobolGrayMap::SimpleSobolGrayMap(const size_t dimension)
: dimension_(dimension),
  premitive_polynomials_(dimension_),
  direction_numbers_(dimension_, std::vector<size_t>(MAX_BIT)),
  number_(dimension_),
  points_(std::vector<double>(dimension_)),
  counter_(0),
  is_first_(true)
  {
  std::vector<size_t> degrees(dimension_);

  // load parameters
  for (size_t dim = 0; dim < dimension_; ++dim) {
    premitive_polynomials_[dim] = joe_kuo_d6_21201_irreducibles[dim];
    degrees[dim] = CalculateDegree<2>(premitive_polynomials_[dim]);
    for (size_t k = 0; k < joe_kuo_d6_21201_initial_number[dim].size(); ++k) {
      direction_numbers_[dim][k] = joe_kuo_d6_21201_initial_number[dim][k];
      direction_numbers_[dim][k] <<= (MAX_BIT - (k + 1));
    }
  }

  // calculate direction number
  for (size_t dim = 0; dim < dimension_; ++dim) {
    const size_t degree = degrees[dim];
    for (size_t k = degree; k < MAX_BIT; ++k) {
      size_t sum = direction_numbers_[dim][k - degree] >> degree;
      for (size_t i = 0; i < degree; ++i) {
        const size_t coeff = (premitive_polynomials_[dim] >> (degree - i) & 1UL);
        if (coeff == 1) {
          sum ^= direction_numbers_[dim][k - i];
        }
      }
      direction_numbers_[dim][k] = sum;
    }
  }

  // initialize
  for (size_t dim = 0; dim < dimension_; ++dim) {
    // initial points is 0
    points_[dim] = 0.0;
  }
}

std::vector<double> SimpleSobolGrayMap::Next() {
  if (is_first_) {
    is_first_ = false;
    return points_;
  }

  // find right most zero bit
  size_t l = 0;
  while (((counter_ >> l) & 1) == 1) {
    l++;
  }
  for (size_t dim = 0; dim < dimension_; ++dim) {
    number_[dim] ^= direction_numbers_[dim][l];
    points_[dim] = number_[dim] * NORMALIZE_FACTOR;
  }

  counter_++;
  return points_;
}

} // namespace gns
