/*
Given a string s, return the number of substrings within s that are palindromes.
A palindrome is a string that reads the same forward and backward.

Example 1
Input: s = "abc"
Output: 3
Explanation: "a", "b", "c".

Example 2:
Input: s = "aaa"
Output: 6
Explanation: "a", "a", "a", "aa", "aa", "aaa". Note that different substrings are counted as different palindromes even if the string contents are the same.

Constraints:
1 <= s.length <= 1000
s consists of lowercase English letters.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Solution {
public:
    int countSubstrings(string s) {
      int res = 0;
      int n = s.size();
      for(int i = 0; i < n; i++){
          // odd length string
          res += isPalindrom(s, i, i);
          // even length string
          res += isPalindrom(s, i, i+1);
      }
      return res;  
    }
private:
   int isPalindrom(const string& str, int left, int right){
        int count = 0;
        while( left >= 0 && right < str.size() ){
            if(str[left] == str[right]){ 
                count++;
                left--;
                right++;
            }
            else
            {
               break;
            }
        }
        return count;
    }
};

/*
// Brute force
class Solution {
public:
    bool isPalindrom(string str, int left, int right){
        while( left < right ){
            if(str[left] != str[right]) return false;

            left++;
            right--;
        }
        return true;
    }
    int countSubstrings(string s) {
      int n = s.size();
      int count = 0;
      for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(isPalindrom(s, i, j)){
                count++;
            }
        }
      }
      return count;  
    }
};

*/
int main() {
    Solution sol;

    string test1 = "abc";
    string test2 = "aaa";

    cout << "Test 1 ('abc'): " << sol.countSubstrings(test1) << " (Expected: 3)" << endl;
    cout << "Test 2 ('aaa'): " << sol.countSubstrings(test2) << " (Expected: 6)" << endl;

    return 0;
}
