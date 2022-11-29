// 2316. 도시 왕복하기 2
// max flow

#include<bits/stdc++.h>

using namespace std;
const int Inf = 1e9;

struct MF{
    struct edge{
        int to, cap, flow, rev;
    };
    
    int sz, Src, Ter;
    vector<vector<edge>> adj;
    vector<int> level, work;
    
    MF(int sz, int S, int T) : sz{sz}, Src{S}, Ter{T} {
        adj=vector<vector<edge>>(sz);
    }
    
    bool bfs(){
        level=vector<int>(sz, -1);
        level[Src]=0;
        queue<int> q;
        q.push(Src);
        
        while(!q.empty() && level[Ter]==-1){
            int cur=q.front();
            q.pop();
            
            for(int i=0;i<adj[cur].size();i++){
                edge te=adj[cur][i];
                int nxt=te.to;
                if(level[nxt]==-1 and te.cap-te.flow>0){
                    level[nxt]=level[cur]+1;
                    if(nxt==Ter) break;
                    q.push(nxt);
                }
            }
        }
        
        return level[Ter]!=-1;
    }
    
    int dfs(int cur, int flow){
        if(cur==Ter) return flow;
        
        for(int &i=work[cur];i<adj[cur].size();i++){
            edge te=adj[cur][i];
            int nxt=te.to;
            if(level[nxt]==level[cur]+1 and te.cap-te.flow>0){
                int f=dfs(nxt, min(flow, te.cap-te.flow));
                if(!f) continue;
                
                adj[cur][i].flow+=f;
                adj[nxt][te.rev].flow-=f;
                
                return f;
            }
        }
        return 0;
    }
    
    int solve(){
        int tFlow=0;
        while(bfs()){
            work=vector<int>(sz,0);
            while(1){
                int flow=dfs(Src, Inf);
                if(!flow) break;
                tFlow+=flow;
            }
        }
        return tFlow;
    }
    
    void link(int u, int v, int cap){
        adj[u].push_back({v, cap, 0, (int)adj[v].size()});
        adj[v].push_back({u, 0, 0, (int)adj[u].size()-1});
    }
};

int main(){
    int n,p; scanf("%d%d", &n,&p);
    MF mf(2*n+1, 1, 2+n);
    for (int i=0; i<p; ++i) {
        int u, v; scanf("%d%d", &u,&v);
        mf.link(u+n, v, 1);
        mf.link(v+n, u, 1);
    }
    
    for (int i=3; i<=n; ++i) {
        mf.link(i, i+n, 1);
    }
    mf.link(1, n+1, Inf);
    mf.link(2, n+2, Inf);
    
    printf("%d\n", mf.solve());
    
    return 0;
}