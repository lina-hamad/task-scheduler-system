// lina hamad    1231412   sec:3
/*this system contains a set of tasks with its details and we have a menu that allows the system to add tasks and 
delete tasks (acoording to the tree key) , search for a task by its name and if the tree is structured by name it uses binary search
but if its by id or date or duration it searches manually like a linked list 
also this system allows users to perform a specific tasks according to the tree key and shows the unperformed and performed tasks 
finally it prints the tree details

 ** Note : if delet and performed must be accessed y id only we can restructure the tree by id and then delete oe perform 
 but it was not mentioned int the project pdf so i prefered to make it according to the tree key and it also take less time complexity 
 than restructring then pweforming and deleting .*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node *TNode;
enum {BYID=1, BYNAME, BYDATE, BYDURATION};
unsigned int TreeType = BYID; // Default tree type is by ID

struct node {
    int ID;
    char name[100];
    char date [15];
    double duration;
    int performed ;
    struct node *left;
    struct node *right;
};
// the bellow 2 functions are to convert the date from string to int and compare it by making it in the form YYYYMMDD to sort it easily
void parseDate(char* dateStr, int* day, int* month, int* year) {
    sscanf(dateStr, "%d/%d/%d", day, month, year);
}
int dateToInt(char* dateStr) {
    int day, month, year;
    parseDate(dateStr, &day, &month, &year);
    return year * 10000 + month * 100 + day;
}
TNode makeEmpty(TNode T){
    if (T != NULL){
        T->left = makeEmpty(T->left);
        T->right = makeEmpty(T->right);
        free(T);
    }
} 
TNode findMin(TNode T){
    if (T->left != NULL){
        while(T->left != NULL){
            T = T->left;
        }
    }
    return T;
}
TNode findMax(TNode T){
    if (T->right != NULL){
        while(T->right != NULL){
            T = T->right;
        }
    }
    return T;
}
TNode insert(int ID , char name[100],char date[15],double duration, TNode T){
    if (T == NULL){
        T =(struct node*)malloc(sizeof(struct node));
        if (T == NULL){
            printf("Out of space\n");
            return NULL;
        }
        T->ID = ID;
        strcpy(T->name, name);
        strcpy(T->date, date);
        T->duration = duration;
        T->performed = 0;
        T->left = T->right = NULL;
    } else if (ID < T->ID){
        T->left = insert(ID, name,date,duration, T->left);
    } else if (ID > T->ID){
        T->right = insert(ID, name,date,duration, T->right);
    } 
    return T;
}
TNode insert_by_ID(int ID , char name[100],char date[15],double duration,int performed, TNode T){
    if (T == NULL){
        T =(struct node*)malloc(sizeof(struct node));
        if (T == NULL){
            printf("Out of space\n");
            return NULL;
        }
        T->ID = ID;
        strcpy(T->name, name);
        strcpy(T->date, date);
        T->duration = duration;
        T->performed = performed;
        T->left = T->right = NULL;
    } else if (ID < T->ID){
        T->left = insert_by_ID(ID, name,date,duration,performed, T->left);
    } else if (ID > T->ID){
        T->right = insert_by_ID(ID, name,date,duration,performed, T->right);
    } 
    return T;
}
TNode insert_by_name(int ID , char name[100],char date[15],double duration,int performed, TNode T){
    if (T == NULL){
        T =(struct node*)malloc(sizeof(struct node));
        if (T == NULL){
            printf("Out of space\n");
            return NULL;
        }
        T->ID = ID;
        strcpy(T->name, name);
        strcpy(T->date, date);
        T->duration = duration;
        T->performed = performed;
        T->left = T->right = NULL;
    } else if (strcmp(name, T->name) < 0){
        T->left = insert_by_name(ID, name,date,duration,performed, T->left);
    } else if (strcmp(name, T->name) > 0){
        T->right = insert_by_name(ID, name,date,duration,performed, T->right);
    } 
    return T;
}
TNode insert_by_date(int ID , char name[100],char date[15],double duration,int performed, TNode T){
    if (T == NULL){
        T =(struct node*)malloc(sizeof(struct node));
        if (T == NULL){
            printf("Out of space\n");
            return NULL;
        }
        T->ID = ID;
        strcpy(T->name, name);
        strcpy(T->date, date);
        T->duration = duration;
        T->performed = performed;
        T->left = T->right = NULL;

    } else {
        int currentDate = dateToInt(date);
        int treeDate = dateToInt(T->date);
        
        if (currentDate < treeDate) {
            T->left = insert_by_date(ID, name, date, duration, performed, T->left);
        } else if (currentDate > treeDate) {
            T->right = insert_by_date(ID, name, date, duration, performed, T->right);
        }
    }
    return T;
}
TNode insert_by_duration(int ID , char name[100],char date[15],double duration,int performed, TNode T){
    if (T == NULL){
        T =(struct node*)malloc(sizeof(struct node));
        if (T == NULL){
            printf("Out of space\n");
            return NULL;
        }
        T->ID = ID;
        strcpy(T->name, name);
        strcpy(T->date, date);
        T->duration = duration;
        T->performed = performed;
        T->left = T->right = NULL;
    } else if (duration < T->duration){
        T->left = insert_by_duration(ID, name,date,duration,performed, T->left);
    } else if (duration > T->duration){
        T->right = insert_by_duration(ID, name,date,duration,performed ,T->right);
    } 
    return T;
}
TNode rebuildTree_By_ID(TNode T ){
    TNode newTree = NULL;
    if (T == NULL) {
        return NULL;
    }
    newTree = rebuildTree_By_ID(T->left);
    newTree = insert_by_ID(T->ID, T->name, T->date, T->duration,T->performed, newTree);
    newTree = rebuildTree_By_ID(T->right);
    return newTree;
}
TNode rebuildTree(TNode T, TNode newTree, int choice) {
    if (T == NULL) {
        return newTree;
    }
    newTree = rebuildTree(T->left, newTree, choice);
    if (choice == 1) {
        newTree = insert_by_ID(T->ID, T->name, T->date, T->duration,T->performed, newTree);
    } else if (choice == 2) {
        newTree = insert_by_name(T->ID, T->name, T->date, T->duration,T->performed, newTree);
    } else if (choice == 3) {
        newTree = insert_by_date(T->ID, T->name, T->date, T->duration,T->performed, newTree);
    } else if (choice == 4) {
        newTree = insert_by_duration(T->ID, T->name, T->date, T->duration,T->performed, newTree);
    }

    newTree = rebuildTree(T->right, newTree, choice);
    return newTree;
}

 TNode restructureTree(TNode T , int choice ){

    TNode newTree = NULL;
    //
    if (T == NULL) {
        return NULL;
    }

    //
   if (choice == 1) {
        newTree = rebuildTree(T,newTree, choice);
        TreeType = BYID; 
    } else if (choice == 2) {
        newTree = rebuildTree(T, newTree, choice);
        TreeType = BYNAME;
    } else if (choice == 3) {
        newTree = rebuildTree(T, newTree, choice);
        TreeType = BYDATE; 
    } else if (choice == 4) {
        newTree = rebuildTree(T, newTree, choice);
        TreeType = BYDURATION; 
    } 
   
    makeEmpty(T);
    return newTree;
}
TNode Load_Tasks_File(TNode T){
    FILE *in = fopen("tasks.txt", "r");
    if (in == NULL){
        printf("Error 404: File not found\n");
        return NULL;
    }
    char sent[300];
    while (fgets(sent, sizeof(sent), in)) {

        char *token;
        char *tmp = sent;

        token = strtok(tmp, "#");
        int ID = atoi(token);
        
        token = strtok(NULL, "#");
        char name[100] = {0};
        strncpy(name, token, sizeof(name) - 1);
        token = strtok(NULL, "#");

        char date[15] = {0};
        strncpy(date, token, sizeof(date) - 1);

        token = strtok(NULL, "#");
        double duration = atof(token);

        T = insert(ID,name,date,duration,T);
        if (T == NULL){
            printf("Memory allocation failed\n");
            fclose(in);
            return NULL;
        }
    }
    fclose(in);
    printf("Tasks loaded successfully :)\n");
    return T;
}
void printTasks(TNode T) {
    if (T != NULL) {
        printTasks(T->left);
        printf("ID: %-4d  Name: %-20s  Date: %-10s  Duration: %5.1f hours performed : %-10s\n", T->ID, T->name, T->date, T->duration, T->performed == 1 ? "Yes" : "No");
        printTasks(T->right);
    }
}
void Add_a_new_Task(TNode T){
    int newID;
    char newName[100];
    char newDate[15];
    double newDuration;

    printf("Enter Task ID: ");
    scanf("%d", &newID);
    getchar();

    printf("Enter Task Name: ");
    gets(newName);

    printf("Enter Task Date (in DD/MM/YYYY form): ");
    gets(newDate);

    printf("Enter Task Duration: ");
    scanf("%lf", &newDuration);

   if (TreeType == BYID) {
        T = insert_by_ID(newID, newName, newDate, newDuration, 0, T);
    } else if (TreeType == BYNAME) {
        T = insert_by_name(newID, newName, newDate, newDuration, 0, T);
    } else if (TreeType == BYDATE) {
        T = insert_by_date(newID, newName, newDate, newDuration,0, T);
    } else if (TreeType == BYDURATION) {
        T = insert_by_duration(newID, newName, newDate, newDuration,0, T);
   } else
    if (T == NULL){
        printf("Memory allocation failed\n");
        return;
    }
    printf("Task added successfully!\n");
}
TNode Delete_a_Task_By_ID(int ID, TNode T){
    if (T == NULL){
        printf("Element not found\n");
        return NULL;
    } else if (ID < T->ID){
        T->left = Delete_a_Task_By_ID(ID, T->left);
    } else if (ID > T->ID){
        T->right = Delete_a_Task_By_ID(ID, T->right);
    } else {
        if (T->left != NULL && T->right != NULL){
            TNode temp = findMin(T->right);
            T->ID = temp->ID;
            strcpy(T->name, temp->name);
            strcpy(T->date, temp->date);
            T->duration = temp->duration;
            T->right = Delete_a_Task_By_ID(temp->ID, T->right);
        } else {
            TNode temp = T;
            if (T->left == NULL){
                T = T->right;
            } else if (T->right == NULL){
                T = T->left;
            }
            free(temp);
        }
    }
    return T;
 }
 TNode Delete_a_Task_By_name(char *name, TNode T){
    if (T == NULL){
        printf("Element not found\n");
        return NULL;
    } else if (strcmp(name, T->name) < 0){
        T->left = Delete_a_Task_By_name(name, T->left);
    } else if (strcmp(name, T->name) > 0){
        T->right = Delete_a_Task_By_name(name, T->right);
    } else {
        if (T->left != NULL && T->right != NULL){
            TNode temp = findMin(T->right);
            T->ID = temp->ID;
            strcpy(T->name, temp->name);
            strcpy(T->date, temp->date);
            T->duration = temp->duration;
            T->right = Delete_a_Task_By_name(temp->name, T->right);
        } else {
            TNode temp = T;
            if (T->left == NULL){
                T = T->right;
            } else if (T->right == NULL){
                T = T->left;
            }
            free(temp);
        }
    }
    return T;
 }
TNode Delete_a_Task_By_date(char *date, TNode T){
    int cdate = dateToInt(date);
    int tdate = dateToInt(T->date);
    if (T == NULL){
        printf("Element not found\n");
        return NULL;
    } else if (cdate < tdate){
        T->left = Delete_a_Task_By_date(date, T->left);
    } else if (cdate > tdate){
        T->right = Delete_a_Task_By_date(date, T->right);
    } else {
        if (T->left != NULL && T->right != NULL){
            TNode temp = findMin(T->right);
            T->ID = temp->ID;
            strcpy(T->name, temp->name);
            strcpy(T->date, temp->date);
            T->duration = temp->duration;
            T->right = Delete_a_Task_By_date(temp->date, T->right);
        } else {
            TNode temp = T;
            if (T->left == NULL){
                T = T->right;
            } else if (T->right == NULL){
                T = T->left;
            }
            free(temp);
        }
    }
    return T;
 }
TNode Delete_a_Task_By_duration(double duration, TNode T){
    if (T == NULL){
        printf("Element not found\n");
        return NULL;
    } else if (duration < T->duration){
        T->left = Delete_a_Task_By_duration(duration, T->left);
    } else if (duration > T->duration){
        T->right = Delete_a_Task_By_duration(duration, T->right);
    } else {
        if (T->left != NULL && T->right != NULL){
            TNode temp = findMin(T->right);
            T->ID = temp->ID;
            strcpy(T->name, temp->name);
            strcpy(T->date, temp->date);
            T->duration = temp->duration;
            T->right = Delete_a_Task_By_duration(temp->duration, T->right);
        } else {
            TNode temp = T;
            if (T->left == NULL){
                T = T->right;
            } else if (T->right == NULL){
                T = T->left;
            }
            free(temp);
        }
    }
    return T;
 }
 TNode Delete_a_Task(TNode T){
    if (TreeType == BYID) {
        printf("Enter Task ID to delete: ");
        int nID;
        scanf("%d", &nID);
        getchar();
        T = Delete_a_Task_By_ID(nID, T);
        if (T == NULL){
            printf("Task not found\n");
            return NULL;

        } else {
            printf("Task deleted successfully\n");
            return T;
        }
        } else if (TreeType == BYNAME) {
            printf("Enter Task Name to delete: ");
            char name[100];
            getchar(); 
            gets(name);
            T = Delete_a_Task_By_name(name, T);
            if (T == NULL){
                printf("Task not found\n");
                return NULL;
            } else {
                printf("Task deleted successfully\n");
                return T;
            }
        } else if (TreeType == BYDATE) {
            printf("Enter Task Date to delete (in DD/MM/YYYY form): ");
            char date[15];
            getchar(); 
            gets(date);
            T = Delete_a_Task_By_date(date, T);
            if (T == NULL){
                printf("Task not found\n");
                return NULL;
            } else {
                printf("Task deleted successfully\n");
                return T;
            }
        } else if (TreeType == BYDURATION)
        {
            printf("Enter Task Duration to delete: ");
            double duration;
            scanf("%lf", &duration);
            T = Delete_a_Task_By_duration(duration, T);
            if (T == NULL){
                printf("Task not found\n");
                return NULL;
            } else {
                printf("Task deleted successfully\n");
                return T;
            }
        } else {
            printf("Invalid tree type\n");
            return NULL;
        }
 }
TNode Search_for_a_Task_by_name_original(char name[100], TNode T){
    if (T == NULL){
        return NULL;
    } 
    if (strcmp(name, T->name) == 0){
        return T;
    } 
    TNode T1 = Search_for_a_Task_by_name_original(name, T->left);
    if (T1 != NULL){
        return T1;
    }
    TNode T2 = Search_for_a_Task_by_name_original(name, T->right);
    if (T2 != NULL){
        return T2;
    }
    free(T1);
    free(T2);
    return NULL;
}
TNode Search_for_a_Task_by_ID(int id, TNode T){
    if (T == NULL){
        return NULL;
    } 
    if (id == T->ID){
        return T;
    } 
    else if (id < T->ID){
        return Search_for_a_Task_by_ID(id, T->left);
    } else {
        return Search_for_a_Task_by_ID(id, T->right);
    }
}
TNode Search_for_a_Task_by_Name(char name[100], TNode T){
    if (T == NULL){
        return NULL;
    } 
    if (strcmp(name, T->name) == 0){
        return T;
    }else if (strcmp(name, T->name) < 0){
        return Search_for_a_Task_by_Name(name, T->left);
    } else {
        return Search_for_a_Task_by_Name(name, T->right);
    } 
}
TNode Search_for_a_Task_by_date(char date[15], TNode T){
    if (T == NULL){
        return NULL;
    } 
    int cdate = dateToInt(date);
    int tdate = dateToInt(T->date);
    if (cdate == tdate){
        return T;
    } else if (cdate < tdate){
        return Search_for_a_Task_by_date(date, T->left);
    } else {
        return Search_for_a_Task_by_date(date, T->right);
    } 
}
TNode Search_for_a_Task_by_duration(double duration, TNode T){
    if (T == NULL){
        return NULL;
    } 
    if (duration == T->duration){
        return T;
    } else if (duration < T->duration){
        return Search_for_a_Task_by_duration(duration, T->left);
    } else {
        return Search_for_a_Task_by_duration(duration, T->right);
    }
}
void Perform_a_Task(TNode T){
    if (TreeType == BYID) {
        printf("Enter Task ID to perform: ");
        int nID;
        scanf("%d", &nID);
        getchar();
        TNode task = Search_for_a_Task_by_ID(nID, T);
        if (task == NULL){
            printf("Task not found\n");
            return;
        }
        task->performed = 1;
        printf("Task %s performed successfully\n", task->name);
    } else if (TreeType == BYNAME) {
        printf("Enter Task Name to perform: ");
        char name[100];
        getchar(); 
        gets(name);
        TNode task = Search_for_a_Task_by_Name(name, T);
        if (task == NULL){
            printf("Task not found\n");
            return;
        }
        task->performed = 1;
        printf("Task %s performed successfully\n", task->name);
    }
    else if (TreeType == BYDATE) {
        printf("Enter Task Date to perform (in DD/MM/YYYY form): ");
        char date[15];
        getchar(); 
        gets(date);
        TNode task = Search_for_a_Task_by_date(date, T);
        if (task == NULL){
            printf("Task not found\n");
            return;
        }
        task->performed = 1;
        printf("Task %s performed successfully\n", task->name);
    } else if (TreeType == BYDURATION) {
        printf("Enter Task Duration to perform: ");
        double duration;
        scanf("%lf", &duration);
        TNode task = Search_for_a_Task_by_duration(duration, T);
        if (task == NULL){
            printf("Task not found\n");
            return;
        }
        task->performed = 1;
        printf("Task %s performed successfully\n", task->name);
    } else {
        printf("Invalid tree type\n");
    }
}
void iterateTree_Unperformed(TNode T) {
    TNode tmp = T;
    if (tmp != NULL) {
        iterateTree_Unperformed(tmp->left);
                if (tmp->performed == 0) {
                    printf("ID: %-4d  Name: %-20s  Date: %-10s  Duration: %5.1f hours performed : %-10s\n", T->ID, T->name, T->date, T->duration, T->performed == 1 ? "Yes" : "No");
                }
                iterateTree_Unperformed(tmp->right);
            }
}
void iterateTree_performed(TNode T) {
    TNode tmp = T;
    if (tmp != NULL) {
        iterateTree_performed(tmp->left);
                if (tmp->performed == 1) {
                    printf("ID: %-4d  Name: %-20s  Date: %-10s  Duration: %5.1f hours performed : %-10s\n", T->ID, T->name, T->date, T->duration, T->performed == 1 ? "Yes" : "No");
                }
                iterateTree_performed(tmp->right);
            }
}
TNode View_the_Unperformed_Tasks( TNode T){
    int tmp = TreeType;
    if (TreeType != BYNAME) {
        T = restructureTree(T, BYNAME); 
    }
    iterateTree_Unperformed(T);
    if (TreeType != tmp) {
        T = restructureTree(T, tmp); 
    }   
    return T;
    
}
TNode View_the_Performed_Tasks(TNode T) {
    int tmp = TreeType;
    if (TreeType != BYID) {
        T = restructureTree(T, BYID); 
    }
    iterateTree_performed(T);  
    if (TreeType != tmp) {
        T = restructureTree(T, tmp); 
    }    
    return T;
}

int Tree_Height(TNode T){
    if (T == NULL){
        return -1;
    } else {
        int leftHeight = Tree_Height(T->left);
        int rightHeight = Tree_Height(T->right);
        if(leftHeight > rightHeight){
            return leftHeight + 1;
        } else {
            return rightHeight + 1;
        }
    }
}
int Tree_Size(TNode T){
    if (T == NULL){
        return 0;
    } else {
        return 1 + Tree_Size(T->left) + Tree_Size(T->right);
    }
}
int Tree_Leaf_Count(TNode T){
    if (T == NULL){
        return 0;
    } else if (T->left == NULL && T->right == NULL){
        return 1;
    } else {
        return Tree_Leaf_Count(T->left) + Tree_Leaf_Count(T->right);
    }
}
int number_of_internal_nodes(TNode T){
    if (T == NULL || (T->left == NULL && T->right == NULL)){
        return 0;
    } else {
        return 1 + number_of_internal_nodes(T->left) + number_of_internal_nodes(T->right);
    }
}
void View_the_tasks_BST_info(TNode T){
    printf("Tree Height: %d\n", Tree_Height(T));
    printf("Tree Size: %d\n", Tree_Size(T));
    printf("Number of Leaf Nodes: %d\n", Tree_Leaf_Count(T));
    printf("Number of Internal Nodes: %d\n", number_of_internal_nodes(T));
}

int main() {
    TNode sys = NULL; 
    char searchName[100];
    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Load Tasks File\n");
        printf("2. Add a New Task\n");
        printf("3. Delete a Task\n");
        printf("4. Search for a Task by Name\n");
        printf("5. Perform a Task \n");
        printf("6. View Unperformed Tasks\n");
        printf("7. view Performed Tasks\n");
        printf("8. Restructure Tree\n");
        printf("9. View Tasks BST Info\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                sys = Load_Tasks_File(sys);
                break;
            case 2:
                Add_a_new_Task(sys);
                break;
            case 3:
                sys = Delete_a_Task(sys);
                break;
            case 4:
                printf("Enter Task Name: ");
                getchar(); 
                gets(searchName);
                TNode foundTask = NULL;
                if (TreeType == BYNAME) {
                    foundTask = Search_for_a_Task_by_Name(searchName, sys);
                }else {
                    foundTask = Search_for_a_Task_by_name_original(searchName, sys); 
                }
                if(foundTask != NULL) {
                    printf("\nTask Found:\n");
                    printf("ID: %-4d  Name: %-20s  Date: %-10s  Duration: %5.1f hours performed : %-10s\n", foundTask->ID, foundTask->name, foundTask->date, foundTask->duration, foundTask->performed == 1 ? "Yes" : "No");
                } else {
                    printf("Task not found.\n");
                }
                break;
            
            case 5:
                Perform_a_Task(sys);
                break;
            case 6:
                printf("Unperformed Tasks:\n");
               sys = View_the_Unperformed_Tasks(sys);
                break;
            case 7:
                printf("Performed Tasks:\n");
                sys = View_the_Performed_Tasks(sys);
                break;
            case 8:
                printf("Restructuring Tree...\n");
                int choice;
                printf("Choose restructuring method:\n1. By ID\n2. By Name\n3. By Date\n4. By Duration\n");
                scanf("%d", &choice);
                sys = restructureTree(sys, choice);
                printTasks(sys); 
                printf("Tree restructured successfully!\n");
                break;
            case 9:
                printf("Tasks BST Info:\n");
                View_the_tasks_BST_info(sys);
                break;
            case 10:
                printf("Exiting the system\n ");
                makeEmpty(sys); 
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
                break;
            
        }
    } while (choice != 10);
    return 0;
}
