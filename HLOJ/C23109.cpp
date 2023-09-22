#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e3+10;
bool mem1;
int n,m,ps[N][N],pt[N][N];
ll a,b,c,d,f[N][N];
string s,t;
bool mem2;
int main() {
    // freopen("string.in","r",stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>a>>b>>c>>d>>s>>t;
    n=s.size(), m=t.size();
    s=" "+s, t=" "+t;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            ps[i][j]=ps[i-1][j];
            if(s[i]==t[j]) ps[i][j]=i;
        }
    for(int j=1;j<=m;j++)
        for(int i=1;i<=n;i++) {
            pt[i][j]=pt[i][j-1];
            if(s[i]==t[j]) pt[i][j]=j;
        }
    memset(f,0x3f,sizeof(f));
    for(int j=0;j<=m;j++) f[0][j]=a*j;
    for(int i=1;i<=n;i++) {
        for(int j=0;j<=m;j++) f[i][j]=min(f[i][j],f[i-1][j]+b);
        for(int j=1;j<=m;j++) f[i][j]=min(f[i][j],f[i-1][j-1]+c*(s[i]!=t[j]));
        for(int j=2;j<=m;j++) {
            int k=ps[i-1][j], l=pt[i][j-1];
            // if(i==n&&j==m) cout<<k<<" "<<l<<endl;
            if(k&&l) f[i][j]=min(f[i][j],f[k-1][l-1]+d+b*(i-k-1)+a*(j-l-1));
        }
        for(int j=0;j<m;j++) f[i][j+1]=min(f[i][j+1],f[i][j]+a);
    }
    cout<<f[n][m]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}