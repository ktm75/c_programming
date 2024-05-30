// 보너스 첫 번째 스테이지까지 했습니다.
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

int train_len, per_prob, citizen_position, zombie_position, madongseok_position, randnum; turn_count = 0;
int citizen_aggro = 1, madongseok_aggro = 1, madongseok_stamina, madongseok_move, madongseok_action, zombie_target;
int old_zombie_position, old_citizen_position, old_madongseok_position;
int old_citizen_aggro, old_madongseok_aggro, old_madongseok_stamina;
int old_villain_position, old_villain_aggro, villain_position, villain_aggro;
char train[LEN_MAX];


//1-1 열차상태출력
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
        train[villain_position] = 'V';
        train[0] = train[train_len - 1] = '#';
        printf("%c", train[i]);
    }
    printf("\n");
    printcover();
    printf("\n");
}

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
    citizen_position = train_len - 6;
    zombie_position = train_len - 3;
    madongseok_position = train_len - 2;
    villain_position = train_len - 5;
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

    // 빌런 이동 
    old_villain_position = villain_position, old_villain_aggro = villain_aggro;
    if (randnum < 100 - per_prob) {
        villain_position -= 1;
        if (villain_aggro < AGGRO_MAX) {
            villain_aggro += 1;
        }
    }
    else {
        if (villain_aggro > AGGRO_MIN) {
            villain_aggro -= 1;
        }
    }
    //1-3 좀비 이동
    turn_count++;
    if (turn_count % 2 != 0) {
        if (madongseok_action == ACTION_PULL && randnum < 100 - per_prob) {
            zombie_position = zombie_position;
        }
        else if (citizen_aggro >= madongseok_aggro && citizen_aggro >= villain_aggro) {
            if (zombie_position == citizen_position + 1) {
                zombie_position = zombie_position;
            }
            else {
                zombie_position -= 1;
            }
        }
        else if (villain_aggro >= citizen_aggro && villain_aggro >= madongseok_aggro) {
            if (zombie_position == villain_position + 1)
            {
                zombie_position = zombie_position;
            }
            else { zombie_position -= 1; }

        }
        else if (madongseok_aggro >= citizen_aggro && madongseok_aggro >= villain_aggro) {
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
    //빌런 이동 출력
    if (randnum < 100 - per_prob) {
        if (old_villain_aggro < AGGRO_MAX) {
            printf("villain: %d -> %d (aggro: %d -> %d)\n", old_villain_position, villain_position, old_villain_aggro, villain_aggro);
        }
        else { printf("villain: %d -> %d (aggro: stay %d)\n", old_villain_position, villain_position, villain_aggro); }
    }
    else {
        if (old_villain_aggro > AGGRO_MIN) {
            printf("villain: stay %d (aggro: %d -> %d)\n", villain_position, old_villain_aggro, villain_aggro);
        }
        else { printf("villain: stay %d (aggro: stay %d)\n", villain_position, old_villain_aggro); }

    }
    //1-4-2 좀비 이동 출력 

    if (turn_count % 2 != 0) {
        if (madongseok_action == ACTION_PULL && randnum < 100 - per_prob) {
            printf("zombie: stay %d (cannot move because of madongseok's Pull)\n", zombie_position);
            printf("\n");
        }
        if (citizen_aggro >= madongseok_aggro && citizen_aggro >= villain_aggro) {
            if (zombie_position == citizen_position + 1) {
                printf("zombie: stay %d(cannot move because of citizen)\n", zombie_position);
                printf("\n");
            }
            else {
                printf("zombie: %d -> %d\n", old_zombie_position, zombie_position);
                printf("\n");
            }
        }
        else if (villain_aggro >= citizen_aggro && villain_aggro >= madongseok_aggro) {
            if (zombie_position == villain_position + 1) {
                printf("zombie: stay %d (cannot move because of Villain)\n", zombie_position);
                printf("\n");
            }
            else {
                printf("zombie: %d -> %d\n", old_zombie_position, zombie_position);
                printf("\n");
            }
        }

        else if (madongseok_aggro >= citizen_aggro && madongseok_aggro >= villain_aggro) {
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






//행동 페이즈 
void behavior() {
    old_madongseok_aggro = madongseok_aggro, old_madongseok_stamina = madongseok_stamina;
    //2-1 시민 행동 출력
    if (citizen_position == 1) {

        printf("You Win!\n"); //아웃트로
        exit(0);
    }
    else if (randnum < 100 - per_prob) {
        printf("citizen moves\n");
    }
    else {
        printf("citizen does nothing\n");
    }
    //빌런 행동 출력
    if (villain_position - 1 == citizen_position) {
        if (randnum <= 30) {
            int temp = citizen_position;
            citizen_position = villain_position;
            villain_position = temp;
            printf("villain change position with citizen\n");
        }
        else { printf("villan fail to change position\n"); }
    }
    //2-2 좀비 행동 출력
    if (zombie_position - 1 != citizen_position && zombie_position + 1 != madongseok_position) {
        zombie_target = ATK_NONE;
    }
    else if (zombie_position - 1 == citizen_position && zombie_position + 1 == madongseok_position) {
        if (citizen_aggro >= madongseok_aggro) {
            zombie_target = ATK_CITIZEN;
        }
        else if (citizen_aggro < madongseok_aggro) {
            zombie_target = ATK_DONGSEOK;
        }
    }
    else if (zombie_position - 1 == citizen_position && zombie_position + 1 != madongseok_position) {
        zombie_target = ATK_CITIZEN;
    }
    else if (zombie_position + 1 == madongseok_position && zombie_position - 1 != citizen_position) {
        zombie_target = ATK_DONGSEOK;
    }

    switch (zombie_target) {
    case ATK_NONE: printf("zombie attacked nobody\n");
        break;

    case ATK_CITIZEN: if (zombie_position - 1 == citizen_position && zombie_position + 1 == madongseok_position) {
        printf("zombie attacked citizen(%d vs %d)\n", citizen_aggro, madongseok_aggro);
    }
                    else if (zombie_position - 1 == citizen_position && zombie_position + 1 != madongseok_position) {
        printf("zombie attacked citizen\n");
    }
                    printf("GAME OVER! citizen dead..\n");
                    exit(0);
    case ATK_DONGSEOK:
        if (zombie_position - 1 == citizen_position && zombie_position + 1 == madongseok_position) {
            if (madongseok_stamina > STM_MIN) {
                madongseok_stamina -= 1;
                printf("zombie attacked madongseok (aggro: %d vs %d, madongseok_stamina: %d -> %d)\n", citizen_aggro, madongseok_aggro, old_madongseok_stamina, madongseok_stamina);
            }
            else { printf("zombie attacked madongseok(aggro: stay %d, madongseok_stamina: stay %d)\n", madongseok_aggro, madongseok_stamina); }
            if (madongseok_stamina == STM_MIN) {
                printf("GAME OVER! madongseok dead..\n");
                exit(0);
            }
        }
        else if (zombie_position + 1 == madongseok_position && zombie_position - 1 != citizen_position) {
            if (madongseok_stamina > STM_MIN) {
                madongseok_stamina -= 1;
                printf("zombie attacked madongseok (aggro: stay %d, madongseok_stamina: %d -> %d)\n", madongseok_aggro, old_madongseok_stamina, madongseok_stamina);
            }
            else { printf("zombie attacked madongseok(aggro: stay %d, madongseok_stamina: stay %d)\n", madongseok_aggro, madongseok_stamina); }
            if (madongseok_stamina == STM_MIN) {
                printf("GAME OVER! madongseok dead..\n");
                exit(0);
            }
        }

        //2-3 마동석 행동 입력 및 출력
        //좀비가 마동석 바로 옆이 아닐 때 
        old_madongseok_aggro = madongseok_aggro, old_madongseok_stamina = madongseok_stamina;
        if (zombie_position + 1 != madongseok_position) {
            printf("madongseok action(0.rest, 1.provoke) >> ");
            scanf_s("%d", &madongseok_action);
            while (madongseok_action < ACTION_REST || madongseok_action > ACTION_PROVOKE) {
                printf("madongseok action(0.rest, 1.provoke) >> ");
                scanf_s("%d", &madongseok_action);
            }

            if (madongseok_action == ACTION_REST) {
                if (madongseok_stamina < STM_MAX && madongseok_aggro > AGGRO_MIN) {
                    madongseok_stamina += 1, madongseok_aggro -= 1;
                    printf("madongseok rests...\n");
                    printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, old_madongseok_stamina, madongseok_stamina);
                    printf("\n");
                }
                else if (madongseok_stamina < STM_MAX && madongseok_aggro <= AGGRO_MIN) {
                    madongseok_stamina += 1;
                    printf("madongseok rests...\n");
                    printf("madongseok: %d (aggro: stay %d, stamina: %d -> %d)\n", madongseok_position, madongseok_aggro, old_madongseok_stamina, madongseok_stamina);
                    printf("\n");
                }
                else if (madongseok_stamina >= STM_MAX && madongseok_aggro > AGGRO_MIN) {
                    madongseok_aggro -= 1;
                    printf("madongseok rests...\n");
                    printf("madongseok: %d (aggro: %d -> %d, stamina: stay %d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, madongseok_stamina);
                    printf("\n");
                }
                else if (madongseok_stamina >= STM_MAX && madongseok_aggro <= AGGRO_MIN) {
                    printf("madongseok rests...\n");
                    printf("madongseok: %d (aggro: stay %d, stamina: stay %d)\n", madongseok_position, madongseok_aggro, madongseok_stamina);
                    printf("\n");
                }
            }

            else if (madongseok_action == ACTION_PROVOKE) {
                printf("madongseok provoked zombie...\n");
                printf("madongseok: %d (aggro: %d -> %d, stamina: stay %d)\n", madongseok_position, madongseok_aggro, AGGRO_MAX, madongseok_stamina);
                madongseok_aggro = AGGRO_MAX;
                printf("\n");
            }
        }
        //마동석 바로 옆이 좀비일 때
        else if (zombie_position + 1 == madongseok_position) {
            printf("madongseok action(0.rest, 1.provoke, 2. pull)>> ");
            scanf_s("%d", &madongseok_action);
            while (madongseok_action < ACTION_REST || madongseok_action > ACTION_PULL) {
                printf("madongseok action(0.rest, 1.provoke, 2. pull)>> ");
                scanf_s("%d", &madongseok_action);
            }

            if (madongseok_action == ACTION_REST) {
                if (madongseok_stamina < STM_MAX && madongseok_aggro > AGGRO_MIN) {
                    madongseok_stamina += 1, madongseok_aggro -= 1;
                    printf("madongseok rests...\n");
                    printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, old_madongseok_stamina, madongseok_stamina);
                    printf("\n");
                }
                else if (madongseok_stamina < STM_MAX && madongseok_aggro <= AGGRO_MIN) {
                    madongseok_stamina += 1;
                    printf("madongseok rests...\n");
                    printf("madongseok: %d (aggro: stay %d, stamina: %d -> %d)\n", madongseok_position, madongseok_aggro, old_madongseok_stamina, madongseok_stamina);
                    printf("\n");
                }
                else if (madongseok_stamina >= STM_MAX && madongseok_aggro > AGGRO_MIN) {
                    madongseok_aggro -= 1;
                    printf("madongseok rests...\n");
                    printf("madongseok: %d (aggro: %d -> %d, stamina: stay %d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, madongseok_stamina);
                    printf("\n");
                }
                else if ((madongseok_stamina >= STM_MAX && madongseok_aggro <= AGGRO_MIN)) {
                    printf("madongseok rests...\n");
                    printf("madongseok: %d (aggro: stay %d, stamina: stay %d)\n", madongseok_position, madongseok_aggro, madongseok_stamina);
                    printf("\n");
                }
            }

            else if (madongseok_action == ACTION_PROVOKE) {
                printf("madongseok provoked zombie...\n");
                printf("madongseok: %d (aggro: %d -> %d, stamina: stay %d)\n", madongseok_position, madongseok_aggro, AGGRO_MAX, madongseok_stamina);
                madongseok_aggro = AGGRO_MAX;
                printf("\n");
                if (madongseok_stamina == STM_MIN) {
                    printf("GAME OVER! madongseok dead..\n");
                    exit(0);
                }
            }


            else if (madongseok_action == ACTION_PULL) {
                if (randnum < 100 - per_prob) {

                    if (madongseok_aggro == 4 && madongseok_stamina > STM_MIN) {
                        madongseok_aggro += 1, madongseok_stamina -= 1;
                        printf("madongseok pulled zombie... Next turn, it can't move\n");
                        printf("madongseok: %d(aggro : %d -> %d, stamina : %d -> % d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, old_madongseok_stamina, madongseok_stamina);
                        printf("\n");
                    }
                    else if (madongseok_aggro < 4 && madongseok_stamina > STM_MIN) {
                        madongseok_aggro += 2, madongseok_stamina -= 1;
                        printf("madongseok pulled zombie... Next turn, it can't move\n");
                        printf("madongseok: %d(aggro : %d -> %d, stamina : %d -> % d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, old_madongseok_stamina, madongseok_stamina);
                        printf("\n");
                    }
                    else if (madongseok_aggro == 4 && madongseok_stamina <= STM_MIN) {
                        madongseok_aggro += 1;
                        printf("madongseok pulled zombie... Next turn, it can't move\n");
                        printf("madongseok: %d(aggro : %d -> %d, stamina : stay %d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, madongseok_stamina);
                        printf("\n");
                    }
                    else if (madongseok_aggro < 4 && madongseok_stamina <= STM_MIN) {
                        madongseok_aggro += 2;
                        printf("madongseok pulled zombie... Next turn, it can't move\n");
                        printf("madongseok: %d(aggro : %d -> %d, stamina : stay %d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, madongseok_stamina);
                        printf("\n");
                    }

                }
                else {
                    if (madongseok_aggro == 4 && madongseok_stamina > STM_MIN) {
                        madongseok_aggro += 1, madongseok_stamina -= 1;
                        printf("madongseok failed to pull zombie\n");
                        printf("madongseok: %d(aggro : %d -> %d, stamina : %d -> % d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, old_madongseok_stamina, madongseok_stamina);
                        printf("\n");
                    }
                    else if (madongseok_aggro < 4 && madongseok_stamina > STM_MIN) {
                        madongseok_aggro += 2, madongseok_stamina -= 1;
                        printf("madongseok failed to pull zombie\n");
                        printf("madongseok: %d(aggro : %d -> %d, stamina : %d -> % d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, old_madongseok_stamina, madongseok_stamina);
                        printf("\n");
                    }
                    else if (madongseok_aggro == 4 && madongseok_stamina <= STM_MIN) {
                        madongseok_aggro += 1;
                        printf("madongseok failed to pull zombie\n");
                        printf("madongseok: %d(aggro : %d -> %d, stamina : stay %d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, madongseok_stamina);
                        printf("\n");
                    }
                    else if (madongseok_aggro < 4 && madongseok_stamina <= STM_MIN) {
                        madongseok_aggro += 2;
                        printf("madongseok failed to pull zombie\n");
                        printf("madongseok: %d(aggro : %d -> %d, stamina : stay %d)\n", madongseok_position, old_madongseok_aggro, madongseok_aggro, madongseok_stamina);
                        printf("\n");
                    }

                }
            }
        }
    }
}



int main(void) {
    StartGame();
    while (1) {
        update();
        behavior();
    }
    return 0;