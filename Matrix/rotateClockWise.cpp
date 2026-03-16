#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void rotateClockwise(vector<vector<int>>& mat)
{
    int n = mat.size();

    // Step 1: Transpose
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            swap(mat[i][j], mat[j][i]);
        }
    }

    // Step 2: Reverse each row
    for(int i = 0; i < n; i++)
    {
        reverse(mat[i].begin(), mat[i].end());
    }
}

void printMatrix(vector<vector<int>>& mat)
{
    for(auto &row : mat)
    {
        for(int val : row)
            cout << val << " ";

        cout << endl;
    }
}

int main()
{
    vector<vector<int>> mat =
    {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };

    rotateClockwise(mat);

    printMatrix(mat);
}
