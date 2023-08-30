#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,p,mx,f[N],zb[N],cnt[N];
string st[N],ans;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	mt19937 rd(20080618);
	cin>>n>>m>>p;
	for(int i=1;i<=n;i++) cin>>st[i];
	for(int i=1;i<(1<<p);i++) cnt[i]=cnt[i-(i&-i)]+1;
	int T=80;
	ans.resize(m+2);
	for(int i=1;i<=m;i++) ans[i]='0';
	while(T--) {
		int k=rd()%n+1,tot=0;
		for(int i=1;i<=m;i++)
			if(st[k][i-1]=='1') zb[++tot]=i;
		int u=(1<<tot)-1;
		for(int i=0;i<=u;i++) f[i]=0;
		for(int i=1;i<=n;i++) {
			int s=0;
			for(int j=1;j<=tot;j++)
				if(st[i][zb[j]-1]=='1') s|=(1<<(j-1));
			f[s]++;
		}
		for(int i=0;i<tot;i++)
			for(int s=0;s<=u;s++) if(!((1<<i)&s)) f[s]+=f[s^(1<<i)];
		int p=-1;
		for(int s=1;s<=u;s++) if(f[s]>=(n+1)/2&&cnt[s]>mx) mx=cnt[s], p=s;
		if(~p) {
			for(int i=1;i<=m;i++) ans[i]='0';
			for(int j=1;j<=tot;j++)
				if((1<<(j-1))&p) ans[zb[j]]='1';
		}
	}
	for(int i=1;i<=m;i++) cout<<ans[i];
	cout<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

