#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n,m,ans=INT_MAX;
vector<int> v[N];
multiset<int> st;
void insert(int val) {
    st.insert(val);
    auto p=st.find(val);
    if(p!=st.begin()) {
        auto p1=p; p1--;
        ans=min(ans,(*p)-(*p1));
    }
    auto p2=p; p2++;
    if(p2!=st.end()) ans=min(ans,(*p2)-*p);
}
multiset<int> st1;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1,x;i<=n;i++) {
        cin>>x; 
        insert(x), v[i].push_back(x);
        if(i>1) st1.insert(abs(x-v[i-1].back()));
    }
    while(m--) {
        string op; int x,y;
        cin>>op;
        if(op=="INSERT") {
            cin>>x>>y;
            insert(y);
            if(x<n)
                st1.erase(st1.find(abs(v[x].back()-(*v[x+1].begin()))));
            st1.insert(abs(y-v[x].back()));
            v[x].push_back(y);
            if(x<n)
                st1.insert(abs(y-(*v[x+1].begin())));
        }
        if(op=="MIN_GAP") cout<<*st1.begin()<<endl;
        if(op=="MIN_SORT_GAP") cout<<ans<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}