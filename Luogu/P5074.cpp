#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=13;
bool mem1;
int n,m,a[N][N];
ll f[100000][2],g[100000][2];
void solve() {
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) cin>>a[i][j];
    memset(g,0,sizeof(g));
    g[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            memset(f,0,sizeof(f));
            int c=1<<(j-1);
            if(a[i][j]) {
                for(int s=0;s<(1<<m);s++) {
                    if(!(c&s)) {
                        f[s][1]+=g[s][1];
                        f[s^c][0]+=g[s][1];
                        f[s^c][1]+=g[s][0];
                    }
                    else {
                        f[s][0]+=g[s][0];
                        f[s^c][0]+=g[s][1];
                        f[s^c][1]+=g[s][0];
                    }
                }
            }
            else for(int s=0;s<(1<<m);s++) if(!(c&s)) f[s][0]=g[s][0];
            for(int s=0;s<(1<<m);s++) {
                g[s][0]=f[s][0];
                g[s][1]=(j!=m)? f[s][1]:0;
            }
        }
    cout<<g[0][0]<<endl;
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