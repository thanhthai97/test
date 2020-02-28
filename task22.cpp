#include <vector>
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