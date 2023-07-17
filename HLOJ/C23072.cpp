#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const ll Mod=998244353;
const ll inv2=499122177;
bool mem1;
int n,p[N];
ll f[N],s[N];
int lowbit(int x) { return x&-x; }
void Add(int x,int v) { for(int i=x;i<=n;i+=lowbit(i)) s[i]=(s[i]+v)%Mod; }
int Query(int x) {
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res=(res+s[i])%Mod;
	return res;
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i+n], p[n-i+1]=p[i+n];
	n<<=1;
	for(int i=1;i<=n;i++) f[i]=s[i]=0;
	for(int i=1;i<=n;i++) {
		ll res=Query(p[i]-1)+1;
		f[p[i]]=(f[p[i]]+res)%Mod, Add(p[i],res);
	}
	cout<<Query(n)*inv2%Mod<<endl;
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
