#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
bool mem1;
int n,m;
int fx[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
string a[N];
struct node {
	int xa,ya,xb,yb;
};
bool in(int x,int y) {
	return (x>=1&&x<=n&&y>=1&&y<=m);
}
void solve() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i], a[i]=" "+a[i];
	vector<vector<vector<vector<int>>>> f;
	f.resize(n+4);
	for(int i=0;i<=n+1;i++) {
		f[i].resize(m+4);
		for(int j=0;j<=m+1;j++) {
			f[i][j].resize(n+4);
			for(int k=0;k<=n+1;k++) {
				f[i][j][k].resize(m+4);
			}
		}	
	}
//	for(int i=1;i<=n;i++)
//		for(int j=1;j<=m;j++)
//			for(int k=0;k<=n+1;k++)
//				for(int l=0;l<=m+1;l++) f[i][j][k][l]=0;
//	return;
	queue<node> q;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)  if(a[i][j]=='.'){
			for(int k=0;k<=n+1;k++)
				for(int l=0;l<=m+1;l++) if(k<1||k>n||l<1||l>m||a[k][l]!='.') {
					f[i][j][k][l]=1;
					q.push({i,j,k,l});
				}
		}
	while(q.size()) {
		node x=q.front(); q.pop();
		for(int op=0;op<4;op++) {
			int nxa=x.xa+fx[op][0], nya=x.ya+fx[op][1];
			int nxb=x.xb+fx[op][0], nyb=x.yb+fx[op][1];
			if(in(nxa,nya)&&in(nxb,nyb)&&!f[nxa][nya][nxb][nyb]&&a[nxa][nya]=='.') {
				f[nxa][nya][nxb][nyb]=1;
				q.push({nxa,nya,nxb,nyb});
			}
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) if(a[i][j]=='.') {
			int pd=1;
			for(int k=1;k<=n;k++)
				for(int l=1;l<=m;l++) if(a[k][l]=='.'&&(k!=i||l!=j)) pd&=f[i][j][k][l];
			ans+=pd;
		}
	cout<<ans<<endl;
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
/*
4
2 5
.OO..
O..O.

1 3
O.O

1 3
.O.

2 3
OOO
OOO
*/
