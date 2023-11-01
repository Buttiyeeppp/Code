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
int n,m,vis[N],head[N],tot=1;
struct Edge {
    int nxt,to;
}eg[N<<1];
void Addedge(int x,int y) {
    eg[++tot]={head[x],y};
    head[x]=tot;
}
int fr[N];
void dfs(int x,int fromeg) {
    vis[x]=1;
    for(int i=head[x];i;i=eg[i].nxt) if((i^1)!=fromeg) {
        int y=eg[i].to;
        if(vis[y]) {
            vector<int> ans;
            int p=fr[x];
            if(x>n) ans.push_back(x);
            while(p!=fr[y]) { ans.push_back(p); p=fr[p]; }
            if(x<=n) ans.push_back(x);
            cout<<ans.size()/2<<endl;
            for(int i=(int)ans.size()-1;i>=0;i--) 
                cout<<((ans[i]>n)? ans[i]-n:ans[i])<<" ";
            cout<<endl;
            exit(0);
        }
        fr[y]=x, dfs(y,i);
    }
}
bool mem2;
int main() {
    // freopen("ex_graph1.in","r",stdin);
    freopen("graph.in","r",stdin);
    freopen("graph.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1,k;i<=m;i++) {
        cin>>k;
        for(int j=1,x;j<=k;j++) {
            cin>>x;
            Addedge(n+i,x), Addedge(x,n+i);
        }
    }
    for(int i=1;i<=n;i++) if(!vis[i]) dfs(i,0);
    cout<<-1<<endl;
 
    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
/*
2 3
2 1 2
2 1 2
2 1 2
*/