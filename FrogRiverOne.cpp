#include <iostream>
#include <vector>

using namespace std;

int solution(int X, vector<int> &A)
{
    int n = A.size();
    for(int i=0;i<n;i++)
    {
        if(A[i]==X)
        {
            return i; break;
        }
    }
    return -1;
}
int main()
{
    vector<int> A = {1,3,1,4,2,3,9,4,7,6};
    cout << solution(5,A);
    return 0;
}