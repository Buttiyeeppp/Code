#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
bool mem1;
ll n,a[N],f[N][N],g[N][N];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int len=1;len<=n;len++)
		for(int l=1;l+len-1<=n;l++) {
			int r=l+len-1;
			if(g[l+1][r]>a[r]) f[l][r]=1;
			else f[l][r]=a[r]-g[l+1][r]+f[l][r-1]+1;
			if(f[l][r-1]>a[l]) g[l][r]=1;
			else g[l][r]=a[l]-f[l][r-1]+g[l+1][r]+1;
		}
	cout<<((f[1][n]>a[1])? "Second":"First")<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);

	memset(f,0x3f,sizeof(f)), memset(g,0x3f,sizeof(g));
	int T; cin>>T;
    while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time "<<clo<<"MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}