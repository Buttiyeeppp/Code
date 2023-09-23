#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=60;
bool mem1;
int n,m,p[N],pos[N][N];
struct node {
    int x,y,ex,ey;
}nd[N];
vector<node> ans[2];
bool move(int op,int u,int dx,int dy) {
    int x=nd[u].x,y=nd[u].y;
    if(pos[x+dx][y+dy]) return false;
    pos[x][y]=0, pos[x+dx][y+dy]=1;
    ans[op].push_back({x,y,x+dx,y+dy});
    nd[u].x+=dx, nd[u].y+=dy;
    return true;
}
void sol(int op) {
    for(int i=1;i<=m;i++) p[i]=i;
    sort(p+1,p+m+1,[](const int &a,const int &b) { return nd[a].ex<nd[b].ex; });
    for(int i=1;i<=m;i++) {
        while(nd[p[i]].x<i&&move(op,p[i],1,0));
        while(nd[p[i]].x>i&&move(op,p[i],-1,0));
    }
    for(int i=1;i<=m;i++) {
        while(nd[i].y<nd[i].ey&&move(op,i,0,1));
        while(nd[i].y>nd[i].ey&&move(op,i,0,-1));
    }
    for(int i=1;i<=m;i++) {
        while(nd[p[i]].x<nd[p[i]].ex&&move(op,p[i],1,0));
        while(nd[p[i]].x>nd[p[i]].ex&&move(op,p[i],-1,0));
    }
    for(int i=m;i>=1;i--) {
        while(nd[p[i]].x<nd[p[i]].ex&&move(op,p[i],1,0));
        while(nd[p[i]].x>nd[p[i]].ex&&move(op,p[i],-1,0));
    }
}
void input(int op) {
    memset(pos,0,sizeof(pos));
    for(int i=1;i<=m;i++) cin>>nd[i].ex>>nd[i].ey, nd[i].x=nd[i].y=i, pos[i][i]=1;
    sol(op);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    input(0), input(1);
    cout<<ans[0].size()+ans[1].size()<<endl;
    reverse(ans[0].begin(),ans[0].end());
    for(auto i:ans[0]) cout<<i.ex<<" "<<i.ey<<" "<<i.x<<" "<<i.y<<endl;
    for(auto i:ans[1]) cout<<i.x<<" "<<i.y<<" "<<i.ex<<" "<<i.ey<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}