#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e2+10;
const double INF=1e11;
bool mem1;
double d[N][N],f[N][N],x[N],y[N];
int n;
double dis(int i,int j) {
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}
double ans=INF;
void work(int op,vector<int> now) {
    if(now.size()==1) return;
    if(!op)
        sort(now.begin(),now.end(),[](const int &q,const int &p) { return x[q]<x[p]; });
    else 
        sort(now.begin(),now.end(),[](const int &q,const int &p) { return y[q]<y[p]; });

    vector<int> lft,rgt;
    int mid=now.size()/2;
    for(int i=0;i<mid;i++) lft.push_back(now[i]);
    for(int i=mid;i<(int)now.size();i++) rgt.push_back(now[i]);
    work(op^1,lft), work(op^1,rgt);

    for(auto i:lft)
        for(auto j:rgt) {
            for(auto k:rgt) f[i][j]=min(f[i][j],d[k][j]+dis(i,k));
        }
    for(auto i:lft)
        for(auto j:rgt)
            for(auto k:lft)
                d[i][j]=d[j][i]=min(d[i][j],d[i][k]+f[k][j]);

    for(auto i:lft) for(auto j:lft) d[i][j]=INF;
    for(auto i:rgt) for(auto j:rgt) d[i][j]=INF;
    
    if((int)now.size()==n) {
        for(auto i:lft)
            for(auto j:rgt) ans=min(ans,d[i][j]);
    }
}
bool mem2;
int main() {
    freopen("splitham.in","r",stdin);
    freopen("splitham.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    vector<int> nd;
    for(int i=1;i<=n;i++) cin>>x[i]>>y[i], nd.push_back(i);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) d[i][j]=f[i][j]=INF;
    for(int i=1;i<=n;i++) d[i][i]=0;
    work(0,nd);
    cout<<fixed<<setprecision(2)<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}