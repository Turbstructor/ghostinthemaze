/* 유클리드 호제법
 *
 * 보안이는 최대공약수를 사랑한다.
 * 그는 두 수가 주어지면 그 수의 최대 공약수를 알고 싶어하지만 그가 만든 프로그램은 비효율적이다.
 * 
 * 그의 프로그램을 발전시키보자.
 * 
 * ex)
 *      gcd(5, 15) = 5
 *      gcd(12, 18) = 6 
 * 
 *      
 * 제약조건 : 
 * time < 2 sec
 *
 */

#include <stdio.h>

using namespace std;

int gcd(int a, int b){
        int bigger = a;
        int smaller = b;
        int i;

        if(b > a){
                bigger = b;
                smaller = a;
        }
        for(i = smaller; i > 0; i--){
                if(bigger % i == 0 && smaller % i == 0)
                        break;
        }
        return i; 
}
