//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.dep_declare.h"
//silver_chain_scope_end
//fdefine.json.c
void *wrapper_json_parse(const char *value);

void *wrapper_json_parse_file(const char *filepath);

void wrapper_json_delete(void *json);

//================================JSON SERIALIZATION================================
char *wrapper_json_print(const void *json);

char *wrapper_json_print_unformatted(const void *json);

int wrapper_json_save_file(const void *json, const char *filepath);

void wrapper_json_free_string(char *str);

//================================JSON CREATION================================
void *wrapper_json_create_object(void);

void *wrapper_json_create_array(void);

void *wrapper_json_create_string(const char *string);

void *wrapper_json_create_number(double num);

void *wrapper_json_create_bool(int boolean);

void *wrapper_json_create_null(void);

void *wrapper_json_duplicate(const void *item, int recurse);

//================================JSON OBJECT MANIPULATION================================
void *wrapper_json_get_object_item(const void *object, const char *key);

int wrapper_json_has_object_item(const void *object, const char *key);

int wrapper_json_add_item_to_object(void *object, const char *key, void *item);

int wrapper_json_delete_item_from_object(void *object, const char *key);

int wrapper_json_replace_item_in_object(void *object, const char *key, void *newitem);

void *wrapper_json_add_string_to_object(void *object, const char *key, const char *string);

void *wrapper_json_add_number_to_object(void *object, const char *key, double number);

void *wrapper_json_add_bool_to_object(void *object, const char *key, int boolean);

void *wrapper_json_add_null_to_object(void *object, const char *key);

void *wrapper_json_add_object_to_object(void *object, const char *key);

void *wrapper_json_add_array_to_object(void *object, const char *key);

//================================JSON ARRAY MANIPULATION================================
int wrapper_json_get_array_size(const void *array);

void *wrapper_json_get_array_item(const void *array, int index);

int wrapper_json_add_item_to_array(void *array, void *item);

int wrapper_json_insert_item_in_array(void *array, int index, void *item);

int wrapper_json_replace_item_in_array(void *array, int index, void *newitem);

void wrapper_json_delete_item_from_array(void *array, int index);

//================================JSON TYPE CHECKING================================
int wrapper_json_is_object(const void *item);

int wrapper_json_is_array(const void *item);

int wrapper_json_is_string(const void *item);

int wrapper_json_is_number(const void *item);

int wrapper_json_is_bool(const void *item);

int wrapper_json_is_null(const void *item);

int wrapper_json_is_true(const void *item);

int wrapper_json_is_false(const void *item);

//================================JSON VALUE GETTERS================================
char *wrapper_json_get_string_value(const void *item);

double wrapper_json_get_number_value(const void *item);

//================================JSON COMPARISON================================
int wrapper_json_compare(const void *a, const void *b, int case_sensitive);

//================================JSON ITERATION================================
void *wrapper_json_get_child(const void *item);

void *wrapper_json_get_next(const void *item);

const char *wrapper_json_get_key(const void *item);

int wrapper_json_get_object_size(const void *object);
//fdefine.asssets.c

const unsigned char *wrapper_get_asset_content(const char *path,long *size,int *is_binary);
void *wrapper_list_assets(const char *path);
//fdefine.https_client.c
void *wrapper_newhttpclient(const char *url);
void wrapper_httpclient_set_method(void *client,const char *method);
void wrapper_httpclient_set_max_redirections(void *client,int max_redirections);
void * wrapper_httpclient_fetch(void *client);
int wrapper_httpclient_response_get_status_code(void *response);

unsigned char * wrapper_httpclient_response_read_body(void *response,long *size);
long wrapper_httpclient_response_get_body_size(void *response);

int wrapper_httpclient_response_get_header_size(void *response);
void wrapper_httpclient_set_header(void *client, const char *key, const char *value);
void wrapper_httpclient_set_body(void *client, unsigned char *content, long size);
void wrapper_httpclient_free(void *client);

char *wrapper_httpclient_response_get_header_value_by_key(void *response, const char *key);
const char *wrapper_httpclient_response_get_header_key_by_index(void *response, int index);
const char *wrapper_httpclient_response_get_header_value_by_index(void *response, int index);

void wrapper_httpclient_response_free(void *response);//fdefine.time.c

#include <time.h>

long wrapper_get_unix_time(void) ;

int wrapper_get_random(void) ;

void wrapper_get_formatted_time(long timestamp, char *buf, int buf_size, const char *fmt) ;
//fdefine.io.c
unsigned char *wrapper_read_any(const char *path, long *size, int *is_binary);
char *wrapper_read_string(const char *path);
void wrapper_write_any(const char *path, const unsigned char *content, long size);

void wrapper_write_string(const char *path, const char *content);
void wrapper_delete_any(const char *path);
void wrapper_create_dir(const char *path);

int wrapper_file_exists(const char *path);
int wrapper_dir_exists(const char *path);

int wrapper_copy_any(const char *src, const char *dst);

int wrapper_move_any(const char *src, const char *dst);

void wrapper_append_string(const char *path, const char *content);

char *wrapper_concat_path(const char *path1, const char *path2);

void wrapper_delete_stringarray(void *array);
long wrapper_get_stringarray_size(void *array);
const char *wrapper_get_stringarray_item(void *array, int index);

void *wrapper_list_files(const char *path);
void *wrapper_list_dirs(const char *path);
void *wrapper_list_any(const char *path);
void *wrapper_list_files_recursively(const char *path);
void *wrapper_list_dirs_recursively(const char *path);
void *wrapper_list_any_recursively(const char *path);
char *wrapper_generate_sha(const unsigned char *data, long size);

char * wrapper_generate_cached_sha_from_file(const char *cache_path,const char *path);//fdefine.argv.c

const char *wrapper_get_arg_value(const void *argv,int index);
int wrapper_get_arg_count(const void *argv);

const char *wrapper_get_arg_flag_value(const void *argv,const char **flags,int total_flags,int index);

int wrapper_get_arg_flag_count(const void *argv,const char **flags,int total_flags);

appbool wrapper_has_arg_flag(const void *argv,const char **flags,int total_flags);//fdefine.server.c



const char *wrapper_get_server_route(const void *apprequest);
const char *wrapper_get_server_method(const void *apprequest);
//================================HEADERS================================
const char *wrapper_get_server_header(const void *apprequest, const char *key);

const char *wrapper_get_server_header_key(const void *apprequest, int index);

const char *wrapper_get_server_header_value(const void *apprequest, int index);

const char *wrapper_get_server_query_param(const void *apprequest, const char *key);

const char *wrapper_get_server_query_param_key(const void *apprequest, int index);

const char *wrapper_get_server_query_param_value(const void *apprequest, int index);

int wrapper_get_server_header_count(const void *apprequest);

int wrapper_get_server_query_param_count(const void *apprequest);

const unsigned char *wrapper_read_server_body(const void *apprequest, long size, long *read_size);
const void *wrapper_read_server_json(const void *apprequest, long size);

const void *wrapper_newappserverresponse();

void wrapper_setappserverresponse_header(void  *appserverresponse, const char *key, const char *value);

void wrapper_setappserverresponse_content(void *appserverresponse, const unsigned char *content, long content_size);

void wrapper_setappserverresponse_status_code(void*appserverresponse, int status_code);


const void  *wrapper_send_any(const unsigned char *content,long content_size,const char *content_type, int status_code);
const void *wrapper_send_text(const char *text,const char *content_type, int status_code);
const void *wrapper_send_file(const char *path,const char *content_type, int status_code);
const void *wrapper_send_json(const void *json, int status_code);



int wrapper_start_server(int port, const appserverresponse *(*handler)(appdeps *d, void *props), void *props, appbool single_process) ;

CwebHttpResponse *main_internal_server_firmware(CwebHttpRequest *request, int argc, char *argv[]) ;
//fdefine.std.c

int wrapper_snprintf(char *str, unsigned long size, const char *format, ...);

unsigned long wrapper_strlen(const char *s);

void *wrapper_malloc(unsigned long size);

void *wrapper_calloc(unsigned long num, unsigned long size);

void *wrapper_realloc(void *ptr, unsigned long size);

char *wrapper_strdup(const char *s);

void *wrapper_memcpy(void *dst, const void *src, unsigned long n);

void *wrapper_memset(void *s, int c, unsigned long n);

int wrapper_strncmp(const char *s1, const char *s2, unsigned long n);

int wrapper_memcmp(const void *s1, const void *s2, unsigned long n);//fdefine.text_stack.c


void *wrapper_new_text_stack(const char *text) ;

void wrapper_text_stack_append(void *text_stack, const char *text) ;

const char *wrapper_text_stack_text(void *text_stack) ;

void wrapper_text_stack_free(void *text_stack) ;

void wrapper_text_stack_restart(void *text_stack) ;

void *wrapper_text_stack_clone(void *text_stack) ;

void wrapper_text_stack_self_substr(void *text_stack, long starter, long end) ;

void wrapper_text_stack_self_pop(void *text_stack, long starter, long end) ;

void wrapper_text_stack_self_insert_at(void *text_stack, long point,
                                       const char *element) ;

void wrapper_text_stack_self_replace(void *text_stack, const char *element,
                                     const char *element_to_replace) ;

void wrapper_text_stack_self_replace_long(void *text_stack, const char *element,
                                          long element_to_replace) ;

void wrapper_text_stack_self_replace_double(void *text_stack,
                                            const char *element,
                                            double element_to_replace) ;

void wrapper_text_stack_self_lower(void *text_stack) ;

void wrapper_text_stack_self_upper(void *text_stack) ;

void wrapper_text_stack_self_captalize(void *text_stack) ;

void wrapper_text_stack_self_reverse(void *text_stack) ;

void wrapper_text_stack_self_trim(void *text_stack) ;

int wrapper_text_stack_starts_with(void *text_stack, const char *element) ;

int wrapper_text_stack_ends_with(void *text_stack, const char *element) ;

int wrapper_text_stack_equal(void *text_stack, const char *element) ;

int wrapper_text_stack_typeof_element(void *text_stack) ;

int wrapper_text_stack_is_a_num(void *text_stack) ;

const char *wrapper_text_stack_typeof_in_str(void *text_stack) ;

int wrapper_text_stack_parse_to_bool(void *text_stack) ;

long wrapper_text_stack_parse_to_integer(void *text_stack) ;

double wrapper_text_stack_parse_to_double(void *text_stack) ;

long wrapper_text_stack_index_of(void *text_stack, const char *element) ;

long wrapper_text_stack_index_of_char(void *text_stack, char element) ;
