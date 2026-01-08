#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct password_data
{
    char*username;
    char*service;
    char*password;
}pass;

char*BANNED_CHR = " !\"#$%&'()*+,/:;<=>?[\\]^`{|}~"; 
char*BANNED_CHR_PASS = ",:;|";

const int MIN_PASS_LEN = 8;
const int MAX_PASS_LEN = 99;

const int MIN_USER_SERVICE_LEN = 6;
const int MAX_USER_SERVICE_LEN = 49;

int find(char*src, char target){
    //checks if target is in src --> 1st index of target else : negative length of src
    int len = strlen(src);
    for(int i = 0; i < len; i++){
        if(src[i] == target){
            return i;
        }

    }
    return -len;

}

char* ascii_2_base16(char* src){
    //returns an encoded string according to base 16 map = "0123456789abcdef"(which is hex is in this case)
    int srclen = strlen(src);
    char* key = malloc((2*srclen+1)*sizeof(char));
    char* b16map = "0123456789abcdef";

    for(int i = 0;i<2*srclen;i+=1){
        key[i] = 0;
    }

    //duplicating chars
    for(int j = 0; j<2*srclen;j+=2){
        key[j] = src[j/2];
        key[j+1] = src[j/2];
    }

    for(int j = 0; j<2*srclen;j+=2){
        key[j] = b16map[key[j]>>4];
        key[j+1] = b16map[src[j/2]&15];
    }

    key[2*srclen] = '\0';
        
    //dont forgot to free that malloc
    //printf("%s\n",key);
    return key;

    
}

char* base16_2_ascii(char* src){
    //returns a decoded string according to base 16 map = "0123456789abcdef"(hex);
    char* b16map = "0123456789abcdef";
    int len = strlen(src)/2;
    char* key = malloc((len+1)*sizeof(char));

    for(int i = 0;i<len;i++){
        //printf("%c %c\n",src[2*i],src[2*i+1]);
        key[i] = find(b16map,src[2*i])<<4 | find(b16map,src[2*i+1]) ;
        //printf("%d\n-------\n",key[i]);

    }
    key[len] = '\0';
    //dont forget to free malloc
    return key;
}

char char_check(char*src,char*banned_chars){
    //returns 0 is a banned char is in src else returns 1
    // banned_chars = " !"#$%&'()*+,/:;<=>?[\]^`{|}~"

    int banlen = strlen(banned_chars); 
    int srclen = strlen(src); 

    for(int i = 0; i < banlen ; i++ ){
        for(int j = 0;j < srclen;j++){
            if(src[j]==banned_chars[i]){
                return 0;
            }
        } 
    }

    return 1;

}

char len_check(char*src,int min_size,int max_size){
    //checks if length of src is in between min_size and max_size
    //returns 0 if length is not in range else 1
    int len = strlen(src);

    if(len<min_size || len>max_size){
        return 0;
    }
    return 1;
}


void printn(char a,int n){
    //to draw lines of specific chars eq. ----------
    for(int i = 0; i<n;i++){
        printf("%c",a);
    }
}



char to_lower(char a){
    //converts uppercase to lowercase
    if(a>='A' && a<='Z'){
        return a + 32;
    }
    else{
        return a;
    }
}




char* str2lower(char str[]){
    //returns a str in lowercase
    int size = strlen(str);
    char* output =  malloc((size+1)*sizeof(char));

    for(int i = 0;i<size;i++){
        output[i] = to_lower(str[i]);
    }
    output[size] = '\0';
    //printf("%s\n",output);
    //dont forget to free the malloc {output}
    return output;
}


int randint(int min,int max){
    //returns a randomly generated number between min and max
    return (rand()%(max-min+1))+min;
}

void PASS_GEN(int size, int n){
    //Generates a strong password of length = size n times

    if(size<8){size = 8;}
    else if(size>99){size = 99;}
    
    for(int j = 0;j<n;j++){
        for(int i = 0; i<16;i++){
            printf("%c",randint(32,126));
        }
        printf("\n");
    }
}

int write(FILE* fptr){
    /*write function- takes input from user as username,password,service, 
    appends all of them in record chunk --> encodes it -->  writes it to data file*/
    pass P1;
    P1.username = malloc(50*sizeof(char));
    P1.service = malloc(50*sizeof(char));
    P1.password = malloc(100*sizeof(char));

    char* Record_chunk = malloc(200*sizeof(char));
    Record_chunk[0] = '\0';//as it is all garbage 

    if(P1.username != NULL && P1.service != NULL && P1.password != NULL && Record_chunk != NULL){
        
        printf("\nvalid chars for Username and Service are [A-Z][a-z][0-9][_-]\n\n");
        printf("Non valid chars for Password are \",:;|]\"\n\n");
        printn('~',67);
        printf("\n");

        do{
            printf("enter username: ");
            fgets(P1.username,50,stdin);
            if((char_check(P1.username,BANNED_CHR) && len_check(P1.username,MIN_USER_SERVICE_LEN,MAX_USER_SERVICE_LEN)) == 0 )printf("Invalid Entry!!!\n\n");
        }while((char_check(P1.username,BANNED_CHR) && len_check(P1.username,MIN_USER_SERVICE_LEN,MAX_USER_SERVICE_LEN)) == 0 );

        P1.username[find(P1.username,'\n')] = '\0';//if find fails to \n it return -1 thats a problem!!!
        
        
        //printf("%s\n",P1.username);

        
        do{
            printf("enter service: ");
            fgets(P1.service,50,stdin);
            if((char_check(P1.service,BANNED_CHR) && len_check(P1.service,MIN_USER_SERVICE_LEN,MAX_USER_SERVICE_LEN))  == 0)printf("Invalid Entry!!!\n\n");
        }while((char_check(P1.service,BANNED_CHR) && len_check(P1.service,MIN_USER_SERVICE_LEN,MAX_USER_SERVICE_LEN))  == 0 );

        P1.service[find(P1.service,'\n')] = '\0';

        //printf("%s\n",P1.service);

        do{
            printf("enter password: ");
            fgets(P1.password,100,stdin);
            if((char_check(P1.password,BANNED_CHR_PASS) && len_check(P1.password,MIN_PASS_LEN,MAX_PASS_LEN))  == 0)printf("Invalid Entry!!!\n\n");
        }while((char_check(P1.password,BANNED_CHR_PASS) && len_check(P1.password,MIN_PASS_LEN,MAX_PASS_LEN))  == 0);

        P1.password[find(P1.password,'\n')] = '\0';

        //printf("%s\n",P1.password);

        strcat(Record_chunk,P1.service);
        strcat(Record_chunk,",");//",/0"
        strcat(Record_chunk,P1.username);
        strcat(Record_chunk,",");//",/0"
        strcat(Record_chunk,P1.password);

        char* Encoded_Record_chunk = ascii_2_base16(Record_chunk);

        //printf("Record chunk: %s\n",Encoded_Record_chunk);

        fprintf(fptr,"%s\n",Encoded_Record_chunk);
        //fprintf(fptr,"%s,%s,%s\n",P1.service,P1.username,P1.password);

        free(Encoded_Record_chunk);
    }
    else{
        printf("error writing!!");
        return 1;
    }

    free(P1.username);
    free(P1.service);
    free(P1.password);

    free(Record_chunk);
    
    return 0;
}
int read(FILE*fptr){
    /*Read function- takes username,service as input from user , loops through each record chunk
    decodes it --> turns user input and the record chunk data in lower case to compare them --> prints the username,password,service */
    rewind(fptr);

    pass P2;//for user to enter value in (target)

    pass P3;//to store the result 

    P2.username = malloc(50*sizeof(char));
    printf("enter username: ");
    fgets(P2.username,50,stdin);
    P2.username[find(P2.username,'\n')] = '\0';

    //printf("%s,%lu\n",P2.username,strlen(P2.username));


    P2.service = malloc(50*sizeof(char));
    printf("enter service: ");
    fgets(P2.service,50,stdin);
    P2.service[find(P2.service,'\n')] = '\0';
   
    //printf("%s,%lu\n",P2.service,strlen(P2.service));
//---------------------------------------------------------
    P3.username = malloc(50*sizeof(char));
    P3.service = malloc(50*sizeof(char));
    P3.password = malloc(100*sizeof(char));

    
    //char*Decoded_Record_chunk = malloc(200*sizeof(char));

    char BUFFER[150];
    int record_matched = 0;

    printn('-',100);//BAR---------
    printf("\n");

    printf("%-30s%-30s%-50s\n","[SERVICE]","[USERNAME]","[PASSWORD]");

    while(fscanf(fptr,"%149[^\n]\n",BUFFER) == 1){

        char* Decoded_Record_chunk = base16_2_ascii(BUFFER);

        sscanf(Decoded_Record_chunk,"%49[^,],%49[^,],%99[^\n]\n",P3.service,P3.username,P3.password);
        //printf("%-30s,%-30s:%-50s\n",P3.service,P3.username,P3.password);

        char* lower3username = str2lower(P3.username); 
        char* lower2username = str2lower(P2.username);

        char* lower3service = str2lower(P3.service);
        char* lower2service = str2lower(P2.service);
        
        if(!strcmp(P2.username,".")){ //no entery for username then checks further for service
            
            if(strstr(lower3service,lower2service) != NULL){
                printf("%-30s%-30s%-50s\n",P3.service,P3.username,P3.password);
                record_matched++;
            }
            
        }
        else if(!strcmp(P2.service,".")){ //no entery for service then checks further for username
            
            if(strstr(lower3username,lower2username) != NULL){
                printf("%-30s%-30s%-50s\n",P3.service,P3.username,P3.password);
                record_matched++;
            }
            
        }
        else{ // both entries are filled by user:result is generate on basis of both inps

            if(strstr(lower3username,lower2username) != NULL && strstr(lower3service,lower2service) != NULL){
                printf("%-30s%-30s%-50s\n",P3.service,P3.username,P3.password);
                record_matched++;
            }

        }

        free(lower3username);
        free(lower2username);

        free(lower3service);
        free(lower2service);

        
        free(Decoded_Record_chunk);
    }

    if(record_matched==0){
        printf("%45s\n","No Results !!");
    }

    printn('-',100);//BAR--------
    printf("\n");
    free(P2.username);
    free(P2.service);
    
    free(P3.username);
    free(P3.service);
    free(P3.password);

    

    return 0;
}



int main(){
    srand(time(NULL));
  
    char choice_buffer[20];
    int choice = 5;//if choice buffer is somthing else than 1,2,3,4 then choice remains unchanged so 5 will be considered as default case


    FILE* fptr = fopen("PASS.data","a+");

    if(!fptr){
        printf("file error!!\n");
        return 1;
    }
    RETRY_LABLE:// lable to get to start;

    printn('=',24);
    printf("Welcome To PASSMAN");
    printn('=',24);
    printf("\n");

    printf("(1) Enter for saving a password\n");
    printf("(2) Enter for reading a password\n");
    printf("(3) Generate a password\n");
    printf("(4) Exit\n");

    printn('=',69);
    printf("\n");

    fgets(choice_buffer,20,stdin);
    sscanf(choice_buffer,"%d",&choice);

    switch(choice){
        case 1:
        write(fptr);
        choice = 5;
        break;

        case 2:
        read(fptr);
        choice = 5;
        break;

        case 3:
        printf("Freshly baked for you ,use them wisely :)\n");
        PASS_GEN(16,4);
        choice = 5;
        break;

        case 4:
        fclose(fptr);
        printf("Take care, come again!!\n");
        return 0;
        break;

        default:
        printf("invalid entry!!\n");
        goto RETRY_LABLE;// if value is invalid(default case):jump back to start;
        break;
    }

    goto RETRY_LABLE;
    
    fclose(fptr);
    return 0;
}