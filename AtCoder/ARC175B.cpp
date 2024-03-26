#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
ll n,a,b;
string st;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>a>>b>>st;
    ll l=0,r=0;
    for(int i=0;i<(int)st.size();i++) {
        if(st[i]=='(') l++;
        else {
            if(l>0) l--;
            else r++;
        }
    }
    // cout<<l<<" "<<r<<endl;
    ll v1=0,v2=0,v3=0,z=(l+r)/2;
    v1=(min(r,z)+min(l,z))*b;
    v2=(min(l,r)+1)/2*a+abs(l-r)/2*b;
    v3=(z-min(l,r))*b+(z+1)/2*a;
    ll ans=min({v1,v2,v3});
    ll val=0,lim=z-min(l,r);
    if(l%2==0) ans=min(ans,l/2*b+r/2*b);
    else ans=min(ans,l/2*b+r/2*b+min(a,b*2));
    for(int i=0;i<=lim;i++) {
        ans=min(ans,(min(l,r)+1)/2*a+abs(l-r)/2*b+val);
        if(l<r) { l++, r--, val+=b; }
        else { l--, r++, val+=b; }
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}