#include<iostream>
#include <vector>
using namespace std;
int solution(vector<int> &A)
{
    unsigned long long int n = A.size();
    double sum=0;
    for (long long int i =0; i<n;i++)
    {
        sum += A[i];
    }
    double total = ((n)*(n+1))/2;
    if (sum == total) return 1;
    else return 0;
    //return total;
}
int main()
{
    vector<int> A = {1,3};
    cout<< solution(A);
}