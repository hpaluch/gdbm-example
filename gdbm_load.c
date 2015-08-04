#include<gdbm.h>

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static const char *DB_FILE = "words.gdbm";

int main(int argc, char ** argv){
	int count = 0;
	GDBM_FILE f;
	char buf[1024];



	f = gdbm_open( DB_FILE, 4096, GDBM_WRCREAT,0664,NULL );
	if ( f == NULL ){
		fprintf(stderr,"Unable to open '%s':%s\n",
			DB_FILE,gdbm_strerror(gdbm_errno));
		return EXIT_FAILURE;
	}

	while (fgets(buf,sizeof(buf)-1,stdin)!=NULL ){
		datum key,val;

		char *nl = strrchr(buf,'\n');
		if ( nl != NULL ){ *nl = '\0'; }
		nl = strrchr(buf,'\r');
		if ( nl != NULL ){ *nl = '\0'; }
		if ( strlen(buf) == 0 ){
			continue;
		}
		key.dptr = buf;
		key.dsize = strlen(buf)+1;
		val.dptr = "";
		val.dsize = strlen("")+1;

		if ( gdbm_store(f,key,val,GDBM_REPLACE) ){
			fprintf(stderr,"Error storing value %s\n",
				gdbm_strerror(gdbm_errno));
			gdbm_close (f);
			return EXIT_FAILURE;

		}
		count ++;
	}
	gdbm_close (f);
	printf("Stored %d entries into %s\n",count,DB_FILE);
	return EXIT_SUCCESS;
}
