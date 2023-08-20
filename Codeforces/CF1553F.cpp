#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
ll n,s1[N],s2[N];
int lowbit(int x) { return x&-x; }
ll Qry(ll s[],int x) {
	if(x>=N) x=N-1;
	ll res=0;
	for(int i=x;i;i-=lowbit(i)) res+=s[i];
	return res;
}
void Add(ll s[],int x,int val) {
	for(int i=x;i<N;i+=lowbit(i)) s[i]+=val;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	ll ans=0,s=0;
	for(int i=1;i<=n;i++) {
		ll x; cin>>x;
		ans+=s, s+=x;
		for(int j=1;j*x<=300000;j++) ans-=x*j*(Qry(s1,x*(j+1)-1)-Qry(s1,x*j-1));
		Add(s1,x,1);
		ans+=x*(i-1)-Qry(s2,x);
		for(int j=1;j*x<=300000;j++) Add(s2,j*x,x);
		cout<<ans<<" ";
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

