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
int n,m,k,a[N],p[N],b[N],f[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	ll ans=0;
	int B=450;
	for(int i=1;i<n;i++) f[i]=abs(a[i]-a[i+1]), ans=max(ans,(2>=k? (ll)f[i]:0ll));
	for(int len=3;len<=B;len++) {
		for(int i=1;i+len-1<=n;i++)
			f[i]=min({f[i],f[i+1],abs(a[i]-a[i+len-1])}), ans=max(ans,(len>=k? 1ll*f[i]*(len-1):0ll));
	}
	for(int v=0;v<=B;v++) {
		for(int i=1;i<=n;i++) p[a[i]]=0;
		for(int i=1,l=0;i<=n;i++) {
			if(a[i]-v>=0&&p[a[i]-v]) b[i]=max(b[i],p[a[i]-v]);
			if(a[i]+v<N&&p[a[i]+v]) b[i]=max(b[i],p[a[i]+v]);
			l=max(l,b[i]), p[a[i]]=i;
			ans=max(ans,(i-l>=k? 1ll*(v+1)*(i-l-1):0ll));
		}
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

