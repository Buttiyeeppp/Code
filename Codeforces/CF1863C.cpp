#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,k,a[N],b[N];
void solve() {
	cin>>n>>k;
	for(int i=0;i<=n;i++) b[i]=0;
	for(int i=1;i<=n;i++) cin>>a[i], b[a[i]]=1;
	for(int i=0;i<=n;i++) if(!b[i]) a[n+1]=i;
	n++;
	int p=n-((k-1)%n+1)+1, s=0;
	while(s<n-1) {
		cout<<a[p]<<" ";
		p++, s++;
		if(p>n) p=1;
	}
	cout<<endl;
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
