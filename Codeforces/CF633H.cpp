#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=3e4+10;
int n,q,l[N],r[N],mx[N],cnt[N],Mod,f[N];
ll ans[N];
int read() {
	int f=1, z=0; char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { z=z*10+ch-'0'; ch=getchar(); }
	return f*z;
}
struct node {
	int v,id;
	bool operator<(const node &q)const {
		return v<q.v;
	}
}a[N];
int Add(int x,int y) { return ((x+y>=Mod)?x+y-Mod:x+y); }
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	n=read(), Mod=read();
	for(int i=1;i<=n;i++) a[i].v=read(), a[i].id=i;
	sort(a+1,a+n+1);
	q=read();
	for(int i=1;i<=q;i++) l[i]=read(), r[i]=read();
	f[1]=f[2]=1;
	for(int i=3;i<=n;i++) f[i]=Add(f[i-1],f[i-2]);
//	for(int i=3;i<=n;i++) f[i]=Add(f[i-1],f[i-2]), cerr<<i<<" "<<f[i]<<endl;
	for(int i=1;i<=n;i++) {
		int v=a[i].v%Mod;
		for(int j=1;j<=q;j++) {
			if(a[i].v>mx[j]&&a[i].id>=l[j]&&a[i].id<=r[j]) ans[j]+=f[++cnt[j]]*v, mx[j]=a[i].v;
		}
	}
	for(int i=1;i<=q;i++) cout<<ans[i]%Mod<<endl;
	return 0;
}

