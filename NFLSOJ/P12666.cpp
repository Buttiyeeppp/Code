#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e5+10;
bool memory1;
int n,sid,l[N],r[N],u[N],d[N];
struct BIT {
    ll v[N];
    void clear() { memset(v,0,sizeof(v)); }
    int lowbit(int x) { return x&-x; }
    void Add(int x,ll val) { if(!x) return; for(int i=x;i<N;i+=lowbit(i)) v[i]+=val; }
    ll Qry(int x) { ll res=0; for(int i=x;i;i-=lowbit(i)) res+=v[i]; return res; }
}bit;
namespace Sub1 {
    int cntl[N],cntr[N],cntu[N],cntd[N],deg[N];
    vector<int> vc1[N],vc2[N];
    ll sol() {
        for(int i=1;i<=n;i++) cntl[l[i]]++, cntr[r[i]]++, cntu[u[i]]++, cntd[d[i]]++;
        for(int i=2*n;i>=1;i--) cntl[i]+=cntl[i+1], cntu[i]+=cntu[i+1];
        for(int i=1;i<=2*n;i++) cntr[i]+=cntr[i-1], cntd[i]+=cntd[i-1];
        for(int i=1;i<=n;i++) {
            deg[i]=cntr[l[i]-1]+cntl[r[i]+1]+cntd[u[i]-1]+cntu[d[i]+1];
        }

        for(int i=1;i<=2*n;i++) vc1[i].clear(), vc2[i].clear();
        for(int i=1;i<=n;i++) vc1[l[i]].push_back(i), vc2[r[i]].push_back(i);

        bit.clear();
        for(int i=1;i<=2*n;i++) {
            for(auto j:vc1[i]) deg[j]-=bit.Qry(u[j]-1);
            for(auto j:vc2[i]) bit.Add(d[j],1);
        }
        bit.clear();
        for(int i=1;i<=2*n;i++) {
            for(auto j:vc1[i]) deg[j]-=bit.Qry((2*n-d[j]+1)-1);
            for(auto j:vc2[i]) bit.Add((2*n-u[j]+1),1);
        }
        bit.clear();
        for(int i=2*n;i>=1;i--) {
            for(auto j:vc2[i]) deg[j]-=bit.Qry(u[j]-1);
            for(auto j:vc1[i]) bit.Add(d[j],1);
        }
        bit.clear();
        for(int i=2*n;i>=1;i--) {
            for(auto j:vc2[i]) deg[j]-=bit.Qry((2*n-d[j]+1)-1);
            for(auto j:vc1[i]) bit.Add((2*n-u[j]+1),1);
        }

        ll res=0;
        for(int i=1;i<=n;i++) res+=1ll*deg[i]*(n-1-deg[i]);
        return res/2;
    }
}
struct SegmentTree {
    struct node {
        ll vl,vr,res;
        node operator+(const node &p) {
            return {vl+p.vl,vr+p.vr,res+p.res+vr*p.vl};
        }
    }nd[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    void Modify(int id,int l,int r,int x,int v,int f) {
        if(l==r) {
            (f? nd[id].vl:nd[id].vr)+=v;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) Modify(ls,l,mid,x,v,f);
        else Modify(rs,mid+1,r,x,v,f);
        nd[id]=nd[ls]+nd[rs];
    }
    node Query(int id,int l,int r,int x,int y) {
        if(x>y) return {0,0,0};
        if(x<=l&&y>=r) return nd[id];
        int mid=(l+r)>>1;
        if(y<=mid) return Query(ls,l,mid,x,y);
        if(x>mid) return Query(rs,mid+1,r,x,y);
        return Query(ls,l,mid,x,y)+Query(rs,mid+1,r,x,y);
    }
}sgt;
int X[N],Y[N],tot1,tot2;
namespace Sub2 {
    vector<PII> vc[N];
    ll sol() {
        for(int i=1;i<=n;i++)
            vc[l[i]].emplace_back(i,+1), vc[r[i]+1].emplace_back(i,-1);
        ll cnt=0,res=0;
        for(int i=1;i<=tot1;i++) {
            sort(vc[i].begin(),vc[i].end(),[](const PII &x,const PII &y) { return x.second<y.second; });
            for(auto now:vc[i]) {
                if(now.second==+1) {
                    ll v=cnt;
                    v-=sgt.Query(1,1,tot2,1,u[now.first]-1).vr+
                       sgt.Query(1,1,tot2,d[now.first]+1,tot2).vl;
                    res+=v*(v-1)/2;
                    res-=sgt.Query(1,1,tot2,u[now.first],d[now.first]).res;
                    // cerr<<"Cnt "<<i<<" "<<v<<endl;
                }
                cnt+=now.second;
                sgt.Modify(1,1,tot2,u[now.first],now.second,1);
                sgt.Modify(1,1,tot2,d[now.first],now.second,0);
            }
        }
        return res;
    }
}
bool memory2;
int main() {
    freopen("rect.in","r",stdin);
    freopen("rect.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>sid;
    for(int i=1;i<=n;i++)
        cin>>l[i]>>r[i]>>u[i]>>d[i], 
        X[++tot1]=l[i], X[++tot1]=r[i], Y[++tot2]=u[i], Y[++tot2]=d[i];

    sort(X+1,X+tot1+1), sort(Y+1,Y+tot2+1);
    tot1=unique(X+1,X+tot1+1)-X-1, tot2=unique(Y+1,Y+tot2+1)-Y-1;
    for(int i=1;i<=n;i++) {
        l[i]=lower_bound(X+1,X+tot1+1,l[i])-X;
        r[i]=lower_bound(X+1,X+tot1+1,r[i])-X;
        u[i]=lower_bound(Y+1,Y+tot2+1,u[i])-Y;
        d[i]=lower_bound(Y+1,Y+tot2+1,d[i])-Y;
        // cerr<<i<<" "<<l[i]<<" "<<r[i]<<" "<<u[i]<<" "<<d[i]<<endl;
    }

    ll ans=1ll*n*(n-1)*(n-2)/6, v1=Sub1::sol(), v2=Sub2::sol();
    ans-=v1+v2;

    // cerr<<"Sub1 "<<v1<<endl;
    // cout<<"Sub2 "<<v2<<endl;
    
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&memory1-&memory2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
/*
3 0
1 1 1 1
2 2 2 2 
3 3 3 3 
*/