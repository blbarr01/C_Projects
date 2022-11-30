#include <prompts.h>
#include <stdio.h>


    // one constant decleration

        /* the ascii range 48 - 57 are the numbers 0-9
         * asci 45 is - 
         * goal is parse the string and cull all characters that would not be in a 
         * phone number xxx-xxx-xxxx
         * 
         * the conditional is intended to determine wheter the character is between 0 and 9
         * or the hyphen 
         * i deliberatly hose the logic structure:
         *  A ^ (B&C) instead of (B&C) ^ A 
         * 
         * 
        */
void printPhoneNumber(char* phoneNumber, int length){
    char temp[length]; 
    for(int i = 0; i< length -1; i++ ){
        if (phoneNumber[i] == '\0')
        {
            continue;            
        }
        
        if(phoneNumber[i] == 45 || (phoneNumber[i] >= 48 && phoneNumber[i] <= 57)){
            temp[i] = phoneNumber[i];
        }
        else{
            printf("invalid phone number provided");
            break;
        }
    }
    printf(" phone number from funtion print call: %s \n", temp);
}


int main(){
    const int phoneNumLength = 16;
    const int nameLength = 32; 
    
    char name[nameLength];
    int age; 
    char phoneNumber[phoneNumLength];
  
    NamePrompt();
    fgets(name,nameLength,stdin);
    AgePrompt();
    scanf("%d", &age);
    PhoneNumberPrompt();
   // fflush(stdin);
    scanf("%s", phoneNumber);


    printf("the name you entered was %s", name);
    printf("the age you entered was %d \n", age);
    //printf("the phone number from main print call %s \n", phoneNumber);
    printPhoneNumber(phoneNumber, phoneNumLength);
    return 0;
}