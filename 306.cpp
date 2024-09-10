#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

//runtime for 1e6 is approximately 2.3 hours locally.
//time complexity is O(n^2) (can it be improved further?)
//solved with sprague-grundy theorem (more information: https://cp-algorithms.com/game_theory/sprague-grundy-nim.html)

typedef std::chrono::high_resolution_clock::time_point Time;
#define duration(a) std::chrono::duration_cast<std::chrono::microseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

int mex(vector<int> &a){
    vector<bool> vis(*max_element(a.begin(), a.end()) + 1, false);
    for(int i : a){
        vis[i] = true;
    }
    int ans = 0;
    while(vis[ans]){
        ans++;
    }
    return ans;
}

void solve(){
    int n; cin >> n;
    Time t1 = timeNow();
    vector<int> gr(n + 1, -1);
    gr[0] = 0, gr[1] = 0;
    int ans = 0;
    for(int i = 2; i <= n; i++){
        vector<int> x;
        for(int j = i - 2; j >= 0; j--){
            x.push_back(gr[j] ^ gr[i - j - 2]);
        }
        gr[i] = mex(x);
        ans += gr[i] != 0;
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
