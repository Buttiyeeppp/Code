#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int n;
PII zb(int x) {
	int h=(x-1)/n+1;
	if(h&1) return make_pair(h,x-(h-1)*n);
	else return make_pair(h,n*h-x+1);
}
void out1() {
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			if(i&1) {
				if(j!=n) cout<<">";
				else cout<<"v";
			}
			else {
				if(j!=1) cout<<"<";
				else cout<<"v";
			}
		}
		cout<<endl;
	}
	cout<<endl;
}
void out2() {
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			if(i&1) {
				if(j!=1) cout<<"<";
				else cout<<"^";
			}
			else {
				if(j!=n) cout<<">";
				else cout<<"^";
			}
		}
		cout<<endl;
	}
	cout<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int x,y;
	cin>>n;
	cout<<"? 1 1"<<endl; out1();
	cin>>x>>y;
	int ed=((n&1)? n:1);
	if(x==n+1&&y==ed) {
		cout<<"? "<<n<<" "<<ed<<endl; out2();
		cin>>x>>y;
		if(x!=-1) return cout<<"! "<<n<<" "<<ed<<" v"<<endl, 0;
		int l=0,r=n*n+1;
		while(l+1<r) {
			int mid=(l+r)>>1; PII pos=zb(mid);
			cout<<"? "<<pos.first<<" "<<pos.second<<endl; out2();
			cin>>x>>y;
			if(x!=-1) l=mid;
			else r=mid;
		}
		l++;
		PII pos=zb(l);
		cout<<"? "<<pos.first<<" "<<pos.second<<endl;
		for(int i=1;i<=n;i++) {
			for(int j=1;j<=n;j++) {
				if(i&1) cout<<"<";
				else cout<<">";
			}
			cout<<endl;
		}
		cout<<endl;
		cin>>x>>y;
		cout<<"! "<<pos.first<<" "<<pos.second<<" ";
		if(x==-1) cout<<((pos.first&1)? '>':'<')<<endl;
		else cout<<"v"<<endl;
		return 0;
	}
	if(x!=-1) {
		if(x==0) return cout<<"! 1 "<<y<<" ^"<<endl, 0;
		if(y==0) return cout<<"! "<<x<<" 1 <"<<endl, 0;
		if(x==n+1) return cout<<"! "<<n<<" "<<y<<" v"<<endl, 0;
		if(y==n+1) return cout<<"! "<<x<<" "<<n<<" >"<<endl, 0;
	}
	int l=0, r=n*n+1;
	while(l+1<r) {
		int mid=(l+r)>>1; PII pos=zb(mid);
		cout<<"? "<<pos.first<<" "<<pos.second<<endl; out1();
		cin>>x>>y;
		if(x!=-1) r=mid;
		else l=mid;
	}
	r--;
	PII pos=zb(r);
	cout<<"? "<<pos.first<<" "<<pos.second<<endl;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			if(i&1) cout<<">";
			else cout<<"<";
		}
		cout<<endl;
	}
	cout<<endl;
	cin>>x>>y;
	cout<<"! "<<pos.first<<" "<<pos.second<<" ";
	if(x==-1) cout<<((pos.first&1)? '<':'>')<<endl;
	else cout<<"^"<<endl;
	
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

