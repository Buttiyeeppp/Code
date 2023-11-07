#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e7+10;
const ll Mod=1e9+7;
bool mem1;
inline char gc(){
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int sum=0,f=0;
	char ch=gc();
	for(;!isdigit(ch);ch=gc())f|=(ch=='-');
	for(;isdigit(ch);ch=gc()) sum=((sum<<1)+(sum<<3)+(ch^48));
	return f?-sum:sum;
}
int n,k;
ll f[N];
struct node {
    int l,mx;
    ll v;
}q[N];
int Mid;
ll pre[N],suf[N];
void rebuild(int l,int r) {
    Mid=(l+r)>>1;
    pre[Mid]=suf[Mid]=q[Mid].v;
    for(int i=Mid-1;i>=l;i--) suf[i]=min(suf[i+1],q[i].v);
    for(int i=Mid+1;i<=r;i++) pre[i]=min(pre[i-1],q[i].v);
}
bool mem2;
int main() {
    freopen("knight.in","r",stdin);
    freopen("knight.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    n=read(), k=read();
    memset(f,0x3f,sizeof(f));
    f[0]=0;
    int l=1,r=0;
    for(int i=1,ai;i<=n;i++) {
        ai=read();
        int L=i;
        while(l<=r&&q[r].mx<=ai) L=q[r].l, r--;
        q[++r]={L,ai,f[L-1]+ai};
        pre[r]=min(pre[r-1],q[r].v);
        if(l<=r&&i-((l==r)? i:q[l+1].l-1)+1>k) l++;
        if(l<=r&&i-q[l].l+1>k) {
            q[l].l=i-k+1;
            q[l].v=f[q[l].l-1]+q[l].mx;
            suf[l]=min(suf[l+1],q[l].v);
        }
        if(l>=Mid||r<=Mid) rebuild(l,r);
        f[i]=min(suf[l],pre[r]);
    }
    // for(int i=1;i<=n;i++) cerr<<f[i]<<" ";
    // cerr<<endl;
    ll ans=0;
    for(int i=1;i<=n;i++) ans=(ans*23+f[i])%Mod;
    cout<<ans<<endl;
    
    #ifdef xxzx
    cerr<<"Time "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
/*
6 3
3 4 1 5 6 8
*/