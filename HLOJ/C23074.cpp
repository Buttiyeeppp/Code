#include<bits/stdc++.h> //30pts
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=5e3+10;
bool mem1;
int a[N],b[N],ls[N],rs[N],f[N][N],Mod,n;
void dfs(int x) {
	if(ls[x]) dfs(ls[x]);
	if(rs[x]) dfs(rs[x]);
	int mn=INT_MAX;
	for(int i=0;i<Mod;i++)
		f[x][i]=f[ls[x]][i]+f[rs[x]][i]+((a[x]+i)%Mod<(b[x]+i)%Mod), mn=min(mn,f[x][i]);
	for(int i=0;i<Mod;i++) f[x][i]=min(f[x][i],mn+1);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>Mod;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i]>>ls[i]>>rs[i];
	dfs(1);
	cout<<f[1][0]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
/*
5 5
4 1 2 0
1 0 3 0
1 2 4 5
0 2 0 0
2 4 0 0
*/
