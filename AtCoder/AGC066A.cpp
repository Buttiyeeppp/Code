#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e2+10;
bool mem1;
int n,d,a[N][N],b[N][N],f[N][N];
bool calc(int x,int y) {
    int res=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) {
            int c=((i+j)&1? x:y), w=a[i][j]%(2*d);
            if(abs(w-c)<abs(w-c-2*d)) b[i][j]=a[i][j]-w+c, res+=abs(w-c);
            else b[i][j]=a[i][j]-w+c+2*d, res+=abs(w-c-2*d);
        }
    // cerr<<x<<" "<<y<<" "<<res<<endl;
    if(res*2>d*n*n) return false;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) cout<<f[i][j]*b[i][j]<<" ";
        cout<<endl;
    }
    return true;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>d;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) cin>>a[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) f[i][j]=(a[i][j]<0? -1:1), a[i][j]=abs(a[i][j]);
    if(!calc(0,d)) calc(d,0);

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}