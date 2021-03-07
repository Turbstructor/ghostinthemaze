#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 300
#define NUM_PROBLEMS 5
#define TIME_LIMIT 30
#define PASSWORD "i09gas"
#define END_MESSAGE "FINISH"

void error_handling(char *message);

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


// 1. recieve answer from client
// 2. check if the recieved answer is correct
// 3. if correct send next level question
//      (if not correct send previous question)

int question(char* quest, char* ans, int sock){
    int str_len;
    int valid_test = 0x0;
    char message[BUF_SIZE];


    write(sock, quest, strlen(quest));
    str_len = read(sock, message, BUF_SIZE);

    if( str_len < 0 ){

        char error_message[100] = { 0x0 };
        sprintf(error_message, "No Response for %d Seconds.\nQuitting the Server Program", TIME_LIMIT);
        error_handling(error_message);
    }


    if(strncmp(message, ans, str_len) == 0)   // if the recieved message was "ans"
        valid_test = 1; 

    return valid_test; 
}

int main(int argc, char *argv[]){
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];

    struct sockaddr_in host_adr, client_adr;

    socklen_t client_adr_size;
    int str_len;


    // needs to initialized to 0
    int valid[NUM_PROBLEMS];

    char* instruction = "\n클라이언트 프로그램을 성공적으로 만드셨군요! 축하합니다.\n이제 다음의 다섯 문제를 푼다면 다음 문제의 암호를 주도록하죠.\n각 문제를 푸는데 30초가 지나면 자동으로 서버가 종료됩니다! 서두르세요!\n";

    char* q_array[NUM_PROBLEMS];
    char* ans_array[NUM_PROBLEMS];

    int is_correct[NUM_PROBLEMS];

    int cur_problem_num;

    q_array[0] = "\n1. 네트워크 방식 중 하나로 csma/cd를 사용하는 방식은?\n 답 : ________\n";
    q_array[1] = "\n2. OSI 7 layer의 앞글자를 입력하시오.\n 답: _______\n";
    q_array[2] = "\n3. hub는 한 포트로 들어오는 데이터를 나머지 모든 포트로 뿌려주는 특성 때문에 multiport ________ 라고 불린다.\n";
    q_array[3] = "\n4. 다음은 어떠한 ip class인가요?\n ip address : 193.1.7.18\n   _  class\n";
    q_array[4] = "\n5. ____ 번호는 컴퓨터에게 부여하는 값이 아닌 프로그램 상에서 생성되는 소켓을 구분하기 위해 소켓에 부여되는 번호이다.\n";

    ans_array[0] = "ethernet";
    ans_array[1] = "apstndp";
    ans_array[2] = "repeater";
    ans_array[3] = "c";
    ans_array[4] = "port";

    struct timeval tv;

    tv.tv_sec = TIME_LIMIT;
    tv.tv_usec = 0;

    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handling("socket() error");

    memset(&host_adr, 0, sizeof(host_adr));         // Initialize host_adr to 0
    host_adr.sin_family = AF_INET;                  // IPv4
    host_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    host_adr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &host_adr, sizeof(host_adr)) == -1)   // binding
        error_handling("bind() error");

    // Connection Waiting Queue = 5
    if(listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    // connect to the client. Trying to recieve.
    client_adr_size = sizeof(client_adr);
    
    clnt_sock = accept(serv_sock, (struct sockaddr*)&client_adr, &client_adr_size);
    if(clnt_sock == -1)
        error_handling("accept() error");
    else
        printf("Connected to Client");
    // repeat until all answers are correct
    while(1){

        // Signal to identify the client
        // str_len = read(clnt_sock, message, BUF_SIZE);

        // Send instruction
        write( clnt_sock, instruction, BUF_SIZE);

        setsockopt( clnt_sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv) );
        cur_problem_num = 0;

        // repeat until all questions are correct or there hasn't reponse for TIME_LIMIT 
        while( 1 ){
            if( cur_problem_num == NUM_PROBLEMS ){
                write( clnt_sock, END_MESSAGE, BUF_SIZE);
                printf("\n\nPASSWORD : %s\n\n", PASSWORD);
                break;
            }

            // + 1 if correct, else, repeat the question
            cur_problem_num += question(q_array[cur_problem_num], ans_array[cur_problem_num], clnt_sock);

        }

        if(cur_problem_num == NUM_PROBLEMS) break;

        close(serv_sock);
    }
    return 0;
}
