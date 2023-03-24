#include <stdio.h>
#include <stdlib.h>	// exit �Լ� ���̺귯��

char lookahead;	// �Էµ� ����
int x, y = 0;	// ��ǥ ����

void nexttoken();
void seq();
void position();	// ��ġ ���

void main() {
	printf("�Է�:");
	nexttoken();
	seq();	// ��ǥ ���
	if (lookahead == '$')	// �������� $��
	{;
		printf("���:");
		position();
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
	return;	// match�� �̵�
}

void position() {	// ��ǥ ���
	printf("(%d,%d)", x, y);
}