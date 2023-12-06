#include <stdio.h>
#include <string.h>
#include<stdbool.h>
#include <ctype.h>
#include <stdlib.h>

void createAccount();
void login();
void deposit(char userFileName[255], char password[255], int balance);
void withdraw(char userFileName[255], char password[255], int balance);
void payment(char userFileName[255], char password[255], int balance);

int main(){
    int input;
    char throwaway;
    do{
    printf("If you would like to create an account, press 1\nIf you would like to log into an account, press 2\nEnter: ");
    scanf("%d", &input);//recieves input
    scanf("%c", &throwaway); //clears input buffer
    if(input == 1){
        printf("\n************************************************************************\nCREATING ACCOUNT\n************************************************************************\n");
        createAccount();
    }
    else if (input == 2){ //login
        printf("\n************************************************************************\nLOGGING INTO ACCOUNT\n************************************************************************\n");
        login();
    }
    else{
        printf("\nInvalid input, please try again\n");
    }
    }while(input != 1 || input != 2); //exits only if a valid input is created
}

void createAccount(){
   while (true){
    char userName[255];
    char buffer[255]; //used as a dummy variable for names
    bool uniqueUsername = true; //used to check if username is unique
    char password[255];   
    printf("What would you like your username to be(lowercase): ");
    fgets(userName, 255, stdin);
    userName[strlen(userName) - 1] = '\0'; //reads name and removes whitespace at end of it
    for(int i = 0; i < strlen(userName); i++){ //makes everything lowercase
        userName[i] = tolower(userName[i]);
    }
    FILE *pF = fopen("usernames.txt", "a+"); //opens 2nd file to read it, and creates it if it doesn't exist
    
    //int length = sizeof(userName)/sizeof(userName[0]);
    while(fgets(buffer, 255, pF)){ //reads file adn checks if the username is on it
        //if(strncmp(buffer, userName, strlen(userName)) == 0){  DIDN'T WORK
        if(strncmp(buffer, userName, strlen(userName)) == 0 && buffer[strlen(userName)] == '\n'){ //checks the amount of characters in the string userName and only compares those characters 
            uniqueUsername = false;
            break;
        }
    }
    if(uniqueUsername == true){
        printf("What is your password: ");
        fgets(password, 255, stdin);
        password[strlen(password)-1] = '\0'; //removes whitespace at end of password cause fgets is just like that

        printf("Your username is %s and your password is %s", userName, password);
        fprintf(pF, "%s\n", userName); //adds username to the list of usernames. 
        //I do know that it would be more efficient to ignore the file with the list of usernames and instead list through the existing profile files of a user but I spent a lot of time figuring out how to check things in a file so I'm gonna keep it in
        char buf[255]; 
        strcpy(buf, userName);
        strcat(buf, ".txt"); //creates a variable which matches the file name
        FILE *pUser = fopen(buf, "w"); //opens a file with the username of the individual
        fprintf(pUser, "%s\n1000", password); //creates a user file
        printf("\nYour username has succesfully been registered into the system!\n\n");
        fclose(pF);
        fclose(pUser);
        break;
    }
    else{
        printf("This username is already taken, try again\n");
    }
    fclose(pF);
   }
}
void login(){
    char userName[255];
    char password[255];
    printf("Enter your username: ");
    fgets(userName, 255, stdin);
    userName[strlen(userName) - 1] = '\0'; 
    char buf[255]; 
    char readFromFile[255];
    strcpy(buf, userName);
    strcat(buf, ".txt");
    FILE *pUser1 = fopen(buf, "r"); //opens file with the username
    if (pUser1 == NULL){ //checks if file exists for user
        printf("\nThis user doesn't exist, L Bozo\n");
    }
    else{
        printf("Enter your password: ");
        fgets(password, 255, stdin);
        password[strlen(password)-1] = '\0'; //removes whitespace at end of line
        fgets(readFromFile, 255, pUser1); //reads file
        if(strncmp(readFromFile, password, strlen(password)) == 0 && readFromFile[strlen(password)] == '\n'){ //checks the amount of characters in the string password and only compares those characters  
                printf("You have succesfully logged in!\n");
        }   
        else{
            printf("Haxor!\n");
            exit(0); //breaks function
        }
        fgets(readFromFile, 255, pUser1); //reads 2nd line
        printf("Welcome %s! Your balance is: $%s\n", userName, readFromFile);
        int balance = atoi(readFromFile); //makes the balance an integer
        int userInput;      
        while (true){
            printf("If you would like to deposit, enter '1', If you would like to withdraw, enter '2', If you would like to make a payment, enter '3': ");
            scanf("%d", &userInput); //recieves userinputgit 
            if(userInput == 1){
                printf("\nEntering deposit mode\n");
                deposit(buf, password, balance);
                break;
            }
            else if (userInput == 2){
                printf("\nEntering withdrawal mode\n");
                withdraw(buf, password, balance);
                break;
            }
            else if (userInput == 3){
                printf("\nEntering payment mode\n");
                payment(buf, password, balance);
                break;
            }
            else{
                printf("Not a correct input idiot, try again\n");
            }
        }

        // for(int i = 0; i == i; i++){
        //     fgets(readFromFile, 255, pUser1); //reads file
        //     if (i == 0){
        //          if(strncmp(readFromFile, password, strlen(password)) == 0 && readFromFile[strlen(password)] == '\n'){ //checks the amount of characters in the string password and only compares those characters 
        //         //important to note that this only works on the assumption that the password that the user entered 
        //         printf("You have succesfully logged in!\n");
        //         }   
        //         else{
        //             printf("Haxor!\n");
        //             break;
        //         }
        //     }
        //     else if (i ==1){
        //         printf("Welcome %s! Your balance is: ", userName/*readFromFile*/);
        //     }
        // }


        // while(fgets(readFromFile, 255, pUser1)){ //reads file adn checks if the password is on it
        //     if(strncmp(readFromFile, password, strlen(password)) == 0 && readFromFile[strlen(password)] == '\n'){ //checks the amount of characters in the string password and only compares those characters 
        //         //important to note that this only works on the assumption that the password that the user entered 
        //         printf("You have succesfully logged in!\n");
        //         printf("Welcome %s! Your balance is: ", userName);
        //     }
        //     else{
        //         printf("Haxor");
        //         break;
        //     }
        // }
    }
}

void deposit(char userFileName[255], char password[255], int balance){
    int depositAmount;
    char term; //throwaway variable
    while (true){
        printf("How much would you like to deposit: "); 
        if(scanf("%d%c", &depositAmount, &term) != 2 ||term != '\n'){ //checks if input was actually an integer
            printf("Enter a valid number!\n");
        }
        else{
            printf("Depositing amount.....\n");
            balance += depositAmount; //adds the deposit amount to the balance
            FILE *pF = fopen(userFileName, "w"); //overrides old user file and creates a new one
            //printf("\nYour password is: %s and your balance is: %s\n", password, userFileName);
            if(pF == NULL){
                printf("File could not be opened!");
            }
            fprintf(pF, "%s\n%d", password, balance);
            printf("Deposit succesful! Your new balance is: $%d\n", balance);
            fclose(pF);
            exit(0);
        }
    }
}
void withdraw(char userFileName[255], char password[255], int balance){
    int withdrawalAmount;
    char term; //thrwoaway varaiable
    while (true){
        printf("Your balance is currently %d, how much would you like to withdraw: ", balance); 
        if(scanf("%d%c", &withdrawalAmount, &term) != 2 ||term != '\n'){ //checks if input was actually an integer
            printf("Enter a valid number!\n");
        }
        else if(withdrawalAmount > balance){
            printf("You have tried withdrawing more than you have loser!\n");
        }
        else{
            printf("Withdrawing amount.....\n");
            balance -= withdrawalAmount; //subtracts withdrawal amount from balance
            FILE *pF = fopen(userFileName, "w"); //overrides old user file and creates a new one
            if(pF == NULL){
                printf("File could not be opened!");
            }
            fprintf(pF, "%s\n%d", password, balance);
            printf("Deposit succesful! Your new balance is: $%d\n", balance);
            fclose(pF);
            exit(0);
        }
    }
}
void payment(char userFileName[255], char password[255], int balance){
    int paymentAmount;
    char term; //thrwoaway varaiable
    while (true){
        printf("Your balance is currently %d, how much would you like to pay: ", balance); 
        if(scanf("%d%c", &paymentAmount, &term) != 2 ||term != '\n'){ //checks if input was actually an integer
            printf("Enter a valid number!\n");
        }
        else if(paymentAmount > balance){
            printf("You have tried paying more than you have loser!\n");
        }
        else{
            printf("Paying amount.....\n");
            balance -= paymentAmount; //subtracts withdrawal amount from balance
            FILE *pF = fopen(userFileName, "w"); //overrides old user file and creates a new one
            if(pF == NULL){
                printf("File could not be opened!");
            }
            fprintf(pF, "%s\n%d", password, balance);
            printf("Deposit succesful! Your new balance is: $%d\n", balance);
            fclose(pF);
            exit(0);
        }
    }
}
