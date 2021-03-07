/* 보안이는 추후에 있을 시험을 위해 dfs와 bfs를 공부하다가 그만 커피를 쏟았다.
 * 그 때문에 아래 코드의 몇줄이 지워졌다. 
 * 끊임없는 시험에 지친 보안이를 위해 지워진 코드를 복구해주자
 * (comment 처리로 지워진 부분만 고치면 된다. )
 *
 *
 * N 은 graph node의 갯수이고 
 * V 는 dfs 혹은 bfs를 시작하는 node의 번호이다.
 * 
 * ex:
 *
 * Input 
 *      mat =
 *            { { 0, 1, 0, 0, 1 },
 *              { 1, 0, 1, 1, 0 },
 *              { 0, 1, 0, 1, 0 },
 *              { 0, 1, 1, 0, 0 },
 *              { 1, 0, 0, 0, 0 } };
 *               
 * Output
 *      dfs_visit = { 2, 1, 5, 3, 4 };
 *      bfs_visit = { 2, 1, 3, 4, 5 };
 * 
 *
 * 결과값은 g_*_result 에 순서대로 넣어주자.
 *
 * 
 */

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

// Result
vector<int> g_dfs_result;
vector<int> g_bfs_result;


#define MAX_VALUE 1001           

int N, V;                       // 노드의 갯수, 시작할 노드 번호 
int mat[MAX_VALUE][MAX_VALUE];  // 인접행렬 배열
int dfs_visit[MAX_VALUE];       // dfs 결과값 
int bfs_visit[MAX_VALUE];       // bfs 결과값

void dfs(int v) {
        g_dfs_result.push_back(v);
        /*            */       
        for(int i = 1; i <= N; i++) {
                if(/*                  */)     
                        continue;
                /*        */
        }
}

void bfs(int v) {     
        queue<int> q;
        /*          */
        bfs_visit[v] = 1;
        
        while(!q.empty()) {
                v = q.front();
                g_bfs_result.push_back(v);
                /*           */
                for(int i = 1; i <= N; i++) {
                        if(/*                */)
                                continue;
                        /*        */
                        bfs_visit[i] = 1;
                }
        }
}
