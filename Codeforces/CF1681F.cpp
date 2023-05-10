#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
#define ls (id<<1)
#define rs (id<<1|1)
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n;
struct edge {
	int x,y;
};
vector<edge> col[N],eg;
vector<int> t[N<<2];
void Modify(int id,int l,int r,int x,int y,int v) {
	if(x<=l&&y>=r) return t[id].push_back(v), void();
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls,l,mid,x,y,v);
	if(y>mid) Modify(rs,mid+1,r,x,y,v);
}
int fa[N];
int find(int x) {
	if(x==fa[x]) return x;
	else return find(fa[x]);
}
ll sz[N],ans;
void calc(int id,int l,int r) {
	vector<int> mem;
	for(auto i:t[id]) {
        // cout<<"Edge "<<l<<" "<<r<<" "<<eg[i].x<<" "<<eg[i].y<<endl;
		int x=find(eg[i].x), y=find(eg[i].y);
        if(x!=y) {
            if(sz[x]<sz[y]) swap(x,y);
            fa[y]=x, sz[x]+=sz[y];
            mem.push_back(y);
        }
	}
	
	if(l==r) {
		for(auto i:col[l]) {
			int x=find(i.x), y=find(i.y);
            // cout<<i.x<<" "<<i.y<<" "<<x<<" "<<y<<" "<<sz[x]*sz[y]<<endl;
			ans+=sz[x]*sz[y];
		}
	}
	else {
		int mid=(l+r)>>1;
		calc(ls,l,mid), calc(rs,mid+1,r);
	}

	for(int j=mem.size()-1;j>=0;j--) {
        int i=mem[j];
        sz[fa[i]]-=sz[i], fa[i]=i;
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,x,y,c;i<n;i++) {
		cin>>x>>y>>c;
		eg.push_back(edge{x,y});
		col[c].push_back(edge{x,y});
		if(1<=c-1) Modify(1,1,n,1,c-1,i-1);
		if(c+1<=n) Modify(1,1,n,c+1,n,i-1); 
	}
	for(int i=1;i<=n;i++) fa[i]=i, sz[i]=1;
	calc(1,1,n);
    cout<<ans<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}