#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const int M=22;
const ll Mod=998244353; 
bool mem1;
int d,n,m,l[N],p[N];
ll f[M][M],mem[M][M],g[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>d>>n>>m;
	for(int i=1;i<=n;i++) cin>>l[i];
	for(int i=1;i<=m;i++) cin>>p[i];
	sort(l+1,l+n+1), sort(p+1,p+m+1);
	p[0]=-1e7, p[m+1]=1e7;
	for(int i=0;i<=m+1;i++)
		for(int j=i+1;j<=m+1;j++) {
			f[i][j]=1;
			for(int k=1;k<=n;k++)
				if(p[i]<=l[k]&&l[k]<=p[j]) f[i][j]=f[i][j]*min({l[k]-p[i],p[j]-l[k],d+1})%Mod;
			mem[i][j]=f[i][j];
		}
	int q; cin>>q;
	for(int i=1,x;i<=q;i++) {
		cin>>x;
		for(int i=0;i<=m+1;i++)
			for(int j=i+1;j<=m+1;j++) {
				f[i][j]=mem[i][j];
				if(p[i]<=x&&x<=p[j]) f[i][j]=f[i][j]*min({x-p[i],p[j]-x,d+1})%Mod;
			}
		g[0]=-1;
		for(int i=1;i<=m+1;i++) {
			g[i]=0;
			for(int j=0;j<i;j++) g[i]=(g[i]-g[j]*f[j][i]%Mod+Mod)%Mod;
		}
		cout<<g[m+1]<<endl;
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
