#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,p[N],Q,pos[N],ans[N];
struct node { int r,id; };
vector<node> qr[N],nd[N];
int s[N];
int lowbit(int x) { return x&-x; }
void add(int x,int v) { for(int i=x;i<=n;i+=lowbit(i)) s[i]+=v; }
int qry(int x) {
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=s[i];
	return res;
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i], pos[p[i]]=i, nd[i].clear(), qr[i].clear();
	for(int i=2;i*i<=2*n;i++)
		for(int j=1;j<=n;j++) {
			int k=i*i-j;
			if(k>j&&k<=n) {
				int p1=pos[j], p2=pos[k];
				if(p1>p2) swap(p1,p2);
				nd[p1].push_back({p2,-1});
			}
		}
	cin>>Q;
	for(int i=1,l,r;i<=Q;i++) { cin>>l>>r, qr[l].push_back({r,i}); }
	memset(s,0,sizeof(s));
	for(int i=n;i>=1;i--) {
		for(auto now:nd[i]) add(now.r,1);
		for(auto now:qr[i]) ans[now.id]=qry(now.r);
	}
	for(int i=1;i<=Q;i++) cout<<ans[i]<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
