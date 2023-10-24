#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
using PLL=pair<ll,ll>;
const int N=5e2+10;
bool mem1;
int n,q,a[N],b[N],vis[N];
ll dis[9][N][N],d[1000][N];
vector<PLL> eg[N];
bool mem2;
int main() {
    freopen("subway.in","r",stdin);
    freopen("subway.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>q;
    memset(dis,0x3f,sizeof(dis));
    for(int op=0;op<q;op++) {
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<=n;i++) cin>>b[i];
        int m; cin>>m;
        for(int i=1;i<=n;i++) eg[i].clear();
        for(int i=1,u,v,w;i<=m;i++) {
            cin>>u>>v>>w;
            eg[u].emplace_back(v,w);
            eg[v].emplace_back(u,w);
        }
        for(int st=1;st<=n;st++) {
            priority_queue<PLL,vector<PLL>,greater<PLL>> que;
            que.emplace(0,st), dis[op][st][st]=0;
            memset(vis,0,sizeof(vis));
            while(que.size()) {
                int x=que.top().second; que.pop();
                if(vis[x]) continue;
                vis[x]=1;
                for(auto y:eg[x]) {
                    if(dis[op][st][y.first]>dis[op][st][x]+y.second)
                        dis[op][st][y.first]=dis[op][st][x]+y.second, que.emplace(dis[op][st][y.first],y.first);
                }
            }
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++) dis[op][i][j]+=a[i]+b[j];
    }
    memset(d,0x3f,sizeof(d));
    d[0][1]=0;
    for(int s=1;s<(1<<q);s++)
        for(int i=0;i<q;i++) if((1<<i)&s)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++)
                    d[s][k]=min(d[s][k],d[s^(1<<i)][j]+dis[i][j][k]);
    ll ans=1e18;
    for(int s=0;s<(1<<q);s++) ans=min(ans,d[s][n]);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
    #endif
    return 0;
}