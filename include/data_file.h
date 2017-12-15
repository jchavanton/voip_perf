#ifndef DATA_FILE_H
#define DATA_FILE_H

#include <pj/types.h>
#include <stdio.h>
#include <string.h>

typedef struct input_file {
	pj_str_t fn;
	FILE *fd;
} input_file_t;

typedef struct input_file_record {
	pj_str_t callerid;
	pj_str_t calledid;
} input_file_record_t;

char* df_get_line(input_file_t*, input_file_record_t*);

#endif
