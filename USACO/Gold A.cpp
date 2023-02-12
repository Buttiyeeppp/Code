#include<bits/stdc++.h>
using namespace std;
const int N=2e3+10;
int n,A,B;
struct who {
    int p,c,x;
    bool operator<(const who &q)const {
        return x<q.x;
    }
}d[N];
int f[N][N],g[N][N];
int main() {
    scanf("%d%d%d",&n,&A,&B);
    for(int i=1;i<=n;i++) scanf("%d%d%d",&d[i].p,&d[i].c,&d[i].x);
    sort(d+1,d+n+1);
    for(int i=1;i<=n;i++) {
        for(int j=0;j<=B;j++) {
            int k=max(d[i].c-((B-j)/d[i].x),0);
            g[i][k]=max(g[i][k],f[i-1][j]+d[i].p);
        }
        for(int j=B;j>=d[i].x*d[i].c;j--) f[i][j]=max(f[i][j],f[i-1][j-d[i].x*d[i].c]+d[i].p);
        for(int j=A;j>=d[i].c;j--) g[i][j]=max(g[i][j],g[i-1][j-d[i].c]+d[i].p);
    }
    printf("%d",g[n][A]);
    return 0;
}