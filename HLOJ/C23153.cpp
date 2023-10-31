#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,m,a[N],b[N],p[N],ans[N],to[N];
bool mem2;
int main() {
    freopen("marketplace.in","r",stdin);
    freopen("marketplace.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    int ed=0;
    for(int i=1,cnt=1;cnt<=m;i=i%n+1,cnt++) {
        ed=i;
        if(!p[a[i]]) p[a[i]]=cnt;
        else if(!p[b[i]]) p[b[i]]=cnt;
        else break;
    }
    vector<int> nd;
    for(int i=1;i<=m;i++) {
        if(!p[i]) ans[ed]++;
        else nd.push_back(i);
    }
    sort(nd.begin(),nd.end(),[](const int &x,const int &y){ return p[x]>p[y]; });
    for(auto i:nd) {
        int pos=p[i], j=(pos-1)%n+1;
        if(b[j]!=i&&pos<p[b[j]]) j=to[b[j]];
        if(!p[b[j]]) j=ed;
        to[i]=j, ans[j]++;
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<endl;

    #ifdef xxzx
    cerr<<"Time "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}