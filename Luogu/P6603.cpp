#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e3+10;
const int M=4100;
bool mem1;
int n,m,l,a[N],f[N][M],vis[N],top[M];
vector<int> g[N];
void Max(int &x,int y) {
	return x=(x>y? x:y), void();
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>l;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y, g[x].push_back(y);
	}
	for(int s=0;s<(1<<l);s++) {
		for(int i=0;i<l;i++) if((1<<i)&s) top[s]=i+1;
	}
	f[1][0]=a[1];
	for(int i=1;i<=n;i++)
		for(int s=0;s<(1<<l);s++) {
			int j=i+top[s];
			if(j>n) continue;
			for(auto to:g[i]) {
				vis[to]=1;
				if(to<=j) Max(f[to][s>>(to-i)],f[i][s]+(((s>>(to-i-1))&1)^1)*a[to]);
				else if(to-j<=l) Max(f[j][1<<(to-j-1)],f[i][s]+a[to]);
			}
			for(auto to:g[j]) {
				if(to-i<=l) Max(f[i][s|(1<<(to-i-1))],f[i][s]+a[to]);
				if(vis[to]) Max(f[to][0],f[i][s]+a[to]);
			}
			for(auto to:g[i]) vis[to]=0;
		}
	cout<<f[n][0]<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

