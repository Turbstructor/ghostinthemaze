#include <cstdio>
#include <cstring>

#define NF "\e[39m"
#define SF "\e[31m"

#define SB "\e[40m"
#define NB "\e[49m"

char crossword[29][65] = {"################### ############","################### ############","################### ##### ######","################### ##### ######","############              ######","############ ###### ############","############ ###### ######### ##","############ ################ ##","############ ### ############ ##","#### ####### ### ############ ##","####         ### ##### ###### ##","#### ####### ### ##### ###### ##","#### ####### ### ##### ###### ##","#### #######               ## ##","#### ########### ##### ###### ##","#### ########### ##### ###### ##","          ###### ##### ###### ##","######### ###### ##### ###### ##","######### ###### ##### ###### ##","######### ############ ###### ##","######### ########              ","######### ############ ###### ##","######### ############ ###### ##","######### ############ ###### ##","######### ############ #########","######### ######################","###               ##############","######### ######################","######### ######################"};

char HorizontalCorrectAnswer[6][20]={"classification","optimizer","gradientdescent","regression","hyperparameter","backpropagation"};
char VerticalCorrectAnswer[8][20]={"outlier","cnn","clustering","roccurve","overfitting","oneshotlearning","activationfunction","neuralnetwork"};
int check[2][8]={{0,0,0,0,0,0,1,1},{0}};


void rule(){
    printf("============================================================\n");
    printf("규칙\n");
    printf("1. 모든 정답은 영어이며 소문자입니다.\n");
    printf("2. 띄어쓰기는 생략하세요.\n");
    printf("3. 정답을 입력할 때 가로의 정답인지 세로의 정답인지 잘 체크하세요.\n");
    printf("4. mono sapcefont로 해주세요.\n");
    printf("============================================================\n");
}

void problem(){
    printf("============================================================\n");
    printf("가로\n");
    printf("1. 스팸 문자인지 아닌지 카테고리 별로 구분하는 것. 기존의 카테고리들을 학습하며 이를 기반으로 데이터의 범주를 구분하여 경계를 나눈다. 14자\n");
    printf("2. 딥러닝에서 학습속도(오차의 최소화)를 빠르고 안정적이게 하는 여러 알고리즘. 예)momentum,SGD 9자\n");
    printf("3. 매개변수를 조정하면서 손실을 최소화하는 가중치와 편향을 구하는 기법. 15자\n");
    printf("4. 주어진 데이터가 어떤 함수로부터 생성됐는지 추측하는 것. 연속된 값을 예측하는 문제이며 주로 패턴, 트렌드 경향을 예측할 때 사용되는데, 공부시간에 따른 시험점수를 예로 들 수 있다. 10자\n");
    printf("5. 모델을 학습시킬 때 사용자에 의해 조작되는 매개변수. 예) learning rate 14자\n");
    printf("6. 기계학습에서 계산 결과와 예측값 사이의 오차를 구하여 가중치를 업데이트하는 과정 15자\n");
    printf("세로\n");
    printf("1. 다른 자료와는 극단적으로 다른 값. 모델의 학습에서 성능 저하의 주요 원인이 된다. 7자\n");
    printf("2. 주로 이미지나 영상을 처리할 때 사용되는 인공신경망으로 convolutional layer와 pooling layer가 활성화함수 앞뒤에 배치되어 있으며 마지막은 이미지를 구분하기 위해 fully connected layer로 구성되어 있다. 3자\n");
    printf("3. 비지도학습에서 사용되며 아무런 정보가 없는 상태에서 데이터를 분류하는 방법이다. 10자\n");
    printf("4. threshold값에 따라 바뀌는 TPR과 FPR의 관계를 곡선으로 나타낸 것. 곡선 아래면적이 1에 가까울수록 좋은 성능을 의미한다. 8자\n");
    printf("5. 생성된 모델이 지나치게 학습이 되어 학습데이터는 잘 예측하지만 새로운 데이터에 대해서는 올바르게 예측하지 못하게 되는 경우를 의미한다. 11자\n");
    printf("6. 학습예제 데이터가 적을 때 분류를 효과적으로 학습하는 것을 목표로 하는 학습방법. 15자\n");
    printf("7. 이전 데이터의 입력에 대해 가중합을 취하고 비선형의 형태로 출력값을 생성하여 다음 레이어로 전달하는 함수 예) ReLU, sigmoid 18자\n");
    printf("8. 사람의 두뇌를 본뜬 모델로 주로 입력층과 하나 이상의 은닉층(hidden layer), 출력층으로 이루어져있다. 13자\n");
    printf("============================================================\n");
}

void crossword_print(){
    for(int i=0; i<29; i++){
        for(int j=0; j<(int)strlen(crossword[i]); j++){
            if(crossword[i][j] == '#') printf("%c",crossword[i][j]);
            else printf( SF SB "%c" NF NB ,crossword[i][j]);
        }
        printf("\n");
    }
}

void change_crossword(char answer[], int VP,int HP, int HorV){
    if(HorV == 0){
        for(int i = 0; i<(int)strlen(answer); i++){
            crossword[VP][HP + i] = answer[i];
        }
    }
    if(HorV == 1){
        for(int i = 0; i<(int)strlen(answer); i++){
            crossword[VP + i][HP] = answer[i];
        }
    }
}
void check_answer(char answer[], int ProblemNumber,int HorV){
    if(HorV == 0){
        if(strcmp(answer,HorizontalCorrectAnswer[ProblemNumber-1])==0){
            check[HorV][ProblemNumber-1] = 1;
            printf("정답입니다!\n");
            if(ProblemNumber == 1) change_crossword(answer, 4, 12, HorV);
            else if(ProblemNumber == 2) change_crossword(answer, 10, 4, HorV);
            else if(ProblemNumber == 3) change_crossword(answer, 13, 12, HorV);
            else if(ProblemNumber == 4) change_crossword(answer, 16, 0, HorV);
            else if(ProblemNumber == 5) change_crossword(answer, 20, 18, HorV);
            else if(ProblemNumber == 6) change_crossword(answer, 26, 3, HorV);
            
        }
        else printf("틀리셨습니다.\n");
        
    }

    if(HorV == 1){
        if(strcmp(answer,VerticalCorrectAnswer[ProblemNumber-1])==0){
            check[HorV][ProblemNumber-1] = 1;
            printf("정답입니다!\n");
            if(ProblemNumber == 1) change_crossword(answer, 0, 19, HorV);
            else if(ProblemNumber == 2) change_crossword(answer, 2, 25, HorV);
            else if(ProblemNumber == 3) change_crossword(answer, 4, 12, HorV);
            else if(ProblemNumber == 4) change_crossword(answer, 9, 4, HorV);
            else if(ProblemNumber == 5) change_crossword(answer, 8, 16, HorV);
            else if(ProblemNumber == 6) change_crossword(answer, 10, 22, HorV);
            else if(ProblemNumber == 7) change_crossword(answer, 6, 29, HorV);
            else if(ProblemNumber == 8) change_crossword(answer, 16, 9, HorV);
        }
        else printf("틀리셨습니다.\n");
    }
}

int check_clear(){
    int clear = 1;
    
    for(int i=0; i<2; i++){
        for(int j=0; j<8; j++){
            if(check[i][j] == 0) {
                clear = 0;
                break;
            }
        }
    }
    return clear;
}
int input(){
    char buffer;
    int a;

    buffer = getc(stdin);
    fflush(stdin);
    if(buffer >= '1' && buffer <= '9'){
        a = (int)buffer - 48;
    }
    return a;
}
int main(){
    
    rule();
    crossword_print();
    problem();
    
    while(1){
        
        int choice;
        int problem_choice;
        char answer[20];
        
        printf("원하는 선택지의 숫자를 입력해 주세요.\n");
        printf("1.문제 출력 2.crossword지도 출력 3.가로정답입력 4.세로정답입력 5.종료\n");
    
        
        choice = input();
    
        if(choice == 5) break;

        switch(choice){
            case 1 :
                problem();
                break;
            case 2 :
                crossword_print();
                break;
            case 3 :
                printf("정답을 입력하고 싶은 가로 문제의 번호를 입력해주세요.\n");
                problem_choice = input();
                if(problem_choice == 1 || problem_choice == 2 || problem_choice == 3 || problem_choice == 4 || problem_choice == 5 || problem_choice == 6){
                    if(check[0][problem_choice-1] == 0){
                        printf("정답을 입력해주세요\n");
                        fgets(answer, sizeof(answer), stdin);
                        fflush(stdin);
                        answer[strlen(answer) - 1] = '\0';
                        check_answer(answer,problem_choice,0);
                    }
                    else printf("이미 정답을 맞추셨습니다.\n");
                }
                else printf("문제번호를 잘못입력하셨습니다.\n");
                break;
            case 4 :
                printf("정답을 입력하고 싶은 세로 문제의 번호를 입력해주세요.\n");
                problem_choice=input();
                if(problem_choice == 1 || problem_choice == 2 || problem_choice == 3 || problem_choice == 4 || problem_choice == 5 || problem_choice == 6 || problem_choice == 7 ||problem_choice == 8){
                    if(check[1][problem_choice-1] == 0){
                        printf("정답을 입력해주세요\n");
                        fgets(answer, sizeof(answer), stdin);
                        fflush(stdin);
                        answer[strlen(answer) - 1] = '\0';
                        check_answer(answer,problem_choice,1);
                    }
                    else printf("이미 정답을 맞추셨습니다.\n");
                }
                else printf("문제번호를 잘못 입력하셨습니다.\n");
                break;
            
            default : 
                printf("잘못입력하셨습니다.\n"); 
                break;
        }

        if( check_clear() == 1){
            crossword_print();
            printf("축하드립니다!! 모두 정답을 맞추셨습니다.\n");
            printf("password code : abc");
            break;
        }

    }
}