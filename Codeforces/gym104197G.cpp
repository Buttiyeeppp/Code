#include<bits/stdc++.h>
using namespace std;
int n;
int f[1<<24],to[1<<24];
char a[30];
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;i++) {
		scanf("%s",a+1);
		for(int j=1;j<=n;j++) if(a[j]=='1') to[(1<<(i-1))]|=(1<<(j-1));
	}
	int u=(1<<n)-1;
	for(int s=1;s<=u;s++) if(!to[s]){
		int g=0;
        for(int x=s;x;x-=x&-x) to[s]|=to[x&-x], g|=(x&-x);
		// for(int i=1;i<=n;i++) if((1<<(i-1))&s) to[s]|=to[1<<(i-1)], g|=(1<<(i-1));
		to[s]&=u^g; 
	}
	f[1]=1;
	for(int s=1;s<=u;s++) {
		int g=(u^s)&to[f[s]];
        for(int x=g;x;x-=x&-x) f[s|(x&-x)]|=(x&-x);
		// for(int i=1;i<=n;i++) if((1<<(i-1))&g) f[s|(1<<(i-1))]|=(1<<(i-1));
	}
	for(int i=1;i<=n;i++) {
		int ed=0;
		for(int s=0;s<=u;s++) if((f[s]&(1<<(i-1)))&&(s&1)) ed|=f[(s^u)|1];
		for(int j=1;j<=n;j++) printf("%d",(((1<<(j-1))&ed)!=0));
		puts("");
	}
	return 0;
}
