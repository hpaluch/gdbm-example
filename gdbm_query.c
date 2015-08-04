#include<gdbm.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static const char *DB_FILE = "words.gdbm";

int main(int argc, char ** argv){
	GDBM_FILE f;
	char buf[1024];

	f = gdbm_open( DB_FILE, 4096, GDBM_READER,0,NULL );
	if ( f == NULL ){
		fprintf(stderr,"Unable to open '%s':%s\n",
			DB_FILE,gdbm_strerror(gdbm_errno));
		return EXIT_FAILURE;
	}

	printf("Enter word to search in %s\nEmpty line to quit\n",DB_FILE);
	while (fgets(buf,sizeof(buf)-1,stdin)!=NULL ){
		datum key,content;

		char *nl = strrchr(buf,'\n');
		if ( nl != NULL ){ *nl = '\0'; }
		nl = strrchr(buf,'\r');
		if ( nl != NULL ){ *nl = '\0'; }
		if ( strlen(buf) == 0 ){
			break;
		}
		key.dptr = buf;
		key.dsize = strlen(buf)+1;

		content = gdbm_fetch(f,key);
		if ( content.dptr != NULL ){
			printf("OK, word '%s' found\n",buf);
			free(content.dptr); content.dptr = NULL;
		} else {
			printf("ERROR, word '%s' not found\n",buf);
		}

	}
	gdbm_close (f);
	return EXIT_SUCCESS;
}
