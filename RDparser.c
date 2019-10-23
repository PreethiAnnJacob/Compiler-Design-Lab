/*Preethi Ann Jacob - RDParser
Construct a Recursive Descent Parser for an expression
E->E+T|T
T->T*F|F
F->(E)|id
Your program will first check whether a grammar is left recursive is not. If it is left recursive, eliminate left recursion and implement RD parser.

Grammar without left recursion
E->TE'
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char str[100],grammar[100][100],v[100],t[100];//String to be parsed,grammar
int lookahead,nv,nt,np;
void removeLeftRecursion();
int find(char str[],char ch);
void inputGrammar();
void substring(char str[],char ch, char ans[]);
void RDParser();
void E();void Edash();void F();void T();void Tdash();
int main()
{   inputGrammar();
	removeLeftRecursion();
    printf("Enter the string to be parsed:");
    scanf("%s",str);//input string to be parsed
    RDParser();
    return 0;
}
void inputGrammar()
{   int i;
    /*printf("Enter the number of variables and terminals:");
    scanf("%d%d",&nv, &nt);*/
	printf("Enter the number of variables:");
	scanf("%d",&nv);
    /*printf("Enter the terminals:");
    scanf("%s",t);*/
    printf("Enter the variables:");
    scanf("%s",v);
    printf("Enter the number of productions:");
    scanf("%d",&np);
    printf("Enter the grammar:\n");
    for(i=0;i<np;i++)
        scanf("%s",grammar[i]);
}
int find(char str[],char ch)
{   int i;
    for(i=0;i<strlen(str);i++)
    {   if(str[i]==ch)
            return i;
    }
    return -1;
}
void substring(char str[],char ch, char ans[])
{   int i;
    for(i=0;i<strlen(str);i++)
    {   if(str[i]==ch)
            break;
    }
    int indexans=0;
    for(i=i+1;i<=strlen(str);i++)
        ans[indexans++]=str[i];
	ans[indexans]='\0';
}
void removeLeftRecursion()
{   int i,j,nnp=0,nonLeftRecursive[100],leftRecursive[100];
	char newgrammar[100][100];
    for(i=0;i<nv;i++)//for each variable
    {   int noOfProdOfThisVariable=0,ilr=0,inlr=0;
		for(j=0;j<np;j++)
        {   if(grammar[j][0]==v[i])//lhs= current variable
            {   //grammarOfThisVariable[index++]=j;
                noOfProdOfThisVariable++;
                if(grammar[j][find(grammar[j],'>')+1]==v[i])//there is left recursion
                    leftRecursive[ilr++]=j;
                else
                    nonLeftRecursive[inlr++]=j;
            }
		}
        if(noOfProdOfThisVariable==0)
        	strcpy(newgrammar[nnp++],grammar[j]);
		else if(ilr==0)
		{	int k;
			for(k=0;k<inlr;k++)
				strcpy(newgrammar[nnp++],grammar[nonLeftRecursive[k]]);
		}
        else
        {
			int k;
			for(k=0;k<inlr;k++)
            {   char str[100];
                str[0]=v[i];str[1]='\0';
                strcat(str,"->");
                char ans[100];substring(grammar[nonLeftRecursive[k]],'>',ans);//printf("Ans:%s\n",ans);
                strcat(str,ans);str[strlen(str)]=v[i];str[strlen(str)+1]='\0';//printf("Ans:%s\n",ans);
                strcat(str,"'");//printf("str:%s\n",str);
                strcpy(newgrammar[nnp++],str);
            }
            for(k=0;k<ilr;k++)
            {   char str[100];str[0]=v[i];str[1]='\0';
                char ans[100],ans2[100];
				strcat(str,"'->");	substring(grammar[leftRecursive[k]],v[i],ans);//printf("Ans:%s\n",ans);
				substring(ans,v[i],ans2);//printf("Ans2:%s\n",ans2);
				ans2[strlen(ans2)]=v[i];ans2[strlen(ans2)+1]='\0';//printf("Ans2:%s\n",ans2);
            	strcat(ans2,"'");//printf("Ans2:%s\n",ans2);
				strcat(str,ans2);
            	strcpy(newgrammar[nnp++],str);
            }
			char str[100];
            str[0]=v[i];str[1]='\0';
            strcat(str,"'->epsilon");
            strcpy(newgrammar[nnp++],str);
        }

		/*printf("%c:::\n",v[i]);
			int k=0;printf("Left:");for(k=0;k<ilr;k++) printf("%d ",leftRecursive[k]);
			printf("\nNonleft:");for(k=0;k<inlr;k++) printf("%d ",nonLeftRecursive[k]);printf("\n");*/
    }
	printf("\nGrammar without left recursion:\n");
	for(i=0;i<nnp;i++)
		printf("%s\n",newgrammar[i]);
}
void RDParser()
{   lookahead=0;
    E();
    if (str[lookahead]=='\0')//End of string
        printf("Successfully parsed\n");
	else printf("Error\n");
}
void E()
{   T();Edash();
}
void Edash()
{   if(str[lookahead]=='+')
    {   lookahead++;
        T();Edash();
    }
    else
        return;
}
void T()
{   F();Tdash();
}
void Tdash()
{   if(str[lookahead]=='*')
    {   lookahead++;
        F();
        Tdash();
    }
    else return;
}
void F()
{   if(str[lookahead]=='(')
    {   lookahead++;
        E();
        if(str[lookahead]==')')
            lookahead++;
        else
        {   if(('a'<=str[lookahead] && str[lookahead]<='z') || ('A'<=str[lookahead] && str[lookahead]<='Z'))//id
                lookahead++;

        else
            {printf("Error\n");exit(0);}
        }
    }
    else
    {   if(('a'<=str[lookahead] && str[lookahead]<='z') || ('A'<=str[lookahead] && str[lookahead]<='Z'))//id
            lookahead++;
        else
            {printf("Error\n");exit(0);}
    }
}
/*Enter the number of variables:3
Enter the variables:ETF
Enter the number of productions:6
Enter the grammar:
E->E+T
E->T
T->T*F
T->F
F->(E)
F->I

Grammar without left recursion:
E->TE'
E'->+TE'
E'->epsilon
T->FT'
T'->*FT'
T'->epsilon
F->(E)
F->I
Enter the string to be parsed:A+B*(C+d)
Successfully parsed

Process returned 0 (0x0)   execution time : 48.663 s
Press any key to continue.
*/
