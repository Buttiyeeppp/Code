#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,a[N],X[N],tot;
struct Option {
    int opt,x,y,k;
}op[N];
const int M=N*200;
int rt[N],v[M],ls[M],rs[M],cnt;
void Modify(int &id,int l,int r,int x,int val) {
    if(!id) id=++cnt;
    if(l==r) return v[id]+=val, void();
    int mid=(l+r)>>1;
    if(x<=mid) Modify(ls[id],l,mid,x,val);
    else Modify(rs[id],mid+1,r,x,val);
    v[id]=v[ls[id]]+v[rs[id]];
}
int lowbit(int x) { return x&-x; }
void modify(int x,int val,int f) {
    for(int i=x;i<=n;i+=lowbit(i)) Modify(rt[i],1,tot,val,f);
}
vector<int> nd1,nd2;
int Query(int l,int r,int val) {
    if(l==r) return l;
    int sum=0,mid=(l+r)>>1;
    for(int i:nd1) sum-=v[ls[i]];
    for(int i:nd2) sum+=v[ls[i]];
    if(sum<val) {
        for(int i=0;i<(int)nd1.size();i++) nd1[i]=rs[nd1[i]];
        for(int i=0;i<(int)nd2.size();i++) nd2[i]=rs[nd2[i]];
        return Query(mid+1,r,val-sum);
    }
    else {
        for(int i=0;i<(int)nd1.size();i++) nd1[i]=ls[nd1[i]];
        for(int i=0;i<(int)nd2.size();i++) nd2[i]=ls[nd2[i]];
        return Query(l,mid,val);
    }
}
int query(int l,int r,int val) {
    nd1.clear(), nd2.clear();
    l--;
    for(int i=l;i;i-=lowbit(i)) nd1.push_back(rt[i]);
    for(int i=r;i;i-=lowbit(i)) nd2.push_back(rt[i]);
    return Query(1,tot,val);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i], X[++tot]=a[i];
    for(int i=1,x,y,k;i<=m;i++) {
        char ch; cin>>ch;
        if(ch=='Q') {
            cin>>x>>y>>k;
            op[i]={0,x,y,k};
        }
        else {
            cin>>x>>y;
            op[i]={1,x,y,0}, X[++tot]=y;
        }
    }

    sort(X+1,X+tot+1);
    tot=unique(X+1,X+tot+1)-X-1;
    for(int i=1;i<=n;i++) a[i]=lower_bound(X+1,X+tot+1,a[i])-X;
    for(int i=1;i<=m;i++) if(op[i].opt) op[i].y=lower_bound(X+1,X+tot+1,op[i].y)-X;

    for(int i=1;i<=n;i++) modify(i,a[i],1);
    for(int i=1;i<=m;i++) {
        Option now=op[i];
        if(!now.opt) {
            cout<<X[query(now.x,now.y,now.k)]<<endl;
        }
        else {
            modify(now.x,a[now.x],-1);
            a[now.x]=now.y;
            modify(now.x,a[now.x],+1);
        }
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}