#include<bits/stdc++.h>
using namespace std;
const int N=2e4+10;
const int M=5e4+10;
int n,m;
vector<int> g[N];
struct Edge {
    int u,v;
}e[M];
inline int read() {
    int f=1,z=0; char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-')  f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        z=z*10+ch-'0';
        ch=getchar();
    }
    return f*z;
}
int low[N],dfn[N],choose[N],tim,sta[N],top;
int col[N],cnt,ind[N],out[N],sz[N];
void tarjan(int x) {
    dfn[x]=low[x]=++tim, sta[++top]=x; 
    for(auto y:g[x]) {
        if(!dfn[y]) {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }else if(!choose[y]) low[x]=min(low[x],dfn[y]);
    }
    if(low[x]==dfn[x]) {
        choose[x]=1, col[x]=++cnt;
        while(sta[top]!=x) {
            int y=sta[top];
            choose[y]=1, col[y]=cnt;
            top--;
        }
        top--;
    }
}
void solve() {
    n=read(), m=read();
    top=cnt=tim=0;
    for(int i=1;i<=n;i++) {
        g[i].clear();
        out[i]=dfn[i]=ind[i]=choose[i]=0;
    } 
    for(int i=1,u,v;i<=m;i++) {
        u=read(), v=read();
        e[i]=(Edge){u,v};
        g[u].push_back(v);
    }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    for(int i=1,u,v;i<=m;i++) {
        u=col[e[i].u], v=col[e[i].v];
        if(u!=v) out[u]++, ind[v]++;
    }
    int suma=0, sumb=0;
    for(int i=1;i<=cnt;i++) {
        if(!out[i]) suma++;
        if(!ind[i]) sumb++;
    }
    if(cnt==1) puts("0");
    else printf("%d\n",max(suma,sumb));
}
int main() {
    // freopen("a.txt","r",stdin);
    int T=read();
    while(T--) solve();
    return 0;
}