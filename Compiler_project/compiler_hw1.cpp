#include <stdio.h>
#include <stdlib.h>	// exit 함수 라이브러리

char lookahead;	// 입력된 문자
int x, y = 0;	// 좌표 설정

void nexttoken();
void seq();
void position();	// 위치 출력

void main() {
	printf("입력:");
	nexttoken();
	seq();	// 좌표 계산
	if (lookahead == '$')	// 마지막이 $면
	{;
		printf("출력:");
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
		exit(1);	// 프로세스 종료
	}
}

void nexttoken() {
	char c;
	while (1) {
		c = getchar();	// 문자 입력
		if (c == EOF) {	// ctrl + z할 경우
			lookahead = '$';
			return;
		}
		if (c == ' ' || c == '\t' || c == '\n' || c == '\0') continue;

		lookahead = c;


		if (c == '$') {	// $입력시 main으로 이동
			lookahead = '$';
			return;
		}
		seq();	// 좌표 계산
		
	}
}

void seq() {// 좌표 계산
	// nexttoken에서 저장된 배열을 보면서 좌표 계산하기
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
	return;	// match로 이동
}

void position() {	// 좌표 출력
	printf("(%d,%d)", x, y);
}