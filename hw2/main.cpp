#include <iostream>
#include <vector>

using namespace std;

vector<int>& naive_mul(const vector<int>& a, int b, int zero_num) {
    auto out = new vector<int>;
    int carry = 0;
    for (auto iter = a.rbegin(); iter != a.rend(); iter++) {
        out->insert(out->begin(), (*iter) * b + carry);
        carry = (*out)[0] / 10;
        (*out)[0] %= 10;
    }
    if (carry != 0) {
        out->insert(out->begin(), carry);
    }
    for (int i = 0; i < zero_num; i++) {
        out->push_back(0);
    }

    return *out;
}

class BigNum {
    bool isNegative = false;
    vector<int> num;

    friend bool operator<(const BigNum&, const BigNum&);
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

istream& operator>>(istream& is, BigNum& bigNum) {
    while(auto i = getchar()) {
        if (i == '-') {
            bigNum.isNegative = true;
            continue;
        } else if (i == '\n') {
            goto is_end;
        }
        bigNum.num.insert(bigNum.num.end(), i - '0');
    }

    is_end:
    return is;
}

ostream& operator<<(ostream& os, const BigNum& bigNum) {
    if (bigNum.isNegative) {
        cout << '-';
    }
    for (int i : bigNum.num) {
        cout << i;
    }
    return os;
}

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

bool operator<(const BigNum& a, const BigNum& b) {
    if (a.isNegative && !b.isNegative) {
        return true;
    } else if (!a.isNegative && b.isNegative) {
        return false;
    }

    if (!a.isNegative) {
        if (a.num.size() < b.num.size()) {
            return true;
        } else if (a.num.size() > b.num.size()) {
            return false;
        }
        auto ai = a.num.begin();
        auto bi = b.num.begin();

        while (ai != a.num.end()) {
            if (*ai < *bi) {
                return true;
            } else if (*ai > *bi) {
                return false;
            }
            ai++;
            bi++;
        }
        return false;
    } else {
        if (a.num.size() > b.num.size()) {
            return true;
        } else if (a.num.size() < b.num.size()) {
            return false;
        }
        auto ai = a.num.begin();
        auto bi = b.num.begin();

        while (ai != a.num.end()) {
            if (*ai > *bi) {
                return true;
            } else if (*ai < *bi) {
                return false;
            }
            ai++;
            bi++;
        }
        return false;
    }
}

BigNum& operator+(const BigNum& a, const BigNum& b) {
    if (!a.isNegative && b.isNegative) {
        auto o = new BigNum;
        o->isNegative = false;
        o->num = b.num;
        return a - *o;
    } else if (a.isNegative && !b.isNegative) {
        auto o = new BigNum;
        o->isNegative = false;
        o->num = a.num;
        return b - *o;
    }

    auto out = new BigNum;
    auto ai = a.num.rbegin();
    auto bi = b.num.rbegin();

    out->isNegative = a.isNegative;

    while (true) {
        static auto carry = false;
        if (ai == a.num.rend() && bi == b.num.rend()) {
            if (carry) {
                out->num.insert(out->num.begin(), 1);
            }
            break;
        } else if (ai == a.num.rend()) {
            int o = *bi + int(carry);
            if (o >= 10) {
                o -= 10;
                carry = true;
            } else {
                carry = false;
            }
            out->num.insert(out->num.begin(), o);

            ++bi;
        } else if (bi == b.num.rend()) {
            int o = *ai + int(carry);
            if (o >= 10) {
                o -= 10;
                carry = true;
            } else {
                carry = false;
            }
            out->num.insert(out->num.begin(), o);

            ++ai;
        } else {
            int o = *ai + *bi + int(carry);
            if (o >= 10) {
                o -= 10;
                carry = true;
            } else {
                carry = false;
            }
            out->num.insert(out->num.begin(), o);

            ++ai;
            ++bi;
        }
    }

    return *out;
}

BigNum& operator-(const BigNum& a, const BigNum& b) {
    if (!a.isNegative && b.isNegative) {
        auto o = new BigNum;
        o->num = b.num;
        o->isNegative = false;
        return a + *o;
    } else if (a.isNegative && !b.isNegative) {
        auto o = new BigNum;
        o->num = b.num;
        o->isNegative = true;
        return a + *o;
    }


    if ((!a.isNegative && !b.isNegative) && a < b) {
        auto a1 = new BigNum;
        a1->num = a.num;
        a1->isNegative = true;
        auto b1 = new BigNum;
        b1->num = b.num;
        b1->isNegative = true;
        return *b1 - *a1;
    } else if ((a.isNegative && b.isNegative) && b < a) {
        auto a1 = new BigNum;
        a1->num = a.num;
        a1->isNegative = false;
        auto b1 = new BigNum;
        b1->num = b.num;
        b1->isNegative = false;
        return *b1 - *a1;
    }

    // a >= b
    auto o = new BigNum;
    o->num = a.num;
    o->isNegative = a.isNegative;
    auto ai = o->num.rbegin();
    int carry = false;
    for (auto bi = b.num.rbegin(); carry || bi != b.num.rend(); ai++) {
        if (carry) {
            (*ai)--;
        }
        if (bi != b.num.rend()) {
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
    auto p = o->num.begin();
    for (; p != o->num.end(); p++) {
        if (*p != 0) {
            break;
        }
    }
    if (p > o->num.begin()) {
        o->num.erase(o->num.begin(), p);
    }
    if (o->num.empty()) {
        o->num.push_back(0);
        o->isNegative = false;
    }

    return *o;
}

BigNum& operator*(const BigNum& a, const BigNum& b) {
    auto out = new BigNum;
    out->num.push_back(0);

    int zero_num = 0;
    for (auto iter = b.num.rbegin(); iter != b.num.rend(); iter++, zero_num++) {
        BigNum temp;
        temp.num = naive_mul(a.num, *iter, zero_num);
        cout << *out << " + " << temp;
        *out = *out + temp;
        cout << " = " << *out << endl;
    }

    if (a.isNegative == b.isNegative) {
        out->isNegative = false;
    } else {
        out->isNegative = true;
    }

    return *out;
}

int main() {
    BigNum a, b;
    cin >> a >> b;

    auto c = a * b;  // test

    cout << c;

    return 0;
}
