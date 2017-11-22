#include <bits/stdc++.h>
#define MAXN 500010
#define ll long long
using namespace std;

int p[MAXN], tp[MAXN], rem[MAXN], cycle;

int findp(int x, int op) {
    if (op) {
        if (rem[x] != cycle) {
            rem[x] = cycle;
            tp[x] = p[x];
        }
        return tp[x] == x ? x : tp[x] = findp(tp[x], 1);
    }
    return p[x] == x ? x : p[x] = findp(p[x], 0);
}
void mergeset(int x, int y, int op) {
	if (op) {
    	x = findp(x, 1), y = findp(y, 1);
		tp[x] = y;
		return;
	}
    x = findp(x, 0), y = findp(y, 0);
    p[x] = y;
}
struct edge {
    int u, v, w;
};
vector <edge> edgelist, weight[MAXN];
vector <pair <int, int>> query[MAXN];
bool possible[MAXN];
int N, M, Q;
int maxW = -1;
int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);
    cin >> N >> M;
    for (int i = 0, a, b, c; i < M; i++) {
        cin >> a >> b >> c;
        edgelist.push_back((edge){a, b, c});
        weight[c].push_back((edge){a, b, i});
        maxW = max(maxW, c);
    }
    cin >> Q;
    for (int i = 0, n; i < Q; i++) {
        cin >> n;
        for (int j = 0, a; j < n; j++) {
            cin >> a; a--;
            query[edgelist[a].w].push_back({i, a});
        }
    }
    for (int i = 0; i <= N; i++)
        p[i] = i, tp[i] = i;
	for (int w = 1; w <= maxW; w++) {
		for (int i = 0; i < query[w].size(); i++) {
			// Record state before adding edge
			auto x = edgelist[query[w][i].second];
			findp(x.u, 0);
			findp(x.v, 0);
		}
		sort(query[w].begin(), query[w].end());
		for (int i = 0; i < query[w].size(); i++) {
			if (!i || query[w][i].first != query[w][i - 1].first) {
				// If query changed, revert all merge operation
				cycle++;
			}	
			auto x = edgelist[query[w][i].second];
			if (findp(x.u, 1) == findp(x.v, 1)) {
				possible[query[w][i].first] = true; continue;
			}
			mergeset(x.u, x.v, 1);
		}
		for (auto i : weight[w]) {
			mergeset(i.u, i.v, 0);
		}
	}
	for (int i = 0; i < Q; i++) {
		possible[i] ? printf("NO\n") : printf("YES\n");
	}
}
