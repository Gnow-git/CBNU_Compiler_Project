#include <stdio.h>
#include <stdlib.h>	// exit �Լ� ���̺귯��
#include <string.h>

char lookahead;	// �Էµ� ����
int size = 10;
int** look_p = (int**)malloc(sizeof(int*) * size);	// �Է� ������ �迭
int x, y, count,start_b,output = 0;	// ��ǥ ����
char error, error_l;	// ������ ���� ����

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
		printf("error\n");

	if (start_b == 0) error = 's';
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

void seq() {

	if (output == 0) {
		printf("���:");
		output++;
	}

	if (start_b >= 0 && lookahead == 'b') { // b�� �����ߴ��� �ľ�
		++start_b;
	}

	if (start_b == 1) {
		if (lookahead == '$') {	// $ �Է½� nexttoken���� �̵�
			return;
		}
		if (error == 'u') {	// �����ǵ� ���� �Է½�
			return;
		}
		match(lookahead);
	}
	if (start_b >= 2) {	// b�� �ι� �Է� ���� ���
		error = 'b';
		return;
	}

}

void instr(char lookahead) {// ��ǥ ���
	// nexttoken���� ����� �迭�� ���鼭 ��ǥ ����ϱ�

	switch (lookahead) {

	case 'b':
		break;
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
	default :		// �����ǵ� ���
		error = 'u';
		error_l = lookahead;
		break;
	}

	if (lookahead != '$' && error != 'u') {
		count++;
		look_p[count] = (int*)malloc(sizeof(int) * 2);

		look_p[count][0] = x;	// x ��ǥ ����
		look_p[count][1] = y;	// y ��ǥ ����
		printf("\(%d,%d\) ", look_p[count][0], look_p[count][1]);	// $���� ��µǴ� ��Ȳ
	}
	
	return;	// match�� �̵�
}