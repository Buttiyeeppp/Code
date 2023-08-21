#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PLL=pair<ll,ll>;
const int N=1e6+10;
bool mem1;
int n,head[N],tot=1;
struct Edge { int to,nxt,l; }eg[N<<1];
void Add(int x,int y,int z) {
	eg[++tot]={y,head[x],z};
	head[x]=tot;
}
int fr[N],vis[N],sp[N],pd;
ll mx[2][N],res,ans;
vector<ll> nd,s;
void dfs(int x,int from) {
	for(int i=head[x];i;i=eg[i].nxt) if((i^1)!=from&&!sp[eg[i].to]) {
		int y=eg[i].to;
		dfs(y,i);
		if(mx[0][y]+eg[i].l>mx[0][x]) mx[1][x]=mx[0][x], mx[0][x]=mx[0][y]+eg[i].l;
		else if(mx[0][y]+eg[i].l>mx[1][x]) mx[1][x]=mx[0][y]+eg[i].l;
	}
	res=max(res,mx[0][x]+mx[1][x]);
}
void find(int x,int from) {
	vis[x]=1;
	for(int i=head[x];i;i=eg[i].nxt) if((i^1)!=from) {
		int y=eg[i].to;
		if(vis[y]&&!pd) {
			ll u=x,len=0; pd=1;
			while(u!=y) {
				nd.push_back(u), s.push_back(len);
				len+=eg[fr[u]^1].l, u=eg[fr[u]^1].to;
			}
			nd.push_back(y), s.push_back(len);
		}
		else if(!vis[y]) fr[y]=i, find(y,i);
	}
}
void calc(int x) {
	pd=0, nd.clear(), s.clear(), find(x,0);
	ll m=nd.size(),len; res=0;
    for(auto now:nd) sp[now]=1;
	for(auto now:nd) dfs(now,0);
    for(auto now:nd) sp[now]=0;
	int spe=(m==2);
	for(int i=head[nd.back()];i;i=eg[i].nxt) {
		if(eg[i].to==nd[0]) {
			if(spe&&eg[i].l==s[1]) { spe=0; continue; }
			len=eg[i].l; break;
		}
	}
	nd.push_back(nd[0]), s.push_back(len+s[m-1]);
	for(int i=1,j=m;i<m;i++,j++)
		nd.push_back(nd[i]), s.push_back(s[i]-s[i-1]+s[j]);
	deque<int> q; q.push_back(0);
	for(int i=1;i<(int)nd.size();i++) {
		while(q.size()&&i-q.front()+1>m) q.pop_front();
		if(q.size()) {
			int j=q.front();
			res=max(res,s[i]-s[j]+mx[0][nd[i]]+mx[0][nd[j]]);
		}
		while(q.size()&&-s[q.back()]+mx[0][nd[q.back()]]<=-s[i]+mx[0][nd[i]]) q.pop_back();
		q.push_back(i);
	}
	ans+=res;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,j,z;i<=n;i++) {
		cin>>j>>z;
		Add(i,j,z), Add(j,i,z);
	}
	for(int i=1;i<=n;i++) if(!vis[i]) calc(i);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

