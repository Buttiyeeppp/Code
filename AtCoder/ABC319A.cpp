#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=20;
bool mem1;
string a[N]={"","tourist","ksun48","Benq","Um_nik","apiad","Stonefeang","ecnerwala","mnbvmar","newbiedmy","semiexp"};
string b[N]={"","3858","3679","3658","3648","3638","3630","3613","3555","3516","3481"};
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    string s; cin>>s;
    for(int i=1;i<=10;i++) if(a[i]==s) cout<<b[i]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}