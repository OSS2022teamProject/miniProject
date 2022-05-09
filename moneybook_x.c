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
    printf("No. 카테고리 항목명 가격 고정/변동 수입/지출\n");
    printf("---------------------------------------------------\n");
    for (i = 0; i < count; i++){
        if (m[i].price == -1) continue;
        printf("%d ", i + 1);
        readBook(m[i]);
    }
    printf("\n");
}

// 하나의 항목 출력
void readBook(moneybook m){
    printf("%s %s %d %s %s\n", m.category, m.name, m.price, m.fix, m.plusMinus);
}

// 항목 번호 검색
int selectDataNo(moneybook* m, int count){
    int no;
    listBook(m, count);
    printf("번호(취소 : 0) : ");
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
    scanf(" %[^\n]", m->fix);
    printf("수입/지출 [+/-] : ");
    scanf(" %[^\n]", m->plusMinus);
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
            fscanf(fp," %[^,], %[^,], %[^,] %[^,] %d ", m[i].category, m[i].name, m[i].fix, m[i].plusMinus, &m[i].price);
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
        fprintf(fp,"%s %s %s %s %d\n", m[i].category, m[i].name, m[i].fix, m[i].plusMinus, m[i].price);
    }
    fclose(fp);
    printf("저장됨!\n");
}

int main(void){
    moneybook mlist[256];
    int index = 0;
    int count = 0;
    int menu;
    count = loadData(mlist);
    index = count;
    while(1){
        menu = selectMenu();
        if(menu == 0) break;
        if(menu == 1 || menu == 3 || menu == 4)
            if(count == 0) continue;
        if(menu == 1) listBook(mlist, count);
        else if(menu == 2){
            count += createBook(&mlist[index++]);
        }
        else if(menu == 3){
            int no = selectDataNo(mlist, index);
            if(no == 0){
                printf("취소됨!\n");
                continue;
            }
            int isupd = updateBook(&mlist[no-1]);
            if(isupd == 1) printf("=> 수정성공!\n");
        }
        else if(menu == 4){
            int no = selectDataNo(mlist, count);
            if (no == 0){
                printf("=> 취소됨!\n");
                continue;
            }
            int deleteok;
            printf("정말로 삭제하시겠습니까?(삭제 : 1) ");
            scanf("%d",&deleteok);
            if(deleteok == 1){
                if(deleteBook(&mlist[no-1])){
                    printf("=> 삭제됨!\n");
                }
            }
        }
        else if(menu == 5) saveData(mlist, count);
        else if(menu == 6) searchBook(mlist, count);
        else if(menu == 7) searchCategory(mlist, count);
        else if(menu == 8) searchFix(mlist, count);
        else if(menu == 9) searchPlusMinus(mlist, count);
    }
    printf("종료됨!\n");
    return 0;
}