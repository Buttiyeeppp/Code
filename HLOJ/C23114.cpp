#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n,q,a[N],tot,ans[N];
struct Edge {
    int l,r;
}eg[N];
struct Query {
    int id,f,l,r;
};
vector<Query> qry[N];
int s[N];
int lowbit(int x) { return x&-x; }
void Add(int x,int v) {
    for(int i=x;i<=n;i+=lowbit(i)) s[i]+=v;
}
int Qry(int x) {
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=s[i];
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>eg[i].l>>eg[i].r;
    int B=sqrt(n);
    for(int t=1,m;t<=q;t++) {
        cin>>m;
        if(m>=B) { // n/B
            for(int i=1;i<=n;i++) a[i]=0;
            for(int i=1,x;i<=m;i++) cin>>x, a[x]++;
            for(int i=2;i<=n;i++) a[i]+=a[i-1];
            int res=0;
            for(int i=1;i<=n;i++) if((a[eg[i].r]-a[eg[i].l-1])&1) res++;
            ans[t]=res;
        }
        else {
            vector<int> v;
            v.push_back(0), v.push_back(n+1);
            for(int i=1,x;i<=m;i++) cin>>x, v.push_back(x);
            sort(v.begin(),v.end());
            for(int i=1;i+1<(int)v.size();i++)
                for(int j=i;j+1<(int)v.size();j+=2) {
                    qry[v[i]].push_back({t,1,v[j],v[j+1]-1});
                    qry[v[i-1]].push_back({t,-1,v[j],v[j+1]-1});
                }
        }
    }
    sort(eg+1,eg+n+1,[](const Edge &x,const Edge &y) { return x.l<y.l; });
    for(int i=1,p=1;i<=n;i++) {
        while(p<=n&&eg[p].l==i) Add(eg[p++].r,1);
        for(auto now:qry[i]) {
            ans[now.id]+=now.f*(Qry(now.r)-Qry(now.l-1));
        }
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}