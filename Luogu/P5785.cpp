#include<bits/stdc++.h>
using namespace std;
#define yep __int128
#define ll long long
const int N=3e5+10;
int n,s,q[N],tot=1;
ll t[N],c[N],f[N];
ll x(int i){ return c[i]; }
ll y(int i){ return f[i]-s*c[i]; }
int find(ll k) {
    int head=1,tail=tot,mem=tot;
    while(head<=tail) {
        int m=(head+tail)>>1;
        if((yep)y(q[m+1])-y(q[m])>(yep)k*(x(q[m+1])-x(q[m])))
            tail=m-1, mem=m;
        else head=m+1;
    }
    return q[mem];
}
bool check(int a,int b,int c,int d) {
    return (yep)(y(a)-y(b))*(x(c)-x(d))>=(yep)(x(a)-x(b))*(y(c)-y(d));
}
int main() {
    scanf("%d%d",&n,&s);
    for(int i=1,T,C;i<=n;i++) {
        scanf("%d%d",&T,&C);
        t[i]=t[i-1]+T, c[i]=c[i-1]+C;
    }
    for(int i=1;i<=n;i++) {
        int j=find(t[i]);
        f[i]=f[j]+t[i]*(c[i]-c[j])+s*(c[n]-c[j]);
        while(tot>1&&check(q[tot],q[tot-1],i,q[tot-1])) tot--;
        q[++tot]=i;
    }
    printf("%lld",f[n]);
    return 0;
}