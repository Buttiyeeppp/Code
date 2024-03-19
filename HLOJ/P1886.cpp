#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define fi first
#define se second
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,k,f[N],g[N];
ll Mod,a[N],c[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
unordered_map<int,int> mp,p;
vector<int> val;
bool mem2;
int main() {
    freopen("seq.in","r",stdin);
    freopen("seq.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k>>Mod;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) c[i]=Pow(a[i],Mod-2);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=min(3,n-i);j++) mp[a[j+i]*c[i]%Mod]++;
    }
    for(auto i:mp) if(i.se>=n/9) val.push_back(i.fi);
    // cerr<<val.size()<<endl;
    vector<int> ans;
    for(auto v:val) {
        ll inv=Pow(v,Mod-2);
        for(int i=1;i<=n;i++) f[i]=1, g[i]=0;
        for(int i=1;i<=n;i++) {
            int pos=p[a[i]*inv%Mod];
            if(pos) f[i]=f[pos]+1, g[i]=pos;
            p[a[i]]=i;
        }
        int jl=0;
        for(int i=1;i<=n;i++) if(f[i]>=k){
            if(!jl||f[i]>f[jl]) jl=i;
        }
        if(!jl) continue;
        k=f[jl], ans.clear();
        int pos=jl;
        while(pos) {
            ans.push_back(pos);
            pos=g[pos];
        }
    }
    if(ans.empty()) cout<<-1<<endl;
    else {
        cout<<k<<endl;
        reverse(ans.begin(),ans.end());
        // ll temp=a[ans[1]]*c[ans[0]]%Mod;
        // for(int i=2;i<k;i++) if(a[ans[i]]*c[ans[i-1]]%Mod!=temp) cout<<"Wrong!!!"<<endl;
        for(auto i:ans) cout<<a[i]<<" ";
        cout<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}