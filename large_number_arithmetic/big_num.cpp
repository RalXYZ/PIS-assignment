#include "big_num.h"

BigNum::BigNum(int num) {
    if (num < 0) {
        this->is_negative = true;
        num = -num;
    } else {
        this->is_negative = false;
    }

    for (int i = num % 10; num != 0; num /= 10, i = num % 10) {
        this->num.push_back(i);
    }
}
