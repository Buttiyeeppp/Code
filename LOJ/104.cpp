#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
mt19937 rd(time(0));
struct Treap {
    int ls[N],rs[N],val[N],rk[N],w[N],sz[N];
    int ans,tot,rt;
    void pushup(int id) { sz[id]=w[id]+sz[ls[id]]+sz[rs[id]]; }
    void lrotate(int &id) {
        int t=rs[id];
        rs[id]=ls[t], ls[t]=id;
        pushup(id), pushup(t);
        id=t;
    }
    void rrotate(int &id) {
        int t=ls[id];
        ls[id]=rs[t], rs[t]=id;
        pushup(id), pushup(t);
        id=t;
    }
    void insert(int &id,int x) {
        if(!id) {
            id=++tot;
            ls[id]=rs[id]=0;
            val[id]=x;
            rk[id]=rd();
            w[id]=sz[id]=1;
            return;
        }
        sz[id]++;
        if(val[id]==x) return w[id]++, void();
        if(val[id]<x) {
            insert(rs[id],x);
            if(rk[id]>rk[rs[id]]) lrotate(id);
        }
        else {
            insert(ls[id],x);
            if(rk[id]>rk[ls[id]]) rrotate(id);
        }
    }
    bool del(int &id,int x) {
        if(!id) return false;
        if(val[id]==x) {
            if(w[id]>1) return w[id]--, sz[id]--, true;
            if(!ls[id]||!rs[id]) return id=ls[id]+rs[id], true;
            if(rk[ls[id]]<rk[rs[id]]) {
                rrotate(id);
                return del(id,x);
            }
            else {
                lrotate(id);
                return del(id,x);
            }
        }
        if(val[id]<x) {
            if(del(rs[id],x)) return sz[id]--, true;
            return false;
        }
        else {
            if(del(ls[id],x)) return sz[id]--, true;
            return false;
        }
    }
    int qrk(int id,int x) {
        if(!id) return 0;
        if(val[id]==x) return sz[ls[id]]+1;
        if(val[id]<x) return sz[ls[id]]+w[id]+qrk(rs[id],x);
        else return qrk(ls[id],x);
    }
    int qnum(int id,int x) {
        if(!id) return 0;
        if(x<=sz[ls[id]]) return qnum(ls[id],x);
        if(w[id]+sz[ls[id]]<x) return qnum(rs[id],x-w[id]-sz[ls[id]]);
        return val[id];
    }
    void qpre(int id,int x) {
        if(!id) return;
        if(val[id]<x) ans=val[id], qpre(rs[id],x);
        else qpre(ls[id],x);
    }
    void qsub(int id,int x) {
        if(!id) return;
        if(val[id]>x) ans=val[id], qsub(ls[id],x);
        else qsub(rs[id],x);
    }
    void insert(int x) { insert(rt,x); }
    void del(int x) { del(rt,x); }
    int qrk(int x) { return qrk(rt,x); }
    int qnum(int x) { return qnum(rt,x); }
    int qpre(int x) { ans=0; qpre(rt,x); return ans; }
    int qsub(int x) { ans=0; qsub(rt,x); return ans; }
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
        if(op==4) cout<<t.qnum(x)<<endl;
        if(op==5) cout<<t.qpre(x)<<endl;
        if(op==6) cout<<t.qsub(x)<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}