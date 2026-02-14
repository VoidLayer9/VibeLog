//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.globals.h"
//silver_chain_scope_end
unsigned char *wrapper_read_any(const char *path, long *size, int *is_binary){
    return dtw_load_any_content(path, size, (bool *)is_binary);
}
char *wrapper_read_string(const char *path){
    return dtw_load_string_file_content(path);
}
void wrapper_write_any(const char *path, const unsigned char *content, long size){
    dtw_write_any_content(path, (unsigned char *)content, size);
}

void wrapper_write_string(const char *path, const char *content){
    dtw_write_string_file_content(path, content);
}
void wrapper_delete_any(const char *path){
    dtw_remove_any(path);
}
void wrapper_create_dir(const char *path){
    dtw_create_dir_recursively(path);
}

int wrapper_file_exists(const char *path){
    return dtw_entity_type(path) == DTW_FILE_TYPE;
}
int wrapper_dir_exists(const char *path){
    return dtw_entity_type(path) == DTW_FOLDER_TYPE;
}

int wrapper_copy_any(const char *src, const char *dst){
    return dtw_copy_any(src, dst, false);
}

int wrapper_move_any(const char *src, const char *dst){
    return dtw_move_any(src, dst, false);
}

void wrapper_append_string(const char *path, const char *content){
    char *existing = dtw_load_string_file_content(path);
    if(existing){
        long existing_len = strlen(existing);
        long content_len = strlen(content);
        char *combined = (char *)malloc(existing_len + content_len + 1);
        memcpy(combined, existing, existing_len);
        memcpy(combined + existing_len, content, content_len + 1);
        dtw_write_string_file_content(path, combined);
        free(existing);
        free(combined);
    } else {
        dtw_write_string_file_content(path, content);
    }
}

char *wrapper_concat_path(const char *path1, const char *path2){
    return dtw_concat_path(path1, path2);
}

void wrapper_delete_stringarray(void *array){
    DtwStringArray_free((DtwStringArray *)array);
}
long wrapper_get_stringarray_size(void *array){
    return ((DtwStringArray *)array)->size;
}
const char *wrapper_get_stringarray_item(void *array, int index){
    return ((DtwStringArray *)array)->strings[index];
}

void *wrapper_list_files(const char *path){
    DtwStringArray *files = dtw_list_files(path,false);
    return (void *)files;
}
void *wrapper_list_dirs(const char *path){
    DtwStringArray *dirs = dtw_list_dirs(path,false);
    return (void *)dirs;
}
void *wrapper_list_any(const char *path){
    DtwStringArray *all = dtw_list_all(path,false);
    return (void *)all;
}
void *wrapper_list_files_recursively(const char *path){
    DtwStringArray *files = dtw_list_files_recursively(path,false);
    return (void *)files;
}
void *wrapper_list_dirs_recursively(const char *path){
    DtwStringArray *dirs = dtw_list_dirs_recursively(path,false);
    return (void *)dirs;
}
void *wrapper_list_any_recursively(const char *path){
    DtwStringArray *all = dtw_list_all_recursively(path,false);
    return (void *)all;
}
char *wrapper_generate_sha(const unsigned char *data, long size){
    return dtw_generate_sha_from_any((unsigned char *)data,size);
}

char * wrapper_generate_cached_sha_from_file(const char *cache_path,const char *path){
    const char *LAST_UPDATE = "l";
    const char *CACHE_SHA_PATH = "s";
    DtwResource * cache_dir = new_DtwResource(cache_path);
    char *sha_of_path = dtw_generate_sha_from_string(path);
    DtwResource * cache_file = DtwResource_sub_resource(cache_dir,sha_of_path);
    free(sha_of_path);
    DtwResource *last_modification = DtwResource_sub_resource(cache_file,LAST_UPDATE);
    DtwResource *sha_of_file = DtwResource_sub_resource(cache_file,CACHE_SHA_PATH);

    if(DtwResource_type(last_modification) == DTW_COMPLEX_LONG_TYPE){
        long last_modification_time_of_file_saved = DtwResource_get_long(last_modification);
        long last_modification_time_of_file = dtw_get_entity_last_motification_in_unix(path);
        if(last_modification_time_of_file_saved == last_modification_time_of_file){
            return DtwResource_get_string(sha_of_file);
        }
    }

    char *sha = dtw_generate_sha_from_file(path);
    DtwResource_set_long(last_modification,dtw_get_entity_last_motification_in_unix(path));
    DtwResource_set_string(sha_of_file,sha);
    DtwResource_commit(cache_dir);
    return sha;
    
}