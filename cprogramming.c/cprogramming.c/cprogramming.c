#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <stdlib.h>

#define LEN_MIN 15
#define LEN_MAX 50
#define PROB_MIN 10
#define PROB_MAX 90



int main(void) {
	//인트로 아스키아트
	printf(" *********  ********  ****      ****  *********  *********** **********\n");
	printf("      ***  ***    *** ******  ******  ***    ***     ***     ***\n");
	printf("     ***   ***    *** ***   **   ***  **********     ***     **********\n");
	printf("    ***    ***    *** ***        ***  ***    ***     ***     ***\n");
	printf("   ***     ***    *** ***        ***  ***    ***     ***     ***\n");
	printf(" *********  ********  ***        ***  *********  *********** **********\n");

	Sleep(2000);
	//열차 초기 상태 출력
	int train_len, per_prob, citizen_position, zombie_position, madongsuk_position, randnum, turn_count = 0;
	printf("train length(15~50)>>");
	scanf_s("%d", &train_len);
	if (train_len < LEN_MIN || train_len > LEN_MAX)
	{
		exit(0);
	}
	printf("percentile probability 'p'(10~90)>>");
	scanf_s("%d", &per_prob);
	if (per_prob < PROB_MIN || per_prob > 90)
	{
		exit(0);
	}
	else
	{
		for (int i = 0; i <= train_len - 1; i++)
		{
			printf("#");
		}
	}
	printf("\n");
	citizen_position = train_len - 6;
	zombie_position = train_len - 3;
	madongsuk_position = train_len - 2;
	for (int i = 0; i <= (train_len - 1); i++)
	{
		if (i == citizen_position)
		{
			printf("C");
		}
		else if (i == zombie_position)
		{
			printf("Z");
		}
		else if (i == madongsuk_position)
		{
			printf("M");
		}
		else if (i == 0)
		{
			printf("#");
		}
		else if (i == train_len - 1)
		{
			printf("#");
		}
		else { printf(" "); }
	}
	printf("\n");
	for (int i = 0; i <= train_len - 1; i++)
	{
		printf("#");
	}
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");

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
			for (int i = 0; i <= train_len - 1; i++)
			{
				printf("#");
			}
			printf("\n");
			for (int i = 0; i <= (train_len - 1); i++)
			{
				if (i == citizen_position)
				{
					printf("C");
				}
				else if (i == zombie_position)
				{
					printf("Z");
				}
				else if (i == madongsuk_position)
				{
					printf("M");
				}
				else if (i == 0)
				{
					printf("#");
				}
				else if (i == train_len - 1)
				{
					printf("#");
				}
				else { printf(" "); }
			}
			printf("\n");
			for (int i = 0; i <= train_len - 1; i++)
			{
				printf("#");
			}
			printf("\n");
			printf("GAME OVER!\n");
			printf("Citizen(s) has(have) been attacked by a zombie\n");
			exit(0);
		}
		// 게임종료(성공), 아웃트로 
		if (citizen_position == 1)
		{
			for (int i = 0; i <= train_len - 1; i++)
			{
				printf("#");
			}
			printf("\n");
			for (int i = 0; i <= (train_len - 1); i++)
			{
				if (i == citizen_position)
				{
					printf("C");
				}
				else if (i == zombie_position)
				{
					printf("Z");
				}
				else if (i == madongsuk_position)
				{
					printf("M");
				}
				else if (i == 0)
				{
					printf("#");
				}
				else if (i == train_len - 1)
				{
					printf("#");
				}
				else { printf(" "); }
			}
			printf("\n");
			for (int i = 0; i <= train_len - 1; i++)
			{
				printf("#");
			}
			printf("\n");
			printf("Game Succes!\n");
			printf("Citizen(s) escape(s) from the zombie");
			exit(0);
		}



		//열차 상태 출력
		for (int i = 0; i <= train_len - 1; i++)
		{
			printf("#");
		}
		printf("\n");
		for (int i = 0; i <= (train_len - 1); i++)
		{
			if (i == citizen_position)
			{
				printf("C");
			}
			else if (i == zombie_position)
			{
				printf("Z");
			}
			else if (i == madongsuk_position)
			{
				printf("M");
			}
			else if (i == 0)
			{
				printf("#");
			}
			else if (i == train_len - 1)
			{
				printf("#");
			}
			else { printf(" "); }
		}
		printf("\n");
		for (int i = 0; i <= train_len - 1; i++)
		{
			printf("#");
		}
		printf("\n");
		//시민, 좀비 상태 출력
		if (randnum < 100 - per_prob)
		{
			printf("citizen: %d -> %d\n", citizen_position + 1, citizen_position);
		}
		else { printf("citizen : stay %d\n", citizen_position); }

		if (turn_count % 2 != 0)
		{
			if (randnum < per_prob)
			{
				printf("zombie: %d -> %d \n", zombie_position + 1, zombie_position);
			}
			else { printf("zombie: stay %d\n", zombie_position); }
		}
		if (turn_count % 2 != 1)
		{
			printf("zombie: stay %d (cannot move)\n", zombie_position);
		}



		Sleep(4000);
		printf("\n");
	}
	return 0;
}