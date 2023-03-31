#include<bits/stdc++.h>
using namespace std;

namespace io {
const int SIZE = 1 << 20;
char Ibuf[SIZE], *Il = Ibuf, *Ir = Ibuf, Obuf[SIZE], *Ol = Obuf, *Or = Ol + SIZE - 1, stack[32];
char isspace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'; }
void fill(void) { return Ir = (Il = Ibuf) + fread(Ibuf, 1, SIZE, stdin), void(); }
void flush(void) { return fwrite(Obuf, 1, Ol - Obuf, stdout), Ol = Obuf, void(); }
char buftop(void) { return Ir == Il ? fill(), *Il : *Il; }
char getch(void) { return Il == Ir ? fill(), Il == Ir ? EOF : *Il++ : *Il++; }
void putch(char x) { return *Ol++ = x, Ol == Or ? flush() : void(); }
template <typename T = int>
T read(void) {
    T x = 0, f = +1;
    char c = getch();
    while (c < '0' || c > '9') c == '-' ? void(f = -f) : void(), c = getch();
    while ('0' <= c && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48), c = getch();
    return x * f;
}
template <typename T>
void write(T x) {
    if (!x) putch('0');
    if (x < 0) putch('-'), x = -x;
    int top = 0;
    while (x) stack[top++] = (x % 10) ^ 48, x /= 10;
    while (top) putch(stack[--top]);
    return;
}
string getstr(const string& suf = "") {
    string s = suf;
    while (isspace(buftop())) getch();
    while (Il != Ir) {
        char* p = Il;
        while (Il < Ir && !isspace(*Il) && *Il != EOF) Il++;
        s.append(p, Il);
        if (Il < Ir) break;
        fill();
    }
    return s;
}
void putstr(string str, int begin = 0, int end = -1) {
    if (end == -1) end = str.size();
    for (int i = begin; i < end; i++) putch(str[i]);
    return;
}
struct Flusher_ {
    ~Flusher_() { flush(); }
} io_flusher_;
}  // namespace io
using io::putch;
using io::read;
using io::write;

const int N=2e5+10;
typedef pair<int,int> PII;
#define ls (id<<1)
#define rs (id<<1|1)
int n,ans[N],f[N],pos[N],a[N],b[N],dfn[N],Mxdfn[N];
vector<vector<int>> G;
int mx[N<<2];
void Modify(int id,int l,int r,int x,int val) {
    if(l==r) {
        mx[id]=val;
        return;
    }
    int mid=(l+r)>>1;
    x<=mid?Modify(ls,l,mid,x,val):Modify(rs,mid+1,r,x,val);
    mx[id]=max(mx[ls],mx[rs]);
}
int Query(int id,int l,int r,int x,int y) {
    if(x>y)return 0;
    if(x<=l&&y>=r) return mx[id];
    int mid=(l+r)>>1;
    if(y<=mid)return Query(ls,l,mid,x,y);
    if(x>mid)return Query(rs,mid+1,r,x,y);
    return max(Query(ls,l,mid,x,y),Query(rs,mid+1,r,x,y));
}
int vis[N],sz[N];
PII dfs1(int x,int s,int from) {
    sz[x]=1;
    int mxS=0; PII ans={INT_MAX,0};
    for(auto now:G[x]) {
        if(now==from||vis[now]) continue;
        ans=min(ans,dfs1(now,s,x));
        sz[x]+=sz[now];
        mxS=max(mxS,sz[now]);
    }
    return min(ans,PII{max(mxS,s-sz[x]),x});
}
void dfs2(int x,int from,int val) {
    Modify(1,1,n,a[x],val*f[x]);
    for(auto y:G[x])
        if(!vis[y]&&y!=from) dfs2(y,x,val);
}
void dfs3(int x,int from) {
    int v=Query(1,1,n,b[x],n)+1;
    ans[x]=max(ans[x],v);
    Modify(1,1,n,a[x],v);
    for(auto y:G[x])
        if(y!=from&&!vis[y]) dfs3(y,x);
    Modify(1,1,n,a[x],0);
}
int dfnT;
vector<int> Node;
void dfs4(int x,int from) {
    Node.push_back(x);
    sz[x]=1; dfn[x]=++dfnT;
    for(auto y:G[x]) {
        if(y==from||vis[y]) continue;
        dfs4(y,x);
        sz[x]+=sz[y];
    }
    Mxdfn[x]=dfnT;
}
void sol(int x) {
    vis[x]=1;
    Node.clear();
    dfnT=0, dfs4(x,0);
    sort(Node.begin(),Node.end(),[&](int x, int y){return a[x]>a[y];});
    int t=0;
    for(auto i:Node) {
        while (a[Node[t]]>=b[i]) Modify(1,1,Mxdfn[x],dfn[Node[t]],f[Node[t]]),t++;
        f[i]=Query(1,1,Mxdfn[x],dfn[i],Mxdfn[i])+1;
    }
    for(int i=0;i<t;i++) Modify(1,1,Mxdfn[x],dfn[Node[i]],0);
    ans[x]=max(ans[x],f[x]);
    for(auto y:G[x])
        if(!vis[y]) dfs2(y,x,1);
    for(auto y:G[x]) {
        if(vis[y]) continue;
        dfs2(y,x,0);
        Modify(1,1,n,a[x],Query(1,1,n,b[x],n)+1);
        dfs3(y,x);
        Modify(1,1,n,a[x],0);
        dfs2(y,x,1);
    }
    for(auto y:G[x])
        if(!vis[y]) dfs2(y,x,0);
    for(auto y:G[x])
        if(!vis[y]) sol(dfs1(y,sz[y],0).second);
}
int main() {
	freopen("lot.in","r",stdin);
	freopen("lot.out","w",stdout);
    n=read();
	for(int i=1;i<=n;i++) a[i]=read(), pos[i] = i;
    sort(pos+1,pos+n+1,[&](int x,int y){ return a[x]<a[y]; });
    G.resize(n+1);
	for(int i=1,u,v;i<n;i++) {
        u=read(),v=read();
		G[u].push_back(v), G[v].push_back(u);
	}
    for(int i=n;i>=1;i--)
        if(a[pos[i]]!=a[pos[i+1]]) b[pos[i]]=i+1;
        else b[pos[i]]=b[pos[i+1]];
    for(int i=1;i<=n;i++) a[pos[i]]=i;
    sol(dfs1(1,n,0).second);
	for(int i=1;i<=n;i++) write(ans[i]),putch('\n');
	return 0;
}