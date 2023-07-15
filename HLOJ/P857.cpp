#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using ull=unsigned long long;
using PII=pair<int,int>;
const int N=3e5+10;
const ll Mod=1000007;
bool mem1;
int n,dfn[N],mxdfn[N],tim,sum[N],pos[N*10],ans[N],tot;
ull v[N];
map<string,int> mp;
string s;
vector<int> g[N];
void dfs(int x,int from,string st) {
//	v[x]=(v[from]*27+(s[x-1]-'a'+1))%Mod;
	dfn[x]=++tim;
	st=st+s[x-1];
	if(!mp[st]) mp[st]=++tot;
	v[x]=mp[st];
	for(auto y:g[x]) if(y!=from) dfs(y,x,st);
	mxdfn[x]=tim;
}
int lowbit(int x) { return x&-x; }
void Modify(int x,int v) { for(int i=x;i<=n;i+=lowbit(i)) sum[i]+=v; }
int Query(int x) {
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=sum[i];
	return res;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>s;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	dfs(1,0,"");
	vector<int> nd;
	for(int i=1;i<=n;i++) nd.push_back(i);
	sort(nd.begin(),nd.end(),[](const int x,const int y){return dfn[x]>dfn[y];});
	for(auto i:nd) {
		if(pos[v[i]]) Modify(pos[v[i]],-1);
		pos[v[i]]=dfn[i], Modify(pos[v[i]],1);
		ans[i]=Query(mxdfn[i])-Query(dfn[i]-1);
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

