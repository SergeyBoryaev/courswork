#include "BigInt.h"

std::vector<unsigned> karacubaMult(const std::vector<unsigned>& a, const std::vector<unsigned>& b);
std::vector<unsigned> mult(const std::vector<unsigned>& a, const std::vector<unsigned>& b);

BigInt BigInt::UnsignAddNumber(const BigInt& b) const
{
    BigInt a;
    a = (*this);
    int remainder = 0;
    for (long i = 0; i < std::max(a.numbers.size(), b.numbers.size()); i++)
    {
        if (i == a.numbers.size())
            a.numbers.push_back(0);
        a.numbers[i] += remainder + (i < b.numbers.size() ? b.numbers[i] : 0);
        remainder = a.numbers[i] >= numberBase;
        if (remainder)
            a.numbers[i] -= numberBase;
    }
    if (remainder)
        a.numbers.push_back(1);
    return a;
}

BigInt BigInt::UnsignDeductionNumber(const BigInt& b) const
{
    BigInt a;
    a = (*this);
    int remainder = 0;
    for (long i = 0; i < b.numbers.size() || remainder; ++i)
    {
        a.numbers[i] -= remainder + (i < b.numbers.size() ? b.numbers[i] : 0);
        remainder = a.numbers[i] < 0;
        if (remainder)
            a.numbers[i] += remainder;
    }
    while (a.numbers.size() > 1 && a.numbers.back() == 0)
        a.numbers.pop_back();
    return a;
}

bool BigInt::UnsignCompare(const BigInt& b) const
{
    if (numbers.size() > b.numbers.size())
        return 1;
    if (numbers.size() < b.numbers.size())
        return 0;
    int i = 0;
    for (; i < numbers.size(); i++)
        if (numbers[i] != b.numbers[i])
            break;
    if (i == numbers.size())
        return 1;
    if (numbers[i] >= b.numbers[i])
        return 1;
    return 0;
}

//конструкторы
BigInt::BigInt()
{
    this->numbers.push_back(0);
    this->sign = 0;
}

BigInt::BigInt(const std::string str)
{
    std::string number = str;
    this->sign = 0;
    if (number[0] == '-')
    {
        this->sign = 1;
        number = number.substr(1);
    }
    for (int i = number.size(); i > 0; i -= 4)
    {
        if (i >= 4)
            this->numbers.push_back(atoi(number.substr(i - 4, 4).data()));
        else
            this->numbers.push_back(atoi(number.substr(0, i).data()));
    }
}

//операции
BigInt BigInt::operator+(const BigInt& b) const
{
    BigInt temp;
    if (this->sign == b.sign)
    {
        temp = (this->UnsignAddNumber(b));
        temp.sign = this->sign;
    }
    else
    {
        if (this->UnsignCompare(b))
        {
            temp = (this->UnsignDeductionNumber(b));
            temp.sign = this->sign;
        }
        else
        {
            temp = (b.UnsignDeductionNumber(*this));
            temp.sign = b.sign;
        }
    }
    return temp;
}

BigInt BigInt::operator-(const BigInt& b) const
{
    BigInt temp;
    if (this->sign != b.sign)
    {
        temp = (this->UnsignAddNumber(b));
        temp.sign = this->sign;
    }
    else
    {
        if (this->UnsignCompare(b))
        {
            temp = (this->UnsignDeductionNumber(b));
            temp.sign = this->sign;
        }
        else
        {
            temp = (b.UnsignDeductionNumber(*this));
            temp.sign = !(b.sign);
        }
    }
    return temp;
}

BigInt BigInt::operator*(const BigInt& b) const
{
    BigInt temp;
    if (this->sign != b.sign)
        temp.sign = 1;
    temp.numbers = karacubaMult(this->numbers, b.numbers);
    return temp;
}

BigInt BigInt::operator/(const BigInt& b) const
{
    BigInt temp, one;
        if (b == temp)
            throw 1;
    one.numbers[0] = 1;
    std::string tmpStr;
    BigInt aNew = *this;
    while (aNew.UnsignCompare(b))
    {
        aNew = aNew.UnsignDeductionNumber(b);
        temp = temp + one;
    }
    if (this->sign != b.sign)
        temp.sign = 1;
    return temp;
}

BigInt BigInt::operator-() const
{
    BigInt temp = (*this);
    temp.sign = !temp.sign;
    return temp;
}

BigInt BigInt::abs() const
{
    BigInt temp = (*this);
    temp.sign = 0;
    return temp;
}
//булевые операции
bool BigInt::operator==(const BigInt& b) const
{
    if (this->sign == b.sign && this->numbers == b.numbers)
        return 1;
    return 0;
}

bool BigInt::operator!=(const BigInt& b) const
{
    return !((*this) == b);
}

bool BigInt::operator>=(const BigInt& b) const
{
    if (this->sign == 0)
    {
        if (b.sign == 1)
            return 1;
        return this->UnsignCompare(b);
    }
    if (b.sign == 0)
        return 0;
    return !(this->UnsignCompare(b));
}

bool BigInt::operator<=(const BigInt& b) const
{
    return !((*this) > b);
}
bool BigInt::operator>(const BigInt& b) const
{
    if ((*this) >= b && ((*this) != b))
        return 1;
    return 0;
}

bool BigInt::operator<(const BigInt& b) const
{
    return !((*this) >= b);
}

//in/out
std::ostream& operator<<(std::ostream& stream, const BigInt& b)
{
    if (b.sign == 1)
        stream << '-';
    for (int i = (int)b.numbers.size() - 1; i >= 0; i--)
        stream << b.numbers[i];
    return stream;
}

std::istream& operator>>(std::istream& stream, BigInt& b)
{
    std::string str;
    stream >> str;
    b = BigInt(str);
    return stream;
}

std::vector<unsigned> mult(const std::vector<unsigned>& a, const std::vector<unsigned>& b)
{
    int remainder = 0;
    std::vector<unsigned> c(a.size() + b.size());
    for (int i = 0; i < a.size(); ++i)
        for (int j = 0; j < (int)b.size() || remainder; ++j)
        {
            long long cur = c[i + j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + remainder;
            c[i + j] = int(cur % 10000);
            remainder = int(cur / 10000);
        }
    while (c.size() > 1 && c.back() == 0)
        c.pop_back();
    return c;
}

std::vector<unsigned> karacubaMult(const std::vector<unsigned>& a, const std::vector<unsigned>& b)
{
    int len = std::max(a.size(), b.size());
    std::vector<unsigned> aNew = a;
    std::vector<unsigned> bNew = b;
    int k = len / 2;
    len = k * 2;
    aNew.resize(len);
    bNew.resize(len);
    if (len <= 4)
        return mult(a, b);
    std::vector<unsigned> c(len * 2);
    std::vector<unsigned> aH{ aNew.begin(), aNew.begin() + k };
    std::vector<unsigned> aL{ aNew.begin() + k, aNew.end() };
    std::vector<unsigned> bH{ bNew.begin(), bNew.begin() + k };
    std::vector<unsigned> bL{ bNew.begin() + k, bNew.end() };
    std::vector<unsigned> P1 = karacubaMult(aL, bL);
    std::vector<unsigned> P2 = karacubaMult(aH, bH);
    std::vector<unsigned> aHL(k);
    std::vector<unsigned> bHL(k);
    for (int i = 0; i < k; i++)
    {
        aHL[i] = aH[i] + aL[i];
        bHL[i] = bH[i] + bL[i];
    }
    std::vector<unsigned> P3 = karacubaMult(aHL, bHL);
    for (int i = 0; i < len; ++i)
    {
        P3[i] -= P2[i] + P1[i];
    }
    for (int i = 0; i < len; ++i)
    {
        c[i] = P2[i];
    }
    for (int i = len; i < 2 * len; ++i)
    {
        c[i] = P1[i - len];
    }
    for (int i = k; i < len + k; ++i)
    {
        c[i] += P3[i - k];
    }
    return c;
}