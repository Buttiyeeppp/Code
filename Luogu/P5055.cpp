#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#endif
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=(2e5)*200;
bool mem1;
mt19937 rd(20080618);
int rt[N];
struct Fhqtreap {
    struct node {
        int ls,rs,val,rk,sz,lz;
        ll sum;
    }nd[N];
    int newnode(int x) { return nd[++cnt]=(node){0,0,x,(int)rd(),1,0,x}, cnt; }
    int nnode(int x) { return nd[++cnt]=nd[x], cnt; }
    int cnt=0;
    void pushup(int x) { 
        nd[x].sz=nd[nd[x].ls].sz+nd[nd[x].rs].sz+1;
        nd[x].sum=nd[x].val+nd[nd[x].ls].sum+nd[nd[x].rs].sum;
    }
    int rev(int x) {
        int p=nnode(x);
        nd[p].lz^=1;
        swap(nd[p].ls,nd[p].rs);
        return p;
    }
    void pushdown(int id) {
        if(!nd[id].lz) return;
        nd[id].lz=0;
        if(nd[id].ls) nd[id].ls=rev(nd[id].ls);
        if(nd[id].rs) nd[id].rs=rev(nd[id].rs);
    }
    int merge(int x,int y) {
        if(!x||!y) return x+y;
        pushdown(x), pushdown(y);
        if(nd[x].rk<nd[y].rk) {
            int p=nnode(x);
            nd[p].rs=merge(nd[p].rs,y), pushup(p);
            return p;
        }
        else {
            int p=nnode(y);
            nd[p].ls=merge(x,nd[p].ls), pushup(p);
            return p;
        }
    }
    int merge(int x,int y,int z) { return merge(merge(x,y),z); }
    PII splitrk(int x,int v) {
        if(!x) return {0,0};
        pushdown(x);
        int p=nnode(x);
        if(v<=nd[nd[x].ls].sz) {
            PII res=splitrk(nd[x].ls,v);
            nd[p].ls=res.second, pushup(p);
            return {res.first,p};
        }
        if(v==nd[nd[x].ls].sz+1) {
            int rs=nd[p].rs; 
            nd[p].rs=0, pushup(p);
            return {p,rs};
        }
        PII res=splitrk(nd[x].rs,v-nd[nd[x].ls].sz-1);
        nd[p].rs=res.first, pushup(p);
        return {p,res.second};
    }
    void reverse(int &x,int l,int r) {
        PII res1=splitrk(x,l-1), res2=splitrk(res1.second,r-l+1);
        int p=rev(res2.first);
        x=merge(res1.first,p,res2.second);
    }
    void insert(int &x,int p,int v) {
        PII res=splitrk(x,p);
        x=merge(res.first,newnode(v),res.second);
    }
    void del(int &x,int p) {
        PII res1=splitrk(x,p-1), res2=splitrk(res1.second,1);
        x=merge(res1.first,res2.second);
    }
    ll qsum(int x,int l,int r) {
        PII res1=splitrk(x,l-1), res2=splitrk(res1.second,r-l+1);
        return nd[res2.first].sum;
    }
}t;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n; cin>>n;
    ll lst=0,v,op,a,b;
    for(int i=1;i<=n;i++) {
        cin>>v>>op>>a, a^=lst;
        if(op!=2) cin>>b, b^=lst;

        if(v) rt[i]=t.nnode(rt[v]);
        if(op==1) t.insert(rt[i],a,b);
        if(op==2) t.del(rt[i],a);
        if(op==3) t.reverse(rt[i],a,b);
        if(op==4) cout<<(lst=t.qsum(rt[i],a,b))<<endl; 
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}