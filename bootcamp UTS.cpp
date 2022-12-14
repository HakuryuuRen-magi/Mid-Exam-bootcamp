#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#ifdef _WIN32
   	#define PLATFORM_NAME "Windows OS"
#elif __APPLE__
	#define PLATFORM_NAME "Mac OS"	
#elif __linux__
    #define PLATFORM_NAME "Linux OS"
#endif
#include <ctype.h>
#include <conio.h>
#define SIZE 9999
int banyakdata=0;
char hapusdish[255];
int valid=0;
int present=0;
int stock=0;
int harga=0;
char udhorder[255][255];
int u=0;
struct DataItem {
	char nama[255];
	char menu[255][255];
	int banyakpermenu[255];
	int harga;
	int banyakmenu;
    int key;
};
int ada=0;  
struct DataItem* hashArray[SIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
   return key % SIZE;
}

struct DataItem *search(int key) {
   int hashIndex = hashCode(key);  
	
   while(hashArray[hashIndex] != NULL) {
	
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]; 
			
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SIZE;
   }        
	
   return NULL;        
}

void insert(int key, char nama[]) {

   struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   strcpy(item->nama, nama);
   item->key = key;

   int hashIndex = hashCode(key);

   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {

      ++hashIndex;
		

      hashIndex %= SIZE;
   }
	
   hashArray[hashIndex] = item;
}

void del(int value)
{
    int key = value % SIZE;
    hashArray[key] = NULL;
}

void display() {
   int i = 0;
	printf("Customer\'s List\n");
	int index=0;
   for(i = 0; i<SIZE; i++) {
	
      if(hashArray[i] != NULL){
       	printf("%d. %s\n", hashArray[i]->key, hashArray[i]->nama);

	  }  
   }
   printf("Press enter to continue...");
}
struct Node {
  char data[255];
  int price;
  int quantity;
  struct Node* next;
  struct Node* prev;
};
struct Node* head = NULL;
void insertFront(struct Node** head, char data[], int price, int quantity) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  strcpy(newNode->data, data);
  newNode->price=price;
  newNode->quantity=quantity;
  newNode->next = (*head);
  newNode->prev = NULL;

  if ((*head) != NULL)
    (*head)->prev = newNode;
  (*head) = newNode;
}

void insertAfter(struct Node* prev_node, char data[], int price, int quantity) {
  if (prev_node == NULL) {
    printf("previous node cannot be null");
    return;
  }
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  strcpy(newNode->data, data);
  newNode->next = prev_node->next;
  newNode->price=price;
  newNode->quantity=quantity;
  prev_node->next = newNode;
  newNode->prev = prev_node;

  if (newNode->next != NULL)
    newNode->next->prev = newNode;
}

void insertEnd(struct Node** head, char data[], int price, int quantity) {
  struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

  strcpy(newNode->data, data);
  newNode->price=price;
  newNode->quantity=quantity;
  newNode->next = NULL;
  struct Node* temp = *head;

  if (*head == NULL) {
    newNode->prev = NULL;
    *head = newNode;
    return;
  }

  while (temp->next != NULL)
    temp = temp->next;

  temp->next = newNode;
  newNode->prev = temp;
}


  void deleteNode(struct Node** head, struct Node* del_node) {
  	while(del_node!=NULL){
  		int ada=1;
  		int leng=strlen(hapusdish);
  		for(int i=0; i<leng; i++){
  			if(hapusdish[i]!=del_node->data[i]) ada=0;
		}
		if(ada==1){
			valid=1;
			  // if head or del is null, deletion is not possible
			  if (*head == NULL || del_node == NULL)
			    return;
			
			  // if del_node is the head node, point the head pointer to the next of del_node
			  if (*head == del_node)
			    *head = del_node->next;
			
			  // if del_node is not at the last node, point the prev of node next to del_node to the previous of del_node
			  if (del_node->next != NULL)
			    del_node->next->prev = del_node->prev;
			
			  // if del_node is not the first node, point the next of the previous node to the next node of del_node
			  if (del_node->prev != NULL)
			    del_node->prev->next = del_node->next;
			
			  // free the memory of del_node
			  free(del_node);
			  banyakdata--;
			  break;
		}
		del_node=del_node->next;
	}

}
void search(struct Node* node, char data[], int banyak) {
  struct Node* last;
  while (node != NULL) {
    int leng=strlen(node->data);
    int ada=1;
    for(int i=0; i<leng; i++){
    	if(node->data[i]!=data[i]) ada=0;
	}
	if(ada==1){
		present=1;
		if(banyak<=node->quantity) stock=1;
		if(present==1&&stock==1){
			harga=node->price*banyak;
			node->quantity-=banyak;
		}
		break;
	}
    last = node;
    node = node->next;
  }
}

void displayList(struct Node* node) {
  struct Node* last;
  printf("Bude\'s Menu\n========================================================\n| No. |     Name              |  Quantity  |   Price   |\n========================================================\n");
  int counter=1;
  while (node != NULL) {
    printf("| %-3d |     %-18s|  %-10d|  %-9d|\n", counter, node->data, node->quantity, node->price);
    last = node;
    node = node->next;
    counter++;
  }
  printf("========================================================\n");
}
char command1[255];
void menu1(){
	int lower=1;
	char dish[255];
	int price;
	int quantity;
	do{
		lower=1;
		printf("Insert the name of the dish [Lowercase letters]: ");
		getchar();
		scanf("%[^\n]", dish);
		int leng=strlen(dish);
		if(leng<1) lower=0;
		for(int i=0; i<leng; i++){
			if(dish[i]!=' '){
				if(dish[i]<97||dish[i]>122) lower=0;
			}
		}
	}while(lower==0);
	do{
		printf("Insert the price of the dish [1000..50000]: ");
		scanf("%d", &price);
	}while(price<1000||price>50000);
	do{
		printf("Insert the quantity of the dish [1..999]: ");
		scanf("%d", &quantity);
	}while(quantity<1||quantity>999);
	printf("\nThe dish has been added!\nPress enter to continue...");
	getch();
	insertEnd(&head, dish, price, quantity);
	banyakdata++;
	system("cls");
}
void menu2(){
	system("cls");
	if (banyakdata>0){
		displayList(head);
		valid=0;
		do{
			printf("Insert dish's name to be deleted: ");
			getchar();
			scanf("%[^\n]", hapusdish);
			deleteNode(&head, head);
		}while(valid==0);
		printf("Deletion success\nPress enter to continue...");
		getch();
		system("cls");
	}
	else {
		printf("Add dish!\nPress enter to continue...");
		getch();
	}
	system("cls");
}
void menu3(){
	int space=0;
	char nama[255];
	do{
		space=0;
		printf("Insert the customer's name [Without space]: ");
		getchar();
		scanf("%[^\n]", nama);
		int leng=strlen(nama);
		for(int i=0; i<leng; i++){
			if(nama[i]==' '||tolower(nama[i])<97||tolower(nama[i])>122) space=1;
		}
	}while(space==1);
	printf("Customer has been added!\nPress enter to continue...");
	strcpy(udhorder[u], nama);
	u++;
	int sum=0;
	int leng=strlen(nama);
	for(int i=0; i<leng; i++){
		sum+=nama[i];
	}
	insert(sum, nama);
	getch();
	system("cls");
}
void menu4(){
	char searched[255];
	int ada1=1;
	printf("Insert the customer name to be searched: ");
	scanf("%s", searched);
	for(int i = 0; i<SIZE; i++) {
		ada1=0;
      if(hashArray[i] != NULL){
      	ada1=1;
      	int leng=strlen(hashArray[i]->nama);
       	for(int z=0; z<leng; z++){
       		if(searched[z]!=hashArray[i]->nama[z]) ada1=0;
			 		
		}
		
	  } 
	  if(ada1==1) break; 
   }
   if(ada1==1) printf("%s is present.\n", searched);
   else printf("%s is not present.\n", searched);
   printf("Press enter to continue...");
   getch();
   system("cls");
}
void menu5(){
	display();
	getch();
	system("cls");
}
void menu6(){
	char menu1[255][255];
	int harga1[255];
	char order[255];
	int banyakpermenu[255];
	int quantity=0;
	int valid=1;
	int key;
	do{
		valid=1;
		printf("Insert the customer name: ");
		scanf("%s", order);
		for(int i = 0; i<SIZE; i++) {
			valid=0;
	      	if(hashArray[i] != NULL){
	      	valid=1;
	      	int leng=strlen(hashArray[i]->nama);
	       	for(int z=0; z<leng; z++){
	       		if(order[z]!=hashArray[i]->nama[z]) valid=0;		 		
			}
	  	} 
	  if(valid==1) {
	  	int key=i;
	  	break;
	  }
   		}
   		if(valid==0) printf("There is no such name as %s.\n", order);
	}while(valid==0);
	do{
		printf("Insert the amount of dish: ");
		scanf("%d", &quantity);
	}while(quantity<1);
	int leng=strlen(order);
	int sum=0;
	for(int i=0; i<leng; i++){
		sum+=order[i];
	}
	hashArray[sum]->banyakmenu=quantity;
	
	for(int i=0; i<quantity; i++){
		char menu2[255]="";
		do{
			int harga=0;
			present=0;
			stock=0;
			printf("[%d] Insert the dish name and quantity: ", i+1);
			getchar();
			scanf("%[^x]x", menu1[i]);
		
			scanf("%d", &banyakpermenu[i]);
			int lang=strlen(menu1[i]);
			for(int z=0; z<lang-1; z++){
				menu2[z]=menu1[i][z];
			}
			search(head, menu2, banyakpermenu[i]);
			if(stock==0) printf("%s is less than %d\n", menu1[i], banyakpermenu[i]);
			if(present==0) printf("%s is not in menu\n", menu1[i]);
		}while (present==0||stock==0);
		strcpy(hashArray[sum]->menu[i], menu2);
		hashArray[sum]->banyakpermenu[i]=banyakpermenu[i];
		hashArray[sum]->harga+=harga;
	}
	printf("Press enter to continue...");
	getch();
	system("cls");
}
void menu7(){
	char bayar[255];
	printf("Insert customer name: ");
	scanf("%s", bayar);
	valid =1;
	for(int i = 0; i<SIZE; i++) {
			valid=0;
	      	if(hashArray[i] != NULL){
	      	valid=1;
	      	int leng=strlen(hashArray[i]->nama);
	       	for(int z=0; z<leng; z++){
	       		if(bayar[z]!=hashArray[i]->nama[z]) valid=0;		 		
			}
	  	} 
	  if(valid==1) {
	  	int key=i;
	  	break;
	  }
	}
	int sum=0;
	int leng= strlen(bayar);
	for(int i=0; i<leng; i++){
		sum+=bayar[i];
	}
	if(valid==1) {
		printf("%s\n", hashArray[sum]->nama);
		for(int i=0; i<hashArray[sum]->banyakmenu; i++){
			printf("[%d] %s x%d\n", i+1, hashArray[sum]->menu[i], hashArray[sum]->banyakpermenu[i]);
		}
	}
	printf("Total order: %d\nPress enter to continue...", hashArray[sum]->harga);
	getch();
	system("cls");
	del(sum);
}
int main(){
	char command;
	time_t t;  
	time(&t);	
	do{
		printf("System: %s\n%s\n1. Add Dish\n2. Remove Dish\n3. Add Customer\n4. Search Customer\n5. View Warteg\n6. Order\n7. Payment\n8. Exit Warteg\n>> ", PLATFORM_NAME, ctime(&t));	
		scanf("%s", command1);
		system("cls");
		if(strlen(command1)==1&&command1[0]>=48&&command1[0]<=57) command=command1[0];
		if(command=='1') menu1();
		else if(command=='2') menu2();
		else if(command=='3') menu3();
		else if(command=='5') menu5();
		else if(command=='4') menu4();
		else if(command=='6') menu6();
		else if(command=='7') menu7();
	}while(command!='8');
	
}
