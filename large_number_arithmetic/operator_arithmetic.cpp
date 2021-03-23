#include "big_num.h"

#include <algorithm>
#include <memory>

BigNum operator+(const BigNum& a, const BigNum& b) {
    if (!a.is_negative && b.is_negative) {
        auto temp = unique_ptr<BigNum>(new BigNum);
        temp->is_negative = false;
        temp->num = b.num;
        return a - *temp;
    } else if (a.is_negative && !b.is_negative) {
        auto temp = unique_ptr<BigNum>(new BigNum);
        temp->is_negative = false;
        temp->num = a.num;
        return b - *temp;
    }

    auto result = unique_ptr<BigNum>(new BigNum);
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

BigNum operator-(const BigNum& a, const BigNum& b) {
    if (!a.is_negative && b.is_negative) {
        auto temp = unique_ptr<BigNum>(new BigNum);
        temp->num = b.num;
        temp->is_negative = false;
        return a + *temp;
    } else if (a.is_negative && !b.is_negative) {
        auto temp = unique_ptr<BigNum>(new BigNum);
        temp->num = b.num;
        temp->is_negative = true;
        return a + *temp;
    }

    if ((!a.is_negative && !b.is_negative) && a < b) {
        auto a1 = unique_ptr<BigNum>(new BigNum);
        a1->num = a.num;
        a1->is_negative = true;
        auto b1 = unique_ptr<BigNum>(new BigNum);
        b1->num = b.num;
        b1->is_negative = true;
        return *b1 - *a1;
    } else if ((a.is_negative && b.is_negative) && a > b) {
        auto a1 = unique_ptr<BigNum>(new BigNum);
        a1->num = a.num;
        a1->is_negative = false;
        auto b1 = unique_ptr<BigNum>(new BigNum);
        b1->num = b.num;
        b1->is_negative = false;
        return *b1 - *a1;
    }

    // a >= b
    auto result = unique_ptr<BigNum>(new BigNum);
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

BigNum operator*(const BigNum& a, const BigNum& b) {
    auto result = unique_ptr<BigNum>(new BigNum);
    result->num.resize(a.num.size() * b.num.size() + 1);
    for (auto &i : result->num) {
        i = 0;
    }

    auto ic = 0;
    for (auto &i : a.num) {
        auto jc = 0;
        for (auto &j : b.num) {
            result->num.at(ic + jc) += i * j;
            jc++;
        }
        ic++;
    }

    for (auto i = result->num.begin(); i < result->num.end(); i++) {
        *(i + 1) +=  *i / 10;
        *i %= 10;
    }

    for (auto i = result->num.rbegin(); i != result->num.rend(); i++) {
        if (*i != 0) {
            break;
        }
        result->num.pop_back();
    }

    if (a.is_negative == b.is_negative) {
        result->is_negative = false;
    } else {
        result->is_negative = true;
    }

    return *result;
}

BigNum operator*(const BigNum& a, const int b) {
    auto result = unique_ptr<BigNum>(new BigNum);
    result->num = a.num;
    result->is_negative = a.is_negative;
    result->is_negative ^= (b < 0);
    auto b_t = abs(b);

    for (auto i = result->num.begin(); i < result->num.end(); i++) {
        *i *= b_t;
    }

    auto carry = 0;
    for (auto i = result->num.begin(); i < result->num.end(); i++) {
        if (*i / 10 > 0) {
            if ((i + 1) == result->num.end()) {
                carry = *i / 10;
            } else {
                *(i + 1) += *i / 10;
            }
            *i %= 10;
        }
    }

    result->num.push_back(carry);

    while ((result->num.rbegin() != result->num.rend()) && (*(result->num.rbegin()) == 0)) {
        result->num.pop_back();
    }

    return *result;
}

BigNum operator/(const BigNum& a, const BigNum& b) {
    auto result = unique_ptr<BigNum>(new BigNum);
    BigNum buffer;
    BigNum a_t;
    a_t.num = a.num;

    for (auto i = a_t.num.rbegin(); i < a_t.num.rend();) {
        buffer.num.insert(buffer.num.begin(), *i);
        int result_digit;
        for (result_digit = 1; ; result_digit++) {
            BigNum div_temp = b * result_digit;
            if (buffer < div_temp) {
                result_digit -= 1;
                break;
            }
        }
        result->num.push_back(result_digit);

        if (result_digit != 0) {
            a_t.num.erase(a_t.num.end() - buffer.num.size(), a_t.num.end());
            i = a_t.num.rbegin();
            auto temp = buffer - (b * result_digit);
            a_t.num.insert(a_t.num.begin(), temp.num.begin(), temp.num.end());
            buffer.num.resize(0);
            buffer.num = temp.num;
        }
        else {
            i++;
        }
    }

    reverse(result->num.begin(), result->num.end());

    while ((result->num.rbegin() != result->num.rend()) && (*(result->num.rbegin()) == 0)) {
        result->num.pop_back();
    }

    return *result;
}
