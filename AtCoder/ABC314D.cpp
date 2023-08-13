#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define xxzx
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n,Q,vis[N],pd1=1,pd2=1; // big/small
char ans[N];
string s;
struct option { int t,x; char c; }q[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>s>>Q;
	for(int i=1;i<=Q;i++) cin>>q[i].t>>q[i].x>>q[i].c;
	for(int i=Q;i>=1;i--) {
		if(q[i].t==1) {
			if(!vis[q[i].x]) {
				vis[q[i].x]=1;
				if(q[i].c>='a'&&q[i].c<='z') {
					if(pd2) ans[q[i].x]=q[i].c;
					else ans[q[i].x]=(char)(q[i].c-32);
				}
				else {
					if(pd1) ans[q[i].x]=q[i].c;
					else ans[q[i].x]=(char)(q[i].c+32);
				}
			}
		}
		else if(q[i].t==2) { // big to small
			if(pd2) pd1=0;
		}
		else {
			if(pd1) pd2=0;
		}
	}
	for(int i=1;i<=n;i++) if(!vis[i]) {
		if(s[i-1]>='a'&&s[i-1]<='z') {
			if(pd2) ans[i]=s[i-1];
			else ans[i]=(char)(s[i-1]-32);
		}
		else {
			if(pd1) ans[i]=s[i-1];
			else ans[i]=(char)(s[i-1]+32);
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i];
	cout<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

