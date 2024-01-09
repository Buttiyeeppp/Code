#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
bool mem1;
ll n,m,v[N],a[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);

	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>v[i];
	ll res[2]={0,0};
	for(int s=2;s<=2*m;s++) {
		for(int i=1;i<=n;i++) a[i]=v[i]%s;
		a[n+1]=0, a[n+2]=s-1;
		sort(a+1,a+n+3);
		for(int i=1;i<=n+1;i++) {
			ll l=a[i]+1, r=min(a[i+1],m);
			if((n+1-i)%2) l=max(l,a[n]/2+1);
			else l=max(l,a[n+1]/2+1);
			l=max(l,s-r), r=min(r,s-l);
			if(l<=r) res[(n+1-i)%2]+=r-l+1;
		}

	}
	ll c=(m*m-res[0]-res[1])/2;
	cout<<c<<" "<<c<<" "<<res[1]<<" "<<res[0]<<endl;

	#ifdef xxzx
	cerr<<"Time: "<<clo<<"MS"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}