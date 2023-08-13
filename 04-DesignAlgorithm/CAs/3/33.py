import heapq
from collections import defaultdict

INF = int(1e18 + 1e5)
mod = int(1e9 + 7)
MAXN = 100010

n, m = map(int, input().split())
majid, s, t = map(int, input().split())

topol = [0] * MAXN
mark = [0] * MAXN
good = [0] * MAXN
dp1 = [0] * MAXN
dp2 = [0] * MAXN
G = defaultdict(list)
dist = [INF] * MAXN
pq = []

def relax(v, d):
    if d < dist[v]:
        dist[v] = d
        heapq.heappush(pq, (d, v))

def dijkstra(src):
    global dist, mark, topol, k
    dist = [INF] * MAXN
    mark = [0] * MAXN
    relax(src, 0)
    k = 0
    while pq:
        u = heapq.heappop(pq)[1]
        if mark[u]:
            continue
        mark[u] = 1
        k += 1
        topol[k] = u
        for v, w in G[u]:
            relax(v, dist[u] + w)

def fix(x):
    if x >= mod:
        x -= mod

def is_ok(u, v, w):
    return dist[u] + w == dist[v]

for _ in range(m):
    u, v, w = map(int, input().split())
    G[u].append((v, w))
    G[v].append((u, w))

dijkstra(s)

if dist[t] >=  INF:
    print("-1")
else:
    dp1[s] = dp2[t] = 1
    for i in range(1, k + 1):
        u = topol[i]
        for v, w in G[u]:
            if is_ok(u, v, w):
                fix(dp1[v] + dp1[u])
                dp1[v] += dp1[u]
    for i in range(k, 0, -1):
        u = topol[i]
        for v, w in G[u]:
            if is_ok(u,v,w):
                fix(dp2[u]+dp2[v])
                dp2[u]+=dp2[v]
    
    for v in range(1,n+1):
        good[v]=(dp1[v]*dp2[v]%mod==dp1[t])
    
    dijkstra(majid)
    
    ans=INF
    
    for v in range(1,n+1):
        if good[v]:
            ans=min(ans,dist[v])
    
    if ans>=INF:
        ans=-1
    
    print(ans)
    