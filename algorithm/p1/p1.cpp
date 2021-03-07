/* Memoization

보안이는 피보나치 수열을 사랑한다. 그는 매일매일 피보나치 수열을 학습하고자해서 프로그램을 짜고자 하였다. 
하지만 피보나치 수를 구하는데 아래의 프로그램은 연산이 너무 많이 필요하고 오래걸려 화가 나서 당신에게 도움을 요청한다.

조건

n <= 500
시간제약 :  < 1 sec


*/


#include <stdio.h>

extern bool checktime();

long long fib(long long n){
    if(n <= 2)
        return 1;
    
    return fib(n - 1) + fib(n - 2);
}
