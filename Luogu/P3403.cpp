#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using ull=unsigned long long;
using PII=pair<int,int>;
using PLL=pair<ll,ll>;
const int N=1e5+10;
const ll INF=(1ull<<63)-1;
bool mem1;
ull h,a[4],f[N],vis[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>h>>a[1]>>a[2]>>a[3];
    h--;
    sort(a+1,a+3+1);
    for(int i=1;i<(int)a[1];i++) f[i]=INF;
    f[0]=0; priority_queue<PLL,vector<PLL>,greater<PLL>> q;
    q.emplace(0,0);
    while(q.size()) {
        int x=q.top().second; q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(int op=2;op<=3;op++) {
            if(f[(x+a[op])%a[1]]>f[x]+a[op]) 
                f[(x+a[op])%a[1]]=f[x]+a[op], q.emplace(f[(x+a[op])%a[1]],(x+a[op])%a[1]);
        }
    }
    ll ans=0;
    for(int i=0;i<(int)a[1];i++) if(f[i]<=h&&vis[i]) {
        ans+=(h-f[i])/a[1]+1;
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}