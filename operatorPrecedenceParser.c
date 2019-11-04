//Preethi Ann Jacob
/*Develop an operator precedence parser for a given language for the grammar
E->E+T|T
T->T*F|F
F->(E)|id
First construct operator precedence parsing table and using the parsing table, perform parsing of an input string
*/

#include <stdio.h>
#include <string.h>

char t[10],v[10],grammar[10][10];//terminals,variables,array of productions
int np,nv,nt;//no of productions,variables,terminals
char leading[10][10],trailing[10][10];//leading and trailing of all variables
char opPrecTable[10][10];//Operator precedence table

int isTerminal(char ch);
int isVariable(char ch);
int charNotPresentInString(char ch,char str[10]);
int indexInVariables(char ch);
int indexInTerminals(char ch);
void appendCharToString(char ch,char str[10]);
void concatStringsWithoutRepetition(char str1[10],char str2[10]);
void displayString();

void inputGrammar();
int isOperatorGrammar();
void findLeading();
void printLeading();
void findTrailing();
void printTrailing();
void createOperatorPrecedenceTable();
void printOperatorPrecedenceTable();

int main()
{
    inputGrammar();
    int check=isOperatorGrammar();
    if(check==0)
        printf("Sorry.Only operator grammar can be parsed.\n");
    else
    {   printf("Given grammar is operator grammar.\n");
    }
    findLeading();
    printLeading();
    findTrailing();
    printTrailing();
    createOperatorPrecedenceTable();
    printOperatorPrecedenceTable();
    return 0;
}
void inputGrammar()
{
    strcpy(t,"+*()i");//Declaring terminals
    strcpy(v,"ETF");//declaring variables
    nt=5;nv=3;np=6;//no of terminals and no of variables and no of productions

    //Declaring the productions
    strcpy(grammar[0],"E->E+T");
    strcpy(grammar[1],"E->T");
    strcpy(grammar[2],"T->T*F");
    strcpy(grammar[3],"T->F");
    strcpy(grammar[4],"F->(E)");
    strcpy(grammar[5],"F->i");
}
int isOperatorGrammar()
{   /*Check if any epsilon production is there*/
    int i;
    for(i=0;i<np;i++)
        if(grammar[i][3]=='e')
            return 0;
    return 1;
}
void findLeading()
{   /*1.leading(A)={a} if A->YaD where Y=e or a single non-terminal*/
    int i;
    for(i=0;i<np;i++)
    {   if  (   isTerminal(grammar[i][3]) || //if A->aD OR
                (   isTerminal(grammar[i][4]) && //a is a terminal in A->YaD and
                    (grammar[i][3]=='e' || isVariable(grammar[i][3])) //Yis e or terminal
                )
            )
        {   char terminal;
            if(isTerminal(grammar[i][3]))
                terminal=grammar[i][3];
            else
                terminal=grammar[i][4];
            int indexA=indexInVariables(grammar[i][0]);//index of A
            appendCharToString(terminal,leading[indexA]);// append terminal a to leading[A] if not already present
        }
    }

    /*2.if A->BY where B is a variable, leading (A)= leading(B)*/
    int j;
    for(j=0;j<np;j++)//Repeat np times the following body to repeat checking for second condition
    {   for(i=0;i<np;i++)
        {   if  (   grammar[i][3]!=grammar[i][0] && //B!=A to avoid leading[A]=leading[B]
                    isVariable(grammar[i][3])
                )
            {   int indexA=indexInVariables(grammar[i][0]);
                int indexB=indexInVariables(grammar[i][3]);
                concatStringsWithoutRepetition(leading[indexA],leading[indexB]);
            }
        }
    }
}
void findTrailing()
{   /*1.Trailing(A)=a if A->YaD where D is epsilon or single nonterminal*/
    int i;
    for(i=0;i<np;i++)
    {   int length=strlen(grammar[i]);
        if  (   isTerminal(grammar[i][length-1]) || //If A->Ya OR
                (   isTerminal(grammar[i][length-2]) && // In if A->YaD, a is a terminal AND
                    ( grammar[i][length-1]=='e' || isVariable(grammar[i][length-1]) ) // D is epsilon or variable
                )
            )
        {   int terminal;
            if(isTerminal(grammar[i][length-1]))
                terminal=grammar[i][length-1];
            else
                terminal=grammar[i][length-2];
            int indexA=indexInVariables(grammar[i][0]);//index of A
            appendCharToString(terminal,trailing[indexA]);// append terminal a to trailing[A] if not already present
        }
    }
    /*2.If A->YB then trailing(A)=trailing(B) where B is a variable*/
    int j;
    for(j=0;j<np;j++)//Repeat np times the following body to repeat checking for second condition
    {   for(i=0;i<np;i++)
        {   int length=strlen(grammar[i]);
            if  (   grammar[i][length-1]!=grammar[i][0] && //B!=A to avoid leading[A]=leading[B]
                    isVariable(grammar[i][length-1])
                )
            {   int indexA=indexInVariables(grammar[i][0]);
                int indexB=indexInVariables(grammar[i][length-1]);
                concatStringsWithoutRepetition(trailing[indexA],trailing[indexB]);
            }
        }
    }
}
void createOperatorPrecedenceTable()
{   int i,j;
    for(j=0;j<np;j++)//for each production A->X1X2...Xn
    {   int length=strlen(grammar[j]);
        for(i=0;i<=length-2;i++)//for X=1 to X=-n-1
        {   if(isTerminal(grammar[j][i]) && isTerminal(grammar[j][i+1])) //if Xi and X i+1 are terminals
            {   int indexR=indexInTerminals(grammar[j][i]);
                int indexC=indexInTerminals(grammar[j][i+1]);
                opPrecTable[indexR][indexC]='=';//Xi = Xi+1
            }
            if( i<=length-3 && isTerminal(grammar[j][i]) && isTerminal(grammar[j][i+2]) && isVariable(grammar[j][i+1]) )//i<=n-2 and Xi Xi+2 are terminals and Xi+1 is a variable
            {   int indexR=indexInTerminals(grammar[j][i]);
                int indexC=indexInTerminals(grammar[j][i+2]);
                opPrecTable[indexR][indexC]='=';//Xi = Xi+2
            }
            if ( isTerminal(grammar[j][i]) && isVariable(grammar[j][i+1]) )//Xi is terminal and Xi+1 is variable
            {   //for all a in leading(Xi+1) Xi<a
                int k;
                int index=indexInVariables(grammar[j][i+1]);// index of Xi+1
                for(k=0;k<strlen(leading[index]);k++)
                {   int indexR=indexInTerminals(grammar[j][i]);
                    int indexC=indexInTerminals(leading[index][k]);
                    opPrecTable[indexR][indexC]='<';//Xi = Xi+2
                }
            }
            if( isVariable(grammar[j][i]) && isTerminal(grammar[j][i+1]) )//Xi variable and Xi+1 Terminal
            {   //for all a in trailing(Xi) set a>Xi+1
                int k;
                int index=indexInVariables(grammar[j][i]);// index of Xi
                for(k=0;k<strlen(leading[index]);k++)
                {   int indexR=indexInTerminals(trailing[index][k]);
                    int indexC=indexInTerminals(grammar[j][i+1]);
                    opPrecTable[indexR][indexC]='>';//Xi = Xi+2
                }
            }
        }
    }
    /*Handling $*/
    //Set $<a for all a in leading(S)
    for(i=0;i<strlen(leading[0]);i++)// 0 is index of starting symbol
    {   int indexR=nt;//index of $
        int indexC=indexInTerminals(leading[0][i]);//index of a
        opPrecTable[indexR][indexC]='<';
    }
    //Set b>$ for all b in trailing (S)
    for(i=0;i<strlen(trailing[0]);i++)// 0 is index of starting symbol
    {   int indexR=indexInTerminals(trailing[0][i]);//index of b
        int indexC=nt;//index of $
        opPrecTable[indexR][indexC]='>';
    }
}
int isTerminal(char ch)
{   int i;
    for(i=0;i<nt;i++)
    {   if (t[i]==ch)
            return 1;
    }
    return 0;
}
int isVariable(char ch)
{   int i;
    for(i=0;i<nv;i++)
    {   if (v[i]==ch)
            return 1;
    }
    return 0;
}
int indexInVariables(char ch)//position of variable in the variable[]
{   int i;
    for(i=0;i<nv;i++)
    {   if(v[i]==ch)
            return i;
    }
    return -1;
}
int indexInTerminals(char ch)//position of variable in the variable[]
{   int i;
    for(i=0;i<nt;i++)
    {   if(t[i]==ch)
            return i;
    }
    return -1;
}
int charNotPresentInString(char ch,char str[10])
{   int i;
    for(i=0;i<strlen(str);i++)
    {   if(ch==str[i])
            return 0;
    }
    return 1;
}
void appendCharToString(char ch,char str[10])
{   if(charNotPresentInString(ch,str))
    {   int length=strlen(str);
        str[length]=ch;
        str[length+1]='\0';
    }
}
void concatStringsWithoutRepetition(char str1[10],char str2[10])
{   int l2=strlen(str2);
    int i;
    for(i=0;i<l2;i++)
        appendCharToString(str2[i],str1);
}
void displayString(char str[10])
{   printf("{ ");
    int i;
    for(i=0;i<strlen(str);i++)
        printf("%c ",str[i]);
    printf("}\n");
}
void printLeading()
{   int i;
    printf("\n");
    for(i=0;i<nv;i++)
    {   printf("Leading[%c]=",v[i]);
        displayString(leading[i]);
    }
}
void printTrailing()
{   int i;
    printf("\n");
    for(i=0;i<nv;i++)
    {   printf("Trailing[%c]=",v[i]);
        displayString(trailing[i]);
    }
}
void printOperatorPrecedenceTable()
{   int i,j;
    printf("\nOperator Precedence Table:\n");
    for(i=0;i<nt;i++)
        printf("\t%c",t[i]);
    printf("\t$\n");
    for(i=0;i<=nt;i++)
    {   if(i==nt)
            printf("$\t");
        else
            printf("%c\t",t[i]);
        for(j=0;j<=nt;j++)
            printf("%c\t",opPrecTable[i][j]);
        printf("\n");
    }
}
/*
Given grammar is operator grammar.

Leading[E]={ + * ( i }
Leading[T]={ * ( i }
Leading[F]={ ( i }

Trailing[E]={ + * ) i }
Trailing[T]={ * ) i }
Trailing[F]={ ) i }

Operator Precedence Table:
        +       *       (       )       i       $
+       >       <       <       >       <       >
*       >       >       <       >       <       >
(       <       <       <       =       <
)       >       >               >               >
i       >       >               >               >
$       <       <       <               <
*/
