#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,q,a[N],p[N],pos[N],fa[N],blo[N];
vector<int> P;
void Get_Prime() {
	for(int i=2;i<N;i++) {
		if(!p[i]) P.push_back(i), p[i]=i;
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			p[now*i]=now;
			if(i%now==0) break;
		}
	}
}
int find(int x) {
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
void merge(int x,int y) {
	int fx=find(x),fy=find(y);
	if(fx!=fy) fa[fx]=fy;
}
map<int,int> mp[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	Get_Prime();
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i], pos[a[i]]=i;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(auto now:P) {
		int fi=-1;
		for(int i=1;now*i<N;i++) if(pos[now*i]) {
			if(fi==-1) fi=pos[now*i];
			else merge(fi,pos[now*i]);
		}
	}
	for(auto now:P) {
		int fi=-1;
		for(int i=1;now*i<N;i++) if(pos[now*i]) {
			fi=pos[now*i]; break;
		}
		if(fi!=-1) blo[now]=find(fi);
	}
	for(int i=1;i<=n;i++) {
		vector<int> nd;
		nd.push_back(find(i));
		int v=a[i]+1;
		while(v>1) {
			int pri=p[v];
			while(v%pri==0) v/=pri;
			if(blo[pri]) nd.push_back(blo[pri]);
		}
		for(int i=0;i+1<(int)nd.size();i++)
			for(int j=i+1;j<(int)nd.size();j++) mp[nd[i]][nd[j]]=mp[nd[j]][nd[i]]=1;
	}
	for(int i=1,s,t;i<=q;i++) {
		cin>>s>>t;
		int fs=find(s),ft=find(t);
		if(fs==ft) cout<<0<<endl;
		else if(mp[fs][ft]) cout<<1<<endl;
		else cout<<2<<endl;
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

