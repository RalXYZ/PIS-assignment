#ifndef SEC2021_HW2_BIG_NUM_H
#define SEC2021_HW2_BIG_NUM_H

#include <iostream>
#include <vector>

using namespace std;

class BigNum {
    bool is_negative = false;
    vector<int> num;

    static bool compare(const BigNum&, const BigNum&);
    friend bool operator<(const BigNum&, const BigNum&);
    friend bool operator>(const BigNum&, const BigNum&);

    friend BigNum& operator+(const BigNum&, const BigNum&);
    friend BigNum& operator-(const BigNum&, const BigNum&);
    friend BigNum& operator*(const BigNum&, const BigNum&);
    friend BigNum& operator/(const BigNum&, const BigNum&);

    friend istream& operator>>(istream&, BigNum&);
    friend ostream& operator<<(ostream&, const BigNum&);

public:
    BigNum() = default;
    explicit BigNum(int);
};

#endif //SEC2021_HW2_BIG_NUM_H
