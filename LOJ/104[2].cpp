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
mt19937 rd(time(0));
struct Fhqtreap {
    int ls[N],rs[N],val[N],rk[N],sz[N];
    int rt,cnt;
    void pushup(int id) { sz[id]=sz[ls[id]]+sz[rs[id]]+1; }
    int newnode(int x) { return cnt++, val[cnt]=x, rk[cnt]=rd(), sz[cnt]=1, cnt; }
    PII splitv(int id,int x) {
        if(!id) return {0,0};
        if(val[id]<=x) {
            PII res=splitv(rs[id],x);
            rs[id]=res.first, pushup(id);
            return {id,res.second};
        }
        else {
            PII res=splitv(ls[id],x);
            ls[id]=res.second, pushup(id);
            return {res.first,id};
        }
    }
    PII splitrk(int id,int x) {
        if(!id) return {0,0};
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
        if(rk[x]<rk[y]) {
            rs[x]=merge(rs[x],y), pushup(x);
            return x;
        }
        else {
            ls[y]=merge(x,ls[y]), pushup(y);
            return y;
        }
    }
    void insert(int x) {
        PII res=splitv(rt,x);
        rt=merge(merge(res.first,newnode(x)),res.second);
    }
    void del(int x) {
        PII res1=splitv(rt,x-1), res2=splitv(res1.second,x);
        int l=res1.first, mid=res2.first, r=res2.second;
        mid=merge(ls[mid],rs[mid]);
        rt=merge(merge(l,mid),r);
    }
    int qrk(int x) {
        PII res=splitv(rt,x-1);
        int ans=sz[res.first]+1;
        rt=merge(res.first,res.second);
        return ans;
    }
    int qkth(int x) {
        int id=rt;
        while(1) {
            if(x<=sz[ls[id]]) id=ls[id];
            else if(x==sz[ls[id]]+1) return val[id];
            else x-=sz[ls[id]]+1, id=rs[id];
        }
    }
    int _qkth(int x) {
        PII res1=splitrk(rt,x-1), res2=splitrk(res1.second,1);
        int ans=val[res2.first];
        merge(merge(res1.first,res2.first),res2.second);
        return ans;
    }
    int qpre(int x) {
        int id=rt, ans=0;
        while(id) {
            if(val[id]<x) ans=val[id], id=rs[id];
            else id=ls[id];
        }
        return ans;
    }
    int _qpre(int x) { return qkth(qrk(x)-1); }
    int qsub(int x) {
        int id=rt, ans=0;
        while(id) {
            if(val[id]>x) ans=val[id], id=ls[id];
            else id=rs[id];
        }
        return ans;
    }
    int _qsub(int x) { return qkth(qrk(x+1)); }
}t;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) {
        int op,x;
        cin>>op>>x;
        if(op==1) t.insert(x);
        if(op==2) t.del(x);
        if(op==3) cout<<t.qrk(x)<<endl;
        if(op==4) cout<<t._qkth(x)<<endl;
        if(op==5) cout<<t._qpre(x)<<endl;
        if(op==6) cout<<t._qsub(x)<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}