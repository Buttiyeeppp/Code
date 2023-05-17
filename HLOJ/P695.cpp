#include <bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
bool mem1;
int n,d,r;
double f[N][N],C[N][N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>d>>r;
    for(int i=0;i<=n+d;i++) C[i][0]=1;
    for(int i=1;i<=n+d;i++)
        for(int j=1;j<=i;j++) C[i][j]=C[i-1][j]+C[i-1][j-1];
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n+d;j++) {
            f[i][j]=min(r,i)*C[j-1][i-1];
            for(int k=0;k<=i;k++) f[i][j]+=C[i][k]*f[k][j-i];
        }
    cout<<fixed<<setprecision(7)<<f[n][d+n]/C[n+d-1][n-1]<<endl;

    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    cerr<<"Time "<<clo<<"MS"<<endl;
    return 0;
}