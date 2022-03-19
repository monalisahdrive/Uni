#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n; 
    int c = 0;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        if (p == 42) c++;
    }
    cout << c << endl;
    return 0;
}