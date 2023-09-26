#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int pd[N];
void solve() {
	string s;
	cin>>s;
	int n=s.size(); s=" "+s;
	int top=0, ans=1, r=1;
	for(int i=1;i<=n;i++) {
		if(s[i]=='+') pd[top+1]=((pd[top]==2)? 2:0), top++;
		if(s[i]=='-') pd[top--]=0, r=min(r,top);
		if(s[i]=='1') {
			if(pd[top]==2) { ans=0; break; }
			pd[top]=1, r=top;
		}
		if(s[i]=='0') {
			if(pd[top]==1||top<=1||top==r) { ans=0; break; }
			pd[top]=2;
		}
	}
	cout<<(ans? "YES":"NO")<<endl;
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
