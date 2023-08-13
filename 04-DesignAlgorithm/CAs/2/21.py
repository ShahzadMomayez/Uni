def solve(tl, tr, h):
    if tr - tl == 0:
        return 0
    mid = A[tl:tr].index(min(A[tl:tr])) + tl
    return min(solve(tl, mid, A[mid]) + solve(mid + 1, tr, A[mid]) + A[mid] - h, tr - tl)

n = int(input())
A = [0] + list(map(int, input().split()))

print(solve(1, n + 1, 0))