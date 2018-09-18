//AARON HABANA
//COMP 322
//PROJECT 4 - fileaccess.c
//GABROVSKY


/*** fileaccess.c ***/

//write a program in C which displays on the screen the user's
// permissions for each one of the files on the command line. 


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pwd.h>
#include <string.h>
#include <unistd.h>

gid_t getguid(void);//initialize getguid()
gid_t getuid(void);//initialize getuid()

/* fileaccess file...         */
/* print info on access modes */
/*                            */


int main(int argc, char *argv[]){
  

   int errors, k, perm;
   struct stat buf;
   char *p;
   char *dir="";
   char *symb;
   char *original;
   struct passwd *pwd;
   pwd = getpwuid(getuid());

   symb = "/";
   errors = 0;

   for(k=1;k<argc;k++){
      
      p=argv[k]; 
      if(*p != '/'){
        dir =(char *)malloc(strlen(pwd->pw_dir)+strlen(argv[k])+2);    //allocate amount of memory for directory string
        strcat(dir, pwd->pw_dir);       // assign user's directoy to dir
        strcat(dir,symb);     // add '/'
        strcat(dir,argv[k]);     // add filename to dir
        original = argv[k];
        argv[k] = dir;      //
        printf("pwd: %s ",pwd->pw_dir);
      }

      //FETCH INODE INFORMATION
      if(stat(argv[k],&buf)==(-1)) {
         fprintf(stderr,"%s: cannot access %s\n",argv[0], argv[k]);
         errors++;
         continue;
      }

      //PRINT FILE PERMISSIONS
      perm=buf.st_mode; //store permissions as an int
      if(getuid()==buf.st_uid){
        //do nothing. user is owner
      }
      else if(getgid()==buf.st_gid){ //if user is not the owner but same group as owner; shift 3 bits
         perm = perm << 3;
      }
      else{ // if user is neither the owner or in the same group as the owner; shift 6 bits
         perm = perm << 6;
      }
      printf("File %s has: \n", argv[k]);

      if(perm & 0400) { //check if permission to read
         printf("read\n");
      }
      else {
         printf("no read\n"); 
      }
      if(perm & 0200) { //check permission to write
         printf("write\n");
      }
      else{
         printf("no write\n");
      } 
      if(perm & 0100) {
         printf("execute\n"); // check permission to exe
      }
      else{
         printf("no execute\n");
      }
      argv[k]=original;
   }
   if(errors){
      return(1);
   }
   else{
      return(0);
   }

}