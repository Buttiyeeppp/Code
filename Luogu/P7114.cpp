#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e6+10;
bool mem1;
string s;
int nxt[N],cnt[30],pre[N],suf[N],c[30];
void solve() {
	cin>>s;
	int n=s.size(); s=" "+s;
	for(int i=2;i<=n;i++) {
		int j=nxt[i-1];
		while(j&&s[j+1]!=s[i]) j=nxt[j];
		nxt[i]=(s[j+1]==s[i]? j+1:0);
	}
	for(int i=0;i<26;i++) cnt[i]=0;
	for(int i=1;i<=n;i++) {
		pre[i]=pre[i-1], cnt[s[i]-'a']++;
		if(cnt[s[i]-'a']&1) pre[i]++;
		else pre[i]--;
	}
	for(int i=0;i<26;i++) cnt[i]=0;
	suf[n+1]=0;
	for(int i=n;i>=1;i--) {
		suf[i]=suf[i+1], cnt[s[i]-'a']++;
		if(cnt[s[i]-'a']&1) suf[i]++;
		else suf[i]--;
	}
	ll ans=0;
	for(int i=0;i<=26;i++) c[i]=0;
	for(int j=pre[1];j<=26;j++) c[j]++;
	for(int i=2;i<n;i++) {
		ans+=c[suf[i+1]];
		for(int j=2*i;j<n;j+=i) {
			if(i%(j-nxt[j])==0&&j/(j-nxt[j])>1) ans+=c[suf[j+1]];
		}
		for(int j=pre[i];j<=26;j++) c[j]++;
	}
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
