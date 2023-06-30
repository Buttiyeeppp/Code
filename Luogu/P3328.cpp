#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const ll Mod=1e9+7;
const int N=3e5+10;
bool mem1;
inline int read() {
	int f=1, z=0; char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { z=z*10+ch-'0'; ch=getchar(); }
	return f*z;
}
int n,Q,a,b;
void Add(int &x,ll y) { return x=(x+y>=Mod? x+y-Mod:x+y), void(); }
struct Matrix {
	int v[3][3];
	Matrix() { memset(v,0,sizeof(v)); }
	Matrix operator*(const Matrix &q)const {
		Matrix res;
		// for(int i=0;i<=2;i++)
		// 	for(int j=0;j<=2;j++)
		// 		for(int k=0;k<=2;k++) Add(res.v[i][j],1ll*v[i][k]*q.v[k][j]%Mod);
        for(int i=0;i<=2;i++) {
            Add(res.v[i][0],1ll*v[i][0]*q.v[0][0]%Mod);
            Add(res.v[i][0],1ll*v[i][1]*q.v[1][0]%Mod);
            Add(res.v[i][0],1ll*v[i][2]*q.v[2][0]%Mod);

            Add(res.v[i][1],1ll*v[i][0]*q.v[0][1]%Mod);
            Add(res.v[i][1],1ll*v[i][1]*q.v[1][1]%Mod);
            Add(res.v[i][1],1ll*v[i][2]*q.v[2][1]%Mod);

            Add(res.v[i][2],1ll*v[i][0]*q.v[0][2]%Mod);
            Add(res.v[i][2],1ll*v[i][1]*q.v[1][2]%Mod);
            Add(res.v[i][2],1ll*v[i][2]*q.v[2][2]%Mod);
        }
		return res;
	}
	Matrix operator+(const Matrix &q)const {
		Matrix res;
		// for(int i=0;i<=2;i++)
		// 	for(int j=0;j<=2;j++) res.v[i][j]=(v[i][j]+q.v[i][j])%Mod;
        for(int i=0;i<=2;i++) {
            res.v[i][0]=(v[i][0]+q.v[i][0])%Mod;
            res.v[i][1]=(v[i][1]+q.v[i][1])%Mod;
            res.v[i][2]=(v[i][2]+q.v[i][2])%Mod;
        }
		return res;
	}
}A,B,F,tA,tB,D;
Matrix pow(Matrix x,ll y) {
	Matrix res=D;
	while(y) {
		if(y&1) res=res*x;
		x=x*x, y>>=1;
	}
	return res;
}
Matrix Trans(Matrix q) {
	Matrix res;
	for(int i=0;i<=2;i++)
		for(int j=0;j<=2;j++) res.v[i][j]=q.v[j][i];
	return res;
}
int ls[N<<2],rs[N<<2];
Matrix s[N<<2],lz[2][N<<2];
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
void init() {
	D.v[0][0]=D.v[1][1]=D.v[2][2]=1;
	F.v[0][0]=2, F.v[0][1]=1, F.v[0][2]=1;

	A.v[0][0]=1, A.v[0][1]=1, A.v[0][2]=0;
	A.v[1][0]=a, A.v[1][1]=0, A.v[1][2]=0;
	A.v[2][0]=b, A.v[2][1]=0, A.v[2][2]=1;
	
	if(a) {
		ll inv=Pow(a,Mod-2);
		B.v[0][0]=0, B.v[0][1]=inv, B.v[0][2]=0;
		B.v[1][0]=1, B.v[1][1]=Mod-inv, B.v[1][2]=0;
		B.v[2][0]=0, B.v[2][1]=Mod-inv*b%Mod, B.v[2][2]=1;
	}
	else {
		B.v[0][0]=0, B.v[0][1]=0, B.v[0][2]=0;
		B.v[1][0]=1, B.v[1][1]=1, B.v[1][2]=0;
		B.v[2][0]=0, B.v[2][1]=Mod-b, B.v[2][2]=1;
	}
	tA=Trans(A), tB=Trans(B);
}
int p[N],tot;
void build(int &id,int l,int r) {
	id=++tot; 
	lz[0][id]=lz[1][id]=D;
	if(l==r) {
		s[id]=pow(tA,p[l-1]-1)*Trans(F)*F*pow(A,p[l+1]-3);
		return;
	}
	int mid=(l+r)>>1;
	build(ls[id],l,mid), build(rs[id],mid+1,r);
	s[id]=s[ls[id]]+s[rs[id]];
}
void pushdown(int id) {
	int pd0=0, pd1=0;
	for(int i=0;i<=2;i++)
		for(int j=0;j<=2;j++) {
			pd0|=(lz[0][id].v[i][j]!=D.v[i][j]), pd1|=(lz[1][id].v[i][j]!=D.v[i][j]); 
		}
	if(pd0) {
		Matrix v=lz[0][id]; lz[0][id]=D;
		s[ls[id]]=v*s[ls[id]], lz[0][ls[id]]=v*lz[0][ls[id]];
		s[rs[id]]=v*s[rs[id]], lz[0][rs[id]]=v*lz[0][rs[id]];
	} 
	if(pd1) {
		Matrix v=lz[1][id]; lz[1][id]=D;
		s[ls[id]]=s[ls[id]]*v, lz[1][ls[id]]=lz[1][ls[id]]*v;
		s[rs[id]]=s[rs[id]]*v, lz[1][rs[id]]=lz[1][rs[id]]*v;
	}
	return;
}
void Modify(int id,int l,int r,int x,int y,Matrix v,int op) {
	if(x<=l&&y>=r) {
		if(!op) s[id]=v*s[id], lz[op][id]=v*lz[op][id];
		else s[id]=s[id]*v, lz[op][id]=lz[op][id]*v;
		return;
	}
	pushdown(id);
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls[id],l,mid,x,y,v,op);
	if(y>mid) Modify(rs[id],mid+1,r,x,y,v,op);
	s[id]=s[ls[id]]+s[rs[id]];
}
Matrix Query(int id,int l,int r,int x,int y) {
	if(x<=l&&y>=r) return s[id];
	pushdown(id);
	int mid=(l+r)>>1; Matrix res;
	if(x<=mid) res=Query(ls[id],l,mid,x,y);
	if(y>mid) res=res+Query(rs[id],mid+1,r,x,y);
	return res;
}
bool mem2;
int main() {
	n=read(), Q=read(), a=read(), b=read();
	init();
	for(int i=1;i<=n;i++) p[i]=read();
	int rt; build(rt,2,n-1);
	string op; int l,r;
	for(int i=1;i<=Q;i++) {
		cin>>op; l=read(), r=read();
		if(op=="plus")
			Modify(1,2,n-1,min(l+1,n-1),min(r+1,n-1),tA,0), Modify(1,2,n-1,max(2,l-1),max(2,r-1),A,1);
		if(op=="minus")
			Modify(1,2,n-1,min(l+1,n-1),min(r+1,n-1),tB,0), Modify(1,2,n-1,max(2,l-1),max(2,r-1),B,1);
		if(op=="query")
			printf("%d\n",Query(1,2,n-1,l+1,r-1).v[0][0]);
	}
	return 0;
}