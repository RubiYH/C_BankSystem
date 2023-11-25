#include <stdio.h>
#include <stdlib.h>

typedef struct Account { //계좌 구조체

	char name[20]; //이름
	int birth; //생년월일
	int phone; //전화번호
	int password; //계좌 비밀번호
	float balance; //잔액

} ACCOUNT;

//메인 기능 함수
void select_menu(); //첫화면(메뉴)
void create_account(); //계좌 생성
void transfer_account(); //계좌 이체
void deposit(); //입금
void withdraw(); //출금

//모듈 함수
void show_account_list(); //계좌 목록 표시
void show_account_detail(); //계좌 조회
void getLineSize(); //txt 파일에 등록된 계좌 수 = txt 파일의 줄 개수
void refreshDB(); //계좌 DB 불러오기
void updateDB(); //계좌 DB 업데이트

int account_index;

ACCOUNT accounts[100]; //계좌 최대 100개

int main() {

	select_menu(); //메뉴 선택
	return 0;
}

//파일 줄 개수 = account_index
void getLineSize() {
	FILE* fp;
	fp = fopen("accounts.txt", "r");
	char tmp;
	int cnt = 1;

	while (fscanf(fp, "%c", &tmp) != EOF) {
		if (tmp == '\n')
			cnt++;
	}

	account_index = cnt - 1;

	fclose(fp);
}

//계좌 목록 불러오기
void refreshDB() {
	getLineSize();
	printf("\n\n등록된 계좌 수: %d개", account_index);

	FILE* f;
	f = fopen("accounts.txt", "r");
	for (int i = 0; i < account_index; i++) {
		fscanf(f, "%s %d %d %d %f", accounts[i].name, &accounts[i].birth, &accounts[i].phone, &accounts[i].password, &accounts[i].balance);
	}
	fclose(f);
}

// 메뉴 선택
void select_menu() {
	refreshDB();

	int selected_number;

	printf("\n\n=======================================\n");
	printf("\n\n메뉴를 선택하세요.\n");
	printf("1. 계좌 생성\n");
	printf("2. 계좌 조회\n");
	printf("3. 계좌 이체\n");
	printf("4. 입금\n");
	printf("5. 출금\n");

	printf("\n원하시는 메뉴의 번호를 입력해주세요: ");
	scanf("%d", &selected_number);

	switch (selected_number) {
	case 1:
		create_account();
		break;
	case 2:
		show_account_detail();
		break;
	case 3:
		transfer_account();
		break;
	case 4:
		deposit();
		break;
	case 5:
		withdraw();
		break;
	default:
		select_menu();
		break;
	}
}

//계좌 생성
void create_account() {
	int new_index = account_index + 1;

	printf("\n\n=======================================\n\n");
	printf("이름을 입력하세요: ");
	scanf("%s", accounts[new_index].name);

	printf("\n생년월일 8자리을 입력하세요: ");
	scanf("%d", &accounts[new_index].birth);

	printf("\n전화번호를 입력하세요: ");
	scanf("%d", &accounts[new_index].phone);

	printf("\n계좌 비밀번호를 입력하세요: ");
	scanf("%d", &accounts[new_index].password);

	FILE* f = fopen("accounts.txt", "a+");

	fprintf(f, "\n%s %d %d %d %f", accounts[new_index].name, accounts[new_index].birth, accounts[new_index].phone, accounts[new_index].password, 0.00);

	fclose(f);

	account_index++;

	printf("\n\n계좌를 생성하였습니다.");
	_sleep(1000);

	select_menu();
}

//계좌 목록 표시
void show_account_list() {
	printf("\n\n=======================================\n");
	printf("\n총 계좌 목록");
	printf("\n\n---------------------------------------\n");

	printf("| [번호] 이름 / 생년월일\n");
	for (int i = 0; i < account_index; i++) {
		printf("| [%d] %s / %d\n", i, accounts[i].name, accounts[i].birth);
	}
	printf("---------------------------------------\n");

}

//계좌 DB 업데이트
void updateDB() {
	FILE* f = fopen("accounts.txt", "w");

	for (int i = 0; i < account_index; i++) {
		fprintf(f, "\n%s %d %d %d %f", accounts[i].name, accounts[i].birth, accounts[i].phone, accounts[i].password, accounts[i].balance);
	}

	fclose(f);
}

//계좌 조회
void show_account_detail() {

	int selected_index;

	show_account_list();

	printf("\n\n조회할 계좌의 번호를 입력하세요. 메뉴로 돌아가려면 -1을 입력하세요: ");
	scanf("%d", &selected_index);

	if (selected_index <= -1) return select_menu();
	if (selected_index > account_index) {
		printf("\n\n존재하지 않는 계좌입니다.\n\n");
		_sleep(1000);
		show_account_detail();
		return;
	}

	int input_password;

	printf("\n계좌 비밀번호를 입력하세요: ");
	scanf("%d", &input_password);

	if (input_password != accounts[selected_index].password) {
		printf("\n비밀번호가 일치하지 않습니다.\n");
		_sleep(1000);
		show_account_detail();
	}
	else {

		printf("\n\n=======================================\n");
		printf("\n%s님의 계좌 정보\n\n", accounts[selected_index].name);
		printf("| 이름: %s\n", accounts[selected_index].name);
		printf("| 생년월일: %d\n", accounts[selected_index].birth);
		printf("| 전화번호: %d\n\n", accounts[selected_index].phone);
		printf("| 잔액: %.2f원\n", accounts[selected_index].balance);

		int next;

		printf("\n다른 계좌를 조회하려면 1, 메뉴로 돌아가려면 2를 입력하세요: ");
		scanf("%d", &next);

		switch (next) {
		case 1:
			show_account_detail();
			break;
		case 2:
		default:
			select_menu();
			break;
		}
	}

}

//계좌 이체
void transfer_account() {
	int select_index_from;

	show_account_list();

	printf("\n이체할 계좌의 번호를 입력하세요. 메뉴로 돌아가려면 -1을 입력하세요: ");
	scanf("%d", &select_index_from);

	if (select_index_from <= -1) return select_menu();
	if (select_index_from > account_index) {
		printf("\n\n존재하지 않는 계좌입니다.\n\n");
		_sleep(1000);
		transfer_account();
		return;
	}

	int input_password_from;

	printf("\n계좌 비밀번호를 입력하세요: ");
	scanf("%d", &input_password_from);

	if (input_password_from != accounts[select_index_from].password) {
		printf("\n비밀번호가 일치하지 않습니다.\n");
		_sleep(1000);
		transfer_account();
	}
	else {
		if (accounts[select_index_from].balance <= 0) {
			printf("\n\n해당 계좌의 잔액이 없습니다. 메뉴로 돌아가서 입금하세요.\n\n");
			_sleep(1000);
			select_menu();
			return;
		}

		int select_index_to;

		show_account_list();

		while (1) {
			printf("\n이체될 계좌의 번호를 입력하세요: ");
			scanf("%d", &select_index_to);

			if (select_index_to == select_index_from) {
				printf("\n이체될 계좌와 이체할 계좌는 동일할 수 없습니다.\n");
				_sleep(1000);
			}
			else {
				break;
			}
		}

		float input_cash;

		printf("\n---------------\n%s님의 계좌 ---> %s님의 계좌\n---------------\n보유 계좌 잔액: %.2f원", accounts[select_index_from].name, accounts[select_index_to].name, accounts[select_index_from].balance);

		while (1) {
			printf("\n\n이체할 금액을 입력하세요: ");
			scanf("%f", &input_cash);

			if (input_cash > accounts[select_index_from].balance) {
				printf("\n\n이체 금액이 잔액을 초과하였습니다.\n\n");
				_sleep(1000);
			}
			else {
				break;
			}
		}

		int final;

		printf("\n---------------\n%s님에게 %.2f원을 이체하시겠습니까?\n이체 후 잔액: %.2f ---> %.2f\n---------------\n", accounts[select_index_to].name, input_cash, accounts[select_index_from].balance, (accounts[select_index_from].balance - input_cash));
		printf("\n이체하려면 1, 취소하려면 2를 입력하세요: ");
		scanf("%d", &final);

		switch (final) {
		case 1:
			accounts[select_index_from].balance -= input_cash;
			accounts[select_index_to].balance += input_cash;

			updateDB();

			printf("\n\n%s님에게 계좌이체를 완료하였습니다.\n\n이체 후 잔액: %.2f원\n", accounts[select_index_to].name, accounts[select_index_from].balance);
			_sleep(1500);
			select_menu();
			break;
		case 2:
		default:
			printf("\n이체를 취소하였습니다.\n");
			_sleep(1500);
			transfer_account();
			break;
		}

	}

}

//입금
void deposit() {
	show_account_list();

	int selected_index;

	printf("\n입금할 계좌의 번호를 입력하세요. 메뉴로 돌아가려면 -1을 입력하세요: ");
	scanf("%d", &selected_index);

	if (selected_index <= -1) return select_menu();
	if (selected_index > account_index) {
		printf("\n\n존재하지 않는 계좌입니다.\n\n");
		_sleep(1000);
		deposit();
		return;
	}

	float input_deposit;

	while (1) {
		printf("\n\n%s님에게 입금할 금액을 입력하세요: ", accounts[selected_index].name);
		scanf("%f", &input_deposit);

		if (input_deposit <= 0) {
			printf("\n\n입금할 금액은 양수만 됩니다.\n\n");
			_sleep(1000);
		}
		else {
			break;
		}
	}

	int final;

	printf("\n\n---------------\n%s님에게 %.2f원을 입금하시겠습니까?\n---------------\n", accounts[selected_index].name, input_deposit);
	printf("입금하려면 1, 취소하려면 2를 입력하세요: ");
	scanf("%d", &final);

	switch (final) {
	case 1:
		accounts[selected_index].balance += input_deposit;

		updateDB();

		printf("\n\n%s님에게 %.2f원을 입금하였습니다.\n\n", accounts[selected_index].name, input_deposit);
		_sleep(1500);
		select_menu();
		break;
	case 2:
	default:
		printf("\n입금을 취소하였습니다.\n");
		_sleep(1500);
		deposit();
		break;
	}


}

//출금
void withdraw() {

	show_account_list();

	int selected_index;

	printf("\n출금할 계좌의 번호를 입력하세요. 메뉴로 돌아가려면 -1을 입력하세요: ");
	scanf("%d", &selected_index);

	if (selected_index <= -1) return select_menu();
	if (selected_index > account_index) {
		printf("\n\n존재하지 않는 계좌입니다.\n\n");
		_sleep(1000);
		withdraw();
		return;
	}

	int input_password;

	printf("\n계좌 비밀번호를 입력하세요: ");
	scanf("%d", &input_password);

	if (input_password != accounts[selected_index].password) {
		printf("\n비밀번호가 일치하지 않습니다.\n");
		_sleep(1000);
		withdraw();
	}
	else {

		float input_withdraw;

		while (1) {
			printf("\n현재 계좌 잔액: %.2f\n%s님의 계좌에서 출금할 금액을 입력하세요: ", accounts[selected_index].balance, accounts[selected_index].name);
			scanf("%f", &input_withdraw);

			if (input_withdraw <= 0) {
				printf("\n\n출금할 금액은 양수만 됩니다.\n\n");
				_sleep(1000);
			}
			else {
				break;
			}
		}

		int final;

		printf("\n\n---------------\n%s님의 계좌에서 %.2f원을 출금하시겠습니까?\n출금 후 잔액: %.2f\n---------------\n", accounts[selected_index].name, input_withdraw, accounts[selected_index].balance - input_withdraw);
		printf("출금하려면 1, 취소하려면 2를 입력하세요: ");
		scanf("%d", &final);

		switch (final) {
		case 1:
			accounts[selected_index].balance -= input_withdraw;

			updateDB();

			printf("\n\n%s님의 계좌에서 %.2f원을 출금하였습니다.\n잔액: %.2f\n", accounts[selected_index].name, input_withdraw, accounts[selected_index].balance);
			_sleep(1500);
			select_menu();
			break;
		case 2:
		default:
			printf("\n출금을 취소하였습니다.\n");
			_sleep(1500);
			withdraw();
			break;
		}


	}
}
