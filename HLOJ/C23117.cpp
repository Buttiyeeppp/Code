#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int M=1e3+10;
const int N=1e5+10;
bool mem1;
const int fac[10]={1,1,2,6,24,120,720,5040,40320};
int n,l[M],r[M];
int s[2][N],pl[10],cnt,mem[N][10],p0[N],vis[10];
ll c[M],f[M][5042];
int calc(int p[]) {
    int res=0;
    for(int i=1;i<=7;i++) {
        vis[p[i]]=1;
        for(int j=0;j<p[i];j++) if(!vis[j]) res+=fac[7-i];
    }
    for(int i=0;i<7;i++) vis[i]=0;
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    
    cin>>n;
    for(int i=1;i<=n;i++)  cin>>l[i]>>r[i]>>c[i];
    for(int i=1;i<=8;i++) pl[i]=i-1;
    do {
        int x[10],y[10],lx=0,ly=0;
        for(int i=1;i<=8;i++) {
            if(pl[i]!=0) x[++lx]=pl[i]-1;
            if(pl[i]!=7) y[++ly]=pl[i];
            if(pl[i]==0) p0[++cnt]=i;
        }
        memcpy(mem[cnt],pl,sizeof(pl));
        s[0][cnt]=calc(x), s[1][cnt]=calc(y);
    }while(next_permutation(pl+1,pl+8+1));
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=cnt;j++) {
            ll res=0;
            for(int k=1;k<p0[j];k++) {
                int p=i-mem[j][k];
                if(p&&l[p]<=i&&r[p]>=i) res+=c[p];
            }
            for(int k=p0[j]+1;k<=8;k++) {
                int p=i-mem[j][k];
                if(p&&l[i]<=p&&r[i]>=p) res+=c[i];
            }
            f[i][s[1][j]]=max(f[i][s[1][j]],f[i-1][s[0][j]]+res);
        }
    }
    ll ans=0;
    for(int i=0;i<5042;i++) ans=max(ans,f[n][i]);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
