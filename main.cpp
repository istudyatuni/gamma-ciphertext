#include <iostream>
#include "magma.h"
using namespace std;

class Gamma {
public:
    Gamma();
    ~Gamma();
};
int Magma::mode = 0;

int main() {
    Magma::setDecrypt();
    cout << hex;
    int256 key(0xffeeddccbbaa9988, 0x7766554433221100, 0xf0f1f2f3f4f5f6f7, 0xf8f9fafbfcfdfeff);
    Magma a(key);
    ullong text = 0xfedcba9876543210;
    ullong message = a.encrypt(text);
    cout << "\nciphertext = " << message << endl;
    message = a.decrypt(message);
    cout << "\nmessage = " << message;
    cout << "\noriginal = " << text;
    return 0;
}
