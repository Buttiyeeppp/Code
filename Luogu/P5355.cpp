#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,a[N],tot,sum[N];
struct query {
	int op,l,r,x,id,blo;
	friend bool operator<(const query &q,const query &p) {
		return (q.blo==p.blo)? ((q.blo&1)? q.r<p.r:q.r>p.r):q.blo<p.blo;
	}
}q[N];
struct qry { 
	int l,r,id;
};
vector<qry> que[N];
int cnt[N],ans[N];
bitset<N> s1,s2;
void add(int x) {
	cnt[a[x]]++, s1[a[x]]=1, s2[100000-a[x]]=1;
}
void del(int x) {
	cnt[a[x]]--;
	if(!cnt[a[x]]) s1[a[x]]=0, s2[100000-a[x]]=0;
}
int pre[N],res[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	int B=1.*n/sqrt(m);
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1,op,l,r,x;i<=m;i++) {
		cin>>op>>l>>r>>x;
		if(op==4&&x<=sqrt(n)+10) que[x].push_back({l,r,i});
		else q[++tot]=query{op,l,r,x,i,(l-1)/B};
	}
	sort(q+1,q+tot+1);
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+(!a[i]);
	for(int i=1,l=1,r=0;i<=tot;i++) {
		while(r<q[i].r) add(++r);
		while(l>q[i].l) add(--l);
		while(r>q[i].r) del(r--);
		while(l<q[i].l) del(l++);
		if(q[i].op==1) ans[q[i].id]=(s1&(s1>>q[i].x)).any();
		if(q[i].op==2) ans[q[i].id]=(s1&(s2>>(100000-q[i].x))).any();
		if(q[i].op==3) {
			if(!q[i].x) ans[q[i].id]=(sum[r]-sum[l-1]!=0);
			else {
				for(int j=1;j<=sqrt(q[i].x)+5;j++) if(q[i].x%j==0&&cnt[j]&&cnt[q[i].x/j]) ans[q[i].id]=1;	
			}
		}
		if(q[i].op==4) {
			for(int j=1;j<=sqrt(n)+5&&1ll*j*q[i].x<N;j++) if(cnt[j]&&cnt[j*q[i].x]) ans[q[i].id]=1;
		}
	}
	for(auto now:que[0])
		ans[now.id]=(sum[now.r]-sum[now.l-1]&&sum[now.r]-sum[now.l-1]!=now.r-now.l+1);
	for(int x=1;x<=sqrt(n)+10;x++) if(que[x].size()) {
		memset(pre,0,sizeof(pre));
		for(int i=1;i<=n;i++) {
			pre[a[i]]=i, res[i]=res[i-1];
			if(1ll*a[i]*x<N) res[i]=max(res[i],min(pre[a[i]],pre[a[i]*x]));
			if(x&&a[i]%x==0) res[i]=max(res[i],min(pre[a[i]],pre[a[i]/x]));
		}
		for(auto now:que[x]) ans[now.id]=(now.l<=res[now.r]);
	}
	for(int i=1;i<=m;i++) cout<<(ans[i]? "yuno":"yumi")<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
