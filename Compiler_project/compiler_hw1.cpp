#include <stdio.h>
#include <stdlib.h>	// exit �Լ� ���̺귯��
#include <string.h>

char lookahead;	// �Էµ� ����
int size = 10;
int** look_p = (int**)malloc(sizeof(int*) * size);	// �Է� ������ �迭
int x, y, count,start = 0;	// ��ǥ ����


void nexttoken();
void instr(char lookahead);
void seq();

void main() {
	printf("�Է�:");
	nexttoken();
	seq();
	if (lookahead == '$')	// �������� $��
	{;
		
		free(look_p);	// �迭 �޸� ����
	}
	else
		printf("main error\n");
}

void match(char token) {
	if (lookahead == token) {
		instr(token);
		nexttoken();
	}
	else {
		printf("match error\n");
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
		
			seq();
		return;
	}
}

void seq() {
	
	if (start == 0 && lookahead == 'b') { // b�� �����ߴ��� �ľ�
		start = 1;
	}
	else if (start == 1) {
		if (lookahead == '$') {	// $�Է½� main���� �̵�
			return;
		}
		match(lookahead);
	}
	else {
		return;
	};

}

void instr(char lookahead) {// ��ǥ ���
	// nexttoken���� ����� �迭�� ���鼭 ��ǥ ����ϱ�


	switch (lookahead) {
	case 'e':		// east
		x = x + 1;
		break;
	case 'n':		// north
		y = y + 1;
		break;
	case 'w':		// west
		x = x - 1;
		break;
	case 's':		// south
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