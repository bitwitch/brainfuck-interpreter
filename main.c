#include <stdio.h> 

/* filecopy: copy file ifp to file ofp */
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
	int memory[MEMORY_MAX];
	int *ptr = memory;
	int c;

	// initialize memory
	for(int i=0; i<MEMORY_MAX; i++)
		memory[i] = 0;

	printf("brainfuck\n");

	// if command line argument
	if (argc > 1) {
		char* fname = argv[1];
		FILE* fp = fopen(fname, "r");
		if (fp == NULL) {
			printf("Error: cannot open file %s\n", argv[1]);
			return 1;
		}

		FILE *code = tmpfile();
		if (code == NULL) { 
			puts("Unable to create temp file bf_program");
			return 1; 
		} 
	
		// parse the file to strip whitespace and bullshit
		while ((c = getc(fp)) != EOF) {
			if (c == '+' || c == '-' || c == '>' || c == '<' || 
				c == '.' || c == ','|| c == '[' || c == ']')
			{
				putc(c, code);
			}
		}

		fclose(fp);
		rewind(code);

		// parse the copied version of the program
		while ((c = fgetc(code)) != EOF) {
			switch(c) {	
				case '+': ++*ptr; break;
				case '-': --*ptr; break;
				case '>': ++ptr; break;	
				case '<': --ptr; break;
				case '.': putchar(*ptr); break;
				case '[':    
					if (*ptr == 0) {
						// jump to closing bracket
						while( (c = fgetc(code)) != ']') {
							if (c == EOF) {
								printf("Error: expected a closing ] but reached EOF\n");
								return 1; 
							}
						}
					} 
					break;
					
				case ']':    
					if (*ptr == 0) {
						// jump to opening bracket
						while ((c = fgetc(code)) != '[')
						{	
							fseek(code, -2, SEEK_CUR);
						}
					} 
					break;
				default: 
					break;
			}
		}

		return 0;

	} else { // no file given as argument

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
}
