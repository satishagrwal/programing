#include <iostream>
#include <string>
#include <algorithm>

void reverseWordsOrder(std::string& s)
{
    // reverse whole string first
    std::reverse(s.begin(), s.end());
    
    std::cout << s << std::endl;
    int n = s.size();
    int start = 0;
  
    // Reverse each workd separately
    for(int end = 0; end <= n; end++){
        if(end == n || s[end] == ' '){
            std::reverse(s.begin() + start, s.begin() + end);
            start = end + 1;
        }
    }
}

int main() {
    std::string s = "The sky is blue";
    reverseWordsOrder(s);
    std::cout << "Reversed Order: [" << s << "]" << std::endl;
    return 0;
}
