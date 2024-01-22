#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,m,a[N],b[N];
struct Bit {
    ll v[N];
    int lowbit(int x) { return x&-x; }
    void Add(int x,ll val) {
        for(int i=x;i<N;i+=lowbit(i)) v[i]+=val;
    }
    ll Qry(int x) {
        ll res=0;
        for(int i=x;i;i-=lowbit(i)) res+=v[i];
        return res;
    }
}s1,s2;
bool mem2;
int main() {
    freopen("ex_saber1.in","r",stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) {
        b[i]=a[i]-a[i-1];
        if(b[i]<0) s1.Add(i,i-1), s2.Add(i,1);
    }
    for(int i=1,op,l,r,x;i<=m;i++) {
        cin>>op>>l>>r;
        if(op==1) {
            cin>>x;
            if(b[l]<0&&b[l]+x>=0) s1.Add(l,-(l-1)), s2.Add(l,-1);
            if(b[r+1]>=0&&b[r+1]-x<0) s1.Add(r+1,r), s2.Add(r+1,1);
            b[l]+=x, b[r+1]-=x;
        }
        else {
            cout<<s1.Qry(r)-s1.Qry(l)-(s2.Qry(r)-s2.Qry(l))*(l-1)<<endl;
        }
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}