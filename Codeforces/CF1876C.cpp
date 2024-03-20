// LUOGU_RID: 151781547
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
int n,a[N],ind[N],col[N],vis[N],yp[N];
vector<int> nd;
void dfs(int x) {
    if(yp[x]) return;
    yp[x]=1;
    nd.push_back(x);
    dfs(a[x]);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        ind[a[i]]++;
    }
    // for(int i=1;i<=n;i++) if(i==a[i]) return cout<<-1<<endl, 0;
    queue<int> q;
    for(int i=1;i<=n;i++) if(!ind[i]) q.push(i);
    while(q.size()) {
        int x=q.front(); q.pop();
        int y=a[x]; vis[x]=1;
        if(!col[x]) col[y]=1;
        ind[y]--;
        if(!ind[y]) q.push(y);
    }
    for(int i=1;i<=n;i++) if(!vis[i]) {
        nd.clear(), dfs(i);
        int p=0;
        for(int i=0;i<(int)nd.size();i++) if(col[nd[i]]) p=i;
        if(nd.size()==1&&!col[nd[0]]) return cout<<-1<<endl, 0;
        for(int i=p,j=p+1;i<(int)nd.size();i++,j++) {
            if(j>=(int)nd.size()) j=0;
            if(j==p) {if(!col[nd[i]]&&!col[nd[j]]) return cout<<-1<<endl, 0;}
            if(!col[nd[i]]) col[nd[j]]=1;
        }
        for(int i=0,j=i+1;i<p;i++,j++) {
            if(j>=(int)nd.size()) j=0;
            if(j==p) {if(!col[nd[i]]&&!col[nd[j]]) return cout<<-1<<endl, 0;}
            if(!col[nd[i]]) col[nd[j]]=1;
        }
    }
    vector<int> ans;
    for(int i=1;i<=n;i++) if(!col[i]) ans.push_back(a[i]);
    cout<<ans.size()<<endl;
    for(auto i:ans) cout<<i<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}