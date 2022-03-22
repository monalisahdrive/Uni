#include <iostream>
#include <algorithm>
using namespace std;
int v[1000], s[500000];

void sum_pairs(int n) {
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            s[k] = v[i]+v[j];
            k++;
        }
    }
}

void b_search(int low, int high, int key, int n) {
    while (low <= high) {
        int m = low + (high - low)/2;
        if (key == s[m]) {
            printf("%d\n", s[m]);
            return;
        }
        else if (key < s[m]) high = m-1;
        else low = m+1;
    }
    if (low == 0) printf("%d\n", s[0]);
    else if (high == n*(n-1)/2) printf("%d\n", s[n*(n-1)/2 - 1]);
    else if (s[low] - key == key - s[high]) printf("%d %d\n", s[high], s[low]);
    else if (s[low] - key < key - s[high]) printf("%d\n", s[low]);
    else printf("%d\n", s[high]);
}

int main() {
    int n;
    scanf("%d", &n); 
    for (int i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    sum_pairs(n);
    sort(s, s+(n*(n-1)/2));
    int q, key;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &key);
        b_search(0,n*(n-1)/2, key,n); 
    }
    return 0;
}