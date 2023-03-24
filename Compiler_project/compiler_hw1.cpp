#include <stdio.h>
#include <stdlib.h>	// exit �Լ� ���̺귯��
#include <string.h>

char lookahead;	// �Էµ� ����
int size = 10;
int** look_p = (int**)malloc(sizeof(int*) * size);	// �Է� ������ �迭
int x, y, count = 0;	// ��ǥ ����


void nexttoken();
void seq();
void position();	// ��ġ ���

void main() {
	printf("�Է�:");
	nexttoken();
	seq();	// ��ǥ ���
	printf("\n");

	if (lookahead == '$')	// �������� $��
	{;
		
		free(look_p);	// �迭 �޸� ����
	}
	else
		printf("error\n");
}

void match(char token) {
	if (lookahead == token) {
		nexttoken();
	}
	else {
		printf("error\n");
		exit(1);	// ���μ��� ����
	}
}

void nexttoken() {
	char c;
	while (1) {
		c = getchar();	// ���� �Է�
		if (c == EOF) {	// ctrl + z�� ���
			lookahead = '$';
			return;
		}
		if (c == ' ' || c == '\t' || c == '\n' || c == '\0') continue;

		lookahead = c;


		if (c == '$') {	// $�Է½� main���� �̵�
			lookahead = '$';
			return;
		}
		
		seq();	// ��ǥ ���
		
	}
}

void seq() {// ��ǥ ���
	// nexttoken���� ����� �迭�� ���鼭 ��ǥ ����ϱ�


	switch (lookahead) {
	case 'e':
		x = x + 1;
		break;
	case 'n':
		y = y + 1;
		break;
	case 'w':
		x = x - 1;
		break;
	case 's':
		y = y - 1;
		break;
	}
	if (lookahead != '$') {
		count++;
		look_p[count] = (int*)malloc(sizeof(int) * 2);
		look_p[count][0] = x;	// x ��ǥ ����
		look_p[count][1] = y;	// y ��ǥ ����
		printf("\(%d,%d\) ", look_p[count][0], look_p[count][1]);	// $���� ��µǴ� ��Ȳ
	}
	
	return;	// match�� �̵�
}

// �ذ��ؾ��Ұ�, ���� ��Ȳ �߰� �� ��� ���� ��ġ ����