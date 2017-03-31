#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "my402list.h"
#include "cs402.h"


//Function declarations
int sortcheck(int argc , char* argv[]);
void Printing(My402List *mylst, int num);
int filereading(char *argv[]);
void sort(int argc, char* argv[]);
void BubbleSortForwardList(My402List *mylst, int num);
void BubbleForward(My402List *pList, My402ListElem **pp_elem1, My402ListElem **pp_elem2);



int main(int argc, char *argv[])
{
  sortcheck(argc,argv);
  filereading(argv);
  return 0;
}

// To check for "sort"
int sortcheck(int argc , char* argv[])
{
  if(argc > 1)
    if(((strcmp(argv[1],"sort") && argv[1])) == 0)
    return TRUE;
  {
    fprintf(stderr,"Malformed Command\nUsage Information : warmup1 sort [tfile]");
    exit(1);
  } 
}


//To create a structure 

typedef struct Trans {
   char sign;
   unsigned long timestamp;
   long int amt;
   char desc[24];
   long int bal;
} transaccess1;

//Printing list

void Printing(My402List *mylst, int num)
{
    struct tm* info;
    char buffer[20];
    unsigned long y;
    unsigned long p[1024];
    int i,j;

    char po1[10],po3[10];
    char po2[10],po4[10],po5[10],po6[10];

    My402ListElem *element=NULL;
    
    
    long int x=0,bal1;
    char sign2;
    //String catenation
    strcpy(po1,"?,???,???");
    strcpy(po2,".??");
    strcpy(po5,po1);
    strcpy(po6,po2);
    strcat(po5,po6);
    strcpy(po3,"(");
    strcpy(po4,")");
    strcat(po3,po1);
    strcat(po2,po4);
    strcat(po3,po2);
    
    i=0;
    j=0;
    //char *oldLocale = setlocale(LC_NUMERIC, NULL);

    for (element=My402ListFirst(mylst); element != NULL; element=My402ListNext(mylst, element)) 
    {
     p[i]=((transaccess1 *)element->obj)->timestamp;
     i++;
    }

    for (element=My402ListFirst(mylst); element != NULL; element=My402ListNext(mylst, element)) 
    {
     if(element!=My402ListLast(mylst) && p[j+1]==p[j]) 
     {
      fprintf(stderr,"Identical Timestamps\n");
      exit(1);    
     }
     j++;
    }
    printf("+-----------------+--------------------------+----------------+----------------+\n");
    printf("|       Date      | Description              |         Amount |        Balance |\n");
    printf("+-----------------+--------------------------+----------------+----------------+\n");
     for (element=My402ListFirst(mylst); element != NULL; element=My402ListNext(mylst, element)) 
     { 
     sign2=((transaccess1 *)element->obj)->sign;
     //schk= 24 - strlen(((transaccess1 *)element->obj)->desc);

     y=((transaccess1 *)element->obj)->timestamp;
     time_t r=y;

     char *s1=ctime(&y);
     info=localtime(&r);
     strftime(buffer,20,"%a %b %d %Y", info);

     long int trint,trmod,balint,balmod,balan;

     trint=(((transaccess1 *)element->obj)->amt)/100;
     balan=((transaccess1 *)element->obj)->amt;
     trmod=balan%100;

     if(sign2=='+')
     {
      x=x+((transaccess1 *)element->obj)->amt;
        bal1=x;
        balint=bal1/100;
        balmod=bal1%100;
     }
     else
     {
      x=x-((transaccess1 *)element->obj)->amt;
        bal1=x;
        balint=bal1/100;
        balmod=bal1%100;
     }

     if(bal1 <0 && sign2=='-')
     {
      if(labs(balint)>10000000)
      {
        if(trmod>=10)
        {
          setlocale(LC_NUMERIC, "en_US");
        printf("| %10.10s%5.5s | %-25s| (%'9li.%li) | %s |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,po3);
        //setlocale(LC_NUMERIC, oldLocale);
        }
        else
        {
         setlocale(LC_NUMERIC, "en_US");
        printf("| %10.10s%5.5s | %-25s| (%'9li.%li) | %s |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,po3);
        //setlocale(LC_NUMERIC, oldLocale);
        }
      }
        else
        {
         if(trmod>=10 && labs(balmod) >=10)
         {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s| (%'9li.%li) | (%'9li.%li) |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale); 
         }

         if(trmod>=10 && labs(balmod) <10)
         {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s| (%'9li.%li) | (%'9li.0%li) |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale); 
         }
        
         if(trmod<10 && labs(balmod) <10)
         {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s| (%'9li.0%li) | (%'9li.0%li) |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale);
         }

         if(trmod<10 && labs(balmod) >=10)
         {
     setlocale(LC_NUMERIC, "en_US");
       printf("| %10.10s%5.5s | %-25s| (%'9li.0%li) | (%'9li.%li) |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));
     //setlocale(LC_NUMERIC, oldLocale); 
         }
      }
    }


    if(bal1<0 && sign2=='+')
    {
      if(labs(balint)>10000000)
      {
        if(trmod>=10)
        {
          setlocale(LC_NUMERIC, "en_US");
         printf("| %10.10s%5.5s | %-25s| %'11li.%li | %s |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,po3);
         //setlocale(LC_NUMERIC, oldLocale); 
        }
        else
        {
          setlocale(LC_NUMERIC, "en_US");
        printf("| %10.10s%5.5s | %-25s| %'11li.0%li | %s |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,po3);
        //setlocale(LC_NUMERIC, oldLocale);
        }
      }
      else
      {
        if(trmod>=10 && labs(balmod)>=10)
        {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s|%'11li.%li  | (%'9li.%li) |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale); 
        }
    
       if(trmod>=10 && labs(balmod)<10)
       {
        setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s|%'11li.%li  | (%'9li.0%li) |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale); 
       }

       if(trmod<10 && labs(balmod)<10)
       {
        setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s|%'11li.0%li  | (%'9li.0%li) |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale);
       }

       if(trmod<10 && labs(balmod)>=10)
       {
        setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s|%'11li.0%li  | (%'9li.%li) |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale);
       }
      }
    }



    if(bal1>0 && sign2=='-')
    {
      if(labs(balint)>10000000)
      {
        if(trmod>=10)
        {
          setlocale(LC_NUMERIC, "en_US");
          printf("| %10.10s%5.5s | %-25s| (%'9li.%li) |  %s  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,po5);
          //setlocale(LC_NUMERIC, oldLocale); 
        }
        else
        {
          setlocale(LC_NUMERIC, "en_US");
          printf("| %10.10s%5.5s | %-25s| (%'9li.0%li) |  %s  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,po5);
          //setlocale(LC_NUMERIC, oldLocale);
        }
        
      }
      else
      {
        if(trmod>=10 && labs(balmod)>=10)
        {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s| (%'9li.%li) |%'11li.%li  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale); 
        }

        if(trmod>=10 && labs(balmod)<10)
        {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s| (%'9li.%li) |%'11li.0%li  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale); 
        }

        if(trmod<10 && labs(balmod)<10)
        {
         setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s| (%'9li.0%li) |%'11li.0%li  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale); 
        }
        if(trmod<10 && labs(balmod)>=10)
        {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s| (%'9li.0%li) |%'11li.%li  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale); 
        }
     
      }
    }


    if(bal1>0 && sign2=='+')
    {
      if(labs(balint)>10000000)
      {
        if(trmod>=10)
        {
          setlocale(LC_NUMERIC, "en_US");
         printf("| %10.10s%5.5s | %-25s| %'11li.%li |  %s  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,po5); 
         //setlocale(LC_NUMERIC, oldLocale);
        }
        else
        {
          setlocale(LC_NUMERIC, "en_US");
        printf("| %10.10s%5.5s | %-25s| %'11li.0%li |  %s  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,po5);
         //setlocale(LC_NUMERIC, oldLocale);
        }
      }
      else
      {
        if(trmod>=10 && labs(balmod)>=10)
        {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s|%'11li.%li  |%'11li.%li  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale);
        }

        if(trmod>=10 && labs(balmod)<10)
        {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s|%'11li.%li  |%'11li.0%li  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale);
        }
       
        if(trmod<10 && labs(balmod)<10)
        {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s|%'11li.0%li  |%'11li.0%li  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale);
        }
        if(trmod<10 && labs(balmod)>=10)
        {
          setlocale(LC_NUMERIC, "en_US");
     printf("| %10.10s%5.5s | %-25s|%'11li.0%li  |%'11li.%li  |\n",s1,s1+19,((transaccess1 *)element->obj)->desc,trint,trmod,labs(balint),labs(balmod));  
     //setlocale(LC_NUMERIC, oldLocale);
        }
     
      }
    }
  }
 printf("+-----------------+--------------------------+----------------+----------------+\n");
}


//To read the contents of a file
int filereading(char *argv[])
{
    char sign1;
    char *d;
    
  unsigned long timestamp1;     
  long int amt1,amt2,amt3,amt4;
  int i;

    My402List list2;
    memset(&list2, 0, sizeof(My402List));
    (void)My402ListInit(&list2);
    
    int num=0;
    FILE *f;
    FILE *f1;
  char buff[1024];
  char buff1[1024];
  f1=fopen("test.tfile","r");
  if(fgets(buff1, sizeof buff1, f1) == NULL )
    {
      fprintf(stderr,"Malformed Command\nUsage Information");
      exit(1);
    }

    //Open file 
    if(argv[2]==NULL)
    {
    f = stdin;
  }
  else 
  {
    f = fopen(argv[2], "r");
  }

    //No file
  if(f == NULL)
  {
    perror("Malformed Command\nUsage Information");
    exit(0);
  }

 

  while ( fgets ( buff, sizeof buff, f ) != NULL )
   {
    if(strlen(buff)>1024)
    {
      fprintf(stderr,"Line exceeding 1024 characters.\n");
      exit(1);
    }
    char *desc1;
        transaccess1 *transaccess = (transaccess1*)malloc(sizeof(transaccess1));
    num++;
    My402ListElem *element=(My402ListElem *)malloc(sizeof(My402ListElem));
        element->obj=transaccess;
        if(strchr(buff,'.')==NULL)
        {
          fprintf(stderr,"Malformed Input\n");
          exit(1);
        }
        //Splitting sign from rest
        sign1=*strtok(buff,"\t");
        if(sign1 != '+' && sign1 != '-')
        {
         fprintf(stderr,"Input file is in wrong format\n");
         exit(1);
        }
        transaccess->sign = sign1;
  
        //Splitting timestamp from rest
        timestamp1= (unsigned int) atof( strtok(NULL,"\t") );
        if(timestamp1 >time(0) || timestamp1 > 4294967295) 
        {
          fprintf(stderr,"Enter a valid timestamp.\n");
          exit(1);
        }
        transaccess->timestamp = timestamp1;
  
        //Splitting amount from rest
       
        amt1=(int) atof( strtok(NULL,"."));
        amt2=amt1 *100;
        d=strtok(NULL,"\t");
        if(strlen(d)!=2)
        {
          fprintf(stderr,"Invalid Transaction amount\n");
          exit(1);
        }
        amt4=(int) atof(d);
        amt3= amt4+amt2;
        if((long int)amt1 > 10000000 || (long int)amt1 <=0)
        {
          fprintf(stderr,"Invalid Transaction amount\n");
          exit(1);
        }
        transaccess->amt = amt3;
        

        //Splitting description from rest
        desc1=strtok(NULL,"\n");
        if(desc1 == NULL)
        {
          fprintf(stderr,"Description NULL\n");
          exit(1); 
        }
        
        
        // printf("%s\n",&desc1[0]);
        while(isspace(*desc1))
        {
          *desc1++;
        }
        
        
              

        for(i=0; i< strlen(desc1); i++)
        {
        
        }
        if(strlen(desc1)>24)
        {
          desc1[24]='\0';
        }
        desc1[i]='\0';

        for(i=0; i< strlen(desc1); i++)
        {
            transaccess->desc[i] = desc1[i];
        }
        transaccess->desc[i] = '\0';

        (void)My402ListAppend(&list2,element->obj);

    }
        BubbleSortForwardList(&list2,num);
        Printing(&list2,num);
     
  
   fclose ( f );
    
     
   return TRUE;
}

void BubbleSortForwardList(My402List *mylst, int num)
{
  My402ListElem *element=NULL;
    int i=0;

    for (i=0; i < num; i++) {
        int j=0, something_swapped=FALSE;
        My402ListElem *next_elem=NULL;

        for (element=My402ListFirst(mylst), j=0; j < num-i-1; element=next_elem, j++) {
            unsigned long cur_val=((transaccess1 *)element->obj)->timestamp, next_val=0;
            
            next_elem=My402ListNext(mylst, element);
            next_val = ((transaccess1 *)next_elem->obj)->timestamp;
            
            if (cur_val > next_val) 
            {
                BubbleForward(mylst, &element, &next_elem);
                something_swapped = TRUE;
            }
        }
        if (!something_swapped) break;
    }
}

void BubbleForward(My402List *pList, My402ListElem **pp_elem1, My402ListElem **pp_elem2)
   
{
    My402ListElem *elem1=(*pp_elem1), *elem2=(*pp_elem2);
    void *obj1=elem1->obj, *obj2=elem2->obj;
    My402ListElem *elem1prev=My402ListPrev(pList, elem1);
    My402ListElem *elem2next=My402ListNext(pList, elem2);

    My402ListUnlink(pList, elem1);
    My402ListUnlink(pList, elem2);
    if (elem1prev == NULL) 
    {
        (void)My402ListPrepend(pList, obj2);
        *pp_elem1 = My402ListFirst(pList);
    } 
    else
    {
        (void)My402ListInsertAfter(pList, obj2, elem1prev);
        *pp_elem1 = My402ListNext(pList, elem1prev);
    }
    if (elem2next == NULL) 
    {
        (void)My402ListAppend(pList, obj1);
        *pp_elem2 = My402ListLast(pList);
    } 
    else
    {
        (void)My402ListInsertBefore(pList, obj1, elem2next);
        *pp_elem2 = My402ListPrev(pList, elem2next);
    }
}

