#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


void pointer_and_function(); // -> 코드영역

int main()
{
	pointer_and_function();

	return 0;
}

int Add(int x, int y) { return x + y; }
int Sub(int x, int y) { return x - y; }

typedef struct _player
{
	char name[256];
	char location[256];
	int hp;
	void (*ifDead[5])(struct _player*);
}player;

void printDead(player* p)
{
	printf("%s 사망\n", p->name);
}

void revive(player* p)
{
	printf("%s 부활\n", p->name);
	p->hp += 200;
}

void moveToTown(player* p)
{
	printf("마을로 이동합니다\n");
	strcpy(p->location, "Town");
}

void pointer_and_function()
{
	{
		char op = '\0';
		printf("연산자 입력 : ");
		scanf_s(" %c", &op, (int)sizeof(op));

		int x = 0;
		printf("피연산자 입력 : ");
		scanf_s("%d", &x);

		int y = 0;
		printf("피연산자 입력 : ");
		scanf_s("%d", &y);

		int (*compute)(int, int) = NULL; // 함수 포인터 정의부

		switch (op)
		{
		case '+': compute = Add; break;
		case '-': compute = Sub; break;
		}

		if (compute != NULL)
			printf("결과 : %d\n", compute(x, y));

		printf("\n");
	}

	{
		player p = {
			"Wizard",
			"Dungeon",
			100,
			{NULL, NULL, NULL}
		};

		p.ifDead[0] = printDead;
		p.ifDead[1] = revive;
		p.ifDead[2] = moveToTown;

		printf("%s의 위치 : %s HP : %d\n", p.name, p.location, p.hp);

		int damage = 0;

		while (1)
		{
			printf("받을 피해 입력(현재 체력 %d) : ", p.hp);
			scanf_s("%d", &damage);
			p.hp -= damage;

			if (p.hp <= 0)
			{
				for (int i = 0; i < 3; i++)
				{
					if (p.ifDead[i] != NULL)
					{
						p.ifDead[i](&p);
					}
				}
				break;
			}
		}

		printf("%s의 위치 : %s HP : %d\n", p.name, p.location, p.hp);
	}
}
