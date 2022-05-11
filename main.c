#include <stdio.h>
#include "moneybook.h"

int main(void){
#ifdef DEBUG
    printf("Debug: %s %s %s %d\n", __DATE__, __TIME__, __FILE__, __LINE__);
#endif
    moneybook mlist[256];
    int index = 0;
    int count = 0;
    int menu;
    count = loadData(mlist);
    index = count;
    while(1){
        menu = selectMenu();
        if(menu == 0) break;
        if(menu == 1 || menu ==3 || menu == 4)
            if(count == 0) continue;
        if(menu == 1) listBook(mlist, count);
        else if(menu == 2){
            count += createBook(&mlist[index++]);
            printf("\n=> 추가됨!\n");
        }
        else if(menu == 3){
            int no = selectDataNo(mlist, index);
            if(no == 0){
                printf("\n취소됨!\n");
                continue;
            }
            int isupd = updateBook(&mlist[no-1]);
            if(isupd == 1) printf("\n=> 수정성공!\n");
        }
        else if(menu == 4){
            int no = selectDataNo(mlist, count);
            if (no == 0){
                printf("\n=> 취소됨!\n");
                continue;
            }
            int deleteok;
            printf("\n정말로 삭제하시겠습니까?(삭제 :1) ");
            scanf("%d",&deleteok);
            if(deleteok == 1){
                if(deleteBook(&mlist[no-1])){
                    printf("\n=> 삭제됨!\n");
                }
            }
        }
        else if(menu == 5) saveData(mlist, count);
        else if(menu == 6) searchBook(mlist, count);
        else if(menu == 7) searchCategory(mlist, count);
        else if(menu == 8) searchFix(mlist, count);
        else if(menu == 9) searchPlusMinus(mlist, count);
    }
    printf("\n종료됨!\n");
    return 0;
}
