#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ls (id<<1)
#define rs (id<<1|1)
const int N=2e5+10;
typedef pair<int,int> PII;
ll read() {
	ll f=1,z=0; char ch=getchar();
	while(ch<'0'||ch>'9') {
		if(ch=='-') f=-1; ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		z=z*10+ch-'0'; ch=getchar();
	}
	return f*z;
}
int n;
ll t,s[4][N<<2];
void Modify(int op,int id,int l,int r,int x,int val) {
	if(l==r) { s[op][id]+=val; return; }
	int mid=(l+r)>>1;
	if(x<=mid) Modify(op,ls,l,mid,x,val);
	else Modify(op,rs,mid+1,r,x,val);
	s[op][id]=s[op][ls]+s[op][rs];
}
ll findl(int id,int l,int r,ll val) {
	if(l==r) return s[1][id];
	int mid=(l+r)>>1;
	if(val>s[0][rs]) return findl(ls,l,mid,val-s[0][rs])+s[1][rs];
	else return findl(rs,mid+1,r,val);
}
ll findr(int id,int l,int r,ll val) {
	if(l==r) return s[3][id];
	int mid=(l+r)>>1;
	if(val>s[2][ls]) return findr(rs,mid+1,r,val-s[2][ls])+s[3][ls];
	else return findr(ls,l,mid,val);
}
ll Query(int op,int id,int l,int r,int x,int y) {
	if(x<=l&&y>=r) return s[op][id];
	int mid=(l+r)>>1;
	if(y<=mid) return Query(op,ls,l,mid,x,y);
	else if(x>mid) return Query(op,rs,mid+1,r,x,y);
	else return Query(op,ls,l,mid,x,y)+Query(op,rs,mid+1,r,x,y);
}
struct node {
	int a,b,id;
}d[N];
bool cmp(node x,node y) { return (x.a==y.a)? x.b<y.b:x.a<y.a; }
bool check(int x,ll val) {
	if(!x) return (val<=t); 
	return (val-findl(1,1,n,x)+findr(1,1,n,x)<=t);
}
int Ans[N],cnt;
//bool spj(ll ans) {
//	ll tim=0,sum=0;
//	for(auto now:Ans) {
//		tim+=m[now].a;
//		if(m[now].b<=Ans.size()) sum++;			
//	}
//	return (sum==ans&&tim<=t);
//}
void solve() {
	n=read(), t=read();
	for(int i=1;i<=n;i++) d[i].a=read(), d[i].b=read(), d[i].id=i;
	for(int i=1;i<=(n<<2);i++) s[0][i]=s[1][i]=s[2][i]=s[3][i]=0;
	sort(d+1,d+n+1,cmp);
	priority_queue<PII,vector<PII>,greater<PII>> q1,q2;
	for(int i=1;i<=n;i++) q2.emplace(d[i].b,i);
	int ans=0, mems;
	ll val=0;
	for(int s=1,tot=0;s<=n;s++) {
		val+=d[s].a;
		if(val>t) break;
		while(q1.size()&&q1.top().first<=s) {
			PII now=q1.top();  q1.pop();
			Modify(0,1,1,n,now.second,-1), Modify(1,1,1,n,now.second,-d[now.second].a);
			tot++;
		}
		if(d[s].b>s) q1.emplace(d[s].b,s), Modify(0,1,1,n,s,1), Modify(1,1,1,n,s,d[s].a);
		else tot++;
		if(d[s].b<=s-1) Modify(2,1,1,n,s,-1), Modify(3,1,1,n,s,-d[s].a);
		while(q2.size()&&q2.top().first<=s) {
			PII now=q2.top(); q2.pop();
			if(now.second>s) Modify(2,1,1,n,now.second,1), Modify(3,1,1,n,now.second,d[now.second].a);
		}
		if(s==n) { if(tot>ans) ans=tot, mems=s; break; }
		int l=0, r=min(Query(0,1,1,n,1,s),Query(2,1,1,n,s+1,n));
		while(l+1<r) {
			int mid=(l+r)>>1;
			check(mid,val);
			if(check(mid,val)) l=mid;
			else r=mid;
		}
		if(check(r,val)) {
			if(tot+r>ans) ans=tot+r, mems=s;
		}
		else if(tot+l>ans) ans=tot+l, mems=s;
	}
	if(ans==0) return printf("0\n0\n\n"), void();
	queue<PII> q;
	int p=mems,cnt=0; ll z=0;
	for(int i=1;i<=mems;i++) z+=d[i].a;
	for(int i=mems+1;i<=n;i++) if(d[i].b<=mems) q.emplace(d[i].a,d[i].id);
	while(p&&d[p].b<=mems) Ans[++cnt]=d[p].id, p--;
	while(q.size()&&z<=t&&p) {
		PII now=q.front();
		z=z-d[p].a+now.first;
		if(z>t) break;
		Ans[++cnt]=now.second, q.pop(), p--;
		while(p&&d[p].b<=mems) Ans[++cnt]=d[p].id, p--;
	}
	for(int i=1;i<=p;i++) Ans[++cnt]=d[i].id;
	printf("%d\n%d\n",ans,cnt);
	for(int i=1;i<=cnt;i++) printf("%d ",Ans[i]);
	puts("");
//	if(!spj(ans)) cout<<"Wrong!\n";
}
int main() {
	freopen("easy.in","r",stdin);
	freopen("easy.out","w",stdout);
	int T=read();
	while(T--) solve();
	return 0;
}