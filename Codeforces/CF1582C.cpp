#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int a[N],b[N];
void solve() {
	int n,ans=INT_MAX; string s;
	cin>>n>>s;
	for(int ch=0;ch<26;ch++) {
		b[0]=0;
		int pd=1,num=0,len=0;
		for(int i=0;i<n;i++) {
			if(s[i]-'a'!=ch) a[++len]=s[i]-'a', b[len]=0;
			else b[len]++, num++;
		}
		for(int l=1,r=len;l<r;l++,r--) if(a[l]!=a[r]) pd=0;
		if(!pd) continue;
		for(int l=0,r=len;l<=r;l++,r--) num-=(1+(l!=r))*min(b[l],b[r]);
		ans=min(ans,num);
	}
	if(ans==INT_MAX) cout<<-1<<endl;
	else cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	int T; cin>>T;
	while(T--) solve();
		
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
/*
kh(yy)hh(y)hk(y)
*/

