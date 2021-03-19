#include "big_num.h"

bool BigNum::compare(const BigNum &a, const BigNum &b) {
    if (a.num.size() < b.num.size()) {
        return true;
    } else if (a.num.size() > b.num.size()) {
        return false;
    }
    auto ai = a.num.rbegin();
    auto bi = b.num.rbegin();

    while (ai != a.num.rend()) {
        if (*ai < *bi) {
            return true;
        } else if (*ai > *bi) {
            return false;
        }
        ai++;
        bi++;
    }
    return false;
}

bool operator<(const BigNum& a, const BigNum& b) {
    if (a.is_negative && !b.is_negative) {
        return true;
    } else if (!a.is_negative && b.is_negative) {
        return false;
    }

    if (!a.is_negative) {
        return BigNum::compare(a, b);
    } else {
        return BigNum::compare(b, a);
    }
}

bool operator>(const BigNum& a, const BigNum& b) {
    if (a.is_negative && !b.is_negative) {
        return false;
    } else if (!a.is_negative && b.is_negative) {
        return true;
    }

    if (a.is_negative) {
        return BigNum::compare(a, b);
    } else {
        return BigNum::compare(b, a);
    }
}
