#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,k,a[N],w[N],c[N],cnt[N];
ll f[N];
void solve() {
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=k;i++) cin>>c[i], w[i]=c[i], f[i]=0;
	for(int i=1,x;i<=k;i++) cin>>x, w[i]-=x;
	ll s=0,mx=0;
	for(int i=1;i<=n;i++) {
		s+=c[a[i]], f[a[i-1]]=mx;
		if(a[i]==a[i-1]) s-=w[a[i]];
		else if(cnt[a[i]]) f[a[i-1]]=max(f[a[i-1]],f[a[i]]+w[a[i]]), mx=max(mx,f[a[i-1]]);
		cnt[a[i]]++;
	}
	mx=0;
	for(int i=1;i<=k;i++) mx=max(mx,f[i]), cnt[i]=0;
	cout<<s-mx<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
