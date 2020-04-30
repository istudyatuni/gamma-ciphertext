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
        }
    }
    void print(std::string a = "") {
        cout << "\nbegin text "<< a <<"\n";
        for (int i = 0; i < size; ++i) {
            cout << text[i] << ' ';
        }
        cout << "\nend text\n";
    }
    ullong get(int i) {
        if (i < size) {
            return text[i];
        }
        else return 0;
    }
    void set(ullong a, int i) {
        if (i < size) {
            text[i] = a;
        }
    }
    int getSize() {
        return size;
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
        Magma alg(key);
        for (int i = 0; i < text.getSize(); ++i) {
            iv = text.get(i) ^ alg.crypt(iv);
            text.set(iv, i);
        }
        return text;
    }
    Data& decrypt(Data& text, ullong iv) {
        Magma alg(key);
        ullong tmp;
        for (int i = 0; i < text.getSize(); ++i) {
            tmp = text.get(i);
            text.set(alg.crypt(iv) ^ tmp, i);
            iv = tmp;
        }
        return text;
    }
};

int main() {
    cout << std::hex;

    vector<ullong> t = {0xfedcba9876543210, 0xffeeddfa540a9988, 0x7766fcfdfeff554};
    Data testText(t, t.size());
    testText.print("original");
    int256 key(0xffeeddccbbaa9988, 0x7766554433221100, 0xf0f1f2f3f4f5f6f7, 0xf8f9fafbfcfdfeff);
    ullong iv = 0xff6554f5f6f78f9f;

    Gamma message(key);
    testText = message.encrypt(testText, iv);
    testText.print("encrypted");
    testText = message.decrypt(testText, iv);
    testText.print("decrypted");
    return 0;
}