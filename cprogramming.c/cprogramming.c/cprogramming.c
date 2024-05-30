//3-2 이동까지 했습니다. 
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 파라미터
#define LEN_MIN 15 // 기차 길이
#define LEN_MAX 50
#define STM_MIN 0 // 마동석 체력
#define STM_MAX 5
#define PROB_MIN 10 // 확률
#define PROB_MAX 90
#define AGGRO_MIN 0 // 어그로 범위
#define AGGRO_MAX 5
// 마동석 이동 방향
#define MOVE_LEFT 1
#define MOVE_STAY 0
// 좀비의 공격 대상
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2
// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2


//열차 초기 상태 출력
int train_len, per_prob, citizen_position, zombie_position, madongseok_position, randnum, turn_count = 0;
int madongseok_stamina, madongseok_aggro = 1, citizen_aggro = 1, madongseok_move;
int old_madongseok_position, old_zombie_position, old_citizen_position, old_citizen_aggro, old_madongseok_aggro;
char train[LEN_MAX];









//열차 초기 상태 출력
void printcover() {
    for (int i = 0; i < train_len; i++) {
        train[i] = '#';
        printf("%c", train[i]);
    }
    printf("\n");
}

void printTrain() {
    printcover();
    for (int i = 0; i < train_len; i++) {
        train[i] = ' ';
        train[citizen_position] = 'C';
        train[zombie_position] = 'Z';
        train[madongseok_position] = 'M';
        train[0] = train[train_len - 1] = '#';
        printf("%c", train[i]);
    }
    printf("\n");
    printcover();
    printf("\n");
}
//게임 시작 
void StartGame() {
    //인트로 아스키아트
    printf(" *********  ********  ****      ****  *********  *********** **********\n");
    printf("      ***  ***    *** ******  ******  ***    ***     ***     ***\n");
    printf("     ***   ***    *** ***   **   ***  **********     ***     **********\n");
    printf("    ***    ***    *** ***        ***  ***    ***     ***     ***\n");
    printf("   ***     ***    *** ***        ***  ***    ***     ***     ***\n");
    printf(" *********  ********  ***        ***  *********  *********** **********\n");
    printf("\n");
    printf("\n");
    printf("train length(15~50)>> ");
    scanf_s("%d", &train_len);
    while (train_len < LEN_MIN || train_len > LEN_MAX) {
        printf("train length(15~50)>> ");
        scanf_s("%d", &train_len);
    }
    printf("madongseok stamina(0~5)>> ");
    scanf_s("%d", &madongseok_stamina);
    while (madongseok_stamina <= STM_MIN || madongseok_stamina > STM_MAX) {
        printf("madongseok stamina(0~5)>> ");
        scanf_s("%d", &madongseok_stamina);
    }
    printf("percentile probability 'p'(10~90)>> ");
    scanf_s("%d", &per_prob);
    while (per_prob < PROB_MIN || per_prob > PROB_MAX) {
        printf("percentile probability 'p'(10~90)>> ");
        scanf_s("%d", &per_prob);
    }
    printf("\n");
    citizen_position = train_len - 6;
    zombie_position = train_len - 3;
    madongseok_position = train_len - 2;
    printTrain();
}
    //이동 페이즈
    void update() {
        old_zombie_position = zombie_position, old_citizen_position = citizen_position, old_madongseok_position = madongseok_position;
        old_citizen_aggro = citizen_aggro, old_madongseok_aggro = madongseok_aggro;
        randnum = rand() % 100;
        //1-2 시민 이동
        if (randnum < 100 - per_prob) {
            citizen_position -= 1;
            if (citizen_aggro < AGGRO_MAX) { citizen_aggro += 1; }
        }

        else {
            if (citizen_aggro > AGGRO_MIN) { citizen_aggro -= 1; }
        }

        //1-3 좀비 이동
        turn_count++;
        if (turn_count % 2 != 0) {
            if (citizen_aggro >= madongseok_aggro) {
                if (zombie_position == citizen_position + 1) {
                    zombie_position = zombie_position;
                }
                else { zombie_position -= 1; }
            }
            else if (citizen_aggro < madongseok_aggro) {
                if (zombie_position == madongseok_position - 1) {
                    zombie_position = zombie_position;
                }
                else { zombie_position += 1; }
            }
        }
        //1-4 열차 상태 출력 
        printTrain();
        //1-4-1 시민 이동 출력
        if (randnum < 100 - per_prob) {
            if (old_citizen_aggro < AGGRO_MAX) {
                printf("citizen: %d -> %d (aggro: %d -> %d)\n", old_citizen_position, citizen_position, old_citizen_aggro, citizen_aggro);
            }
            else { printf("citizen: %d -> %d (aggro: stay %d)\n", old_citizen_position, citizen_position, citizen_aggro); }
        }
        else {
            if (old_citizen_aggro > AGGRO_MIN) {
                printf("citizen: stay %d (aggro: %d -> %d)\n", citizen_position, old_citizen_aggro, citizen_aggro);
            }
            else { printf("citizen: stay %d (aggro: stay %d)\n", citizen_position, old_citizen_aggro); }
        }
        //1-4-2 좀비 이동 출력 

        if (turn_count % 2 != 0) {
            if (citizen_aggro >= madongseok_aggro) {
                if (zombie_position == citizen_position + 1) {
                    printf("zombie: stay %d(cannot move because of citizen)\n", zombie_position);
                    printf("\n");
                }
                else {

                    printf("zombie: %d -> %d\n", old_zombie_position, zombie_position);
                    printf("\n");
                }
            }

            else if (citizen_aggro < madongseok_aggro) {
                if (old_zombie_position == madongseok_position - 1) {
                    printf("zombie: stay %d(cannot move because of madongseok)\n", zombie_position);
                    printf("\n");
                }
                else {

                    printf("zombie: %d -> %d\n", old_zombie_position, zombie_position);
                    printf("\n");
                }
            }
        }
        else {
            printf("zombie: stay %d (cannot move at turn(%%2 == 0))\n", zombie_position);
            printf("\n");
        }


        //1-5-1 마동석 이동(입력) 
        printf("madongseok move(0:stay, 1:left)>> ");
        scanf_s("%d", &madongseok_move);
        while (madongseok_move < MOVE_STAY || madongseok_move > MOVE_LEFT) {
            printf("madongseok move(0:stay, 1:left)>> ");
            scanf_s("%d", &madongseok_move);
        }
        if (madongseok_position - 1 == zombie_position && madongseok_move == MOVE_LEFT) {
            while (madongseok_move == MOVE_LEFT) {
                printf("madongseok cannot move because of zombie\n");
                printf("madongseok move(0:stay, 1:left)>> ");
                scanf_s("%d", &madongseok_move);
            }
        }

        //1-5-2 마동석 이동 출력   
        if (madongseok_move == MOVE_STAY) {
            printTrain();
            if (madongseok_aggro > AGGRO_MIN) {
                madongseok_aggro -= 1;
                printf("madongseok: stay %d (aggro: %d -> %d, stamina: stay %d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, madongseok_stamina);
            }
            else { printf("madongseok: stay %d (aggro: stay %d, stamina: stay %d)\n", madongseok_position, madongseok_aggro, madongseok_stamina); }
        }
        else if (madongseok_move == MOVE_LEFT) {
            madongseok_position -= 1;
            printTrain();
            if (madongseok_aggro < AGGRO_MAX) {
                madongseok_aggro += 1;
                printf("madongseok: %d -> %d (aggro: %d -> %d, stamina: stay %d)\n", old_madongseok_position, madongseok_position, old_madongseok_aggro, madongseok_aggro, madongseok_stamina);
            }
            else {
                printf("madongseok: %d -> %d (aggro: stay %d, stamina: stay %d)\n", old_madongseok_position, madongseok_position, madongseok_aggro, madongseok_stamina);
            }

        }
    }
    int main(void) {
        while (1) {
            StartGame();
            update();
        }
        return 0;
    }
