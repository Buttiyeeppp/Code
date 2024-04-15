#include <bits/stdc++.h>
using namespace std;
int n;
// int p[1000010],cnt1,cnt2;
int Qry(int l,int r) {
    cout<<"? "<<l<<" "<<r<<endl;

    // cnt1++,cnt2+=r-l+1;
    // int mx=0,pos=-1;
    // for(int i=l;i<=r;i++) mx=max(mx,p[i]);
    // for(int i=l;i<=r;i++) if(p[i]!=mx) {
    //     if(pos==-1||p[i]>p[pos]) pos=i;
    // }
    // return pos;

    int x; cin>>x;
    return x;
}
int pd;
void Answer(int x) {
    cout<<"! "<<x<<endl;

    // if(p[x]!=n) cout<<"Wrong!"<<endl;
    // if(cnt1>ceil(1.5*log2(n))) cout<<"To many Queries1! "<<cnt1<<" "<<ceil(1.5*log2(n))<<endl;
    // if(cnt2>3*n) cout<<"Queries2 too long! "<<cnt2<<" "<<3*n<<endl;

    pd=1;
}
int lim=5;
void sol(int l,int r,int p=-1) {
    if(pd) return;
    if(l==r) return Answer(l);
    if(!(~p)||p<l||p>r) p=Qry(l,r);
    if(l+1==r) return Answer(p==r? l:r);

    int len=max(0.618*(r-l+1),2.0);
    if(l+len-1>=p) {
        if(Qry(l,l+len-1)==p) sol(l,l+len-1,p);
        else sol(l+len,r,p);
    }
    else {
        if(Qry(r-len+1,r)==p) sol(r-len+1,r,p);
        else sol(l,r-len,p);
    }
}
void solve() {
    cin>>n;
    
    // n=1e6;
    // cnt1=cnt2=0;
    // p[1]=4,p[2]=2,p[3]=1,p[4]=3,p[5]=5;
    // for(int i=1;i<=n;i++) p[i]=i;
    // shuffle(p+1,p+n+1,mt19937(random_device()()));
    // for(int i=1;i<=n;i++) cout<<p[i]<<" ";
    // cout<<endl;

    pd=0, sol(1,n);
}
int main() {

    // while(1) solve();
    int T; cin>>T;
    while(T--) solve();

    return 0;
}