#include <iostream>
#include <vector>
using namespace std;

vector<int> solution(vector<int> &A, int K)
{
    //vector<int> A = {3,8,9,7,6};
    int temp;
    int n = A.size();
    if(n == 0) return A;
    if(K>=n) K = K-n;
    for (int i =0;i<K;i++)
    {
        temp = A[n-1];
        for(int i=n; i>0;i--)
        {
            A[i] = A[i-1];
        }
        A[0] = temp;
    }
    cout << "[";
    for (int i=0; i < n;i++)
    {
        
        cout<<A[i];
        if(i<n-1) cout << ", ";
        else if(i==(n-1)) cout << ']';
    }
    return A;
}

int main()
{
    vector<int> A = {};
    solution( A, 1);
    
}