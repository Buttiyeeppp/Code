#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n,m,a[N],nd[N];
inline int read() {
	int f=1,z=0; char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { z=z*10+ch-'0'; ch=getchar(); }
	return f*z;
}
inline void write(ll x) {
	if(x<0) putchar('-'), x=-x;
	if(x>9) write(x/10);
	putchar((x%10)+'0');
}
struct query {
	int l,r,blo,op;
	friend bool operator<(const query &x,const query &y) {
		return (x.blo==y.blo)? x.r>y.r:x.blo<y.blo;
	}
}q[N];
ll ans,Ans[N];
inline int abs(int x,int y) { return (x>=y? x-y:y-x); }
struct chain {
	int pre[N],nxt[N],st[N],top;
	chain() { memset(pre,0,sizeof(pre)), memset(nxt,0,sizeof(nxt)); }
	ll del(int x) {
		st[++top]=x;
		ll res=0;
		if(pre[x]) res-=abs(pre[x]-x);
		if(nxt[x]) res-=abs(nxt[x]-x);
		if(pre[x]&&nxt[x]) res+=abs(nxt[x]-pre[x]);
		pre[nxt[x]]=pre[x], nxt[pre[x]]=nxt[x];
		return res;
	}
	void back() {
		int x=st[top--];
		nxt[pre[x]]=x, pre[nxt[x]]=x;
		return;
	}
}ch;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	n=read(), m=read();
	int B=1.*n/sqrt(m);
	for(int i=1;i<=n;i++) a[i]=read(), nd[i]=i;
	for(int i=1;i<=m;i++) q[i].l=read(), q[i].r=read(), q[i].blo=(q[i].l-1)/B, q[i].op=i;
	sort(q+1,q+m+1);
	sort(nd+1,nd+n+1,[](const int &x,const int &y){ return a[x]<a[y]; });
	for(int i=2;i<=n;i++)
		ans+=abs(nd[i]-nd[i-1]), ch.nxt[nd[i-1]]=nd[i], ch.pre[nd[i]]=nd[i-1];
	int l=1,r; ll now;
	for(int i=1;i<=m;i++) {
		if(i==1||q[i].blo!=q[i-1].blo) {
			while(ch.top) ch.back();
			while(l<q[i].blo*B+1) ans+=ch.del(l++);
			now=ans, ch.top=0, r=n;
		}
		while(r>q[i].r) now+=ch.del(r--);
		ll mem=now;
		for(int j=q[i].blo*B+1;j<q[i].l;j++) now+=ch.del(j);
		Ans[q[i].op]=now;
		for(int j=q[i].blo*B+1;j<q[i].l;j++) ch.back();
		now=mem;
	}
	for(int i=1;i<=m;i++) write(Ans[i]), putchar('\n');
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
