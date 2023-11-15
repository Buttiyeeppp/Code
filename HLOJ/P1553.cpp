#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
string s;
int n,a[N],nxt[N],ed[N],f[N];
int ch[N][30],tot,fa[N][20];
const ll Mod[2]={1000000007,998244353};
const ll P=1331;
ll fac[2][N][20],Pow[2][N];
void init() {
    for(int k=0;k<2;k++) {
        Pow[k][0]=1;
        for(int i=1;i<N;i++) Pow[k][i]=Pow[k][i-1]*P%Mod[k];
    }
}
void build(int x) {
    for(int j=1;j<20;j++)
        fa[x][j]=fa[fa[x][j-1]][j-1],
        fac[0][x][j]=(fac[0][x][j-1]*Pow[0][1<<(j-1)]+fac[0][fa[x][j-1]][j-1])%Mod[0],
        fac[1][x][j]=(fac[1][x][j-1]*Pow[1][1<<(j-1)]+fac[1][fa[x][j-1]][j-1])%Mod[1];
}
void out(int x) {
    while(x) {
        cout<<((fac[0][x][0]==1)? '(':')');
        x=fa[x][0];
    }
    cout<<endl;
}
int comp(int x,int y) {
    for(int j=19;j>=0;j--) if(fa[x][j]&&fa[y][j]) {
        if(fac[0][x][j]==fac[0][y][j]&&fac[1][x][j]==fac[1][y][j]) x=fa[x][j], y=fa[y][j];
    }
    if(x&&y&&fac[0][x][0]==fac[0][y][0]&&fac[1][x][0]==fac[1][y][0]) x=fa[x][0], y=fa[y][0];
    // cout<<x<<" "<<y<<" "<<fac[x][0]<<" "<<fac[y][0]<<endl;
    if(!x||!y) return (!x);
    return (fac[0][x][0]<fac[0][y][0]);
}
bool mem2;
int main() {
    freopen("kacbret.in","r",stdin);
    freopen("kacbret.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>s;
    n=s.size(); s=" "+s;
    for(int i=1;i<=n;i++) a[i]=(s[i]=='(')? 1:2;
    for(int i=n;i>=1;i--) if(s[i]=='(') {
        // int p=i;
        // while(p&&p<n&&s[p+1]=='(') p=nxt[p+1];
        // nxt[i]=p+1;
        if(i<n&&s[i+1]==')') nxt[i]=i+1;
        else nxt[i]=ed[i+1];
        if(nxt[i]<n) {
            if(s[nxt[i]+1]=='(') ed[i]=ed[nxt[i]+1];
            else ed[i]=(nxt[i]? nxt[i]+1:0);
        }
        // cerr<<i<<" "<<nxt[i]<<endl;
    }
    init();
    for(int i=n;i>=1;i--) {
        if(!ch[f[i+1]][a[i]]) 
            ch[f[i+1]][a[i]]=++tot, fa[tot][0]=f[i+1], 
            fac[0][tot][0]=fac[1][tot][0]=a[i], build(tot);
        f[i]=ch[f[i+1]][a[i]]; 
        if(nxt[i]&&comp(f[nxt[i]+1],f[i])) f[i]=f[nxt[i]+1];
        // cout<<i<<" "<<nxt[i]+1<<" "; out(f[i]);
    }
    out(f[1]);

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}