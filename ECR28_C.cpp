#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define MMS(x, y) memset((x), (y), sizeof(x))
#define ll long long
#define vi vector <int>
#define pii pair <int, int>
#define EPS 1e-9

#define MAXN 100010

using namespace std;

ll pre[MAXN];
ll query(int l, int r) {
    return pre[r] - ((l - 1 >= 0) ? pre[l - 1] : 0);
}
ll check(int st, int ed, int& t) {
    ll mx = -INF;
    for (int mid = st; mid <= ed; mid++) {
        ll a1 = (mid == st) ? 0 : query(st, mid - 1);
        ll a2 = (mid == ed) ? 0 : - query(mid, ed - 1);
        if (a1 + a2 > mx) {
            mx = a1 + a2;
            t = mid;
        }
    }
    return mx;
}
int N;
int t1, t2;
int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> pre[i];
        if (i) pre[i] += pre[i - 1];
    }
    int i1, i2, i3;
    ll maxa = -INF;
    for (int i = 0; i <= N; i++) {
        ll a1 = check(0, i, t1);
        ll a2 = check(i, N, t2);
        if (maxa < a1 + a2) {
            maxa = a1 + a2;
            i1 = t1, i2 = i, i3 = t2;
        }
    }
    cout << i1 << " " << i2 << " " << i3;
}
