#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e7+10;
bool mem1;
int n,z[N];
void getz(string st) {
    memset(z,0,sizeof(z));
    int p=1, n=st.size();
    st=" "+st;
    for(int i=2;i<=n;i++) {
        z[i]=0;
        if(z[p]+p-i>=0) z[i]=min(z[p]+p-i,z[i-p]);
        while(st[i+z[i]]==st[z[i]+1]) z[i]++;
        if(z[i]+i>z[p]+p) p=i;
    }
    for(int i=0;i<n;i++) z[i]=z[i+1]-1;
}
int l[N],tl[N],r[N],tr[N],m;
char a[N];
void manacher() {
    int p=0;
    for(int i=1;i<=m;i++) {
        l[i]=1;
        if(i<=p+l[p]-1) l[i]=min(l[2*p-i],p+l[p]-i);
        while(i-l[i]>=1&&i+l[i]<=m&&a[i-l[i]]==a[i+l[i]]) l[i]++;
        if(i+l[i]>p+l[p]) p=i;
    }
    memset(tl,0,sizeof(tl)), memset(tr,0,sizeof(tr));
    int j=0;
    for(int i=1;i<=m;i++) if(a[i]!='!') {
        if(l[i]>=l[i-1]) tl[j]=tr[j]=l[i]/2;
        else tl[j]=tr[j]=l[i-1]/2, tl[j]++;
        j++;
    }
    for(int i=0;i<j;i++) l[i]=tl[i], r[i]=tr[i];
}
int c[N],c2[N];
int calc(string st) {
    n=st.size();
    a[m=1]='!';
    for(int i=0;i<n;i++) a[++m]=st[i], a[++m]='!';
    manacher();

    reverse(st.begin(),st.end());
    string stl=st;
    reverse(st.begin(),st.end());

    getz(st+stl);
    for(int i=n;i<=2*n-1;i++) c2[2*n-1-i-z[i]]=max(c2[2*n-1-i-z[i]],z[i]+1);
    for(int i=1;i<n;i++) c2[i]=max(c2[i],c2[i-1]-1);
    for(int i=0;i<n;i++) c2[i]=min(c2[i],i);
    for(int i=n;i<=2*n-1;i++) c[2*n-1-i]=z[i];
    for(int i=n-2;i>=0;i--) c[i]=max(c[i],c[i+1]);
    for(int i=0;i<n;i++) c[i]=min({c[i],i-1,n-i-1});

    int res=0;
    for(int i=0;i<n;i++) {
        int L=i-l[i], R=i+r[i], len=R-L-1;
        res=max(res,len);
        if(L>0&&R<n-1) {
            if(c[R]>=L) res=max(res,2*(L+1)+len);
            res=max(res,2*c2[R]+len);
        }
    }
    return res;
}
bool mem2;
int main() {
    #ifndef xxzx
    freopen("string.in","r",stdin);
    freopen("string.out","w",stdout);
    #endif
    ios::sync_with_stdio(false), cin.tie(nullptr);

    string st; cin>>st;
    int p=0;
    while(st[p]==st[st.size()-p-1]&&p<(int)st.size()-p-1) p++;
    st=st.substr(p,st.size()-2*p);

    calc(st);
    int v1=calc(st);
    reverse(st.begin(),st.end());
    int v2=calc(st);
    cout<<max(v1,v2)+2*p<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
/*

abc efe r cba h
abcefercbah

abc r efe cba h
abcrefecbah

abcrefecbahhabcefercba

cdabefba
cd ab ef ba

gbuiaq  szhtivbwcc  wrhjtddq  ywpnpizwrc  rr   qddtjhrw   qaiubg

 'szhtivbwcc'  wrhjtddq  'ywpnpizwrc'  rr   qddtjhrw

                                             7~0
*/