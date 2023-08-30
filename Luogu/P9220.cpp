#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,col[N],c[N];
vector<int> eg[N],ng[N];
int dfn[N],low[N],tim,st[N],top,ch[N],cnt,sp;
void tarjan(int x) {
	dfn[x]=low[x]=++tim, st[++top]=x;
	for(auto y:eg[x]) {
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(!ch[y]) low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]) {
		cnt++;
		c[cnt]=col[x];
		while(st[top+1]!=x) {
			if(col[st[top]]!=c[cnt]) sp=1;
			ch[st[top]]=cnt;
			top--;
		}
	}
}
int ind[N],vis[N];
void dfs(int x) {
	vis[x]=1;
	for(auto y:ng[x]) if(!vis[y]) dfs(y);
}
void solve() {
	memset(st,0,sizeof(st));
	tim=top=cnt=sp=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>col[i], eg[i].clear(), ch[i]=dfn[i]=0;
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y, eg[x].push_back(y);
	}
	sp=cnt=tim=top=0;
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	if(sp) return cout<<"N", void();
	for(int i=1;i<=cnt;i++) ind[i]=vis[i]=0, ng[i].clear();
	for(int x=1;x<=n;x++)
		for(auto y:eg[x]) if(ch[x]!=ch[y]){
			ind[ch[y]]++, ng[ch[x]].push_back(ch[y]);
		}	
	queue<int> q;
	for(int i=1;i<=cnt;i++) if(!ind[i]) q.push(i);
	int p=-1;
	while(q.size()) {
		int x=q.front(); q.pop();
		if(c[x]) { p=x; break; }
		for(auto y:ng[x]) {
			ind[y]--;
			if(!ind[y]) q.push(y);
		}
	}
	if(~p) {
		dfs(p);
		int pd=1;
		for(int i=1;i<=cnt;i++) if(c[i]!=vis[i]) pd=0;
		if(pd) return cout<<"A", void();
	}
	int tot=0;
	for(int i=1;i<=cnt;i++) tot+=c[i];
	if((!tot)||(cnt==2&&tot==1)||(cnt==2&&tot==2)) cout<<"B";
	else cout<<"N";
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
