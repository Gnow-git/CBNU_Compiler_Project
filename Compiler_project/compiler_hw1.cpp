#include <stdio.h>
#include <stdlib.h>	// exit 함수 라이브러리

char lookahead;	// 입력된 문자
void nexttoken();
void seq();

void main() {
	nexttoken();
	seq();
	if (lookahead == '$')	// 마지막이 $면
		printf("\n");
	else
		printf("error\n");
}

void match(char token) {
	if (lookahead == token)
		nexttoken();
	else {
		printf("error\n");
		exit(1);	// 프로세스 종료
	}
}

void nexttoken() {
	char c;

	while (1) {
		c = getchar();
		if (c == EOF) {	// ctrl + z할 경우
			lookahead = '$';
			return;
		}
		if (c == ' ' || c == '\t' || c == '\n' || c == '\0') continue;

		lookahead = c;
		printf("%c", lookahead);

		// $시 출력되게 짜야함
		match(lookahead);	// getchar로 받아온 것에서 문자 하나씩 match로 넘어감

		return;
	}
}

void seq() {	// 새로 추가

}