/*Implement the back end of the compiler which takes the three address code and produces the 8086 assembly language instructions that can be assembled and run
using an 8086 assembler. The target assembly instructions can be simple move, add,sub, jump etc.
*/

#include <stdio.h>
#include <string.h>

int n;
char tac[10][10];

void input3AC();
void CodeGen();

int main()
{   input3AC();
    CodeGen();
    return 0;
}
void input3AC()
{   printf("Enter the number of lines:");
    scanf("%d",&n);
    printf("Enter %d 3AC codes:\n",n);
    int i;
    for(i=0;i<n;i++)
        scanf("%s",tac[i]);
}
void CodeGen()
{   char op[3];
    int i;
    printf("\nCode generated:\n\n");
    for(i=0;i<n;i++)
    {   int l=strlen(tac[i]);
        if(l==5)
        {   printf("MOV AL,%c\n",tac[i][2]);
            printf("MOV AH,%c\n",tac[i][4]);
            if(tac[i][3]=='+') strcpy(op,"ADD");
            else if(tac[i][3]=='-') strcpy(op,"SUB");
            else if(tac[i][3]=='*') strcpy(op,"MUL");
            else if(tac[i][3]=='/') strcpy(op,"DIV");
            else strcpy(op,"");
            printf("%s AL,AH\n",op);
            printf("MOV %c,AL\n",tac[i][0]);
        }
        else//copy instruction
        {   printf("MOV AL,%c\n",tac[i][2]);
            printf("MOV %c,AL\n",tac[i][0]);
        }
        printf("\n");
        //printf("%d",i);
    }
    printf("HLT\n");
}
/*char registers[8][2];
strcpy(registers[0],"AL");
strcpy(registers[1],"AH");
strcpy(registers[2],"BL");
strcpy(registers[3],"BH");
strcpy(registers[4],"CL");
strcpy(registers[5],"CH");
strcpy(registers[6],"DL");
strcpy(registers[7],"DH");
int r=0;int nr=8;*/
/*r=(r+1)%nr;int r1=r;
printf("MOV %s,%c\n",registers[r1],tac[i][2]);
r=(r+1)%nr;int r2=r;
printf("MOV %s,%c\n",registers[r2],tac[i][4]);*/
/*printf("%s %s,%s\n",op,registers[r1],registers[r2]);
printf("MOV %c,%s\n",tac[i][0],registers[r1]);*/
/*r=(r+1)%nr;int r1=r;
printf("MOV %s,%c\n",registers[r1],tac[i][2]);
printf("MOV %c,%s\n",tac[i][0],registers[r1]);*/

/*
Enter the number of lines:5
Enter 5 3AC codes:
a=b+c
d=e
f=g*h
i=j/k
l=m-n

Code generated:

MOV AL,b
MOV AH,c
ADD AL,AH
MOV a,AL

MOV AL,e
MOV d,AL

MOV AL,g
MOV AH,h
MUL AL,AH
MOV f,AL

MOV AL,j
MOV AH,k
DIV AL,AH
MOV i,AL

MOV AL,m
MOV AH,n
SUB AL,AH
MOV l,AL

HLT

Process returned 0 (0x0)   execution time : 31.246 s
Press any key to continue.

*/
