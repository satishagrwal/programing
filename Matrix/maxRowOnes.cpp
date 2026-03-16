#include <iostream>
#include <vector>

using namespace std;

/*
int maxRowOnes(vector<vector<int>>& mat)
{
    int rows = mat.size();
    int cols = mat[0].size();

    int maxRow = -1;
    int maxCount = 0;

    for(int i = 0; i < rows; i++)
    {
        int count = 0;

        for(int j = 0; j < cols; j++)
        {
            if(mat[i][j] == 1)
                count++;
        }

        if(count > maxCount)
        {
            maxCount = count;
            maxRow = i;
        }
    }

    return maxRow;
}
*/

int rowWithMaxOnes(vector<vector<int>>& mat)
{
    int rows = mat.size();
    int cols = mat[0].size();

    int i = 0;
    int j = cols - 1;

    int maxRow = -1;

    while(i < rows && j >= 0)
    {
        if(mat[i][j] == 1)
        {
            maxRow = i;
            j--;
        }
        else
        {
            i++;
        }
    }

    return maxRow;
}

int main()
{
    vector<vector<int>> mat =
    {
        {0,0,0,1},
        {0,1,1,1},
        {0,0,1,1},
        {0,0,0,0}
    };

    cout << "Row with max 1s = " << rowWithMaxOnes(mat) << endl;

    return 0;
}
