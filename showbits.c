#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<regex.h>

void showbits(char*);

int main(int argc, char** argv)
{

	int i = 0, i_flag = 0;
	char* c_argv;
	if(argc < 2) {fprintf(stderr, "Usage: showbits [num] \n");exit(1);}
	c_argv = strdup(argv[1]);		
	showbits(c_argv);
	free(c_argv);	
	exit(0);
}

void showbits(char* c_argv)
{
	int status = 0, i = 0, i_bits = 0, i_flag = 0, n_flag = 0;
	int *a_bits, *a_bits_tmp;
	size_t s_long, s_long_bit;
    int d, j = 0;
	typedef unsigned char uc;
	uc* p;
	double f;

	regex_t compiled;
	regmatch_t matchptr;
    const char* c_pattern = "^[-]?[0-9]+[.]?[0-9]*[eE]?[+-]?[0-9]*$"; //匹配数字的正则表达式，正负整数和浮点数
    //c_pattern = "^3{3}$";
	if(regcomp(&compiled, c_pattern, REG_EXTENDED))
		{perror("regcomp");return;}

	if((status = regexec(&compiled, c_argv, 1, &matchptr, 0)))
		if(status == REG_NOMATCH){fprintf(stderr, "regexec error\n");return;}

	if(matchptr.rm_so != -1)

	while(c_argv[i] != '\0')
		{
	   /* if(((c_argv[i] < 48) || (c_argv[i] > 57)) && (c_argv[i] != '.') && (c_argv[i] != '-')) {fprintf(stderr, "Input num error!\n"); exit(1);} */
	   /* else if(c_argv[i] == '.') {if(i&&(!i_flag)) i_flag++; else {fprintf(stderr, "Input num error!!\n"); exit(1);}} */
	   /* else if(c_argv[i] == '-') {if(!i&&(!n_flag)&&(c_argv[1]!='.')) n_flag++; else {fprintf(stderr, "Input num error!!\n"); exit(1);}} */
			if(c_argv[i] == '.') i_flag++;
			i++;
        }
	else
		{fprintf(stderr, "Can not find number!\n");return;}
i = 0;
if(!i_flag)
	{
		s_long = sizeof(int);
		s_long_bit = s_long * 8;
        a_bits = malloc(sizeof(int) * s_long_bit);
		d = atoi(c_argv);
 		
		do
			{
				i_bits = d & 1;
				a_bits[i++] = i_bits;
				d >>= 1;
			} while(i < s_long_bit);

i = 1;
while(s_long_bit > 0) {printf("%d", a_bits[--s_long_bit]);if((i % 4) == 0) putchar(' ');i++;}

	}
else
	{
		s_long = sizeof(double);
		s_long_bit = s_long * 8;
        a_bits_tmp = a_bits = malloc(sizeof(int) * s_long_bit);
        f = atof(c_argv);
		p = (uc*) &f; 		
	
		for(i=0,j=0;j < s_long;j++,p++,i=0){
		while(i < 8)
			{
   
				i_bits = (*p & 0x80) / 0x80;
				*a_bits_tmp++ = i_bits;
				*p <<= 1;
                i++;

			} 

		}

		while(s_long_bit > 7){
		for(i=s_long_bit-8;i < s_long_bit;) { printf("%d", a_bits[i++]);if((i % 4) == 0) putchar(' '); }
		s_long_bit -= 8;
		}
	}
puts("");
regfree(&compiled);
free(a_bits);
return;
}
