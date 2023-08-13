#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define xxzx
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
bool mem1;
int n,vis[N],mn[N],c[N],a[N][40];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) {
		cin>>c[i];
		for(int j=1,x;j<=c[i];j++) cin>>x, a[i][x]=1;
	}
	int x,mn=INT_MAX; cin>>x;
	for(int i=1;i<=n;i++) if(a[i][x]) mn=min(mn,c[i]);
	vector<int> nd;
	for(int i=1;i<=n;i++) if(a[i][x]&&c[i]==mn) nd.push_back(i);
	cout<<nd.size()<<endl;
	for(auto now:nd) cout<<now<<" "; cout<<endl; 
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

