#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
int f[6000];
bool mem1;
void solve() {
	string a,b;
	cin>>a>>b;
	int n=a.size();
	for(int i=1;i<=n;i++) f[i]=0;
	f[1]=f[0]=1;
	a=" "+a, b=" "+b;
	for(int i=2;i<=n;i++) {
		for(int j=1;j<=i;j++)
			if(a[i]==b[i]&&a[j]==b[j]&&a[i]==a[j]) f[i]|=f[j-1];
	}
	cout<<(f[n]? "YES":"NO")<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
