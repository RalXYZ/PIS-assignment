#include "big_num.h"

BigNum& operator+(const BigNum& a, const BigNum& b) {
    if (!a.is_negative && b.is_negative) {
        auto temp = new BigNum;
        temp->is_negative = false;
        temp->num = b.num;
        return a - *temp;
    } else if (a.is_negative && !b.is_negative) {
        auto temp = new BigNum;
        temp->is_negative = false;
        temp->num = a.num;
        return b - *temp;
    }

    auto result = new BigNum;
    auto ai = a.num.begin();
    auto bi = b.num.begin();

    result->is_negative = a.is_negative;

    auto carry = false;
    while (true) {
        if (ai == a.num.end() && bi == b.num.end()) {
            if (carry) {
                result->num.push_back(1);
            }
            break;
        } else {
            int result_digit;
            if (ai == a.num.end()) {
                result_digit = *bi + int(carry);
                ++bi;
            } else if (bi == b.num.end()) {
                result_digit = *ai + int(carry);
                ++ai;
            } else {
                result_digit = *ai + *bi + int(carry);
                ++ai;
                ++bi;
            }

            if (result_digit >= 10) {
                result_digit -= 10;
                carry = true;
            } else {
                carry = false;
            }
            result->num.push_back(result_digit);
        }
    }

    return *result;
}

BigNum& operator-(const BigNum& a, const BigNum& b) {
    if (!a.is_negative && b.is_negative) {
        auto temp = new BigNum;
        temp->num = b.num;
        temp->is_negative = false;
        return a + *temp;
    } else if (a.is_negative && !b.is_negative) {
        auto temp = new BigNum;
        temp->num = b.num;
        temp->is_negative = true;
        return a + *temp;
    }

    if ((!a.is_negative && !b.is_negative) && a < b) {
        auto a1 = new BigNum;
        a1->num = a.num;
        a1->is_negative = true;
        auto b1 = new BigNum;
        b1->num = b.num;
        b1->is_negative = true;
        return *b1 - *a1;
    } else if ((a.is_negative && b.is_negative) && a > b) {
        auto a1 = new BigNum;
        a1->num = a.num;
        a1->is_negative = false;
        auto b1 = new BigNum;
        b1->num = b.num;
        b1->is_negative = false;
        return *b1 - *a1;
    }

    // a >= b
    auto result = new BigNum;
    result->num = a.num;
    result->is_negative = a.is_negative;
    auto ai = result->num.begin();
    int carry = false;
    for (auto bi = b.num.begin(); carry || bi != b.num.end(); ai++) {
        if (carry) {
            (*ai)--;
        }
        if (bi != b.num.end()) {
            *ai -= *bi;
            bi++;
        }
        if (*ai < 0) {
            carry = true;
            *ai += 10;
        } else {
            carry = false;
        }
    }
    auto p = result->num.rbegin();
    for (; p != result->num.rend(); p++) {
        if (*p != 0) {
            break;
        }
        result->num.pop_back();
    }

    return *result;
}

BigNum& operator*(const BigNum& a, const BigNum& b) {
    auto out = new BigNum;
    out->num.resize(a.num.size() * b.num.size() + 1);
    for (auto &i : out->num) {
        i = 0;
    }

    auto ic = 0;
    for (auto &i : a.num) {
        auto jc = 0;
        for (auto &j : b.num) {
            out->num.at(ic + jc) += i * j;
            jc++;
        }
        ic++;
    }

    for (auto i = out->num.begin(); i < out->num.end(); i++) {
        *(i + 1) +=  *i / 10;
        *i %= 10;
    }

    for (auto i = out->num.rbegin(); i != out->num.rend(); i++) {
        if (*i != 0) {
            break;
        }
        out->num.pop_back();
    }

    if (a.is_negative == b.is_negative) {
        out->is_negative = false;
    } else {
        out->is_negative = true;
    }

    return *out;
}
