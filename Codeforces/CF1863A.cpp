#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int n,a,q;
string s;
void solve() {
	cin>>n>>a>>q>>s;
	int pd=(a==n),sum=a;
	for(int i=0;i<q;i++) {
		if(s[i]=='+') sum++,a++;
		else a--;
		if(a==n) pd=1;
	}
	if(pd) cout<<"YES"<<endl;
	else if(sum<n) cout<<"NO"<<endl;
	else cout<<"MAYBE"<<endl;
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
