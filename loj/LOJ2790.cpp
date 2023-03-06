#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
const int N=2.5e6+10; 
int n,m,g,Q;
vector<ll> z[N],z1[N],z2[N],z3[N],z4[N];
void out(vector<ll> a[]) {
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) cerr<<a[i][j]<<" ";
		cerr<<endl;
	}
	cerr<<"--------\n";
}
signed main() {
	scanf("%lld%lld%lld",&m,&n,&g);
	for(int i=0;i<=n+1;i++) z[i].resize(m+2), z1[i].resize(m+2), z2[i].resize(m+2), z3[i].resize(m+2), z4[i].resize(m+2);
	for(int i=1,x,y,a,b;i<=g;i++) {
		scanf("%lld%lld%lld%lld",&y,&x,&a,&b);
		int t=a/b;
        if(!t) {
	    	z[max(x-t,1ll)][max(y-t,1ll)]+=a-b*t;
			if(x+t+1<=n&&y+t+1<=m) z[x+t+1][y+t+1]+=a-b*t;
			if(x+t+1<=n) z[x+t+1][max(y-t,1ll)]-=a-b*t;
			if(y+t+1<=m) z[max(x-t,1ll)][y+t+1]-=a-b*t;
            continue;
        }
        // cerr<<a-b*t<<endl;
		//左上 
		z[max(x-t,1ll)][max(y-t,1ll)]+=a-b*t;
		if(min(t-x,t-y)>0) z[1][1]+=min(t-x,t-y)*b;
		if(x-t+1<1&&y-x+1>1) z3[1][max(1ll,y-t+1)]+=b, z3[1][y-x+1]-=b, z1[1][y-x+1]+=b;
		else if(y-t+1<1&&x-y+1>1) z4[max(x-t+1,1ll)][1]+=b, z4[x-y+1][1]-=b, z1[x-y+1][1]+=b;
		else z1[max(x-t+1,1ll)][max(y-t+1,1ll)]+=b;
		z1[x+1][y+1]-=b;
		//右下 
		if(x+1<=n&&y+1<=m) {
			if(x+t+1<=n&&y+t+1<=m) z[x+t+1][y+t+1]+=a-b*t;
			z1[x+1][y+1]+=b, z1[min(x+t+1,n+1)][min(y+t+1,m+1)]-=b;
		}
		//左下
		if(x+1<=n) {
			if(x+t+1<=n) z[x+t+1][max(y-t,1ll)]-=a-b*t;
			if(x+t>n&&x+y+1-n>1) z2[n][x+y+1-n]-=b;
			else if(y-t+1<1&&x+y>1) z4[x+y+1][1]-=b,  z4[min(n,x+t)+1][1]+=b, z2[x+y][1]-=b;
			else z2[x+t-max({0ll,x+t-n,t-y})][y-t+1+max({0ll,x+t-n,t-y})]-=b,
                cerr << x+t-max({0ll,x+t-n,t-y}) << ' ' << y-t+1+max({0ll,x+t-n,t-y}) << endl;  
			z2[x][y+1]+=b;
		}
		//右上 
		if(y+1<=m) {
			if(y+t+1<=m) z[max(x-t,1ll)][y+t+1]-=a-b*t;
			if(y+t>m&&x+y-m-1>1); 
			else if(x-t+1<1&&y+x<m) z3[1][y+x]-=b, z3[1][min(y+t,m)+1]+=b, z2[1][y+x]+=b;
			z2[x][y+1]-=b, z2[max(x-t,0ll)][min(y+t+1,m+1)]+=b;
		}
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) z1[i][j]+=z1[i-1][j-1];
	for(int i=n;i>=1;i--) for(int j=1;j<=m;j++) z2[i][j]+=z2[i+1][j-1];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) z3[i][j]+=z3[i][j-1];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) z4[i][j]+=z4[i-1][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) z[i][j]+=z1[i][j]+z2[i][j]+z3[i][j]+z4[i][j];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) z[i][j]+=z[i-1][j]+z[i][j-1]-z[i-1][j-1];
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) z[i][j]+=z[i-1][j]+z[i][j-1]-z[i-1][j-1];
    scanf("%lld",&Q);
	for(int i=1,Xa,Xb,Ya,Yb;i<=Q;i++) {
		scanf("%lld%lld%lld%lld",&Ya,&Xa,&Yb,&Xb);
//		printf("%.0lf\n",1.0*(z[Xb][Yb]-z[Xb][Ya-1]-z[Xa-1][Yb]+z[Xa-1][Ya-1])/(Xb-Xa+1)/(Yb-Ya+1)+0.0000000000001);
		long long t=z[Xb][Yb]-z[Xb][Ya-1]-z[Xa-1][Yb]+z[Xa-1][Ya-1], s=(Xb-Xa+1)*(Yb-Ya+1);
        long long ans=t/s;
        if (t%s*2>=s) ans++;
        cout<<ans<<endl;
	}
	return 0;
}