#include "big_num.h"

BigNum::BigNum(int num) {
    if (num < 0) {
        this->isNegative = true;
        num = -num;
    } else {
        this->isNegative = false;
    }

    for (int i = num % 10; num != 0; num /= 10, i = num % 10) {
        this->num.insert(this->num.begin(), i);
    }
}
