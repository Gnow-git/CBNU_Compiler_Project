#include <stdio.h>
#include <stdlib.h>	// exit 함수 라이브러리

char lookahead;	// 입력된 문자
void nexttoken();
void seq();
void move(char token);


void main() {
	nexttoken();
	seq();
	if (lookahead == '$')	// 마지막이 $면
	{
		printf("main으로 이동 \n");
		printf("좌표 출력");
	}
	else
		printf("error\n");
}

void match(char token) {
	if (lookahead == token) {
		move(token);	// 토큰 전달
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


		if (lookahead == '$') {	// $입력시 main으로 이동
			printf("end");
			return;
		}
		else {
			match(lookahead);	// getchar로 받아온 것에서 문자 하나씩 match로 넘어감
		}
		
	}
}

void move(char token) {	// 이동 처리 함수
	switch (token) {
		case 'b' :
			printf("현 위치(0,0)\n");
			break;
		case 'e':
			printf("동 쪽(1,0)\n");
			break;
		case 'n':
			printf("북 쪽(0,1)\n");
			break;
		case 'w':
			printf("서 쪽(-1,0)\n");
			break;
		case 's':
			printf("남 쪽(0,-1)\n");
			break;
	}
}

void seq() {// 좌표 계산
	// nexttoken에서 저장된 배열을 보면서 좌표 계산하기

	return;	// match로 이동
}