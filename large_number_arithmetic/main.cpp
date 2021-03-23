#include "big_num.h"

using namespace std;

int main() {
    BigNum input_a, input_b;
    cout << "Input number a: ";
    cin >> input_a;
    cout << "Input number b: ";
    cin >> input_b;

    cout << "a + b: " << input_a + input_b << endl <<
            "a - b: " << input_a - input_b << endl <<
            "a * b: " << input_a * input_b << endl <<
            "a / b: " << input_a / input_b << endl <<
            "a % b: " << input_a % input_b << endl;

    BigNum p, g, a, b;
    cout << "Input number p: ";
    cin >> p;
    cout << "Input number g: ";
    cin >> g;
    cout << "Input A's private key: ";
    cin >> a;
    cout << "Input B's private key: ";
    cin >> b;

    // auto p = 509_b;
    // auto g = 5_b;
    // int a = 123;
    auto A = 1_b;
    for (int i = 0; i < a; i++) {
        A = A * g;
    }
    A = A % p;
    cout << R"(A's private key: )" << A << endl;

    // int b = 456;
    auto B = 1_b;
    for (int i = 0; i < b; i++) {
        B = B * g;
    }
    B = B % p;
    cout << R"(B's private key: )" << B << endl;

    auto s = 1_b;
    for (int i = 0; i < b; i++) {
        s = s * A;
    }
    s = s % p;
    cout << "Session key: " << s << endl;

    return 0;
}
