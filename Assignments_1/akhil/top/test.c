/**
 * File              : test.c
 * Author            : Akhil Budampati <a.budampati@globaledgesoft.com>
 * Date              : 17.07.2018
 * Last Modified Date: 10.08.2018
 * Last Modified By  : Akhil Budampati <a.budampati@globaledgesoft.com>
 */
//#include<stdio.h> 
//#include<stdlib.h>
//#include<assert.h>
//#include<unistd.h>

int main( int argc, char **argv ){
    int count = 0;
    FILE * test_fp =  NULL;
    FILE * test_fpp = NULL; 
    char * buff = (char *)malloc(sizeof(char)*128) ;
    assert(buff); 
    if(NULL == (test_fp = fopen(argv[1], "r"))){
        perror("fopen");
        exit(0);
    }
    fclose(stdin);
    perror("fclose");
    while(1){
    while(fgetc(test_fp) != EOF){
        fseek(test_fp,-1,SEEK_CUR);
    fgets(buff,128, test_fp);
    for(count = 0; buff[count]!= '\n' && buff[count] != EOF; count++);
    buff[count-1] = '\0';
    fprintf(stdout,"%s",buff);
   fflush(stdout);
    } 
    sleep(1);
    fprintf(stdout, "\r");
    rewind(test_fp);
    }
    return 0;
    
}
