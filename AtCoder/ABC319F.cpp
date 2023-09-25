#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e3+10;
bool mem1;
int n,fa[N],t[N],vis[N],p[N];
ll s[N],g[N],f[N],mx;
vector<int> nd,eg[N];
void calc(int S) {
    priority_queue<PII,vector<PII>,greater<PII>> q;
    q.emplace(0,1);
    memset(vis,0,sizeof(vis));
    ll res=0;
    while(q.size()) {
        int u=q.top().second; q.pop();
        if(t[u]==1) {
            if(f[S]<s[u]) break;
            f[S]+=g[u], res+=g[u];
        }
        for(auto to:eg[u]) {
            if(t[to]==1) q.emplace(s[to],to);
            else if(!((1<<p[to])&S)) vis[p[to]]=1; 
            else q.emplace(0,to);
        }
    }
    if(f[S]>=mx) {
        cout<<"Yes"<<endl;
        exit(0);
    }
    for(int i=0;i<(int)nd.size();i++) if(vis[i])
        f[S|(1<<i)]=max(f[S|(1<<i)],f[S]*g[nd[i]]-res);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=2;i<=n;i++) {
        cin>>fa[i]>>t[i]>>s[i]>>g[i];
        eg[fa[i]].push_back(i);
        if(t[i]==2) p[i]=nd.size(), nd.push_back(i);
        else mx=max(mx,s[i]);
    }
    f[0]=1, calc(0);
    for(int i=0;i<(1<<nd.size());i++) calc(i);
    cout<<"No"<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}