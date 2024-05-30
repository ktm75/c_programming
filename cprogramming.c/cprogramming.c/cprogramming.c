//2-2 마동석 체력추가까지 했습니다.
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
int madongseok_stamina, madongseok_aggro = 1, citizen_aggro = 1;
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
int main(void) {
	//인트로 아스키아트
	printf(" *********  ********  ****      ****  *********  *********** **********\n");
	printf("      ***  ***    *** ******  ******  ***    ***     ***     ***\n");
	printf("     ***   ***    *** ***   **   ***  **********     ***     **********\n");
	printf("    ***    ***    *** ***        ***  ***    ***     ***     ***\n");
	printf("   ***     ***    *** ***        ***  ***    ***     ***     ***\n");
	printf(" *********  ********  ***        ***  *********  *********** **********\n");
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
	while (1) {
		//시민 이동
		randnum = rand() % 100;
		if (randnum < 100 - per_prob)
		{
			citizen_position = train_len - (train_len - citizen_position) - 1;
		}
		else { citizen_position = train_len - (train_len - citizen_position); }



		//좀비 이동
		turn_count++;
		if (turn_count % 2 != 0)
		{
			if (randnum < per_prob)
			{
				zombie_position = train_len - (train_len - zombie_position) - 1;
			}
		}
		else { zombie_position = train_len - (train_len - zombie_position); }

		// 게임 종료(실패), 아웃트로
		if (zombie_position == citizen_position + 1)
		{
			printTrain();
			printf("\n");
			printf("GAME OVER!\n");
			printf("Citizen(s) has(have) been attacked by a zombie\n");
			exit(0);
		}
		// 게임종료(성공), 아웃트로 
		if (citizen_position == 1) {
			printTrain();
			printf("\n");
			printf("Game Succes!\n");
			printf("Citizen(s) escape(s) from the zombie");
			exit(0);
		}



		//열차 상태 출력
		printTrain();
		//시민, 좀비 상태 출력
		if (randnum < 100 - per_prob) {
			printf("citizen: %d -> %d\n", citizen_position + 1, citizen_position);
		}
		else { printf("citizen : stay %d\n", citizen_position); }

		if (turn_count % 2 != 0) {
			if (randnum < per_prob) {
				printf("zombie: %d -> %d \n", zombie_position + 1, zombie_position);
			}
			else { printf("zombie: stay %d\n", zombie_position); }
		}
		else if (turn_count % 2 != 1) {
			printf("zombie: stay %d (cannot move)\n", zombie_position);
		}
		printf("\n");
	}
	return 0;
}
