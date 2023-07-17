#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
bool mem1;
vector<ll> w;
ll n;
void solve() {
	cin>>n;
	cout<<upper_bound(w.begin(),w.end(),n)-w.begin()<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	for(__int128 x=1;x<=1000000;x++) {
		w.push_back(x*x*x);
		if(x!=1) {
			__int128 p=x*x*x,lst=x,mem;
			while(p<=1e18&&p>0) {
				if(lst!=x) w.push_back(p);
				mem=p, p=p*x*x-lst, lst=mem;
			}
		}
	}
	sort(w.begin(),w.end());
	int T; cin>>T;
	while(T--) solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
