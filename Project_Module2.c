#include <stdio.h>

struct Student {
    int id;
    char name[50];
    char gmail[50];
    char phone[20];
	
};
//void role(){
//	int chooseRole;
//do{
//	printf("***Student Management System Using C***\n");
//	printf("\t   CHOOSE YOUR ROLE\n");
//	printf("\t======================\n");
//	printf("\t[1] Admin.\n");
//	printf("\t[2] Student.\n");
//	printf("\t[3] Teacher.\n");
//	printf("\t[0] Exit the Program.\n");
//	printf("\t======================\n");
//	printf("Enter The Choice: ");
//	scanf("%d",&chooseRole);
//}while(chooseRole==0);
//}

void readFile(struct Student students[], int *n) {
    FILE *file = fopen("studentManagement.bin", "rb");
    if (!file) {
        *n = 0;
        return;
    }
    fread(n, sizeof(int), 1, file);
    fread(students, sizeof(struct Student), *n, file);
    fclose(file);
}

void writeFile(struct Student students[], int n) {
    FILE *file = fopen("studentManagement.bin", "wb");
    if (!file) {
        printf("Loi khi mo file.\n");
        return;
    }
    fwrite(&n, sizeof(int), 1, file);
    fwrite(students, sizeof(struct Student), n, file);
    fclose(file);
}

void printStudents(struct Student students[], int n) {
    printf("\n\t\t**** All Students ****\n\n");
    printf("|======|==========================|===========================|===================|===========|\n");
    printf("|  %s  |%15s           |%16s           |%12s       | %s |\n", "ID", "Name", "Gmail","Phone","NO.Course");
    printf("|======|==========================|===========================|===================|===========|\n");
    for (int i = 0; i < n; i++) {
        printf("|%-5d |%-26s|%-27s|%-19s|%-11d|\n", students[i].id, students[i].name, students[i].gmail,students[i].phone,i+1);
    }
}

void addStudent(struct Student students[], int *n) {
    if (*n >= 100) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }
    struct Student newStudent;
    printf("ID: ");
    scanf("%d", &newStudent.id);
    getchar();
    printf("Name: ");
    fgets(newStudent.name, 50, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    printf("Gmail: ");
	fgets(newStudent.gmail, 50, stdin);
    newStudent.gmail[strcspn(newStudent.gmail, "\n")] = 0;
    printf("Phone: ");
	fgets(newStudent.phone, 20, stdin);
    newStudent.phone[strcspn(newStudent.phone, "\n")] = 0;

    students[*n] = newStudent;
    (*n)++;
    writeFile(students, *n);
    printf("Sinh vien da duoc them.\n");
}

void editStudent(struct Student students[], int n) {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            printf("Name: ");
            getchar();
            fgets(students[i].name, 50, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;
            writeFile(students, n);
            printf("Gmail: ");
           
            fgets(students[i].gmail, 50, stdin);
            students[i].gmail[strcspn(students[i].gmail, "\n")] = 0;
            writeFile(students, n);
            printf("Phone: ");
            fgets(students[i].phone, 20, stdin);
            students[i].phone[strcspn(students[i].phone, "\n")] = 0;
            writeFile(students, n);
            printf("Thong tin sinh vien da duoc cap nhat.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}

void deleteStudent(struct Student students[], int *n) {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *n - 1; j++) {
                students[j] = students[j + 1];
            }
            (*n)--;
            writeFile(students, *n);
            printf("Sinh vien da duoc xoa.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}

void searchStudent(struct Student students[], int n) {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (students[i].id == id) {
            printf("\nSinh vien tim thay: \n");
            printf("%-5s%-20s%-10s\n", "ID", "Name", "Gmail");
            printf("%-5d%-20s%-10s\n", students[i].id, students[i].name, students[i].gmail);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID %d.\n", id);
}

void sortStudents(struct Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (students[i].id > students[j].id) {
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    writeFile(students, n);
    printf("Danh sach sinh vien da duoc sap xep.\n");
}

int main() {
    struct Student students[100];
    int n = 0;
    readFile(students, &n);

    int choice;
    
	int chooseRole;
do{
	printf("***Student Management System Using C***\n");
	printf("\t   CHOOSE YOUR ROLE\n");
	printf("\t======================\n");
	printf("\t[1] Admin.\n");
	printf("\t[2] Student.\n");
	printf("\t[3] Teacher.\n");
	printf("\t[0] Exit the Program.\n");
	printf("\t======================\n");
	printf("Enter The Choice: ");
	scanf("%d",&chooseRole);
}while(chooseRole==0);

    if(chooseRole==2){
	do {
        printf("\n\t     STUDENT MENU\n");
        printf("\t======================\n");
        printf("\t1. In danh sach sinh vien\n");
        printf("\t2. Them sinh vien\n");
        printf("\t3. Sua thong tin sinh vien\n");
        printf("\t4. Xoa sinh vien\n");
        printf("\t5. Tim kiem sinh vien\n");
        printf("\t6. Sap xep danh sach sinh vien\n");
        printf("\t7. Thoat\n");
        printf("\t8. Quay lai MENU\n");
       	printf("\t======================\n");
        printf("\tEnter the choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printStudents(students, n);
                break;
            case 2:
                addStudent(students, &n);
                break;
            case 3:
                editStudent(students, n);
                break;
            case 4:
                deleteStudent(students, &n);
                break;
            case 5:
                searchStudent(students, n);
                break;
            case 6:
                sortStudents(students, n);
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            case 8:
                
                break;
                
            default:
                printf("Lua chon khong hop le.\n");
                break;
        }
    } while (choice != 7);
}

    return 0;
}
