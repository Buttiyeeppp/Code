#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
ll n,m,dis[2][N],tot;
struct Line {
    vector<int> v,t;
}l[N],nl[N];
vector<PII> eg[2][N];
void dij(int op,int st) {
    memset(dis[op],0x3f,sizeof(dis[op]));
    priority_queue<PII,vector<PII>,greater<PII>> q;
    dis[op][st]=0, q.emplace(0,st);
    while(q.size()) {
        int x=q.top().second;  q.pop();
        for(auto y:eg[op][x]) {
            if(dis[op][y.first]>dis[op][x]+y.second)
                dis[op][y.first]=dis[op][x]+y.second, q.emplace(dis[op][y.first],y.first);
        }
    }
}
vector<int> nd[N],p,sta[N];
ll f[N];
ll X(int x) { return dis[0][x]; }
ll Y(int x) { return f[x]+dis[0][x]*dis[0][x]; }
double slope(int x,int y) { if(X(x)==X(y)) cerr<<"Oh!"<<endl; return 1.*(Y(x)-Y(y))/(X(x)-X(y)); }
const ll INF=1e17;
ll Qry(int x,ll k) {
    int siz=sta[x].size();
    if(!siz) return -INF;
    while(siz>1&&slope(sta[x][siz-1],sta[x][siz-2])<=k) {
        sta[x].pop_back(), siz--;
    }
    int y=sta[x].back();
    // cout<<"Qry "<<y<<" "<<Y(y)-k*X(y)<<endl;
    return Y(y)-k*X(y);
}
void insert(int i,int x) {
    int siz=sta[i].size();
    while(siz>1&&slope(sta[i][siz-1],sta[i][siz-2])<=slope(x,sta[i][siz-2]))
        sta[i].pop_back(), siz--;
    sta[i].push_back(x);
}
void Max(ll &x,ll y) { return x=(x>=y)? x:y, void(); }
bool mem2;
int main() {
    // freopen("ex_metropolis5.in","r",stdin);
    freopen("metropolis.in","r",stdin);
    freopen("metropolis.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1,s;i<=m;i++) {
        cin>>s;
        l[i].v.resize(s+2), l[i].t.resize(s+2);
        for(int j=1;j<=s;j++) cin>>l[i].v[j]>>l[i].t[j];
        cin>>l[i].v[s+1];
        for(int j=1;j<=s;j++) {
            eg[0][l[i].v[j]].emplace_back(l[i].v[j+1],l[i].t[j]);
            eg[1][l[i].v[j+1]].emplace_back(l[i].v[j],l[i].t[j]);
        }
    }
    dij(0,1), dij(1,n);
    for(int i=1;i<=m;i++) {
        int s=l[i].v.size()-1;
        Line now=l[i];
        for(int i=1;i<=s;i++) {
            if(i==1||dis[0][now.v[i-1]]+now.t[i-1]+dis[1][now.v[i]]!=dis[0][n])
                tot++, nl[tot].v.push_back(now.v[i]);
            else nl[tot].t.push_back(now.v[i-1]), nl[tot].v.push_back(now.v[i]);
        }
    }
    for(int i=1;i<=tot;i++) {
        for(auto j:nl[i].v) nd[j].push_back(i);
    }
    for(int i=1;i<=n;i++) p.push_back(i);
    sort(p.begin(),p.end(),[](const int &x,const int &y){ return dis[0][x]<dis[0][y]; });
    memset(f,-0x3f,sizeof(f));
    f[1]=0;
    for(auto i:p) {
        for(auto j:nd[i]) Max(f[i],Qry(j,2*dis[0][i])+dis[0][i]*dis[0][i]);
        for(auto j:nd[i]) insert(j,i);
    }
    cout<<dis[0][n]<<" "<<f[n]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}