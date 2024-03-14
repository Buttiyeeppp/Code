#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
const int N=1e5+10;
const __int128 INF=(__int128)1<<121;
template<typename T=int> T read() {
    T x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') f*=-1; ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=x*10+ch-'0'; ch=getchar();
    }
    return f*x;
}
template<typename T> void write(T x) {
    if(x<0) putchar('-'), x=-x;
    if(x>=10) write(x/10), x%=10;
    putchar(x+'0');
}
int c,T,n,m,b[N];
int ch[N*122][2],tot;
ll sum[N*122];
__int128 k,a[N],mn[N*122];
int nnode() { return tot++, ch[tot][0]=ch[tot][1]=0, sum[tot]=0, mn[tot]=INF, tot; }
void insert(__int128 x,ll y) {
    int p=1;
    for(int i=k-1;i>=0;i--) {
        int v=((x&((__int128)1<<i))!=0);
        if(!ch[p][v]) ch[p][v]=nnode();
        p=ch[p][v], sum[p]+=y, mn[p]=min(mn[p],x);
    }
}
__int128 dfs(int p,__int128 ans,__int128 x,__int128 mnv,ll smv,__int128 val) {
    int ls=ch[p][0], rs=ch[p][1];
    if((!ls&&!rs)||!val) return min(mnv+x,ans+val*2-(val!=0));
    __int128 res=0;
    if(smv+sum[ls]<=m&&min(mnv,mn[ls])+x-val>=ans+val)
        res=max(res,dfs(rs,ans+val,x-val,min(mnv,mn[ls]),smv+sum[ls],val>>1));
    else res=max(res,dfs(rs,ans,x,mnv,smv,val>>1));

    if(smv+sum[rs]<=m&&min(mnv,mn[rs])+x>=ans+val)
        res=max(res,dfs(ls,ans+val,x,min(mnv,mn[rs]),smv+sum[rs],val>>1));
    else if(mnv+x-val>=ans) res=max(res,dfs(ls,ans,x-val,mnv,smv,val>>1));
    return res;
}
void solve() {
    n=read(), m=read(), k=read<__int128>();
    for(int i=1;i<=n;i++) a[i]=read<__int128>();
    __int128 smv=0, mnv=INF;
    for(int i=1;i<=n;i++) b[i]=read(), smv+=b[i], mnv=min(mnv,a[i]);
    if(smv<=m) return write(mnv+((__int128)1<<k)-1), putchar('\n'), void();
    if(!k) return putchar('0'), putchar('\n'), void();
    tot=0, nnode();
    for(int i=1;i<=n;i++) insert(a[i],b[i]);
    write(dfs(1,0,((__int128)1<<k)-1,INF,0,(__int128)1<<(k-1)));
    putchar('\n');
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    sum[0]=0, mn[0]=INF;
    c=read(), T=read();
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}