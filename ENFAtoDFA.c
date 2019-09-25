//Write a program to find ε – closure of all states of any given NFA with ε transition.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int split(char [1000],char [1000][1000]);//function to split string to array
void cleaning(char [1000]);
void findNewstates(char [1000],char [1000]);//find new state added to the current Epsilon closure
void inputENFA();
void findEclosure();
void outputEclosure();
void ENFAtoNFA();
void outputNFA();
int ns,na;//no of states, alphabets
char f[10];//Set of final states of NFA
char tdn[10][10][10];//Transition diagram of ENFA
char td[10][10][10];//Transition diagram of NFA
char Eclosure[1000][1000];
int countUnprocessed;//count unprocessed states in each eclosure
int indexUnprocessed;//index from which the stats need to be processed in each eclosure
int Unprocessed[1000];
int main()
{   inputENFA();
    findEclosure();
    ENFAtoNFA();
    //outputEclosure();
    outputNFA();
    //printf("%d ",countUnprocessed);
    return 0;
}
void ENFAtoNFA()
{   /*
    for i=0 to ns
    {   copy Eclosure[i] to str
        split str to arr
        for j=0 to na
        {   td[state][alphabet]=""
            for each element in arr
                td[state][alphabet]+=tdn[element][alphabet]
        }
    }
    clean
    for i=0 to ns
        for j=0 to na
            split td[state][alphabet] into arr
                concateate e closure of each
    clean
    */
    int i,j,k;

    for(i=0;i<ns;i++)
    {   char str[100];char array[1000][1000];
        strcpy(str,Eclosure[i]);
        int n=split(str,array);//Array:{"0","1","1","2"}
        for(j=0;j<na;j++)
        {   strcpy(td[i][j],"");
            for(k=0;k<n;k++)
            {   strcat(td[i][j],",");
                strcat(td[i][j],tdn[atoi(array[k])][j+1]);
            }
        }
    }
    for(i=0;i<ns;i++)
        for(j=0;j<na;j++)
            cleaning(td[i][j]);
    for(i=0;i<ns;i++)
    {   for(j=0;j<na;j++)
        {   char str[100],newstr[100];char array[1000][1000];
            strcpy(str,td[i][j]);
            int n=split(str,array);//Array:{"0","1","1","2"}
            strcpy(newstr,"");
            for(k=0;k<n;k++)
            {   strcat(newstr,",");
                strcat(newstr,Eclosure[atoi(array[k])]);
            }
            cleaning(newstr);
            strcpy(td[i][j],newstr);
        }
    }
}
void outputNFA()
{   int i,j;
    printf("\nTransition table of NFA:\n");
    for(i=0;i<na;i++)
        printf("\t%c",'a'+i);
    for(i=0;i<ns;i++)
    {   printf("\n%d\t",i);
        for(j=0;j<na;j++)
            printf("%s\t",td[i][j]);
    }
}
void findNewstates(char str1[1000],char str2[1000])
{   char copy1[1000],copy2[1000];
    char array1[1000][1000],array2[1000][1000];
    int i,j;
    strcpy(copy1,str1);strcpy(copy2,str2);
    int n1=split(copy1,array1);
    int n2=split(copy2,array2);
    for(i=0;i<n1;i++)
    {   int flag=1;
        for(j=0;j<n2;j++)
        {   if(strcmp(array1[i],array2[j])==0)
            {   flag=0;break;
            }
        }
        if(flag==1)
        {   Unprocessed[countUnprocessed++]=i;
        }
    }
}
void findEclosure()
{   /*  for each state
        {   initialize Eclosure to the state
            countUnprocessed=1
            indexUnprocessed=0
            while(countUnprocessed>0)
            {   Concatenate the E transition in transition diagram to Eclosure of that state
                clean Eclosure
                for each new state added to the Eclosure
                    countUnprocessed++
                countUnprocessed--
                indexUnprocessed++
            }
        }
    */
    int i;
    for(i=0;i<ns;i++)
    {   char str[1000],copy[1000];
        itoa(i,str,10);//printf("%s",str);
        strcpy(Eclosure[i],str);
        Unprocessed[0]=i;
        countUnprocessed=1;
        indexUnprocessed=0;
        while(countUnprocessed>0)
        {   strcpy(copy,Eclosure[i]);
            strcat(Eclosure[i],",");
            strcat(Eclosure[i],tdn[Unprocessed[indexUnprocessed]][0]);
            cleaning(Eclosure[i]);//printf("%d %s %s\n",countUnprocessed,Eclosure[i],copy);
            findNewstates(Eclosure[i],copy);
            countUnprocessed--;
            indexUnprocessed++;
        }
    }
}
void inputENFA()
{
    int i,j;

    printf("Enter the number of states : ");
    scanf("%d",&ns);
    printf("Enter the number of alphabets needed:");
    scanf("%d",&na);

    printf("\nStates : ");
    for(i=0;i<ns;i++)
        printf("%d ",i);
    printf("\nStart state: 0\nAlphabets:E ");
    for(i=0;i<na;i++)
        printf("%c ",'a'+i);

    //printf("\n\nEnter the number of final states:");
    //scanf("%d",&nf);
    printf("\nEnter the final states:");
    //for(i=0;i<nf;i++)
    scanf("%s",f);

    printf("\nComplete the transition table(Enter -1 if null):\n\tE");
    for(i=0;i<na;i++)
        printf("\t%c",'a'+i);
    printf("\n");
    for(i=0;i<ns;i++)
    {   printf("%d\t",i);
        for(j=0;j<=na;j++)
            scanf("%s",tdn[i][j]);
    }

    printf("\nTransition table of ENFA:\n\tE");
    for(i=0;i<na;i++)
        printf("\t%c",'a'+i);
    for(i=0;i<ns;i++)
    {   printf("\n%d\t",i);
        for(j=0;j<=na;j++)
            printf("%s\t",tdn[i][j]);
    }
    printf("\n");
}
int split(char buf[1000],char array[1000][1000])
{   int i = 0,j;
    char *p = strtok (buf, ",");

    while (p != NULL)
    {   strcpy(array[i++],p);
        p = strtok (NULL, ",");
    }

    /*for (j = 0; j < i; ++j)
        printf("%s\n", array[j]);*/
    return i;
}
void cleaning(char str[1000])
{   //"0,1,1,2" -> "0,1,2"//Remove repetitions and order it

    //Remove repetitions
    char array[1000][1000];
    int i,j;
    int n=split(str,array);//Array:{"0","1","1","2"}
    char newstr[1000];strcpy(newstr,"");
    for(i=0;i<n;i++)
    {   int found=0;
        for(j=0;j<i;j++)
        {   if(strcmp(array[j],array[i])==0)
            {   found=1;break;
            }
        }
        if(found==0)
        {   strcat(newstr,",");
            strcat(newstr,array[i]);
        }
    }
    //Order it
    n=split(newstr,array);
    for(i=0;i<n-1;i++)
    {   for(j=i+1;j<n;j++)
        {   if(strcmp(array[i],array[j])>0)
            {   char temp[10];
                strcpy(temp,array[i]);
                strcpy(array[i],array[j]);
                strcpy(array[j],temp);
            }
        }
    }
    //Copy unrepeated order sequence to the DFA
    strcpy(str,"");
    for(i=0;i<n;i++)
    {   if(strcmp(array[i],"-1")!=0)//dont concatenate null
        {   strcat(str,array[i]);
            if(i<n-1)
                strcat(str,",");
        }
    }
    if(strcmp(str,"")==0)//if null make it -1
        strcpy(str,"-1");
}
void outputEclosure()
{   int i;
    for(i=0;i<ns;i++)
        printf("Eclosure(%d)=%s\n",i,Eclosure[i]);
    printf("\n");
}
