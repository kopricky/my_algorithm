#include "../header.hpp"

//負の辺が存在する場合の最小費用流(ベルマンフォードでポテンシャルを計算可能)
//最小費用がint,頂点数がn
//min_cost_flow<int> mcf(n);
//適宜add_edge
//mcf.solve(始点,終点,流量)で最小費用流を計算
template<typename T> class min_cost_flow{
public:
    struct edge {
        int to,cap;
        T cost;
        int rev;
    };
	using pti = pair<T,int>;
    vector<vector<edge> > G;
	vector<T> h,dist;
	vector<int> prevv,preve;
	T inf;
    int V;
    min_cost_flow(int node_size){
        V = node_size;
		inf = numeric_limits<T>::max() / 100;
        G.resize(V), h.resize(V), dist.resize(V), prevv.resize(V), preve.resize(V);
	}
    void add_edge(int from, int to, int cap, T cost){
        G[from].push_back((edge){to, cap, cost, (int)G[to].size()});
        G[to].push_back((edge){from, 0, -cost, (int)G[from].size() - 1});
    }
    T solve(int s,int t,int f){
        T res = 0;
        fill(h.begin(),h.end(),inf);
        h[s] = 0;
        bool update = true;
        while(update){
            update = false;
            rep(v,V){
                if(h[v] == inf){
                    continue;
                }
                rep(i,G[v].size()){
                    edge& e = G[v][i];
                    if(e.cap > 0 && h[e.to] > h[v] + e.cost){
                        h[e.to] = h[v] + e.cost;
                        update = true;
                    }
                }
            }
        }
        while(f > 0){
            priority_queue<pti,vector<pti>,greater<pti> > que;
            fill(dist.begin(),dist.end(),inf);
            dist[s] = 0;
            que.push(pti(0,s));
            while(!que.empty()){
                pti p = que.top();
                que.pop();
                int v = p.second;
                if(dist[v] < p.first){
                    continue;
                }
                rep(i,G[v].size()){
                    edge& e = G[v][i];
                    if(e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]){
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prevv[e.to] = v, preve[e.to] = i;
                        que.push(pti(dist[e.to], e.to));
                    }
                }
            }
            if(dist[t] == inf){
                return -1;
            }
            rep(i,V){
                h[i] += dist[i];
            }
            int d = f;
            for(int v = t; v != s; v = prevv[v]){
                d = min(d, G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d * h[t];
            for(int v = t; v != s;v = prevv[v]){
                edge& e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};
