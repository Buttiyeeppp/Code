#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=(5e5+10)*50;
bool mem1;
mt19937 rd(time(0));
int rt[N];
struct Fhqtreap {
    struct node {
        int ls,rs,val,rk,sz;
    }nd[N];
    void print(int x) {
        node p=nd[x];
        cout<<p.ls<<" "<<p.rs<<" "<<p.val<<" "<<p.rk<<" "<<p.sz<<endl;
    }
    int cnt;
    void pushup(int id) { nd[id].sz=nd[nd[id].ls].sz+nd[nd[id].rs].sz+1; }
    int newnode(int x) { return nd[++cnt]=(node){0,0,x,(int)rd(),1}, cnt; }
    int nnode(int x) { return nd[++cnt]=nd[x], cnt; }
    int merge(int x,int y) {
        if(!x||!y) return x+y;
        if(nd[x].rk<nd[y].rk) {
            int id=nnode(x);
            nd[id].rs=merge(nd[id].rs,y), pushup(id);
            return id;
        }
        else {
            int id=nnode(y);
            nd[id].ls=merge(x,nd[id].ls), pushup(id);
            return id;
        }
    }
    int merge(int x,int y,int z) { return merge(merge(x,y),z); }
    PII splitv(int id,int x) {
        if(!id) return {0,0};
        int p=nnode(id);
        if(nd[id].val<=x) {
            PII res=splitv(nd[p].rs,x);
            nd[p].rs=res.first, pushup(p);
            return {p,res.second};
        }
        else {
            PII res=splitv(nd[p].ls,x);
            nd[p].ls=res.second, pushup(p);
            return {res.first,p};
        }
    }
    void insert(int &id,int x) {
        PII res=splitv(id,x);
        id=merge(res.first,newnode(x),res.second);
    }
    void del(int &id,int x) {
        PII res1=splitv(id,x-1), res2=splitv(res1.second,x);
        res2.first=merge(nd[res2.first].ls,nd[res2.first].rs);
        id=merge(res1.first,res2.first,res2.second);
    }
    int qrk(int id,int x) {
        PII res=splitv(id,x-1);
        int ans=nd[res.first].sz+1;
        return ans;
    }
    int qkth(int id,int x) {
        if(!id) return -1;
        if(x<=nd[nd[id].ls].sz) return qkth(nd[id].ls,x);
        if(x==nd[nd[id].ls].sz+1) return nd[id].val;
        return qkth(nd[id].rs,x-nd[nd[id].ls].sz-1);
    }
    int qpre(int id,int x) { return qkth(id,qrk(id,x)-1); }
    int qsub(int id,int x) { return qkth(id,qrk(id,x+1)); }
}t;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    for(int i=1;i<=T;i++) {
        int v,op,x;
        cin>>v>>op>>x;
        if(v) rt[i]=t.nnode(rt[v]);
        if(op==1) t.insert(rt[i],x);
        if(op==2) t.del(rt[i],x);
        if(op==3) cout<<t.qrk(rt[i],x)<<endl;
        if(op==4) cout<<t.qkth(rt[i],x)<<endl;
        if(op==5) {
            int ans=t.qpre(rt[i],x);
            cout<<((~ans)? ans:-2147483647)<<endl;
        }
        if(op==6) {
            int ans=t.qsub(rt[i],x);
            cout<<((~ans)? ans:+2147483647)<<endl;
        }
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}