#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2.5e4+10;
bool mem1;
int n,k,a[N];
ll f[26][N];
struct Bit {
    int v[N];
    int lowbit(int x) { return x&-x; }
    void Add(int x,int val) {
        for(int i=x;i<=n;i+=lowbit(i)) v[i]+=val;
    }
    int Qry(int x) {
        int res=0;
        for(int i=x;i;i-=lowbit(i)) res+=v[i];
        return res;
    }
}t;
ll c;
int L=1,R=0;
void Add(int x,int op) {
    if(op) c+=t.Qry(a[x]-1);
    else c+=t.Qry(n)-t.Qry(a[x]);
    t.Add(a[x],+1);
}
void Del(int x,int op) {
    t.Add(a[x],-1);
    if(op) c-=t.Qry(a[x]-1);
    else c-=t.Qry(n)-t.Qry(a[x]);
}
void calc(int p,int l,int r,int x,int y) {
    int mid=(l+r)>>1,ap=x;
    while(R<mid) Add(++R,1);
    while(L>x+1) Add(--L,0);
    while(R>mid) Del(R--,1);
    while(L<x+1) Del(L++,0);
    ll mn=f[p-1][x]+c;
    // if(p==1) cout<<mid<<" "<<L<<" "<<R<<" "<<mn<<endl;
    for(int i=x+1;i<=min(y,mid-1);i++) {
        Del(L++,0);
        if(c+f[p-1][i]<mn) mn=c+f[p-1][i], ap=i;
    }
    f[p][mid]=mn;
    if(l<mid) calc(p,l,mid-1,x,ap);
    if(mid<r) calc(p,mid+1,r,ap,y);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    memset(f,0x3f,sizeof(f));
    f[0][0]=0;
    for(int i=1;i<=k;i++) calc(i,1,n,0,n);
    cout<<f[k][n]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}