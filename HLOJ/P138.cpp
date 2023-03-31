#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int prime[N];
vector<int> P;
void Get_Prime() {
	for(int i=2;i<N;i++) {
		if(!prime[i]) P.push_back(i);
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			prime[now*i]=1;
			if(i%now==0) break;
		}
	}
	return;
}
map<pair<int,int>,int> mp;
int solve(int a,int b) {
	if(mp[make_pair(a,b)]) return mp[make_pair(a,b)];
	if(a==1) return mp[make_pair(a,b)]=0;
	if(b==1) return mp[make_pair(a,b)]=a-1;	
    vector<int> y;
	int nb=b;
	for(auto now:P) {
		if(now*now>nb) break;
		if(nb%now==0) {
			y.emplace_back(now);
			while(nb%now==0) nb/=now;
		}
	}
    if(nb>1) y.emplace_back(nb);
	int mn=0x3f3f3f3f,p;
	for(auto now:y) {
		p=(a/now)*now;
		mn=min(mn,abs(a-p)+solve(p/now,b/now)+1);
		p=(a/now+(a%now!=0))*now;
		mn=min(mn,abs(a-p)+solve(p/now,b/now)+1);
	}
	return mp[make_pair(a,b)]=min(a-1,mn);
}
int main() {
	freopen("operate.in","r",stdin);
	freopen("operate.out","w",stdout);
//	freopen("d.txt","w",stdout);
	Get_Prime();
	int T,a,b; scanf("%d",&T);
	while(T--) scanf("%d%d",&a,&b), printf("%d\n",solve(min(a,b),abs(a-b)));
	return 0;
}