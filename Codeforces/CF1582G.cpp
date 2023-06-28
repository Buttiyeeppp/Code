#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PIL=pair<int,ll>;
const int N=1e6+10;
bool mem1;
int n,a[N],prime[N],l[N],top;
vector<int> P;
string b;
void init() {
	for(int i=2;i<N;i++) {
		if(!prime[i]) P.push_back(i), prime[i]=i;
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			prime[now*i]=now;
			if(i%now==0) break;
		}
	}
}
vector<int> st[N];
PIL sta[N];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i], l[i]=i;
	cin>>b;
	for(int i=1;i<=n;i++) {
		while(a[i]!=1) {
//			cout<<i<<" "<<a[i]<<" "<<prime[a[i]]<<endl;
			int p=prime[a[i]]; a[i]/=p;
			if(b[i-1]=='*') st[p].push_back(i);
			else {
				if(st[p].size()) {
					l[i]=min(l[i],st[p].back());
					st[p].pop_back();
				}
				else l[i]=0;
			}
		}
	}
	ll ans=0; top=0;
	for(int i=n;i>=1;i--) {
		ll now=1;
		while(top&&sta[top].first>=l[i]) 
			now+=sta[top].second, top--;
		sta[++top]=make_pair(l[i],now);
		if(i==l[i]) ans+=now;
	}
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	init();
	solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

