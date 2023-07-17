#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,h[N],f[N][20][2],w[N][20][2][2];
int dis(int x,int y) { return abs(h[x]-h[y]); }
PII Get(int x,int s) {
	int d0=0,d1=0;
	for(int i=19;i>=0;i--) {
		if(f[x][i][1]&&d0+d1+w[x][i][1][0]+w[x][i][1][1]<=s) {
			d0+=w[x][i][1][0], d1+=w[x][i][1][1], x=f[x][i][1];
		}
	}
	return {d1,d0};
}
int d;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	cin>>n;
	for(int i=1;i<=n;i++) cin>>h[i];
	set<PII> s;
	for(int i=n;i>=1;i--) {
		auto it=s.upper_bound({h[i],0});
		vector<int> nd;
		if(it!=s.end()) {
			nd.push_back((*it).second);
			it++;
			if(it!=s.end()) nd.push_back((*it).second);
			it--;	
		}
		if(it!=s.begin()) nd.push_back((*(--it)).second);
		if(it!=s.begin()) nd.push_back((*(--it)).second);
		d=i;
		sort(nd.begin(),nd.end(),[](const int x,const int y){
			return dis(d,x)<dis(d,y)||(dis(d,x)==dis(d,y)&&h[x]<h[y]);});
		if(nd.size()) {
			if(nd.size()>1) f[i][0][1]=nd[1], w[i][0][1][1]=dis(i,nd[1]);
			f[i][0][0]=nd[0], w[i][0][0][0]=dis(nd[0],i);		
		}
		s.emplace(h[i],i);
	}
//	for(int i=1;i<=n;i++) cerr<<"f "<<i<<" "<<f[i][0][0]<<" "<<f[i][0][1]<<endl;
	for(int j=1;j<19;j++)
		for(int i=1;i<=n;i++) {
			for(int p1=0;p1<=1;p1++) {
				f[i][j][p1]=f[f[i][j-1][p1]][j-1][p1^(j==1)];
				for(int p2=0;p2<=1;p2++)
					w[i][j][p1][p2]=w[i][j-1][p1][p2]+w[f[i][j-1][p1]][j-1][p1^(j==1)][p2];
			}
		}
	int m,p=0; PII ans;
	cin>>m;
	for(int i=1;i<=n;i++) {
		PII now=Get(i,m);
//		cerr<<"Chk "<<i<<" "<<now.first<<" "<<now.second<<" "<<ans.first<<" "<<ans.second<<endl;
		if(!p) p=i,ans=now;
		else if(!now.second) { if(!ans.second&&h[i]>h[p]) p=i,ans=now; }
		else if(1ll*now.first*ans.second<1ll*now.second*ans.first||(1ll*now.first*ans.second==1ll*now.second*ans.first&&h[i]>h[p])) p=i,ans=now;
	}
	cout<<p<<endl;
	cin>>m;
	for(int i=1,s,x;i<=m;i++) {
		cin>>s>>x;
		PII now=Get(s,x);
		cout<<now.first<<" "<<now.second<<endl;
	}
	
	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
