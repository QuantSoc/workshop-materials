#include <iostream>
#include <vector>

using namespace std;

int solveTrappingRainwater(vector<int> &heights) {
    // todo: solve this
    int n = heights.size();

    vector<int> leftMax(n);
    vector<int> rightMax(n);

    int runningMax = heights[0];
    for (int i = 0; i < heights.size(); i++) {
        runningMax = max(runningMax, heights[i]);
        rightMax[i] = runningMax;
    }

    runningMax = 0;
    for (int i = n-1; i >= 0; i--) {
        runningMax = max(runningMax, heights[i]);
        leftMax[i] = runningMax;
    }

    int totalWater = 0;
    for (int i = 0; i < n; i++) {
        totalWater += max(min(leftMax[i], rightMax[i]) - heights[i], 0);
    }

    return totalWater;
}

int main() {
    vector<int> heights = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

    cout << "Expected Answer: 6\n";
    cout << "Actual Answer: " << solveTrappingRainwater(heights) << "\n";
}

