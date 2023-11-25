# C언어 프로그래밍 세특 - 은행 계좌 시스템 구현

## C언어의 구조체를 활용한 CLI 기반의 간단한 계좌 시스템 시뮬레이션

  
[소스 코드](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/%EC%86%8C%EC%8A%A4.c)  

시연 영상 - https://drive.google.com/file/d/1dWJ1HAKC_q3GQDeU7Ax74LOxNLVAuO2f/view?usp=drive_link  

  
## 주요 기능 함수  
  
- [첫화면(메뉴)](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/%EC%86%8C%EC%8A%A4.c?plain=1#L68-L105)
- [계좌 생성](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/소스.c?plain=1#L107-L136)
- [계좌 이체](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/소스.c?plain=1#L218-L314)
- [입금](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/소스.c?plain=1#L316-L373)
- [출금](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/소스.c?plain=1#L375-L446)
  
  
## 기타 모듈 함수  
  
- [계좌 목록 표시](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/소스.c?plain=1#L138-L150)
- [계좌 조회](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/소스.c?plain=1#L163-L216)
- [등록된 총 계좌 수 불러오기](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/소스.c?plain=1#L38-L53)
- [계좌 DB 불러오기](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/소스.c?plain=1#L56-L66)
- [계좌 DB 업데이트](https://github.com/RubiYH/C_BankSystem/blob/master/Project1/소스.c?plain=1#L152-L161)
  
  
## 계좌 DB

텍스트 파일을 이용하여 간단한 관계형 DB를 구현함. `fscanf()` 함수를 통해 띄어쓰기 단위로 각 변수를 입력받고 구조체에 저장함.

* 계좌 형식  
`accounts.txt`  
```-> 홍길동  14430101 1011112222   4321   30000.000000```  
```-> [이름] [생년월일]  [전화번호] [계좌 비밀번호]  [잔액]```

* 구조체
```c
typedef struct Account {

	char name[20]; //이름
	int birth; //생년월일
	int phone; //전화번호
	int password; //계좌 비밀번호
	float balance; //잔액

} ACCOUNT;
```
