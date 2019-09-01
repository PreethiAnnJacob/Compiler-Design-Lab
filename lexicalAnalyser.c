/*Design and implement a lexical analyzer for given language using C and the lexical
analyzer should ignore redundant spaces, tabs and new lines.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int blank(char *w)
{	int i;
	if(strlen(w)==0)
		return 1;
	for(i=0;i<strlen(w);i++)
	{	if(w[i]!=' ' && w[i]!='\t' && w[i]!='\n')
			return 0;
	}
	return 1;
}
int main(int argc,char * argv[])
{   if(argc<2)
        return 1;
	
    //Read filename from args
    char *filename=argv[1];
    FILE *fp=fopen(filename,"r");
    if(fp==NULL)
            return 1;

    FILE *fp2=fopen("ans.txt","w");
    if(fp2==NULL)
            return 1;
	char keyword[10][10]={"int","float","printf","main"};
	int kl=4;
    char c;

    //Word creation
    char *w=(char*)malloc(500*sizeof(char));
    w[0]='\0';int wi=0;

    char word[100];strcpy(word,"");

    //Flags
    int checkcom=0,singleComment=0,multipleComment=0,starAfterMultipleComment=0,preprocessor=0,checkString=0;

    while((c=fgetc(fp))!=EOF)
    {   //printf("%c",c);

        //Handling single line and multiple line comments
        if(singleComment==1)
        {   if(c=='\n') singleComment=0;
            continue;
        }
        if(multipleComment==1)
        {   if(starAfterMultipleComment==1 && c=='/')
            {   multipleComment=0;starAfterMultipleComment=0;}
            if(c=='*') starAfterMultipleComment=1;
            else
                starAfterMultipleComment=0;
            continue;
        }
        if(c=='/')
        {   if (checkcom==0) checkcom=1;
            else
            {   singleComment=1;
                checkcom=0;
            }
        }
        else if(checkcom==1)
        {   if(c=='*'){multipleComment=1;checkcom=0;}
            else
            {   fprintf(fp2,"/ - operator\n");
                if(c!='\n'||c!=' '||c!='\t')w[wi++]=c;
            }
        }
        else if(c=='"')
		{   if(checkString==0)
			{	w[wi++]=c;
				checkString=1;
			}
			else
			{   w[wi++]=c;
				w[wi++]='\0';
				if(blank(w)==0)fprintf(fp2,"%s - literal\n",w);
				w[0]='\0';wi=0;
				checkString=0;
			}
		}
		else if(checkString==1)
		{   w[wi++]=c;
		}
        else if(preprocessor==1)
        {   if(strcmp(word,"#define")!=0 && (c==' ' || c=='<'))
            {   w[wi++]='\0';
                if(blank(w)==0)fprintf(fp2,"%s - preprocessor directive\n",w);
                strcpy(word,w);
                w[0]='\0';wi=0;
            }
            else if(c=='>')
            {   w[wi++]='\0';
                fprintf(fp2,"%s - header file\n",w);

                w[0]='\0';wi=0;
                preprocessor=0;
                strcpy(word,"");
            }
            else if(c=='\n')
            {   w[wi++]='\0';
                fprintf(fp2,"%s - constant\n",w);
                w[0]='\0';wi=0;
                preprocessor=0;
                strcpy(word,"");
            }
            else if(c==' '||c=='\t')
            {   w[wi++]='\0';
                fprintf(fp2,"%s - identifier\n",w);

                w[0]='\0';wi=0;
            }
            else
            {   w[wi++]=c;
            }
        }
        else if(c=='#')
        {   preprocessor=1;w[wi++]=c;
        }
        else if(c=='+'||c=='-'||c=='/'||c=='*'||c=='<'||c=='>'||c=='=')
        {   w[wi++]='\0';
            if(blank(w)==0)fprintf(fp2,"%s",w);
            //check if constant
			int i;
			for(i=0;i<strlen(w);i++)
			{	if(!((w[i]>='0' && w[i]<='9')||w[i]=='.'))
				{	break;
				}
			}
			if (i==strlen(w))
			{	if(blank(w)==0)fprintf(fp2," - constant\n");
			}
			else
			{	//check if keyword
				int i;
				for(i=0;i<kl;i++)
				{	if(strcmp(keyword[i],w)==0)
						break;
				}
				if(i<kl)
				{	fprintf(fp2," - keyword\n");
				}
				else //check if identifier
				{	if(w[0]>='0' && w[0]<='9')
						fprintf(fp2," - invalid identifier\n");
					else
					{	int i;
						for(i=1;i<strlen(w);i++)
						{	if(!((w[i]>='0' && w[i]<='9')||(w[i]>='A' && w[i]<='Z')||(w[i]>='a'&&w[i]<='z')||w[i]=='_'||w[i]=='$'))
							{	break;
							}
						}
						if(i==strlen(w))
						{	fprintf(fp2," - identifier\n");
						}
						else
						{	fprintf(fp2," - invalid identifier\n");
						}
					}
				}
			}
			w[0]='\0';wi=0;
			
			fprintf(fp2,"%c - operator\n",c);
        }
        else if(c==' '||c=='\t'||c=='\n'||c==';'||c==','||c=='('||c==')')
        {   w[wi++]='\0';
            if(blank(w)==0)if(blank(w)==0)fprintf(fp2,"%s ",w);

			//check if constant
			int i;
			for(i=0;i<strlen(w);i++)
			{	if(!((w[i]>='0' && w[i]<='9')||w[i]=='.'))
				{	break;
				}
			}
			if (i==strlen(w))
			{	fprintf(fp2," - constant\n");
			}
			else
			{	//check if keyword
				int i;
				for(i=0;i<kl;i++)
				{	if(strcmp(keyword[i],w)==0)
						break;
				}
				if(i<kl)
				{	fprintf(fp2," - keyword\n");
				}
				else //check if identifier
				{	if(w[0]>='0' && w[0]<='9')
					{	fprintf(fp2," - invalid identifier\n");
					}
					else
					{	int i;
						for(i=1;i<strlen(w);i++)
						{	if(!((w[i]>='0' && w[i]<='9')||(w[i]>='A' && w[i]<='Z')||(w[i]>='a'&&w[i]<='z')||w[i]=='_'||w[i]=='$'))
							{	break;
							}
						}
						if(i==strlen(w))
						{	fprintf(fp2," - identifier\n");
						}
						else
						{	fprintf(fp2," - invalid identifier\n");
						}
					}
				}
			}

			if(c!=' ' && c!='\t' &&c!='\n')
				fprintf(fp2,"%c - special character\n",c);
            w[0]='\0';wi=0;
        }
        else
        {   w[wi++]=c;
        }
       
    }
    w[wi++]='\0';
    if(wi>1)printf("Written to ans.txt\n");
    return 0;
}
