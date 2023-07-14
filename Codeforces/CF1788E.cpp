#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,a[N],f[N],mx[N],tot;
ll s[N],x[N];
int lowbit(int x) { return x&-x; }
void Modify(int x,int v) { for(int i=x;i<=tot;i+=lowbit(i)) mx[i]=max(mx[i],v); }
int Qry(int x) {
	int res=INT_MIN;
	for(int i=x;i;i-=lowbit(i)) res=max(res,mx[i]);
	return res;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i], s[i]=s[i-1]+a[i], x[i]=s[i];
	sort(x+1,x+n+1); tot=unique(x+1,x+n+1)-x-1;
	memset(mx,-0x3f,sizeof(mx));
	for(int i=1;i<=n;i++) {
		int u=lower_bound(x+1,x+tot+1,s[i])-x;
		f[i]=max(f[i-1],Qry(u)+i);
		if(s[i]>=0) f[i]=max(f[i],i);
		Modify(u,f[i]-i);
	}
	cout<<f[n]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

