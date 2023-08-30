#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
void solve() {
	int n;
	string s;
	cin>>n>>s;
	int cnt=0,pd=0;
	for(int i=0;i<n;i++) if(s[i]=='0') cnt++;
	for(int i=0;i<=n/2;i++) if(s[i]!=s[n-i-1]) pd++;
	if(!cnt) return cout<<"DRAW"<<endl, void();
	if(!pd) return cout<<(((cnt&1)&&cnt>1)? "ALICE":"BOB")<<endl, void();
	cout<<((s[n/2]=='0'&&cnt==2&&(n&1))? "DRAW":"ALICE")<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

