#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "moneybook.h"

int selectMenu(){
    int menu;
    printf("\n*** 가계부 검색창 ***\n");
    printf("1. 가계부 조회\n");
    printf("2. 항목 추가\n");
    printf("3. 항목 수정\n");
    printf("4. 항목 삭제\n");
    printf("5. 파일 저장\n");
    printf("6. 항목 이름 검색\n");
    printf("7. 카테고리 검색\n");
    printf("8. 고정/변동 검색\n");
    printf("9. 수입/지출 검색\n");
    printf("0. 종료\n\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    return menu;
}

// 전체 가계부 상태 출력 (sum출력 필요)
void listBook(moneybook *m, int count){
    int i = 0;

    printf("\n%-s\t%-10s\t%-12s\t%-12s\t%-12s\t%-12s\t\n","No.", "카테고리", "항목명", "가격", "고정/변동", "수입/지출");
    printf("---------------------------------------------------------------------------------\n");
    for (i = 0; i < count; i++){
        if (m[i].price == -1) continue;
        printf("%2d\t ", i + 1);
        readBook(m[i]);
    }
    sumBook(m, i);
}

// 하나의 항목 출력
void readBook(moneybook m){
    printf("%-12s\t%-10s\t%-10d\t%-10s\t%-10s\t\n", m.category, m.name, m.price, m.fix, m.plusMinus);
}

// 항목 합계 계산
void sumBook(moneybook *m, int cnt){    
    int sum=0;
    for(int i=0 ; i<cnt ; i++){
        if(!strcmp(m[i].plusMinus,"+"))
            sum+=m[i].price;
        else
            sum-=m[i].price;
    }
    printf(" sum: %d\n",sum);
} 

// 항목 번호 검색
int selectDataNo(moneybook* m, int count){
    int no;
    listBook(m, count);
    printf("\n번호(취소 : 0) : ");
    scanf("%d", &no);
    return no;
}

// 항목 추가
int createBook(moneybook *m){
    printf("카테고리 : ");
    scanf(" %[^\n]", m->category);
    printf("이름 : ");
    scanf(" %[^\n]", m->name);
    printf("금액 : ");
    scanf(" %d", &m->price);
    printf("고정/변동 [y/n]: ");
    scanf(" %[^\n]", m->fix);
    printf("수입/지출 [+/-] : ");
    scanf(" %[^\n]", m->plusMinus);
    return 1;
}

// 항목 이름 검색
void searchBook(moneybook *m, int count){
    char bname[20];
    int scnt = 0;
    printf("검색할 항목 이름 : ");
    scanf(" %s", bname);
    printf("No. 카테고리 항목명 가격 고정/변동[y/n] 수입/지출[+/-]\n");
    printf("---------------------------------------------------\n");
    for(int i = 0; i < count; i++){
        if(m[i].price == -1) continue;
        if(strstr(m[i].name, bname)){
            printf("%2d ",i + 1);
            readBook(m[i]);
            scnt ++;
        }
    }
    if(scnt == 0) printf("=> 검색된 데이터 없음!");
    printf("\n");
}

// 제품 가격 검색
void searchCategory(moneybook *m, int count){
    char cname[256];
    int scnt = 0;
    printf("검색할 카테고리 : ");
    scanf(" %s", cname);
    printf("No. 카테고리 항목명 가격 고정/변동[y/n] 수입/지출[+/-]\n");
    printf("---------------------------------------------------\n");
    for(int i = 0; i < count; i++){
        if(m[i].price == -1) continue;
        if(strstr(m[i].category, cname)){
            printf("%2d ",i + 1);
            readBook(m[i]);
            scnt ++;
        }
    }
    if(scnt == 0) printf("=> 검색된 데이터 없음!");
    printf("\n");
}

// 고정/변동 검색
void searchFix(moneybook *m, int count){
    char fname[5];
    int scnt = 0;
    printf("고정/변동[y/n] : ");
    scanf(" %s", fname);
    printf("No. 카테고리 항목명 가격 고정/변동[y/n] 수입/지출[+/-]\n");
    printf("---------------------------------------------------\n");
    for(int i = 0; i < count; i++){
        if(m[i].price == -1) continue;
        if(strstr(m[i].fix, fname)){
            printf("%2d ",i + 1);
            readBook(m[i]);
            scnt ++;
        }
    }
    if(scnt == 0) printf("=> 검색된 데이터 없음!");
    printf("\n");
}

// 수입/지출 검색
void searchPlusMinus(moneybook *m, int count){
    char Pmname[5];
    int scnt = 0;
    printf("수입/지출[+/-] : ");
    scanf(" %s", Pmname);
    printf("No. 카테고리 항목명 가격 고정/변동[y/n] 수입/지출[+/-]\n");
    printf("---------------------------------------------------\n");
    for(int i = 0; i < count; i++){
        if(m[i].price == -1) continue;
        if(strstr(m[i].plusMinus, Pmname)){
            printf("%2d ",i + 1);
            readBook(m[i]);
            scnt ++;
        }
    }
    if(scnt == 0) printf("=> 검색된 데이터 없음!");
    printf("\n");
}

// 항목 수정
int updateBook(moneybook *m){
    printf("카테고리 : ");
    scanf(" %[^\n]", m->category);
    printf("이름 : ");
    scanf(" %[^\n]", m->name);
    printf("금액 : ");
    scanf(" %d", &m->price);
    printf("고정/변동 [y/n]: ");
    scanf("%s", m->fix);
    printf("수입/지출 [+/-] : ");
    scanf("%s", m->plusMinus);
    return 1;
}

// 항목 삭제
int deleteBook(moneybook *m){
    m->price = -1;
    return 1;
}

// File에서 데이터 불러오기
int loadData(moneybook *m){
    FILE *fp;
    fp = fopen("moneybook.txt","rt");
    int i = 0;
    if(fp == NULL){
        printf("=> 파일 없음\n");
    }
    else{
        for(; i < 256; i++){
            fscanf(fp," %[^:]%*c%[^:]%*c%[^:]%*c%[^:]%*c%d", m[i].category, m[i].name, m[i].fix, m[i].plusMinus, &m[i].price);
            if (feof(fp)) break;
        }
        fclose(fp);
        printf("=> 로딩 성공!\n");
    }
    return i;
}

// File 저장
void saveData(moneybook *m, int count){
    FILE *fp;
    fp = fopen("moneybook.txt","wt");
    for(int i = 0; i < count; i++){
        if(m[i].price == -1) continue;
        fprintf(fp,"%s:%s:%s:%s:%d\n",m[i].category, m[i].name, m[i].fix, m[i].plusMinus, m[i].price);
    }
    fclose(fp);
    printf("저장됨!\n");
}
