#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e2+10;
bool mem1;
int n,m,a[N][N],s[N][N],cnt,sum;
int vis[N],match[N];
vector<int> g[N];
bool dfs(int x) {
	for(auto y:g[x]) {
		if(vis[y]) continue;
		vis[y]=1;
		if(!match[y]||dfs(match[y]))
			return match[y]=x, true;
	}
	return false;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		string s; cin>>s;
		for(int j=1;j<=m;j++) a[i][j]=(s[j-1]=='B');
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) s[i][j]=a[i][j]^a[i+1][j]^a[i][j+1]^a[i+1][j+1], sum+=(s[i][j]&&!(i==n&&j==m));
	for(int i=1;i<n;i++)
		for(int j=1;j<m;j++) {
			if(s[i][j]&&s[i][m]&&s[n][j]) g[i].push_back(j);
		}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) cerr<<s[i][j]<<" ";
		cerr<<endl;
	}
	for(int i=1;i<=n;i++) {
		memset(vis,0,sizeof(vis));
		if(dfs(i)) cnt++;	
	}
	//cnt*2+(sum-cnt*3)
	cout<<sum-cnt+((cnt&1)!=a[n][m])<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}

