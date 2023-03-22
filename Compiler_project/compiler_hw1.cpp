#include <stdio.h>
#include <stdlib.h>	// exit 함수 라이브러리

char lookahead;
void nexttoken();
void seq();

void main() {
	nexttoken();
	seq();
	if (lookahead == '$')
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
		if (c == EOF) {
			lookahead = '$';
			return;
		}
		if (c == ' ' || c == '\t' || c == '\n' || c == '\0') continue;
		lookahead = c;
		return;
	}
}

void seq() {	// 새로 추가

}