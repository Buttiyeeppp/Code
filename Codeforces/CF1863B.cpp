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
int n,a[N],p[N];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i], p[a[i]]=i;
	int v=1, ans=0;
	while(v<=n) {
		int pos=-1;
		while(v<=n&&p[v]>pos) {
			pos=p[v], v++;
		}
		ans++;
	}
	cout<<ans-1<<endl;
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
