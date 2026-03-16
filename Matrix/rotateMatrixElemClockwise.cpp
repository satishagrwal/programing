/*
Given a matrix, clockwise rotate elements in it.
For 3*3 matrix
------------------
Input: 
1    2    3
4    5    6
7    8    9

Output:
4    1    2
7    5    3
8    9    6

For 4*4 matrix
-------------------
Input:
1    2    3    4    
5    6    7    8
9    10   11   12
13   14   15   16

Output:
5    1    2    3
9    10   6    4
13   11   7    8
14   15   16   12

*/

#include <iostream>
#include <vector>

using namespace std;

void rotateBoundary(vector<vector<int>>& mat)
{
    int n = mat.size();
    int m = mat[0].size();

    int prev = mat[1][0];

    // top row
    for(int j=0;j<m;j++)
    {
        int curr = mat[0][j];
        mat[0][j] = prev;
        prev = curr;
    }

    // right column
    for(int i=1;i<n;i++)
    {
        int curr = mat[i][m-1];
        mat[i][m-1] = prev;
        prev = curr;
    }

    // bottom row
    for(int j=m-2;j>=0;j--)
    {
        int curr = mat[n-1][j];
        mat[n-1][j] = prev;
        prev = curr;
    }

    // left column
    for(int i=n-2;i>=0;i--)
    {
        int curr = mat[i][0];
        mat[i][0] = prev;
        prev = curr;
    }
}

void printMatrix(vector<vector<int>>& mat)
{
    for(auto &row : mat)
    {
        for(int v : row)
            cout << v << " ";

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

    rotateBoundary(mat);

    printMatrix(mat);
}
