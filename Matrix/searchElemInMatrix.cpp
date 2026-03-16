#include <iostream>
#include <vector>

using namespace std;

bool searchMatrix(vector<vector<int>>& mat, int target)
{
    if(mat.empty() || mat[0].empty())
        return false;

    int rows = mat.size();
    int cols = mat[0].size();

    int i = 0;
    int j = cols - 1;

    while(i < rows && j >= 0)
    {
        if(mat[i][j] == target)
            return true;

        else if(mat[i][j] > target)
            j--;   // move left

        else
            i++;   // move down
    }

    return false;
}

int main()
{
    vector<vector<int>> mat =
    {
        {1,4,7,11},
        {2,5,8,12},
        {3,6,9,16},
        {10,13,14,17}
    };

    int target = 6;

    if(searchMatrix(mat, target))
        cout << "Element found\n";
    else
        cout << "Element not found\n";

    return 0;
}
