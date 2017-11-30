/*
*Program for multiplying two large numbers.
*Incoming parameters from the files test1.txt and test2.txt.
*The result is output to a file result.txt.
*Implemented standard multiplication algorithm.
*/

#include <stdio.h>
//#include <stdlib.h> //malloc    

void multiply(unsigned short w[], unsigned short u[], unsigned short v[], int m, int n);

int main(void)
{
	int ch, m, n;
	FILE * fp1, * fp2, * fp3;
	m = 0;
	n = 0;

	fp1 = fopen("test1.txt", "r");
	while (( ch = getc(fp1)) != EOF )
	{
		/* '\032' end-of-file marker in text files DOS*/
		/* 3. \r - carriage return, it is necessary to check the file*/
		if (ch == '\n')
		{
			--m;
		}
		++m;
	}
	fp2 = fopen("test2.txt", "r");
	while (( ch = getc(fp2)) != EOF )
	{
		if (ch == '\n')
		{
			--n;
		}
		++n;
	}
	
	unsigned short result[m+n];//Result, no more than numbers m+n
	unsigned short x[m];
	unsigned short y[n];

	/*
	unsigned short * result;
	unsigned short * x;
	unsigned short * y;
	result = (unsigned short *) malloc ((m+n) * sizeof(unsigned short));
	x = (unsigned short *) malloc (m * sizeof(unsigned short));
	y = (unsigned short *) malloc (n * sizeof(unsigned short)); 
	free(result);
	free(x);
	free(y);
	*/

	fseek(fp1, 0L, SEEK_SET);//Go to the beginning of the file after counting the number of characters
	for (int i = 0; (ch = getc(fp1)) != EOF; ++i )
	{
		x[m - 1 - i] = ch - '0';
	}

	fseek(fp2, 0L, SEEK_SET);
	for (int i = 0; (ch = getc(fp2)) != EOF; ++i )
	{
		y[n - 1 - i] = ch - '0';
	}

	multiply(result, x, y, m, n);

	fp3 = fopen("t3.txt", "w");

	//Delete the last zero in the array (if any)
	int i = m+n-1;
	if ( result[i] == 0)
	{
		--i;
	}
	while ( i >= 0 )
	{
		putc(result[i] + '0', fp3);
		--i;
	}

	if ( fclose(fp1) != 0 )
		printf( " Error closing file \n") ;
	if ( fclose(fp2) != 0 )
		printf( " Error closing file \n") ;
	if ( fclose(fp3) != 0 )
		printf( " Error closing file \n") ;
	return 0;
}

void multiply(unsigned short w[], unsigned short u[], unsigned short v[], int m, int n) 
{
   	unsigned int t;

   	for (int i = 0; i < m+n; i++)
	{	
		w[i] = 0;	
  	}
	for (int j = 0; j < n; j++)
	{
      	for (int i = 0; i < m; i++)
      	{
         	t = u[i] * v[j] + w[i + j];
        	w[i + j] = t;         
      	}
    }
    for (int i = 0; i < m+n ; ++i)
	{
   	 	w[i + 1] +=  w[i] / 10;
    	w[i] %= 10;
	}	
}