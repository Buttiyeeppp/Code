#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,m,a[N],X[N],tot,qcnt,ans[N];
namespace Bit {
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
}
using namespace Bit;
struct Option {
    int opt,x,y,k,id;
}op[N];
void sol(int st,int ed,int l,int r) {
    if(st>ed) return;
    if(l==r) {
        for(int i=st;i<=ed;i++) if(!op[i].opt)
            ans[op[i].id]=l;
        return;
    }
    vector<Option> lft,rig;
    int mid=(l+r)>>1;
    for(int i=st;i<=ed;i++) {
        Option now=op[i];
        if(!now.opt) {
            int v=Qry(now.y)-Qry(now.x-1);
            if(v<now.k) now.k-=v, rig.push_back(now);
            else lft.push_back(now);
        }
        else {
            if(now.y<=mid) Add(now.x,now.k), lft.push_back(now);
            else rig.push_back(now);
        }
    }
    for(Option i:lft) if(i.opt) Add(i.x,-i.k);
    for(int i=st,j=0;j<(int)lft.size();i++,j++) op[i]=lft[j];
    for(int i=st+lft.size(),j=0;j<(int)rig.size();i++,j++) op[i]=rig[j];
    sol(st,st+lft.size()-1,l,mid), sol(st+lft.size(),ed,mid+1,r);
}
int mcnt;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i], X[++tot]=a[i], op[++mcnt]={1,i,a[i],1,0};
    for(int i=1,x,y,k;i<=m;i++) {
        char ch; cin>>ch;
        if(ch=='Q') {
            cin>>x>>y>>k;
            op[++mcnt]={0,x,y,k,++qcnt};
        }
        else {
            cin>>x>>y;
            op[++mcnt]={1,x,a[x],-1,0};
            a[x]=y, X[++tot]=y;
            op[++mcnt]={1,x,a[x],+1,0};
        }
    }

    sort(X+1,X+tot+1);
    tot=unique(X+1,X+tot+1)-X-1;
    for(int i=1;i<=mcnt;i++) if(op[i].opt) op[i].y=lower_bound(X+1,X+tot+1,op[i].y)-X;

    sol(1,mcnt,1,tot);
    for(int i=1;i<=qcnt;i++) cout<<X[ans[i]]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}