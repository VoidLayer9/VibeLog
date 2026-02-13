/* This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <https://unlicense.org>
 */ 
#ifndef CArgvParse_macros
#define CArgvParse_macros

#ifndef C_ARGV_PARSER_MAX_ARGS
#define C_ARGV_PARSER_MAX_ARGS 1000
#endif
#ifdef __cplusplus
#define C_ARGV_PARSER_NULL nullptr
#else
#define C_ARGV_PARSER_NULL ((void*)0)
#endif 


typedef unsigned char c_argv_bool;

#define C_ARGV_PARSER_TRUE 1
#define C_ARGV_PARSER_FALSE 0


#ifndef C_ARGV_UNUSED_START 
#define C_ARGV_UNUSED_START 1
#endif

#endif

#ifndef CArgvParse_types
#define CArgvParse_types
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct CArgvParse{

    int used_args[C_ARGV_PARSER_MAX_ARGS];
    int total_used_args;
     char **args;
    int total_args;

    const char **flag_identifiers;
    int total_flag_indentifiers;

 }CArgvParse;

#endif

#ifndef CArgvParse_typesB
#define CArgvParse_typesB
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CArgvParseNamespace{

    CArgvParse (*newCArgvParse)(int argc, char **argv);

    const char *(*get_arg)(CArgvParse *self,int index);
    long long (*get_arg_number)(CArgvParse *self,int index);
    short (*get_arg_bool)(CArgvParse *self,int index);
    
    int (*get_flag_size)(CArgvParse *self,const char **flags,int flags_size);
    
    const char *(*get_flag)(CArgvParse *self ,const char **flags,int flags_size, int index);
    long long (*get_flag_number)(CArgvParse *self ,const char **flags,int flags_size, int index);
    short (*get_flag_bool)(CArgvParse *self ,const char **flags,int flags_size, int index);
    
    const char *(*get_next_unused_arg)(CArgvParse *self);
    long long (*get_next_unused_arg_number)(CArgvParse *self);
    short (*get_next_unused_arg_bool)(CArgvParse *self);
    
    c_argv_bool (*is_flags_present)(CArgvParse *self,const char **flag,int flags_size);
    
    c_argv_bool (*is_one_of_args_present)(CArgvParse *self,const char **args,int args_size);
    
    int (*get_infinity_flag_size)(CArgvParse *self,const char **flags,int flags_size);
    
    const char *(*get_infinty_flag)(CArgvParse *self ,const char **flags,int flags_size, int index);
    long long(*get_infinty_flag_number)(CArgvParse *self ,const char **flags,int flags_size, int index);
    short (*get_infinty_flag_bool)(CArgvParse *self ,const char **flags,int flags_size, int index);
    
    int (*get_compact_flag_size)(CArgvParse *self,const char **flags,int flags_size);
    
    const char * (*get_compact_flag)(CArgvParse *self ,const char **flags,int flags_size, int index);
    long long(*get_compact_flag_number)(CArgvParse *self ,const char **flags,int flags_size, int index);
    short (*get_compact_flag_bool)(CArgvParse *self ,const char **flags,int flags_size, int index);
    
}CArgvParseNamespace;

#endif

#ifndef CArgvParse_fdeclare
#define CArgvParse_fdeclare
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end





CArgvParse newCArgvParse(int argc, char **argv);

const char *CArgvParse_get_arg(CArgvParse *self,int index);

long long CArgvParse_get_arg_number(CArgvParse *self, int index);

short CArgvParse_get_arg_bool(CArgvParse *self, int index);

int privateCArgv_parser_get_flag_identifier_start_size(CArgvParse *self,const char *flag,int flag_size);

c_argv_bool CArgvParse_is_flags_present(CArgvParse *self,const char **flags,int flags_size);

c_argv_bool CArgvParse_is_one_of_args_present(CArgvParse *self,const char **args,int args_size);

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end






int CArgvParse_get_compact_flag_size(CArgvParse *self,const char **flags,int flags_size);

const char * CArgvParse_get_compact_flag(CArgvParse *self ,const char **flags,int flags_size, int index);

long long CArgvParse_get_compact_flag_number(CArgvParse *self ,const char **flags,int flags_size, int index);

short CArgvParse_get_compact_flag_bool(CArgvParse *self ,const char **flags,int flags_size, int index);

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


int CArgvParse_get_infinity_flag_size(CArgvParse *self,const char **flags,int flags_size);

const char * CArgvParse_get_infinty_flag(CArgvParse *self ,const char **flags,int flags_size, int index);

long long CArgvParse_get_infinty_flag_number(CArgvParse *self ,const char **flags,int flags_size, int index);

short CArgvParse_get_infinty_flag_bool(CArgvParse *self ,const char **flags,int flags_size, int index);

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

CArgvParseNamespace newCArgvParseNamespace();
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end






int CArgvParse_get_flag_size(CArgvParse *self,const char **flags,int flags_size);

const char * CArgvParse_get_flag(CArgvParse *self ,const char **flags,int flags_size, int index);

long long CArgvParse_get_flag_number(CArgvParse *self, const char **flags, int flags_size, int index);

short CArgvParse_get_flag_bool(CArgvParse *self ,const char **flags,int flags_size, int index);

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


c_argv_bool private_CArgvParse_its_used(CArgvParse *self,int index);

void private_CArgvParse_add_used(CArgvParse *self,int index);

const char *CArgvParse_get_next_unused_arg(CArgvParse *self);

long long CArgvParse_get_next_unused_arg_number(CArgvParse *self);

short CArgvParse_get_next_unused_arg_bool(CArgvParse *self);

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


short privateArgv_parser_string_cmp(const char *s1, const char *s2);

long long privateArgv_parser_string_to_long_long(const char *text);

long long privateArgv_parser_string_to_long_long_by_size(const char *text, long size_length);

int privateArgv_parser_string_size(const char *string);

c_argv_bool privateArgv_parsser_starts_with(const char *string,int string_size, const char *start,int start_size);

c_argv_bool privateArgv_strings_equals(const char *string1,int string1_size,const char *string2,int string2_size);


#endif
