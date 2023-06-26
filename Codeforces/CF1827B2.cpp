#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=5e6+10;
bool mem1;
int n;
struct node {
	int v,op;
	bool operator<(const node &q)const {
		return v<q.v;
	}
}nd[N];
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>nd[i].v, nd[i].op=i;
	ll ans=0;
	for(int i=1;i<n;i++) ans+=1ll*i*(n-i);
	set<int> s1,s2;
	for(int i=0;i<=n+1;i++) s1.insert(i);
	s2.insert(0), s2.insert(n+1);
	sort(nd+1,nd+n+1);
	for(int i=1;i<=n;i++) {
		int a,b,c,d;
		b=nd[i].op;
		a=*(--s1.lower_bound(b));
		c=*s1.upper_bound(b);
		d=*s2.lower_bound(c);
		ans-=1ll*(b-a)*(d-c);
		s1.erase(b), s2.insert(b);
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

