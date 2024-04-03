#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e6+10;
const ll Mod=1e9+9;
const ll inv=500000005;
bool mem1;
ll m,n,a[22][N],b[22][N],c[22][N];
void FWT(ll *f,int op) {
    for(int i=1;i<n;i<<=1) {
        for(int j=0;j<n;j+=(i<<1)) {
            for(int k=j;k<j+i;k++) {
                ll x=f[k], y=f[k+i];
                f[k]=(x+y)%Mod, f[k+i]=(x-y+Mod)%Mod;
                if(op==-1) f[k]=f[k]*inv%Mod, f[k+i]=f[k+i]*inv%Mod;
            }
        }
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>m;
    n=1<<m;
    for(int i=0,x;i<n;i++) cin>>x, a[__builtin_popcount(i)][i]=x;
    for(int i=0,x;i<n;i++) cin>>x, b[__builtin_popcount(i)][i]=x;
    for(int i=0;i<=m;i++) FWT(a[i],1), FWT(b[i],1);
    for(int i=0;i<=m;i++) {
        for(int j=0;j<=i;j++)
            for(int k=0;k<n;k++) c[i][k]=(c[i][k]+a[j][k]*b[i-j][k])%Mod;
    }
    for(int i=0;i<=m;i++) FWT(c[i],-1);
    for(int i=0;i<n;i++) cout<<c[__builtin_popcount(i)][i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}