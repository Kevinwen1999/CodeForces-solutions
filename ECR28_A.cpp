#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
#define MMS(x, y) memset((x), (y), sizeof(x))
#define ll long long
#define vi vector <int>
#define pii pair <int, int>
#define EPS 1e-9

#define MAXN 100010

using namespace std;

int N;
int A[MAXN];
int suf[MAXN];
int pre[MAXN];
vi ones;
int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        if (A[i]) ones.push_back(i);
        pre[i] = A[i] + pre[i - 1];
    }
    if (ones.empty() || ones.size() == N) {
        return cout << N, 0;
    }
    for (int i = N; i > 0; i--) {
        suf[i] = suf[i + 1] + A[i];
    }
    int maxa = max(ones.size(), N - ones.size());
    for (int i = 1; i <= N; i++) {
        maxa = max(maxa, i - 1 - pre[i - 1] + suf[i]);
    }
    cout << maxa << "\n";
}
