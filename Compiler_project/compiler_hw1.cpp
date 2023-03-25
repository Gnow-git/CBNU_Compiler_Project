#include <stdio.h>
#include <stdlib.h>	// exit 함수 라이브러리
#include <string.h>

char lookahead;	// 입력된 문자
int size = 10;
int** look_p = (int**)malloc(sizeof(int*) * size);	// 입력 저장할 배열
int x, y, count,start = 0;	// 좌표 설정


void nexttoken();
void instr(char lookahead);
void seq();

void main() {
	printf("입력:");
	nexttoken();
	seq();
	if (lookahead == '$')	// 마지막이 $면
	{;
		
		free(look_p);	// 배열 메모리 해제
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
		
			seq();
		return;
	}
}

void seq() {
	
	if (start == 0 && lookahead == 'b') { // b로 시작했는지 파악
		start = 1;
	}
	else if (start == 1) {
		if (lookahead == '$') {	// $입력시 main으로 이동
			return;
		}
		match(lookahead);
	}
	else {
		return;
	};

}

void instr(char lookahead) {// 좌표 계산
	// nexttoken에서 저장된 배열을 보면서 좌표 계산하기


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

		look_p[count][0] = x;	// x 좌표 저장
		look_p[count][1] = y;	// y 좌표 저장
		printf("\(%d,%d\) ", look_p[count][0], look_p[count][1]);	// $까지 출력되는 상황
	}
	
	return;	// match로 이동
}

// 해결해야할것, 에러 상황 추가 및 출력 문구 위치 지정