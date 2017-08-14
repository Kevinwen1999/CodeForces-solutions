#include <bits/stdc++.h>
using namespace std;
int N, K;
int cnt[5];
int main() {
    cin>>N>>K;
    int num4 = N, num2 = 2 * N, num1 = 0;
    for (int i = 0, a; i < K; i++) {
        cin>>a;
        while(a >= 3) {
            if (num4) {
                a -= 4;
                num4--;
            } else if (num2) {
                a -= 2;
                num2--;
            } else
                return cout<<"NO\n", 0;
        }
        if (a)
            cnt[a]++;
    }
    while(cnt[2]) {
        if (num2) {
            num2--;
            cnt[2]--;
        } else if (num4){
            num4--;
            num1++;
            cnt[2]--;
        } else {
            cnt[2]--;
            cnt[1] += 2;
        }
    }
    if (cnt[1] > num4 * 2 + num2 + num1)
        return cout<<"NO\n", 0;
    cout<<"YES\n";
}
