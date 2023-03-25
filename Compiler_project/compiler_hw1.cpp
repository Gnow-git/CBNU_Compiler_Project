#include <stdio.h>
#include <stdlib.h>	// exit 함수 라이브러리
#include <string.h>

char lookahead;	// 입력된 문자
int size = 100;	// 좌표가 저장될 배열 크기
int** look_p = (int**)malloc(sizeof(int*) * size);	// 입력 저장할 배열
int x, y, count,start_b,output = 0;	// 좌표 (x,y), 배열 위치, 문구 반복 방지 함수
char error, error_l;	// 에러 상황, 미정의된 문자

void nexttoken();	// 토큰 이동 함수
void seq();	// 오류 및 match 제어 함수
void instr(char lookahead);	// 좌표 계산 함수

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

	if (start_b == 0) error = 's';	// b로 시작 안할 경우

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

void match(char token) {	// 토큰 확인 함수
	if (lookahead == token) {
		instr(token);	// 좌표 계산
		nexttoken();	// 다음 토큰으로 이동
	}
	else {
		printf("match error\n");
		exit(1);	// 프로세스 종료
	}
}

void nexttoken() {	// 토큰 이동 함수
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

void seq() {	// 오류 및 match 제어 함수

	if (output == 0) {	// 출력 문구 한번만 나오게 지정
		printf("출력:");
		output++;
	}

	if (start_b >= 0 && lookahead == 'b') { // b로 시작했는지 파악
		++start_b;
	}

	if (start_b == 1) {	// 명령이 b로 시작할 경우
		if (lookahead == '$') {	// 명령이 $ 이면 nexttoken으로 이동
			return;
		}

		if (error == 'u') {	// 미정의된 명령 입력시
			return;
		}

		match(lookahead);	// 토큰 확인 함수
	}

	if (start_b >= 2) {	// b가 두번 입력 됐을 경우
		error = 'b';
		return;
	}

}

void instr(char lookahead) {	// 좌표 계산 함수

	switch (lookahead) {	// 명령에 따라 좌표 계산

	case 'b':
		x, y = 0;	// 현 위치 설정
		break;

	case 'e':		// east(오른쪽)
		x = x + 1;
		break;

	case 'n':		// north(위쪽)
		y = y + 1;
		break;

	case 'w':		// west(왼쪽)
		x = x - 1;
		break;

	case 's':		// south(아래쪽)
		y = y - 1;
		break;

	default :		// 미정의된 명령
		error = 'u';			// 에러 상황 지정
		error_l = lookahead;	// 해당 명령
		break;
	}

	if (lookahead != '$' && error != 'u') {	// 명령 끝과 미정의된 명령이 아닐 경우
		count++;	// 저장될 위치 1씩 증가
		look_p[count] = (int*)malloc(sizeof(int) * 2);	// x, y 저장할 공간 동적할당

		look_p[count][0] = x;	// x 좌표 저장
		look_p[count][1] = y;	// y 좌표 저장

		printf("\(%d,%d\) ", look_p[count][0], look_p[count][1]);	// 명령에 따른 x, y 좌표 출력
	}
	
	return;	// match로 이동
}