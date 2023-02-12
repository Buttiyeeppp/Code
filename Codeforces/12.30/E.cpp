#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e4+10;
int n,m,x[20],p[N];
char c[20][N];
struct node {
    int id,a;
    bool operator<(const node &q)const {
        return a<q.a;
    }
}d[N];
void solve() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&x[i]);
    for(int i=1;i<=n;i++) scanf("%s",c[i]+1);
    ll ans=-1;
    for(int s=0;s<(1<<n);s++) {
        for(int i=1;i<=m;i++) d[i]=(node){i,0};
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=m;j++) {
                if(c[i][j]=='1') {
                    if((s>>(i-1))&1) d[j].a++;
                    else d[j].a--;
                }
            }
        }
        sort(d+1,d+m+1);
        ll sum=0;
        for(int i=1;i<=m;i++) sum+=d[i].a*i;
        for(int i=1;i<=n;i++) {
            if((s>>(i-1))&1) sum-=x[i];
            else sum+=x[i];
        }
        if(sum>ans) {
            ans=sum;
            for(int i=1;i<=m;i++) p[d[i].id]=i;
        }
    }
    for(int i=1;i<=m;i++) printf("%d ",p[i]);
    puts("");
    return;
}
int main() {
    int T; scanf("%d",&T);
    while(T--) solve();
    return 0;
}