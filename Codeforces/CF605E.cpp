#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,vis[N];
double e[N],s[N],p[N][N];
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) scanf("%lf",&p[i][j]), p[i][j]/=100.0;
    if(n==1) {puts("0"); return 0;}
    vis[n]=1, e[n]=0;
    for(int i=1;i<n;i++) e[i]=1, s[i]=1-p[i][n];
    while(1) {
        double mn=DBL_MAX; int u=-1;
        for(int i=1;i<=n;i++)
            if(!vis[i]&&e[i]/(1-s[i])<mn)
                mn=e[i]/(1-s[i]), u=i;
        vis[u]=1;
        if(u==1) {printf("%.8lf",e[u]/(1-s[u])); break;}
        for(int i=1;i<=n;i++) if(!vis[i])
            e[i]+=e[u]/(1-s[u])*p[i][u]*s[i], s[i]*=(1-p[i][u]);
    }
    return 0;
}