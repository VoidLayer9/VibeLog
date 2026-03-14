//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.globals.h"
//silver_chain_scope_end
void *wrapper_json_parse(void *ctx, const char *value) {
    return (void *)cJSON_Parse(value);
}

void *wrapper_json_parse_file(void *ctx, const char *filepath) {
    char *content = dtw_load_string_file_content(filepath);
    if(content == NULL) return NULL;
    cJSON *json = cJSON_Parse(content);
    free(content);
    return (void *)json;
}

void wrapper_json_delete(void *ctx, void *json) {
    cJSON_Delete((cJSON *)json);
}

//================================JSON SERIALIZATION================================
char *wrapper_json_print(void *ctx, const void *json) {
    return cJSON_Print((cJSON *)json);
}

char *wrapper_json_print_unformatted(void *ctx, const void *json) {
    return cJSON_PrintUnformatted((cJSON *)json);
}

int wrapper_json_save_file(void *ctx, const void *json, const char *filepath) {
    char *content = cJSON_Print((cJSON *)json);
    if(content == NULL) return 0;
    dtw_write_string_file_content(filepath, content);
    cJSON_free(content);
    return 1;
}

void wrapper_json_free_string(void *ctx, char *str) {
    cJSON_free(str);
}

//================================JSON CREATION================================
void *wrapper_json_create_object(void *ctx) {
    return (void *)cJSON_CreateObject();
}

void *wrapper_json_create_array(void *ctx) {
    return (void *)cJSON_CreateArray();
}

void *wrapper_json_create_string(void *ctx, const char *string) {
    return (void *)cJSON_CreateString(string);
}

void *wrapper_json_create_number(void *ctx, double num) {
    return (void *)cJSON_CreateNumber(num);
}

void *wrapper_json_create_bool(void *ctx, int boolean) {
    return (void *)cJSON_CreateBool(boolean);
}

void *wrapper_json_create_null(void *ctx) {
    return (void *)cJSON_CreateNull();
}

void *wrapper_json_duplicate(void *ctx, const void *item, int recurse) {
    return (void *)cJSON_Duplicate((cJSON *)item, recurse);
}

//================================JSON OBJECT MANIPULATION================================
void *wrapper_json_get_object_item(void *ctx, const void *object, const char *key) {
    return (void *)cJSON_GetObjectItem((cJSON *)object, key);
}

int wrapper_json_has_object_item(void *ctx, const void *object, const char *key) {
    return cJSON_HasObjectItem((cJSON *)object, key);
}

int wrapper_json_add_item_to_object(void *ctx, void *object, const char *key, void *item) {
    return cJSON_AddItemToObject((cJSON *)object, key, (cJSON *)item);
}

int wrapper_json_delete_item_from_object(void *ctx, void *object, const char *key) {
    cJSON_DeleteItemFromObject((cJSON *)object, key);
    return 1;
}

int wrapper_json_replace_item_in_object(void *ctx, void *object, const char *key, void *newitem) {
    return cJSON_ReplaceItemInObject((cJSON *)object, key, (cJSON *)newitem);
}

void *wrapper_json_add_string_to_object(void *ctx, void *object, const char *key, const char *string) {
    return (void *)cJSON_AddStringToObject((cJSON *)object, key, string);
}

void *wrapper_json_add_number_to_object(void *ctx, void *object, const char *key, double number) {
    return (void *)cJSON_AddNumberToObject((cJSON *)object, key, number);
}

void *wrapper_json_add_bool_to_object(void *ctx, void *object, const char *key, int boolean) {
    return (void *)cJSON_AddBoolToObject((cJSON *)object, key, boolean);
}

void *wrapper_json_add_null_to_object(void *ctx, void *object, const char *key) {
    return (void *)cJSON_AddNullToObject((cJSON *)object, key);
}

void *wrapper_json_add_object_to_object(void *ctx, void *object, const char *key) {
    return (void *)cJSON_AddObjectToObject((cJSON *)object, key);
}

void *wrapper_json_add_array_to_object(void *ctx, void *object, const char *key) {
    return (void *)cJSON_AddArrayToObject((cJSON *)object, key);
}

//================================JSON ARRAY MANIPULATION================================
int wrapper_json_get_array_size(void *ctx, const void *array) {
    return cJSON_GetArraySize((cJSON *)array);
}

void *wrapper_json_get_array_item(void *ctx, const void *array, int index) {
    return (void *)cJSON_GetArrayItem((cJSON *)array, index);
}

int wrapper_json_add_item_to_array(void *ctx, void *array, void *item) {
    return cJSON_AddItemToArray((cJSON *)array, (cJSON *)item);
}

int wrapper_json_insert_item_in_array(void *ctx, void *array, int index, void *item) {
    return cJSON_InsertItemInArray((cJSON *)array, index, (cJSON *)item);
}

int wrapper_json_replace_item_in_array(void *ctx, void *array, int index, void *newitem) {
    return cJSON_ReplaceItemInArray((cJSON *)array, index, (cJSON *)newitem);
}

void wrapper_json_delete_item_from_array(void *ctx, void *array, int index) {
    cJSON_DeleteItemFromArray((cJSON *)array, index);
}

//================================JSON TYPE CHECKING================================
int wrapper_json_is_object(void *ctx, const void *item) {
    return cJSON_IsObject((cJSON *)item);
}

int wrapper_json_is_array(void *ctx, const void *item) {
    return cJSON_IsArray((cJSON *)item);
}

int wrapper_json_is_string(void *ctx, const void *item) {
    return cJSON_IsString((cJSON *)item);
}

int wrapper_json_is_number(void *ctx, const void *item) {
    return cJSON_IsNumber((cJSON *)item);
}

int wrapper_json_is_bool(void *ctx, const void *item) {
    return cJSON_IsBool((cJSON *)item);
}

int wrapper_json_is_null(void *ctx, const void *item) {
    return cJSON_IsNull((cJSON *)item);
}

int wrapper_json_is_true(void *ctx, const void *item) {
    return cJSON_IsTrue((cJSON *)item);
}

int wrapper_json_is_false(void *ctx, const void *item) {
    return cJSON_IsFalse((cJSON *)item);
}

//================================JSON VALUE GETTERS================================
char *wrapper_json_get_string_value(void *ctx, const void *item) {
    return cJSON_GetStringValue((cJSON *)item);
}

double wrapper_json_get_number_value(void *ctx, const void *item) {
    return cJSON_GetNumberValue((cJSON *)item);
}

//================================JSON COMPARISON================================
int wrapper_json_compare(void *ctx, const void *a, const void *b, int case_sensitive) {
    return cJSON_Compare((cJSON *)a, (cJSON *)b, case_sensitive);
}

//================================JSON ITERATION================================
void *wrapper_json_get_child(void *ctx, const void *item) {
    return (void *)((cJSON *)item)->child;
}

void *wrapper_json_get_next(void *ctx, const void *item) {
    return (void *)((cJSON *)item)->next;
}

const char *wrapper_json_get_key(void *ctx, const void *item) {
    return ((cJSON *)item)->string;
}

int wrapper_json_get_object_size(void *ctx, const void *object) {
    int count = 0;
    cJSON *child = ((cJSON *)object)->child;
    while(child){
        count++;
        child = child->next;
    }
    return count;
}
