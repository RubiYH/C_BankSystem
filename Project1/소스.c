#include <stdio.h>
#include <stdlib.h>

typedef struct Account { //���� ����ü

	char name[20]; //�̸�
	int birth; //�������
	int phone; //��ȭ��ȣ
	int password; //���� ��й�ȣ
	float balance; //�ܾ�

} ACCOUNT;

//���� ��� �Լ�
void select_menu(); //ùȭ��(�޴�)
void create_account(); //���� ����
void transfer_account(); //���� ��ü
void deposit(); //�Ա�
void withdraw(); //���

//��� �Լ�
void show_account_list(); //���� ��� ǥ��
void show_account_detail(); //���� ��ȸ
void getLineSize(); //txt ���Ͽ� ��ϵ� ���� �� = txt ������ �� ����
void refreshDB(); //���� DB �ҷ�����
void updateDB(); //���� DB ������Ʈ

int account_index;

ACCOUNT accounts[100]; //���� �ִ� 100��

int main() {

	select_menu(); //�޴� ����
	return 0;
}

//���� �� ���� = db_size
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

//���� ��� �ҷ�����
void refreshDB() {
	getLineSize();
	printf("\n\n��ϵ� ���� ��: %d��", account_index);

	FILE* f;
	f = fopen("accounts.txt", "r");
	for (int i = 0; i < account_index; i++) {
		fscanf(f, "%s %d %d %d %f", accounts[i].name, &accounts[i].birth, &accounts[i].phone, &accounts[i].password, &accounts[i].balance);
	}
	fclose(f);
}

// �޴� ����
void select_menu() {
	refreshDB();

	int selected_number;

	printf("\n\n=======================================\n");
	printf("\n\n�޴��� �����ϼ���.\n");
	printf("1. ���� ����\n");
	printf("2. ���� ��ȸ\n");
	printf("3. ���� ��ü\n");
	printf("4. �Ա�\n");
	printf("5. ���\n");

	printf("\n���Ͻô� �޴��� ��ȣ�� �Է����ּ���: ");
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

//���� ����
void create_account() {
	int new_index = account_index + 1;

	printf("\n\n=======================================\n\n");
	printf("�̸��� �Է��ϼ���: ");
	scanf("%s", accounts[new_index].name);

	printf("\n������� 8�ڸ��� �Է��ϼ���: ");
	scanf("%d", &accounts[new_index].birth);

	printf("\n��ȭ��ȣ�� �Է��ϼ���: ");
	scanf("%d", &accounts[new_index].phone);

	printf("\n���� ��й�ȣ�� �Է��ϼ���: ");
	scanf("%d", &accounts[new_index].password);

	FILE* f = fopen("accounts.txt", "a+");

	fprintf(f, "\n%s %d %d %d %f", accounts[new_index].name, accounts[new_index].birth, accounts[new_index].phone, accounts[new_index].password, 0.00);

	fclose(f);

	account_index++;

	printf("\n\n���¸� �����Ͽ����ϴ�.");
	_sleep(1000);

	select_menu();
}

//���� ��� ǥ��
void show_account_list() {
	printf("\n\n=======================================\n");
	printf("\n�� ���� ���");
	printf("\n\n---------------------------------------\n");

	printf("| [��ȣ] �̸� / �������\n");
	for (int i = 0; i < account_index; i++) {
		printf("| [%d] %s / %d\n", i, accounts[i].name, accounts[i].birth);
	}
	printf("---------------------------------------\n");

}

//���� DB ������Ʈ
void updateDB() {
	FILE* f = fopen("accounts.txt", "w");

	for (int i = 0; i < account_index; i++) {
		fprintf(f, "\n%s %d %d %d %f", accounts[i].name, accounts[i].birth, accounts[i].phone, accounts[i].password, accounts[i].balance);
	}

	fclose(f);
}

//���� ��ȸ
void show_account_detail() {

	int selected_index;

	show_account_list();

	printf("\n\n��ȸ�� ������ ��ȣ�� �Է��ϼ���. �޴��� ���ư����� -1�� �Է��ϼ���: ");
	scanf("%d", &selected_index);

	if (selected_index <= -1) return select_menu();
	if (selected_index > account_index) {
		printf("\n\n�������� �ʴ� �����Դϴ�.\n\n");
		_sleep(1000);
		show_account_detail();
		return;
	}

	int input_password;

	printf("\n���� ��й�ȣ�� �Է��ϼ���: ");
	scanf("%d", &input_password);

	if (input_password != accounts[selected_index].password) {
		printf("\n��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n");
		_sleep(1000);
		show_account_detail();
	}
	else {

		printf("\n\n=======================================\n");
		printf("\n%s���� ���� ����\n\n", accounts[selected_index].name);
		printf("| �̸�: %s\n", accounts[selected_index].name);
		printf("| �������: %d\n", accounts[selected_index].birth);
		printf("| ��ȭ��ȣ: %d\n\n", accounts[selected_index].phone);
		printf("| �ܾ�: %.2f��\n", accounts[selected_index].balance);

		int next;

		printf("\n�ٸ� ���¸� ��ȸ�Ϸ��� 1, �޴��� ���ư����� 2�� �Է��ϼ���: ");
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

//���� ��ü
void transfer_account() {
	int select_index_from;

	show_account_list();

	printf("\n��ü�� ������ ��ȣ�� �Է��ϼ���. �޴��� ���ư����� -1�� �Է��ϼ���: ");
	scanf("%d", &select_index_from);

	if (select_index_from <= -1) return select_menu();
	if (select_index_from > account_index) {
		printf("\n\n�������� �ʴ� �����Դϴ�.\n\n");
		_sleep(1000);
		transfer_account();
		return;
	}

	int input_password_from;

	printf("\n���� ��й�ȣ�� �Է��ϼ���: ");
	scanf("%d", &input_password_from);

	if (input_password_from != accounts[select_index_from].password) {
		printf("\n��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n");
		_sleep(1000);
		transfer_account();
	}
	else {
		if (accounts[select_index_from].balance <= 0) {
			printf("\n\n�ش� ������ �ܾ��� �����ϴ�. �޴��� ���ư��� �Ա��ϼ���.\n\n");
			_sleep(1000);
			select_menu();
			return;
		}

		int select_index_to;

		show_account_list();

		while (1) {
			printf("\n��ü�� ������ ��ȣ�� �Է��ϼ���: ");
			scanf("%d", &select_index_to);

			if (select_index_to == select_index_from) {
				printf("\n��ü�� ���¿� ��ü�� ���´� ������ �� �����ϴ�.\n");
				_sleep(1000);
			}
			else {
				break;
			}
		}

		float input_cash;

		printf("\n---------------\n%s���� ���� ---> %s���� ����\n---------------\n���� ���� �ܾ�: %.2f��", accounts[select_index_from].name, accounts[select_index_to].name, accounts[select_index_from].balance);

		while (1) {
			printf("\n\n��ü�� �ݾ��� �Է��ϼ���: ");
			scanf("%f", &input_cash);

			if (input_cash > accounts[select_index_from].balance) {
				printf("\n\n��ü �ݾ��� �ܾ��� �ʰ��Ͽ����ϴ�.\n\n");
				_sleep(1000);
			}
			else {
				break;
			}
		}

		int final;

		printf("\n---------------\n%s�Կ��� %.2f���� ��ü�Ͻðڽ��ϱ�?\n��ü �� �ܾ�: %.2f ---> %.2f\n---------------\n", accounts[select_index_to].name, input_cash, accounts[select_index_from].balance, (accounts[select_index_from].balance - input_cash));
		printf("\n��ü�Ϸ��� 1, ����Ϸ��� 2�� �Է��ϼ���: ");
		scanf("%d", &final);

		switch (final) {
		case 1:
			accounts[select_index_from].balance -= input_cash;
			accounts[select_index_to].balance += input_cash;

			updateDB();

			printf("\n\n%s�Կ��� ������ü�� �Ϸ��Ͽ����ϴ�.\n\n��ü �� �ܾ�: %.2f��\n", accounts[select_index_to].name, accounts[select_index_from].balance);
			_sleep(1500);
			select_menu();
			break;
		case 2:
		default:
			printf("\n��ü�� ����Ͽ����ϴ�.\n");
			_sleep(1500);
			transfer_account();
			break;
		}

	}

}

//�Ա�
void deposit() {
	show_account_list();

	int selected_index;

	printf("\n�Ա��� ������ ��ȣ�� �Է��ϼ���. �޴��� ���ư����� -1�� �Է��ϼ���: ");
	scanf("%d", &selected_index);

	if (selected_index <= -1) return select_menu();
	if (selected_index > account_index) {
		printf("\n\n�������� �ʴ� �����Դϴ�.\n\n");
		_sleep(1000);
		deposit();
		return;
	}

	float input_deposit;

	while (1) {
		printf("\n\n%s�Կ��� �Ա��� �ݾ��� �Է��ϼ���: ", accounts[selected_index].name);
		scanf("%f", &input_deposit);

		if (input_deposit <= 0) {
			printf("\n\n�Ա��� �ݾ��� ����� �˴ϴ�.\n\n");
			_sleep(1000);
		}
		else {
			break;
		}
	}

	int final;

	printf("\n\n---------------\n%s�Կ��� %.2f���� �Ա��Ͻðڽ��ϱ�?\n---------------\n", accounts[selected_index].name, input_deposit);
	printf("�Ա��Ϸ��� 1, ����Ϸ��� 2�� �Է��ϼ���: ");
	scanf("%d", &final);

	switch (final) {
	case 1:
		accounts[selected_index].balance += input_deposit;

		updateDB();

		printf("\n\n%s�Կ��� %.2f���� �Ա��Ͽ����ϴ�.\n\n", accounts[selected_index].name, input_deposit);
		_sleep(1500);
		select_menu();
		break;
	case 2:
	default:
		printf("\n�Ա��� ����Ͽ����ϴ�.\n");
		_sleep(1500);
		deposit();
		break;
	}


}

//���
void withdraw() {

	show_account_list();

	int selected_index;

	printf("\n����� ������ ��ȣ�� �Է��ϼ���. �޴��� ���ư����� -1�� �Է��ϼ���: ");
	scanf("%d", &selected_index);

	if (selected_index <= -1) return select_menu();
	if (selected_index > account_index) {
		printf("\n\n�������� �ʴ� �����Դϴ�.\n\n");
		_sleep(1000);
		withdraw();
		return;
	}

	int input_password;

	printf("\n���� ��й�ȣ�� �Է��ϼ���: ");
	scanf("%d", &input_password);

	if (input_password != accounts[selected_index].password) {
		printf("\n��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n");
		_sleep(1000);
		withdraw();
	}
	else {

		float input_withdraw;

		while (1) {
			printf("\n���� ���� �ܾ�: %.2f\n%s���� ���¿��� ����� �ݾ��� �Է��ϼ���: ", accounts[selected_index].balance, accounts[selected_index].name);
			scanf("%f", &input_withdraw);

			if (input_withdraw <= 0) {
				printf("\n\n����� �ݾ��� ����� �˴ϴ�.\n\n");
				_sleep(1000);
			}
			else {
				break;
			}
		}

		int final;

		printf("\n\n---------------\n%s���� ���¿��� %.2f���� ����Ͻðڽ��ϱ�?\n��� �� �ܾ�: %.2f\n---------------\n", accounts[selected_index].name, input_withdraw, accounts[selected_index].balance - input_withdraw);
		printf("����Ϸ��� 1, ����Ϸ��� 2�� �Է��ϼ���: ");
		scanf("%d", &final);

		switch (final) {
		case 1:
			accounts[selected_index].balance -= input_withdraw;

			updateDB();

			printf("\n\n%s���� ���¿��� %.2f���� ����Ͽ����ϴ�.\n�ܾ�: %.2f\n", accounts[selected_index].name, input_withdraw, accounts[selected_index].balance);
			_sleep(1500);
			select_menu();
			break;
		case 2:
		default:
			printf("\n����� ����Ͽ����ϴ�.\n");
			_sleep(1500);
			withdraw();
			break;
		}


	}
}