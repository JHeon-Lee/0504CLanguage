#include <stdio.h>

// 힙 영역 -> 동적할당

char* readName()
{
	char name[30];
	printf("이름을 입력하시오 : ");
	gets(name);
	return name;
}

void dynamic_allocation();

char* scanName();

int main()
{
	char* name = scanName();

	printf("name : %s\n", name);

	free(name);
	name = NULL;

	//dynamic_allocation();

	//{
	//	char* name1 = "\0";
	//	char* name2 = "\0";
	//	name1 = readName();
	//	printf("name1 : %s\n", name1); // 쓰레기값 출력 -> readName() 안에 name[30]이 지역변수이기 때문
	//	name2 = readName();
	//	printf("name2 : %s\n", name2);
	//}

	return 0;
}

void dynamic_allocation()
{
	// malloc
	{
		int* ptr = NULL;

		ptr = (int*)malloc(sizeof(int) * 5);
		// 동적할당 정의 기본형. malloc은 기본형이 void 이므로 앞에 자신이 원하는 자료형을 적어줘야하고, 원하는 크기로 넣을 수 있음

		if (ptr == NULL)
		{
			printf("메모리 할당 실패!\n");
			exit(1); // 1 --> EXIT_FAILURE - stdlib.h에 있음
			// exit(EXIT_SUCCESS); --> 0
		}

		printf("Before free 0x%p\n", ptr);

		free(ptr);
		// 반드시 해제시켜야 한다. -> 안하면 메모리 누수 발생 (면접)

		printf("After free 0x%p\n", ptr);
		// 해제해준 뒤에도 주소공간이 남음 --> 주소는 남아있음 (허상 포인터, dangling pointer)
		// - 메모리가 해제된 주소를 가리키는 포인터 (면접 기출)
		
		ptr = NULL; // 까지 해줘야 완벽

		printf("After free 0x%p\n", ptr);

#define Red 1 // 매크로 상수
#define FREE(ptr) if(ptr != NULL) {free(ptr); ptr = NULL;} // 매크로 함수로 한번에 해줄수 있음

		FREE(ptr);
	}

	//calloc
	{
		int size = 0;

		printf("동적 할당할 int형 변수의 메모리 공간 입력 => ");
		scanf_s("%d", &size);

		int* ma, * ca;
		ma = (int*)malloc(sizeof(int) * size);
		ca = (int*)calloc(size, sizeof(int)); // calloc 정의부
		// malloc과 달리 바로 0으로 초기화됨

		printf("\n초기화 전\n\n");

		for (int i = 0; i < size; i++)
		{
			printf("ma[%d] : %d\n", i, ma[i]); // 쓰레기값
			printf("ca[%d] : %d\n", i, ca[i]); // 0
		}

		for (int i = 0; i < size; i++)
		{
			ma[i] = 0;
		}

		printf("\n초기화 후\n\n");

		for (int i = 0; i < size; i++)
		{
			printf("ma[%d] : %d\n", i, ma[i]); // 0
			printf("ca[%d] : %d\n", i, ca[i]); // 0
		}

		free(ca);
		ca = NULL;

		free(ma);
		ma = NULL;
	}

	//realloc - 할당된 공간 늘리기
	{
		int size = 0;

		printf("동적 할당할 double형 변수의 메모리 공간 입력 => ");
		scanf_s("%d", &size);

		double* ptr = (double*)calloc(size, sizeof(double));

		printf("\nptr의 할당받은 주소 : %p\n", ptr);

		for (int i = 0; i < size; i++)
		{
			printf("ca[%d] : %lf\n", i, ptr[i]);
		}

		printf("\n재할당할 double형 변수의 메모리 공간 입력 => ");
		scanf_s("%d", &size);

		ptr = (double*)realloc((double*)ptr, size);

		printf("\nptr의 재할당받은 주소 : %p\n", ptr); // 주소 바뀜

		for (int i = 0; i < size; i++)
		{
			printf("ca[%d] : %lf\n", i, ptr[i]); // 재할당 시 초기화되지않음
		}
		pritnf("\n");

		// 메모리 잡히는 방식 --> 외부 단편화(면접)

		free(ptr);
		ptr = NULL;
	}

	{
		int n = 5;
		double* ptr = (double*)malloc(n * sizeof(double));

		if (ptr != NULL)
		{
			for (int i = 0; i < n; i++)
			{
				printf("ptr[%d] : %lf\n", i, ptr[i]); // 배열처럼 사용 가능
			}

			printf("\n");

			for (int i = 0; i < n; i++)
				*(ptr + i) = (double)i;

			free(ptr);
			ptr = NULL;
		}
	}
}

char* scanName()
{
	char buffer[100] = { 0 };

	printf("이름을 입력해 주세요 : ");
	scanf_s("%s", buffer, sizeof(buffer));
	
	int size = strlen(buffer) + sizeof((char)('\0'));

	if(size == sizeof((char)('\0')))
		return NULL;

	char* name = (char*)calloc(size, sizeof(char));

	if (name != NULL)
		strcpy_s(name, size, buffer);

	return name;
}


/*
	homework
	섯다
	플레이어 수
	이름 받고
	2 패 보이게 하고 돈(10000원 시작, 지면 500원씩 까이고 승자 독식), 족보 보이게
	0 끝 1 계속
*/