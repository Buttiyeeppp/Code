#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=60+10;
bool mem1;
int n,m,p[N],pos[N][N],vis[N];
struct node {
    int x,y,ex,ey;
}nd[N];
bool yep() {
    for(int i=1;i<=m;i++)
        if(!(nd[i].x==nd[i].ex&&nd[i].y==nd[i].ey)) return false;
    return true;
}
mt19937 rd(time(0));
vector<node> ans;
void mv(int x,int y,int ex,int ey) {
    int i=pos[x][y];
    pos[x][y]=0, pos[ex][ey]=i;
    nd[i].x=ex, nd[i].y=ey;
    ans.push_back({x,y,ex,ey});
}
bool can(int x,int y,int dx,int dy) {
    if(!pos[x][y]) return true;
    if(x+dx>=1&&x+dx<=n&&y+dy>=1&&y+dy<=n)
        if(can(x+dx,y+dy,dx,dy)) return mv(x,y,x+dx,y+dy), true;
    return false;
}
void move(int i) {
    vis[i]=1;
    int dx=((nd[i].x<=nd[i].ex)? 1:-1);
    while(nd[i].x!=nd[i].ex&&!vis[pos[nd[i].x+dx][nd[i].y]]) {
        if(can(nd[i].x+dx,nd[i].y,0,1)||can(nd[i].x+dx,nd[i].y,0,-1)) mv(nd[i].x,nd[i].y,nd[i].x+dx,nd[i].y);
    }
    int dy=((nd[i].y<=nd[i].ey)? 1:-1);
    while(nd[i].y!=nd[i].ey&&!vis[pos[nd[i].x][nd[i].y+dy]]) {
        if(can(nd[i].x,nd[i].y+dy,1,0)||can(nd[i].x,nd[i].y+dy,-1,0)) mv(nd[i].x,nd[i].y,nd[i].x,nd[i].y+dy);
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>nd[i].x>>nd[i].y, pos[nd[i].x][nd[i].y]=i;
    for(int i=1;i<=m;i++) cin>>nd[i].ex>>nd[i].ey, p[i]=i;
    while(!yep()) {
        shuffle(p+1,p+m+1,rd);
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=m;i++) move(p[i]);
    }
    cout<<ans.size()<<endl;
    for(auto i:ans) cout<<i.x<<" "<<i.y<<" "<<i.ex<<" "<<i.ey<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
