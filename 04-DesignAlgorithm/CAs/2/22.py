m, n = map(int, input().split())

orkMap = [list(map(int, input().split())) for _ in range(m)]

dpLtR = [0] * n
dpRtL = [0] * n

for j in range(1, n):
    orkMap[0][j] += orkMap[0][j-1]

for i in range(1, m-1):
    dpLtR[0] = orkMap[i-1][0] + orkMap[i][0]
    for j in range(1, n):
        dpLtR[j] = min(dpLtR[j-1], orkMap[i-1][j]) + orkMap[i][j]
    dpRtL[n-1] = orkMap[i-1][n-1] + orkMap[i][n-1]
    for j in range(n-2, -1, -1):
        dpRtL[j] = min(dpRtL[j+1], orkMap[i-1][j]) + orkMap[i][j]

    for j in range(n):
        orkMap[i][j] = min(dpRtL[j], dpLtR[j])

orkMap[m-1][0] += orkMap[m-2][0]
for j in range(1, n):
    orkMap[m-1][j] += min(orkMap[m-1][j-1], orkMap[m-2][j])

print(orkMap[m-1][n-1])