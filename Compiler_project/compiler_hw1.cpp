#include <stdio.h>
#include <stdlib.h>	// exit 함수 라이브러리
#include <string.h>

char lookahead;	// 입력된 문자
int size = 10;
int** look_p = (int**)malloc(sizeof(int*) * size);	// 입력 저장할 배열
int x, y, count,start_b,output = 0;	// 좌표 설정
char error, error_l;	// 에러에 대한 문구

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
		printf("error\n");

	if (start_b == 0) error = 's';
	switch (error) {	// 에러 처리
	case 's' :
		printf("(b로 시작하지 않아 문법 오류)\n");
		break;
	case 'u':
		printf("(미정의된 명령 %c에 대한 오류)\n", error_l);
		break;
	case 'b' :
		printf("(중간에 b가 나올 수 없음. 문법 오류)\n");
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
		exit(1);	// 프로세스 종료
	}
}

void nexttoken() {
	char c;
	if (error == 'u') return;	// 끊어서 명령을 입력할 경우 예외처리
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

	if (output == 0) {
		printf("출력:");
		output++;
	}

	if (start_b >= 0 && lookahead == 'b') { // b로 시작했는지 파악
		++start_b;
	}

	if (start_b == 1) {
		if (lookahead == '$') {	// $ 입력시 nexttoken으로 이동
			return;
		}
		if (error == 'u') {	// 미정의된 문자 입력시
			return;
		}
		match(lookahead);
	}
	if (start_b >= 2) {	// b가 두번 입력 됐을 경우
		error = 'b';
		return;
	}

}

void instr(char lookahead) {// 좌표 계산
	// nexttoken에서 저장된 배열을 보면서 좌표 계산하기

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
	default :		// 미정의된 명령
		error = 'u';
		error_l = lookahead;
		break;
	}

	if (lookahead != '$' && error != 'u') {
		count++;
		look_p[count] = (int*)malloc(sizeof(int) * 2);

		look_p[count][0] = x;	// x 좌표 저장
		look_p[count][1] = y;	// y 좌표 저장
		printf("\(%d,%d\) ", look_p[count][0], look_p[count][1]);	// $까지 출력되는 상황
	}
	
	return;	// match로 이동
}