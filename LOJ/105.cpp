#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m;
mt19937 rd(20080618);
struct FhqTreap {
    int ls[N],rs[N],val[N],rk[N],sz[N],lz[N];
    int rt,st[N],top;
    void pushup(int id) { sz[id]=sz[ls[id]]+sz[rs[id]]+1; }
    void dfs(int id) {
        if(ls[id]) dfs(ls[id]);
        if(rs[id]) dfs(rs[id]);
        pushup(id);
    }
    void build() {
        for(int i=1;i<=n;i++) val[i]=i, rk[i]=rd();
        for(int i=1;i<=n;i++) {
            int p=0;
            while(top&&rk[st[top]]>rk[i]) p=st[top--];
            ls[i]=p;
            if(top) rs[st[top]]=i;
            st[++top]=i;
        }
        rt=st[1];
        dfs(rt);
    }
    void pushdown(int id) {
        if(!lz[id]) return;
        swap(ls[id],rs[id]);
        lz[ls[id]]^=1, lz[rs[id]]^=1, lz[id]=0;
    }
    PII splitrk(int id,int x) {
        if(!id) return {0,0};
        pushdown(id);
        if(x<=sz[ls[id]]) {
            PII res=splitrk(ls[id],x);
            ls[id]=res.second, pushup(id);
            return {res.first,id};
        }
        if(x==sz[ls[id]]+1) {
            int p=rs[id];
            rs[id]=0, pushup(id);
            return {id,p};
        }
        PII res=splitrk(rs[id],x-sz[ls[id]]-1);
        rs[id]=res.first, pushup(id);
        return {id,res.second};
    }
    int merge(int x,int y) {
        if(!x||!y) return x+y;
        pushdown(x), pushdown(y);
        if(rk[x]<rk[y]) {
            rs[x]=merge(rs[x],y), pushup(x);
            return x;
        }
        else {
            ls[y]=merge(x,ls[y]), pushup(y);
            return y;
        }
    }
    void reverse(int l,int r) {
        PII res1=splitrk(rt,l-1), res2=splitrk(res1.second,r-l+1);
        lz[res2.first]^=1;
        rt=merge(merge(res1.first,res2.first),res2.second);
    }
    void print(int id) {
        pushdown(id);
        if(ls[id]) print(ls[id]);
        cout<<val[id]<<" ";
        if(rs[id]) print(rs[id]);
    }
}t;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    t.build();
    for(int i=1,l,r;i<=m;i++) {
        cin>>l>>r;
        t.reverse(l,r);
    }
    t.print(t.rt), cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
