/*
Given a string s, return the longest palindromic substring in s.

Example 1:
Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:
Input: s = "cbbd"
Output: "bb"
 
Constraints:
1 <= s.length <= 1000
s consist of only digits and English letters.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        
        int sIndex = 0;
        int sLength = 0;
        for(int i = 0; i < n; i++){
          
          // odd string length
          lengthOfPalString(s, i, i, sIndex, sLength);
          // even string length
          lengthOfPalString(s, i, i+1, sIndex, sLength);
        }
        return s.substr(sIndex, sLength);
    }
private:
    void lengthOfPalString(string& str, int left, int right, int& sIdx, int& sLen)
    {
        while( left >= 0 && right < str.size() )
          {
            if(str[left] == str[right])
            {
                if(sLen < (right - left + 1))
                {
                    sLen = (right - left + 1);
                    sIdx = left;
                }
                left--;
                right++;
            }
            else
            {
                break;
            }
        }
    }
};

int main() {
    Solution sol;

    string test1 = "babad";
    string test2 = "cbbd";
    
    // 3. Call the function and print the results
    cout << "Test 1 ('babad'): " << sol.longestPalindrome(test1) << " (Expected: bab)" << endl;
    cout << "Test 2 ('cbbd'): " << sol.longestPalindrome(test2) << " (Expected: bb)" << endl;

    return 0;
}
