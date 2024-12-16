#include <stdio.h>
#include <string.h>
#include<ctype.h>
#include<stdlib.h>


//structure for bank using required data items
struct bank {
    char name[100];
    int number;
    int balance;
    struct bank *next;
};

typedef struct bank Bank;

Bank *first=NULL;
Bank *last=NULL;

// Function declarations
void read();
void display();
void balance();
void withdral();
void search();
void deposit();
void update();
void transfer();


// Global variables

//int n = 0;
int acc_num;
int count=0;

// Main function

int main() {

    int choice;

    for(;;) {
        printf("\nBanking System Menu:\n");
        printf("1. Enter Account Details\n");
        printf("2. Display All Accounts\n");
        printf("3. Check Balance\n");
        printf("4. Withdraw Money\n");
        printf("5. Search Account\n");
        printf("6. Deposit Money\n");
        printf("7. Update Account\n");
        printf("8. Transfer Money\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        //switch case used to enter a choice
        switch (choice) {
            case 1:
                read();
                break;
            case 2:
                display();
                break;
            case 3:
                balance();
                break;
           case 4:
                withdral();
                break;
            case 5:
                search();
                break;
            case 6:
                deposit();
                break;
            case 7:
                update();
                break;
            case 8:
                transfer();
            break;
                
            case 9:
                printf("Exiting the program.\n");
                return 0; // Exit the program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

//read function used to read the account holder's details

void read() 
{
    Bank *new=(Bank*)malloc(sizeof(Bank));
    count=count+1;
    
    if(first==NULL)
    {
        printf("Enter the account holder name:\n");
        getchar();
        scanf("%[^\n]s",new->name);
        printf("Enter the account number:\n");
        scanf("%d", &new->number);
        printf("Enter the initial balance:\n");
        scanf("%d", &new->balance);
        
        new->next=NULL;
        first=last=new;
    }
    
    else
    {
        printf("Enter the account holder name:\n");
        getchar();
        scanf("%[^\n]s", new->name);
        printf("Enter the account number:\n");
        scanf("%d", &new->number);
        printf("Enter the initial balance:\n");
        scanf("%d", &new->balance);

        last->next=new;
        last=new;
    }
}

//display function used to display the details of account holders
void display() 
{
    printf("We have %d no of records in the bank:\n",count);
    
    Bank *temp=first;
    
    while(temp!=NULL)
    {
        printf("Account Holder Details:\n");
        printf("Name: %s\n", temp->name);
        printf("Account Number: %d\n", temp->number);
        printf("Balance: %d\n", temp->balance);
        printf("-------------------------------\n");
        temp=temp->next;
    }
}

//balance function used to chek the account balance
void balance() 
{
    printf("Enter the account number to check balance:\n");
    scanf("%d", &acc_num);
    Bank *temp=first;
    while(temp!=NULL) 
    {
        if (acc_num==temp->number) 
        {
            printf("The balance in account %d is: %d\n", temp->number,temp->balance);
            return;
        }
         temp=temp->next;
    }
    printf("Account not found.\n");
}

//withdrawl function used to withdraw money from any account
void withdral() 
{
    int amt;
    
    printf("Enter the account number to withdraw from:\n");
    scanf("%d", &acc_num);
    Bank *temp=first;
    
    while(temp!=NULL)
    {
        if (acc_num==temp->number) 
        {
            printf("Enter the amount to withdraw:\n");
            scanf("%d", &amt);
            if (amt > temp->balance) 
            {
                printf("Insufficient balance.\n");
            } 
            else 
            {
                temp->balance = temp->balance - amt;
                printf("Withdrawal successful. New balance is: %d\n",temp->balance);
            }
            return;
        }
        temp=temp->next;
    }
    
    printf("Account not found.\n");
}

//search function used to search the account is presenyt or not
void search() 
{
    printf("Enter the account number to search:\n");
    scanf("%d", &acc_num);

    Bank *temp=first;
    
    while(temp!=NULL) 
    {
        if (acc_num==temp->number) 
        {
            printf("Account Found!\n");
            printf("Name: %s\n", temp->name);
            printf("Account Number: %d\n",temp->number);
            printf("Balance: %d\n",temp->balance);
            return;
        }
        temp=temp->next;
    }
    
    
    printf("Account not found.\n");
}

//deposit function used to deposit money to any account
void deposit() 
{
    int amount;
    printf("Enter the account number to deposit into:\n");
    scanf("%d", &acc_num);
    Bank*temp=first;
    while (temp!=NULL) 
    {
        

            if (acc_num==temp->number) 
            {
                if(amount>0){
                    printf("Enter the amount to deposit:\n");
                    scanf("%d", &amount);
                    temp->balance += amount;
                    printf("Deposit successful. New balance is: %d\n",temp->balance);
                    return;
                }
                else{
                    printf("You have entered invalid amount");
                }
            }
        
        temp=temp->next;
    }
    
    
    printf("Account not found.\n");
}

//update function to update username of the account
void update() 
{
    char name[100];
    printf("Enter the account number to update:\n");
    scanf("%d", &acc_num);

    Bank*temp=first;

    while (temp!=NULL) 
    {
        if (acc_num==temp->number) 
        {
            printf("Enter the new name:\n");
            getchar();
            scanf("%[^\n]s",name);
            strcpy(temp->name,name);
            
            printf("Name %s updated successfully.\n",temp->name);
            
            return;
            
        }
        temp=temp->next;
    }
    
    printf("Account not found.\n");
}

void transfer(){
    
    int source,destination,credit;
    printf("enter the amount:\n");
    scanf("%d",&credit);

    printf("Enter the Account number you want to transfer the money:\n");
    scanf("%d",&destination);

    printf("Enter the number you want to Debit the money:\n");
    scanf("%d",&source);

    Bank *temp=first;

    Bank *posofdebit=NULL;
    Bank *posofcred=NULL;

    int flag=0;

    while(temp!=NULL)
    {
        
        if(source == temp->number){
             if(credit>temp->balance){
             printf("Insufficient balance");
             exit(0);
              }
            flag=1;
            posofdebit=temp;
          break;
            
        }
         temp=temp->next;
     }
    temp=first;
    flag=0;
    
    while(temp!=NULL){
        if(destination== temp->number)
        {
          flag=1;
          posofcred=temp;
          break;
        }
        temp=temp->next;
    }     
    if(flag==1)
    {
          posofcred->balance=posofcred->balance+credit;
          printf("amount credited  Rs.%d\n",credit);
          printf("current balance =%d",posofcred->balance);
          
          posofdebit->balance=posofdebit->balance-credit;
          printf("amount Debited  Rs.%d\n",credit);
          printf("current balance =%d",posofdebit->balance);
          
    }
    else
    {
        printf("Account Number Not found!");
        exit(0);
    }
   
}
