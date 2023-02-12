#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=998244353;
const int N=1e3+10;
const int M=2e5+10;
int n,a[N][N];
vector<pair<int,int> > pos[M];
ll fac[N],inv[N],f[N][N];
ll Mul(ll x,ll y) {
    ll sum=1;
    while(y) {
        if(y&1) sum=sum*x%Mod;
        x=x*x%Mod;
        y>>=1;
    }
    return sum;
}
void init() {
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Mul(fac[N-1],Mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(ll x,ll y) {
    if(y==0||x==y) return 1;
    return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
int main() {
    freopen("path.in","r",stdin);
    freopen("path.out","w",stdout);
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",&a[i][j]), pos[a[i][j]].emplace_back(i,j);
    ll ans=0;
    for(int v=1;v<=n*n;v++) {
        if((int)pos[v].size()<=n) {
            for(int i=0;i<(int)pos[v].size();i++)
                for(int j=i;j<(int)pos[v].size();j++) {
                    int a=pos[v][j].first-pos[v][i].first, b=pos[v][j].second-pos[v][i].second;
                    if(a<0||b<0) continue;
                    ans=(ans+C(a+b,a))%Mod;
                }
        }
        else {
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++) {
                    f[i][j]=(f[i-1][j]+f[i][j-1]+(a[i][j]==v))%Mod;
                }
            for(int i=0;i<(int)pos[v].size();i++) 
                ans=(ans+f[pos[v][i].first][pos[v][i].second])%Mod;
        }
    }
    printf("%lld",ans);
    return 0;
}
