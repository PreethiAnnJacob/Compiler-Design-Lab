#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int split(char [1000],char [1000][1000]);//function to split string to array
void cleaning(char [1000]);
void checkNewstate(char [1000]);
void findFinalStatesOfDFA(char [1000][1000]);
void inputNFA();
void NFAtoDFA();
void outputDFA();
int ns,na;//int nf;//no of states, alphabets, no of final states in NFA
char f[10];//Set of final states of NFA
char tdn[10][10][10];//Transition diagram of NFA
char qd[10][10];//Set of states of DFA
char tdd[10][10][10];//transition diagram of DFA
int nsd;//nsd tracks number of states in DFA
int noOfNewstates=0;//no of new states of DFA
char fd[1000][1000];//final states of DFA
int main ()
{   inputNFA();
    NFAtoDFA();
    outputDFA();
    return 0;
}
void NFAtoDFA()
{   //qd[][] stores the set of states in DFA
    //tdd[][][] - array of strings for transition diagram of DFA
    //nsd tracks number of states in DFA
    //newstate track the index from which all states of DFA are unprocessed in DFA
    //add 0 to qd. update newstate=0.
    /* while(newstate)
    {   split qd[newstate] to different states of NFA into arr1[][]
        for each alphabet
        {   for each state in arr1
                concatenate tdn[state][alphabet] into tdd[newstate][alphabet]
            cleaning(tdd[newstate][alphabet])
            check if newstate?
        }
    }
    */

    //add 0 to qd. update newstate=0.
    strcpy(qd[0],"0");
    nsd=1;
    int newstate=0;//newstate track the index from which all states of DFA are unprocessed in DFA
    noOfNewstates=1;
    char arr[1000][1000];

    while(noOfNewstates>0)
    {   char str[1000];strcpy(str,qd[newstate]);
        int nsi=split(str,arr);//no of states of NFA inside one state of DFA
        strcpy(tdd[newstate][0],qd[newstate]);//printf("\nQD:");int k;for(k=0;k<nsd;k++)    printf("%s ",qd[k]);printf("\n");
        int i;
        for(i=0;i<na;i++)
        {   strcpy(tdd[newstate][i+1],"");
            int j;
            for(j=0;j<nsi;j++)
            {   strcat(tdd[newstate][i+1],",");
                strcat(tdd[newstate][i+1],tdn[atoi(arr[j])][i]);
            }
            //printf("\nDFA before cleaning%d:\n",nsd);outputDFA();
            cleaning(tdd[newstate][i+1]);//printf("\nDFA after cleaning%d:\n",nsd);outputDFA();
            checkNewstate(tdd[newstate][i+1]);//printf("\nQD:");for(k=0;k<nsd;k++)    printf("%s ",qd[k]);printf("\n");printf("\nDFA after newstate%d:\n",nsd);outputDFA();
        }
        noOfNewstates--;
        newstate++;
        //printf("\nnofoNewstates=%d\nindexOfnewstate=%d\n",noOfNewstates,newstate);
    }
}
void checkNewstate(char str[1000])
{   int found=0;
    int i;
    for(i=0;i<nsd;i++)
    {   found=0;
        if(strcmp(str,qd[i])==0)
        {   found=1;
            break;
        }
    }
    if(found==0)
    {   strcpy(qd[nsd++],str);
        /*printf("\nQD:");
        for(i=0;i<nsd;i++)
            printf("%s ",qd[i]);
        printf("\nNewstate:%s\n",str);
        printf("nsd:%d\n",nsd);*/
        noOfNewstates++;//printf("noOfNewstates:%d\n",noOfNewstates);
    }
}
void findFinalStatesOfDFA(char fd[1000][1000])
{   char array1[1000][1000];
    char array2[1000][1000];char str[1000];
    int i,j,k;int l=0;int flag=0;

    int n1=split(f,array1);//printf("FN");for(x=0;x<n1;x++)printf("%s ",array1[x]);printf("\n");
    //for each qd,check if at least one final state in NFA is in that state of DFA
    for(i=0;i<nsd;i++)
    {   //now qd[i] has one DFA state
        strcpy(str,qd[i]);
        int n2=split(str,array2);//printf("QD:");for(x=0;x<n2;x++)printf("%s ",array2[x]);printf("\n");
        for(j=0;j<n2;j++)
        {   for(k=0;k<n1;k++)
            {   if(strcmp(array2[j],array1[k])==0)
                {   strcpy(fd[l++],qd[i]);flag=1;
                }
            }
            if(flag==1)
            {   flag=0;
                break;
            }
        }
    }
    for(i=0;i<l;i++)
        printf("%s ",fd[i]);
    printf("\n");
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
void inputNFA()
{
    int i,j;

    printf("Enter the number of states : ");
    scanf("%d",&ns);
    printf("Enter the number of alphabets needed:");
    scanf("%d",&na);

    printf("\nStates : ");
    for(i=0;i<ns;i++)
        printf("%d ",i);
    printf("\nStart state: 0\nAlphabets:");
    for(i=0;i<na;i++)
        printf("%c ",'a'+i);

    //printf("\n\nEnter the number of final states:");
    //scanf("%d",&nf);
    printf("Enter the final states:");
    //for(i=0;i<nf;i++)
    scanf("%s",f);

    printf("\nComplete the transition table(Enter -1 if null):\n");
    for(i=0;i<na;i++)
        printf("\t%c",'a'+i);
    printf("\n");
    for(i=0;i<ns;i++)
    {   printf("%d\t",i);
        for(j=0;j<na;j++)
            scanf("%s",tdn[i][j]);
    }

    printf("\nTransition table of NFA:\n");
    for(i=0;i<na;i++)
        printf("\t%c",'a'+i);
    for(i=0;i<ns;i++)
    {   printf("\n%d\t",i);
        for(j=0;j<na;j++)
            printf("%s\t",tdn[i][j]);
    }
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

void outputDFA()
{   int i,j;
    printf("\nTransition table of DFA:\n");
    for(i=0;i<na;i++)
        printf("\t%c",'a'+i);
    for(i=0;i<nsd;i++)
    {   printf("\n");
        for(j=0;j<=na;j++)
            printf("%s\t",tdd[i][j]);
    }

    printf("\nStates of DFA:");
    for(i=0;i<nsd;i++)
        printf("%s ",qd[i]);
    printf("\nAlphabets used: ");
    for(i=0;i<na;i++)
        printf("%c ",'a'+i);
    printf("\nFinal states of DFA:");
    findFinalStatesOfDFA(fd);
}
