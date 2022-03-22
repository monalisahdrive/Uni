#include <iostream>
using namespace std;
bool possible(int v[], int n, int x, int k) { //verificar
    int sum = 0, c = 1;
    for (int i = 0; i < n; i++) {
        if (v[i] > x) return false;
        sum += v[i];
        if (sum == x) {
            c += (i < n-1);
            sum = 0;
        } else if (sum > x) {
            c++; 
            sum = v[i];
        }
    }
    return c <= k;
}
int b_search(int v[], int n, int sum, int k) { //certo
    int low = v[0], high = sum, m;
    while (high > low) {
        m = low + (high - low) / 2;
        if (possible(v,n,m,k)) high = m;
        else low = m+1;
    }
    if(possible(v,n,min(low,min(high,m)),k)) return min(low,min(high,m));
    if (high != min(high,min(low,m)) && possible(v,n,high,k)) return high;
    if (low != min(low,min(high,m)) && possible(v,n,low,k)) return low;
    return m;
}
int main() {
    int n;
    scanf("%d", &n);
    int v[n], sum = 0, q, val;
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
        sum += v[i];
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &val);
        printf("%d\n",b_search(v,n,sum,val));
    }
    return 0;
}