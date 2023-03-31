#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=1e9+7;
const int N=4e3+10;
int n;
struct segment {
    int l,r;
    bool operator<(const segment &q)const {
        return r==q.r? l>q.l:r<q.r;
    }
}d[N];
ll f[N][N],s[N][N];
int lowbit(int x) { return x&-x; }
void Add(int i,int j,int val) { for(int x=j;x<N;x+=lowbit(x)) s[i][x]=(s[i][x]+val)%Mod; }
int Query(int i,int j) { ll sum=0; for(int x=j;x;x-=lowbit(x)) sum=(sum+s[i][x])%Mod; return sum; }
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&d[i].l,&d[i].r);
    sort(d+1,d+n+1);
    ll ans=n;
    for(int i=1;i<=n;i++) {
        f[i][0]=1;
        for(int j=1;j<i;j++) {
            if(d[i].l<=d[j].r&&d[j].l<d[i].l) f[i][j]=Query(j,d[i].l-1)+1;
            else if(d[i].l<=d[j].l&&d[i].r>=d[j].r) f[i][j]=Query(i,d[j].l-1)+1;
            f[i][j]%=Mod;
            Add(i,d[j].r,f[i][j]);
            ans=(ans+f[i][j])%Mod;
        }
    }
    printf("%lld",ans);
    return 0;
}