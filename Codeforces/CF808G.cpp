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
string s,t;
int nxt[N],f[N],g[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>s>>t;
	int n=s.size(), m=t.size();
	s=" "+s, t=" "+t;
	for(int i=2;i<=m;i++) {
		int j=nxt[i-1];
		while(j&&t[j+1]!=t[i]) j=nxt[j];
		if(t[j+1]==t[i]) nxt[i]=j+1;
	}
	for(int i=m;i<=n;i++) {
		f[i]=f[i-1];
		int pd=1;
		for(int j=i-m+1,p=1;p<=m;j++,p++)
			if(!(s[j]=='?'||s[j]==t[p])) pd=0;
		if(!pd) continue;
		g[i]=f[i-m]+1;
		for(int j=nxt[m];j;j=nxt[j]) {
			g[i]=max(g[i],g[i-(m-j)]+1);
		}
		f[i]=max(f[i],g[i]);
	}
	cout<<f[n]<<endl;

	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

