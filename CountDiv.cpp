#include <iostream>

using namespace std;
int solution(int A, int B, int K)
{
    int c=0;
    //if(A>B) return c;
    int boisoA = A/K;
    int minz = boisoA*K;
    for(int i = minz; i <= B; i+=K)  
    {if(i>=A) c++;}
    
    return c;
    
}
int main()
{
    cout<< solution(6,11,2);
    return 0;
}