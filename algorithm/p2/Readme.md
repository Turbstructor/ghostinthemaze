Problem 2. Prefix Sum

보안이는 구간합 또한 사랑한다.
그런데 구간합을 빠르게 구하지는 못 하나보다.
그를 도와줘서 구간합이 빠르게 진행되게 도와주자.

parameter로는 구간합을 진행할 배열(arr) 와 구간합을 묻는 질문의 갯수(num_query)와
구간합을 묻는 질문들(query)이 input으로 들어온다.

output으로는 각각의 질문들을 순서대로 대답이 push_back된 vector(query)를 return 한다

ex)

Input
    arr = { 1, 2, 3, 4, 5 };
    num_query = 2;
    query = { { 2,  3}, { 1, 4 } };

Output
    result = { { 5 }, { 10 }};    // ( 2 + 3 ), ( 1 + 2 + 3 + 4 )


제약조건 :
time < 1 sec
arr.size < 10000000

마찬가지로 ($make)를 통해 빌드하면 p2.exe가 생성되는데 만약 소정의 testcase와 제약조건을 만족시킨다면 다음 문제를 위한 비밀번호를 제공한다. 다음 문제도 같은 방식으로 진행되기 때문에 이와같은 설명을 생략하겠다. 
