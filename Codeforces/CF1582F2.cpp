#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=9e3+10;
bool mem1;
int n,ap[N],pos[N];
vector<int> l[N];
void solve() {
	cin>>n;
	for(int i=0;i<=9000;i++) l[i].push_back(0), pos[i]=5001;
	pos[0]=0, ap[0]=1;
	for(int i=1,x;i<=n;i++) {
		cin>>x;
		for(auto now:l[x]) {
			int v=now^x;
			ap[v]=1;
			for(int j=x+1;j<pos[v];j++) l[j].push_back(v);
			pos[v]=min(pos[v],x+1);
		}
		l[x].clear();
	}
	vector<int> ans;
	for(int i=0;i<=9000;i++) if(ap[i]) ans.push_back(i);
	cout<<ans.size()<<endl;
	for(auto now:ans) cout<<now<<" ";
	cout<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

