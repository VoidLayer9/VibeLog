//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.dep_declare.h"
//silver_chain_scope_end
//fdefine.json.c
void *wrapper_json_parse(void *ctx, const char *value) ;

void *wrapper_json_parse_file(void *ctx, const char *filepath) ;

void wrapper_json_delete(void *ctx, void *json) ;

//================================JSON SERIALIZATION================================
char *wrapper_json_print(void *ctx, const void *json) ;

char *wrapper_json_print_unformatted(void *ctx, const void *json) ;

int wrapper_json_save_file(void *ctx, const void *json, const char *filepath) ;

void wrapper_json_free_string(void *ctx, char *str) ;

//================================JSON CREATION================================
void *wrapper_json_create_object(void *ctx) ;

void *wrapper_json_create_array(void *ctx) ;

void *wrapper_json_create_string(void *ctx, const char *string) ;

void *wrapper_json_create_number(void *ctx, double num) ;

void *wrapper_json_create_bool(void *ctx, int boolean) ;

void *wrapper_json_create_null(void *ctx) ;

void *wrapper_json_duplicate(void *ctx, const void *item, int recurse) ;

//================================JSON OBJECT MANIPULATION================================
void *wrapper_json_get_object_item(void *ctx, const void *object, const char *key) ;

int wrapper_json_has_object_item(void *ctx, const void *object, const char *key) ;

int wrapper_json_add_item_to_object(void *ctx, void *object, const char *key, void *item) ;

int wrapper_json_delete_item_from_object(void *ctx, void *object, const char *key) ;

int wrapper_json_replace_item_in_object(void *ctx, void *object, const char *key, void *newitem) ;

void *wrapper_json_add_string_to_object(void *ctx, void *object, const char *key, const char *string) ;

void *wrapper_json_add_number_to_object(void *ctx, void *object, const char *key, double number) ;

void *wrapper_json_add_bool_to_object(void *ctx, void *object, const char *key, int boolean) ;

void *wrapper_json_add_null_to_object(void *ctx, void *object, const char *key) ;

void *wrapper_json_add_object_to_object(void *ctx, void *object, const char *key) ;

void *wrapper_json_add_array_to_object(void *ctx, void *object, const char *key) ;

//================================JSON ARRAY MANIPULATION================================
int wrapper_json_get_array_size(void *ctx, const void *array) ;

void *wrapper_json_get_array_item(void *ctx, const void *array, int index) ;

int wrapper_json_add_item_to_array(void *ctx, void *array, void *item) ;

int wrapper_json_insert_item_in_array(void *ctx, void *array, int index, void *item) ;

int wrapper_json_replace_item_in_array(void *ctx, void *array, int index, void *newitem) ;

void wrapper_json_delete_item_from_array(void *ctx, void *array, int index) ;

//================================JSON TYPE CHECKING================================
int wrapper_json_is_object(void *ctx, const void *item) ;

int wrapper_json_is_array(void *ctx, const void *item) ;

int wrapper_json_is_string(void *ctx, const void *item) ;

int wrapper_json_is_number(void *ctx, const void *item) ;

int wrapper_json_is_bool(void *ctx, const void *item) ;

int wrapper_json_is_null(void *ctx, const void *item) ;

int wrapper_json_is_true(void *ctx, const void *item) ;

int wrapper_json_is_false(void *ctx, const void *item) ;

//================================JSON VALUE GETTERS================================
char *wrapper_json_get_string_value(void *ctx, const void *item) ;

double wrapper_json_get_number_value(void *ctx, const void *item) ;

//================================JSON COMPARISON================================
int wrapper_json_compare(void *ctx, const void *a, const void *b, int case_sensitive) ;

//================================JSON ITERATION================================
void *wrapper_json_get_child(void *ctx, const void *item) ;

void *wrapper_json_get_next(void *ctx, const void *item) ;

const char *wrapper_json_get_key(void *ctx, const void *item) ;

int wrapper_json_get_object_size(void *ctx, const void *object) ;
//fdefine.asssets.c

const unsigned char *wrapper_get_asset_content(void *ctx, const char *path,long *size,int *is_binary) ;
void *wrapper_list_assets(void *ctx, const char *path) ;
//fdefine.https_client.c


void *wrapper_newhttpclient(void *ctx, const char *url) ;
void wrapper_httpclient_set_method(void *ctx, void *client, const char *method) ;
void wrapper_httpclient_set_max_redirections(void *ctx, void *client,
                                             int max_redirections) ;
void *wrapper_httpclient_fetch(void *ctx, void *client) ;
int wrapper_httpclient_response_get_status_code(void *ctx, void *response) ;

const unsigned char *wrapper_httpclient_response_read_body(void *ctx, void *response,
                                                           long *size) ;
long wrapper_httpclient_response_get_body_size(void *ctx, void *response) ;

int wrapper_httpclient_response_get_header_size(void *ctx, void *response) ;
void wrapper_httpclient_set_header(void *ctx, void *client, const char *key,
                                   const char *value) ;
void wrapper_httpclient_set_body(void *ctx, void *client, unsigned char *content,
                                 long size) ;
void wrapper_httpclient_free(void *ctx, void *client) ;

const char *
wrapper_httpclient_response_get_header_value_by_key(void *ctx, void *response,
                                                    const char *key) ;
const char *wrapper_httpclient_response_get_header_key_by_index(void *ctx, void *response,
                                                                int index) ;
const char *
wrapper_httpclient_response_get_header_value_by_index(void *ctx, void *response,
                                                      int index) ;

void wrapper_httpclient_response_free(void *ctx, void *response) ;

int wrapper_httpclient_response_get_header_count(void *ctx, void *response) ;
//fdefine.time.c

#include <time.h>

long wrapper_get_unix_time(void *ctx) ;

int wrapper_get_random(void *ctx) ;

void wrapper_get_formatted_time(void *ctx, long timestamp, char *buf, int buf_size, const char *fmt) ;
//fdefine.io.c
unsigned char *wrapper_read_any(void *ctx, const char *path, long *size, int *is_binary) ;
char *wrapper_read_string(void *ctx, const char *path) ;
void wrapper_write_any(void *ctx, const char *path, const unsigned char *content, long size) ;

void wrapper_write_string(void *ctx, const char *path, const char *content) ;
void wrapper_delete_any(void *ctx, const char *path) ;
void wrapper_create_dir(void *ctx, const char *path) ;

int wrapper_file_exists(void *ctx, const char *path) ;
int wrapper_dir_exists(void *ctx, const char *path) ;

int wrapper_copy_any(void *ctx, const char *src, const char *dst) ;

int wrapper_move_any(void *ctx, const char *src, const char *dst) ;

void wrapper_append_string(void *ctx, const char *path, const char *content) ;

char *wrapper_concat_path(void *ctx, const char *path1, const char *path2) ;

void wrapper_delete_stringarray(void *ctx, void *array) ;
long wrapper_get_stringarray_size(void *ctx, void *array) ;
const char *wrapper_get_stringarray_item(void *ctx, void *array, int index) ;

void *wrapper_list_files(void *ctx, const char *path) ;
void *wrapper_list_dirs(void *ctx, const char *path) ;
void *wrapper_list_any(void *ctx, const char *path) ;
void *wrapper_list_files_recursively(void *ctx, const char *path) ;
void *wrapper_list_dirs_recursively(void *ctx, const char *path) ;
void *wrapper_list_any_recursively(void *ctx, const char *path) ;
char *wrapper_generate_sha(void *ctx, const unsigned char *data, long size) ;

char * wrapper_generate_cached_sha_from_file(void *ctx, const char *cache_path,const char *path) ;//fdefine.argv.c

const char *wrapper_get_arg_value(void *ctx, const void *argv,int index) ;
int wrapper_get_arg_count(void *ctx, const void *argv) ;

const char *wrapper_get_arg_flag_value(void *ctx, const void *argv,const char **flags,int total_flags,int index) ;

int wrapper_get_arg_flag_count(void *ctx, const void *argv,const char **flags,int total_flags) ;

int wrapper_has_arg_flag(void *ctx, const void *argv,const char **flags,int total_flags) ;//fdefine.server.c



const char *wrapper_get_server_route(void *ctx, const void *apprequest) ;
const char *wrapper_get_server_method(void *ctx, const void *apprequest) ;
//================================HEADERS================================
const char *wrapper_get_server_header(void *ctx, const void *apprequest, const char *key) ;

const char *wrapper_get_server_header_key(void *ctx, const void *apprequest, int index) ;

const char *wrapper_get_server_header_value(void *ctx, const void *apprequest, int index) ;

const char *wrapper_get_server_query_param(void *ctx, const void *apprequest, const char *key) ;

const char *wrapper_get_server_query_param_key(void *ctx, const void *apprequest, int index) ;

const char *wrapper_get_server_query_param_value(void *ctx, const void *apprequest, int index) ;

int wrapper_get_server_header_count(void *ctx, const void *apprequest) ;

int wrapper_get_server_query_param_count(void *ctx, const void *apprequest) ;

const unsigned char *wrapper_read_server_body(void *ctx, const void *apprequest, long size, long *read_size) ;
const void *wrapper_read_server_json(void *ctx, const void *apprequest, long size) ;

const void *wrapper_newappserverresponse(void *ctx) ;

void wrapper_setappserverresponse_header(void *ctx, void  *appserverresponse, const char *key, const char *value) ;

void wrapper_setappserverresponse_content(void *ctx, void *appserverresponse, const unsigned char *content, long content_size) ;

void wrapper_setappserverresponse_status_code(void *ctx, void*appserverresponse, int status_code) ;


const void  *wrapper_send_any(void *ctx, const unsigned char *content,long content_size,const char *content_type, int status_code) ;
const void *wrapper_send_text(void *ctx, const char *text,const char *content_type, int status_code) ;
const void *wrapper_send_file(void *ctx, const char *path,const char *content_type, int status_code) ;
const void *wrapper_send_json(void *ctx, const void *json, int status_code) ;


/*
int wrapper_start_server(int port, const appserverresponse *(*handler)(appdeps *d, void *props), void *props, appbool single_process) {
    global_app_handler = handler;
    global_app_props = props;
    if (global_firmware_mode) return 0;
    CwebServer server = newCwebSever(port, main_internal_server);
    server.use_static = false;
    #if !defined(_WIN32) && !defined(_WIN64)
        server.single_process = single_process;
    #endif
    CwebServer_start(&server);
    return 0;
;

CwebHttpResponse *main_internal_server_firmware(CwebHttpRequest *request, int argc, char *argv[]) {
    global_firmware_mode = 1;
    global_argv = newCArgvParse(argc, argv);
    global_appdeps.argv = &global_argv;
    global_appdeps.appserverrequest = (const void*)request;
    appmain(&global_appdeps);
    if (global_app_handler) {
        const void *response = global_app_handler(&global_appdeps, global_app_props);
        return (CwebHttpResponse *)response;
    ;
    return NULL;
;
*///fdefine.std.c


int wrapper_snprintf(void *ctx, char *str, unsigned long size, const char *format, ...) ;
int wrapper_sprintf(void *ctx, char *str, const char *format, ...) ;
unsigned long wrapper_strlen(void *ctx, const char *s) ;

void *wrapper_malloc(void *ctx, unsigned long size) ;

void *wrapper_calloc(void *ctx, unsigned long num, unsigned long size) ;

void *wrapper_realloc(void *ctx, void *ptr, unsigned long size) ;

char *wrapper_strdup(void *ctx, const char *s) ;

void *wrapper_memcpy(void *ctx, void *dst, const void *src, unsigned long n) ;

void *wrapper_memset(void *ctx, void *s, int c, unsigned long n) ;

int wrapper_strncmp(void *ctx, const char *s1, const char *s2, unsigned long n) ;

int wrapper_memcmp(void *ctx, const void *s1, const void *s2, unsigned long n) ;

char *wrapper_strcpy(void *ctx, char *dst, const char *src) ;

char *wrapper_strcat(void *ctx, char *dst, const char *src) ;

int wrapper_run_command(void *ctx, const char *cmd) ;
//fdefine.text_stack.c


void *wrapper_new_text_stack(void *ctx, const char *text) ;

void wrapper_text_stack_append(void *ctx, void *text_stack, const char *text) ;

const char *wrapper_text_stack_text(void *ctx, void *text_stack) ;

void wrapper_text_stack_free(void *ctx, void *text_stack) ;

void wrapper_text_stack_restart(void *ctx, void *text_stack) ;

void *wrapper_text_stack_clone(void *ctx, void *text_stack) ;

void wrapper_text_stack_self_substr(void *ctx, void *text_stack, long starter, long end) ;

void wrapper_text_stack_self_pop(void *ctx, void *text_stack, long starter, long end) ;

void wrapper_text_stack_self_insert_at(void *ctx, void *text_stack, long point,
                                       const char *element) ;

void wrapper_text_stack_self_replace(void *ctx, void *text_stack, const char *element,
                                     const char *element_to_replace) ;

void wrapper_text_stack_self_replace_long(void *ctx, void *text_stack, const char *element,
                                          long element_to_replace) ;

void wrapper_text_stack_self_replace_double(void *ctx, void *text_stack,
                                            const char *element,
                                            double element_to_replace) ;

void wrapper_text_stack_self_lower(void *ctx, void *text_stack) ;

void wrapper_text_stack_self_upper(void *ctx, void *text_stack) ;

void wrapper_text_stack_self_captalize(void *ctx, void *text_stack) ;

void wrapper_text_stack_self_reverse(void *ctx, void *text_stack) ;

void wrapper_text_stack_self_trim(void *ctx, void *text_stack) ;

int wrapper_text_stack_starts_with(void *ctx, void *text_stack, const char *element) ;

int wrapper_text_stack_ends_with(void *ctx, void *text_stack, const char *element) ;

int wrapper_text_stack_equal(void *ctx, void *text_stack, const char *element) ;

int wrapper_text_stack_typeof_element(void *ctx, void *text_stack) ;

int wrapper_text_stack_is_a_num(void *ctx, void *text_stack) ;

const char *wrapper_text_stack_typeof_in_str(void *ctx, void *text_stack) ;

int wrapper_text_stack_parse_to_bool(void *ctx, void *text_stack) ;

long wrapper_text_stack_parse_to_integer(void *ctx, void *text_stack) ;

double wrapper_text_stack_parse_to_double(void *ctx, void *text_stack) ;

long wrapper_text_stack_index_of(void *ctx, void *text_stack, const char *element) ;

long wrapper_text_stack_index_of_char(void *ctx, void *text_stack, char element) ;
