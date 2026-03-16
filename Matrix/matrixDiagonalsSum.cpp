#include <iostream>
#include <vector>

int diagonalsSum(std::vector<std::vector<int>>& mat)
{
    int n = mat.size();
    int sum = 0;
    
    for(int i = 0; i < n; i++){
        
        // NO need to check row and column equality
        sum += mat[i][i];
        
        if(i != n-i-1)
        {
            sum += mat[i][n-i-1];
        }
    }
    return sum;
}

int main()
{
    /*
    // Even length matrix
    std::vector<std::vector<int>> mat =
    {
        {1,4,7,11},
        {2,5,8,12},
        {3,6,9,16},
        {10,13,14,17}
    };
    */
    // odd Length matrix
    std::vector<std::vector<int>> mat =
    {
        {1,4,7},
        {2,5,8},
        {3,6,9}
    };
    
    
    auto result = diagonalsSum(mat);

    std::cout<<"Diagonals sum = "<<result<<std::endl;


    return 0;
}
