#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e4+10;
bool mem1;
ll pri[N],d[N],mu[N],sd[N],smu[N];
vector<int> P;
void init() {
    mu[1]=1;
    for(int i=2;i<N;i++) {
        if(!pri[i]) mu[i]=-1, P.push_back(i);
        for(auto now:P) {
            if(1ll*now*i>=N) break;
            pri[now*i]=1;
            if(i%now==0) { mu[now*i]=0; break; }
            mu[now*i]=mu[i]*-1;
        }
    }
    for(int i=1;i<N;i++) {
        for(int v=i;v<N;v+=i) d[v]++;
    }
    for(int i=1;i<N;i++) {
        sd[i]=sd[i-1]+d[i];
        smu[i]=smu[i-1]+mu[i];
    }
}
void solve() {
    ll n,m; cin>>n>>m;
    ll res=0;
    for(ll l=1,r;l<=min(n,m);l=r+1) {
        r=min(n/(n/l),m/(m/l));
        res+=(smu[r]-smu[l-1])*sd[n/l]*sd[m/l];
    }
    cout<<res<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}