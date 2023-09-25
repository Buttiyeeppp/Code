#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
// #define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
bool mem1;
int n,pd[2],mx,dep[N],p[N],col[N];
vector<int> g[N],nd[N];
void dfs(int x,int op) {
    mx=max(mx,dep[x]);
    nd[op].push_back(x);
    if(g[x].size()==1) pd[dep[x]&1]=1, p[op]=x, cerr<<x<<endl;
    for(auto y:g[x]) dep[y]=dep[x]+1, dfs(y,op);
}
void sol1() {
    cout<<1<<endl;
    for(int i=2;i<=n;i++) cout<<1<<" "; cout<<endl;
    int op,e;
    while(cin>>op) {
        if(op) break;
        cin>>e;
        cout<<1<<endl;
    }
}
void sol2() {
    cout<<2<<endl;
    // for(int i=2;i<=n;i++) cout<<(((dep[i]&1)==(dep[p]&1))? 1:2)<<" "; cout<<endl;
    for(auto to:g[1]) {
        for(auto now:nd[to]) col[now]=(((dep[now]&1)==(dep[p[to]]&1))? 1:2);
    }
    for(int i=2;i<=n;i++) cout<<col[i]<<" "; cout<<endl;
    int op,e1,e2;
    while(cin>>op) {
        if(op) break;
        cin>>e1>>e2;
        if(!e1) cout<<2<<endl;
        else if(!e2) cout<<1<<endl;
        else if(e1!=e2) {
            if(e1>e2) cout<<2<<endl;
            else cout<<1<<endl;
        }
        else {
            // if(pd[1]) cout<<2<<endl;
            // else cout<<1<<endl;
            cout<<1<<endl;
        }
    }
}
void sol3() {
    cout<<3<<endl;
    for(int i=2;i<=n;i++) cout<<(dep[i]-1)%3+1<<" "; cout<<endl;
    int op,e1,e2,e3;
    while(cin>>op) {
        if(op) break;
        cin>>e1>>e2>>e3;
        if(e1+e2+e3==1) {
            if(e1) cout<<1<<endl;
            if(e2) cout<<2<<endl;
            if(e3) cout<<3<<endl;
        }   
        else {
            if(!e1) cout<<2<<endl;
            if(!e2) cout<<3<<endl;
            if(!e3) cout<<1<<endl;
        }
    }
}
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) g[i].clear();
    for(int i=2,x;i<=n;i++) cin>>x, g[x].push_back(i);
    int yep=0;
    dep[1]=mx=0;
    for(auto to:g[1]) {
        memset(pd,0,sizeof(pd));
        p[to]=to, dep[to]=1;
        dfs(to,to);
        if(pd[0]&&pd[1]) yep=1;
    }
    if(mx==1) sol1();
    else if(yep) sol3();
    else sol2();
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T=1;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}