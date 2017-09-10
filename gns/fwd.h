#pragma once

namespace gns {
/*--------------------------------------------------------------------------
 * galois_field.h
 *------------------------------------------------------------------------*/
template <int Base>
class GaloisField;

/*--------------------------------------------------------------------------
 * galois_field_operator.h
 *------------------------------------------------------------------------*/
/**
 * @brief
 *
 * @tparam Base
 * @param left
 * @param right
 *
 * @return
 */
template <int Base>
inline unsigned char add(const unsigned char left, const unsigned char right);
/**
 * @brief
 *
 * @tparam Base
 * @param left
 * @param right
 *
 * @return
 */
template <int Base>
inline unsigned char sub(const unsigned char left, const unsigned char right);
/**
 * @brief
 *
 * @tparam Base
 * @param left
 * @param right
 *
 * @return
 */
template <int Base>
inline unsigned char mult(const unsigned char left, const unsigned char right);
/**
 * @brief
 *
 * @tparam Base
 * @param left
 * @param right
 *
 * @return
 */
template <int Base>
inline unsigned char div(const unsigned char left, const unsigned char right);
/**
 * @brief 
 *
 * @tparam Base
 * @param left
 * @param right
 *
 * @return 
 */
template <int Base>
inline unsigned char minus(const unsigned char value);
}  // namespace gns
