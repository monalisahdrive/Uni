#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
typedef struct Letter {
    char l;
    int f; //frequência
    int i; //índice para guardar a primeira ocorrência da letra
} L;
struct compareLetter {
    bool operator()(const L l1, const L l2) {
        if (l1.f > l2.f) return true;
        if (l1.f < l2.f) return false;
        return l1.i < l2.i;
    }
};
int main() {
    string t;
    cin >> t;
    int n = t.length();
    L frag[26] = {'0', 0, 0};
    for (int i = 0; i < n; i++) {
        char c = t[i];
        if (frag[c-'A'].f != 0) {
            frag[c-'A'].f++;
        } else {
            frag[c-'A'] = {c,1,i};
        }
    }
    sort(frag, frag+26, compareLetter());
    for (int i = 0; i < 26; i++) {
        if (frag[i].f != 0) printf("%c %d\n", frag[i].l, frag[i].f);
    }
    return 0;
}