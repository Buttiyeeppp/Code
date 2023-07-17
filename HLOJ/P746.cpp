#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
bool mem1;
int n,cnt[N],yep,tot,sm[N],yep1;
string s[N];
bool mem2;
int main() {
//	freopen("hominid4.in","r",stdin);
//	freopen("a.txt","w",stdoout);
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i], s[i]=" "+s[i];
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			if(s[i][j]=='x')
				sm[i]++, cnt[j]++, yep1=1;
		}
		if(sm[i]==n) yep=1;
	}
	for(int j=1;j<=n;j++) {
		int sum=0;
		for(int i=1;i<=n;i++) sum+=(s[i][j]=='x');
		tot+=(sum==n);
	}
	if(yep) cout<<n-tot<<endl;
	else {
		int ans=INT_MAX;
		for(int i=1;i<=n;i++) ans=min(ans,n-sm[i]+n-tot+1-(cnt[i]!=0));
		cout<<ans<<endl;
	}
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

