#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
ll a[5],b[5],n;
bool check2(ll x,ll y) { // +x *y
    // for(int i=1;i<=n;i++) {
    //     if((a[i]+x)*y==b[i]||a[i]+x==b[i]||a[i]*y==b[i]) continue;
    //     return false;
    // }
    if(!((a[1]+x)*y==b[1]||a[1]+x==b[1]||a[1]*y==b[1])) return false;
    if(!((a[2]+x)*y==b[2]||a[2]+x==b[2]||a[2]*y==b[2])) return false;
    if(!((a[3]+x)*y==b[3]||a[3]+x==b[3]||a[3]*y==b[3])) return false;
    return true;
}
bool check3(ll x,ll y) { // *x +y
    // for(int i=1;i<=n;i++) {
    //     if(a[i]*x+y==b[i]||a[i]*x==b[i]||a[i]+y==b[i]) continue;
    //     return false;
    // }
    if(!(a[1]*x+y==b[1]||a[1]*x==b[1]||a[1]+y==b[1])) return false;
    if(!(a[2]*x+y==b[2]||a[2]*x==b[2]||a[2]+y==b[2])) return false;
    if(!(a[3]*x+y==b[3]||a[3]*x==b[3]||a[3]+y==b[3])) return false;
    return true;
}
bool calc(int x,int y) {
    if((a[x]-a[y])&&(b[x]-b[y])%(a[x]-a[y])==0) {
        ll v1=(b[x]-b[y])/(a[x]-a[y]), v2=b[x]-a[x]*v1;
        if(check3(v1,v2)) return true;
    }
    return false;
}
int p[5];
void solve() {
    ll A,B,C,D,E,F;
    cin>>A>>B>>C>>D>>E>>F;
    n=0;
    if(A!=D) a[++n]=A, b[n]=D;
    if(B!=E&&!(B==A&&E==D)) a[++n]=B, b[n]=E; 
    if(C!=F&&!(C==A&&F==D)&&!(C==B&&F==E)) a[++n]=C, b[n]=F;
    if(n<=1) return cout<<n<<endl, void();

    ll v=b[1]-a[1], pd=1;
    for(int i=2;i<=n;i++) pd&=(v==b[i]-a[i]);
    if(pd) return cout<<1<<endl, void();

    if(a[1]) {
        v=b[1]/a[1], pd=(b[1]%a[1]==0);
        for(int i=2;i<=n;i++) pd&=(a[i]&&(v==b[i]/a[i])&&(b[i]%a[i]==0));
        if(pd) return cout<<1<<endl, void();
    }

    if(n==2) return cout<<2<<endl, void();

    if(calc(1,2)||calc(1,3)||calc(2,3)) return cout<<2<<endl, void();
    for(int i=1;i<=n;i++) check3(0,b[i]);

    for(int i=1;i<=n;i++) p[i]=i;
    do {
        ll x=b[p[1]]-a[p[1]];

        if(a[p[2]]) {
            ll y=b[p[2]]/a[p[2]];
            if(b[p[2]]%a[p[2]]==0) {
                if(a[p[3]]*y+x==b[p[3]]||a[p[3]]*y==b[p[3]]||a[p[3]]+x==b[p[3]]||(a[p[3]]+x)*y==b[p[3]]) return cout<<2<<endl, void();
            }

            if(a[p[1]]) {
                ll y1=b[p[1]]/a[p[1]];
                if(b[p[1]]%a[p[1]]==0&&b[p[2]]%a[p[2]]==0) {
                    if(y1==y) return cout<<2<<endl, void();
                    if(a[p[3]]*y==b[p[3]]||a[p[3]]*y1==b[p[3]]||a[p[3]]*y*y1==b[p[3]]) return cout<<2<<endl, void();
                }
            }
        }

        ll x2=b[p[2]]-a[p[2]];
        if(a[p[3]]+x==b[p[3]]||a[p[3]]+x2==b[p[3]]||a[p[3]]+x+x2==b[p[3]]) return cout<<2<<endl, void();

        ll c=b[p[1]]*a[p[2]]-b[p[2]]*a[p[1]], d=b[p[2]]-b[p[1]];
        if(d&&(c%d==0)&&(a[p[1]]+c/d)) if(check2(c/d,b[p[1]]/(a[p[1]]+c/d))) return cout<<2<<endl, void(); 
        // cout<<(!d&&c%d==0)<<" "<<c%d<<" "<<c<<" "<<d<<" "<<c/d<<" "<<b[p[1]]/(a[p[1]]+c/d)<<endl;

        // if(x==x2) return cout<<2<<endl, void();
    } while(next_permutation(p+1,p+n+1));

    /*
    for(int i=1;i<=n;i++) {
        for(ll x=1,p;x*x<=abs(b[i]);x++) if(b[i]%x==0) {
            p=x;
            if(check2(b[i]/p-a[i],p)) return cout<<2<<endl, void();
            if(check2(b[i]/(-p)-a[i],-p)) return cout<<2<<endl, void();
            p=b[i]/x;
            if(check2(b[i]/p-a[i],p)) return cout<<2<<endl, void();
            if(check2(b[i]/(-p)-a[i],-p)) return cout<<2<<endl, void();
        }
    }
    */

    return cout<<3<<endl, void();
}
bool mem2;
int main() {
    // freopen("triple2.in","r",stdin);
    // freopen("triple.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}