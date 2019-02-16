//
// Created by ZV on 28.09.2018.
//

#ifndef BIGUNSIGNEDINTEGER_BIGUNSIGNEDINT_H
#define BIGUNSIGNEDINTEGER_BIGUNSIGNEDINT_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <regex>
#include <queue>

const std::size_t BIG_UNSIGNED_INT_SIZE = 64;

class BigUnsignedIntBase10;

/**
 * Template of input operator for BigUnsignedInt of size N. Expects
 * a number in decimal system as input.
 * @tparam N - size of BigUnsignedInt to read
 * @param is - input stream from which BigUnsignedInt will be read
 * @param bigUnsignedInt - object to store number read
 * @return - reference to is
 */
std::istream& operator>>(std::istream& is, BigUnsignedIntBase10& bigUnsignedInt);

/**
 * Template of output operator for BigUnsignedInt of size N. Outputs
 * binary representation of provided object.
 * @tparam N - size of BigUnsignedInt to write
 * @param os - output stream
 * @param number - object to write to stream
 * @return - reference to os
 */
std::ostream& operator<<(std::ostream& os, const BigUnsignedIntBase10& number);

/**
 * Template of output operator for BigUnsignedInt rvalues of size N.
 * Outputs binary representation of provided object.
 * @tparam N - size of BigUnsignedInt to write
 * @param os - output stream
 * @param bigUnsignedInt - object to write to stream
 * @return - reference to os
 */
std::ostream& operator<<(std::ostream& os, BigUnsignedIntBase10&& bigUnsignedInt);

/**
 * Template of shift to the left operator for BigUnsignedInt of size N.
 * @tparam N - size of BigUnsignedInt
 * @param bigUnsignedInt - object to shift
 * @param shift - number of bits to shift
 * @return - copy of bigUnsignedInt shifted by the provided number of bits
 */

/*BigUnsignedIntBase10 operator<<(BigUnsignedIntBase10 bigUnsignedInt, std::size_t shift);*/

/**
 * Template of operator+ for BigUnsignedInt of size N.
 * @tparam N - size of BigUnsignedInt
 * @param a - first operand
 * @param b - second operand
 * @return - sum of first and second operands
 */
BigUnsignedIntBase10 operator+(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

/**
 * Template of operator- for BigUnsignedInt of size N.
 * @tparam N - size of BigUnsignedInt
 * @param a - first operand
 * @param b - second operand
 * @return - difference between first and second operands
 */
BigUnsignedIntBase10 operator-(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

/**
 * Tempalate of operator* for BigUnsignedInt of size N.
 * @tparam N - size of BigUnsignedInt
 * @param a - first operand
 * @param b - second operand
 * @return - product of first and second operands
 */
BigUnsignedIntBase10 operator*(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

/**
 *
 * @param a
 * @param b
 * @return
 */
BigUnsignedIntBase10 operator/(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

/**
 *
 * @param a
 * @param b
 * @return
 */
std::pair<BigUnsignedIntBase10, BigUnsignedIntBase10>
quotientAndMod(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

/**
 *
 * @param a
 * @param b
 * @return
 */
bool operator<(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

bool operator>(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

bool operator<=(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

bool operator>=(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

bool operator==(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

bool operator!=(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

/**
 *
 * @param a
 * @param b
 * @return
 */
BigUnsignedIntBase10 MultInverse(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

/**
 * BigUnsignedInt class represents unsigned integer which has N bits
 * in binary representation.
 * @tparam N - number of bits in unsigned integer
 */
class BigUnsignedIntBase10 {
public:

    ///
    /// Type aliases
    ///
    using Digit = unsigned int;
    using UnsignedVector = std::vector<Digit>;
    using size_type = UnsignedVector::size_type;

    static const Digit _base = 10;
    static const Digit _max_digit = _base - 1;

    ///
    /// Friends
    ///
    friend std::istream& operator>>(std::istream& is, BigUnsignedIntBase10& bigUnsignedInt);

    friend std::ostream& operator<<(std::ostream& os, const BigUnsignedIntBase10& bigUnsignedInt);

    friend std::ostream& operator<<(std::ostream& os, BigUnsignedIntBase10&& bigUnsignedInt);

    friend bool operator<(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

    friend bool operator==(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

    friend BigUnsignedIntBase10 operator*(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

    friend std::pair<BigUnsignedIntBase10, BigUnsignedIntBase10>
    quotientAndMod(const BigUnsignedIntBase10& a, const BigUnsignedIntBase10& b);

public:

    ///\brief Default constructor
    BigUnsignedIntBase10() = default;

    /**\brief Creates BigUnsignedInt object from string representation.
     * Throws same exceptions as createFromString for the same reasons.
     * @param stringRepr - string containing an unsigned number
     */
    explicit BigUnsignedIntBase10(std::string_view str);

    /**
     * \brief Creates BigUnisgnedInt object capable to hold size digits.
     * @param size - quantity of digits in this number.
     */
    explicit BigUnsignedIntBase10(size_type size) : _digits(size, 0), _digitsNumber(size) {}

    /**
     * Creates number from specified range.
     * @param b - iterator to the least significant digit.
     * @param e - iterator to past the most significant digit.
     */
    BigUnsignedIntBase10(UnsignedVector::const_iterator b, UnsignedVector::const_iterator e);

    /**\brief Increases this BigUnsignedInt by other.
     * @param other - BigUnsignedInt to add
     * @return - reference to *this object increased by other
     */
    BigUnsignedIntBase10& operator+=(const BigUnsignedIntBase10& other);

    /**\brief Decreases this BigUnsignedInt by other.
     * @param other - BigUnsignedInt to subtract
     * @return - reference to *this object decreased by other
     */
    BigUnsignedIntBase10& operator-=(const BigUnsignedIntBase10& other);

    /**\brief Multiplies this BigUnsignedInt by other.
     * @param other - BigUnsignedInt to multiply on
     * @return - reference to *this object multiplied by other
     */
    BigUnsignedIntBase10& operator*=(const BigUnsignedIntBase10& other);

    /**
     * \brief Divides this BigUnsignedInt by other.
     * @param other - BigUnsignedInt to divide by.
     * @return - reference to *this object divided by other
     */
    BigUnsignedIntBase10& operator/=(const BigUnsignedIntBase10& other);

    /**
     * \brief Divides this BigUnsignedInt by other, returning quotient and reminder.
     * This function modifies *this by storing quotient in it.
     * @param other - BigUnsignedInt to divide by.
     * @return - pair (quotient, reminder), where quotient is reference to *this object
     * and reminder is ordinary BigUnsignedInt.
     */
    std::pair<BigUnsignedIntBase10, BigUnsignedIntBase10> quotientAndMod(const BigUnsignedIntBase10& other) const;

    /**
     *
     * @param degree
     * @return
     */
    BigUnsignedIntBase10 pow(const BigUnsignedIntBase10& degree);

    /**
     *
     * @param a
     * @return
     */
    BigUnsignedIntBase10 multInverse(BigUnsignedIntBase10 a);

    /**
     * \brief Provides access to digits of the number by index.
     * @param index - position of digit in number
     * @return - Reference to digit in specified position.
     */
    UnsignedVector::value_type& operator[](size_type index) { return _digits[index]; }

    /**
     * \brief Provides access to digits of the number by index.
     * @param index - position of digit in number
     * @return - Reference to digit in specified position.
     */
    const UnsignedVector::value_type& operator[](size_type index) const { return _digits[index]; }

    /**
     * @return String representation of number
     */
    std::string to_string() const;

private:

    /**
     * \brief Resets number to zero
     */
    void resetToZero();

    /**
     * Stores binary representation of number contained in string in provided object.
     * Throws invalid argument exception if provided string contains something
     * else but digits, size of BigUnsignedInt is too small to represent provided number.
     * @param input - string containing an unsigned number
     * @param number - object to store the number converted from string
     */
    static void createFromString(std::string_view str, BigUnsignedIntBase10& number);

    /**
     * Sets the _digitsNumber with appropriate number.
     */
    size_type countSignificantNumbers();

    /**
     * Performs division of *this on digit d.
     * @param d - digit to divide on.
     * @return - pair (quotient, reminder)
     */
    std::pair<BigUnsignedIntBase10, BigUnsignedIntBase10> quotientAndMod(Digit d) const;

    /**
     * \breif Resizes number so it can store specified number of digits
     * @param size - new required number of digits
     */
    void resize(size_type size);

    /**
     * @return - Number of digits which can be stored without resize in this number.
     */
    inline size_type size() const { _digits.size(); }

    /**
     * @return - Index of the most significant digit counting from end of _digits.
     */
    inline size_type startIndex() const { return size() - _digitsNumber; }

    /**
     * @return - reverse iterator to the position of the most significant digit.
     */
    UnsignedVector::reverse_iterator startIter() { return _digits.rbegin() + startIndex(); }

    /**
     * @return - constant reverse iterator to the position of the most significant digit.
     */
    UnsignedVector::const_reverse_iterator startIter() const { return _digits.crbegin() + startIndex(); }

private:
    UnsignedVector _digits; // Stores digit of the number in reverse order (little-endian)
    size_type _digitsNumber; // number of significant digits
};

#endif //BIGUNSIGNEDINTEGER_BIGUNSIGNEDINT_H
