#include <iostream>
using namespace std;

int sum_digits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n%10;
        n /= 10;
    }
    return sum;
}

int main() {
    int t;
    cin >> t; 
    int n, k;
    for (int i = 0; i < t; i++) {
        cin >> n >> k; 
        if (sum_digits(n) == k) n++;
        while (sum_digits(n) != k) n++;
        cout << n << endl;
    }
    return 0;
}