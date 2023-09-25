#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,mx1[N][20],mx2[N],now[5],Log[N];
ll h[N],a[N],x,ans[N];
ll calc(int i) { return h[i]*(a[i]/x+(a[i]%x!=0)); }
bool cmp(int q,int p) {
    return h[q]*(a[q]/x+(a[q]%x!=0))>h[p]*(a[p]/x+(a[p]%x!=0));
}
bool h_cmp(int q,int p) { return h[q]>h[p]; }
int mx_Query(int l,int r) {
    int len=Log[r-l+1];
    return (h_cmp(mx1[l][len],mx1[r-(1<<len)+1][len]))? mx1[l][len]:mx1[r-(1<<len)+1][len];
}
PII Query(int l,int r) {
    int res1=mx_Query(l,r);
    if(!res1) return {0,0};
    int res2=mx2[a[res1]],mem=0;
    if(l<a[res1]&&h_cmp(mem=mx_Query(l,a[res1]-1),res2))  res2=mem;
    if(a[res1]<r&&h_cmp(mem=mx_Query(a[res1]+1,r),res2))  res2=mem;
    return {res1,res2};
}
void self_sort() {
    ll c[5];
    for(int i=1;i<=4;i++) c[i]=calc(now[i]);
    if(c[3]>c[1]) now[2]=now[1], c[2]=c[1], now[1]=now[3], c[1]=c[3];
    else if(c[3]>c[2]) now[2]=now[3], c[2]=c[3];
    if(c[4]>c[1]) now[2]=now[1], c[2]=c[1], now[1]=now[4], c[1]=c[4];
    else if(c[4]>c[2]) now[2]=now[4], c[2]=c[4];
}
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>h[i];
    memset(mx1,0,sizeof(mx1)), memset(mx2,0,sizeof(mx2));
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        if(h_cmp(i,mx1[a[i]][0]))
            mx2[a[i]]=mx1[a[i]][0], mx1[a[i]][0]=i;
        else if(h_cmp(i,mx2[a[i]])) mx2[a[i]]=i;
    }
    for(int j=1;j<20;j++)
        for(int i=1;i+(1<<j)-1<N;i++) {
            mx1[i][j]=(h_cmp(mx1[i][j-1],mx1[i+(1<<(j-1))][j-1]))? mx1[i][j-1]:mx1[i+(1<<(j-1))][j-1];
        }
    memset(ans,0,sizeof(ans));
    for(x=1;x<=N-10;x++) {
        memset(now,0,sizeof(now));
        for(int v=1;(v-1)*x+1<=N-10;v++) {
            PII res=Query((v-1)*x+1,min((int)(v*x),N-10));
            now[3]=res.first, now[4]=res.second;
            self_sort();
        }
        if(cmp(now[1],now[2])) ans[now[1]]=max(ans[now[1]],calc(now[1])-calc(now[2]));
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<" "; 
    cout<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    for(int i=2;i<N;i++) Log[i]=Log[i>>1]+1;
    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}