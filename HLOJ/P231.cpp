#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,b[N],l[N];
PII fa[N];
vector<int> ans;
stack<int> st;
queue<int> que;
void out1() { ans.push_back(1), que.push(st.top()), st.pop(); }
void out2() { ans.push_back(2), st.push(que.front()), que.pop(); }
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	int m=n; queue<int> q;
	for(int i=1;i<=n;i++) q.push(i), l[i]=1;
	while(q.size()>1) fa[q.front()]={++m,1}, q.pop(), fa[q.front()]={m,0}, q.pop(), q.push(m);
	if(q.size()) q.pop(); 
	b[m]=1;
	for(int i=m-1;i>=1;i--) b[i]=b[fa[i].first]^fa[i].second;
	for(int i=1;i<=m;i++) l[fa[i].first]+=l[i];
	for(int i=1,x;i<=n;i++) cin>>x, st.push(x), q.push(i);
	for(int i=1;i<=n;i++) out1();
	while(q.size()>1) {
		int u=q.front(); q.pop();
		for(int i=1;i<=l[u];i++) out2();
		int v=q.front(); q.pop();
		q.push(fa[u].first);
		int i=l[u], j=l[v];
		while(i&&j) {
			if((st.top()<que.front())^b[fa[u].first]) out1(), i--;
			else out2(), out1(), j--;
		}
		while(i) out1(), i--;
		while(j) out2(), out1(), j--;
	}
	for(int i=1;i<=n;i++) out2();
	cout<<ans.size()<<endl;
	for(auto now:ans) cout<<now<<" ";
	cout<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

