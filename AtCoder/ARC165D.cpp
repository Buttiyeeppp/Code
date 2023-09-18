#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e3+10;
bool mem1;
int n,m,a[N],b[N],c[N],d[N];
int yep[N],fa[N],rond;
int dfn[N],low[N],col[N],cnt,tim,st[N],top;
vector<int> eg[N],nd[N];
int find(int x) {
    return (x==fa[x])? x:(fa[x]=find(fa[x]));
}
void merge(int x,int y) {
    int fx=find(x), fy=find(y);
    if(fy!=fx) fa[fy]=fx;
}
void tarjan(int x) {
    dfn[x]=low[x]=++tim;
    st[++top]=x;
    for(auto y:eg[x]) {
        if(y==x) rond=1;
        if(!dfn[y]) {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(!col[y]) low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x]) {
        cnt++;
        while(st[top+1]!=x) {
            int y=st[top];
            if(y!=x) rond=1;
            nd[cnt].push_back(y);
            col[y]=cnt;
            top--;
        }
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=m;i++) cin>>a[i]>>b[i]>>c[i]>>d[i];
    for(int i=1;i<=n;i++) fa[i]=i;
    while(1) {
        memset(dfn,0,sizeof(dfn)), memset(col,0,sizeof(col)), memset(st,0,sizeof(st));
        top=tim=cnt=rond=0;
        for(int i=1;i<=n;i++) eg[i].clear();
        for(int i=1;i<=m;i++) if(!yep[i])
            eg[find(a[i])].push_back(find(c[i]));
        for(int i=1;i<=n;i++) if(!dfn[i]&&find(i)==i) tarjan(i);
        if(!rond) return cout<<"Yes"<<endl, 0;
        for(int i=1;i<=m;i++) if(!yep[i]) {
            if(col[find(a[i])]==col[find(c[i])]) {
                if(c[i]==d[i]) return cout<<"No"<<endl, 0;
                if(a[i]==b[i]) yep[i]=1;
                else a[i]++, c[i]++;
            }
        }
        for(int i=1;i<=cnt;i++) {
            for(int j=1;j<(int)nd[i].size();j++) merge(nd[i][0],nd[i][j]);
            nd[i].clear();
        }
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
/*
3 1
1 3 1 2
*/