#include <stdio.h>

// �� ���� -> �����Ҵ�

char* readName()
{
	char name[30];
	printf("�̸��� �Է��Ͻÿ� : ");
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
	//	printf("name1 : %s\n", name1); // �����Ⱚ ��� -> readName() �ȿ� name[30]�� ���������̱� ����
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
		// �����Ҵ� ���� �⺻��. malloc�� �⺻���� void �̹Ƿ� �տ� �ڽ��� ���ϴ� �ڷ����� ��������ϰ�, ���ϴ� ũ��� ���� �� ����

		if (ptr == NULL)
		{
			printf("�޸� �Ҵ� ����!\n");
			exit(1); // 1 --> EXIT_FAILURE - stdlib.h�� ����
			// exit(EXIT_SUCCESS); --> 0
		}

		printf("Before free 0x%p\n", ptr);

		free(ptr);
		// �ݵ�� �������Ѿ� �Ѵ�. -> ���ϸ� �޸� ���� �߻� (����)

		printf("After free 0x%p\n", ptr);
		// �������� �ڿ��� �ּҰ����� ���� --> �ּҴ� �������� (��� ������, dangling pointer)
		// - �޸𸮰� ������ �ּҸ� ����Ű�� ������ (���� ����)
		
		ptr = NULL; // ���� ����� �Ϻ�

		printf("After free 0x%p\n", ptr);

#define Red 1 // ��ũ�� ���
#define FREE(ptr) if(ptr != NULL) {free(ptr); ptr = NULL;} // ��ũ�� �Լ��� �ѹ��� ���ټ� ����

		FREE(ptr);
	}

	//calloc
	{
		int size = 0;

		printf("���� �Ҵ��� int�� ������ �޸� ���� �Է� => ");
		scanf_s("%d", &size);

		int* ma, * ca;
		ma = (int*)malloc(sizeof(int) * size);
		ca = (int*)calloc(size, sizeof(int)); // calloc ���Ǻ�
		// malloc�� �޸� �ٷ� 0���� �ʱ�ȭ��

		printf("\n�ʱ�ȭ ��\n\n");

		for (int i = 0; i < size; i++)
		{
			printf("ma[%d] : %d\n", i, ma[i]); // �����Ⱚ
			printf("ca[%d] : %d\n", i, ca[i]); // 0
		}

		for (int i = 0; i < size; i++)
		{
			ma[i] = 0;
		}

		printf("\n�ʱ�ȭ ��\n\n");

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

	//realloc - �Ҵ�� ���� �ø���
	{
		int size = 0;

		printf("���� �Ҵ��� double�� ������ �޸� ���� �Է� => ");
		scanf_s("%d", &size);

		double* ptr = (double*)calloc(size, sizeof(double));

		printf("\nptr�� �Ҵ���� �ּ� : %p\n", ptr);

		for (int i = 0; i < size; i++)
		{
			printf("ca[%d] : %lf\n", i, ptr[i]);
		}

		printf("\n���Ҵ��� double�� ������ �޸� ���� �Է� => ");
		scanf_s("%d", &size);

		ptr = (double*)realloc((double*)ptr, size);

		printf("\nptr�� ���Ҵ���� �ּ� : %p\n", ptr); // �ּ� �ٲ�

		for (int i = 0; i < size; i++)
		{
			printf("ca[%d] : %lf\n", i, ptr[i]); // ���Ҵ� �� �ʱ�ȭ��������
		}
		pritnf("\n");

		// �޸� ������ ��� --> �ܺ� ����ȭ(����)

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
				printf("ptr[%d] : %lf\n", i, ptr[i]); // �迭ó�� ��� ����
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

	printf("�̸��� �Է��� �ּ��� : ");
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
	����
	�÷��̾� ��
	�̸� �ް�
	2 �� ���̰� �ϰ� ��(10000�� ����, ���� 500���� ���̰� ���� ����), ���� ���̰�
	0 �� 1 ���
*/