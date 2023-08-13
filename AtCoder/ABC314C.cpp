#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define xxzx
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,c[N],p[N];
vector<int> nd[N];
string s;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>s;
	for(int i=0;i<n;i++) cin>>c[i], nd[c[i]].push_back(i);
	for(int i=1;i<=m;i++) p[i]=-1;
	for(int i=0;i<n;i++) {
		int col=c[i];
		if(p[col]==-1) cout<<s[nd[col].back()];
		else cout<<s[nd[col][p[col]]];
		p[col]++;
	}
	
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

