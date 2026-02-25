/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.
Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
 

Constraints:

3 <= nums.length <= 3000
-105 <= nums[i] <= 105
*/
/*
Brute force

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
       int n = nums.size();
       set<vector<int>> uniqueTriplet;
       for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            for(int k = j+1; k < n; k++){
                if( (nums[i] + nums[j] + nums[k]) == 0 )
                {
                   vector<int> tmp = {nums[i], nums[j], nums[k]};
                   sort(tmp.begin(), tmp.end());
                   uniqueTriplet.insert(tmp);
                }
            }
        }
       }
       vector<vector<int>> result(uniqueTriplet.begin(), uniqueTriplet.end());
       return result; 
    }
};
*/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
      int n = nums.size();
      sort(nums.begin(), nums.end());
      set<vector<int>> uniqueTriplet;

      for(int i = 0; i < n; i++)
      {
        int a = nums[i];
        int left = i + 1;
        int right = n - 1;
        while(left < right)
        {
            int currSum = a + nums[left] + nums[right];
            if(currSum == 0)
            {
               uniqueTriplet.insert({nums[i], nums[left], nums[right]});
               left++;
               right--;
            }
            else if( currSum < 0)
            {
                left++;
            }
            else
            {
                right--;
            }
        } 
       }
       vector<vector<int>> result(uniqueTriplet.begin(), uniqueTriplet.end());
       return result;
    }
};
