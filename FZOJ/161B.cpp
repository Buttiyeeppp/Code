#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,B,a[N],b[N];
void solve() {
    cin>>n>>B;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    ll v=0,s=0,ans=0;
    priority_queue<int> q;
    for(int i=1;i<=n;i++) {
        s+=a[i];
        ans=max(ans,s+v);
        v+=b[i], s-=b[i], q.push(b[i]);
        while(s<0) {
            if(q.empty()) return cout<<ans<<endl, void();
            int val=q.top();
            s+=val-B, v-=val; q.pop();
        }
    }
    cout<<ans<<endl;
}
bool mem2;
int main() {
    freopen("piece.in","r",stdin);
    freopen("piece.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}