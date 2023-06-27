#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,k,a[N];
ll ans[N],sum[N],cnt[N],delta[N];
struct query {
	int l,r,op,blo;
	friend bool operator<(const query &x,const query &y) {
		return (x.blo==y.blo)? ((x.blo&1)? x.r<y.r:x.r>y.r):x.blo<y.blo;
	}
}q[N];
vector<int> num;
vector<query> que[N];
int l=1,r=0;
void updr(int f,int i) {
	int nr=r,qr=q[i].r;
	if(nr>qr) swap(nr,qr);
	delta[i]+=f*(sum[qr]-sum[nr]);
	que[l-1].push_back({nr+1,qr,-f,i});
	r=q[i].r;
}
void updl(int f,int i) {
	int nl=l,ql=q[i].l;
	if(nl<ql) swap(nl,ql);
	delta[i]-=f*(sum[nl-1]-sum[ql-1]); //-(!k)*(nl-ql)
	que[r].push_back({ql,nl-1,f,i});
	l=q[i].l;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>k;
	int B=1.*n/sqrt(m);
	for(int i=0;i<16384;i++)
		if(__builtin_popcount(i)==k) num.push_back(i);
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		sum[i]=sum[i-1]+cnt[a[i]];
		for(auto now:num) cnt[now^a[i]]++;
	}
//	cerr<<"Sum "; for(int i=1;i<=n;i++) cerr<<sum[i]<<" "; cerr<<endl;
	for(int i=1;i<=m;i++) cin>>q[i].l>>q[i].r, q[i].op=i, q[i].blo=(q[i].l-1)/B;
	sort(q+1,q+m+1);
//	for(int i=1;i<=m;i++) cerr<<"Q "<<q[i].l<<" "<<q[i].r<<" "<<q[i].op<<endl;
	for(int i=1;i<=m;i++) {
		if(r<q[i].r) updr(1,i);
		if(l>q[i].l) updl(1,i);
		if(r>q[i].r) updr(-1,i);
		if(l<q[i].l) updl(-1,i);
	}
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++) {
		for(auto now:num) cnt[now^a[i]]++;
		for(auto now:que[i]) {
			for(int j=now.l;j<=now.r;j++) delta[now.blo]+=now.op*(cnt[a[j]]-(!k&&j<=i));
		}
	}
	for(int i=1;i<=m;i++) ans[q[i].op]=ans[q[i-1].op]+delta[i];
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
