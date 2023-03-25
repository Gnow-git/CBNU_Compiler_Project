#include <stdio.h>
#include <stdlib.h>	// exit �Լ� ���̺귯��
#include <string.h>

char lookahead;	// �Էµ� ����
int size = 100;	// ��ǥ�� ����� �迭 ũ��
int** look_p = (int**)malloc(sizeof(int*) * size);	// �Է� ������ �迭
int x, y, count,start_b,output = 0;	// ��ǥ (x,y), �迭 ��ġ, ���� �ݺ� ���� �Լ�
char error, error_l;	// ���� ��Ȳ, �����ǵ� ����

void nexttoken();	// ��ū �̵� �Լ�
void seq();	// ���� �� match ���� �Լ�
void instr(char lookahead);	// ��ǥ ��� �Լ�

void main() {
	printf("�Է�:");
	nexttoken();
	seq();

	if (lookahead == '$')	// �������� $��
	{;
		
		free(look_p);	// �迭 �޸� ����
	}
	else
		printf("error\n");

	if (start_b == 0) error = 's';	// b�� ���� ���� ���

	switch (error) {	// ���� ó��

	case 's' :
		printf("(b�� �������� �ʾ� ���� ����)\n");
		break;

	case 'u':
		printf("(�����ǵ� ��� %c�� ���� ����)\n", error_l);
		break;

	case 'b' :
		printf("(�߰��� b�� ���� �� ����. ���� ����)\n");
		break;

	default :
		printf("\n");
		break;
	}
}

void match(char token) {	// ��ū Ȯ�� �Լ�
	if (lookahead == token) {
		instr(token);	// ��ǥ ���
		nexttoken();	// ���� ��ū���� �̵�
	}
	else {
		printf("match error\n");
		exit(1);	// ���μ��� ����
	}
}

void nexttoken() {	// ��ū �̵� �Լ�
	char c;
	if (error == 'u') return;	// ��� ����� �Է��� ��� ����ó��
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

void seq() {	// ���� �� match ���� �Լ�

	if (output == 0) {	// ��� ���� �ѹ��� ������ ����
		printf("���:");
		output++;
	}

	if (start_b >= 0 && lookahead == 'b') { // b�� �����ߴ��� �ľ�
		++start_b;
	}

	if (start_b == 1) {	// ����� b�� ������ ���
		if (lookahead == '$') {	// ����� $ �̸� nexttoken���� �̵�
			return;
		}

		if (error == 'u') {	// �����ǵ� ��� �Է½�
			return;
		}

		match(lookahead);	// ��ū Ȯ�� �Լ�
	}

	if (start_b >= 2) {	// b�� �ι� �Է� ���� ���
		error = 'b';
		return;
	}

}

void instr(char lookahead) {	// ��ǥ ��� �Լ�

	switch (lookahead) {	// ��ɿ� ���� ��ǥ ���

	case 'b':
		x, y = 0;	// �� ��ġ ����
		break;

	case 'e':		// east(������)
		x = x + 1;
		break;

	case 'n':		// north(����)
		y = y + 1;
		break;

	case 'w':		// west(����)
		x = x - 1;
		break;

	case 's':		// south(�Ʒ���)
		y = y - 1;
		break;

	default :		// �����ǵ� ���
		error = 'u';			// ���� ��Ȳ ����
		error_l = lookahead;	// �ش� ���
		break;
	}

	if (lookahead != '$' && error != 'u') {	// ��� ���� �����ǵ� ����� �ƴ� ���
		count++;	// ����� ��ġ 1�� ����
		look_p[count] = (int*)malloc(sizeof(int) * 2);	// x, y ������ ���� �����Ҵ�

		look_p[count][0] = x;	// x ��ǥ ����
		look_p[count][1] = y;	// y ��ǥ ����

		printf("\(%d,%d\) ", look_p[count][0], look_p[count][1]);	// ��ɿ� ���� x, y ��ǥ ���
	}
	
	return;	// match�� �̵�
}