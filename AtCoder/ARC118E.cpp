#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e2+10;
const ll Mod=998244353;
bool mem1;
int n,m,x[N],X[N],Y[N];
ll f[N][N][N][2][2],fac[N];
void Add(ll &x,ll y) { x=(x+y>=Mod)? x+y-Mod:x+y; }
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    fac[0]=1, x[n+1]=-1;
    for(int i=1;i<=n;i++) {
        fac[i]=fac[i-1]*i%Mod;
        cin>>x[i];
        if(x[i]!=-1) X[i]=Y[x[i]]=1;
        else m++;
    }
    f[0][0][0][1][1]=1;
    for(int i=0;i<=n+1;i++)
        for(int j=0;j<=n+1;j++) {
            for(int k=0;k<=m;k++) {
                for(int a=0;a<=1;a++) for(int b=0;b<=1;b++) if(f[i][j][k][a][b]) {
                    ll v=f[i][j][k][a][b], nv=(Mod-v)%Mod;
                    if(j<n+1&&x[i]!=j+1) {
                        Add(f[i][j+1][k][a][Y[j+1]],v);
                        if(!a&&!Y[j+1]) Add(f[i][j+1][k+1][1][1],nv);
                    }
                    if(i<n+1&&x[i+1]!=j) {
                        Add(f[i+1][j][k][X[i+1]][b],v);
                        if(!X[i+1]&&!b) Add(f[i+1][j][k+1][1][1],nv);
                    }
                }
            }
        }
    ll ans=0;
    for(int k=0;k<=m;k++) Add(ans,f[n+1][n+1][k][0][0]*fac[m-k]%Mod);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}