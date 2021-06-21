#include <iostream>

using namespace std;

const int NUM = 4;
const int PACKAGE = 7;

int main() {

    const int c[NUM+1] = {0,1,4,5,7};
    const int w[NUM+1] = {0,1,3,4,5};
    const int pkg = 7;
    { // 空间复杂度 o(num * package)
        int dp[NUM+1][PACKAGE+1] = {
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,
        };

        for (int i = 1; i < NUM+1; i++) {
            for (int k = 1; k < PACKAGE+1; k++) {
                int use = (k-w[i] >= 0) ? (c[i]+dp[i-1][k-w[i]]) : 0;
                int nuse = dp[i-1][k];
                dp[i][k] = max(use, nuse);
            }
        }

        cout << "dp1: " << dp[NUM][PACKAGE] << endl;
    }
    {
        // 优化 dp[i] 只与 dp[i-1] 相关，可以将空间复杂度优化为 o(package)
        // 状态转移方程：dp[k] = max(c[i]+dp[k-w[i]], dp[k])
        int dp[PACKAGE+1] = {0};

        for (int i = 1; i < NUM+1; i++) {
            for (int k = PACKAGE; k >= 1; k--) {
                int use = (k - w[i] >= 0) ? (dp[k - w[i]] + c[i]) : 0;
                int nuse = dp[k];
                dp[k] = max(use, nuse);
                // cout << i << " -> " << dp[k] << ";";
            }
            // cout << endl;
        }

        cout << "dp2: " << dp[PACKAGE] << endl;
    }
    return 0;
}