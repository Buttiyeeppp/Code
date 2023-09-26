#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
bool mem1;
int n,a[N][N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int j=1;j<n;j++)
        for(int i=1,v=j;i<n;i++) {
            a[i][j]=v++;
            if(v==n) v=1;
        }
    for(int i=1;i<n;i++)
        a[i][n]=a[n][i]=a[i][i], a[i][i]=0;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) cout<<a[i][j]<<" ";
        cout<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}