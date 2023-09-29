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
int n,a[N],b[N],fa[N];
vector<int> nd[N];
void dfs(int x,int rt) {
    fa[x]=rt;
    if(!fa[b[x]]) dfs(b[x],rt);
}
int find(int x) {
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
int tp[N];
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) nd[i].clear(), fa[i]=tp[i]=0;
    for(int i=1;i<=n;i++) cin>>a[i] ,nd[a[i]].push_back(i);
    int tot=0,p;
    for(int i=1;i<=n;i++) if(nd[i].size()&1) tot++, p=i;
    if(tot>1||(!((n&1)&&tot==1)&&tot)) return cout<<"NO"<<endl, void();
    int m=1;
    for(int i=1;i<=n;i++) {
        for(int j=0;j+1<(int)nd[i].size();j+=2) 
            b[m]=nd[i][j], b[n-m+1]=nd[i][j+1], m++;
    }
    if(tot) b[m]=nd[p].back();
    for(int i=1;i<=n;i++) if(!fa[i]) dfs(i,i);
    for(int i=1;i<=n;i++)  {
        int v=a[b[i]];
        if(!tp[v]) { tp[v]=i; continue; }
        int f=find(i), tmpf=find(tp[v]);
        if(f!=tmpf) {
            swap(b[tp[v]],b[i]);
            fa[f]=tmpf;
        }
    }
    int ftmp=find(1);
    for(int i=2;i<n-i+1;i++) {
        int f=find(i);
        if(f!=ftmp) {
            int mem=b[1];
            b[1]=b[i], b[i]=b[n], b[n]=b[n-i+1], b[n-i+1]=mem;
            fa[f]=ftmp;
        }
    }
    for(int i=1;i<=n;i++) if(find(i)!=ftmp) return cout<<"No"<<endl, void();
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++) cout<<b[i]<<" ";
    cout<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}