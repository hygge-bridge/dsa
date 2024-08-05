#include <iostream>
#include <string>
using namespace std;

// 字符串暴力匹配算法，未匹配返回-1
int Bf(const string& mainstr, const string& substr) {
    int i = 0;  // mainstr的索引
    int j = 0;  // substr的索引
    while (i < mainstr.size() && j < substr.size()) {
        if (mainstr[i] == substr[j]) {
            ++i;
            ++j;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= substr.size()) {
        return i - j;
    }
    else {
        return -1;
    }
}

int main() {
    string mainstr("helloworld");
    string substr("llo2");
    cout << Bf(mainstr, substr) << endl;;
    return 0;
}