#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
// #define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e2+10;
bool mem1;
int n,la,lb,a[N],b[N],mem[N][N];
bool comp(int x,int y) {
    if(~mem[x][y]) return mem[x][y];
    cout<<"? "<<x<<" "<<y<<endl;
    char ch; cin>>ch;
    mem[x][y]=(ch=='>'? 1:0), mem[y][x]=mem[x][y]^1;
    return mem[x][y];
}
void in(int *x,int n,int v) {
    int p=n;
    for(int i=1;i<n;i++) if(comp(v,x[i])) { p=i; break; }
    for(int i=n-1;i>=p;i--) x[i+1]=x[i];
    x[p]=v;
}
void solve() {
    cin>>n;
    la=(n+1)/2, lb=n+1-la;
    for(int i=1;i<=la;i++) a[i]=i;
    for(int i=la+1;i<=n+1;i++) b[i-la]=i;
    memset(mem,-1,sizeof(mem));
    sort(a+1,a+la+1,comp), sort(b+1,b+lb+1,comp);
    for(int i=1;i<=n;i++) {
        int v=comp(a[la],b[lb]);
        if(i==n) break;
        if(!v) in(a,la,n+1+i);
        else in(b,lb,n+1+i);
    }
    cout<<"!"<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}