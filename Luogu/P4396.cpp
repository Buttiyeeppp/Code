#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
//#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,a[N],ap[N],cnt1[N],cnt2[N],blo[N];
PII ans[N];
struct query {
	int l,r,a,b,op;
	friend bool operator<(const query &x,const query &y) {
		if(blo[x.l]==blo[y.l]) return (blo[x.l]&1)? x.r<y.r:x.r>y.r;
		return blo[x.l]<blo[y.l];
	}
}q[N];
void add(int x) {
	x=a[x];
	ap[x]++, cnt1[blo[x]]++;
	if(ap[x]==1) cnt2[blo[x]]++;
}
void del(int x) {
	x=a[x];
	ap[x]--, cnt1[blo[x]]--;
	if(!ap[x]) cnt2[blo[x]]--;
}
bool mem2;
int main() {
	freopen("P4396_1.in","r",stdin);
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	int B=1.*n/sqrt(m)+1, V=0;
	cout<<B<<endl;
	for(int i=1;i<=n;i++) cin>>a[i], blo[i]=((i<=B)? 0:blo[i-B]+1), V=max(V,a[i]);
	for(int i=1;i<=m;i++) cin>>q[i].l>>q[i].r>>q[i].a>>q[i].b, q[i].op=i;
	sort(q+1,q+m+1);
	B=sqrt(V);
	for(int i=1;i<=V;i++) blo[i]=((i<=B)? 0:blo[i-B]+1);
	int l=1, r=0;
	for(int i=1;i<=m;i++) {
		while(l>q[i].l) add(--l);
		while(r<q[i].r) add(++r);
		while(l<q[i].l) del(l++);
		while(r>q[i].r) del(r--);
	cout<<"Here"<<endl;
		int bl=blo[q[i].a], br=blo[q[i].b], ans1=0, ans2=0;
		if(bl==br) {
			for(int j=q[i].a;j<=q[i].b;j++) if(ap[j]) ans1+=ap[j], ans2++;
		}
		else {
			for(int j=bl+1;j<br;i++) ans1+=cnt1[j], ans2+=cnt2[j];
			for(int j=q[i].a;j<=(bl+1)*B;j++) if(ap[j]) ans1+=ap[j], ans2++;
			for(int j=br*B+1;j<=q[i].b;j++) if(ap[j]) ans1+=ap[j], ans2++;
		}
		ans[q[i].op]=make_pair(ans1,ans2);
	}
	for(int i=1;i<=m;i++) cout<<ans[i].first<<" "<<ans[i].second<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

