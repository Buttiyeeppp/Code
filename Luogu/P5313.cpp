#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using ull=unsigned long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,a[N],tot,ans[N],B;
struct query {
	int l,r,b,id;
}q[N];
vector<query> que[N];
bool cmp(query &x,query &y) {
	int xb=(x.l-1)/B, yb=(y.l-1)/B;
	return (xb==yb)? ((xb&1)? x.r<y.r:x.r>y.r):xb<yb;
}
ull val[65];
bool pd=0;
struct Bitset {
	vector<ull> v;
	int sz;
	bool any() {
		for(int i=0;i<=sz;i++) if(v[i]) return true;
		return false;
	}
	void set1(int x) { v[x>>6]|=(1ull<<(x&63)); }
	void set0(int x) { v[x>>6]&=~(1ull<<(x&63)); }
	void set() { for(int i=0;i<=sz;i++) v[i]=~0ull; }
	void reset() { for(int i=0;i<=sz;i++) v[i]=0; }
	void init(int x,int op) { 
		v.resize((x>>6)+3), sz=(x>>6);
		op? set():reset();
	}
	/*
	Bitset operator&(const Bitset &q)const {
		Bitset res; res.init(sz<<6,0);
		pd=0;
		for(int i=0;i<=sz;i++) {
			res.v[i]=v[i]&q.v[i];
			if(res.v[i]) pd=1;
		}
		return res;
	}
	*/
	void operator &=(const Bitset &q) {
		pd=0;
		for(int i=0;i<=sz;i++) v[i]&=q.v[i], pd|=v[i];
	}
	int mex() {
		for(int i=0;;i++) 
			if(~v[i]) return (i<<6)|__builtin_ctzll(~v[i]);
	}
	void split(int len,Bitset res[]) {
		for(int i=0;i<=N/len+1;i++) res[i].init(len,0);
		int beg=0,p=0,pos=0,i=0; //beg为v[i]剩下的位置的开端，p为更新至res[p]，pos为更新至res[p]的v[pos]处 
		while(i<=sz) {
			if(pos==(len>>6)) { // len&63位
				if(63-beg>=(len&63)) res[p].v[pos]=(v[i]&val[beg+(len&63)])>>beg, beg+=(len&63);
				else res[p].v[pos]=(v[i]>>beg)|((v[i+1]&val[beg+(len&63)-64])<<(64-beg)), beg+=(len&63)-64, i++;
				p++, pos=0;
			}
			else { // 64位 
				if(beg) res[p].v[pos]=(v[i]>>beg)|((v[i+1]&val[beg])<<(64-beg));
				else res[p].v[pos]=v[i];
				i++, pos++;
			}
		}
	}
};
int cnt[N],V;
Bitset now[330],_now,res[N];
void add(int x,int b) {
	int v=a[x]; cnt[v]++;
	if(cnt[v]==1) now[v%b].set1(v/b);
}
void del(int x,int b) {
	int v=a[x]; cnt[v]--;
	if(!cnt[v]) now[v%b].set0(v/b);
}
void _add(int x) {
	int v=a[x]; cnt[v]++;
	if(cnt[v]==1) _now.set1(v);
}
void _del(int x) {
	int v=a[x]; cnt[v]--;
	if(!cnt[v]) _now.set0(v);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	val[1]=1;
	for(int i=2;i<=64;i++) val[i]=val[i-1]|(1ull<<(i-1));
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i], V=max(V,a[i]);
	cin>>m;
	for(int i=1,l,r,b;i<=m;i++) {
		cin>>l>>r>>b;
		if(b<=63) que[b].push_back({l,r,b,i});
		else q[++tot]=query{l,r,b,i};
	}
	for(int i=1;i<=63;i++) if(que[i].size()) {
		B=1.*n/sqrt(que[i].size())+1;
		sort(que[i].begin(),que[i].end(),cmp);
		for(int j=0;j<i;j++) now[j].init(V/i,0);
		int l=1,r=0;
		for(auto nw:que[i]) {
			while(r<nw.r) add(++r,i);
			while(l>nw.l) add(--l,i);
			while(r>nw.r) del(r--,i);
			while(l<nw.l) del(l++,i);
			for(int j=0;j<i;j++) ans[nw.id]=max(ans[nw.id],now[j].mex());
		}
		while(l<=r) del(l++,i);
	}
	B=1.*n/sqrt(tot);
	sort(q+1,q+tot+1,cmp);
	_now.init(V,0);
	for(int i=1,l=1,r=0;i<=tot;i++) {
		while(r<q[i].r) _add(++r);
		while(l>q[i].l) _add(--l);
		while(r>q[i].r) _del(r--);
		while(l<q[i].l) _del(l++);
		_now.split(q[i].b,res);
		Bitset Ans; Ans.init(q[i].b,1);
		for(int j=0;;j++) {
			Ans&=res[j];
			if(!pd) { ans[q[i].id]=j; break; }
		}
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
