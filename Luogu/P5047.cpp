#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+1000;
bool mem1;
int n,m,a[N];
ll mv[N],sum[N],sum1[N],ans[N];
struct query {
	int l,r,op,blo,sp;
	friend bool operator<(const query &x,const query &y) {
		return (x.blo==y.blo)? ((x.blo&1)? x.r<y.r:x.r>y.r):x.blo<y.blo;
	}
}q[N];
bool mem2;
int s[N],X[N],tot;
int lowbit(int x) { return x&-x; }
void Add(int x) { for(int i=x;i<=tot;i+=lowbit(i)) s[i]++; }
int Query(int x) {
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=s[i];
	return res;
}
int l=1,r=0;
vector<query> que[N];
void updr(int f,int x,int y,int i) {
	r=(f==1)? y:x;
	mv[i]+=f*(sum[y]-sum[x]);
	que[l-1].push_back({x+1,y,-f,i,0});
}
void updl(int f,int x,int y,int i) {
	l=(f==1)? y:x;
	mv[i]-=f*(sum1[x-1]-sum1[y-1]);
	que[r].push_back({y,x-1,f,i,1});
}
int cnt[N],c[N],cnt1[N],c1[N];
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	int B=1.*n/sqrt(m);
	for(int i=1;i<=n;i++) cin>>a[i], X[i]=a[i];
	sort(X+1,X+n+1); tot=unique(X+1,X+n+1)-X-1;
	for(int i=1;i<=n;i++) a[i]=lower_bound(X+1,X+tot+1,a[i])-X;
	for(int i=1;i<=n;i++) {
		sum[i]=sum[i-1]+i-1-Query(a[i]), sum1[i]=sum1[i-1]+Query(a[i]-1);
		Add(a[i]);
	}
	for(int i=1;i<=m;i++) cin>>q[i].l>>q[i].r, q[i].op=i, q[i].blo=(q[i].l-1)/B;
	sort(q+1,q+m+1);
	for(int i=1;i<=m;i++) {
		if(r<q[i].r) updr(1,r,q[i].r,i);
		if(l>q[i].l) updl(1,l,q[i].l,i);
		if(r>q[i].r) updr(-1,q[i].r,r,i);
		if(l<q[i].l) updl(-1,q[i].l,l,i);
	}
	B=sqrt(n);
	for(int i=1,blo;i<=n;i++) {
		a[i]++; blo=(a[i]-1)/B;
		for(int j=a[i];j<=(blo+1)*B;j++) cnt[j]++;
		for(int j=blo+1;j*B+1<=tot;j++) c[j]++;
		a[i]-=2; blo=(a[i]-1)/B;
		for(int j=blo*B+1;j<=a[i];j++) cnt1[j]++;
		for(int j=0;j<blo;j++) c1[j]++;
		a[i]++;
		for(auto now:que[i]) {
			for(int j=now.l;j<=now.r;j++) {
				if(now.sp) mv[now.blo]+=now.op*(cnt[a[j]]+c[(a[j]-1)/B]);
				else mv[now.blo]+=now.op*(cnt1[a[j]]+c1[(a[j]-1)/B]);
			}
		}
	}
	for(int i=1;i<=m;i++) ans[q[i].op]=ans[q[i-1].op]+mv[i];
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
