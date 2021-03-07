/* Disjonted Union
 *
 * 보안이는 분리 집합을 사랑한다. 
 * N개의 node 가 주어지고 M개의 edges 가 주어졌을 때 
 * 임의의 노드 a와 b가 서로 같은 그래프에 속해있는지 확인하는 코드를 짰으나
 * 이번에는 그의 고양이가 그의 컵을 엎질러 코드가 상당부분이 지워졌다.
 * 
 * 지워진 코드를 복구해 다시 사용가능하게 바꿔주자.
 * 단, 지워진 부분(코멘트 처리된 부분)외에는 수정해서는 안된다.
 * 보안이가 매우 싫어할 것이다.
 * 
 * use_union의 인풋으로는 graph의 edge들의 배열이 주어지고 (query). 두 수(a, b) 가 같은 집합인지 알아낸다. 만약 같은 집합이라면 is_union 은 true로 , 아니라면 false 가 된다.
 *
 * ex)
 * Input
 *      query = { { 1, 2 }, { 3, 4 } };
 *      a = 1 ;
 *      b = 2 ;
 *      
 * Output
 *      is_union = true;
 *
 * 제약조건 : 
 * time < 2 sec
 *
 */
#pragma once

#include <stdio.h>
#include <vector>
#include <utility>
#include <string.h>


using namespace std;

const int MAX = 10000;

int parent[MAX];
int N, M; // N == num of nodes, M = num of edges

//find
int find(int u){
        /*                                */
        return /*                  */
}
// merge
void merge(int a, int b){
        /*                       */
}

bool use_union(vector<pair<int, int>> query , int a, int b){
        
        bool is_union = false; 
        
        // initialize
        memset(parent, 0, sizeof(parent));
        for(int i = 0; i < MAX; i++){
                parent[i] = i;
        }

        for(int i = 0 ; i < query.size(); i++){
                int node1 = query[i].first;
                int node2 = query[i].second;
                merge(node1, node2);
        }
        // check
        if(/*               */)
                is_union = true;
        
        if(is_union)
                printf("a and b are in the same group\n");
        else
                printf("a and b are not in the same group\n");

        return is_union;
}
