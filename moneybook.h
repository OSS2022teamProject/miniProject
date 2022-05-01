typedef struct{
	char plusMinus; // 수입/지출 (수입:+ / 지출:-)
	char name[20]; // 이름
	int price; // 가격
	char category[256]; // 카테고리
	char fix; // 고정/변동(y/n)
} moneybook;

int selectMenu();

void listBook(moneybook *m, int count); // 전체 가계부 상태 출력 (sum출력 필요)
void readBook(moneybook m); // 하나의 항목 출력
int createBook(moneybook *m); // 항목 추가

int updateBook(moneybook *m); // 항목 수정
int deleteBook(moneybook *m); // 항목 삭제

void sumBook(moneybook *m); // 항목 합계 계산

int selectDataNo(moneybook *m, int count); // 항목 번호 검색
void searchBook(moneybook *m, int count); // 항목 이름 검색
void searchKategorie(moneybook *m, int count); // 가계부 카테고리 검색 (sum출력 필요)
void searchFix(moneybook *m, int count); // 고정/변동 검색

void saveData(moneybook *m, int count); // File 저장
int loadData(moneybook *m); // File에서 데이터 불러오기
