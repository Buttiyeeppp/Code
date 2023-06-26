#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+7;
bool mem1;
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
ll f[30];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	string s;
	cin>>s;
	int n=s.size();
	ll inv2=Pow(2,Mod-2), sum=0;
	for(int i=0;i<n;i++) {
		ll mem=f[s[i]-'a'];
		f[s[i]-'a']=inv2*(f[s[i]-'a']+sum+1)%Mod;	
		sum=(sum-mem+f[s[i]-'a']+Mod)%Mod;
	}
	cout<<sum*Pow(2,n)%Mod<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
