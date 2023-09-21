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
int n,p[N],vis[N],tot,ans[N];
vector<int> nd[N],r[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=n;i++) if(!vis[i]) {
        nd[++tot].push_back(i), vis[i]=1;
        int u=p[i];
        while(!vis[u]) nd[tot].push_back(u), vis[u]=1, u=p[u];
        r[nd[tot].size()].push_back(tot);
        // cout<<nd[tot].size()<<endl;
    }
    for(int l=1;l<=n;l++) if(r[l].size()) {
        if(l&1) {
            int k=(l+1)/2;
            for(auto now:r[l]) {
                for(int i=0;i<l;i++) {
                    ans[nd[now][i]]=nd[now][(i+k)%l];
                }
            }
        }
        else {
            if(r[l].size()&1) return cout<<-1<<endl, 0;
            for(int i=0;i<(int)r[l].size();i+=2) {
                int r1=r[l][i], r2=r[l][i+1];
                for(int j=0;j<l;j++) ans[nd[r1][j]]=nd[r2][j], ans[nd[r2][j]]=nd[r1][(j+1)%l];
            }
        }
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}