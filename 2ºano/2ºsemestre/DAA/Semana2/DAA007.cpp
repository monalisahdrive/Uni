#include<iostream>
using namespace std;
int main() {
    int n, max = -2000, sum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        sum += value;
        if (max < sum) max = sum;
        if (sum < 0) sum = 0;
    }
    printf("%d\n", max);
     return 0;
}