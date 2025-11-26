#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 50

typedef struct Date {
    int day, month, year;
} Date;

typedef struct Book {
    int bookId, publishYear, quantity;
    char title[50];
    char author[50];
} Book;

typedef struct Borrow {
    int borrowId;
    char borrowName[50];
    int status;
    int bookId;
    Date borrowDate;
    Date borrowReturn;
} Borrow;

int isEmptyString(char s[]){
    return (s[0] == '\0');
}

void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int inputIntRange(int min, int max){
    int n;
    while(1){
        if(scanf("%d", &n) != 1){
            printf("nhap sai !, nhap lai : ");
            clearBuffer();
            continue;
        }
        if(getchar() != '\n'){
            clearBuffer();
            printf("nhap sai !, nhap lai : ");
            continue;
        }
        if(n < min || n > max){
            printf("nhap sai !, nhap lai : ");
            continue;
        }
        return n;
    }
}

int isLeapYear(int y){
    return ( (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0) );
}

int validDate(Date d){
    if(d.year < 1900) return 0;
    if(d.month < 1 || d.month > 12) return 0;
    if(d.day < 1) return 0;
    int mdays;
    if(d.month == 1 || d.month == 3 || d.month == 5 || d.month == 7 || d.month == 8 || d.month == 10 || d.month == 12)
        mdays = 31;
    else if(d.month == 4 || d.month == 6 || d.month == 9 || d.month == 11)
        mdays = 30;
    else
        mdays = isLeapYear(d.year) ? 29 : 28;
    if(d.day > mdays) return 0;
    return 1;
}

int compareDate(Date a, Date b){
    if(a.year != b.year) return (a.year > b.year) ? 1 : -1;
    if(a.month != b.month) return (a.month > b.month) ? 1 : -1;
    if(a.day != b.day) return (a.day > b.day) ? 1 : -1;
    return 0;
}

void showBook(Book book){
    printf("\nId: %d\nTen sach: %s\nTac gia: %s\nNam xuat ban: %d\nSo luong sach: %d\n",
           book.bookId, book.title, book.author, book.publishYear, book.quantity);
}

void delBooksByIndex(int index, int *n, Book books[]){
    for(int i = index; i < *n - 1; i++){
        books[i] = books[i + 1];
    }
    (*n)--;
}

int isDuplicateTitle(char title[], Book books[], int count){
    for(int i = 0; i < count; i++){
        if(strcmp(books[i].title, title) == 0) return 1;
    }
    return 0;
}

void updateBooks(Book books[], int i, Book updateBook){
    updateBook.bookId = books[i].bookId;
    books[i] = updateBook;
}

void addBook(Book *book, Book books[], int i){
   book->bookId = (i == 0 ? 1 : books[i - 1].bookId + 1);
   while(1){
       printf("nhap ten sach : ");
       fgets(book->title, sizeof(book->title), stdin);
       book->title[strcspn(book->title, "\n")] = '\0';
       if(isEmptyString(book->title)){
           printf("Ten sach khong duoc de trong!\n");
           continue;
       }
       if(isDuplicateTitle(book->title, books, i)){
           printf("Ten sach bi trung, nhap lai!\n");
           continue;
       }
       break;
   }
   while(1){
       printf("nhap tac gia : ");
       fgets(book->author, sizeof(book->author), stdin);
       book->author[strcspn(book->author, "\n")] = '\0';
       if(isEmptyString(book->author)){
           printf("Ten tac gia khong duoc de trong!\n");
           continue;
       }
       break;
   }
   printf("nhap nam xuat ban : ");
   while(scanf("%d", &book->publishYear) != 1 || book->publishYear < 1900){
       printf("nhap sai !, nhap lai : ");
       clearBuffer();
   }
   clearBuffer();
   printf("nhap so luong : ");
   while(scanf("%d", &book->quantity) != 1 || book->quantity < 0 || book->quantity > MAX){
       printf("nhap sai !, nhap lai : ");
       clearBuffer();
   }
   clearBuffer();
}

void inputListBook(int n, Book books[]){
    for(int i = 0; i < n; i++){
        printf("\nnhap thong tin sach thu %d\n", i + 1);
        addBook(&books[i], books, i);
    }
}

void searchBooks(int n, Book books[], char titleSearch[]){
    int found = 0;
    for(int i = 0; i < n; i++){
        if(strstr(books[i].title, titleSearch) != NULL ){
            showBook(books[i]);
            found = 1;
        }
    }
    if(!found) printf("khong tim thay !\n");
}

void menu(){
    printf("\n=================Menu=================\n");
    printf("1.them moi sach\n");
    printf("2.cap nhat thong tin sach\n");
    printf("3.hien thi danh sach sach\n");
    printf("4.xoa thong tin sach\n");
    printf("5.tim kiem sach\n");
    printf("6.them moi phieu muon\n");
    printf("7.tra sach\n");
    printf("8.hien thi danh sach phieu muon\n");
    printf("0.thoat menu !\n");
    printf("======================================\n");
}

int findBookIndexById(Book books[], int n, int id){
    for(int i = 0; i < n; i++){
        if(books[i].bookId == id) return i;
    }
    return -1;
}

int findBorrowIndexById(Borrow borrows[], int m, int id){
    for(int i = 0; i < m; i++){
        if(borrows[i].borrowId == id) return i;
    }
    return -1;
}

int isBookCurrentlyBorrowed(Borrow borrows[], int m, int bookId){
    for(int i = 0; i < m; i++){
        if(borrows[i].bookId == bookId && borrows[i].status == 1) return 1;
    }
    return 0;
}

void showBorrow(Borrow b){
    printf("\nBorrowId: %d\nNguoi muon: %s\nBookId: %d\nNgay muon: %02d/%02d/%04d\n",
           b.borrowId, b.borrowName, b.bookId, b.borrowDate.day, b.borrowDate.month, b.borrowDate.year);
    if(b.status == 1){
        printf("Trang thai: dang muon\n");
    } else {
        printf("Trang thai: da tra\n");
        printf("Ngay tra: %02d/%02d/%04d\n", b.borrowReturn.day, b.borrowReturn.month, b.borrowReturn.year);
    }
}

void showBooksPaginated(Book books[], int n){
    if(n == 0){
        printf("Danh sach sach rong!\n");
        return;
    }
    int itemPage = 10;
    int currentPage = 1;
    int maxPage = (n + itemPage - 1) / itemPage;
    while(1){
        int startIndex = (currentPage - 1) * itemPage;
        int endIndex = startIndex + itemPage;
        if(endIndex > n) endIndex = n;
        printf("\n--- Trang %d / %d ---\n", currentPage, maxPage);
        for(int i = startIndex; i < endIndex; i++){
            showBook(books[i]);
        }
        int choicePage;
        printf("Ban dang o trang: %d\n", currentPage);
        printf("Chon chuc nang (1 - trang truoc, 2 - thoat, 3 - trang tiep): ");
        choicePage = inputIntRange(1,3);
        if(choicePage == 1){
            if(currentPage > 1) currentPage--;
            else printf("Ban dang o trang dau tien\n");
        } else if(choicePage == 2){
            break;
        } else if(choicePage == 3){
            if(currentPage < maxPage) currentPage++;
            else printf("Ban dang o trang cuoi cung\n");
        }
    }
}

void showBorrowsPaginated(Borrow borrows[], int m){
    if(m == 0){
        printf("Danh sach phieu muon trong\n");
        return;
    }
    int itemPage = 10;
    int currentPage = 1;
    int maxPage = (m + itemPage - 1) / itemPage;
    while(1){
        int startIndex = (currentPage - 1) * itemPage;
        int endIndex = startIndex + itemPage;
        if(endIndex > m) endIndex = m;
        printf("\n--- Trang %d / %d ---\n", currentPage, maxPage);
        for(int i = startIndex; i < endIndex; i++){
            showBorrow(borrows[i]);
        }
        int choicePage;
        printf("Chon chuc nang (1 - trang truoc, 2 - thoat, 3 - trang tiep): ");
        choicePage = inputIntRange(1,3);
        if(choicePage == 1){
            if(currentPage > 1) currentPage--;
            else printf("Ban dang o trang dau tien\n");
        } else if(choicePage == 2){
            break;
        } else if(choicePage == 3){
            if(currentPage < maxPage) currentPage++;
            else printf("Ban dang o trang cuoi cung\n");
        }
    }
}

void addBorrow(Borrow *b, Borrow borrows[], int m, Book books[], int n){
    b->borrowId = (m == 0 ? 1 : borrows[m - 1].borrowId + 1);
    while(1){
        printf("nhap id sach muon: ");
        int tmp;
        if(scanf("%d", &tmp) != 1){
            printf("nhap sai, nhap lai\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        int idx = findBookIndexById(books, n, tmp);
        if(idx == -1){
            printf("khong ton tai sach, nhap lai\n");
            continue;
        }
        if(books[idx].quantity <= 0){
            printf("Sach khong con trong kho\n");
            continue;
        }
        b->bookId = tmp;
        break;
    }
    while(1){
        printf("nhap ten nguoi muon: ");
        fgets(b->borrowName, sizeof(b->borrowName), stdin);
        b->borrowName[strcspn(b->borrowName, "\n")] = '\null';
        if(isEmptyString(b->borrowName)){
            printf("Ten nguoi muon khong duoc de trong\n");
            continue;
        }
        break;
    }
    Date d;
    while(1){
        printf("nhap ngay muon (dd mm yyyy): ");
        if(scanf("%d %d %d", &d.day, &d.month, &d.year) != 3){
            printf("nhap sai, nhap lai\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        if(!validDate(d)){
            printf("Ngay khong hop le, nhap lai\n");
            continue;
        }
        b->borrowDate = d;
        break;
    }
    b->status = 1;
    b->borrowReturn.day = 0;
    b->borrowReturn.month = 0;
    b->borrowReturn.year = 0;
    int bookIdx = findBookIndexById(books, n, b->bookId);
    if(bookIdx != -1) books[bookIdx].quantity -= 1;
}

void returnBook(Borrow borrows[], int m, Book books[], int n){
    if(m == 0){
        printf("Danh sach phieu muon trong\n");
        return;
    }
    printf("nhap id phieu muon: ");
    int id;
    if(scanf("%d", &id) != 1){
        printf("nhap sai\n");
        clearBuffer();
        return;
    }
    clearBuffer();
    int idx = findBorrowIndexById(borrows, m, id);
    if(idx == -1){
        printf("Khong tim thay phieu muon\n");
        return;
    }
    if(borrows[idx].status == 0){
        printf("Phieu da duoc tra truoc do\n");
        return;
    }
    Date rt;
    while(1){
        printf("nhap ngay tra (dd mm yyyy): ");
        if(scanf("%d %d %d", &rt.day, &rt.month, &rt.year) != 3){
            printf("nhap sai, nhap lai\n");
            clearBuffer();
            continue;
        }
        clearBuffer();
        if(!validDate(rt)){
            printf("Ngay khong hop le, nhap lai\n");
            continue;
        }
        if(compareDate(rt, borrows[idx].borrowDate) < 0){
            printf("Ngay tra phai sau hoac bang ngay muon\n");
            continue;
        }
        break;
    }
    borrows[idx].borrowReturn = rt;
    borrows[idx].status = 0;
    int bookIdx = findBookIndexById(books, n, borrows[idx].bookId);
    if(bookIdx != -1)
        books[bookIdx].quantity += 1;
    printf("Tra sach thanh cong\n");
}

int main(){
    Book books[MAX];
    Borrow borrows[MAX];
    int n = 0, m = 0;
    int choice;
    while(1){
        menu();
        printf("nhap lua chon :");
        choice = inputIntRange(0,8);
        switch(choice){
            case 1:
                {
                    printf("nhap so luong sach muon them : ");
                    int k = inputIntRange(1, MAX - n);
                    inputListBook(k, books + n);
                    int start = n;
                    for(int i = start; i < start + k; i++){
                        if(i == 0) books[i].bookId = 1;
                        else books[i].bookId = books[i - 1].bookId + 1;
                    }
                    n += k;
                    for(int i = n - k; i < n; i++) showBook(books[i]);
                }
                break;
            case 2:
                {
                    if(n == 0){
                        printf("Danh sach sach rong\n");
                        break;
                    }
                    int idUpdate;
                    printf("nhap vao id sach can cap nhat : ");
                    if(scanf("%d", &idUpdate) != 1){
                        printf("nhap sai\n");
                        clearBuffer();
                        break;
                    }
                    clearBuffer();
                    int foundIndex = findBookIndexById(books, n, idUpdate);
                    if(foundIndex != -1){
                        Book updateBook;
                        addBook(&updateBook, books, n);
                        updateBooks(books, foundIndex, updateBook);
                        printf("cap nhat thanh cong !\n");
                    } else {
                        printf("khong tim thay !\n");
                    }
                }
                break;
            case 3:
                showBooksPaginated(books, n);
                break;
            case 4:
                {
                    if(n == 0){
                        printf("Danh sach sach rong\n");
                        break;
                    }
                    int idDel;
                    printf("nhap id sach muon xoa : ");
                    if(scanf("%d", &idDel) != 1){
                        printf("nhap sai\n");
                        clearBuffer();
                        break;
                    }
                    clearBuffer();
                    int idx = findBookIndexById(books, n, idDel);
                    if(idx == -1){
                        printf("Khong tim thay!\n");
                    } else {
                        if(isBookCurrentlyBorrowed(borrows, m, idDel)){
                            printf("Khong the xoa sach vi co nguoi dang muon\n");
                        } else {
                            delBooksByIndex(idx, &n, books);
                            printf("Xoa thanh cong!\n");
                        }
                    }
                }
                break;
            case 5:
                {
                    if(n == 0){
                        printf("Danh sach sach rong\n");
                        break;
                    }
                    char titleSearch[100];
                    while(1){
                        printf("nhap vao ten can tim : ");
                        fgets(titleSearch, sizeof(titleSearch), stdin);
                        titleSearch[strcspn(titleSearch, "\n")] = '\0';
                        if(isEmptyString(titleSearch)){
                            printf("Ten tim kiem khong duoc de trong!\n");
                            continue;
                        }
                        break;
                    }
                    searchBooks(n, books, titleSearch);
                }
                break;
            case 6:
                {
                    if(n == 0){
                        printf("Khong co sach trong he thong\n");
                        break;
                    }
                    if(m >= MAX){
                        printf("Khong the them phieu muon, da dat toi gioi han\n");
                        break;
                    }
                    Borrow b;
                    addBorrow(&b, borrows, m, books, n);
                    borrows[m++] = b;
                    printf("Them phieu muon thanh cong\n");
                }
                break;
            case 7:
                {
                    returnBook(borrows, m, books, n);
                }
                break;
            case 8:
                showBorrowsPaginated(borrows, m);
                break;
            case 0:
                printf("da thoat !\n");
                exit(0);
                break;
            default:
                printf("nhap sai!, nhap lai\n");
        }
    }
    return 0;
}
