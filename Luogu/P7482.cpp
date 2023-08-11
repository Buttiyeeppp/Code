#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll Mod=1e9+7;
bool mem1;
int n,v[N];
ll f[N][2],g[N][2],ans,pf[N],pg[N];
bool cmd(int x,int y) {
	return f[x][0]-g[x][0]<f[y][0]-g[y][0];
}
void solve(int l,int r) {
	if(l==r) return ans=(ans+v[l])%Mod, void();
	int mid=(l+r)>>1;
	solve(l,mid), solve(mid+1,r);
	for(int i=l;i<=r;i++) f[i][0]=f[i][1]=g[i][0]=g[i][1]=0;
	f[mid][1]=v[mid];
	for(int i=mid-1;i>=l;i--) {
		f[i][1]=f[i+1][0]+v[i], g[i][1]=g[i+1][0]+v[i];;
		f[i][0]=max(f[i+1][0],f[i+1][1]), g[i][0]=max(g[i+1][0],g[i+1][1]);
	}
	f[mid+1][1]=v[mid+1];
	for(int i=mid+2;i<=r;i++) {
		f[i][1]=f[i-1][0]+v[i], g[i][1]=g[i-1][0]+v[i];;
		f[i][0]=max(f[i-1][0],f[i-1][1]), g[i][0]=max(g[i-1][0],g[i-1][1]);
	}
	for(int i=l;i<=r;i++) f[i][0]=max(f[i][0],f[i][1]), g[i][0]=max(g[i][0],g[i][1]);
	vector<int> lft,rgt;
	for(int i=l;i<=mid;i++) lft.push_back(i);
	for(int i=mid+1;i<=r;i++) rgt.push_back(i);
	sort(lft.begin(),lft.end(),cmd), sort(rgt.begin(),rgt.end(),cmd);
	pf[0]=f[rgt[0]][0], pg[0]=g[rgt[0]][0];
	for(int i=1;i<rgt.size();i++)
		pf[i]=pf[i-1]+f[rgt[i]][0], pg[i]=pg[i-1]+g[rgt[i]][0];
//	cerr<<"Rgt ";
//	for(auto now:rgt) cerr<<now<<" "; cerr<<endl;
//	for(int i=l;i<=r;i++) cerr<<f[i][0]<<" "; cerr<<endl;
//	for(int i=l;i<=r;i++) cerr<<g[i][0]<<" "; cerr<<endl;
	int p=-1;
	for(int i=0;i<lft.size();i++) {
		while(p+1<rgt.size()&&f[lft[i]][0]-g[lft[i]][0]>=f[rgt[p+1]][0]-g[rgt[p+1]][0]) p++;
		if(p>=0) ans=(ans+f[lft[i]][0]%Mod*(p+1)+pg[p])%Mod;
		if(p+1<rgt.size()) ans=(ans+g[lft[i]][0]%Mod*(rgt.size()-1-p)+pf[rgt.size()-1]-(p!=-1? pf[p]:0))%Mod;
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>v[i];
	solve(1,n);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
