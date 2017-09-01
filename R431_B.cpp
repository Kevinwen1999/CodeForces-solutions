#include <bits/stdc++.h>
#define ll long long
#define MAXN 1010
#define INF 0x3f3f3f3f
using namespace std;
int N;
ll  A[MAXN];
vector <pair <int, ll> > points, other;
unordered_map <double, vector <pair <int, ll> > > um;
double slp(pair<int, ll> &a, pair<int, ll> &b) {
    double ans = (double)(b.second - a.second) / (double) (b.first - a.first);
    return ans;
}
double checkother() {
    double S = INF;
    for (int i = 1; i < other.size(); i++) {
        if (S == INF) {
            S = slp(other[i], other[0]);
        } else if (slp(other[i], other[0]) != S)
            return INF;
    }
    return S;
}
bool check (double S) {
    other.clear();
    for (int i = 1; i < N; i++) {
        if (slp(points[i], points[0]) != S)
            other.push_back(points[i]);
    }
    if (other.size() == 1) return true;
    return checkother() == S;
}
int main() {
    cin>>N;
    for (int i = 1; i <= N; i++) {
        cin>>A[i];
        points.push_back({i, A[i]});
        if (points.size() > 1) other.push_back(points.back());
    }
    double tmp = checkother();
    if (tmp == slp(points[1], points[0]))
        return cout<<"No", 0;
    else if (tmp != INF)
        return cout<<"Yes", 0;
    for (int i = 1; i < N; i++) {
        if (check(slp(points[i], points[0]))) {
            return cout<<"Yes", 0;
        }
    }
    return cout<<"No", 0;
}
