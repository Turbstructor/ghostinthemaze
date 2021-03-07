/* Problem 2. Prefix Sum
 *  
 * 보안이는 구간합 또한 사랑한다. 
 * 그런데 구간합을 빠르게 구하지는 못 하나보다.
 * 그를 도와줘서 구간합이 빠르게 진행되게 도와주자.
 * 
 * parameter로는 구간합을 진행할 배열(arr) 와 구간합을 묻는 질문의 갯수(num_query)와 
 * 구간합을 묻는 질문들(query)이 input으로 들어온다.
 *
 * output으로는 각각의 질문들을 순서대로 대답이 push_back된 vector(query)를 return 한다
 *
 * ex)
 * 
 * Input
 *      arr = { 1, 2, 3, 4, 5 };
 *      num_query = 2;
 *      query = { { 2,  3}, { 1, 4 } };
 *
 * Output
 *      result = { { 5 }, { 10 }};    // ( 2 + 3 ), ( 1 + 2 + 3 + 4 )
 * 
 *
 * 제약조건 :
 * time < 1 sec
 * arr.size < 10000000
 *
 */

#include <stdio.h>
#include <vector>

using namespace std;


vector<long long> prefix_Sum(vector<int> arr, int num_query, vector <pair <int, int> > query){
        int arr_size = arr.size();
        vector<long long> sum(arr_size);
        vector<long long> result;


        for(int i = 0; i < num_query; i++){
                int low = query[i].first;
                int high = query[i].second;
                long long subSum = 0;

                for(int j = low; j <= high; j++){
                        subSum += arr[j];
                }

                result.push_back(subSum);
                
        }
        return result;
}
