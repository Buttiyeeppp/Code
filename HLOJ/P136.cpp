#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=3e2+10;
ll n,Mod,f[N][N],d[N],pw2[N*N];
void Add(ll &x,ll y) { x=(x+y>=Mod? x+y-Mod:x+y); }
void init() {
    pw2[0]=1; 
    for(int i=1;i<N*N;i++) pw2[i]=pw2[i-1]*2%Mod;
}
int main() {
    freopen("interval.in","r",stdin);
    freopen("interval.out","w",stdout);
    scanf("%lld%lld",&n,&Mod);
    init();
    f[0][0]=1;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=i;j++) {
            for(int k=0;k<i;k++) Add(f[i][j],f[k][j-1]*pw2[max(0,(i-k-1)*(i-k-2)/2)]%Mod);
        }
        d[i]=pw2[(i+1)*i/2];
        for(int j=1;j<i;j++) Add(d[i],(-f[i][j]*d[j]%Mod+Mod)%Mod);
    }
    printf("%lld",d[n]);
    return 0;
}