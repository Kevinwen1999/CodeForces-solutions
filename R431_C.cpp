#include <bits/stdc++.h>
#define ll long long
using namespace std;
int N;
ll sum(ll n) {
    return n * (n - 1) / 2LL;
}
int main() {
    cin>>N;
    if (N == 0)
        return cout<<"a"<<"\n", 0;
    for (int add = 0; add < 26; add++) {
        if (N == 0) break;
        ll l = 2, r = 100000;
        while (l <= r) {
            ll mid = (l + r) >> 1;
            if (sum(mid) <= N) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        N -= sum(r);
        char tmp = 'a' + add;
        for (int i = 0; i < r; i++)
            cout<<tmp;
    }
}
