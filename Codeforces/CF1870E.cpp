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
int n,a[N],dp[N][N],vis[N],nxt[N][N],ap[N];
void calc(int i,int j) {
    vis[j]=1;
    for(int s=0;s<=n+1;s++) {
        if(nxt[i+1][s]<=n) dp[nxt[i+1][s]][s^j]=1;
    }
}
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++)
        for(int j=0;j<=n+1;j++) nxt[i][j]=INT_MAX;
    for(int i=1;i<=n;i++) {
        memset(ap,0,sizeof(ap));
        int val=0;
        for(int j=i;j<=n;j++) {
            ap[a[j]]=1;
            while(ap[val]) val++;
            nxt[i][val]=min(nxt[i][val],j);
        }
    }
    for(int i=n-1;i>=1;i--)
        for(int v=0;v<=n+1;v++) nxt[i][v]=min(nxt[i+1][v],nxt[i][v]);
    memset(vis,0,sizeof(vis));
    for(int i=0;i<=n;i++)
        for(int v=0;v<=n+1;v++) dp[i][v]=0;
    dp[0][0]=1;
    for(int i=0;i<=n;i++)
        for(int v=0;v<=n+1;v++) if(!vis[v]&&dp[i][v]) calc(i,v);
    for(int v=n+1;v>=0;v--) if(vis[v]) return cout<<v<<endl, void();
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
/*
1
10
2 1 0 7 1 2 0 2 4 3
*/