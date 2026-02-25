/*
Given two arrays, deadline[] and profit[], where deadline[i] is the last time unit by which the i-th job must be completed, and profit[i] is the profit earned from completing it.
Each job takes 1 unit time, and only one job can be scheduled at a time. A job earns profit only if finished within its deadline. Find the number of jobs completed and maximum profit.

Examples:
Input: deadline[] = [4, 1, 1, 1], profit[] = [20, 10, 40, 30]
Output: [2, 60]
Explanation: Job 1 (profit 20, deadline 4) can be scheduled. Among the three jobs with deadline 1, only one fits, so we pick the highest profit (40). Hence, 2 jobs with total profit = 60.

Input: deadline[] = [2, 1, 2, 1, 1], profit[] = [100, 19, 27, 25, 15]
Output: [2, 127]
Explanation: Picking the job with profit 100 (deadline 2) and the job with profit 27 (deadline 2); they can occupy the two available slots before deadline 2. Thus 2 jobs are scheduled for a maximum total profit of 127.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Job {
    char id;
    int deadline;
    int profit;
};

bool compare(Job a, Job b) {
    return a.profit > b.profit;
}


void solve(Job arr[], int n) {
    sort(arr, arr + n, compare);

    // 1. Find the maximum deadline to size the slots correctly
    int maxDeadline = 0;
    for (int i = 0; i < n; i++) 
        maxDeadline = max(maxDeadline, arr[i].deadline);

    int maxProfit = 0, count = 0;
    // 2. Size based on maxDeadline
    vector<int> slot(maxDeadline + 1, -1); 

    for (int i = 0; i < n; i++) {
        // 3. Start from the job's deadline and move backwards
        for (int j = arr[i].deadline; j > 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i; 
                maxProfit += arr[i].profit;
                count++;
                break;
            }
        }
    }

    cout << "Scheduled Jobs: " << count << "\nTotal Profit: " << maxProfit << endl;
}

int main() {
    //Job arr1[] = { {'a', 4, 20}, {'b', 1, 10}, {'c', 1, 40}, {'d', 1, 30} };
    Job arr1[] = { {'a', 2, 100}, {'b', 1, 19}, {'c', 2, 27}, {'d', 1, 25}, {'d', 1, 15}  };
    int n = sizeof(arr1) / sizeof(arr1[0]);
    
    solve(arr1, n);
    return 0;
}
