#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e4+10;
bool mem1;
int n,a[N];
vector<int> v[4];
vector<PII> ans;
void move(int x,int y) {
	ans.emplace_back(x,y);
	v[y].push_back(v[x].back());
	v[x].pop_back();
}
void solve(int l,int r,int x,int z,int op) {
	int y;
	for(y=1;y<=3;y++) if(x!=y&&z!=y) break;
	if(l==r) return move(x,z), void();
	int mid=(l+r)>>1;
	if(!op) {
		for(int i=l;i<=r;i++) {
			if(v[x].back()>mid) move(x,y);
			else move(x,z);
		}
		solve(l,mid,z,x,op^1), solve(mid+1,r,y,z,op);
		for(int i=l;i<=mid;i++) move(x,z);
	}
	else {
		for(int i=l;i<=r;i++) {
			if(v[x].back()>mid) move(x,z);
			else move(x,y);
		}
		solve(mid+1,r,z,x,op^1), solve(l,mid,y,z,op);
		for(int i=mid+1;i<=r;i++) move(x,z);
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,x;i<=n;i++) cin>>x, v[1].push_back(x);
	reverse(v[1].begin(),v[1].end());
	solve(1,n,1,3,0);
	cout<<ans.size()<<endl;
	for(auto now:ans) cout<<(char)('A'+now.first-1)<<" "<<(char)('A'+now.second-1)<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

