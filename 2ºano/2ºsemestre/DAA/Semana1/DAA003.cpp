#include <iostream>
#include <string>
#include <ctype.h>
#include <cctype>
#include <cmath>
using namespace std;

int gen(string s) { // certo
    if (isalpha(s[0]) && isdigit(s[7])) return 1;
    if (isdigit(s[0]) && isalpha(s[7])) return 2;
    if (isdigit(s[0]) && isdigit(s[7])) return 3;
    return 4;
}

int convert(char c) {
    int r = c-'A';
    if (c > 'K') r--;
    if (c > 'W') r--;
    if (c > 'Y') r--;
    return r;
}

int result(string x, int gen_x) {
    int result = 0;
    if (gen_x == 1) result = convert(x[0])*23*10*10*10*10 + convert(x[1])*10*10*10*10 + (x[3]-'0')*10*10*10 + (x[4]-'0')*10*10 + (x[6]-'0')*10 + (x[7]-'0');
    else if (gen_x == 2) result = convert(x[6])*23*10*10*10*10 + convert(x[7])*10*10*10*10 + (x[0]-'0')*10*10*10 + (x[1]-'0')*10*10 + (x[3]-'0')*10 + (x[4]-'0') + 5290000;
    else if (gen_x == 3)  result = convert(x[3])*23*10*10*10*10 + convert(x[4])*10*10*10*10 + (x[0]-'0')*10*10*10 + (x[1]-'0')*10*10 + (x[6]-'0')*10 + (x[7]-'0') + 2*5290000;
    else result = x[4]-'0'+ (x[3]-'0')*10 + convert(x[7])*10*10 + convert(x[6])*23*10*10 + convert(x[1])*23*23*10*10 + convert(x[0])*23*23*23*10*10 + 3*5290000;
    return result;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        string x1, x2;
        cin >> x1 >> x2;
        cout << abs(result(x1, gen(x1))-result(x2, gen(x2))) << endl;
    }
}