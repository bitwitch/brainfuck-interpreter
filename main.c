#include <stdio.h> 

// filecopy: copy file ifp to file ofp
void filecopy(FILE *ifp, FILE *ofp)
{
	int c; 
	while ((c = getc(ifp)) != EOF)
		putc(c, ofp); 
}

int main(int argc, char** argv)
{
	// memory
	int MEMORY_MAX = 30000;
	int CODE_MAX = 30000;
	int memory[MEMORY_MAX];
	char code[CODE_MAX];
	int *ptr = memory;
	int c, i, loop;

	// initialize memory and bracket stack
	for(int i=0; i<MEMORY_MAX; i++) {
		memory[i]  = 0;
	}

	printf("brainfuck\n");

	// if command line argument
	if (argc > 1) {
		char* fname = argv[1];
		FILE* fp = fopen(fname, "r");
		if (fp == NULL) {
			printf("Error: cannot open file %s\n", argv[1]);
			return 1;
		}
		
		// parse the file to strip whitespace and bullshit
		for (i = 0; (c = getc(fp)) != EOF; ) {
			if (c == '+' || c == '-' || c == '>' || c == '<' || 
				c == '.' || c == ',' || c == '[' || c == ']')
			{
				code[i++] = c;	
			}
		}
        
		fclose(fp);
		code[i] = '\0';

	} else { 
		// read brainfuck program from stdin 
		fgets(code, CODE_MAX, stdin);	
	}
	
	// interpret the program
	for (i = 0; code[i] != 0; i++) {
		char c = code[i];
		switch(c) {	
			case '+': ++*ptr; break;
			case '-': --*ptr; break;
			case '>': ++ptr; break;	
			case '<': --ptr; break;
			case '.': putchar(*ptr); break;
			case '[':  
				if (*ptr == 0) {
					// jump to matching ] 
					loop = 1; 
					while (loop > 0) { 
						c = code[++i]; 
						if (c == '[') { 
							loop++; 
						} else if (c == ']') { 
							loop--; 
						} 
					} 
				} 
				break;	
			case ']':
				if (*ptr != 0) {   
					loop = 1;
					while (loop > 0) {
						c = code[--i];
						if (c == '[') {
							loop--;
						} else if (c == ']') {
							loop++;
						}
					}
				}
				break;
			default: 
				break;
		}
	}
		
	putchar('\n'); 
	return 0;
}
