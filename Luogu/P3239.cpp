#include<bits/stdc++.h>
using namespace std;
#define ld long double
const int N=300;
int n,r,d[N];
ld a[N],f[N][N];
ld Mul(ld x,int y) {
    ld sum=1;
    while(y) {
        if(y&1) sum=sum*x;
        x=x*x, y>>=1;
    }
    return sum;
}
void solve() {
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;i++) scanf("%Lf%d",&a[i],&d[i]);
    memset(f,0,sizeof(f)), f[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=min(i,r);j++) f[i][j]=f[i-1][j]*Mul(1-a[i],r-j)+(j?f[i-1][j-1]*(1-Mul(1-a[i],r-j+1)):0);
    ld ans=0;
    for(int i=1;i<=n;i++) {
        ld p=0;
        for(int j=0;j<=min(i-1,r);j++) p+=f[i-1][j]*(1-Mul(1-a[i],r-j));
        ans+=p*d[i];
    }
    printf("%.11Lf\n",ans);
}
int main() {
    int T; scanf("%d",&T);
    while(T--) solve();
    return 0;
}