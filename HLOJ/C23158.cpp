#include<bits/stdc++.h>
#include <cstdio>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e2+10;
bool mem1;
int n,L,R,s[N],f[N][N],g[N][N];
void Min(int &x,int y) { return x=(x<=y)? x:y, void(); }
int read() {
    int f=1,z=0; char ch=getchar();
    while(ch<'0'||ch>'9') { if(ch=='-') f*=-1; ch=getchar(); }
    while(ch>='0'&&ch<='9') { z=z*10+ch-'0'; ch=getchar(); }
    return f*z;
}
const int INF=0x3f3f3f3f;
bool mem2;
int main() {
    freopen("rock.in","r",stdin);
    freopen("rock.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    n=read(),L=read(),R=read();
    L=max(L,2), R=min(R,n);
    for(int i=1;i<=n;i++) s[i]=s[i-1]+read();
    memset(g,0x3f,sizeof(g));
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++) g[i][i]=0;
    for(int l=n;l>=1;l--) {
        f[0][l-1]=0;
        for(int r=l;r<=n;r++) {
            for(int k=1;k<=min(R,r-l+1);k++) {
                for(int d=l-1;d<r;d++) Min(f[k][r],f[k-1][d]+g[r][d+1]);
            }
            int sum=s[r]-s[l-1];
            for(int k=L;k<=R;k++) Min(f[1][r],f[k][r]+sum);
            g[r][l]=f[1][r];
        }
        f[0][l-1]=INF;
        for(int r=l;r<=n;r++)
            for(int k=1;k<=min(R,r-l+1);k++) f[k][r]=INF;
    }
    cout<<((g[n][1])==INF? -1:g[n][1])<<endl;

    #ifdef xxzx
    cerr<<"Time "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}