#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int phi[N],pri[N];
ll g[N];
vector<int> P;
void init() {
    phi[1]=1;
    for(int i=2;i<N;i++) {
        if(!pri[i]) phi[i]=i-1, P.push_back(i);
        for(auto now:P) {
            if(1ll*now*i>=N) break;
            pri[i*now]=1;
            if(i%now==0) {phi[i*now]=phi[i]*now; break;}
            phi[i*now]=phi[i]*(now-1);
        }
    }
    for(int d=1;d<N;d++) {
        for(int v=d;v<N;v+=d) {
            if(d==1) g[v]++;
            else g[v]+=1ll*phi[d]*d/2;
        }
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    int T; cin>>T;
    while(T--) {
        ll n; cin>>n;
        cout<<n*g[n]<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}