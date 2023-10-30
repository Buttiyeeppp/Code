#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
using ll=long long;
using PII=pair<int,int>;
bool mem1;
namespace IO{
	const int S=(1<<20);
	int x,flag,num[50];char c;
	char ibuf[S],*iS=ibuf,*iT=ibuf;
	char obuf[S],*oS=obuf,*oT=obuf+S;
	char getc(){
//		return getchar();
		if (iS==iT)iS=ibuf,iT=ibuf+fread(ibuf,1,S,stdin);
		return (iS==iT ? EOF : *iS++);
	}
	void flush(){
		fwrite(obuf,1,oS-obuf,stdout),oS=obuf;
	}
	void putc(char c){
		*oS++=c;
		if (oS==oT)flush();
	}
	int read(){
		x=flag=0,c=getc();
		while ((c<'0')||(c>'9'))flag|=(c=='-'),c=getc();
		while ((c>='0')&&(c<='9'))x=x*10+c-'0',c=getc();
		return (flag ? -x : x);
	}
	char read_char(){
		c=getc();
		while (1)c=getc();
		return c;
	}
	void write(ll x,char c='\0'){
		if (x<0)putc('-'),x=-x;
		while (x)num[++num[0]]=x%10,x/=10;
		if (!num[0])putc('0');
		while (num[0])putc(num[num[0]--]+'0');
		putc(c);
	}
};
const int N=1e6+10;
namespace Segt {
    int v[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    void pushdown(int id) {
        if(!v[id]) return;
        v[ls]=v[rs]=v[id], v[id]=0;
    }
    void Build(int id,int l,int r) {
        v[id]=0;
        if(l==r) return;
        int mid=(l+r)>>1;
        Build(ls,l,mid), Build(rs,mid+1,r);
    }
    void Modify(int id,int l,int r,int x,int y,int val) {
        if(x<=l&&y>=r) return v[id]=val, void();
        int mid=(l+r)>>1;
        pushdown(id);
        if(x<=mid) Modify(ls,l,mid,x,y,val);
        if(y>mid) Modify(rs,mid+1,r,x,y,val);
    }
    int Query(int id,int l,int r,int x) {
        if(l==r) return v[id];
        int mid=(l+r)>>1;
        pushdown(id);
        if(x<=mid) return Query(ls,l,mid,x);
        return Query(rs,mid+1,r,x);
    }
}
int n,m,q;
namespace Bit {
    ll v[N];
    int lowbit(int x) { return x&-x; }
    void Add(int x,ll val) {
        for(int i=x;i<=m;i+=lowbit(i)) v[i]+=val;
    }
    ll Qry(int x) {
        ll res=0;
        for(int i=x;i;i-=lowbit(i)) res+=v[i];
        return res;
    }
}
vector<PII> nd[N],qr[N];
ll a[N],ans[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    n=IO::read(), m=IO::read(), q=IO::read();
    for(int i=1,op,x,y;i<=m;i++) {
        op=IO::read();
        if(op==1) {
            x=IO::read(), y=IO::read();
            int ax=Segt::Query(1,1,n,x), ay=Segt::Query(1,1,n,y);
            Segt::Modify(1,1,n,x,x,ay),Segt::Modify(1,1,n,y,y,ax);
        }
        if(op==2) {
            x=IO::read(), y=IO::read();
            a[i]=IO::read(), Segt::Modify(1,1,n,x,y,i);
        }
        if(op==3) {
            x=IO::read();
            int t=Segt::Query(1,1,n,x);
            nd[t].emplace_back(i,a[t]);
        }
    }
    for(int i=1,l,r;i<=q;i++) {
        l=IO::read(), r=IO::read();
        qr[l].emplace_back(r,i);
    }
    for(int l=m;l>=1;l--) {
        for(auto now:nd[l]) Bit::Add(now.first,now.second);
        for(auto now:qr[l]) ans[now.second]=Bit::Qry(now.first);
    }
    for(int i=1;i<=q;i++) IO::write(ans[i],'\n');
    IO::flush();

    #ifdef xxzx
    cerr<<"Time "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}