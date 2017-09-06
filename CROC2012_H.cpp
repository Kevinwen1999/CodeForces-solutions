#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define MAXN 5005
#define prm 307
using namespace std;
ll x, y, d;
ll f1[MAXN], f2[MAXN];
ll prex[MAXN];
ll e[MAXN];
int N;
void extendedeuclid(ll a, ll b, ll &x, ll &y, ll &d) {
    if (!b) {x = 1; y = 0; d = a; return;}
    extendedeuclid(b, a % b, x, y, d);
    ll x1 = y;
    ll y1 = x - (a/b)*y;
    x = x1;
    y = y1;
}
void precalc_exponents() {
    prex[0] = 1;
    extendedeuclid(MOD, 1, x, y, d);
    e[0] = y;
    for (int i = 1; i < MAXN; i++) {
        prex[i] = (prex[i - 1] * prm) % MOD;
        extendedeuclid(MOD, prex[i] % MOD, x, y, d);
        e[i] = y;
    }
}
void hash_string(string& in, ll F[], int p) {
    for (int i = 0; i < in.size(); i++) {
        F[i] = (((in[i] - 'a') % MOD) * (prex[i] % MOD)) % MOD;
        if (i) F[i] = (F[i] + F[i - 1]) % MOD;
    }
}
ll query_hash(ll F[], int p, int i, int j) {
    ll val = F[j] - (i ? F[i - 1] : 0);
    val %= MOD;
    y = e[i];
    y %= MOD;
    val = (val * y) % MOD;
    return (val + MOD) % MOD;
}
void init(string& in) {
    hash_string(in, f1, prm);
    reverse(in.begin(), in.end());
    hash_string(in, f2, prm);
}
bool ispalindrome(int i, int j) {
    return query_hash(f1, prm, i, j) == query_hash(f2, prm, N - 1 - j, N - 1 - i);
}
ll dp[MAXN][MAXN];
bool ispa[MAXN][MAXN];
void calc() {
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
            ispa[i][j] = ispalindrome(i, j);
    for (int i = 0; i < N; i++)
        dp[i][i] = 1;
    for (int len = 2; len <= N; len++) {
        for (int i = 0; i + len - 1 < N; i++) {
            int j = i + len - 1;
            dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - dp[i + 1][j - 1] + ispa[i][j];
        }
    }
}
int main() {
    precalc_exponents();
    string in; cin>>in;
    N = in.size();
    init(in);
    calc();
    int Q;
    scanf("%d", &Q);
    while(Q--) {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%lld\n", dp[--a][--b]);
    }
}
