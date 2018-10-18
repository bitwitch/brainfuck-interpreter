#include <stdio.h> 

int main(int argc, char** argv) 
{
	// memory
	int MEMORY_MAX = 30000;
	int memory[MEMORY_MAX];
	int *ptr = memory;

	// initialize memory
	for(int i=0; i<MEMORY_MAX; i++)
		memory[i] = 0;

	printf("brainfuck\n");

	int c; 
	while ( (c = getchar()) != EOF ) 
	{
		switch(c) 
		{	
			case '+': ++*ptr; break;
			case '-': --*ptr; break;
			case '>': ++ptr; break;
			case '<': --ptr; break;
			case '.': putchar(*ptr); break;
				// if (*ptr >= 32 && *ptr <= 126) {
				// 	printf("%c", *ptr);
				// } else {
				// 	printf("%i", *ptr);
				// }
				// break;
			case '[':    
				if (*ptr == 0) {
					// jump to closing bracket
					while( (c = getchar()) != ']')
						;
				} 
				break;
				
			case ']':    
				if (*ptr == 0) {
					// jump to opening bracket
				} 
				break;
			default: 
				break;
		}
	}
		
	putchar('\n'); 


	return 0; 
}
