#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,a[N],l[N],r[N];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	l[1]=r[n]=1;
	for(int i=2;i<=n;i++) l[i]=l[i-1]+(a[i]>=a[i-1]);
	for(int i=n-1;i>=1;i--) r[i]=r[i+1]+(a[i]>=a[i+1]);
	int ans=l[n];
	for(int i=0;i<n;i++) ans=min(ans,l[i]+r[i+1]-1);
	cout<<ans<<endl;
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
