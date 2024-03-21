#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2.1e3;
bool mem1;
int n,m,a[2][N][N];
vector<PII> ans;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    m=1<<n;
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++) cin>>a[(n-1)&1][i][j];
    for(int k=n-1;k>=1;k--) {
        int f=k&1, l=1<<(k-1);
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++) a[f^1][i][j]=0;
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++) if(a[f][i][j]) {
                // cerr<<i<<" "<<j<<" "<<f<<" "<<l<<endl;
                a[f^1][(i-l+m)%m][j]^=1;
                a[f^1][(i+l)%m][j]^=1;
                a[f^1][i][(j-l+m)%m]^=1;
                a[f^1][i][(j+l)%m]^=1;
                a[f^1][i][j]^=1;
            }
    }
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++) if(a[0][i][j]) ans.emplace_back(i,j);
    cout<<ans.size()<<endl;
    for(auto i:ans) cout<<i.first<<" "<<i.second<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}