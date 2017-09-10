#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define MMS(x, y) memset((x), (y), sizeof(x))
#define ll long long
#define vi vector <int>
#define pii pair <int, int>
#define EPS 1e-9

#define MAXN 100010

using namespace std;

int N, K, M;

multiset <int> ms, lst;
int tot;
vi ones;
int main() {
    cin >> N >> K >> M;
    for (int i = 0, a; i < K; i++) {
        cin >> a;
        ms.insert(a);
        tot += a;
    }
    int maxa = 0;
    for (int com = 0; com <= N; com++) {
        if (com * tot > M) break;
        int ans = (com) * (K + 1);
        int n = N - com;
        lst.clear();
        for (int j = 0; j < n; j++) {
            for (int i : ms) {
                lst.insert(i);
            }
        }
        int r = M - com * tot;
        for (int i : lst) {
            if (!r) break;
            if (r < i) break;
            ans++, r -= i;
        }
        maxa = max(maxa, ans);
    }
    cout << maxa << "\n";
}
