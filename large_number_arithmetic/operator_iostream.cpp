#include "big_num.h"

istream& operator>>(istream& is, BigNum& bigNum) {
    BigNum temp;
    while(auto i = getchar()) {
        if (i == '-') {
            bigNum.is_negative = true;
            continue;
        } else if (i == '\n') {
            break;
        }
        temp.num.push_back(i - '0');
    }

    for (auto i = temp.num.rbegin(); i < temp.num.rend(); i++) {
        bigNum.num.push_back(*i);
    }

    for (auto i = bigNum.num.rbegin(); i != bigNum.num.rend(); i++) {
        if (*i != 0) {
            break;
        }
        bigNum.num.pop_back();
    }

    return is;
}

ostream& operator<<(ostream& os, const BigNum& bigNum) {
    if (bigNum.num.empty()) {
        cout << '0';
        return os;
    }

    if (bigNum.is_negative) {
        cout << '-';
    }
    for (auto i = bigNum.num.rbegin(); i != bigNum.num.rend(); i++) {
        cout << *i;
    }
    return os;
}
