#include<bits/stdc++.h>
using namespace std;
const int N=3e2+10;
int n,m;
struct L {
	double p[N],P,a;
	bool operator<(const L &q)const
        { return P*n+(1.-P)*a+(1.-P)*q.P*n+(1.-P)*(1.-q.P)*q.a<
                 q.P*n+(1.-q.P)*q.a+(1.-q.P)*P*n+(1.-P)*(1.-q.P)*a; }
}l[N];
bool cmp(double x,double y) { return x<y; }
double f[N][N];
double r(double x) {
	int z=(int)(x*100000);
	if((int)(x*1000000)%10>=5) z++;
	return 1.0*z/100000;
}
int main() {
	// freopen("ex_kenkoooo2.in","r",stdin);
	freopen("kenkoooo.in","r",stdin);
	freopen("kenkoooo.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) l[i].P=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            scanf("%lf",&l[j].p[i]); l[j].p[i]/=100.0;
        }
    for(int i=1;i<=m;i++) {
        sort(l[i].p+1,l[i].p+n+1,cmp);
        l[i].P=1;
        for(int j=1;j<=n;j++) {
            l[i].a+=l[i].P*(1-l[i].p[j])*j;
            l[i].P*=l[i].p[j];
        }
        l[i].a/=1-l[i].P;
    }
    sort(l+1,l+m+1);
    double ans=0, pp=1;
    for(int i=1;i<=m;i++) {
        ans+=pp*l[i].P*n+pp*(1-l[i].P)*l[i].a;
        pp*=(1-l[i].P);
    }
    printf("%.5lf",ans);
	return 0;
}
/*
2 2
50 50
50 50

3 3 
96 4 70
25 50 16
84 43 28
*/