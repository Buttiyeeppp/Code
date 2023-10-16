#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e3+10;
bool mem1;
ll n,l[N],r[N],X[N],tot,dis[N],vis[N],len[N];
vector<PII> g[N];
bool check(int k) {
    for(int i=0;i<=tot;i++) g[i].clear();
    for(int i=1;i<=tot;i++) g[i].emplace_back(i-1,0), g[i-1].emplace_back(i,1);
    for(int i=1;i<=n;i++) {
        g[r[i]].emplace_back(l[i]-1,-1);
        g[l[i]-1].emplace_back(r[i],k);
    }
    queue<int> q;
    for(int i=0;i<=tot;i++) dis[i]=len[i]=0, vis[i]=1, q.push(i);
    while(q.size()) {
        int x=q.front(); q.pop();
        vis[x]=0;
        for(auto to:g[x]) {
            int y=to.first;
            if(dis[y]>dis[x]+to.second) {
                dis[y]=dis[x]+to.second, len[y]=len[x]+1;
                if(len[y]>tot) return false;
                if(!vis[y]) vis[y]=1, q.push(y);
            }
        }
    }
    return true;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>l[i]>>r[i];
        X[++tot]=l[i], X[++tot]=r[i];
    }
    sort(X+1,X+tot+1);
    tot=unique(X+1,X+tot+1)-X-1;
    for(int i=1;i<=n;i++)
        l[i]=lower_bound(X+1,X+tot+1,l[i])-X, r[i]=lower_bound(X+1,X+tot+1,r[i])-X;
    int l=0, r=tot+1;
    while(l+1<r) {
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid;
    }
    check(r);
    vector<ll> ans;
    for(int i=1;i<=tot;i++) if(dis[i]>dis[i-1]) {
        ans.push_back(X[i]);
    }
    cout<<ans.size()<<endl;
    for(auto i:ans) cout<<i<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}