#include<vector>
#include<iostream>
using namespace std;

int solution(vector<int> &A) {
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
  vector<int> A = {3, 4, 6, 7, 7, 3, 9};
  count << solution(A);
  return 0;  
}
