#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int nxt[N][30],tot,n,m,pos[N],fa[N],fail[N],dep[N];
string s;
vector<int> eg[N];
void build() {
    queue<int> q;
    for(int i=0;i<26;i++)
        if(nxt[0][i]) q.push(nxt[0][i]);
    while(q.size()) {
        int x=q.front(); q.pop();
        eg[fail[x]].push_back(x);
        for(int i=0;i<26;i++) {
            if(nxt[x][i]) fail[nxt[x][i]]=nxt[fail[x]][i], q.push(nxt[x][i]);
            else nxt[x][i]=nxt[fail[x]][i];
        }
    }
}
int dfn[N],mxdfn[N],tim;
void dfs(int x) {
    dfn[x]=++tim;
    for(auto y:eg[x]) dfs(y);
    mxdfn[x]=tim;
}
int v[N];
int lowbit(int x) { return x&-x; }
void Add(int x,int val) {
    for(int i=x;i<=tim;i+=lowbit(i)) v[i]+=val;
}
int Qry(int x) {
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=v[i];
    return res;
}
vector<PII> qr[N];
int ans[N];
void dfs1(int x) {
    Add(dfn[x],1);
    for(auto now:qr[x]) {
        ans[now.second]=Qry(mxdfn[now.first])-Qry(dfn[now.first]-1);
    }
    for(int i=0;i<26;i++) if(nxt[x][i]&&dep[nxt[x][i]]==dep[x]+1) dfs1(nxt[x][i]);
    Add(dfn[x],-1);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>s;
    for(int i=0,p=0;i<(int)s.size();i++) {
        if(s[i]>='a'&&s[i]<='z') {
            if(!nxt[p][s[i]-'a']) nxt[p][s[i]-'a']=++tot, fa[tot]=p, dep[tot]=dep[p]+1;
            p=nxt[p][s[i]-'a'];
        }
        else if(s[i]=='B') p=fa[p];
        else if(s[i]=='P') pos[++n]=p;
    }
    build(), dfs(0);
    cin>>m;
    for(int i=1,x,y;i<=m;i++) {
        cin>>x>>y;
        qr[pos[y]].push_back({pos[x],i});
    }
    dfs1(0);
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}