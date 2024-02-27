#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e4+10;
bool mem1;
int n,k,a[N],X[N],Y[N];
vector<int> f,g;
int rt[N],ls[N*20],rs[N*20],nd[N*20],tot;
int nnode(int x) { return tot++, ls[tot]=ls[x], rs[tot]=rs[x], nd[tot]=nd[x], tot; }
int nk[N],nb[N];
int y(int i,int x) {  return nk[i]*x+nb[i];  }
void Modify(int id,int l,int r,int i) {
    if(l==r) {
        if(y(i,l)<y(nd[id],l)) nd[id]=i;
        return;
    }
    int mid=(l+r)>>1;
    if(y(i,mid)<y(nd[id],mid)) swap(nd[id],i);
    if(y(i,l)<y(nd[id],l)) ls[id]=nnode(ls[id]), Modify(ls[id],l,mid,i);
    else rs[id]=nnode(rs[id]), Modify(rs[id],mid+1,r,i);
}
int Query(int id,int l,int r,int x) {
    int mid=(l+r)>>1, v=y(nd[id],x);
    if(!id||l==r) return v;
    if(x<=mid) return min(Query(ls[id],l,mid,x),v);
    else return min(Query(rs[id],mid+1,r,x),v);
}
struct St {
    deque<int> d;
    void merge(St &a) {
        if(a.d.size()<d.size()) {
            for(int i=a.d.size()-1;i>=0;i--) {
                int x=a.d[i];
                while(d.size()>1&&1ll*(Y[d[1]]-Y[d[0]])*(X[d[1]]-X[x])<=1ll*(Y[d[1]]-Y[x])*(X[d[1]]-X[d[0]])) d.pop_front();
                d.push_front(x);
            }
        }
        else {
            int i=a.d.size()-1;
            for(auto x:d) {
                while(i>=1&&1ll*(Y[a.d[i]]-Y[a.d[i-1]])*(X[x]-X[a.d[i-1]])>=1ll*(Y[x]-Y[a.d[i-1]])*(X[a.d[i]]-X[a.d[i-1]])) a.d.pop_back(), i--;
                a.d.push_back(x), i++;
            }
            swap(d,a.d);
        }
    }
    int qry(int k) {
        int l=0,r=d.size();
        while(l+1<r) {
            int mid=(l+r)>>1;
            if(1ll*k*(X[d[mid]]-X[d[mid-1]])>(Y[d[mid]]-Y[d[mid-1]])) l=mid;
            else r=mid;
        }
        // cout<<"qry "<<d[r]<<" "<<Y[d[r]]-k*X[d[r]]<<endl;
        return Y[d[l]]-k*X[d[l]];
    }
}tb[N];
int st[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    f.resize(n+2), g.resize(n+2);
    for(int i=1,v=0;i<=n;i++) v=max(v,a[i]), f[i+1]=1ll*v*i;
    nb[0]=2e9;
    for(int t=2;t<=k;t++) {
        swap(f,g);
        int top=0; tot=0;
        for(int i=t;i<=n;i++) {
            Y[i]=g[i], X[i]=i-1;
            tb[i].d.resize(1), tb[i].d[0]=i;
            while(top&&a[i]>=a[st[top]]) tb[i].merge(tb[st[top--]]);
            rt[i]=nnode(rt[st[top]]);
            st[++top]=i;
            nk[i]=a[i], nb[i]=tb[i].qry(a[i]);
            Modify(rt[i],1,n,i), f[i+1]=Query(rt[i],1,n,i);
            // cerr<<t<<" "<<i<<" "<<f[i+1]<<" "<<g[i]<<" "<<y(i,i)<<" "<<rt[st[top-1]]<<" "<<nb[i]<<" "<<X[i]<<" "<<Y[i]<<" "<<a[i]<<endl;
        }
    }
    cout<<f[n+1]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}