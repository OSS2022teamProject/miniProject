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
    int sum=0;
    printf("No. 카테고리  항목명   가격  고정/변동  수입/지출\n");
    printf("---------------------------------------------------\n");
    for (i = 0; i < count; i++){
        if (m[i].price == -1) continue;
        printf("%d ", i + 1);
        readBook(m[i]);
        if(!strcmp(m[i].plusMinus,"+"))
            sum+=m[i].price;
        else
            sum-=m[i].price;
    }
    printf("sum: %d\n",sum);
}

// 하나의 항목 출력
void readBook(moneybook m){
    printf("  %-12s%-10s%  -10d%-10s%-10s\n", m.category, m.name, m.price, m.fix, m.plusMinus);
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
    printf("==>추가됨!\n");
    return 1;
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

