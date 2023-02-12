#include<bits/stdc++.h>
using namespace std;
#define double long double
const int N=70;
int n,m;
struct node {
    int a,b;
    double p;
}d[N];
double f[N][5007];
bool check(double x) {
    f[n][0]=0;
    for(int i=n-1;i>=0;i--) {
        for(int j=m+1;j<=5002;j++) f[i+1][j]=x;
        for(int j=0;j<=m;j++)
            f[i][j]=min(x,
                        (f[i+1][j+d[i+1].a]+d[i+1].a)*d[i+1].p+
                        (f[i+1][j+d[i+1].b]+d[i+1].b)*(1-d[i+1].p));
    }
    // printf("%.9Lf %.9Lf\n",f[0][0],x);
    return f[0][0]<x;
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {
        scanf("%d%d%Lf",&d[i].a,&d[i].b,&d[i].p);
        d[i].p/=100;
    }
    double l=0,r=1e9,eps=1e-12; int cnt=0;
    while(l+eps<r) {
        cnt++;
        if(cnt>100) break;
        double mid=(l+r)/2;
        if (check(mid)) r=mid;
        else l=mid;
    }
    if(check(r)) printf("%.9Lf",l);
    else printf("%.9Lf",r);
    return 0;
}