#include <bits/stdc++.h>
#define MAXN 200010
#define ll long long
#define LG 30
#define SIGMA 2
#define ull unsigned long long
ull MOD = 1000000007;
using namespace std;

int ch[MAXN * LG][SIGMA];
int val[MAXN * LG];
int endu[MAXN * LG];
int cheapest[MAXN];
int recrd[MAXN];
vector <int> A;

int sz;

int cidx, ti, tj, xx;

void init_trie() {
	memset(ch, -1, sizeof ch);
	sz = 1;
}
void add(int u, int num, int pos) {
	if (pos < 0) {
		val[u] += 1;
		endu[u] = cidx;
		return;
	}
	int nx = (num >> pos) & 1;
	if (ch[u][nx] == -1) {
		ch[u][nx] = sz++;
	}
	add(ch[u][nx], num, pos - 1);
	val[u] = 0;
	for (int i = 0; i < SIGMA; i++) {
		if (~ch[u][i])
			val[u] += val[ch[u][i]];
	}
}
void del(int u, int num, int pos) {
	if (pos < 0) {
		val[u] -= 1;
		endu[u] = -1;
		return;
	}
	int nx = (num >> pos) & 1;
	del(ch[u][nx], num, pos - 1);
	val[u] = 0;
	for (int i = 0; i < SIGMA; i++) {
		if (~ch[u][i])
			val[u] += val[ch[u][i]];
	}
}
void findans(int u, int num, int pos) {
	if (pos < 0) {
        tj = endu[u];
		return;
	}
	int nx = (num >> pos) & 1;
	if (ch[u][nx] == -1 || val[ch[u][nx]] == 0)
		nx = 1 - nx;
	findans(ch[u][nx], num, pos - 1);
}
priority_queue <pair <int, pair <int, int>>> PQ;
void getans(int u) {
	cidx = u;
	findans(0, A[u], LG - 1);
	PQ.push({-(A[tj] ^ A[u]), {u, tj}});
}
vector <int> adj;
int N;
int visited[MAXN];
int main() {
	cin.sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> N;
	init_trie();
	A.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> A[i];
	}
	sort(A.begin(), A.end());
	A.erase(unique(A.begin(), A.end()), A.end());
	N = A.size();
	for (int i = 1; i < N; i++)
		cidx = i,
		add(0, A[i], LG - 1);
	int nt = N - 1;
	ull MSTweight = 0;
	getans(0);
	while (nt) {
		auto i = PQ.top();
		PQ.pop();
		int u = i.second.first, v = i.second.second;
		if (!visited[v]) {
			visited[v] = true;
			MSTweight -= i.first;
			nt--;
			cidx = v;
			del(0, A[v], LG - 1);
			getans(v);
		}
		getans(u);
	}
	cout << MSTweight << "\n";
}

