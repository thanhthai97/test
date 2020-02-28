#include <vector>
#include <iostream>
using namespace std;
int solution(vector<int> &A)
{
    unsigned int size = A.size();
        unsigned long long int sum = 0;
        
        for (unsigned int i=0; i<size; i++) {
            // A xor B xor A = B
            sum ^= A[i];
        }
        
        return sum;
}
int main()
{
    vector<int> A = {3,3,5,4,5,7,4};
    int a = solution(A);
    cout << a;
}