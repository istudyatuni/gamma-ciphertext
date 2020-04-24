#include <vector>
#include <iostream>
#include "magma.h"
using std::vector;
using std::cout;
class Data {
    ullong *text;
    int size;
public:
    Data(const vector<ullong>& a, int size): size{static_cast<int>(size)} {
        text = new ullong[size];
        for (int i = 0; i < size; ++i) {
            text[i] = a[i];
            cout << text[i] << ' ';
        }
    }
    void print(std::string a = "") {
        cout << "\nbegin text "<< a <<"\n";
        for (int i = 0; i < size; ++i) {
            cout << text[i] << ' ';
        }
        cout << "\nend text\n";
    }
    ~Data() {
        delete[]text;
    }
    
};
class Gamma {
    int256 key;
public:
    Gamma(int256 key): key{key}{}
    Data& encrypt(Data& text, ullong iv) {
        Magma::setDecrypt();
        return text;
    }
};

int Magma::mode;
int main() {
    cout << std::hex;

    vector<ullong> t = {0xfedcba9876543210, 0xffeeddfa540a9988, 0x7766fcfdfeff554};
    Data testText(t, t.size());
    int256 key(0xffeeddccbbaa9988, 0x7766554433221100, 0xf0f1f2f3f4f5f6f7, 0xf8f9fafbfcfdfeff);
    ullong iv = 0xff6554f5f6f78f9f;

    Gamma message(key);
    testText = message.encrypt(testText, iv);
    testText.print("encrypted");
    return 0;
}