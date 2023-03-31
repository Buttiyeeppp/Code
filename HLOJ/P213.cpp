#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N=2e5+10;
int n,m,E,a[N],b[N],v[N];
vector<ll> f;
ll ans=0;
bool check(int l,int x,int r) {
	for(int i=l+1;i<=x;i++) for(int j=m;j>=b[i];j--) f[j]=max(f[j],f[j-b[i]]+v[i]);
	for(int i=x+1;i<r;i++) for(int j=m;j>=a[i];j--) f[j]=max(f[j],f[j-a[i]]+v[i]);
	ll sum=0;
	for(int i=1;i<=m;i++) sum+=f[i];
	return sum>1ll*E*m;
}
void Adda(int l,int r) {
	for(int i=l;i<=r;i++) for(int j=m;j>=a[i];j--) f[j]=max(f[j],f[j-a[i]]+v[i]);
}
void Addb(int l,int r) {
	for(int i=l;i<=r;i++) for(int j=m;j>=b[i];j--) f[j]=max(f[j],f[j-b[i]]+v[i]);
}
void solve(int l,int r,int tl,int tr) {
	int x=(l+r)>>1;
	vector<ll> mem,g=f;
	Adda(l,x-1), Addb(x,min(r,tl-1));
	int head=max(x-1,tl-1), tail=tr+1;
	mem=f;
	while(head+1<tail) {
		int mid=(head+tail)>>1;
		if(check(head,mid,tail)) {
			f=mem;
			Addb(head+1,mid);
			head=mid;
			mem=f;
		}
		else {
			f=mem;
			Adda(mid,tail-1);
			tail=mid;
			mem=f;
		}
	}
	// cerr<<x<<" "<<head<<endl;
	ans+=n-head;
	f=g;
	Addb(x,min(r,tl-1)), Adda(head+1,tr);
	if(l<=x-1) solve(l,x-1,tl,head);
	f=g;
	Adda(l,x), Addb(max(r+1,tl),head-1);
	if(x+1<=r) solve(x+1,r,head,tr);
}
int main() {
	freopen("store.in","r",stdin);
	freopen("store.out","w",stdout);
	scanf("%d%d%d",&n,&m,&E);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) scanf("%d",&b[i]);
	for(int i=1;i<=n;i++) scanf("%d",&v[i]);
	f.resize(m+1);
	solve(1,n,0,n);
	printf("%lld\n",ans);
	return 0;
}