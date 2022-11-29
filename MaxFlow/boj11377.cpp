// 11377. 열혈강호 3
// Category : Max-Flow

#include <bits/stdc++.h>

using namespace std;

struct MF {
    struct edge{
        int to, cap, rev;
    };
    int sz, Src, Ter;
    vector<vector<edge>> adj;
    vector<int> level;
    vector<int> work;
    
    MF(int sz, int s, int t) : sz{sz}, Src{s}, Ter{t} {
        adj=vector<vector<edge>>(sz);
    }
    
    bool bfs() {
        level=vector<int>(sz, -1);
        level[Src]=0;
        queue<int> q;
        q.push({Src});
        
        while(!q.empty() and level[Ter]==-1) {
            int cur = q.front();
            q.pop();
            
            for(int i=0;i<adj[cur].size();++i) {
                edge tmp=adj[cur][i];
                int nxt=tmp.to;
                
                if(level[nxt]==-1 and tmp.cap>0){
                    level[nxt]=level[cur]+1;
                    if(nxt==Ter) break;
                    q.push(nxt);
                }
            }
        }
        return level[Ter]!=-1;
    }
    
    int dfs(int cur, int flow) {
        if(cur==Ter) return flow;
        
        for(int &i=work[cur]; i<adj[cur].size();i++) {
            edge tmp=adj[cur][i];
            int nxt = tmp.to;
            if(level[nxt]==level[cur]+1 and tmp.cap>0) {
                int f=dfs(nxt, min(flow, tmp.cap));
                if(!f) continue;
                adj[cur][i].cap-=f;
                adj[nxt][tmp.rev].cap+=f;
                return f;
            }
        }
        return 0;
    }
    
    
    int solve() {
        int total=0;
        while(bfs()) {
            work=vector<int>(sz,0);
            while(1) {
                int flow=dfs(Src, INT_MAX);
                if(!flow) break;
                
                total+=flow;
            }
        }
        return total;
    }
    
    void link(int u, int v, int c) {
        adj[u].push_back({v, c, (int)adj[v].size()});
        adj[v].push_back({u, 0, (int)adj[u].size()-1});
    }
};

int main() {
    int n,m,k; scanf("%d%d%d", &n, &m, &k);
    MF mf(n+m+3, 0, n+m+2);
    mf.link(0, n+m+1, k);
    
    for(int i=1;i<=n;i++){
        mf.link(0, i, 1);
        mf.link(n+m+1, i, 1);
        int c; scanf("%d", &c);
        
        for(int j=0;j<c;j++) {
            int t; scanf("%d", &t);
            mf.link(i, n+t, 1);
        }
    }
    
    for(int j=1;j<=m;j++) {
        mf.link(n+j, n+m+2, 1);
    }
    
    printf("%d\n", mf.solve());
    return 0;
}