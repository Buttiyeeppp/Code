#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=7e2+10;
bool memory1;
int n,h[N][N],v[N][N],fx[2][2]={{1,0},{0,1}},t1,t2,ans=1;
struct Edge {
    int x,y,a,b;
}eg1[N*N*2],eg2[N*N*2];
int sz[N*N],fa[N*N];
int find(int x) {
    return (x==fa[x])? x:find(fa[x]);
}
vector<PII> mem;
void merge(int x,int y) {
    x=find(x),y=find(y);
    if(x==y) return;
    if(sz[x]>sz[y]) swap(x,y);
    fa[x]=y,sz[y]+=sz[x],ans=max(ans,sz[y]);
    mem.emplace_back(x,y);
}
bool memory2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) cin>>h[i][j];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) cin>>v[i][j];
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) for(int k:{0,1}) {
            int ni=i+fx[k][0],nj=j+fx[k][1];
            if(ni<=n&&nj<=n) {
                if((PII){h[i][j],v[i][j]}==(PII){h[ni][nj],v[ni][nj]}) {
                    eg1[++t1]={(i-1)*n+j,(ni-1)*n+nj,0,0};
                }
                else if((h[i][j]>h[ni][nj]&&v[i][j]<v[ni][nj])||
                        (h[i][j]<h[ni][nj]&&v[i][j]>v[ni][nj])||
                        h[i][j]==h[ni][nj]){
                    eg2[++t2]={(i-1)*n+j,(ni-1)*n+nj,abs(h[i][j]-h[ni][nj]),abs(v[i][j]-v[ni][nj])};
                }
            }
        }
    }
    sort(eg2+1,eg2+t2+1,[](const Edge &x,const Edge &y) {
        return 1ll*x.a*y.b<1ll*y.a*x.b;
    });
    for(int i=1;i<=n*n;i++) sz[i]=1,fa[i]=i;
    for(int i=1;i<=t1;i++) merge(eg1[i].x,eg1[i].y);
    // for(int i=1;i<=t1;i++) cerr<<eg1[i].x<<" "<<eg1[i].y<<endl;
    // cerr<<"------ "<<ans<<endl;
    for(int i=1,j;i<=t2;i=j) {
        mem.clear();
        j=i;
        for(;j<=t2&&1ll*eg2[i].a*eg2[j].b==1ll*eg2[j].a*eg2[i].b;j++) {
            merge(eg2[j].x,eg2[j].y);
            // cerr<<eg2[j].x<<" "<<eg2[j].y<<endl;
        }
        // cerr<<"------- "<<ans<<endl;
        reverse(mem.begin(),mem.end());
        for(auto i:mem) fa[i.first]=i.first,sz[i.second]-=sz[i.first];
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&memory1-&memory2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}