#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,k,cnt;
struct node {
	int a,b,c,sum,ans;
}d[N],nd[N];
bool cmp2(node x,node y) {
	return (x.b==y.b)? x.c<y.c:x.b<y.b;
}
bool cmp1(node x,node y) {
	return (x.a==y.a)? cmp2(x,y):x.a<y.a;
}
int sum[N<<1];
int lowbit(int x) { return x&-x; }
void add(int x,int val) { for(int i=x;i<=k;i+=lowbit(i)) sum[i]+=val; }
int query(int x) {
	int s=0;
	for(int i=x;i;i-=lowbit(i)) s+=sum[i];
	return s;
}
int out[N];
void solve(int l,int r) {
	if(l==r) return;
	int mid=(l+r)>>1;
	solve(l,mid), solve(mid+1,r);
	sort(nd+l,nd+mid+1,cmp2), sort(nd+mid+1,nd+r+1,cmp2);
	int p=l;
	for(int i=mid+1;i<=r;i++) {
		while(p<=mid&&nd[p].b<=nd[i].b) add(nd[p].c,nd[p].sum), p++;
		nd[i].ans+=query(nd[i].c);
	}
	for(int i=l;i<p;i++) add(nd[i].c,-nd[i].sum);
}
int main() {
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d%d%d",&d[i].a,&d[i].b,&d[i].c);
	sort(d+1,d+n+1,cmp1);
	for(int i=1;i<=n;i++) { 
		if(cnt&&d[i].a==nd[cnt].a&&d[i].b==nd[cnt].b&&d[i].c==nd[cnt].c) nd[cnt].sum++;
		else cnt++, nd[cnt]=(node){d[i].a,d[i].b,d[i].c,1,0};
	}
	solve(1,cnt);
	for(int i=1;i<=cnt;i++) out[nd[i].ans+nd[i].sum-1]+=nd[i].sum;
	for(int i=0;i<n;i++) printf("%d\n",out[i]);
	return 0;
}
