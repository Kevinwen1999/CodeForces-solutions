#include <bits/stdc++.h>
#define MAXN 300010
#define LG 20
#define SIGMA 2
using namespace std;

int ch[MAXN * LG][SIGMA];
int val[MAXN * LG];
int sz;
int x = 0;
void init_trie() {
    memset(ch, -1, sizeof ch);
    sz = 1;
}
void add(int u, int num, int pos) {
    if (pos < 0) {
        val[u] = 1;
        return;
    }
    int nx = (num >> pos) & 1;
    if (ch[u][nx] == -1)
        ch[u][nx] = sz++;
    add(ch[u][nx], num, pos - 1);
    val[u] = 0;
    for (int i = 0; i < 2; i++)
        if (ch[u][i] != -1)
            val[u] += val[ch[u][i]];
}
void getans(int u, int num, int pos, int &ans) {
    if (u == -1) {
        // set rest of bits to 0
        return;
    }
    int nx = (num >> pos) & 1; // prevent overflow
    if (val[ch[u][nx]] == (1 << pos))
        nx = 1 - nx;
    ans |= (nx ^ ((num >> pos) & 1)) << pos;
    getans(ch[u][nx], num, pos - 1, ans);
}
int N, M;
int main() {
    cin>>N>>M;
    init_trie();
    for (int i = 0, a; i < N; i++) {
        cin>>a;
        add(0, a, LG - 1);
    }
    for (int i = 0, a; i < M; i++) {
        cin>>a;
        x ^= a;
        a = 0;
        getans(0, x, LG - 1, a);
        cout<<a<<"\n";
    }
}
