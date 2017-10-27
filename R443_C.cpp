#include <bits/stdc++.h>
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define MMS(x, y) memset((x), (y), sizeof(x))
#define ll long long
#define vi vector <int>
#define pii pair <int, int>
#define EPS 1e-9
#define EPSS 1e-10

#define MAXN 1010
#define MAXL 5
#define SEGN 300030

using namespace std;
int N;
int n;
struct node{
    char op;
    int a;
};
vector <node> v;
int table[10][2];
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        char op; int a;
        scanf(" %c %d", &op, &a);
        v.push_back({op, a});
    }
    int nand = 1023, nor = 0, nxor = 0;
    for (int i = 0; i < 10; i++) {
        table[i][0] = 0, table[i][1] = 1;
        for (int j = 0; j < N; j++) {
            switch (v[j].op) {
                case '&': {
                    for (int k = 0; k < 2; k++) {
                        table[i][k] &= (v[j].a >> i) & 1;
                    }
                    break;
                }
                case '|': {
                    for (int k = 0; k < 2; k++) {
                        table[i][k] |= (v[j].a >> i) & 1;
                    }
                    break;
                }
                case '^': {
                    for (int k = 0; k < 2; k++) {
                        table[i][k] ^= (v[j].a >> i) & 1;
                    }
                    break;
                }
            }
        }
        if (table[i][0] == 0 && table[i][1] == 0) {
            nand ^= (1 << i);
        } else if (table[i][0] == 1 && table[i][1] == 1) {
            nor |= (1 << i);
        } else if (table[i][0] == 1 && table[i][1] == 0) {
            nxor |= (1 << i);
        }
    }
    cout << 3 << "\n";
    printf("& %d\n", nand);
    printf("| %d\n", nor);
    printf("^ %d\n", nxor);
}
