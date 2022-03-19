#include <iostream>
int main() {
    int n;
    scanf("%d", &n);
    int asum[n+1] = {0};
    for (int i = 1; i <= n; i++){
        int val;
        scanf("%d", &val);
        asum[i] = asum[i-1] + val;
    } 
    int f, a, b;
    scanf("%d", &f);
    for (int i = 0; i < f; i++) {
        scanf("%d %d", &a, &b);
        printf("%d\n", asum[b]-asum[a-1]);
    }
    return 0;
}
