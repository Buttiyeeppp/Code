#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=10;
const int M=1e5+10;
bool mem1;
int n,s[N],b[M],cnt[N],tot,c[N];
void dfs(int step) {
	if(step==n+1) {
		tot++;
		int v=0;
		for(int s=0;s<(1<<n);s++) {
			int sum=0, bh=tot, pd=0;
			for(int i=1;i<=n;i++)
				if((1<<(i-1))&s) {
					if(cnt[i]==1) pd=1;
					sum++, bh-=c[i+1];
				}
			if(pd) continue;
//			if(tot==3) cout<<"Chk "<<s<<" "<<bh<<" "<<b[bh]<<endl;
			v=v+((sum&1)? -1:1)*b[bh];
		}
		cout<<v<<" ";
		return;
	}
	for(int i=1;i<=s[step];i++) cnt[step]=i, dfs(step+1);
}
void solve() {
	cin>>n;
	int sz=1;
	for(int i=1;i<=n;i++) cin>>s[i], sz*=s[i];
	c[n+1]=1;
	for(int i=n;i>=1;i--) c[i]=c[i+1]*s[i];
	for(int i=1;i<=sz;i++) cin>>b[i];
	dfs(1);
	cout<<endl;
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

