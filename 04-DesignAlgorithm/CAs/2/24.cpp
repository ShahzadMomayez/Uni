/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int n, m, t;
    cin >> n >> m >> t;
    
    vector<int> e(n), d(n);
    for (int i = 0; i < n; i++) {
        cin >> e[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    
    vector<vector<int>> adjM(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++) {
        int g1, g2;
        cin >> g1 >> g2;
        adjM[g1-1][g2-1] = adjM[g2-1][g1-1] = 1;
    }
    
    vector<vector<int>> planet;
    vector<int> bD;
    int size = adjM.size();
    vector<bool> isVisited(size, false);
    vector<int> q(1, 0);
    isVisited[0] = true;
    vector<int> asteroid;
    int biodiversity = 0;
    
    while (!q.empty()) {
        int node = q[0];
        q.erase(q.begin());
        
        if (find(asteroid.begin(), asteroid.end(), node) == asteroid.end()) {
            asteroid.push_back(node);
            biodiversity += d[node];
        }
        
        for (int i = 0; i < size; i++) {
            if (!isVisited[i] && adjM[node][i] == 1) {
                q.push_back(i);
                asteroid.push_back(i);
                biodiversity += d[i];
                isVisited[i] = true;
            }
        }
        
        if (q.empty()) {
            planet.push_back(asteroid);
            bD.push_back(biodiversity);
            
            for (int j = 0; j < size; j++) {
                if (!isVisited[j]) {
                    asteroid.clear();
                    biodiversity = 0;
                    isVisited[j] = true;
                    q.push_back(j);
                    break;
                }
            }
        }
    }
    
    size = planet.size();
    vector<int> allJungles(size, 0);
    vector<vector<int>> bestJungle(size, vector<int>(2, 0));
    vector<vector<int>> dp(size + 1, vector<int>(t + 1, 0));
    
    for (int i = 0; i < size; i++) {
        int all = 0, one = INT_MAX, bio = -1;
        for (int j = 0; j < planet[i].size(); j++) {
            int index = planet[i][j];
            all += e[index];
            if (one > e[index]) {
                bio = d[index];
                one = e[index];
            }
        }
        allJungles[i] = all;
        bestJungle[i][0] = one;
        bestJungle[i][1] = bio;
    }
    
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= t; j++) {
            if (j < bestJungle[i - 1][0]) {
                dp[i][j] = dp[i - 1][j];
                continue;
            }
            
            int s = planet[i - 1].size();
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - bestJungle[i - 1][0]] + bestJungle[i - 1][1]);
            
            for (int k = 0; k < s; k++) {
                int index = planet[i - 1][k];
                if (e[index] <= j) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - e[index]] + d[index]);
                }
            }
            
            if (j >= allJungles[i - 1]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - allJungles[i - 1]] + bD[i - 1]);
            }
        }
    }
    
    cout << dp[size][t] << endl;
    
    return 0;
}