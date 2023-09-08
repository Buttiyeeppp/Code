#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=7e5+10;
const ll P=10;
bool mem1;
string s,x,st;
ll z[N],temp[5],hs[5][N],Pow[5][N],Mod[5];
ll Hash(int l,int r,int c) {
	return (hs[c][r]-hs[c][l-1]*Pow[c][r-l+1]%Mod[c]+Mod[c])%Mod[c];
}
void chk(int a,int b,int c,int d) {
	if(a>b||c>d) return;
	for(int x=0;x<5;x++) {
		if((Hash(a,b,x)+Hash(c,d,x))%Mod[x]!=temp[x]) return;
	}
	cout<<a+1<<" "<<b+1<<endl<<c+1<<" "<<d+1<<endl;
	exit(0);
}
bool Pri(int x) {
	if(!x) return false;
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return false;
	return true;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	mt19937 rd(time(0));
	for(int c=0;c<5;c++) {
		while(!Pri(Mod[c]=rd()%1000000008));
	}
	cin>>s>>x;
	st=x+s;
	int slen=s.size(), xlen=x.size();
	for(int i=1,l=0;i<st.size();i++) {
		if(z[l]+l>i) z[i]=min(z[l]+l-i,z[i-l]);
		while(i+z[i]<st.size()&&st[z[i]]==st[i+z[i]]) z[i]++;
		if(i+z[i]>l+z[l]) l=i;
	}
	for(int i=xlen;i<st.size();i++) z[i-xlen]=min(z[i],(ll)xlen);
	for(int c=0;c<5;c++) {
		Pow[c][0]=1;
		for(int i=1;i<N;i++) Pow[c][i]=Pow[c][i-1]*P%Mod[c];
		for(int i=0;i<xlen;i++) temp[c]=(temp[c]*P+x[i]-'0')%Mod[c];
		hs[c][0]=s[0]-'0';
		for(int i=1;i<slen;i++) hs[c][i]=(hs[c][i-1]*P+s[i]-'0')%Mod[c];
	}
	for(int i=0;i+2*xlen-3<slen;i++) chk(i,i+xlen-2,i+xlen-1,i+2*xlen-3);
	for(int i=0,l;i+xlen-1<slen;i++) {
		l=xlen-z[i];
		if(i+xlen+l-1<slen) chk(i,i+xlen-1,i+xlen,i+xlen+l-1);
		if(i-l>=0) chk(i-l,i-1,i,i+xlen-1);
		l=xlen-z[i]-1;
		if(i+xlen+l-1<slen) chk(i,i+xlen-1,i+xlen,i+xlen+l-1);
		if(i-l>=0) chk(i-l,i-1,i,i+xlen-1);
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

