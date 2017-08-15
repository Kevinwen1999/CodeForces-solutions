#include <bits/stdc++.h>
#define MAXN 200010
#define MAXG 1000000
#define MOD 1000000007
#define ll long long
using namespace std;
int N;
ll a[MAXN];
ll F[MAXG + 1];
ll ans[MAXG + 1];
ll fast_exp(ll base, ll exp){
    base%=MOD;
    ll result = 1;
    while(exp>0){
        if (exp & 1){
            result = (result*base)%MOD;
        }
        base = (base*base)%MOD;
        exp>>=1;
    }
    return result;
}

void calc(int u) {
    ans[u] = (F[u] * (fast_exp(2, F[u] - 1)) % MOD);
    for (int i = 2; i * u <= MAXG; i++) {
        ans[u] -= ans[i * u];
        ans[u] %= MOD;
    }
}
int main() {
    cin>>N;
    for (int i = 0, in; i < N; i++) {
        cin>>in;
        for (int j = 1; j <= sqrt(in); j++) {
            if (in % j == 0) {
                F[j]++;
                if (j != sqrt(in)) {
                    F[in / j]++;
                }
            }
        }
    }
    ll fin = 0;
    for (int i = MAXG; i >= 2; i--) {
        calc(i);
        fin += (i * ans[i]) % MOD;
        fin %= MOD;
    }
    cout<<(fin + MOD) % MOD<<"\n";
}
