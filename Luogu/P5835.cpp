#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e4+10;
bool mem1;
int n,len,f[N];
ll sum;
struct node {
	int w,x,d;
}a[N];
bool check(int t) {
	int l=1,r=n; ll res=0;
	for(int i=1;i<=n;i++) {
		if(a[i].d==-1&&a[i].x-t<=0) res+=a[l++].w;
		if(a[i].d==1&&a[i].x+t>=len) res+=a[r--].w;
	}
	return (res*2>=sum);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	cin>>n>>len;
	for(int i=1;i<=n;i++) cin>>a[i].w>>a[i].x>>a[i].d, sum+=a[i].w;
	sort(a+1,a+n+1,[](const node q,const node p){ return q.x<p.x; });
	int l=-1,r=0x3f3f3f3f;
	while(l+1<r) {
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid;
	}
	int t=r,tot=0; ll ans=0;
	for(int i=1;i<=n;i++) {
		if(a[i].d==-1) {
			int l=0,r=tot+1,p=a[i].x-2*t;
			while(l+1<r) {
				int mid=(l+r)>>1;
				if(p<=f[mid]) r=mid;
				else l=mid;
			}
			ans+=tot-r+1;
		}
		else f[++tot]=a[i].x;
	}
	cout<<ans<<endl;

	#ifdef xxzx
	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}
