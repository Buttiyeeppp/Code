#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
bool mem1;
int l1,l2,n1,n2,s[N],pos[N];
string s1,s2;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	while(cin>>s2>>l2>>s1>>l1) {
		n2=s2.size(), n1=s1.size();
		for(int k=1;k<=n2;k++) {
			int p=k; s[k]=0;
			for(int i=1;i<=n1;i++) {
				if(s1[i-1]==s2[p-1]) {
					if(p==n2) p=1, s[k]++;
					else p++;
				}
			}
			pos[k]=p;
		}
		ll p=1, ans=0;
		for(int i=1;i<=l1;i++) ans+=1ll*s[p], p=pos[p];
		cout<<ans/l2<<endl;
	}
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

