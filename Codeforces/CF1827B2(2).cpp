#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=5e6+10;
bool mem1;
int n,a[N],st[N],top,tot;
struct query {
	int i,j,c;
}q[N];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	ll ans=0; top=tot=0;
	for(int i=1;i<=n;i++) {
		while(top&&a[st[top]]<a[i])
			q[++tot]=query{i,st[top],st[top]-st[top-1]}, top--;
		if(top) ans+=1ll*st[top]*(n-i+1);
		st[++top]=i;
	}
	top=0;
	for(int i=n,p=tot;i>=1;i--) {
		while(top&&a[st[top]]>a[i]) top--;
		st[++top]=i;
		while(p&&q[p].i==i) {
			while(top&&a[st[top]]>a[q[p].j]) top--;
			if(top) ans+=1ll*q[p].c*(n-st[top]+1);
			p--;
		}
	}
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T=1;
	while(T--) solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

