#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int n,Q;
string s;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>Q>>s;
	set<int> g;
	for(int i=1;i<=n;i++) if((i&1)!=(s[i-1]=='(')) g.insert(i), cerr<<i;
	while(Q--) {
		int x; cin>>x;
		if(g.count(x)) g.erase(x);
		else g.insert(x);
		if(n%2) cout<<"NO\n";
		else if(g.size()&&(((*g.begin())%2==1)||((*g.rbegin())%2==0))) cout<<"NO\n";
		else cout<<"YES\n";
	}
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

