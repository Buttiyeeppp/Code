#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e4+10;
bool memory1;
ll n,k,m,a[N],b[N],p[N],vis[N];
bool memory2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k>>m;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i],p[i]=i;
    sort(p+1,p+n+1,[](const int &x,const int &y){return (PII){b[x],a[x]}<(PII){b[y],a[y]};});
    priority_queue<int,vector<int>,greater<int>> q;
    priority_queue<PII,vector<PII>,greater<PII>> qa,qb;
    for(int i=1;i<=k;i++) {
        m-=b[p[i]],q.push(a[p[i]]-b[p[i]]),vis[p[i]]=1;
        if(m<0) {cout<<i-1<<endl; return 0;}
    }
    for(int i=k+1;i<=n;i++) qa.emplace(a[p[i]],p[i]),qb.emplace(b[p[i]],p[i]);
    for(int i=k+1;i<=n;i++) {
        while(vis[qa.top().second]) qa.pop();
        while(vis[qb.top().second]) qb.pop();
        int v1=qa.top().first,v2=qb.top().first+q.top();
        if(v1<v2) {
            m-=v1,vis[qa.top().second]=1,qa.pop();
        }
        else {
            int p=qb.top().second;
            m-=v2,vis[p]=1,qb.pop(),q.pop();
            q.push(a[p]-b[p]);
        }
        if(m<0) {cout<<i-1<<endl; return 0;}
    }
    cout<<n<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&memory1-&memory2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}