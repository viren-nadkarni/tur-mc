/* 
 * File:   main.c
 * Author: viren
 *
 * Created on November 1, 2012, 9:53 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* a turing machine emulator
 * 
 * the inbuilt transtition table is for finding the factorial of 'n'
 */

#define SZ 124					//the number of rows in transition table
#define TP_SZ 64				//the length of the tape, important

#define Left -1
#define Right 1
#define True 35
#define False 43
#define Halt 104

/* the transition table values are stored in an integer array
 * int		stateNumber
 * char		read
 * char		write
 * int		nextState
 * int		direction
 * 
 * 104='h' (halt)
 * 043='+' (tape symbol false/blank)
 * 035='#' (tape symbol true)
 * 
 * -1=go left
 * +1=go right
 *  0=no change
 */

int table[SZ][5]={
	0,False,False,1,Right,
	1,True,True,2,Right,
	1,False,False,56,0,
	2,False,False,12,Left,
	2,True,False,3,Right,
	3,True,True,3,Right,
	3,False,False,4,Right,
	4,True,True,3,Right,
	4,False,True,5,Left,
	5,False,False,6,Left,
	5,True,True,5,Left,
	6,False,True,7,Right,
	6,True,True,6,Left,
	7,False,False,1,Right,
	7,True,False,8,Right,
	8,False,False,9,Right,
	8,True,True,8,Right,
	9,False,True,5,Left,
	9,True,True,9,Right,
	10,True,True,10,Right,
	10,False,False,11,Right,
	11,True,True,11,Right,
	11,False,False,6,Left,
	12,True,False,13,Left,
	12,False,False,14,Left,
	13,True,True,13,Left,
	13,False,False,14,Left,
	14,False,False,15,Right,
	14,True,True,13,Left,
	15,False,False,31,Right,
	15,True,True,31,0,
	31,False,False,98,Right,
	31,True,False,16,Right,
	16,False,False,17,Right,
	16,True,True,16,Right,
	17,False,False,98,Left,
	17,True,False,18,Right,
	18,False,False,19,Right,
	18,True,True,18,Right,
	19,False,False,20,0,
	19,True,True,18,Right,
	20,False,True,21,Left,
	20,True,True,20,Right,
	21,False,False,44,Left,
	21,True,True,21,Left,
	44,False,False,22,Left,
	44,True,True,21,Left,
	22,False,False,23,Right,
	22,True,True,21,Left,
	23,False,False,45,Right,
	45,False,False,24,Right,
	24,False,False,25,Right,
	24,True,True,24,Right,
	25,False,True,40,Right,
	25,True,True,25,Right,
	26,False,False,27,Left,
	26,True,True,26,Left,
	27,False,False,29,Right,
	27,True,True,28,Left,
	28,False,False,15,Right,
	28,True,True,28,Left,
	29,False,False,29,Right,
	29,True,False,30,Right,
	30,False,False,Halt,Left,
	30,True,False,30,Right,
	40,False,False,50,0,
	40,True,False,41,Right,
	41,False,False,42,Right,
	41,True,True,41,Right,
	42,False,False,43,Left,
	42,True,True,41,Right,
	43,False,True,21,Left,
	50,True,False,51,Left,
	50,False,False,52,Left,
	51,True,True,51,Left,
	51,False,False,52,Left,
	52,False,False,53,Right,
	52,True,True,51,Left,
	53,False,False,62,Right,
	62,True,True,63,Right,
	63,False,False,64,Left,
	63,True,True,54,Left,
	64,False,False,64,Right,
	64,True,False,65,Right,
	65,False,False,66,Right,
	66,False,False,90,Right,
	66,True,True,90,Right,
	90,False,False,91,Left,
	90,True,True,67,Left,
	67,True,False,68,Right,
	68,False,False,69,Right,
	68,True,True,68,Right,
	69,False,False,70,Left,
	69,True,True,68,Right,
	70,False,True,71,Left,
	71,False,False,72,Left,
	71,True,True,71,Left,
	72,False,False,73,Right,
	72,True,True,71,Left,
	73,False,False,66,Right,
	91,True,False,92,Right,
	92,False,False,93,Right,
	92,True,True,92,Right,
	93,False,False,94,Left,
	93,True,True,92,Right,
	94,False,True,95,Left,
	95,False,False,96,Left,
	95,True,True,95,Left,
	96,False,False,97,Right,
	96,True,True,95,Left,
	97,False,False,15,Right,
	98,False,True,Halt,Right,
	54,False,False,15,Right,
	54,True,False,55,Right,
	55,False,False,56,Right,
	55,True,True,55,Right,
	56,False,False,Halt,Right,
	56,True,False,57,Right,
	57,False,False,58,Right,
	57,True,True,57,Right,
	58,False,False,59,Left,
	58,True,True,57,Right,
	59,False,True,21,Left,
	59,True,True,60,Right
};

int main(int argc, char** argv) 
{
	int tape[TP_SZ],i,j;
	for(i=0;i<TP_SZ;++i)
		tape[i]=False;
		
	int currentState=0,read,step=0,tapeHead=1;
	
	//put value of 'n' in bits here
	//do not change following bits
	tape[0]=False;
	tape[1]=False;
	//following bits may be changed
	tape[2]=True;
	tape[3]=True;
	tape[4]=True;
//	tape[5]=True;
	
	printf("\nInitial tape:\n");
	for(i=0;i<TP_SZ;++i)
		printf("%c",tape[i]);
	printf("\n\n\n\n");
		
	while(currentState!=Halt)
	{
		for(j=0;j<SZ;++j)
		{
			if(currentState==table[j][0] && tape[tapeHead]==table[j][1])
			{
				tape[tapeHead]=table[j][2];
				tapeHead+=table[j][4];
				currentState=table[j][3];
				break;
			}			
		}
		
		for(i=0;i<TP_SZ;++i)
			printf("%c",tape[i]);
		printf("\n");
		
		for(i=0;i<TP_SZ;++i)
		{
			if(i==tapeHead)
				printf("^");
			else 
				printf(" ");
		}
		
		printf("  (%d)\t%d  %c  %c  %d  %d",step,table[j][0],table[j][1],
			 table[j][2], table[j][3], table[j][4]);
		printf("\n");
		
		step++;
	}
	
	printf("\n\n\nFinal tape:\n");
	for(i=0;i<TP_SZ;++i)
		printf("%c",tape[i]);
	printf("\nTotal steps: %d",step-1);
	
	return (EXIT_SUCCESS);
}


