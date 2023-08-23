#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n,m,k,w[N],ind[N];
vector<int> g[N];
int dfn[N],low[N],tim,choose[N],st[N],top;
int col[N],cnt,mn[N];
void tarjan(int x) {
	dfn[x]=low[x]=++tim, st[++top]=x;
	for(auto y:g[x]) {
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(!col[y]) low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]) {
		cnt++;
		while(st[top+1]!=x) {
			col[st[top]]=cnt;
			if(!mn[cnt]||w[mn[cnt]]>w[st[top]]) mn[cnt]=st[top];
			top--;
		}
	}
}
int pd[N];
bool mem2;
int main() {
	freopen("P5008_1.in","r",stdin);
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>w[i];
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y;
		g[x].push_back(y);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int x=1;x<=n;x++)
		for(auto y:g[x]) {
			if(col[x]!=col[y]||x==y) ind[col[y]]++;
		}
	for(int i=1;i<=cnt;i++) if(!ind[i]) pd[mn[i]]=1;
	vector<int> val;
	for(int i=1;i<=n;i++) if(!pd[i]) val.push_back(w[i]);
	cout<<val.size()<<endl;
	sort(val.begin(),val.end(),[](const int &x,const int &y) { return x>y; });
	int ans=0;
	for(int i=0;i<min((int)val.size(),k);i++) ans+=val[i];
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

