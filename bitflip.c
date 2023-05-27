//Eduardo Aparicio Jaime
//PID 5645176
//This is my work
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void writeToFile(FILE* output,u_int16_t val)
{
	fprintf(output,"%u\n",val);
}
void printToScreen(u_int16_t n)
{
	printf("%d/n",n);
}

int flipEven(u_int16_t n)
{
	u_int16_t result = 0;
	u_int16_t counter = 0;

	for (u_int16_t i = n; i > 0; i >>=1)
	{
		if(counter % 2 == 1 )
		{
			result |= (1 << counter);
		}
		counter++;
	}
	return n ^ result;
}

int flipOdd(u_int16_t n)
{
	u_int16_t result = 0;
        u_int16_t counter = 0;

        for (u_int16_t i = n; i > 0; i >>=1)
        {
                if(counter % 2 == 0 )
                {
                        result |= (1 << counter);
                }
                counter++;
        }
        return n ^ result;

}

int flipAll(u_int16_t n)
{
	return ~n;
}

int switchLeftRight(u_int16_t n)
{
	u_int16_t ltr = 0;

	ltr = ltr >> n;

//	for (u_int16_t i = 0; i < 16 ;i ++)
//	{
//		ltr >> i;
//	}
	return ltr;
}
int main(int argc, char **argv)
{
	FILE* outputFile;
	extern char *optarg;
	extern int optind;
	int c,err = 0;
	u_int16_t intval;
	u_int16_t even;
        u_int16_t odd;
        u_int16_t all;
        u_int16_t ltr;

	int eflag = 0, fflag = 0, aflag = 0 ,sflag = 0, oflag = 0;;
	char* outputFileName = NULL;
	static char usage[] = "usage: bitflip [-e] [-f] [-a] [-s] [-o outputfilename] intval\n";

	while(( c = getopt(argc, argv, "efaso:")) != -1)
		switch(c)
		{
			case 'e':
				eflag = 1;
		
				// flip all even bits
				break;
			case 'f':
                                fflag = 1;
				// Flip all odd bits
                                break;
			case 'a':
                                aflag = 1;
				// Flip all bits
                                break;
			case 's':
                                sflag = 1;
				//switch them from right to left
                                break;
			case 'o':
                                oflag = 1;
				outputFileName = optarg;
                                break;

			case '?':
				err = 1;
				break;
		}

	if(argv[optind] == NULL)
	{
		printf("silly boy you need to input an int value\n");
		printf("%s",usage);
		exit(1);
	}

	intval = atoi(argv[optind]);
	printf("Value:  %d\n",intval);
	
	

	if(outputFileName != NULL)
	{
		if(!(outputFile = fopen(outputFileName,"w")))
		{
			printf("no output file\n");
			exit(1);		
		}	
		else
		{
			fprintf(outputFile,"Value: ");
			writeToFile(outputFile,intval);
			if(eflag == 1)
			{
				even = flipEven(intval);
				fprintf(outputFile,"Even bits flipped: ");
				writeToFile(outputFile,even);
			}
			if(fflag == 1)
                        {
				odd = flipOdd(intval);
				fprintf(outputFile,"Odd bits flipped: ");
                                writeToFile(outputFile,odd);
                        }
			if(aflag == 1)
                        {
				all = flipAll(intval);
				fprintf(outputFile,"All bits flipped: ");
                                writeToFile(outputFile,all);
                        }
			if(sflag == 1)
                        {
				ltr = switchLeftRight(intval);
				fprintf(outputFile,"Switched all bits: ");
                                writeToFile(outputFile,ltr);
                        }

		}
		fclose(outputFile);
	}
	else
	{
		if(eflag == 1)
        	{
                	even = flipEven(intval);
                	printf("Even bits flipped: %d\n",even);
        	}
        	if(fflag == 1)
        	{
                	odd = flipOdd(intval);
                	printf("Odd bits flipped: %d\n",odd);
        	}
        	if(aflag == 1)
        	{
             		all = flipAll(intval);
               		printf("All bits flipped %u\n",all);
        	}
        	if(sflag == 1)
        	{
              		ltr = switchLeftRight(intval);
              		printf("Switched all bits: %d\n",ltr);
        	}
	}

	return 0;
}
