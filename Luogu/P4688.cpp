#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int M=33344;
bool mem1;
int n,m,B,v[N];
struct element { 
	int v,id;
	friend bool operator<(const element &x,const element &y) {
		return x.v<y.v;
	}
}a[N];
int p,cnt,c[N],ans[N];
bitset<N> b[M],now;
struct query {
	int l,r,op,blo;
	friend bool operator<(const query &x,const query &y) {
		return (x.blo==y.blo)? ((x.blo&1)? x.r<y.r:x.r>y.r):x.blo<y.blo;
	}
}q[N];
void add(int x) {
	now[v[x]+c[v[x]]]=1, c[v[x]]++;
}
void del(int x) {
	c[v[x]]--, now[v[x]+c[v[x]]]=0;
}
void solve() {
	if(p>=m) return;
	memset(c,0,sizeof(c)); cnt=0;
	for(int i=p+1;i-p<M&&i<=m&&cnt+3<N;i++) {
		b[i-p].set();
		cnt++; cin>>q[cnt].l>>q[cnt].r; q[cnt].op=i, q[cnt].blo=(q[cnt].l-1)/B, ans[i]+=q[cnt].r-q[cnt].l+1;
		cnt++; cin>>q[cnt].l>>q[cnt].r; q[cnt].op=i, q[cnt].blo=(q[cnt].l-1)/B, ans[i]+=q[cnt].r-q[cnt].l+1;
		cnt++; cin>>q[cnt].l>>q[cnt].r; q[cnt].op=i, q[cnt].blo=(q[cnt].l-1)/B, ans[i]+=q[cnt].r-q[cnt].l+1;
	}
	sort(q+1,q+cnt+1);
	now.reset();
	for(int i=1,l=1,r=0;i<=cnt;i++) {
		while(r<q[i].r) add(++r);
		while(l>q[i].l) add(--l);
		while(r>q[i].r) del(r--);
		while(l<q[i].l) del(l++);
		b[q[i].op-p]&=now;
	}
//	for(int i=1;i<=cnt/3;i++) {
//		cout<<"B["<<i+p<<"] "<<" "<<b[i].count()<<" ";
//		for(int j=1;j<=n;j++) if(b[i][j]) cout<<j<<" ";
//		cout<<endl;
//	}
//	for(int i=1;i<=cnt/3;i++) cout<<"Ans "<<i+p<<" "<<ans[i+p]<<" "<<b[i].count()<<endl;
	for(int i=1;i<=cnt/3;i++) ans[i+p]-=3*b[i].count();
	p+=cnt/3;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	B=1.*n/sqrt(m);
	for(int i=1;i<=n;i++) cin>>a[i].v, a[i].id=i;
	sort(a+1,a+n+1);
	for(int i=1;i<=n;i++) v[a[i].id]=(a[i].v==a[i-1].v)? v[a[i-1].id]:i;
//	cerr<<"V "; for(int i=1;i<=n;i++) cerr<<v[i]<<" "; cerr<<endl;
	solve(), solve(), solve();
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

