#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1.5e3+10;
bool mem1;
int n,k,c[N][N],sum[N];
bool cnt[N*N];
struct node { int x,y; };
vector<node> d[N][N];
node nd;
int dis(node a,node b) { return max(a.x-b.x,a.y-b.y); }
bool cmp(node a,node b) { return dis(nd,a)<dis(nd,b); }
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) cin>>c[i][j];
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			nd={i,j};
			vector<node> res; res.push_back(nd);
			if(i>1) for(auto now:d[i-1][j]) res.push_back(node{now.x,now.y});
			if(j>1) for(auto now:d[i][j-1]) res.push_back(node{now.x,now.y});
			if(i>1&&j>1) for(auto now:d[i-1][j-1]) res.push_back(node{now.x,now.y});
			sort(res.begin(),res.end(),cmp);
			int l=INT_MAX;
			for(auto now:res) {
				if(cnt[c[now.x][now.y]]) continue;
				cnt[c[now.x][now.y]]=1;
				d[i][j].push_back(now);
				if(d[i][j].size()>k) { l=dis(nd,now); break; }
			}
			for(auto now:res) cnt[c[now.x][now.y]]=0;
			l=min({l,i,j});
			sum[1]++, sum[l+1]--;
			d[i-1][j-1].clear();
		}
	}
	for(int i=1;i<=n;i++) sum[i]+=sum[i-1], cout<<sum[i]<<endl;
		
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
