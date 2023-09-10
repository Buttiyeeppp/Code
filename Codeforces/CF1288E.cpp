#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=6e5+10;
bool mem1;
int n,m,p[N],s[N],l[N],r[N];
int lowbit(int x) { return x&-x; }
void Add(int x,int v) {
    for(int i=x;i<=n+m;i+=lowbit(i)) s[i]+=v;
}
int Qry(int x) {
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=s[i];
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) p[i]=i+m, Add(i+m,1), l[i]=r[i]=i;
    int now=m;
    for(int i=1,x;i<=m;i++) {
        cin>>x;
        l[x]=1, r[x]=max(r[x],Qry(p[x]));
        Add(p[x],-1), p[x]=now--, Add(p[x],1);
    }
    for(int i=1;i<=n;i++) r[i]=max(r[i],Qry(p[i]));
    for(int i=1;i<=n;i++) cout<<l[i]<<" "<<r[i]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}