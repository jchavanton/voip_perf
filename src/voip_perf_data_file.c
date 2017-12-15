#include "data_file.h"

static int df_open(input_file_t *in) {
	in->fd = fopen(in->fn.ptr, "r");
	if (in->fd == NULL) {
		printf("[%s][ERROR] cannot not open data file [%s]\n", __FILE__, in->fn.ptr);
		return 0;
	}
}

char* df_get_line(input_file_t *in, input_file_record_t *rec) {
	pj_str_t l = { NULL, 0 };
	memset(rec, 0, sizeof(input_file_record_t));
	if (!in) {
		printf("[%s][ERROR] input_file not initialized\n", __FILE__);
		return NULL;
	}
	if (!in->fn.ptr) {
		printf("[%s][ERROR] file name not set\n", __FILE__);
		return NULL;
	}
	if (!in->fd) {
		if (!df_open(in))
			return NULL;
	}
	size_t len = 0;
	if ((l.slen = getline(&l.ptr, &len, in->fd)) != -1) {
		int idx=0;
		while (idx<l.slen) {
			if (l.ptr[idx] == ',' || l.ptr[idx] == '\n') {
				rec->calledid.ptr=l.ptr;
				rec->calledid.slen=idx;
		//printf("callerid[%.*s]", (int)rec->calledid.slen, rec->calledid.ptr);
				idx++;
				break;
			}
			idx++;
		}
		int tmp=idx;
		while (idx<l.slen) {
			if (l.ptr[idx] == ',' || l.ptr[idx] == '\n') {
				rec->callerid.ptr=&l.ptr[tmp];
				rec->callerid.slen=idx-tmp-1;
		//printf("calledid[%.*s]", (int)rec->callerid.slen, rec->callerid.ptr);
				break;
			}
			idx++;
		}
		return l.ptr;
	} else {
		printf("[%s] EOF\n", __FILE__);
		fclose(in->fd);
		return NULL;
	}
}



//	while ((read = getline(&line, &len, fp)) != -1) {
//		if (!process_line(line, read))
//			return 0;
//	}
//	fclose(fp);
//	if (line)
//		free(line);
//	return 1;
