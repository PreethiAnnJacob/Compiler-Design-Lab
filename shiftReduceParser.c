//shift reduce parser for E->E+E|E*E|(E)|id
#include <stdio.h>
#include <string.h>
char input[10];
char grammar[10][10];
char stack[10];

void push(char ch,char stack[10]);
void removeFirstChar(char str[10]);
void replaceLast(int lengthRHS,char prod[]);
void initialization();
void SRparse();

int main()
{   initialization();
    SRparse();
    return 0;
}
void initialization()
{   strcpy(grammar[0],"E->E+E");
    strcpy(grammar[1],"E->E*E");
    strcpy(grammar[2],"E->(E)");
    strcpy(grammar[3],"E->i");
    printf("Input string: ");
    scanf("%s",input);
    strcpy(stack,"$");
}
void SRparse()
{   printf("Stack\t\tInput\t\tAction\n");
    int condn=0;
    while(!(strcmp(stack,"$E")==0 && strcmp(input,"")==0) && condn==0)
    {   int i;
        int x=strlen(stack)-1;
        int reductionPossible=-1;
        for(i=0;i<4;i++)
        {   int j;
            reductionPossible=1;
            x=strlen(stack)-1;
            for(j=strlen(grammar[i])-1;j>=3;j--)
            {   if(grammar[i][j]==stack[x])
                {   x--;
                }
                else
                {   reductionPossible=0;
                    break;
                }
            }
            if(reductionPossible==1)
            {   printf("%s\t\t%s\t\tReduce by %s\n",stack,input,grammar[i]);
                int lengthRHS=strlen(grammar[i])-3;
                replaceLast(lengthRHS,grammar[i]);
                break;
            }
        }
        if(reductionPossible!=1 && strcmp(input,"")==0)
            condn=1;
        if(reductionPossible!=1)
        {   printf("%s\t\t%s\t\tShift\n",stack,input);
            push(input[0],stack);
            removeFirstChar(input);
        }
    }
    if(strcmp(stack,"$E")==0 && strcmp(input,"")==0 )
        printf("%s\t\t%s\t\tAccepted\n",stack,input);
    else printf("%s\t\t%s\t\tNot Accepted\n",stack,input);
}
void push(char ch,char str[10])
{   int l=strlen(str);
    str[l]=ch;
    str[l+1]='\0';
}
void removeFirstChar(char str[10])
{   int i;
    int l=strlen(str);
    for(i=1;i<=l;i++)
        str[i-1]=str[i];
}
void replaceLast(int lengthRHS,char prod[])
{
    stack[strlen(stack)-lengthRHS]=prod[0];
    stack[strlen(stack)-lengthRHS+1]='\0';
}
/*
Input string: i*(i+i)
Stack           Input           Action
$               i*(i+i)         Shift
$i              *(i+i)          Reduce by E->i
$E              *(i+i)          Shift
$E*             (i+i)           Shift
$E*(            i+i)            Shift
$E*(i           +i)             Reduce by E->i
$E*(E           +i)             Shift
$E*(E+          i)              Shift
$E*(E+i         )               Reduce by E->i
$E*(E+E         )               Reduce by E->E+E
$E*(E           )               Shift
$E*(E)                          Reduce by E->(E)
$E*E                            Reduce by E->E*E
$E                              Accepted
*/
