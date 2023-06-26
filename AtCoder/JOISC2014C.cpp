#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,v[N];
ll X[N],cnt[N],tot[N],Ans[N];
struct query {
	int l,r,bl,op;
	friend bool operator<(const query &x,const query &y) {
		return (x.bl==y.bl)? x.r<y.r:x.bl<y.bl;
	}
}q[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	int B=1.*n/sqrt(m);
	for(int i=1;i<=n;i++) cin>>v[i], X[i]=v[i];
	sort(X+1,X+n+1); int tot1=unique(X+1,X+n+1)-X-1;
	for(int i=1;i<=n;i++) v[i]=lower_bound(X+1,X+tot1+1,v[i])-X;
	for(int i=1;i<=m;i++) cin>>q[i].l>>q[i].r, q[i].bl=(q[i].l-1)/B, q[i].op=i;
	sort(q+1,q+m+1);
	ll r,ans,mem;
	for(int i=1;i<=m;i++) {
		if(i==1||q[i].bl!=q[i-1].bl) {
			if(i!=1) for(int j=(q[i-1].bl+1)*B+1;j<=r;j++) cnt[v[j]]=0;
			r=(q[i].bl+1)*B, mem=-1;
		}
		if(q[i].bl==(q[i].r-1)/B) {
			ans=-1;
			for(int j=q[i].l;j<=q[i].r;j++) {
				tot[v[j]]++;
				if(ans==-1||X[v[j]]*tot[v[j]]>ans) ans=X[v[j]]*tot[v[j]];
			}
			Ans[q[i].op]=ans;
			for(int j=q[i].l;j<=q[i].r;j++) tot[v[j]]--;
			continue;
		}
		while(r<q[i].r) {
			r++, cnt[v[r]]++;
			if(mem==-1||X[v[r]]*cnt[v[r]]>mem) mem=X[v[r]]*cnt[v[r]];
		}
		ans=mem;
		for(int j=q[i].l;j<=(q[i].bl+1)*B;j++) {
			cnt[v[j]]++;
			if(ans==-1||X[v[j]]*cnt[v[j]]>ans) ans=X[v[j]]*cnt[v[j]];
		}
		Ans[q[i].op]=ans;
		for(int j=q[i].l;j<=(q[i].bl+1)*B;j++) cnt[v[j]]--;
	}
	for(int i=1;i<=m;i++) cout<<Ans[i]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
