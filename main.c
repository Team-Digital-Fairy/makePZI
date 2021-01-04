#include "pzi.h"
#include <stdio.h>
#include <argp.h>
#include <stdlib.h>
#include <string.h>

void print_usage() {
	printf("makepzi <command> <pzi file> [data]\n");
}


int main(int argc, char* argv[]) {
	FILE *f;

	printf("DBG: hdr_pcm_data sz %ld (%lx)\n",sizeof(hdr_pcm_data),sizeof(hdr_pcm_data));
	printf("DBG: pzi_data sz %ld (%lx)\n",sizeof(pzi_data),sizeof(pzi_data));

	if(argc < 2) {
		print_usage();
		return 0;
	}
	
	// TODO: Optimize this selection mechanism for selecting which functions
	if(!strcmp(argv[1],"i")) {
		f = fopen(argv[2],"rb");
		if(f == NULL) { print_usage(); return -1; }
		pzi_data *pd = malloc(sizeof(pzi_data));
		memset(pd,0,sizeof(pzi_data)); 
		fread(pd,sizeof(pzi_data),1,f);
		fclose(f);
		for(int i=0; i<128; i++ ) {
		printf("%03d %08X %08X %08X %08X %6d\n",i,
				pd->pcmdata[i].startaddr,
				pd->pcmdata[i].size,
				pd->pcmdata[i].loop_start,
				pd->pcmdata[i].loop_end,
				pd->pcmdata[i].freq
			);
		}
		free(pd);
	}
	if(!strcmp(argv[1],"a")) { // Append requires three arguments
		if(argc < 4) {
			printf("Usage: a <pzi file> <file to append>\n");
			return -2;
		}
		FILE *append_file;
		
		f = fopen(argv[2],"rb");
		if(f == NULL) {
			printf("File Open Error, is filename correct?\n");
			return -3;
		}
		append_file = fopen(argv[3],"rb");
		if(append_file == NULL) {
			printf("File Open Error, is filename correct?\n");
			return -3;
		}
		pzi_data *pd = malloc(sizeof(pzi_data));
		memset(pd,0,sizeof(pzi_data));
		fread(pd,sizeof(pzi_data),1,f);
		fclose(f);

		fseek(append_file, 0L, SEEK_END);
		uint64_t fsz = ftell(append_file);
		rewind(append_file);
		
		printf("DBG: filesize: %ld",fsz);

		// Find Next Empty thing. probably better to seek that
		// Loop point is 0
		// End address is 0
		



		
	}

}
