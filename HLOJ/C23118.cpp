#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=7e5+10;
bool mem1;
int n,a[N],p[N];
int rt[N],s[N*23],ls[N*23],rs[N*23],tot;
void Modify(int &id1,int id2,int l,int r,int x) {
    if(!id1) id1=++tot;
    if(l==r) return s[id1]=s[id2]+1, void();
    int mid=(l+r)>>1;
    if(x<=mid) rs[id1]=rs[id2], Modify(ls[id1],ls[id2],l,mid,x);
    else ls[id1]=ls[id2], Modify(rs[id1],rs[id2],mid+1,r,x);
    s[id1]=s[ls[id1]]+s[rs[id1]];
}
int Query(int id1,int id2,int l,int r,int x,int y) {
    if(x<=l&&y>=r) return s[id2]-s[id1];
    int res=0, mid=(l+r)>>1;
    if(x<=mid) res+=Query(ls[id1],ls[id2],l,mid,x,y);
    if(y>mid) res+=Query(rs[id1],rs[id2],mid+1,r,x,y);
    return res;
}
int find(int id1,int id2,int l,int r,int v) {
    if(l==r) return l;
    int mid=(l+r)>>1;
    if(s[ls[id2]]-s[ls[id1]]<v) 
        return find(rs[id1],rs[id2],mid+1,r,v-(s[ls[id2]]-s[ls[id1]]));
    else return find(ls[id1],ls[id2],l,mid,v);
}
ll ans;
void sol(int x,int y) {
    ll cnt=y-x+1, gt=(cnt+1)/2;
    ans+=cnt;
    int l=find(rt[x-1],rt[y],1,n,gt);
    if(x<a[l]-1) sol(x,a[l]-1);
    if(a[l]+1<y) sol(a[l]+1,y);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i], p[a[i]]=i;
    for(int i=1;i<=n;i++) Modify(rt[i],rt[i-1],1,n,p[i]);
    sol(1,n);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}