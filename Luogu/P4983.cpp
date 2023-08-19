#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll INF=1e15;
bool mem1;
int n,m,a[N],g[N],q[N];
ll s[N],f[N];
ll K(int x) { return 2*s[x]; }
ll X(int x) { return s[x]; }
ll Y(int x) { return f[x]-2*s[x]+s[x]*s[x]; }
void check(ll x) {
	int l=1, r=1; q[1]=0;
	for(int i=1;i<=n;i++) {
		while(l<r&&K(i)*(X(q[l+1])-X(q[l]))>Y(q[l+1])-Y(q[l])) l++;
		f[i]=Y(q[l])-K(i)*X(q[l])+s[i]*s[i]+2*s[i]+1-x;
		g[i]=g[q[l]]+1;
		while(l<=r&&(Y(i)-Y(q[r]))*(X(q[r])-X(q[r-1]))<(Y(q[r])-Y(q[r-1]))*(X(i)-X(q[r]))) r--;
		q[++r]=i;
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i], s[i]=s[i-1]+a[i];
	ll l=-INF, r=1;
	while(l+1<r) {
		ll mid=(l+r)>>1; check(mid);
		if(g[n]<=m) l=mid;
		else r=mid;
	}
	check(l);
	cout<<f[n]+l*m<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

