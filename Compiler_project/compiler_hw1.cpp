#include <stdio.h>
#include <stdlib.h>	// exit �Լ� ���̺귯��

char lookahead;	// �Էµ� ����
void nexttoken();
void seq();
void move(char token);


void main() {
	nexttoken();
	seq();
	if (lookahead == '$')	// �������� $��
	{
		printf("main���� �̵� \n");
		printf("��ǥ ���");
	}
	else
		printf("error\n");
}

void match(char token) {
	if (lookahead == token) {
		move(token);	// ��ū ����
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


		if (lookahead == '$') {	// $�Է½� main���� �̵�
			printf("end");
			return;
		}
		else {
			match(lookahead);	// getchar�� �޾ƿ� �Ϳ��� ���� �ϳ��� match�� �Ѿ
		}
		
	}
}

void move(char token) {	// �̵� ó�� �Լ�
	switch (token) {
		case 'b' :
			printf("�� ��ġ(0,0)\n");
			break;
		case 'e':
			printf("�� ��(1,0)\n");
			break;
		case 'n':
			printf("�� ��(0,1)\n");
			break;
		case 'w':
			printf("�� ��(-1,0)\n");
			break;
		case 's':
			printf("�� ��(0,-1)\n");
			break;
	}
}

void seq() {// ��ǥ ���
	// nexttoken���� ����� �迭�� ���鼭 ��ǥ ����ϱ�

	return;	// match�� �̵�
}