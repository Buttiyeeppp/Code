#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
const int M=2e5+10;
bool mem1;
int n,m,d[N][N],c[M];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++) {
        cin>>x>>y;
        d[x][y]=i;
    }
    for(int k=n;k>=1;k--) {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++) {
                int v=(d[i][k]<=d[k][j])? d[i][k]:d[k][j];
                if(v>d[i][j]) d[i][j]=v;
            }
        for(int i=k+1;i<=n;i++) { // i->k, k->i
            int v=(d[i][k]<=d[k][i])? d[i][k]:d[k][i];
            if(v) c[v-1]++;
        }
    }
    c[m]+=n;
    for(int i=m-1;i>=0;i--) c[i]+=c[i+1];
    for(int i=0;i<=m;i++) cout<<c[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}