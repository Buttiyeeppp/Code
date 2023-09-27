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
template<typename T> void write(T x) {
    if(x<0) x=-x, putchar('-');
    if(x>9) write(x/10);
    putchar((x%10)+'0');
}
ll n,m;
__int128 f[N];
void solve() {
    cin>>n>>m;
    memset(f,0,sizeof(f));
    for(int i=max(n,m);i>=1;i--) {
        __int128 c1=0,c2=0;
        for(int j=1;i*j<n;j++) f[i]+=m*(n-i*j), c1+=n-i*j;
        for(int j=1;i*j<m;j++) f[i]+=n*(m-i*j), c2+=m-i*j;
        f[i]+=2*c1*c2;
        for(int j=2;i*j<=max(n,m);j++) f[i]-=f[i*j];
    }
    __int128 ans=0;
    for(int i=1;i<=max(n,m);i++) {
        ans+=f[i]*n*m*i-(i-1)*f[i]*2*i-2*f[i]*i;
    }
    write(ans);
    putchar('\n');
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