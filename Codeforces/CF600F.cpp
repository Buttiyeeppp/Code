#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int M=2e3+10;
bool mem1;
int a,b,m,u[N],v[N],deg[N],p[N],to[M][M];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>a>>b>>m;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i], v[i]+=a, deg[u[i]]++, deg[v[i]]++;
	int mx=0;
	for(int i=1;i<=a+b;i++) mx=max(mx,deg[i]);
	for(int i=1;i<=m;i++) {
		int c1=1, c2=1;
		while(to[u[i]][c1]) c1++;
		while(to[v[i]][c2]) c2++;
		to[u[i]][c1]=v[i], to[v[i]][c2]=u[i];
		if(c1==c2) continue;
		for(int now=c2,x=v[i];x;x=to[x][now],now^=c1^c2)
			swap(to[x][c1],to[x][c2]);
	}
	cout<<mx<<endl;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=mx;j++) if(to[u[i]][j]==v[i]) cout<<j<<" ";
	cout<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}

