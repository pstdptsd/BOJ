// 10217. KCM Travel

#include <bits/stdc++.h>

using namespace std;

struct edge{
    int to, dst, cst;
};

struct info {
    int dst;
    int id, cst;
    bool operator<(const info &rhs) const {
        return dst > rhs.dst;
    }
};

void solve(){
    int n,m,k; scanf("%d%d%d",&n,&m,&k);
    vector<vector<edge>> Adj(n+1);
    vector<vector<int>> Dst(n+1, vector<int>(m+1,INT_MAX));
    
    for(int i=0;i<k;i++) {
        int a,b,c,d; scanf("%d%d%d%d", &a,&b,&c,&d);
        Adj[a].push_back({b,d,c});
    }
    
    priority_queue<info> pq;
    Dst[1][0]=0;
    pq.push({0, 1, 0});
    
    while(!pq.empty()){
        info tInfo=pq.top();
        pq.pop();
        
        int cur=tInfo.id;
        int cst=tInfo.cst;
        int dst=tInfo.dst;
        
        if(cur==n) break;
        if(Dst[cur][cst] < dst) continue;
        
        for(int i=0;i<Adj[cur].size();i++) {
            edge tmp=Adj[cur][i];
            int nxt=tmp.to;
            if(cst+tmp.cst <= m && Dst[nxt][cst+tmp.cst] > dst+tmp.dst) {
                Dst[nxt][cst+tmp.cst]=dst+tmp.dst;
                pq.push({Dst[nxt][cst+tmp.cst], nxt, cst+tmp.cst});
            }
        }
    }
    
    int res = INT_MAX;
    for(int i=0;i<=m;i++) {
        res=min(res, Dst[n][i]);
    }
    
    if(res==INT_MAX) printf("Poor KCM\n");
    else printf("%d\n", res);
}

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        solve();
    }
}