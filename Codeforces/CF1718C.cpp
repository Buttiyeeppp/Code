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
int n,a[N],p[N],q;
vector<int> P;
void Get_Prime() {
	for(int i=2;i<N;i++) {
		if(!p[i]) P.push_back(i);
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			p[i*now]=1;
			if(i%now==0) break;
		}
	}
}
ll d[30][N];
void solve() {
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i];
	vector<ll> v;
	for(auto now:P) {
		if(now>n) break;
		if(n%now==0) v.push_back(n/now);
	}
	multiset<ll> ans;
	for(int i=0;i<v.size();i++)
		for(int j=0;j<=n;j++) d[i][j]=0;
	for(int i=0;i<v.size();i++) {
		for(int j=1;j<=n;j++) d[i][(j-1)%v[i]]+=v[i]*a[j];
		for(int j=0;j<v[i];j++) ans.insert(d[i][j]);
	}
	cout<<*(--ans.end())<<endl;
	for(int i=1,p,x;i<=q;i++) {
		cin>>p>>x;
		for(int i=0;i<v.size();i++) {
			ans.erase(ans.find(d[i][(p-1)%v[i]]));
			d[i][(p-1)%v[i]]+=v[i]*(x-a[p]);
			ans.insert(d[i][(p-1)%v[i]]);
		}
		a[p]=x;
		cout<<*(--ans.end())<<endl;
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	Get_Prime();
	int T; cin>>T;
	while(T--) solve();	
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
