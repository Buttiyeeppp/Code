#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
#define ls (id<<1)
#define rs (id<<1|1)
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int M=2.5e6;
const int B=7.5e6;
bool mem1;
int n,q,a[N],b[N],c[N],d[N],ans[N];
int head[35000000],tot;
struct Edge {
	int nxt,to;
}eg[B];
void Add(int x,int y) { eg[++tot]=Edge{head[x],y}, head[x]=tot; }
void Add_Edge(int id,int l,int r,int x) {
	Add(id,x);
	if(l==r) return;
	int mid=(l+r)>>1;
	c[abs(x)]<=mid? Add_Edge(ls,l,mid,x):Add_Edge(rs,mid+1,r,x);
}
int sz[M],ch[M][2],cnt;
void insert(int x) {
	int p=1;
	for(int i=(1<<23);i;i>>=1) {
		bool op=(x&i);
		if(!ch[p][op]) ch[p][op]=++cnt, sz[cnt]=ch[cnt][0]=ch[cnt][1]=0;
		p=ch[p][op], sz[p]++;
	}
}
int Query(int c,int d) {
	int p=1,res=0;
	for(int i=(1<<23);i;i>>=1) {
		bool op=(c&i);
		if(d&i) res+=sz[ch[p][op]], p=ch[p][op^1];
		else p=ch[p][op];
	}
	return res+sz[p];
}
vector<int> qr[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>q;
	for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
	for(int i=1,l,r;i<=q;i++) 
		cin>>l>>r>>c[i]>>d[i], qr[l-1].push_back(-i), qr[r].push_back(i);
	for(int i=n;i>=1;i--) {
		for(auto now:qr[i]) Add_Edge(1,0,(1<<24)-1,now);
		int k=1;
		for(int j=(1<<23);j;j>>=1) {
			k<<=1, k^=(bool)(a[i]&j);
			if(b[i]&j) {
				Add(k,i+q);
				k^=1;
			}
		}
		Add(k,i+q);
	}
	for(int i=0;i<(1<<25);i++) {
		cnt=1, ch[1][0]=ch[1][1]=0;
		for(int u=head[i];u;u=eg[u].nxt) {
			int to=eg[u].to;
			if(to<0) ans[-to]-=Query(c[-to],d[-to]);
			else if(to<=q) ans[to]+=Query(c[to],d[to]);
			else insert(a[to-q]);
		}
	}
	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
