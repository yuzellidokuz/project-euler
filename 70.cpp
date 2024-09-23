#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

//pretty straightforward implementation.
//runs in 4.4 seconds locally

typedef std::chrono::high_resolution_clock::time_point Time;
#define duration(a) std::chrono::duration_cast<std::chrono::microseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

vector<int> lp, pr;

void linear_sieve(int maxn){
    lp.resize(maxn + 1, 0);
    for(int i = 2; i <= maxn; i++){
        if(lp[i] == 0){
            lp[i] = i;
            pr.push_back(i);
        }
        for(int j = 0; i * pr[j] <= maxn; j++){
            lp[i * pr[j]] = pr[j];
            if(pr[j] == lp[i]){
                break;
            }
        }
    }
}

bool check(int x, int y){
    vector<int> a, b;
    while(x){
        a.push_back(x % 10);
        x /= 10;
    }
    while(y){
        b.push_back(y % 10);
        y /= 10;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

bool comp(pair<i64, i64> a, pair<i64, i64> b){
    return a.second * b.first < a.first * b.second;
}

void solve(){
    int n; cin >> n;
    Time t1 = timeNow();
    linear_sieve(n);
    int ans;
    pair<i64, i64> mn = {2e9, 1};
    for(int i = 2; i <= n; i++){
        set<int> prime;
        int x = i;
        while(x > 1){
            prime.insert(lp[x]);
            x /= lp[x];
        }
        i64 totient = i;
        for(i64 j : prime){
            totient /= j;
            totient *= j - 1;
        }
        if(comp(mn, {i, totient}) and check(i, totient)){
            ans = i, mn = {i, totient};
        }
    }
    cout << "ans: " << ans << "\n";
    cout << "Runtime: " << duration(timeNow() - t1) / 1000000.0 << " seconds.\n";
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t = 1; //cin >> t;
    while(t--){
        solve();
    }
}
