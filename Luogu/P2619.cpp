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
int n,m,k;
struct Edge {
	int x,y,w,c;
	bool operator<(const Edge &q)const {
		return (w==q.w? c>q.c:w<q.w);
	}
}eg[N],g[N];
ll tot,sum,fa[N];
int find(int x) {
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void check(int x) {
	for(int i=1;i<=m;i++) {
		g[i]=eg[i];
		if(!g[i].c) g[i].w-=x;
	}
	sort(g+1,g+m+1);
	tot=sum=0;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++) {
		int fx=find(g[i].x), fy=find(g[i].y);
		if(fx!=fy) {
			fa[fx]=fy, sum+=g[i].w, tot+=(g[i].c==0);
		}
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++) cin>>eg[i].x>>eg[i].y>>eg[i].w>>eg[i].c, eg[i].x++, eg[i].y++;
	int l=-1e9,r=1e9;
	while(l+1<r) {
		int mid=(l+r)>>1; check(mid);
		if(tot<=k) l=mid;
		else r=mid;
	}
	check(l);
	cout<<sum+1ll*l*k<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

