#include <bits/stdc++.h>
#define MAXN 200010
using namespace std;
int N;
int A[MAXN], ans[MAXN];
vector <int> adj[MAXN];
vector <int> factor;
int cnt[MAXN];
int gcd(int a, int b) {
    return !b ? a : gcd(b, a % b);
}
void dfs1(int u, int pa) {
    for (int i : adj[u]) {
        if (i == pa) continue;
        ans[i] = gcd(ans[u], A[i]);
        dfs1(i, u);
    }
}
void dfs(int u, int pa, int dep) {
    for (int i : factor) {
        cnt[i] += (A[u] % i == 0);
        if (cnt[i] >= dep - 1)
            ans[u] = max(ans[u], i);
    }
    for (auto i : adj[u]) {
        if (i == pa) continue;
        dfs(i, u, dep + 1);
    }
    for (int i : factor) {
        cnt[i] -= (A[u] % i == 0);
    }
}
int main() {
    cin>>N;
    for (int i = 0; i < N; i++)
        cin>>A[i];
    for (int i = 0, a, b; i < N - 1; i++) {
        cin>>a>>b; a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= sqrt(A[0]); i++) {
        if (A[0] % i == 0) {
            factor.push_back(i);
            factor.push_back(A[0] / i);
            if (i * i == A[0])
                factor.pop_back();
        }
    }
    dfs1(0, -1);
    dfs(0, -1, 1);
    for (int i = 0; i < N; i++)
        cout<<ans[i]<<" ";
}
