//Preethi Ann Jacob
//Implement Intermediate code generation for simple expressions.3 Address Code

#include <stdio.h>
#include <string.h>

char infix[30];
char operators[7];
char postfix[10];
char icg[30][10];

void inputProgram();
void findPostfix();
void intermediateCodeGeneration();

int main()
{   inputProgram();
    findPostfix();
    intermediateCodeGeneration();
    return 0;
}
void inputProgram()
{   printf("Enter the input expression:\n");
    scanf("%s",infix);//scanf("%[^\t]",inputPgm);
    strcpy(operators,"=-+*/");//array of operators in the increasing order of precedence
}
int precedence(char ch)
{   int i;
    for(i=0;i<strlen(operators);i++)
        if(operators[i]==ch)
            return i;
    return -1;
}
void findPostfix()
{   int i;
    int npostfix=0;
    char stack[30];
    strcpy(stack,"");
    for(i=0;i<strlen(infix);i++)
    {   if( ('a'<=infix[i] && infix[i]<='z') | ('A'<=infix[i] && infix[i]<='Z') )//operand
        {   //printf("operand:%d\n",i);
            postfix[npostfix++]=infix[i];//add operand to postfix output
        }
        else if(infix[i]==')')
        {   while(stack[strlen(stack)-1]!='(')
            {   postfix[npostfix++]=stack[strlen(stack)-1];postfix[npostfix]='\0';
                stack[strlen(stack)-1]='\0';
            }
            stack[strlen(stack)-1]='\0';// thus remove ( from stack
        }
        else
        {   if( (infix[i]=='(') | (strcmp(stack,"")==0) | (precedence(stack[strlen(stack)-1]) < precedence(infix[i]) ) ) // if stack empty OR if precedence of operator on top of stack < operator in infix
            {   int l=strlen(stack);
                stack[l]=infix[i];//Push operator in infix to stack
                stack[l+1]='\0';//printf("%d Size of stack:%d\n",i,strlen(stack));
            }
            else
            {   //Pop to output until stack empty or precedence(top)<precedence(operator we are looking)
                while(1)
                {   if(stack[strlen(stack)-1]=='(')
                    {   break;
                    }
                    else
                    {   postfix[npostfix++]=stack[strlen(stack)-1];postfix[npostfix]='\0';
                        stack[strlen(stack)-1]='\0';
                        if( (strcmp(stack,"")==0) | ( precedence(stack[strlen(stack)-1]) < precedence(infix[i]) ) )
                            break;
                    }
                }
                int l=strlen(stack);
                stack[l]=infix[i];//Push operator in infix to stack
                stack[l+1]='\0';
            }
        }
        //printf("%s\t%d\t%s\n",stack,i,postfix);
    }
    //empty the stack
    while(strcmp(stack,"")!=0)
    {   postfix[npostfix++]=stack[strlen(stack)-1];postfix[npostfix]='\0';
        stack[strlen(stack)-1]='\0';
    }
    postfix[npostfix]='\0';
    //printf("Postfix : %s\n",postfix);
}
int isOperator(char ch)
{   int i;
    for(i=0;i<strlen(operators);i++)
    {   if(operators[i]==ch)
            return 1;
    }
    return 0;
}
void intermediateCodeGeneration()
{   /*
    ntemp=0;char temp='A';
    Input is postfix expression :  eg. eabc+d*-=
    take copy of postfix in pfcopy
    scan from left to right of pfcopy using i
        if(operator found at i)
            char currentTemp='A'+ntemp;ntemp++;
            copy to the next line of icg[][]:"currenttemp=pfcopy[i-2]+pfcopy[i]+pfcopy[i-1]"
            replace op[i-2]op[i-1]op[i] with currentTemp in pfcopy
    */
    int ntemp=0;
    int nicg=0;
    char pfcopy[30];strcpy(pfcopy,postfix);
    int i;
    for(i=0;i<strlen(pfcopy);i++)
    {   if(isOperator(pfcopy[i]))
        {   char temp='A'+ntemp++;

            //make intermediate code
            if(pfcopy[i]=='=')
            {   icg[nicg][0]=pfcopy[i-2];
                icg[nicg][1]='=';
                icg[nicg][2]=pfcopy[i-1];
                icg[nicg][3]='\0';
                nicg++;
            }
            else
            {   icg[nicg][0]=temp;
                icg[nicg][1]='=';
                icg[nicg][2]=pfcopy[i-2];
                icg[nicg][3]=pfcopy[i];
                icg[nicg][4]=pfcopy[i-1];
                icg[nicg][5]='\0';
                nicg++;
            }

            //make changes in pfcopy postfix expression
            int j;
            pfcopy[i-2]=temp;
            for(j=i+1;j<=strlen(pfcopy);j++)
                pfcopy[j-2]=pfcopy[j];
            i=0;
        }
    }
    printf("Intermediate Code generated:\n");
    for(i=0;i<nicg;i++)
    {   printf("%s\n",icg[i]);
    }
}
/*
Enter the input expression:
a+(b/d+f*(e-c)-g)
Intermediate Code generated:
A=b/d
B=e-c
C=f*B
D=A+C
E=D-g
F=a+E
*/
