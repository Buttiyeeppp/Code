#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
const int N=3e5+10;
int n,a[N],cnt[N],ap[N];
void solve1() {
	cout<<n+2<<endl;
	int p=(a[1]!=1? 1:2);
	cout<<p<<" ";
	for(int i=1;i<=n;i++) {
		if(a[i]==p) cout<<a[1]<<" ";
		else cout<<a[i]<<" ";
	}
	cout<<a[1]<<" ";
}
queue<int> q;
stack<int> st;
void back(int u) {
	st.pop(), ap[u]--, q.push(u);
	while(st.top()!=u) {
		int v=st.top(); st.pop();
		ap[v]--, q.push(v);
	}
	st.pop(), ap[u]--, q.push(u);
}
void insert(int u) {
	st.push(u), ap[u]++;
	if(ap[u]==2) back(u);
}
void solve2() {
	cout<<n<<endl;
	int p=0;
	for(int i=1;i<=n;i++) {
		if(!p&&cnt[i]==2) p=i;
		for(int j=1;j<=cnt[i];j++) q.push(i);
	}
	cout<<p<<" ";
	insert(p), insert(a[1]);
	for(int i=2;i<=n;i++) {
		if(ap[a[i]]) {
			cout<<p<<" ";
			insert(p), insert(a[i]), p=a[i];
		}
		else {
			while(q.front()==p||q.front()==a[i]) q.push(q.front()), q.pop();
			int u=q.front(); q.pop();
			cout<<u<<" ";
			insert(u), insert(a[i]);
		}
	}
}
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cnt[i]=2;
	int ok=0;
	for(int i=1;i<=n;i++) {
		cin>>a[i], cnt[a[i]]--;	
		if(!cnt[a[i]]) ok=1;
	}
	if(n==1) cout<<-1<<endl;
	else if(!ok) solve1();
	else solve2();
	return 0;
}