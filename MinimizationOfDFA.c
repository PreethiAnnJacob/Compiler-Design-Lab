/*Minimization of DFA*/
#include <stdio.h>
#include <stdlib.h>
void inputDFA();//input DFA as a transition table(array of integers) with state and alphabets as integers
int findRowInPartition(int);
void createNewpartition(int,int,int);
void minimizeDFA();
void printDFA();
void printMinimizedDFA();
int ns,na,nf,nfm,np,td[10][10],tdm[10][10],p[10][10],fs[10],fsm[10];//no of states, no of alphabets,number of final states,number of final states in minimized DFA, number of partitions,transition table,transition table of minimized DFA,partition[row][state],final states of DFA, final states of minimized DFA
int main()
{
    inputDFA();
    minimizeDFA();
    printMinimizedDFA();
    return 0;
}
void inputDFA()//Input DFA. Handle transition table and partition P0
{   int s,a,f;//index for states,index for alphabets, for final states
    printf("Enter the number of states, alphabets, final states: ");
    scanf("%d%d%d",&ns,&na,&nf);
    printf("Fill the transition table:\n");
    for(a=0;a<na;a++)
        printf("\t%d",a);
    printf("\n");
    for(s=0;s<ns;s++)
    {   printf("%d\t",s);
        for(a=0;a<na;a++)
        {   scanf("%d",&td[s][a]);
        }
    }
    printf("\n");

    //Initialize partition table's first row
    np=2;
    for(s=0;s<ns;s++)
        p[0][s]=0;
    int temp,fsindex=0;
    printf("Enter the final states:");
    for(f=0;f<nf;f++)
    {   scanf("%d",&temp);
        p[0][temp]=1;
        fs[fsindex++]=temp;
    }
    for(s=0;s<ns;s++)
    {   if(p[0][s]==0)  p[1][s]=1;
        else    p[1][s]=0;
    }
}
void printDFA()
{   int s,a,r;//index for states,index for alphabets
    printf("Transition table : \n");
    for(a=0;a<na;a++)
        printf("\t%d",a);
    for(s=0;s<ns;s++)
    {   printf("\n%d\t",s);
        for(a=0;a<na;a++)
        {   printf("%d\t",td[s][a]);
        }
    }
    printf("\n");

    printf("Partition table:\n");
    for(s=0;s<ns;s++)
        printf("\t%d",s);
    printf("\n");
    for(r=0;r<np;r++)
    {   printf("%d\t",r);
        for(s=0;s<ns;s++)
        {   printf("%d\t",p[r][s]);
        }
        printf("\n");
    }
}
void printMinimizedDFA()
{   int s,a,r,i;//index for states,index for alphabets, random index
    printf("MINIMIZED DFA:\nTransition table : \n");
    for(a=0;a<na;a++)
        printf("\t%d",a);
    for(s=0;s<np;s++)
    {   printf("\n%d\t",s);
        for(a=0;a<na;a++)
        {   printf("%d\t",tdm[s][a]);
        }
    }
    printf("\n");

    nfm=0;
    for(r=0;r<np;r++)
    {   int foundfinal=0;
        printf("State %d merges the states ",r);
        for(s=0;s<ns;s++)
            if(p[r][s]==1)
            {   printf("%d ",s);
                //check if current state has a final state of DFA
                for(i=0;i<nf && foundfinal==0;i++)
                {   if(fs[i]==s)
                    {   fsm[nfm++]=r;foundfinal=1;
                    }
                }
            }
        printf("\n");
    }
    printf("Initial state:");
    for(r=0;r<np;r++)
        if(p[r][0]==1)
            printf("%d\n",r);
    printf("Final states:");
    for(i=0;i<nfm;i++)
        printf("%d ",fsm[i]);
    printf("\n");
}
int findRowInPartition(int state)
{   int r;
    for(r=0;r<np;r++)
            if(p[r][state]==1)
                return r;
    return -1;
}
void createNewpartition(int s, int st,int a)
{   for(s=0;s<ns;s++)
        p[np][s]=0;
    p[np][st]=1;
    p[findRowInPartition(td[st][a])][st]=0;
    np++;
}
void minimizeDFA()
{   int r,s,st,a;
    int distinguish=0;
    for(r=0;r<np;r++)
    {   for(s=0;s<ns;s++)
        {   if(p[r][s]==1)
            {   for(st=s+1;st<ns;st++)
                {   if(p[r][st]==1)
                    {   distinguish=0;
                        for(a=0;a<na;a++)
                        {   if(findRowInPartition(td[s][a])!=findRowInPartition(td[st][a]))
                            {   distinguish=1;
                                createNewpartition(s,st,a);
                                break;
                            }
                        }
                        if(distinguish==1)  break;
                    }
                    if(distinguish==1)  break;
                }
            }
            if(distinguish==1)break;
        }
        if(distinguish==1){distinguish=0;r=0;}
    }
    //Now we get the partitions
    //Make merged transition table for minimized DFA
    for(s=0;s<np;s++)
    {   for(a=0;a<na;a++)
        {   //find any value i n the row s in partition table
            for(st=0;st<ns;st++)
            {   if(p[s][st]==1)
                    break;//st gets the value
            }
            tdm[s][a]=findRowInPartition(td[st][a]);
        }
    }
}
/*
Enter the number of states, alphabets, final states: 6 2 3
Fill the transition table:
        0       1
0       3       1
1       2       5
2       2       5
3       0       4
4       2       5
5       5       5

Enter the final states:1 2 4
MINIMIZED DFA:
Transition table :
        0       1
0       0       2
1       1       0
2       2       2
State 0 merges the states 1 2 4
State 1 merges the states 0 3
State 2 merges the states 5
Initial state:1
Final states:0

Process returned 0 (0x0)   execution time : 36.427 s
Press any key to continue.

*/
