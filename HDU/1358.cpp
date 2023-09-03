#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,nxt[N];
string s;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int tot=0;
	while(cin>>n) {
		if(!n) return 0;
		cin>>s; s=" "+s;
		for(int i=2;i<=n;i++) {
			int j=nxt[i-1];
			while(s[j+1]!=s[i]&&j) j=nxt[j];
			nxt[i]=(s[j+1]==s[i]? j+1:0);
		}
		cout<<"Test case #"<<(++tot)<<endl; 
		for(int i=2;i<=n;i++) {
			if(i%(i-nxt[i])==0&&i/(i-nxt[i])>1) cout<<i<<" "<<i/(i-nxt[i])<<endl;
		}
		cout<<endl;
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

