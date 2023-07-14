#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,x[N],l[N],nxt[N][20],Q,mx[N];
ll w[N][20];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>x[i]>>l[i];
	for(int i=n-1;i>=1;i--) {
		int p=i+1; mx[i]=x[i]+l[i];
		while(p&&mx[i]>=x[p]) mx[i]=max(mx[i],mx[p]), p=nxt[p][0];
		nxt[i][0]=p, w[i][0]=x[p]-mx[i];
	}
	for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++) nxt[i][j]=nxt[nxt[i][j-1]][j-1], w[i][j]=w[i][j-1]+w[nxt[i][j-1]][j-1];
	cin>>Q;
	for(int i=1,l,r;i<=Q;i++) {
		cin>>l>>r;
		ll ans=0;
		for(int j=19;j>=0;j--)
			if(nxt[l][j]&&nxt[l][j]<=r) ans+=w[l][j], l=nxt[l][j];
		cout<<ans<<endl;
	}
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

