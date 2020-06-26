#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class BigInt
{
private:
    std::vector<unsigned> numbers;
    bool sign;
    static const int numberBase = 10000; // 10000*10000=100000000-max in int
    BigInt UnsignDeductionNumber(const BigInt& b) const;
    BigInt UnsignAddNumber(const BigInt& b) const;
    bool UnsignCompare(const BigInt& b) const;

public:
    // конструкторы
    BigInt();
    BigInt(const std::string str);
    // операции
    BigInt operator+(const BigInt& b) const;
    BigInt operator-(const BigInt& b) const;
    BigInt operator*(const BigInt& b) const;
    BigInt operator/(const BigInt& b) const;
    BigInt operator-() const;
    BigInt abs() const;
    // булевые операции
    bool operator==(const BigInt& b) const;
    bool operator!=(const BigInt& b) const;
    bool operator>=(const BigInt& b) const;
    bool operator<=(const BigInt& b) const;
    bool operator>(const BigInt& b) const;
    bool operator<(const BigInt& b) const;
    // in/out
    friend std::ostream& operator<<(std::ostream& stream, const BigInt& b);
    friend std::istream& operator>>(std::istream& stream, BigInt& b);
};

#endif
