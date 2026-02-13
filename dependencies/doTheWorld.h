/* MIT License

Copyright (c) 2023 Mateus Moutinho Queiroz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 */ 
#ifndef doTheWorld_dep_declare
#define doTheWorld_dep_declare



#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>

#include <stdarg.h>

#include <errno.h>



#if defined(__linux__) || defined(__APPLE__)
#include <unistd.h>
#include <sys/time.h>
#include <sys/file.h>

#include <sys/wait.h>
  #include <dirent.h>
  #include <unistd.h>
#elif _WIN32
  #include <windows.h>
  #include <tchar.h>
  #include <wchar.h>
  #include <locale.h>
  #include <direct.h>
#endif
#if defined(DTW_ALLOW_CHASH) && !defined(CHashManipulator_dep_declare)
  #include DTW_CHASH_PATH
#endif 

#if !defined(cJSON__h)
/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef cJSON__h
#define cJSON__h

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
#define __WINDOWS__
#endif

#ifdef __WINDOWS__

/* When compiling for windows, we specify a specific calling convention to avoid issues where we are being called from a project with a different default calling convention.  For windows you have 3 define options:

CJSON_HIDE_SYMBOLS - Define this in the case where you don't want to ever dllexport symbols
CJSON_EXPORT_SYMBOLS - Define this on library build when you want to dllexport symbols (default)
CJSON_IMPORT_SYMBOLS - Define this if you want to dllimport symbol

For *nix builds that support visibility attribute, you can define similar behavior by

setting default visibility to hidden by adding
-fvisibility=hidden (for gcc)
or
-xldscope=hidden (for sun cc)
to CFLAGS

then using the CJSON_API_VISIBILITY flag to "export" the same symbols the way CJSON_EXPORT_SYMBOLS does

*/

#define CJSON_CDECL __cdecl
#define CJSON_STDCALL __stdcall

/* export symbols by default, this is necessary for copy pasting the C and header file */
#if !defined(CJSON_HIDE_SYMBOLS) && !defined(CJSON_IMPORT_SYMBOLS) && !defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_EXPORT_SYMBOLS
#endif

#if defined(CJSON_HIDE_SYMBOLS)
#define CJSON_PUBLIC(type)   type CJSON_STDCALL
#elif defined(CJSON_EXPORT_SYMBOLS)
#define CJSON_PUBLIC(type)   __declspec(dllexport) type CJSON_STDCALL
#elif defined(CJSON_IMPORT_SYMBOLS)
#define CJSON_PUBLIC(type)   __declspec(dllimport) type CJSON_STDCALL
#endif
#else /* !__WINDOWS__ */
#define CJSON_CDECL
#define CJSON_STDCALL

#if (defined(__GNUC__) || defined(__SUNPRO_CC) || defined (__SUNPRO_C)) && defined(CJSON_API_VISIBILITY)
#define CJSON_PUBLIC(type)   __attribute__((visibility("default"))) type
#else
#define CJSON_PUBLIC(type) type
#endif
#endif

/* project version */
#define CJSON_VERSION_MAJOR 1
#define CJSON_VERSION_MINOR 7
#define CJSON_VERSION_PATCH 18

#include <stddef.h>

/* cJSON Types: */
#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7) /* raw json */

#define cJSON_IsReference 256
#define cJSON_StringIsConst 512

/* The cJSON structure: */
typedef struct cJSON
{
    /* next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem */
    struct cJSON *next;
    struct cJSON *prev;
    /* An array or object item will have a child pointer pointing to a chain of the items in the array/object. */
    struct cJSON *child;

    /* The type of the item, as above. */
    int type;

    /* The item's string, if type==cJSON_String  and type == cJSON_Raw */
    char *valuestring;
    /* writing to valueint is DEPRECATED, use cJSON_SetNumberValue instead */
    int valueint;
    /* The item's number, if type==cJSON_Number */
    double valuedouble;

    /* The item's name string, if this item is the child of, or is in the list of subitems of an object. */
    char *string;
} cJSON;

typedef struct cJSON_Hooks
{
      /* malloc/free are CDECL on Windows regardless of the default calling convention of the compiler, so ensure the hooks allow passing those functions directly. */
      void *(CJSON_CDECL *malloc_fn)(size_t sz);
      void (CJSON_CDECL *free_fn)(void *ptr);
} cJSON_Hooks;

typedef int cJSON_bool;

/* Limits how deeply nested arrays/objects can be before cJSON rejects to parse them.
 * This is to prevent stack overflows. */
#ifndef CJSON_NESTING_LIMIT
#define CJSON_NESTING_LIMIT 1000
#endif

/* returns the version of cJSON as a string */
CJSON_PUBLIC(const char*) cJSON_Version(void);

/* Supply malloc, realloc and free functions to cJSON */
CJSON_PUBLIC(void) cJSON_InitHooks(cJSON_Hooks* hooks);

/* Memory Management: the caller is always responsible to free the results from all variants of cJSON_Parse (with cJSON_Delete) and cJSON_Print (with stdlib free, cJSON_Hooks.free_fn, or cJSON_free as appropriate). The exception is cJSON_PrintPreallocated, where the caller has full responsibility of the buffer. */
/* Supply a block of JSON, and this returns a cJSON object you can interrogate. */
CJSON_PUBLIC(cJSON *) cJSON_Parse(const char *value);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLength(const char *value, size_t buffer_length);
/* ParseWithOpts allows you to require (and check) that the JSON is null terminated, and to retrieve the pointer to the final byte parsed. */
/* If you supply a ptr in return_parse_end and parsing fails, then return_parse_end will contain a pointer to the error so will match cJSON_GetErrorPtr(). */
CJSON_PUBLIC(cJSON *) cJSON_ParseWithOpts(const char *value, const char **return_parse_end, cJSON_bool require_null_terminated);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLengthOpts(const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated);

/* Render a cJSON entity to text for transfer/storage. */
CJSON_PUBLIC(char *) cJSON_Print(const cJSON *item);
/* Render a cJSON entity to text for transfer/storage without any formatting. */
CJSON_PUBLIC(char *) cJSON_PrintUnformatted(const cJSON *item);
/* Render a cJSON entity to text using a buffered strategy. prebuffer is a guess at the final size. guessing well reduces reallocation. fmt=0 gives unformatted, =1 gives formatted */
CJSON_PUBLIC(char *) cJSON_PrintBuffered(const cJSON *item, int prebuffer, cJSON_bool fmt);
/* Render a cJSON entity to text using a buffer already allocated in memory with given length. Returns 1 on success and 0 on failure. */
/* NOTE: cJSON is not always 100% accurate in estimating how much memory it will use, so to be safe allocate 5 bytes more than you actually need */
CJSON_PUBLIC(cJSON_bool) cJSON_PrintPreallocated(cJSON *item, char *buffer, const int length, const cJSON_bool format);
/* Delete a cJSON entity and all subentities. */
CJSON_PUBLIC(void) cJSON_Delete(cJSON *item);

/* Returns the number of items in an array (or object). */
CJSON_PUBLIC(int) cJSON_GetArraySize(const cJSON *array);
/* Retrieve item number "index" from array "array". Returns NULL if unsuccessful. */
CJSON_PUBLIC(cJSON *) cJSON_GetArrayItem(const cJSON *array, int index);
/* Get item "string" from object. Case insensitive. */
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItem(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItemCaseSensitive(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON_bool) cJSON_HasObjectItem(const cJSON *object, const char *string);
/* For analysing failed parses. This returns a pointer to the parse error. You'll probably need to look a few chars back to make sense of it. Defined when cJSON_Parse() returns 0. 0 when cJSON_Parse() succeeds. */
CJSON_PUBLIC(const char *) cJSON_GetErrorPtr(void);

/* Check item type and return its value */
CJSON_PUBLIC(char *) cJSON_GetStringValue(const cJSON * const item);
CJSON_PUBLIC(double) cJSON_GetNumberValue(const cJSON * const item);

/* These functions check the type of an item */
CJSON_PUBLIC(cJSON_bool) cJSON_IsInvalid(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsFalse(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsTrue(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsBool(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNull(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNumber(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsString(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsArray(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsObject(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsRaw(const cJSON * const item);

/* These calls create a cJSON item of the appropriate type. */
CJSON_PUBLIC(cJSON *) cJSON_CreateNull(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateTrue(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateFalse(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateBool(cJSON_bool boolean);
CJSON_PUBLIC(cJSON *) cJSON_CreateNumber(double num);
CJSON_PUBLIC(cJSON *) cJSON_CreateString(const char *string);
/* raw json */
CJSON_PUBLIC(cJSON *) cJSON_CreateRaw(const char *raw);
CJSON_PUBLIC(cJSON *) cJSON_CreateArray(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateObject(void);

/* Create a string where valuestring references a string so
 * it will not be freed by cJSON_Delete */
CJSON_PUBLIC(cJSON *) cJSON_CreateStringReference(const char *string);
/* Create an object/array that only references it's elements so
 * they will not be freed by cJSON_Delete */
CJSON_PUBLIC(cJSON *) cJSON_CreateObjectReference(const cJSON *child);
CJSON_PUBLIC(cJSON *) cJSON_CreateArrayReference(const cJSON *child);

/* These utilities create an Array of count items.
 * The parameter count cannot be greater than the number of elements in the number array, otherwise array access will be out of bounds.*/
CJSON_PUBLIC(cJSON *) cJSON_CreateIntArray(const int *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateFloatArray(const float *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateDoubleArray(const double *numbers, int count);
CJSON_PUBLIC(cJSON *) cJSON_CreateStringArray(const char *const *strings, int count);

/* Append item to the specified array/object. */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObject(cJSON *object, const char *string, cJSON *item);
/* Use this when string is definitely const (i.e. a literal, or as good as), and will definitely survive the cJSON object.
 * WARNING: When this function was used, make sure to always check that (item->type & cJSON_StringIsConst) is zero before
 * writing to `item->string` */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemToObjectCS(cJSON *object, const char *string, cJSON *item);
/* Append reference to item to the specified array/object. Use this when you want to add an existing cJSON to a new cJSON, but don't want to corrupt your existing cJSON. */
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(cJSON_bool) cJSON_AddItemReferenceToObject(cJSON *object, const char *string, cJSON *item);

/* Remove/Detach items from Arrays/Objects. */
CJSON_PUBLIC(cJSON *) cJSON_DetachItemViaPointer(cJSON *parent, cJSON * const item);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(void) cJSON_DeleteItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromObjectCaseSensitive(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_DeleteItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const char *string);

/* Update array items. */
CJSON_PUBLIC(cJSON_bool) cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem); /* Shifts pre-existing items to the right. */
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemViaPointer(cJSON * const parent, cJSON * const item, cJSON * replacement);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObject(cJSON *object,const char *string,cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object,const char *string,cJSON *newitem);

/* Duplicate a cJSON item */
CJSON_PUBLIC(cJSON *) cJSON_Duplicate(const cJSON *item, cJSON_bool recurse);
/* Duplicate will create a new, identical cJSON item to the one you pass, in new memory that will
 * need to be released. With recurse!=0, it will duplicate any children connected to the item.
 * The item->next and ->prev pointers are always zero on return from Duplicate. */
/* Recursively compare two cJSON items for equality. If either a or b is NULL or invalid, they will be considered unequal.
 * case_sensitive determines if object keys are treated case sensitive (1) or case insensitive (0) */
CJSON_PUBLIC(cJSON_bool) cJSON_Compare(const cJSON * const a, const cJSON * const b, const cJSON_bool case_sensitive);

/* Minify a strings, remove blank characters(such as ' ', '\t', '\r', '\n') from strings.
 * The input pointer json cannot point to a read-only address area, such as a string constant, 
 * but should point to a readable and writable address area. */
CJSON_PUBLIC(void) cJSON_Minify(char *json);

/* Helper functions for creating and adding items to an object at the same time.
 * They return the added item or NULL on failure. */
CJSON_PUBLIC(cJSON*) cJSON_AddNullToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddTrueToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddFalseToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddBoolToObject(cJSON * const object, const char * const name, const cJSON_bool boolean);
CJSON_PUBLIC(cJSON*) cJSON_AddNumberToObject(cJSON * const object, const char * const name, const double number);
CJSON_PUBLIC(cJSON*) cJSON_AddStringToObject(cJSON * const object, const char * const name, const char * const string);
CJSON_PUBLIC(cJSON*) cJSON_AddRawToObject(cJSON * const object, const char * const name, const char * const raw);
CJSON_PUBLIC(cJSON*) cJSON_AddObjectToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON*) cJSON_AddArrayToObject(cJSON * const object, const char * const name);

/* When assigning an integer value, it needs to be propagated to valuedouble too. */
#define cJSON_SetIntValue(object, number) ((object) ? (object)->valueint = (object)->valuedouble = (number) : (number))
/* helper for the cJSON_SetNumberValue macro */
CJSON_PUBLIC(double) cJSON_SetNumberHelper(cJSON *object, double number);
#define cJSON_SetNumberValue(object, number) ((object != NULL) ? cJSON_SetNumberHelper(object, (double)number) : (number))
/* Change the valuestring of a cJSON_String object, only takes effect when type of object is cJSON_String */
CJSON_PUBLIC(char*) cJSON_SetValuestring(cJSON *object, const char *valuestring);

/* If the object is not a boolean type this does nothing and returns cJSON_Invalid else it returns the new type*/
#define cJSON_SetBoolValue(object, boolValue) ( \
    (object != NULL && ((object)->type & (cJSON_False|cJSON_True))) ? \
    (object)->type=((object)->type &(~(cJSON_False|cJSON_True)))|((boolValue)?cJSON_True:cJSON_False) : \
    cJSON_Invalid\
)

/* Macro for iterating over an array or object */
#define cJSON_ArrayForEach(element, array) for(element = (array != NULL) ? (array)->child : NULL; element != NULL; element = element->next)

/* malloc/free objects using the malloc/free functions that have been set with cJSON_InitHooks */
CJSON_PUBLIC(void *) cJSON_malloc(size_t size);
CJSON_PUBLIC(void) cJSON_free(void *object);

#ifdef __cplusplus
}
#endif

#endif

#define DTW_CJSON_IMPLEMENTED
#endif

#if !defined(SHA_256_H)
#ifndef SHA_256_H
#define SHA_256_H

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief Size of the SHA-256 sum. This times eight is 256 bits.
 */
#define SIZE_OF_SHA_256_HASH 32

/*
 * @brief Size of the chunks used for the calculations.
 *
 * @note This should mostly be ignored by the user, although when using the streaming API, it has an impact for
 * performance. Add chunks whose size is a multiple of this, and you will avoid a lot of superfluous copying in RAM!
 */
#define SIZE_OF_SHA_256_CHUNK 64

/*
 * @brief The opaque SHA-256 type, that should be instantiated when using the streaming API.
 *
 * @note Although the details are exposed here, in order to make instantiation easy, you should refrain from directly
 * accessing the fields, as they may change in the future.
 */
struct Sha_256 {
	uint8_t *hash;
	uint8_t chunk[SIZE_OF_SHA_256_CHUNK];
	uint8_t *chunk_pos;
	size_t space_left;
	uint64_t total_len;
	uint32_t h[8];
};

/*
 * @brief The simple SHA-256 calculation function.
 * @param hash Hash array, where the result is delivered.
 * @param input Pointer to the data the hash shall be calculated on.
 * @param len Length of the input data, in byte.
 *
 * @note If all of the data you are calculating the hash value on is available in a contiguous buffer in memory, this is
 * the function you should use.
 *
 * @note If either of the passed pointers is NULL, the results are unpredictable.
 *
 * @note See note about maximum data length for sha_256_write, as it applies for this function's len argument too.
 */
void calc_sha_256(uint8_t hash[SIZE_OF_SHA_256_HASH], const void *input, size_t len);

/*
 * @brief Initialize a SHA-256 streaming calculation.
 * @param sha_256 A pointer to a SHA-256 structure.
 * @param hash Hash array, where the result will be delivered.
 *
 * @note If all of the data you are calculating the hash value on is not available in a contiguous buffer in memory,
 * this is where you should start. Instantiate a SHA-256 structure, for instance by simply declaring it locally, make
 * your hash buffer available, and invoke this function. Once a SHA-256 hash has been calculated (see further below) a
 * SHA-256 structure can be initialized again for the next calculation.
 *
 * @note If either of the passed pointers is NULL, the results are unpredictable.
 */
void sha_256_init(struct Sha_256 *sha_256, uint8_t hash[SIZE_OF_SHA_256_HASH]);

/*
 * @brief Stream more input data for an on-going SHA-256 calculation.
 * @param sha_256 A pointer to a previously initialized SHA-256 structure.
 * @param data Pointer to the data to be added to the calculation.
 * @param len Length of the data to add, in byte.
 *
 * @note This function may be invoked an arbitrary number of times between initialization and closing, but the maximum
 * data length is limited by the SHA-256 algorithm: the total number of bits (i.e. the total number of bytes times
 * eight) must be representable by a 64-bit unsigned integer. While that is not a practical limitation, the results are
 * unpredictable if that limit is exceeded.
 *
 * @note This function may be invoked on empty data (zero length), although that obviously will not add any data.
 *
 * @note If either of the passed pointers is NULL, the results are unpredictable.
 */
void sha_256_write(struct Sha_256 *sha_256, const void *data, size_t len);

/*
 * @brief Conclude a SHA-256 streaming calculation, making the hash value available.
 * @param sha_256 A pointer to a previously initialized SHA-256 structure.
 * @return Pointer to the hash array, where the result is delivered.
 *
 * @note After this function has been invoked, the result is available in the hash buffer that initially was provided. A
 * pointer to the hash value is returned for convenience, but you should feel free to ignore it: it is simply a pointer
 * to the first byte of your initially provided hash array.
 *
 * @note If the passed pointer is NULL, the results are unpredictable.
 *
 * @note Invoking this function for a calculation with no data (the writing function has never been invoked, or it only
 * has been invoked with empty data) is legal. It will calculate the SHA-256 value of the empty string.
 */
uint8_t *sha_256_close(struct Sha_256 *sha_256);

#ifdef __cplusplus
}
#endif

#endif

#define DTW_SHA256_IMPLEMENTED
#endif

#if !defined(_AES_H_)
#ifndef _AES_H_
#define _AES_H_

#include <stdint.h>

// #define the macros below to 1/0 to enable/disable the mode of operation.
//
// CBC enables AES encryption in CBC-mode of operation.
// CTR enables encryption in counter-mode.
// ECB enables the basic ECB 16-byte block algorithm. All can be enabled simultaneously.

// The #ifndef-guard allows it to be configured before #include'ing or at compile time.
#ifndef CBC
  #define CBC 1
#endif

#ifndef ECB
  #define ECB 1
#endif

#ifndef CTR
  #define CTR 1
#endif


#define AES128 1
//#define AES192 1
//#define AES256 1

#define AES_BLOCKLEN 16 //Block length in bytes AES is 128b block only

#if defined(AES256) && (AES256 == 1)
    #define AES_KEYLEN 32
    #define AES_keyExpSize 240
#elif defined(AES192) && (AES192 == 1)
    #define AES_KEYLEN 24
    #define AES_keyExpSize 208
#else
    #define AES_KEYLEN 16   // Key length in bytes
    #define AES_keyExpSize 176
#endif

struct AES_ctx
{
  uint8_t RoundKey[AES_keyExpSize];
#if (defined(CBC) && (CBC == 1)) || (defined(CTR) && (CTR == 1))
  uint8_t Iv[AES_BLOCKLEN];
#endif
};

void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key);
#if (defined(CBC) && (CBC == 1)) || (defined(CTR) && (CTR == 1))
void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv);
void AES_ctx_set_iv(struct AES_ctx* ctx, const uint8_t* iv);
#endif

#if defined(ECB) && (ECB == 1)
// buffer size is exactly AES_BLOCKLEN bytes; 
// you need only AES_init_ctx as IV is not used in ECB 
// NB: ECB is considered insecure for most uses
void AES_ECB_encrypt(struct AES_ctx* ctx, uint8_t* buf);
void AES_ECB_decrypt(struct AES_ctx* ctx, uint8_t* buf);

#endif // #if defined(ECB) && (ECB == !)


#if defined(CBC) && (CBC == 1)
// buffer size MUST be mutile of AES_BLOCKLEN;
// Suggest https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: you need to set IV in ctx via AES_init_ctx_iv() or AES_ctx_set_iv()
//        no IV should ever be reused with the same key 
void AES_CBC_encrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);
void AES_CBC_decrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);

#endif // #if defined(CBC) && (CBC == 1)


#if defined(CTR) && (CTR == 1)

// Same function for encrypting as for decrypting. 
// IV is incremented for every block, and used after encryption as XOR-compliment for output
// Suggesting https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: you need to set IV in ctx with AES_init_ctx_iv() or AES_ctx_set_iv()
//        no IV should ever be reused with the same key 
void AES_CTR_xcrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);

#endif // #if defined(CTR) && (CTR == 1)


#endif //_AES_H_

#define DTW_AES_IMPLEMENTED
#endif
#endif

#ifndef doTheWorld_consts
#define doTheWorld_consts
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#define DTW_RAW_MODE 0
#define DTW_B64_MODE 1
#define DTW_HEX_MODE 2

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end




#define DTW_FILE_TYPE 1
#define DTW_FOLDER_TYPE 2
#define DTW_ALL_TYPE 3
#define DTW_NOT_FOUND -1

#define DTW_COMPLEX_BINARY 10
#define DTW_COMPLEX_STRING_TYPE 11
#define DTW_COMPLEX_LONG_TYPE 12
#define DTW_COMPLEX_DOUBLE_TYPE 13
#define DTW_COMPLEX_BOOL_TYPE 14

#define DTW_MERGE true


#define DTW_NOT_MERGE false

#define DTW_NOT_NUMERICAL -2
#define DTW_NOT_BOOL -3

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#define DTW_CONCAT_PATH true
#define DTW_NOT_CONCAT_PATH false
#define WIN32_FILETYPE 32

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#define DTW_MULTIFILE_LOCKER_TOTAL_CHECK 500
#define DTW_MULTIFILE_LOCKER_MAX_TIMEOUT 10
#define DTW_MULFILE_LOCKER_MAX_WAIT 10


#define DTW_LOCKER_LOCKED 0
#define DTW_LOCKER_IMPOSSIBLE_TO_CREATE_FILE_DESCRIPTOR 5
#define DTW_LOCKER_FLCTL_FAIL 6
#define DTW_LOCKER_WAIT_ERROR 21
#define DTW_LOCKER_OS_NOT_PREDICTIBLE -1


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#define DTW_RESOURCE_ELEMENT_IS_NULL -1
#define DTW_RESOURCE_OK 0
#define DTW_RESOURCE_ELEMENT_NOT_EXIST 1
#define DTW_RESOURCE_ELEMENT_NOT_BOOL 2
#define DTW_RESOURCE_ELEMENT_NOT_LONG 3
#define DTW_RESOURCE_ELEMENT_NOT_DOUBLE 4
#define DTW_RESOURCE_ELEMENT_NOT_STRING 5
#define DTW_RESOURCE_PRIMARY_KEY_ALREADY_EXIST 6
#define DTW_RESOURCE_PRIMARY_KEY_CANNOT_HAVE_SUB_RESOURCE 7
#define DTW_IMPOSSIBLE_TO_RENAME_A_PRIMARY_KEY 8
#define DTW_RESOURCE_RENAMED_RESOURCE_CANNOT_HAVE_SONS 9
#define DTW_RESOURCE_IMPSSIBLE_TO_ADD_INSERTION_OUTSIDE_ROOT_SCHEMA 10
#define DTW_RESOURCE_IMPOSSIBLE_TO_ADD_SUB_RESOURCE_INSIDE_SCHEMA_STRUCT 11
#define DTW_RESOURCE_ONLY_ROOT_SCHEMA_CAN_FIND_BY_ID_OR_PK 12
#define DTW_RESOURCE_ONLY_ROOT_SCHEMA_HAVE_SCHEMA_VALUES 13
#define DTW_RESOURCE_ONLY_ROOT_SCHEMA_CANN_MODIFY_SCHEMA_PROPS 14


#define PRIVATE_DTW_SCHEMA_ROOT  1
#define PRIVATE_DTW_SCHEMA_VALUE 2
#define PRIVATE_DTW_SCHEMA_ELEMENT 3
#define PRIVATE_DTW_SCHEMA_ELEMENT_PROP 4
#define PRIVATE_DTW_SCHEMA_INDEX 5
#define PRIVATE_DTW_SCHEMA_PK_FOLDER 6
#define PRIVATE_DTW_SCHEMA_PK_VALUE 7


#define DTW_SCHEMA_DEFAULT_VALUES_NAME "value"
#define DTW_SCHEMA_DEFAULT_INDEX_NAME "index"

#define DTW_RESOURCE_ALL -1

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

enum {

    JSON_TRANSACTION_WRONG_TYPE,
    JSON_TRANSACTION_NOT_PRESENT_VALUE,
    JSON_TRANSACTION_INVALID_ACTION
};


enum {
    DTW_ACTION_FILE_NOT_FOUND,
    DTW_ACTION_ITS_NOT_JSON,
    DTW_ACTION_WRITE,
    DTW_ACTION_MOVE,
    DTW_ACTION_MOVE_MERGING,
    DTW_ACTION_COPY,
    DTW_ACTION_COPY_MERGING,
    DTW_ACTION_DELETE
};


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



#define DTW_NOT_MIMIFY 1
#define DTW_MIMIFY 2

#define DTW_NOT_LOAD 1
#define DTW_LOAD 2

#define DTW_HIDE 1
#define DTW_INCLUDE 2




#define DTW_IS_BINARY true
#define DTW_IS_NOT_BINARY false
#define DTW_IGNORE true
#define DTW_NOT_IGNORE false

#define DTW_SET_AS_ACTION 1
#define DTW_EXECUTE_NOW 2

#define DTW_MODIFY 1
#define DTW_WRITE 2
#define DTW_REMOVE 3


#define DTW_JSON_TYPE_ERROR 1
#define DTW_JSON_SYNTAX_ERROR 2
#define DTW_JSON_REQUIRED_KEY_ERROR 3
#define DTW_JSON_REQUIRED_VALUE_ERROR 4
#define DTW_JSON_NOT_FOUND_ERROR 5
#define DTW_ACTION_ERROR (-1)


#endif

#ifndef doTheWorld_macros
#define doTheWorld_macros
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#if defined(__linux__) || defined(__APPLE__)
#define dtw_create_dir(path) mkdir(path,0777)
#elif _WIN32
#define dtw_create_dir(path) _mkdir(path)

#endif



//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#define DtwSchemaRebase self->root_props->schema_unsafe =old;
#define privateDtwSchemaUnsafe(scope){\
    bool old = self->root_props->schema_unsafe;\
    self->root_props->schema_unsafe = true;\
    scope;\
    DtwSchemaRebase\
}

#endif

#ifndef doTheWorld_types
#define doTheWorld_types
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct privateDtwAES_RAW_EncryptionInterface{
     uint8_t key[16];
     struct AES_ctx  ctx;
     uint8_t iv[16];
     void (*encrypt_buffer)( struct privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);
     void (*decrypt_buffer)(struct privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

}privateDtwAES_RAW_EncryptionInterface;
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct DtwEncriptionInterface{
    void *obj;
    unsigned char * (*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size);
   unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size);
   void (*free_obj)(void *obj);
}DtwEncriptionInterface;



//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef  struct DtwHash{
    char *hash;
}DtwHash;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#if defined(__linux__) || defined(__APPLE__)

typedef struct {

    char *filename;
    int file_descriptor;


}privateDtwFlockLockedElement;
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct DtwEncryptionNamespace{
//initializer
DtwEncriptionInterface *(*newInterface_raw)(void *obj, unsigned char *(*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size), unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size), void (*free_obj)(void *obj));
DtwEncriptionInterface *(*newAES_ECB_EncryptionInterface)(const uint8_t* key,int key_size);
DtwEncriptionInterface *(*newAES_ECB_EncryptionInterface_str)(const char* key);
DtwEncriptionInterface *(*newAES_Custom_CBC_v1_interface)(const char *key);
DtwEncriptionInterface *(*newAES_CBC_EncryptionInterface)(const uint8_t* key,int key_size,const uint8_t *iv, int iv_size);
DtwEncriptionInterface *(*newAES_CBC_EncryptionInterface_str)(const char* key,const char *iv);


//basic
unsigned char *(*encrypt_buffer)(DtwEncriptionInterface *self, unsigned char *value,long size,long *out_size);
unsigned char *(*decrypt_buffer)(DtwEncriptionInterface *self, unsigned char *encrypted_value,long size,long *out_size,bool *is_binary);
void (*free)(DtwEncriptionInterface *self);

//basic io
bool (*write_any_content)(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);
bool (*write_string_file_content)(DtwEncriptionInterface *self,const char *file_name,const char *value);
unsigned char *(*load_any_content)(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);
char *(*load_string_file_content)(DtwEncriptionInterface *self,const char *file_name);



//hex
char *(*encrypt_buffer_hex)(DtwEncriptionInterface *self, unsigned char *value,long size);
unsigned char *(*decrypt_buffer_hex)(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary);
bool (*write_any_content_hex)(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);
bool (*write_string_file_content_hex)(DtwEncriptionInterface *self,const char *file_name,const char *value);
unsigned char *(*load_any_content_hex)(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);
char *(*load_string_file_content_hex)(DtwEncriptionInterface *self,const char *file_name);


///b64
char *(*encrypt_buffer_b64)(DtwEncriptionInterface *self, unsigned char *value,long size);
unsigned char *(*decrypt_buffer_b64)(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary);
bool (*write_any_content_b64)(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);
bool (*write_string_file_content_b64)(DtwEncriptionInterface *self,const char *file_name,const char *value);
unsigned char *(*load_any_content_b64)(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);
char *(*load_string_file_content_b64)(DtwEncriptionInterface *self,const char *file_name);


}DtwEncryptionNamespace;
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct DtwRandonizer{
    long internal_seed;
    long seed;
    long actual_generation;

}DtwRandonizer;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



#ifdef DTW_ALLOW_CHASH


typedef  struct{
    char *key;
    CHash *element;
    bool free_key;
}privateDtw_CHash_element_and_key;

#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef  struct{
    char *key;
    bool free_key;
    cJSON *element;
}privateDtw_cJSON_element_and_key;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct DtwStringArray {
    int size;
    char **strings;
}DtwStringArray;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#ifndef PRIVATE_DTW_ACTION_TRANSACTION_TYPE_H
#define PRIVATE_DTW_ACTION_TRANSACTION_TYPE_H
typedef struct DtwActionTransaction{
    short action_type;
    unsigned  char *content;
    long size;
    bool is_binary;
    DtwEncriptionInterface *encryption;
    short encryption_mode;

    char *dest;
    char *source;

}DtwActionTransaction;
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#ifndef PRIVATE_DTW_JSON_TRANSACTION_ERROR_TYPE_H
#define PRIVATE_DTW_JSON_TRANSACTION_ERROR_TYPE_H
typedef struct DtwJsonTransactionError{
    int code;
    char *mensage;
    char *path;


}DtwJsonTransactionError;
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#ifndef PRIVATE_DTW_JSON_TREE_ERROR_TYPE_H
#define PRIVATE_DTW_JSON_TREE_ERROR_TYPE_H
typedef struct DtwJsonTreeError {
    int code;
    int position;
    const char *menssage;


}DtwJsonTreeError;
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct DtwTreeProps{
    int minification;
    int content;
    int path_atributes;
    int hadware_data;
    int content_data;
    int ignored_elements;

}DtwTreeProps;

#endif

#ifndef doTheWorld_typesb
#define doTheWorld_typesb
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#if defined(__linux__) || defined(__APPLE__)

typedef struct {
    privateDtwFlockLockedElement **elements;
    int size;
}privateDtwFlockArray;
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct {

    int total_checks;
    int process;
    int max_wait;
    int max_lock_time;
    DtwStringArray *locked_elements;


}DtwMultiFileLocker;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct DtwPath {
    char *original_path_string;
    char *path;
    DtwStringArray *garbage;


}DtwPath;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct DtwSchema{


    const char *value_name;
    const char *index_name;

    char *name;
    struct DtwSchema **sub_schemas;
    int size;
    DtwStringArray  *primary_keys;
}DtwSchema;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#ifndef PRIVATE_DT_TRANSACTION_TYPE_H
#define PRIVATE_DT_TRANSACTION_TYPE_H

typedef struct DtwTransaction{
    DtwEncriptionInterface *encryption;
    short encryption_mode;
    DtwActionTransaction  **actions;
    bool encryption_owner;
    long size;

}DtwTransaction;
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#ifndef PRIVATE_DTW_TRANSACTION_REPORT_TYPE_H
#define PRIVATE_DTW_TRANSACTION_REPORT_TYPE_H
typedef struct DtwTreeTransactionReport{
    DtwStringArray *write;
    DtwStringArray *modify;
    DtwStringArray *remove;

}DtwTreeTransactionReport;
#endif

#endif

#ifndef doTheWorld_typesc
#define doTheWorld_typesc
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



#ifndef  PRIVATE_DTW_DATABASE_SCHEMA_TYPE_H
#define PRIVATE_DTW_DATABASE_SCHEMA_TYPE_H
typedef struct DtwDatabaseSchema{

    const char *value_name;
    const char *index_name;
    struct DtwSchema **sub_schemas;
    int size;
}DtwDatabaseSchema;
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct DtwTreePart{

    DtwPath *path;
    void *owner;
    long content_size;
    long  hardware_content_size;
    bool content_exist_in_hardware;
    bool ignore;
    bool is_binary;
    bool metadata_loaded;
    char *current_sha;
    char * last_modification_in_str;
    long last_modification_time;
    char *hawdware_content_sha;

    unsigned char *content;
    int pending_action;

}DtwTreePart;

#endif

#ifndef doTheWorld_typesc_flock_locker
#define doTheWorld_typesc_flock_locker
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#if defined(__linux__) || defined(__APPLE__)

typedef struct {
    const char *temp_folder;
    privateDtwFlockArray  *locked_files;
}DtwFlockLocker;
#endif

#endif

#ifndef doTheWorld_typesd
#define doTheWorld_typesd
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end





typedef struct {
#if defined(__linux__) || defined(__APPLE__)
    DtwFlockLocker *locker;
#endif
#ifdef _WIN32
    DtwMultiFileLocker  *locker;
#endif

} DtwLocker;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#ifndef  PRIVATE_DTW_TREE_TYPE_H
#define  PRIVATE_DTW_TREE_TYPE_H
typedef struct  DtwTree{
    int size;
    DtwTreePart **tree_parts;

}DtwTree;
#endif

#endif

#ifndef doTheWorld_typese
#define doTheWorld_typese
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct {
    DtwTransaction  *transaction;
    DtwRandonizer  *randonizer;
    DtwLocker *locker;
    bool schema_unsafe;
    int error_code;
    char *error_path;
    char *error_message;
    DtwEncriptionInterface *encryption_interface;
    short encryption_mode;
    bool encryption_owner;

}privateDtwResourceRootProps;

#endif

#ifndef doTheWorld_typesf
#define doTheWorld_typesf
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end




typedef struct DtwResource{

    bool allow_transaction;
    bool use_locker_on_unique_values;


    privateDtwResourceRootProps *root_props;
    struct DtwResource *mother;
    char *name;
    char *path;

    
    //in the schema struct there is:
    //|/root
    //|/root/values
    //|root/values/element  <-----------------------------|
    //|root/values/element/pk_name ->any(write_point)     |
    //|root/values/element/element_prop ->any(write_point)|
    //|root/index                                         |
    //|root/index/pk_name/pk_sha ->txt  -------------------
    DtwSchema *attached_schema;
    DtwDatabaseSchema *datatabase_schema;
    struct DtwResource *values_resource;
    struct DtwResource *index_resource;
    int schema_type;

    bool loaded;
    bool is_binary;
    bool were_renamed;
    unsigned char *value_any;
    long value_size;

    //cache implementation
    bool cache_sub_resources;
    void *sub_resources;

}DtwResource;

#endif

#ifndef doTheWorld_typesg
#define doTheWorld_typesg
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct{
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    void(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
}DtwResourceForeachProps;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#ifdef DTW_ALLOW_CHASH

typedef  struct{
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    CHash *(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
} DtwResourceCHashrrayMapProps;
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#ifdef DTW_ALLOW_CHASH

typedef  struct{
    char *(*key_provider_callback)(DtwResource *item,void *args);
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    CHash *(*callback)(DtwResource *item, void *args);
    void *args;
    bool free_key;
    int start;
    int qtd;
} DtwResourceCHashObjectMapProps;
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef  struct{
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    cJSON *(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
} DtwResourcecJSONArrayMapProps;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef  struct{
    char *(*key_provider_callback)(DtwResource *item,void *args);
    bool free_key;
    bool(*filtrage_callback)(DtwResource *item, void *args_filter);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    cJSON *(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
} DtwResourcecJSONObjectMapProps;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct {
    void *result;
    void *args;
    DtwResource *current;
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
}privateDtwResource_map_element;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct {
    void *main_array;
    void(*append)(void *main_array_arg, void *item);
    bool(*filtrage_callback)(DtwResource *item, void *args);
    int (*ordenation_callback)(DtwResource *item1, DtwResource *item2, void *args);
    void *(*callback)(DtwResource *item, void *args);
    void *args;
    int start;
    int qtd;
}DtwResourceMapProps;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct DtwResourceArray{
    DtwResource **resources;
    long size;

}DtwResourceArray;

#endif

#ifndef doTheWorld_typesi
#define doTheWorld_typesi
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#ifndef PRIVATE_DTW_DATABASE_SCHEMA_MODULE_TYPE_H
#define PRIVATE_DTW_DATABASE_SCHEMA_MODULE_TYPE_H
typedef struct {
    DtwSchema * (*sub_schema)(DtwDatabaseSchema *self,const char *name);
}DtwDatabaseSchemaModule;
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end




typedef struct DtwHashModule{
    DtwHash * (*newHash)();
    bool  (*digest_any)(DtwHash *self,unsigned char *content,long size);
    bool (*digest_string)(DtwHash * self, const char *content);
    void (*digest_long)(DtwHash * self,long content);
    void (*digest_double)(DtwHash * self,double content);
    void (*digest_bool)(DtwHash * self,bool content);
    bool  (*digest_file)(DtwHash * self, const char *path);
    bool  (*digest_entity_last_modification)(DtwHash * self, const char *path);
    bool (*digest_string_array)(DtwHash *self,DtwStringArray *element);
    bool (*digest_string_array_last_modifications)(DtwHash *self,DtwStringArray *element);
    bool (*digest_string_array_last_modifications_adding_name)(DtwHash *self,DtwStringArray *element);
    bool (*digest_string_array_content)(DtwHash *self,DtwStringArray *element);
    bool (*digest_string_array_content_adding_name)(DtwHash *self,DtwStringArray *element);
    bool (*digest_folder_by_last_modification)(DtwHash *self,const char *path);
    bool (*digest_folder_by_content)(DtwHash *self,const char *path);
    void  (*free)(DtwHash *self);

}DtwHashModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct DtwLockerModule{
    DtwLocker * (*newLocker)();
    int (*lock)(DtwLocker *self, const  char *element);
    void (*unlock)(DtwLocker *self, const  char *element);
    void (*represemt)(DtwLocker *self);
    void (*free)(DtwLocker *self);

}DtwLockerModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct DtwPathModule{
    //Getters

    DtwPath * (*newPath)(const char *path);
    bool  (*changed)(struct DtwPath *self);
    char *(*get_full_name) (struct DtwPath *self);
    char *(*get_name) (struct DtwPath *self);
    char *(*get_extension) (struct DtwPath *self);

    char *(*get_path) (struct DtwPath *self);
    char *(*get_dir) (struct DtwPath *self);

    int (*get_total_dirs)(DtwPath *self);
    char *(*get_sub_dirs_from_index)(DtwPath *self, int start,int end);
    void (*insert_dir_at_index)(DtwPath *self,int index,const char *dir);
    void (*remove_sub_dirs_at_index)(DtwPath *self,int start,int end);
    void (*insert_dir_after)(DtwPath *self,const char *str,const char *dir);
    void (*insert_dir_before)(DtwPath *self,const char *str,const char *dir);
    void (*replace_dirs)(DtwPath *self,const char *str,const char *dir);
    void (*remove_sub_dirs_at)(DtwPath *self,const char *str);


    //Setters
    void (*set_extension) (struct DtwPath *self, const char *extension);
    void (*set_name) (struct DtwPath *self, const char *name);
    void (*set_dir) (struct DtwPath *self, const char *path);
    void (*set_full_name) (struct DtwPath *self, const char *full_name);
    void (*set_path) (struct DtwPath *self, const char *target_path);

    void (*add_start_dir)(struct DtwPath *self, const char *start_dir);
    void (*add_end_dir)(struct DtwPath *self, const char *end_dir);

    void (*represent)(struct DtwPath *self);
    void (*free) (struct DtwPath *self);

}DtwPathModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct  DtwRandonizerModule{
    DtwRandonizer * (*newRandonizer)();
    int (*generate_num)(DtwRandonizer *self,int max);
    char * (*generate_token)(DtwRandonizer*self, int size);
    void (*free)(DtwRandonizer *self);
}DtwRandonizerModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct DtwResourceArrayModule{

    void (*append)(DtwResourceArray *self, DtwResource *element);
    DtwResource * (*get_by_name)(DtwResourceArray *self, const char *name);
    void (*represent)(DtwResourceArray *self);
    void (*free)(DtwResourceArray *self);

}DtwResourceArrayModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct DtwResourceModule{

    DtwResource *(*newResource)(const char *path);
    int (*get_error_code)(DtwResource *self);
    bool (*error)(DtwResource *self);

    void (*set_encryption)(DtwResource *self,DtwEncriptionInterface *encryption_interface,short mode);
    
    void (*set_Resource_as_encryption_object_owner)(DtwResource *self);

    DtwResourceForeachProps (*create_foreach_props)( void(*callback)(DtwResource *item, void *args));
    void (*each)(DtwResource *self,DtwResourceForeachProps props);
    void (*schema_each)(DtwResource *self,DtwResourceForeachProps props);

    DtwResourceMapProps (*create_map_props)(
        void *main_array,
        void(*append)(void *main_array_arg, void *item),
        void *(*callback)(DtwResource *item, void *args)
    );
    void (*map)(DtwResource *self,DtwResourceMapProps props);
    void (*schema_map)(DtwResource *self,DtwResourceMapProps props);

    DtwResourcecJSONArrayMapProps (*create_cJSONArrayMapProps)(cJSON *(*callback)(DtwResource *item, void *args));
    cJSON *(*map_cJSONArray)(DtwResource *self,DtwResourcecJSONArrayMapProps props);
    cJSON *(*schema_map_cJSONArray)(DtwResource *self,DtwResourcecJSONArrayMapProps props);

    DtwResourcecJSONObjectMapProps (*create_cJSONObjectProps)(
        cJSON *(*callback)(DtwResource *item, void *args),
        char *(*key_provider_callback)(DtwResource *item,void *args)
    );

    cJSON *(*map_cJSONObject)(DtwResource *self,DtwResourcecJSONObjectMapProps props);
    cJSON *(*schema_map_cJSONObject)(DtwResource *self,DtwResourcecJSONObjectMapProps props);


    #ifdef DTW_ALLOW_CHASH
    DtwResourceCHashrrayMapProps  (*create_CHashrrayMapProps)(    CHash *(*callback)(DtwResource *item, void *args));


    CHashArray *(*map_CHashArray)(DtwResource *self,DtwResourceCHashrrayMapProps props);
    CHashArray *(*schema_map_CHashArray)(DtwResource *self,DtwResourceCHashrrayMapProps props);

    DtwResourceCHashObjectMapProps (*createCHashObjectMapProps)(
        CHash *(*callback)(DtwResource *item, void *args),
        char*(*key_provider)(DtwResource *item, void *args_filter)
    );

    CHashObject *(*map_CHashObject)(DtwResource *self,DtwResourceCHashObjectMapProps props);
    CHashObject *(*schema_map_CHashObject)(DtwResource *self,DtwResourceCHashObjectMapProps props);


    #endif

    char * (*get_error_message)(DtwResource *self);
    bool (*is_file)(DtwResource *self);
    void (*destroy_sub_resource)(DtwResource *self, const char *key);
    void (*rename_sub_resource)(DtwResource *self,const char *old_name,const  char *new_name);
    DtwResource * (*sub_resource)(struct DtwResource *self,const  char *format,...);
    unsigned char *(*get_any_from_sub_resource)(DtwResource *self, long *size, bool *is_binary,const char *format,...);
    unsigned char *(*get_binary_from_sub_resource)(DtwResource *self, long *size,const char *format,...);
    char *(*get_string_from_sub_resource)(DtwResource *self,const char *format,...);
    long (*get_long_from_sub_resource)(DtwResource *self,const char *format,...);
    double (*get_double_from_sub_resource)(DtwResource *self,const char *format,...);
    bool (*get_bool_from_sub_resource)(DtwResource *self,const char *format,...);
    void (*set_any_in_sub_resource)(DtwResource *self,const char *key, unsigned char *element, long size,bool is_binary);
    void (*set_binary_in_sub_resource)(DtwResource *self,const char *key, unsigned char *element, long size);
    void (*set_string_in_sub_resource)(DtwResource *self,const char *key,const  char *element);
    void (*set_long_in_sub_resource)(DtwResource *self,const char *key,long element);
    void (*set_double_in_sub_resource)(DtwResource *self,const char *key,double element);
    void (*set_bool_in_sub_resource)( DtwResource *self,const char *key,bool element);
    void (*set_binary_sha)(DtwResource *self, unsigned  char *value, long size);
    void (*set_string_sha)(DtwResource *self,const char *value);
    void (*set_binary_sha_in_sub_resource)(DtwResource *self,const char *key, unsigned  char *value, long size);
    void (*set_string_sha_in_sub_resource)(DtwResource *self,const char *key,const char *value);



    DtwResource * (*new_schema_insertion)(DtwResource *self);
    DtwResource  *(*find_by_name_id)(DtwResource *self, const char *name);
    DtwResource * (*find_by_primary_key_with_binary)(DtwResource *self, const char *primary_key, unsigned  char *value, long size);
    DtwResource * (*find_by_primary_key_with_string)(DtwResource *self, const char *key, const char *value);
    void (*dangerous_remove_schema_prop)(DtwResource*self,const char *prop);
    void (*dangerous_rename_schema_prop)(DtwResource*self,const char *prop,const char *new_name);
    DtwDatabaseSchema * (*newDatabaseSchema)(DtwResource *self);

    char * (*get_error_path)(DtwResource *self);
    DtwResourceArray * (*get_schema_values)(DtwResource *self);


    DtwResource * (*sub_resource_ensuring_not_exist)(DtwResource *self,const  char *format, ...);
    DtwResource * (*sub_resource_next)(DtwResource *self, const char *end_path);
    DtwResource * (*sub_resource_now)(DtwResource *self, const char *end_path);

    DtwResource * (*sub_resource_now_in_unix)(DtwResource *self,const char *end_path);
    DtwResource * (*sub_resource_random)(DtwResource *self,const char *end_path);


    void (*load)(DtwResource *self);

    void (*unload)(DtwResource *self);

    int (*lock)(DtwResource *self);
    void (*unlock)(DtwResource *self);

    void (*destroy)(DtwResource *self);
    void  (*clear_errors)(DtwResource *self);
    unsigned char *(*get_any)(struct DtwResource *self, long *size, bool *is_binary);

    unsigned char *(*get_binary)(struct DtwResource *self, long *size);

    char *(*get_string)(struct DtwResource *self);

    long (*get_long)(struct DtwResource *self);

    double (*get_double)(struct DtwResource *self);

    bool (*get_bool)(struct DtwResource *self);
    void (*set_any)(DtwResource *self, unsigned char *element, long size,bool is_binary);
    void (*set_binary)(DtwResource *self, unsigned char *element, long size);

    void (*set_string)(DtwResource *self,const  char *element);

    void (*set_long)(DtwResource *self,long element);

    void (*set_double)(DtwResource *self,double element);

    void (*set_bool)(DtwResource *self,bool element);



    DtwStringArray *(*list_names)(DtwResource *self);

    long (*size)(DtwResource *self);
    int (*type)(DtwResource *self);

    const char *(*type_in_str)(DtwResource *self);
    void (*commit)(DtwResource *self);

    void (*represent)(DtwResource *self);

    void (*rename)(DtwResource *self,const char *new_name);

    void (*free)(DtwResource *self);
    DtwResourceArray * (*sub_resources)(DtwResource *self);
    DtwResourceArrayModule array;


}DtwResourceModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct {
    void (*add_primary_key)(DtwSchema *self, const char *primary_key);
    DtwSchema * (*sub_schema)(DtwSchema *self,const char *name);
}DtwSchemaModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct DtwStringArrayModule{
    DtwStringArray *(*newStringArray)();

    void (*set_value)(struct DtwStringArray *self,int index,const char *value);

    void (*append)(struct DtwStringArray *self,const char *string);

    void (*pop)(struct DtwStringArray *self, int position);

    void (*merge)(struct DtwStringArray *self, struct DtwStringArray *other);

    void (*represent)(struct DtwStringArray *self);

    int (*find_position)(struct DtwStringArray *self,const char *string);

    void (*sort)(struct DtwStringArray *self);

    void (*free)(struct DtwStringArray *self);


}DtwStringArrayModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct DtwActionTransactionModule{

    DtwActionTransaction *(*newAction)();

    DtwActionTransaction * (*write_any)(DtwEncriptionInterface *encryption, short encryption_mode,const char *source,unsigned  char *content,long size,bool is_binary);

    DtwActionTransaction * (*move_any)(const char *source, const char *dest);
    DtwActionTransaction * (*move_any_merging)(const char *source, const char *dest);
    DtwActionTransaction * (*copy_any_merging)(const char *source, const char *dest);

    DtwActionTransaction * (*copy_any)(const char *source, const char *dest);

    DtwActionTransaction * (*delete_any)(const char *source);

    short (*convert_action_to_integer)(char *action);

    const char * (*convert_action_to_string)(int action);

    void (*commit)(DtwActionTransaction* self,const char *path);

    void (*represent)(DtwActionTransaction* self);

    void (*free)(DtwActionTransaction* self);

}DtwActionTransactionModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct DtwJsonTransactionErrorModule{
    void (*represent)(struct DtwJsonTransactionError *self);
    void (*free)(struct DtwJsonTransactionError *self);

}DtwJsonTransactionErrorModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct DtwTransactionModule{
    DtwTransaction *(*newTransaction)();
    DtwTransaction * (*newTransaction_from_json)(cJSON *json_entry);
    DtwTransaction * (*newTransaction_from_json_file)(const char *filename);
    DtwJsonTransactionError * (*validate_json_transaction_file)(const char *filename);
    void (*set_encryption)(DtwTransaction *self,DtwEncriptionInterface *encryption,short encryption_mode);
    void (*set_transaction_as_encryption_object_owner)(DtwTransaction *self);

    void (*remove_from_index)(DtwTransaction *self,long index);
    void (*remove_from_source)(DtwTransaction *self,const char *source);
    void (*filter)(DtwTransaction *self,bool (*callback)(DtwActionTransaction *action));

    void (*append_action)(struct DtwTransaction *self,struct DtwActionTransaction  *action);
    void (*write_any)(struct DtwTransaction *self,const char *path,unsigned char *content, long size,bool is_binary);
    void (*write_string)(struct DtwTransaction *self,const char *path,const char *content);

    void (*write_long)(struct DtwTransaction *self,const char *path,long value);
    void (*write_bool)(struct DtwTransaction *self,const char *path,bool value);
    void (*write_double)(struct DtwTransaction *self,const char *path,double value);

    void (*move_any_merging)(struct DtwTransaction *self,const char *source,const char *dest);
    void (*copy_any_merging)(struct DtwTransaction *self,const char *source,const char *dest);


    void (*move_any)(struct DtwTransaction *self,const char *source,const char *dest);
    void (*copy_any)(struct DtwTransaction *self,const char *source,const char *dest);
    void (*delete_any)(struct DtwTransaction *self,const char *source);

    cJSON *(*dumps_transaction_to_json)(struct DtwTransaction *self);
    void (*dumps_transaction_to_json_file)(struct DtwTransaction *self,const char *filename);

    void (*commit)(struct DtwTransaction *self,const char *source);
    void (*represent)(struct DtwTransaction *self);
    void (*free)(struct DtwTransaction *self);

    DtwActionTransactionModule action;
    DtwJsonTransactionErrorModule json_error;


}DtwTransactionModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct DtwJsonTreeErrorModule{

    DtwJsonTreeError * (*validate_json_tree_by_cJSON)(cJSON *json_tree);
    DtwJsonTreeError * (*validate_json_tree_by_content)(const char *content);
    void (*free)(struct DtwJsonTreeError *self);
    void (*represent)(struct DtwJsonTreeError *self);

}DtwJsonTreeErrorModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct  DtwTreeTransactionReportModule{

    void (*represent)(struct DtwTreeTransactionReport *report);
    void (*free)(struct DtwTreeTransactionReport *report);

}DtwTreeTransactionReportModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct DtwTreePartModule{

    DtwTreePart  *(*newPart)(const char *path, DtwTreeProps props);
    DtwTreePart  *(*newPartEmpty)(const char *path);
    DtwTreePart * (*newPartLoading)(const char *path);

    char *(*get_content_string_by_reference)(struct DtwTreePart *self);
    unsigned char *(*get_content_binary_by_reference)(struct DtwTreePart *self);

    char *(*get_content_sha)(struct DtwTreePart *self);
    void (*set_any_content)(struct DtwTreePart *self,unsigned char *content,long content_size,bool is_binary);
    void (*set_string_content)(struct DtwTreePart *self,const char *content);
    void (*set_binary_content)(struct DtwTreePart *self,unsigned char *content,long content_size);
    void (*load_content_from_hardware)(struct DtwTreePart *self);
    void (*free_content)(struct DtwTreePart *self);
    void(*represent)(struct DtwTreePart *self);

    bool(*hardware_remove)(struct DtwTreePart *self, int transaction);
    bool(*hardware_write)(struct DtwTreePart *self, int transaction);
    bool(*hardware_modify)(struct DtwTreePart *self, int transaction);
    bool(*hardware_commit)(struct DtwTreePart *self);

    void (*free)(struct DtwTreePart *self);
    struct DtwTreePart *(*self_copy)(struct DtwTreePart *self);
}DtwTreePartModule;

#endif

#ifndef doTheWorld_typesj
#define doTheWorld_typesj
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct DtwTreeModule{

    DtwTree  *(*newTree)();
    void (*add_tree_part_by_copy)(
             DtwTree *self,
             DtwTreePart *tree_part
    );

    void (*remove_tree_part)(
             DtwTree *self,
            int position
    );

    void (*add_tree_part_getting_owenership)(
             DtwTree *self,
             DtwTreePart *tree_part
    );
    void (*add_tree_part_referencing)(
            DtwTree *self,
            DtwTreePart *tree_part
    );
        void (*add_tree_parts_from_string_array)(
            struct DtwTree *self,
            struct DtwStringArray *paths,
            DtwTreeProps props
    );

    struct DtwTree *(*get_sub_tree)(
            struct DtwTree *self,
            const char *path,
            bool copy_content
    );

    void (*add_tree_from_hardware)(
            struct DtwTree *self,
            const char *path,
            DtwTreeProps props
    );
    //Listage Functions

    DtwTreePart *(*find_tree_part_by_function)(
            struct DtwTree *self,
            bool (*caller)(struct  DtwTreePart *part,void *args),
            void *args
    );

    DtwTree *(*filter)(
            struct DtwTree *self,
            bool (*caller)(struct  DtwTreePart *part)
    );

    DtwTree *(*map)(
            struct DtwTree *self,
            struct  DtwTreePart*(*caller)(struct  DtwTreePart *part)
    );


    DtwStringArray * (*list_files)(struct DtwTree *self, const char *path,bool concat_path);
    DtwStringArray * (*list_dirs)(struct DtwTree *self, const char *path,bool concat_path);
    DtwStringArray * (*list_all)(struct DtwTree *self, const char *path,bool concat_path);

    DtwStringArray * (*list_files_recursively)(struct DtwTree *self, const char *path,bool concat_path);
    DtwStringArray * (*list_dirs_recursively)(struct DtwTree *self, const char *path,bool concat_path);
    DtwStringArray * (*list_all_recursively)(struct DtwTree *self, const char *path,bool concat_path);


    struct DtwTreePart *(*find_tree_part_by_name)( struct DtwTree *self,const char *name);
    struct DtwTreePart *(*find_tree_part_by_path)(   struct DtwTree *self,const char *path);


    struct DtwTreeTransactionReport * (*create_report)(struct DtwTree *self);

    bool (*loads_json_tree)(
            struct DtwTree *self,
            const char *content
    );


    bool (*loads_json_tree_from_file)(
            struct DtwTree *self,
            const char *path
    );

    char *(*dumps_json_tree)(
            struct DtwTree *self,
            DtwTreeProps props
    );

    void (*dumps_json_tree_to_file)(
            struct DtwTree *self,
            const char *path,
            DtwTreeProps  props
    );

    void (*represent)(struct DtwTree *self);
    void (*insecure_hardware_remove_tree)(struct DtwTree *self);
    void (*insecure_hardware_write_tree)(struct DtwTree *self);
    void (*hardware_commit_tree)(struct DtwTree *self);
    void (*free)(struct DtwTree *self);

    DtwTreeTransactionReportModule transaction_report;

    DtwTreePartModule part;
    DtwJsonTreeErrorModule json_error;

}DtwTreeModule;

#endif

#ifndef doTheWorld_typesm
#define doTheWorld_typesm
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end




typedef struct DtwNamespace{
    //IO
    void (*create_dir_recursively)(const char *path);

    bool (*remove_any)(const char* path);

    char *(*get_current_dir)();

    unsigned char *(*load_any_content)(const char * path,long *size,bool *is_binary);

    char *(*get_absolute_path)(const char *path);

    char *(*load_string_file_content)(const char * path);

    unsigned char *(*load_binary_content)(const char * path,long *size);

    bool (*write_any_content)(const char *path,unsigned  char *content,long size);

    bool (*write_string_file_content)(const char *path,const char *content);

    int (*entity_type)(const char *path);

    int (*complex_entity_type)(const char *path);

    const char *(*convert_entity)(int entity_type);

    bool (*copy_any)(const char* src_path,const  char* dest_path,bool merge);

    bool (*move_any)(const char* src_path, const char* dest_path,bool merge);

    //numeral io

    long (*load_long_file_content)(const char * path);

    double (*load_double_file_content)(const char * path);

    bool (*load_bool_file_content)(const char * path);



    void (*write_long_file_content)(const char *path, long value);

    void (*write_bool_file_content)(const char *path, bool value);

    void (*write_double_file_content)(const char *path,double value);



    //listage

    DtwStringArray * (*list_files)(const char *path, bool concat_path);
    DtwStringArray * (*list_dirs)(const char *path, bool concat_path);

    DtwStringArray *  (*list_all)(const char *path,  bool concat_path);
    DtwStringArray * (*list_dirs_recursively)(const char *path,bool concat_path);
    DtwStringArray *  (*list_files_recursively)(const char *path,bool concat_path);
    DtwStringArray * (*list_all_recursively)(const char *path,bool concat_path);


    //extras

    char * (*generate_sha_from_file)(const char *path);

    char * (*generate_sha_from_string)(const char *string);

    char * (*generate_sha_from_any)(void *anything , long size);

    long int (*get_entity_last_motification_in_unix)(const char *path);

    char * (*convert_unix_time_to_string)(long int unix_time);

    char * (*get_entity_last_motification_in_string)(const char *path);

    char *(*concat_path)(const char *path1, const char *path2);


    //base64

    char *(*base64_encode)(unsigned char *data, long input_length);

    unsigned char *(*base64_decode)(const char *data, long *output_length);

    char *(*convert_binary_file_to_base64)(const char *path);
    //string array

    DtwStringArrayModule string_array;
    DtwEncryptionNamespace encryption;
    DtwPathModule path;

    DtwLockerModule locker;

    DtwSchemaModule schema;
    DtwDatabaseSchemaModule database_schema;
    DtwTreeModule tree;
    DtwHashModule  hash;
    DtwTransactionModule transaction;

    DtwResourceModule resource;
    DtwRandonizerModule randonizer;

}DtwNamespace;

#endif

#ifndef doTheWorld_fdeclare
#define doTheWorld_fdeclare
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end
//fdefine.base64.c

char *dtw_base64_encode(unsigned char *data, long input_length) ;


unsigned char *dtw_base64_decode(const char *data, long *output_length) ;



char *dtw_convert_binary_file_to_base64(const char *path);
//fdefine.listage_wrappers.c




 DtwStringArray * dtw_list_files(const char *path, bool concat_path);

 DtwStringArray * dtw_list_dirs(const char *path, bool concat_path);

 DtwStringArray *  dtw_list_all(const char *path,  bool concat_path);
//fdefine.extras.c



char * dtw_generate_sha_from_file(const char *path);

char * dtw_generate_sha_from_any(void *anything , long size);

char * dtw_generate_sha_from_string(const char *string);


long int dtw_get_entity_last_motification_in_unix(const char *path);

char * dtw_convert_unix_time_to_string(long int unix_time);

char * dtw_get_entity_last_motification_in_string(const char *path);

const char * private_dtw_convert_action_to_string(short action);

short private_dtw_convert_string_to_action(const char *action);

void private_dtw_add_end_bar_to_dirs_string_array(struct DtwStringArray * dirs);



struct DtwStringArray* private_dtw_remove_start_path(struct DtwStringArray *paths,const char *rm_path);


long dtw_get_time();
long private_dtw_convert_index(long index,long size);

char *dtw_convert_binary_to_hex(unsigned char *value,long size);


unsigned char *dtw_convert_hex_to_binary(const char *value,long *out_size);//fdefine.string_functions.c



void private_dtw_remove_double_bars_from_string_array(struct DtwStringArray*path);

char *dtw_concat_path(const char *path1, const char *path2);

char * private_dtw_format_vaarg(const char *expresion, va_list args);

char *private_dtw_format_path(const char *path);


char * private_dtw_sub_str(const char *str, long start,long end);


bool dtw_starts_with(const char *string, const char *prefix);

bool dtw_ends_with(const char *string, const char *suffix);

char *private_dtw_replace_string_once(const char *target, const char *old_element, const char *new_element) ;

char* dtw_replace_string(const char *target, const char *old_element, const char *new_element) ;



char *private_dtw_change_beginning_of_string(const char *target,int start_element_to_remove_size, const char *new_element) ;



char *private_dtw_realoc_formatting(char *ptr,const char *format,...);
char *private_dtw_formatt(const char *format,...);
bool dtw_is_string_at_point(
        const char *str,
        long str_size,
        const char *target,
        long target_size,
        long target_point
        );

long  dtw_index_of_string(const char *str,const char *element);

double private_dtw_convert_string_to_number(const char *num, bool *its_a_number);
//fdefine.io.c






void dtw_create_dir_recursively(const char *path);
char *dtw_get_absolute_path(const char *path);
char *dtw_get_current_dir();



bool dtw_remove_any(const char* path) ;



unsigned char *dtw_load_any_content(const char * path,long *size,bool *is_binary);


char *dtw_load_string_file_content(const char * path);


unsigned char *dtw_load_binary_content(const char * path,long *size);


bool dtw_write_any_content(const char *path,unsigned  char *content,long size);


bool dtw_write_string_file_content(const char *path,const char *content);


int dtw_entity_type(const char *path);


int dtw_complex_entity_type(const char *path);

long dtw_get_total_itens_of_dir(const char *path);

const char *dtw_convert_entity(int entity_type);

bool dtw_copy_any(const char* src_path,const  char* dest_path,bool merge) ;

bool dtw_move_any(const char* src_path, const char* dest_path,bool merge) ;
//fdefine.multidimension_listage.c



 DtwStringArray * dtw_list_dirs_recursively(const char *path,bool concat_path);



 DtwStringArray *  dtw_list_files_recursively(const char *path,bool concat_path);


 DtwStringArray * dtw_list_all_recursively(const char *path,bool concat_path);
//fdefine.sha256.c




char * calc_sha_256_returning_string(const void *input, size_t len)
;

void  calc_sha_256_from_string(uint8_t hash[SIZE_OF_SHA_256_HASH], const char *input)
;

char * calc_sha_256_from_string_returning_string(const char *input)
;

int calc_sha_256_from_file(uint8_t hash[SIZE_OF_SHA_256_HASH], const char *filename)
;

char * calc_sha_256_from_file_returning_string(const char *filename)
;
char * sha256_open_file(const char *filename, int *size);
//fdefine.numeral_io.c



long dtw_load_long_file_content_setting_error(const char *path,int *error);


long dtw_load_long_file_content(const char * path);


double dtw_load_double_file_content_setting_error(const char * path, int *error);


double dtw_load_double_file_content(const char * path);


bool dtw_load_bool_file_content_setting_error(const char * path, int *error);


bool dtw_load_bool_file_content(const char * path);



void dtw_write_long_file_content(const char *path, long value);


void dtw_write_double_file_content(const char *path,double value);


void dtw_write_bool_file_content(const char *path, bool value);
//string_array/fdefine.string_array.c




struct DtwStringArray * newDtwStringArray();

int DtwStringArray_find_position( DtwStringArray *self, const char *string);


void DtwStringArray_set_value( DtwStringArray *self, int index, const char *value);
void DtwStringArray_append_getting_ownership( DtwStringArray *self, char *string);

// Function prototypes
void DtwStringArray_append( DtwStringArray *self, const  char *string);

void DtwStringArray_pop( DtwStringArray *self, int position);

void DtwStringArray_merge( DtwStringArray *self,  DtwStringArray *other);


void DtwStringArray_represent( DtwStringArray *self);

int private_dtw_string_cmp(const void *a, const void *b);

void DtwStringArray_sort(struct DtwStringArray *self) ;

 DtwStringArray * DtwStringArray_clone(DtwStringArray *self);

char * privateDtwStringArray_append_if_not_included(DtwStringArray *self,char *value);
void DtwStringArray_free(struct DtwStringArray *self);
//monodimension_listage/fdefine.monodimension_listage_win32.c



#ifdef _WIN32


bool private_dtw_verify_if_add(const int expected_type, WIN32_FIND_DATAA entry);

bool private_dtw_verify_if_skip(WIN32_FIND_DATAA *entry);

struct DtwStringArray *  dtw_list_basic(const char *path,int expected_type,bool concat_path);
#endif
//monodimension_listage/fdefine.monodimension_listage_linux.c




#if defined(__linux__) || defined(__APPLE__)

bool private_dtw_verify_if_add(const int expected_type, int d_type);
bool private_dtw_verify_if_skip(struct dirent *entry);

struct DtwStringArray * dtw_list_basic(const char *path,int expected_type,bool concat_path);

#endif
//path/fdefine.getters.c




char * DtwPath_get_name(struct DtwPath *self);
char * DtwPath_get_extension(struct DtwPath *self);

char * DtwPath_get_full_name(struct DtwPath *self);

char * DtwPath_get_dir(struct DtwPath *self);

char * DtwPath_get_path(struct DtwPath *self);
//path/fdefine.index.c



int DtwPath_get_total_dirs(DtwPath *self);

char *DtwPath_get_sub_dirs_from_index(DtwPath *self, int start, int end);



int private_dtw_count_dirs_before(const char *dirs,int index);

void DtwPath_insert_dir_at_index(DtwPath *self, int index, const char *dir);



void DtwPath_remove_sub_dirs_at_index(DtwPath *self, int start, int end);
//path/fdefine.meta.c



void DtwPath_insert_dir_after(DtwPath *self,const char *str,const char *dir);

void DtwPath_insert_dir_before(DtwPath *self,const char *str,const char *dir);

void DtwPath_remove_sub_dirs_at(DtwPath *self,const char *str);
//path/fdefine.setters.c




void DtwPath_set_extension(struct DtwPath *self, const char *extension);


void DtwPath_set_name(struct DtwPath * self, const char * name);



void DtwPath_set_full_name(struct DtwPath * self, const char * full_name);


void DtwPath_set_dir(struct DtwPath *self, const char *dir);


void DtwPath_set_path(struct DtwPath *self, const char *target_path) ;


void DtwPath_add_start_dir(struct DtwPath *self, const char *start_dir);

void DtwPath_add_end_dir(struct DtwPath *self, const char *end_dir);

void DtwPath_replace_dirs(DtwPath *self,const char *str,const char *dir);
//path/fdefine.basic.c




struct DtwPath * newDtwPath(const char *path) ;
bool DtwPath_changed(struct DtwPath *self);




void DtwPath_represent(struct DtwPath *self);



void DtwPath_free(struct DtwPath *self) ;
//hash/fdefine.hash.c








DtwHash * newDtwHash();

bool  DtwHash_digest_any(DtwHash *self,unsigned char *content,long size);

bool  DtwHash_digest_string(DtwHash * self, const char *content);

void DtwHash_digest_long(DtwHash * self,long content);

void DtwHash_digest_double(DtwHash * self,double content);

void DtwHash_digest_bool(DtwHash * self,bool content);

bool  DtwHash_digest_file(DtwHash * self, const char *path);

bool  DtwHash_digest_entity_last_modification(DtwHash * self, const char *path);


bool  DtwHash_digest_string_array(DtwHash *self,DtwStringArray *element);

bool  DtwHash_digest_string_array_last_modifications(DtwHash *self,DtwStringArray *element);

bool DtwHash_digest_string_array_last_modifications_adding_name(DtwHash *self,DtwStringArray *element);


bool DtwHash_digest_string_array_content(DtwHash *self,DtwStringArray *element);

bool DtwHash_digest_string_array_content_adding_name(DtwHash *self,DtwStringArray *element);


bool DtwHash_digest_folder_by_last_modification(DtwHash *self,const char *path);

bool DtwHash_digest_folder_by_content(DtwHash *self,const char *path);

void  DtwHash_free(DtwHash *self);
//encryption/fdefine.aesCBC_encryption.c



void privteDtwAES_CBC_EncryptionInterface_encrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

void privteDtwAES_CBC_EncryptionInterface_decrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

DtwEncriptionInterface *newDtwAES_CBC_EncryptionInterface(const uint8_t* key,int key_size,const uint8_t *iv, int iv_size);
DtwEncriptionInterface *newDtwAES_CBC_EncryptionInterface_str(const char* key,const char *iv);
//encryption/fdefine.aesECB_encryption.c

void privteDtwAES_ECB_EncryptionInterface_encrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

void privteDtwAES_ECB_EncryptionInterface_decrypt_buffer(privateDtwAES_RAW_EncryptionInterface *self,uint8_t* buf, uint32_t length);

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface(const uint8_t* key,int key_size);

DtwEncriptionInterface *newDtwAES_ECB_EncryptionInterface_str(const char* key);//randonizer/fdefine.randonizer.c






DtwRandonizer * newDtwRandonizer();

int DtwRandonizer_generate_num(DtwRandonizer *self,int max) ;
char * DtwRandonizer_generate_token(struct DtwRandonizer*self, int size);

void DtwRandonizer_free(struct DtwRandonizer *self);
//namespace/string_array_module/fdefine.string_array_module.c



DtwStringArrayModule newDtwStringArrayModule();
//namespace/database_schema_module/fdefine.database_schema_module.c




DtwDatabaseSchemaModule newDtwDatabaseSchemaModule();
//namespace/namespace/fdefine.namespace.c



DtwNamespace newDtwNamespace();
//namespace/randonizer_module/fdefine.randonizer_module.c




DtwRandonizerModule newDtwRandonizerModule();
//namespace/hash_module/fdefine.hash_module.c




DtwHashModule newDtwHashModule();
//namespace/path_module/fdefine.path_module.c



DtwPathModule newDtwPathModule();
//namespace/encryption/fdefine.encryption_namespace.c


DtwEncryptionNamespace newDtwEncryptionNamespace();//namespace/schema_module/fdefine.schema_module.c




DtwSchemaModule newDtwSchemaModule();
//namespace/locker/fdefine.locker.c



DtwLockerModule newDtwLockerModule();
//resource/resource/fdefine.custom_constructors.c




DtwResource * DtwResource_sub_resource_next(DtwResource *self, const char *end_path);


DtwResource * DtwResource_sub_resource_now(DtwResource *self, const char *end_path);


DtwResource * DtwResource_sub_resource_now_in_unix(DtwResource *self, const char *end_path);

DtwResource * DtwResource_sub_resource_random(DtwResource *self, const char *end_path);
//resource/resource/fdefine.getters.c



unsigned char *DtwResource_get_any(DtwResource *self, long *size, bool *is_binary);

unsigned char *DtwResource_get_any_from_sub_resource(DtwResource *self, long *size, bool *is_binary,const char *format,...);

unsigned char *DtwResource_get_binary(DtwResource *self, long *size);

unsigned char *DtwResource_get_binary_from_sub_resource(DtwResource *self, long *size,const char *format,...);


char *DtwResource_get_string(DtwResource *self);


char *DtwResource_get_string_from_sub_resource(DtwResource *self,const char *format,...);


long DtwResource_get_long(DtwResource *self);


long DtwResource_get_long_from_sub_resource(DtwResource *self,const char *format,...);


double DtwResource_get_double(DtwResource *self);

double DtwResource_get_double_from_sub_resource(DtwResource *self,const char *format,...);


bool DtwResource_get_bool(DtwResource *self);

bool DtwResource_get_bool_from_sub_resource(DtwResource *self,const char *format,...);
//resource/resource/fdefine.extras.c





bool DtwResource_error(DtwResource *self);

void DtwResource_set_encryption(DtwResource *self,DtwEncriptionInterface *encryption_interface,short mode);

int DtwResource_get_error_code(DtwResource *self);
char * DtwResource_get_error_path(DtwResource *self);


char * DtwResource_get_error_message(DtwResource *self);
void  DtwResource_clear_errors(DtwResource *self);


void  private_DtwResource_raise_error(DtwResource *self, int error_code, const char *format,...);

void DtwResource_rename(DtwResource *self,const char *new_name);

void DtwResource_rename_sub_resource(DtwResource *self,const char *old_name,const  char *new_name);

int DtwResource_lock(DtwResource *self);

void DtwResource_unlock(DtwResource *self);


void DtwResource_set_Resource_as_encryption_object_owner(DtwResource *self);
void DtwResource_commit(DtwResource *self);

long DtwResource_size(DtwResource *self);



DtwStringArray *DtwResource_list_names(DtwResource *self);

int DtwResource_type(DtwResource *self);
bool DtwResource_is_file(DtwResource *self);

const char * DtwResource_type_in_str(DtwResource *self);

void DtwResource_represent(DtwResource *self);
//resource/resource/fdefine.schema.c



bool private_DtwResource_its_a_pk(DtwResource *self);

void privateDtwResource_ensure_its_possible_to_sub_resource(DtwResource *self);


DtwResource * DtwResource_new_schema_insertion(DtwResource *self);

DtwResource  *DtwResource_find_by_name_id(DtwResource *self, const char *name);
DtwResource * DtwResource_find_by_primary_key_with_binary(DtwResource *self, const char *primary_key, unsigned  char *value, long size);



DtwResource * DtwResource_find_by_primary_key_with_string(DtwResource *self, const char *key, const char *value);


void DtwResource_dangerous_remove_schema_prop(DtwResource*self,const char *prop);


void DtwResource_dangerous_rename_schema_prop(DtwResource*self,const char *prop,const char *new_name);



DtwDatabaseSchema * DtwResource_newDatabaseSchema(DtwResource *self);
//resource/resource/fdefine.loaders_and_unloaders.c




void DtwResource_unload(DtwResource *self);

void DtwResource_load(DtwResource *self);
void DtwResource_load_if_not_loaded(DtwResource *self);
//resource/resource/fdefine.constructors_and_destructors.c




DtwResource *new_DtwResource(const char *path);

DtwResource * DtwResource_sub_resource(DtwResource *self,const  char *format, ...);
DtwResource * DtwResource_sub_resource_ensuring_not_exist(DtwResource *self,const  char *format, ...);

void DtwResource_free(DtwResource *self);
//resource/resource/fdefine.sub_resource_setters.c



void DtwResource_set_any_in_sub_resource(DtwResource *self,const char *key, unsigned char *element, long size,bool is_binary) ;

void DtwResource_set_binary_in_sub_resource(DtwResource *self,const char *key, unsigned char *element, long size);

void DtwResource_set_binary_sha_in_sub_resource(DtwResource *self, const char *key, unsigned  char *value, long size);


void DtwResource_set_string_sha_in_sub_resource(DtwResource *self, const char *key, const char *value);

void DtwResource_set_string_in_sub_resource(DtwResource *self, const char *key, const  char *element);

void DtwResource_set_long_in_sub_resource(DtwResource *self, const char *key, long element);

void DtwResource_set_double_in_sub_resource(DtwResource *self, const char *key, double element);

void DtwResource_set_bool_in_sub_resource(DtwResource *self,const char *key, bool element);
//resource/resource/fdefine.destroy.c



void private_DtwResurce_destroy_primary_key(DtwResource *self) ;
void private_DtwResource_destroy_all_primary_keys(DtwResource *self);
void DtwResource_destroy(DtwResource *self);

void DtwResource_destroy_sub_resource(DtwResource *self, const char *key);
//resource/resource/fdefine.setters.c




void private_dtw_resource_set_primary_key(DtwResource *self, unsigned  char *element, long size);
void DtwResource_set_any(DtwResource *self, unsigned char *element, long size,bool is_binary);
void DtwResource_set_binary(DtwResource *self, unsigned char *element, long size);

void DtwResource_set_string(DtwResource *self,const  char *element);

void DtwResource_set_binary_sha(DtwResource *self, unsigned  char *value, long size);

void DtwResource_set_string_sha(DtwResource *self,const char *value);








void DtwResource_set_long(DtwResource *self,long element);

void DtwResource_set_double(DtwResource *self,double element);

void DtwResource_set_bool( DtwResource *self,bool element);
//resource/resource/fdefine.resource_array.c


#include <time.h>


DtwResourceArray * DtwResource_get_schema_values(DtwResource *self);


DtwResourceArray * DtwResource_sub_resources(DtwResource *self);
//resource/resource_array/fdefine.resource_array.c





DtwResourceArray * newDtwResourceArray();


void DtwResourceArray_append(DtwResourceArray *self, DtwResource *element);


DtwResource* DtwResourceArray_get_by_name(DtwResourceArray *self, const char *name);



void DtwResourceArray_represent(DtwResourceArray *self);

void DtwResourceArray_free(DtwResourceArray *self);
//resource/database_schema/fdefine.database_schema.c



DtwDatabaseSchema *private_newDtwDtatabaseSchema();


DtwSchema * privateDtwDtatabaseSchema_get_sub_schema(DtwDatabaseSchema *self,const char *name);

DtwSchema * DtwDtatabaseSchema_new_subSchema(DtwDatabaseSchema *self,const char *name);



void private_new_DtwDtatabaseSchema_free(DtwDatabaseSchema *self);
//resource/root_props/fdefine.root_props.c




privateDtwResourceRootProps *private_newDtwResourceRootProps();


void privateDtwResourceRootProps_free(privateDtwResourceRootProps *self);
//resource/schema/fdefine.schema.c



DtwSchema *private_newDtwSchema(const char *name);


DtwSchema * privateDtwSchema_get_sub_schema(DtwSchema *self,const char *name);

DtwSchema * DtwSchema_new_subSchema(DtwSchema *self,const char *name);


void DtwSchema_add_primary_key(DtwSchema *self,const char *name);

void private_newDtwSchema_free(DtwSchema *self);
//transaction/action/fdefine.action_parsment.c



short DtwActionTransaction_convert_action_to_integer(char *action);

const char * DtwActionTransaction_convert_action_to_string(int action);

DtwJsonTransactionError * private_dtw_validate_json_action_transaction(cJSON *json_obj);


DtwActionTransaction * private_DtwActionTransaction_parse_json_object(cJSON *json_obj);

cJSON *  private_DtwActionTransaction_create_json_object(DtwActionTransaction* self);



void DtwActionTransaction_represent(DtwActionTransaction* self);
//transaction/action/fdefine.action.c




DtwActionTransaction * newDtwActionTransaction();


DtwActionTransaction * DtwActionTransaction_write_any(DtwEncriptionInterface *encryption, short encryption_mode, const char *source, unsigned  char *content,long size,bool is_binary);


DtwActionTransaction * DtwActionTransaction_move_any(const char *source, const char *dest);


DtwActionTransaction * DtwActionTransaction_copy_any(const char *source, const char *dest);
DtwActionTransaction * DtwActionTransaction_move_any_merging(const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_copy_any_merging(const char *source, const char *dest);

DtwActionTransaction * DtwActionTransaction_delete_any(const char *source);



void DtwActionTransaction_commit(DtwActionTransaction* self,const char *path);


void DtwActionTransaction_free(DtwActionTransaction* self);
//transaction/transaction/fdefine.transaction_parsment.c




DtwJsonTransactionError * dtw_validate_json_transaction(cJSON *json_entry);


DtwJsonTransactionError * dtw_validate_json_transaction_file(const char *filename);


DtwTransaction * newDtwTransaction_from_json(cJSON *json_entry);



DtwTransaction * newDtwTransaction_from_json_file(const char *filename);

cJSON * DtwTransaction_dumps_to_json(struct DtwTransaction *self);


void DtwTransaction_dumps_to_json_file(struct DtwTransaction *self,const char *filename);

void DtwTransaction_represent(struct DtwTransaction *self);
//transaction/transaction/fdefine.transaction.c




DtwTransaction * newDtwTransaction();

void DtwTransaction_set_transaction_as_encryption_object_owner(DtwTransaction *self);

void DtwTransaction_set_encryption(DtwTransaction *self,DtwEncriptionInterface *encryption,short encryiption_mode);

void DtwTransaction_append_action(struct DtwTransaction *self,struct DtwActionTransaction  *action);


void DtwTransaction_remove_from_index(DtwTransaction *self,long index);
void DtwTransaction_filter(DtwTransaction *self,bool (*callback)(DtwActionTransaction *action));

void DtwTransaction_remove_from_source(DtwTransaction *self,const char *source);


void DtwTransaction_write_any(struct DtwTransaction *self,const char *path,unsigned char *content, long size,bool is_binary);

void DtwTransaction_write_string(struct DtwTransaction *self,const char *path,const char *content);


void DtwTransaction_write_long(struct DtwTransaction *self,const char *path,long value);

void DtwTransaction_write_bool(struct DtwTransaction *self,const char *path,bool value);

void DtwTransaction_write_double(struct DtwTransaction *self,const char *path,double value);


void DtwTransaction_move_any(struct DtwTransaction *self,const char *source,const char *dest);

void DtwTransaction_copy_any(struct DtwTransaction *self,const char *source,const char *dest);

void DtwTransaction_move_any_merging(struct DtwTransaction *self,const char *source,const char *dest);


void DtwTransaction_copy_any_merging(struct DtwTransaction *self,const char *source,const char *dest);


void DtwTransaction_delete_any(struct DtwTransaction *self,const char *source);



void DtwTransaction_commit(struct DtwTransaction *self,const char *path);



void DtwTransaction_free(struct DtwTransaction *self);
//transaction/json_error/fdefine.json_transaction_error.c







DtwJsonTransactionError * private_new_DtwJsonTransactionError( int code,const char *mensage,const  char *path);

void DtwJsonTransactionError_represent(struct DtwJsonTransactionError *self);

void DtwJsonTransactionError_prepend_path(struct DtwJsonTransactionError *self,char *path);


void DtwJsonTransactionError_free(struct DtwJsonTransactionError *self);
//tree/tree_part/fdefine.hardware_tree_part.c








void DtwTreePart_load_content_from_hardware(struct DtwTreePart *self);



bool DtwTreePart_hardware_remove(struct DtwTreePart *self, int transaction);

bool DtwTreePart_hardware_write(struct DtwTreePart *self, int transaction);

bool DtwTreePart_hardware_modify(struct DtwTreePart *self, int transaction);

bool DtwTreePart_hardware_commit(struct DtwTreePart *self);
//tree/tree_part/fdefine.tree_part.c




void private_DtwTreePart_set_last_modification(DtwTreePart *self,long last_modification) ;
 DtwTreePart * newDtwTreePart(const char *path, DtwTreeProps props);
char *DtwTreePart_get_content_string_by_reference(struct DtwTreePart *self);

unsigned char *DtwTreePart_get_content_binary_by_reference(struct DtwTreePart *self);


  DtwTreePart * DtwTreePart_self_copy( DtwTreePart *self);

void DtwTreePart_set_any_content( DtwTreePart *self, unsigned char *content, long content_size, bool is_binary);

void DtwTreePart_set_string_content( DtwTreePart *self, const char *content);

void DtwTreePart_set_binary_content( DtwTreePart *self, unsigned char *content, long content_size);


char *DtwTreePart_get_content_sha( DtwTreePart *self);







void DtwTreePart_represent(struct DtwTreePart *self);


void DtwTreePart_free_content(struct DtwTreePart *self);
void DtwTreePart_free(struct DtwTreePart *self);

 DtwTreePart * newDtwTreePartEmpty(const char *path);


 DtwTreePart * newDtwTreePartLoading(const char *path);
//tree/tree/fdefine.tree_finding.c



struct DtwTreePart *DtwTree_find_tree_part_by_function(
        struct DtwTree *self,
        bool (*caller)(struct  DtwTreePart *part,void *args),
        void *args
);

struct DtwTree *DtwTree_filter(
        struct DtwTree *self,
        bool (*caller)(struct  DtwTreePart *part)
);


 DtwTree *DtwTree_map(DtwTree *self,DtwTreePart *(*caller)( DtwTreePart *part));


 DtwTreePart *DtwTree_find_tree_part_by_name( DtwTree *self, const char *name);

 DtwTreePart *DtwTree_find_tree_part_by_path( DtwTree *self, const char *path);
//tree/tree/fdefine.tree.c





struct  DtwTree * newDtwTree();


struct DtwTree *DtwTree_get_sub_tree(struct DtwTree *self, const char *path, bool copy_content);

void DtwTree_add_tree_part_referencing(struct DtwTree *self, struct DtwTreePart *tree_part) ;

void DtwTree_add_tree_part_copy( DtwTree *self,  DtwTreePart *tree_part);

void DtwTree_remove_tree_part(struct DtwTree *self, int position);

struct DtwTreeTransactionReport * DtwTree_create_report(struct DtwTree *self);


void DtwTree_add_tree_part_getting_onwership( DtwTree *self,  DtwTreePart *tree_part);



void DtwTree_represent( DtwTree *self);

void DtwTree_add_tree_parts_from_string_array( DtwTree *self,  DtwStringArray *paths,DtwTreeProps props);


void DtwTree_add_tree_from_hardware( DtwTree *self,const char *path, DtwTreeProps props);

void DtwTree_free( DtwTree *self);
void DtwTree_insecure_hardware_remove_tree(struct DtwTree *self);

void DtwTree_insecure_hardware_write_tree(struct DtwTree *self);

void DtwTree_hardware_commit_tree(struct DtwTree *self);
//tree/tree/fdefine.json_tree.c




bool DtwTree_loads_json_tree(struct DtwTree *self, const char *all_tree);


bool DtwTree_loads_json_tree_from_file( DtwTree *self, const char *path);

char * DtwTree_dumps_tree_json( DtwTree *self, DtwTreeProps  props);

void  DtwTree_dumps_tree_json_to_file(struct DtwTree *self, const char *path, DtwTreeProps  props);
//tree/tree/fdefine.listage.c



//listages
 DtwStringArray *DtwTree_list_files( DtwTree *self, const char *path,bool concat_path);

 DtwStringArray *DtwTree_list_dirs( DtwTree *self, const char *path,bool concat_path);

struct DtwStringArray *DtwTree_list_all( DtwTree *self, const char *path,bool concat_path);

 DtwStringArray *DtwTree_list_files_recursively( DtwTree *self, const char *path,bool concat_path);

 DtwStringArray *DtwTree_list_dirs_recursively( DtwTree *self, const char *path,bool concat_path);


 DtwStringArray *DtwTree_list_all_recursively( DtwTree *self, const char *path,bool concat_path);
//tree/json_error/fdefine.json_error.c



DtwJsonTreeError * newDtwJsonError();

DtwJsonTreeError * DtwJsonTreeError_validate_json_tree_by_cJSON(cJSON *json_tree);

 DtwJsonTreeError * DtwJsonTreeError_validate_json_tree_by_content(const char *content);




void DtwJsonTreeError_represent( DtwJsonTreeError *self);

void DtwJsonTreeError_free(struct DtwJsonTreeError *self);
//tree/tree_props/fdefine.tree_props.c



DtwTreeProps DtwTreeProps_format_props(DtwTreeProps props);
//tree/transaction_report/fdefine.transaction_report.c




struct DtwTreeTransactionReport * newDtwTreeTransactionReport();

void  DtwTreeTransactionReport_represent(struct DtwTreeTransactionReport *report);

void  DtwTreeTransactionReport_free(struct DtwTreeTransactionReport *report);
//encryption/encryption_interface/fdefine.custom_saves.c


bool private_DtwEncriptionInterface_write_any_content_custom_mode(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size,short mode);



unsigned char *private_DtwEncriptionInterface_load_any_content_custom_mode(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary,short mode);//encryption/encryption_interface/fdefine.encryption_interface_basic.c


DtwEncriptionInterface *newDtwEncriptionInterface_raw(void *obj,    unsigned char *(*encrypt_buffer)(void *obj, unsigned char *value,long size,long *out_size), unsigned char *(*decrypt_buffer)(void *obj, unsigned char *encrypted_value,long size,long *out_size), void (*free_obj)(void *obj));

unsigned char *DtwEncriptionInterface_encrypt_buffer(DtwEncriptionInterface *self, unsigned char *value,long size,long *out_size);


unsigned char *DtwEncriptionInterface_decrypt_buffer(DtwEncriptionInterface *self, unsigned char *encrypted_value,long size,long *out_size,bool *is_binary);

void DtwEncriptionInterface_free(DtwEncriptionInterface *self);//encryption/encryption_interface/fdefine.encryption_interface_files.c



bool DtwEncriptionInterface_write_any_content(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);


bool DtwEncriptionInterface_write_string_file_content(DtwEncriptionInterface *self,const char *file_name,const char *value);


unsigned char *DtwEncriptionInterface_load_any_content(DtwEncriptionInterface *self,const char *file_name,long *out_size,bool *is_binary);




char *DtwEncriptionInterface_load_string_file_content(DtwEncriptionInterface *self,const char *file_name);

//encryption/encryption_interface/fdefine.encryption_interface_hex.c





char *DtwEncriptionInterface_encrypt_buffer_hex(DtwEncriptionInterface *self, unsigned char *value,long size);



unsigned char *DtwEncriptionInterface_decrypt_buffer_hex(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary);


bool DtwEncriptionInterface_write_any_content_hex(DtwEncriptionInterface *self,const char *file_name,unsigned char  *value,long size);

bool DtwEncriptionInterface_write_string_file_content_hex(DtwEncriptionInterface *self,const char *file_name,const char *value);

unsigned char *DtwEncriptionInterface_load_any_content_hex(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);

char *DtwEncriptionInterface_load_string_file_content_hex(DtwEncriptionInterface *self,const char *file_name);

//encryption/encryption_interface/fdefine.encryption_interface_b64.c


char *DtwEncriptionInterface_encrypt_buffer_b64(DtwEncriptionInterface *self, unsigned char *value,long size);

unsigned char *DtwEncriptionInterface_decrypt_buffer_b64(DtwEncriptionInterface *self, const   char *encrypted_value,long *out_size,bool *is_binary);


bool DtwEncriptionInterface_write_any_content_b64(DtwEncriptionInterface *self,const char *file_name,unsigned char *value,long size);



bool DtwEncriptionInterface_write_string_file_content_b64(DtwEncriptionInterface *self,const char *file_name,const char *value);



unsigned char *DtwEncriptionInterface_load_any_content_b64(DtwEncriptionInterface *self,const  char *file_name,long *out_size,bool *is_binary);




char *DtwEncriptionInterface_load_string_file_content_b64(DtwEncriptionInterface *self,const char *file_name);

//encryption/aesCustomCBC_v1_encryption/fdefine.aesCustomCB_v1_enrcryption .c



DtwEncriptionInterface *newDtwAES_Custom_CBC_v1_interface(const char *key);
//encryption/aesRAW_encryption/fdefine.aesRAW_encryption.c


unsigned char * privateDtwAES_RAW_EncryptionInterface_encrypt_buffer(void *obj, unsigned char *value,long entry_size,long *out_size);

unsigned char *privateDtwAES_RAW_EncryptionInterface_decrypt_buffer(void *obj, unsigned char *encrypted_value,long entry_size,long *out_size);

void  privateDtwAES_RAW_EncryptionInterface_free_obj(void *obj);


DtwEncriptionInterface *newDtwAES_RAW_EncryptionInterface(const uint8_t* key,int key_size);
//lockers/multifile_locker/fdefine.multifile_locker.c





DtwMultiFileLocker *newDtwMultiFileLocker();




int  DtwMultiFIleLocker_lock(DtwMultiFileLocker *self, const char *element) ;

void DtwMultifileLocker_unlock(DtwMultiFileLocker *self, const  char *element);


void DtwMultiFileLocker_represemt(DtwMultiFileLocker *self);

void DtwMultiFileLocker_free(DtwMultiFileLocker *self);
//lockers/locker/fdefine.locker.c




DtwLocker *newDtwLocker();

int DtwLocker_lock(DtwLocker *self, const  char *element);

void DtwLocker_unlock(DtwLocker *self, const  char *element);

void DtwLocker_represemt(DtwLocker *self);

void DtwLocker_free(DtwLocker *self);
//namespace/tree_module/tree/fdefine.tree.c



DtwTreeModule newDtwTreeModule();
//namespace/tree_module/json_error/fdefine.json_error.c



DtwJsonTreeErrorModule newDtwJsonTreeErrorModule();
//namespace/tree_module/tree_part_module/fdefine.tree_part_module.c




DtwTreePartModule newDtwTreePartModule();
//namespace/tree_module/transaction_report/fdefine.transaction_report_module.c



DtwTreeTransactionReportModule newDtwTreeTransactionReportModule();
//namespace/transaction_module/json_error_module/fdefine.json_error_module.c



DtwJsonTransactionErrorModule newDtwJsonTransactionErrorModule();
//namespace/transaction_module/action/fdefine.action.c



DtwActionTransactionModule newDtwActionTransactionModule();
//namespace/transaction_module/transaction_module/fdefine.transaction_module.c




DtwTransactionModule newDtwTransactionModule();
//namespace/resource_module/resource_module/fdefine.resource_module.c



DtwResourceModule newDtwResourceModule();
//namespace/resource_module/resource_array_module/fdefine.resource_array_module.c



DtwResourceArrayModule newDtwResourceArrayModule();
//lockers/flock_locker/flock_locker/fdefine.flock_locker.c


#if defined(__linux__) || defined(__APPLE__)

DtwFlockLocker * newFlockLocker();
int  DtwFlockLocker_lock(DtwFlockLocker *self, const char *filename) ;

void private_FlockLocker_unlock_by_index(DtwFlockLocker *self, int index);
void DtwFlockLocker_unlock(DtwFlockLocker *self, const char *filename);
void  DtwFlockLocker_represent(DtwFlockLocker *self);
void  DtwFlockLocker_free(DtwFlockLocker *self);
#endif
//resource/resource/iterables/forEach/fdefine.foreach.c




DtwResourceForeachProps DtwResource_create_foreach_props( void(*callback)(DtwResource *item, void *args));

void DtwResource_foreach(DtwResource *self,DtwResourceForeachProps props);

void DtwResource_schema_foreach(DtwResource *self,DtwResourceForeachProps props);
//lockers/flock_locker/flockarray/flock_locked_element/fdefine.flock_locked_element.c

#if defined(__linux__) || defined(__APPLE__)



privateDtwFlockLockedElement * private_new_privateDtwFlockLockedElement(const char *filename, int file_descriptor);

void privateDtwFlockLockedElement_represent(privateDtwFlockLockedElement *self);
void privateDtwFlockLockedElement_free(privateDtwFlockLockedElement *self);
#endif
//lockers/flock_locker/flockarray/flock_array/fdefine.flock_array.c

#if defined(__linux__) || defined(__APPLE__)

privateDtwFlockArray * private_new_privateFlockArray();


int  privateDtwFlockArray_index_of(privateDtwFlockArray *self, const char *filename);
void privateDtwFlockArray_append(privateDtwFlockArray *self, const char *filename, int file_descriptor);

void privateDtwFlockArray_destroy_by_index(privateDtwFlockArray *self, int position);


void privateDtwFlockArray_represent(privateDtwFlockArray *self);

void privateDtwFlockArray_free(privateDtwFlockArray *self);
#endif
//resource/resource/iterables/map/default/fdefine.default.c



DtwResourceMapProps DtwResource_create_map_props(
    void *main_array,
    void(*append)(void *main_array_arg, void *item),
    void *(*callback)(DtwResource *item, void *args)
);

int  private_dtwResource_compare(const void *item1,const void*item2);

void DtwResource_map(DtwResource *self,DtwResourceMapProps props);
void DtwResource_schema_map(DtwResource *self,DtwResourceMapProps props);
//resource/resource/iterables/map/CHash/map_chash_object/fdefine.map_chash_object.c

#ifdef DTW_ALLOW_CHASH


DtwResourceCHashObjectMapProps DtwResource_createCHashObjectMapProps(
    CHash *(*callback)(DtwResource *item, void *args),
    char* (*key_provider)(DtwResource *item, void *args_filter)
);


void  *private_dtw_CHashObject_callback(DtwResource *item,void *args) ;

bool private_dtw_CHashObject_filtrage(DtwResource *item,void *args) ;

int private_dtw_CHashObject_ordenation(DtwResource *item1,DtwResource *item2,void *args) ;

void privateDtwResource_add_to_item_to_CHashObject(void* object, void *item);


CHash *DtwResource_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props);

CHash *DtwResource_schema_map_CHashObject(DtwResource *self,DtwResourceCHashObjectMapProps props);
#endif
//resource/resource/iterables/map/CHash/map_chash_array/fdefine.map_chash_array.c

#ifdef DTW_ALLOW_CHASH

DtwResourceCHashrrayMapProps  DtwResource_create_CHashrrayMapProps(    CHash *(*callback)(DtwResource *item, void *args));

void  *private_dtw_CHashArray_callback(DtwResource *item,void *args) ;

bool private_dtw_CHashArray_filtrage(DtwResource *item,void *args) ;

int private_dtw_CHashArray_ordenation(DtwResource *item1,DtwResource *item2,void *args) ;

void privateDtwResource_add_to_item_to_CHashArray_array(void* array, void *item);

CHashArray *DtwResource_map_CHashArray(DtwResource *self,DtwResourceCHashrrayMapProps props);
CHashArray *DtwResource_schema_map_CHashArray(DtwResource *self,DtwResourceCHashrrayMapProps props);
#endif
//resource/resource/iterables/map/cJSON/map_cjson_array/fdefine.map_cjson_array.c


DtwResourcecJSONArrayMapProps DtwResource_create_cJSONArrayMapProps(cJSON *(*callback)(DtwResource *item, void *args));

void  *private_dtw_cJSONArray_callback(DtwResource *item,void *args) ;

bool private_dtw_cJSONArray_filtrage(DtwResource *item,void *args) ;

int private_dtw_cJSONArray_ordenation(DtwResource *item1,DtwResource *item2,void *args) ;

void privateDtwResource_add_to_item_to_cJSONArray_array(void* array, void *item);

cJSON *DtwResource_map_cJSONArray(DtwResource *self,DtwResourcecJSONArrayMapProps props);

cJSON *DtwResource_schema_map_cJSONArray(DtwResource *self,DtwResourcecJSONArrayMapProps props);
//resource/resource/iterables/map/cJSON/map_cjson_object/fdefine.map_cjson_object.c



DtwResourcecJSONObjectMapProps DtwResource_create_cJSONObjectProps(
    cJSON *(*callback)(DtwResource *item, void *args),
    char *(*key_provider_callback)(DtwResource *item,void *args)
);

void  *private_dtw_cJSONObject_callback(DtwResource *item,void *args) ;

bool private_dtw_cJSONObject_filtrage(DtwResource *item,void *args) ;

int private_dtw_cJSONObject_ordenation(DtwResource *item1,DtwResource *item2,void *args) ;

void privateDtwResource_add_to_item_to_cJSONObject(void* object, void *item);


cJSON *DtwResource_map_cJSONObject(DtwResource *self,DtwResourcecJSONObjectMapProps props);

cJSON *DtwResource_schema_map_cJSONObject(DtwResource *self,DtwResourcecJSONObjectMapProps props);

#endif
