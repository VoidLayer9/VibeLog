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
#ifndef CWebStudio_dep_declare
#define CWebStudio_dep_declare

#if defined(__linux__) || defined(__APPLE__)
#include <sys/wait.h>
#endif

#if defined(__APPLE__)
#define CWEB_LINUX_EMULATION
#define __linux__
#define __linux
#endif

#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#if !defined(CTextEngine_fdeclare)
/* MIT License

Copyright (c) 2023 OUI

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
#ifndef CTextEngine_native_imports
#define CTextEngine_native_imports
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>


#endif

#ifndef CTextEngine_macros
#define CTextEngine_macros
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#define CTextScope(s,t)\
ctext_open(s, t);\
for(int snaunduwwqwetjsdvda = 0; snaunduwwqwetjsdvda < 1; ctext_close(s, t), ++snaunduwwqwetjsdvda)

#define CTextScope_format(s,t, ...)\
CTextStack_open_format(s,t,__VA_ARGS__);\
for(int snaunduwwqwetjsdvda = 0; snaunduwwqwetjsdvda < 1; ctext_close(s, t), ++snaunduwwqwetjsdvda)

#endif

#ifndef CTextEngine_types
#define CTextEngine_types
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct CTextStack{

    char *rendered_text;
    size_t rendered_text_alocation_size;
    size_t size;

    char *line_breaker;
    char *separator;
    int ident_level;

}CTextStack;

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#define CTEXT_LINE_BREAKER "\n"
#define CTEXT_SEPARATOR "   "

#define CTEXT_LONG 1
#define CTEXT_DOUBLE 2
#define CTEXT_BOOL 3
#define CTEXT_STRING 4

#endif

#ifndef CTextEngine_typesB
#define CTextEngine_typesB
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct CTextArray{

    CTextStack **stacks;
    long size;


}CTextArray;


#endif

#ifndef CTextEngine_typesC
#define CTextEngine_typesC
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



typedef struct CTextStackModule{

    //admnistrative methods
    CTextStack  *(*newStack)(const char *line_breaker, const char *separator);
    CTextStack *(*newStack_string)(const char *starter);
    CTextStack *(*newStack_string_format)(const char *format, ...);

    CTextStack *(*newStack_string_getting_ownership)(const char *starter);
    CTextStack *(*newStack_string_empty)();

    void (*free)(struct CTextStack *self);
    struct CTextStack *(*clone)(struct CTextStack *self);
    void (*represent)(struct CTextStack *self);
    char *(*self_transform_in_string_and_self_clear)(struct CTextStack *self);
    void (*restart)(struct CTextStack *self);

    //render methods
    void (*text)(struct CTextStack *self, const char *element);

    void (*segment_text)(struct CTextStack *self, const char *element);

    void (*format)(struct CTextStack *self, const char *format, ...);

    void (*segment)(struct CTextStack *self);

    void (*segment_format)(struct CTextStack *self, const char *format, ...);

    void (*open_format)(struct CTextStack *self, const char *tag, const char *format,...);

    void (*only_open_format)(struct CTextStack *self, const char *tag, const char *format,...);

    void (*auto_close_format)(struct CTextStack *self, const char *tag, const char *format,...);

    void (*open)(struct CTextStack *self, const char *tag);

    void (*close)(struct CTextStack *self, const char *tag);


    //algorithm methods
    struct CTextStack * (*substr)(struct CTextStack *self, long starter, long end);
    void  (*self_substr)(struct CTextStack *self, long starter, long end);


    struct CTextStack *(*pop)(struct CTextStack *self, long starter, long end);
    void(*self_pop)(struct CTextStack *self, long starter, long end);



    struct CTextStack *(*insert_at)(struct CTextStack *self,long point, const char *element);
    void (*self_insert_at)(struct CTextStack *self,long point, const char *element);

    struct CTextStack *(*replace)(struct CTextStack *self,const char *element, const char *element_to_replace);
    void (*self_replace)(struct CTextStack *self,const char *element, const char *element_to_replace);


    struct CTextStack *(*replace_long)(struct CTextStack *self,const char *element, long element_to_replace);
    void(*self_replace_long)(struct CTextStack *self,const char *element, long element_to_replace);


    struct CTextStack *(*replace_double)(struct CTextStack *self,const char *element, double element_to_replace);
    void (*self_replace_double)(struct CTextStack *self,const char *element, double element_to_replace);


    struct CTextStack * (*lower)(struct CTextStack *self);
    void(*self_lower)(struct CTextStack *self);

    struct CTextStack * (*upper)(struct CTextStack *self);
    void(*self_upper)(struct CTextStack *self);

    struct CTextStack *(*captalize)(struct CTextStack *self);
    void (*self_captalize)(struct CTextStack *self);

    struct CTextStack * (*reverse)(struct CTextStack *self);
    void(*self_reverse)(struct CTextStack *self);

    struct CTextStack * (*trim)(struct CTextStack *self);
    void(*self_trim)(struct CTextStack *self);

    bool (*starts_with)(struct CTextStack *self, const char *element);
    bool (*ends_with)(struct CTextStack *self, const char *element);

    bool (*equal)(struct  CTextStack *self,const char *element);
    int (*typeof_element)(struct CTextStack *self);
    bool (*is_a_num)(struct CTextStack *self);

    const char * (*typeof_in_str)(struct CTextStack *self);
    bool  (*parse_to_bool)(struct CTextStack *self);
    long  (*parse_to_integer)(struct CTextStack *self);
    double  (*parse_to_double)(struct CTextStack *self);

    long (*index_of)(struct CTextStack *self, const char *element);
    long (*index_of_char)(struct CTextStack *self, char element);
}CTextStackModule;



//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CTextArrayModule{
    CTextArray *(*newArray)();
    void (*append)(CTextArray *self,CTextStack *element);
    void (*append_string)(CTextArray *self,const char *element);
    CTextStack * (*join)(CTextArray *self,const char *separator);

    CTextArray * (*map)(CTextArray *self, CTextStack *(caller)(CTextStack* element));
    CTextArray * (*filter)(CTextArray *self, bool (caller)(CTextStack* element));
    void  (*foreach)(CTextArray *self, void (*caller)(CTextStack* element));
    bool (*includes)(CTextArray *self,const char *element);
    void (*represent)(CTextArray *self);
    void (*free)(CTextArray *self);

}CTextArrayModule;

#endif

#ifndef CTextEngine_typesD
#define CTextEngine_typesD
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end




typedef struct CTextNamespace{

    CTextArrayModule array;
    CTextStackModule stack;

}CTextNamespace;

#endif

#ifndef CTextEngine_consts
#define CTextEngine_consts
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#define CTEXT_BY_OWNESHIP 1
#define CTEXT_BY_COPY 2
#define CTEXT_BY_REFERENCE 3

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end
//
// Created by jurandi on 18-04-2023.
//
#define CTEXT_HTML "html"
#define CTEXT_BODY "body"
#define CTEXT_DIV "div"
#define CTEXT_H1 "h1"
#define CTEXT_H2 "h2"
#define CTEXT_H3 "h3"
#define CTEXT_H4 "h4"
#define CTEXT_H5 "h5"
#define CTEXT_H6 "h6"
#define CTEXT_P "p"
#define CTEXT_SPAN "span"
#define CTEXT_A "a"
#define CTEXT_IMG "img"
#define CTEXT_INPUT "input"
#define CTEXT_BUTTON "button"
#define CTEXT_TABLE "table"
#define CTEXT_TR "tr"
#define CTEXT_TD "td"
#define TH "th"
#define CTEXT_THEAD "thead"
#define CTEXT_TBODY "tbody"
#define CTEXT_TFOOT "tfoot"
#define CTEXT_UL "ul"
#define CTEXT_LI "li"
#define CTEXT_OL "ol"
#define CTEXT_FORM "form"
#define CTEXT_LABEL "label"
#define CTEXT_SELECT "select"
#define CTEXT_OPTION "option"
#define CTEXT_TEXTAREA "textarea"
#define CTEXT_SCRIPT "script"
#define CTEXT_STYLE "style"
#define CTEXT_META "meta"
#define CTEXT_LINK "link"
#define CTEXT_HEAD "head"
#define CTEXT_BASE "base"
#define CTEXT_BR "br"
#define CTEXT_HR "hr"
#define CTEXT_TITLE "title"
#define CTEXT_IFRAME "iframe"
#define CTEXT_NAV "nav"
#define CTEXT_HEADER "header"
#define CTEXT_FOOTER "footer"
#define CTEXT_SECTION "section"
#define CTEXT_ARTICLE "article"
#define CTEXT_ASIDE "aside"
#define CTEXT_DETAILS "details"
#define CTEXT_SUMMARY "summary"
#define CTEXT_DIALOG "dialog"
#define MENU "menu"
#define MENUITEM "menuitem"
#define CTEXT_MAIN "main"
#define CTEXT_CANVAS "canvas"
#define CTEXT_AUDIO "audio"
#define CTEXT_VIDEO "video"
#define CTEXT_SOURCE "source"
#define CTEXT_TRACK "track"
#define CTEXT_EMBED "embed"
#define CTEXT_PARAM "param"
    




#endif

#ifndef CTextEngine_fdeclare
#define CTextEngine_fdeclare
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


CTextArray * newCTextArray();


void CTextArray_append(CTextArray *self,CTextStack *element);


void CTextArray_append_string(CTextArray *self,const char *element);

CTextStack * CTextArray_join(CTextArray *self,const char *separator);

CTextArray * CTextArray_split(const char *element,const char *target);

CTextArray * CTextArray_map(CTextArray *self, CTextStack *(caller)(CTextStack* element));

CTextArray * CTextArray_filter(CTextArray *self, bool (caller)(CTextStack* element));

void  CTextArray_foreach(CTextArray *self, void (*caller)(CTextStack* element));

bool CTextArray_includes(CTextArray *self,const char *element);

void  CTextArray_free(CTextArray *self);

void CTextArray_represent(CTextArray *self);

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

CTextStackModule newCTextStackModule();

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



CTextArrayModule newCTextArrayModule();

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


CTextNamespace newCTextNamespace();

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end






char * CTextStack_self_transform_in_string_and_self_clear(struct CTextStack *self);

void private_CTextStack_parse_ownership(struct CTextStack *self, struct CTextStack *new_stack);

void CTextStack_restart(struct CTextStack *self);

void CTextStack_represent(struct CTextStack *self);

void CTextStack_free(struct CTextStack *self);

 CTextStack * CTextStack_clone(struct CTextStack *self);

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



 CTextStack * CTextStack_substr(struct CTextStack *self, long starter, long end);


void CTextStack_self_substr(struct CTextStack *self, long starter, long end);

struct CTextStack *CTextStack_replace(struct CTextStack *self,const char *element, const char *element_to_replace);

void CTextStack_self_replace(struct CTextStack *self,const char *element, const char *element_to_replace);


struct CTextStack *CTextStack_replace_long(struct CTextStack *self,const char *element, long element_to_replace);



void CTextStack_self_replace_long(struct CTextStack *self,const char *element, long element_to_replace);


struct CTextStack *CTextStack_replace_double(struct CTextStack *self,const char *element, double element_to_replace);


void CTextStack_self_replace_double(struct CTextStack *self,const char *element, double element_to_replace);


long CTextStack_index_of(struct  CTextStack *self, const char *element);

long CTextStack_index_of_char(struct  CTextStack *self, char element);

bool CTextStack_starts_with(struct  CTextStack *self, const char *element);


bool CTextStack_ends_with(struct  CTextStack *self, const char *element);



struct CTextStack *CTextStack_lower(struct CTextStack *self);

void CTextStack_self_lower(struct CTextStack *self);


struct CTextStack *CTextStack_upper(struct CTextStack *self);


CTextStack *CTextStack_captalize(struct CTextStack *self);

void CTextStack_self_captalize(struct CTextStack *self);


void CTextStack_self_upper(struct CTextStack *self);


 CTextStack *CTextStack_reverse(struct CTextStack *self);

void CTextStack_self_reverse(struct CTextStack *self);


CTextStack *CTextStack_pop(struct CTextStack *self, long starter, long end);


void  CTextStack_self_pop(struct CTextStack *self, long starter, long end);



CTextStack *CTextStack_insert_at(struct CTextStack *self,long point, const char *element);


void CTextStack_self_insert_at(struct CTextStack *self,long point, const char *element);

CTextStack *CTextStack_trim(struct CTextStack *self);

void CTextStack_self_trim(struct CTextStack *self);

bool CTextStack_equal(  CTextStack *self,const char *element);

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

 CTextStack * newCTextStack(const char *line_breaker, const char *separator);

 CTextStack *newCTextStack_string(const char *starter);


 CTextStack *newCTextStack_string_format(const char *format, ...);


 CTextStack *newCTextStack_string_getting_ownership(const char *starter);

 CTextStack *newCTextStack_string_empty();

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

int CTextStack_typeof(struct CTextStack *self);

bool CTextStack_is_a_num(struct CTextStack *self);

const char * CTextStack_typeof_in_str(struct CTextStack *self);

bool  CTextStack_parse_to_bool(struct CTextStack *self);

long  CTextStack_parse_to_integer(struct CTextStack *self);

double  CTextStack_parse_to_double(struct CTextStack *self);

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

void private_ctext_text_double_size_if_reachs(struct CTextStack *self);


void CTextStack_text(struct CTextStack *self, const char *text);



void CTextStack_segment_text(struct CTextStack *self, const char *text);


void CTextStack_format(struct CTextStack *self, const char *format, ...);


void CTextStack_segment_format(struct CTextStack *self, const char *format, ...);



void CTextStack_segment(struct CTextStack *self);


void CTextStack_open_format(struct CTextStack *self, const char *tag, const char *format, ...);




void CTextStack_only_open_format(struct CTextStack *self, const char *tag, const char *format, ...);


void CTextStack_auto_close_format(struct CTextStack *self, const char *tag, const char *format, ...);


void ctext_open(struct CTextStack *self, const char *tag);



void ctext_close(struct CTextStack *self, const char *tag);

//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


long private_CText_transform_index(long size, long value);


void private_ctext_generate_formated_text(
    struct CTextStack *stack,
    const char *format,
    va_list argptr
    );
#endif

#define CWEB_CTEXT_ENGINE_DECLARATED
#endif

#if !defined(UniversalSocket_dep) && !defined(CWEB_MOCK_UNIVERSAL_SOCKET)
/* MIT License

Copyright (c) 2024 Samuel Henrique

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
#ifndef UniversalSocket_dep
#define UniversalSocket_dep



#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>


//#define _GET_ADDR_INFO_DEFAULT_


#if defined(__linux__)
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#endif


#if defined(__APPLE__)
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#endif

#if defined(_WIN32)

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#endif

#endif

#ifndef UniversalSocket_mac
#define UniversalSocket_mac

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



#define UNI_AF_INET AF_INET
#define UNI_INADDR_ANY INADDR_ANY
#define UNI_FD_SET FD_SET
#define UNI_FD_CLR FD_CLR
#define UNI_FD_ISSET FD_ISSET
#define UNI_FD_ZERO FD_ZERO
#define UNI_SOCK_STREAM SOCK_STREAM
#define UNI_SOCK_DGRAM SOCK_DGRAM
#define UNI_SOCK_RAW SOCK_RAW
#define UNI_MSG_PEEK MSG_PEEK
#define UNI_SO_RCVTIMEO SO_RCVTIMEO
#define UNI_SO_SNDTIMEO SO_SNDTIMEO
#define UNI_SO_KEEPALIVE SO_KEEPALIVE
#define UNI_SO_BROADCAST SO_BROADCAST
#define UNI_SO_LINGER SO_LINGER
#define UNI_AF_UNSPEC AF_UNSPEC
#define UNI_IPPROTO_TCP IPPROTO_TCP
#define UNI_IPPROTO_UDP IPPROTO_UDP
#define UNI_MSG_OOB MSG_OOB
#define UNI_AF_INET6 AF_INET6
#define UNI_SHUT_RD SHUT_RD
#define UNI_SHUT_WR SHUT_WR
#define UNI_SHUT_RDWR SHUT_RDWR

#define UNI_SO_REUSEADDR SO_REUSEADDR
#define UNI_SO_RCVBUF SO_RCVBUF
#define UNI_SOL_SOCKET SOL_SOCKET
#define UNI_AF_INET6 AF_INET6

#define UNI_INET6_ADDRSTRLEN INET6_ADDRSTRLEN

#define UNI_EAI_MEMORY EAI_MEMORY

#define UNI_INET_ADDRSTRLEN INET_ADDRSTRLEN




//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



#if defined(__linux__)

#define UNI_INVALID_SOCKET -1
#define UNI_SOCKET_ERROR -1
#define UNI_EAGAIN EAGAIN
#define UNI_EWOULDBLOCK EWOULDBLOCK

#define UNI_ECONNREFUSED ECONNREFUSED
#define UNI_ETIMEDOUT ETIMEDOUT
#define UNI_EINPROGRESS EINPROGRESS
#define UNI_EADDRNOTAVAIL EADDRNOTAVAIL
#define UNI_ENETUNREACH ENETUNREACH
#define UNI_MSG_WAITALL MSG_WAITALL

#define UNI_EAI_NONAME EAI_NONAME 
#define UNI_EAI_AGAIN EAI_AGAIN
#define UNI_EAI_FAIL EAI_FAIL
#define UNI_EAI_NODATA EAI_NONAME

#endif


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



#if defined(__APPLE__)

#define UNI_INVALID_SOCKET -1
#define UNI_SOCKET_ERROR -1
#define UNI_EAGAIN EAGAIN
#define UNI_EWOULDBLOCK EWOULDBLOCK

#define UNI_ECONNREFUSED ECONNREFUSED
#define UNI_ETIMEDOUT ETIMEDOUT
#define UNI_EINPROGRESS EINPROGRESS
#define UNI_EADDRNOTAVAIL EADDRNOTAVAIL
#define UNI_ENETUNREACH ENETUNREACH
#define UNI_MSG_WAITALL MSG_WAITALL

#define UNI_EAI_NONAME EAI_NONAME 
#define UNI_EAI_AGAIN EAI_AGAIN
#define UNI_EAI_FAIL EAI_FAIL
#define UNI_EAI_NODATA EAI_NONAME

#endif


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



#if defined(_WIN32)

#define UNI_INVALID_SOCKET INVALID_SOCKET
#define UNI_SOCKET_ERROR SOCKET_ERROR
#define UNI_EAGAIN WSAEWOULDBLOCK
#define UNI_EWOULDBLOCK WSAEWOULDBLOCK
#define UNI_MSG_WAITALL 0

#define UNI_ECONNREFUSED WSAECONNREFUSED
#define UNI_ETIMEDOUT WSAETIMEDOUT
#define UNI_EINPROGRESS WSAEINPROGRESS
#define UNI_EADDRNOTAVAIL WSAEADDRNOTAVAIL
#define UNI_ENETUNREACH WSAENETUNREACH

#define UNI_EAI_NONAME WSAHOST_NOT_FOUND
#define UNI_EAI_AGAIN WSATRY_AGAIN
#define UNI_EAI_FAIL WSANO_RECOVERY
#define UNI_EAI_NODATA WSANO_DATA

#endif








#endif

#ifndef UniversalSocket_types
#define UniversalSocket_types

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct sockaddr Universal_sockaddr;

typedef struct sockaddr_in Universal_sockaddr_in;

typedef struct sockaddr_in6 Universal_sockaddr_in6;

typedef struct sockaddr_storage Universal_sockaddr_storage;

typedef struct addrinfo Universal_addrinfo;

typedef struct in_addr Universal_in_addr;

typedef struct in6_addr Universal_in6_addr;

typedef struct hostent Universal_hostent;





//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#if defined(__linux__)

typedef int Universal_socket_int;

typedef socklen_t Universal_socket_len;

typedef unsigned int Universal_DWORD;

typedef ssize_t Universal_ssize_t;

#endif


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#if defined(__APPLE__)

typedef int Universal_socket_int;

typedef socklen_t Universal_socket_len;

typedef unsigned int Universal_DWORD;

typedef ssize_t Universal_ssize_t;

#endif


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end




#if defined(_WIN32)

typedef SOCKET Universal_socket_int;

typedef int Universal_socket_len;

typedef DWORD Universal_DWORD;

typedef unsigned long in_addr_t;

typedef long Universal_ssize_t;

#endif

#endif

#ifndef UniversalSocket_dec
#define UniversalSocket_dec

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end




extern const char* Universal_inet_ntoa(Universal_in_addr addr);

extern ssize_t Universal_recv (int fd, void *buf, size_t n, int flags);



//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



extern ssize_t Universal_send (int fd, const void *buf, size_t n, int flags);

extern const char *Universal_inet_ntop(int af, const void *src, char *dst, Universal_socket_len size);

extern int Universal_inet_pton(int af, const char *src, void *dst);

uint32_t Universal_ntohl(uint32_t netlong);

uint16_t Universal_htons(uint16_t value);

uint16_t Universal_ntohs(uint16_t value);

extern in_addr_t Universal_inet_addr(const char *ip);




//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


extern int Universal_bind (int fd,Universal_sockaddr_in  *addrin , Universal_socket_len len);

extern int Universal_accept (int fd, Universal_sockaddr_in *addrin,
		   Universal_socket_len *adrr_len);

extern int Universal_listen (int fd, int n);

extern int Universal_connect(int sockfd, const Universal_sockaddr *addr, socklen_t addrlen);




//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end






int Universal_getaddrinfo(const char *node, const char *service, const Universal_addrinfo *hints, Universal_addrinfo **res);






//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



extern char *Universal_GetLastError();









//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


extern int Universal_start_all ();

extern int Universal_close (int fd);

extern int Universal_end ();

//#if defined(_GET_ADDR_INFO_DEFAULT_)

int Universal_getaddrinfo(const char *node, const char *service, const Universal_addrinfo *hints, Universal_addrinfo **res);

void Universal_freeaddrinfo(Universal_addrinfo *addrinfo_ptr);
//#endif





//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


int Universal_socket (int domain, int type, int protocol);

int Universal_ZeroMemory(void *ptr, size_t num);

int Universal_setsockopt(
    Universal_socket_int sockfd,
    int level,
    int optname,
    const void *optval,
    Universal_socket_len optlen
);

int Universal_getsockopt(
    Universal_socket_int sockfd,
    int level,
    int optname,
    void *optval,
    Universal_socket_len *optlen
);

Universal_hostent *Universal_gethostbyname(const char *hostname);






//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end




#if defined(_WIN32)

ssize_t private_Universal_recv_all(int fd, void *buf, size_t n);

#endif

#endif

#define CWEB_UNIVERSAL_SOCKET_DECLARATED
#endif 

#if !defined(cJSON__h) && !defined(CWEB_MOCK_CJSON) 
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

#define CWEB_CJSON_DECLARATED
#endif

#if !defined(UniversalGarbage_fdeclare) && !defined(CWEB_MOCK_UNIVERSAL_GARBAGE)
/* MIT License

Copyright (c) 2023 OUI

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
#ifndef UniversalGarbage_native_imports
#define UniversalGarbage_native_imports

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#endif

#ifndef UniversalGarbage_macros
#define UniversalGarbage_macros
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#define UniversalGarbage_create_empty_struct(name,element_type) \
(element_type*)malloc(sizeof(element_type));    \
*name = (element_type){0};\


#define UniversalGarbage_cast(value) ((void**)&value)


#define UniversalGarbage_add(garbage,deallocator_callback,value) \
    rawUniversalGarbage_add(garbage,(void(*)(void*))deallocator_callback,UniversalGarbage_cast(value))

#define UniversalGarbage_add_simple(garbage,value) \
     UniversalGarbage_add(garbage,free,value)


#define UniversalGarbage_add_return(garbage,deallocator_callback,value) \
        UniversalGarbage_add(garbage->return_values,deallocator_callback,value)


#define UniversalGarbage_add_simple_return(garbage,value) \
    UniversalGarbage_add_simple(garbage->return_values,value)



#define  UniversalGarbage_remove(garbage,value) \
    rawUniversalGarbage_remove(garbage,UniversalGarbage_cast(value));\


#define  UniversalGarbage_disconnect(garbage,value) \
    rawUniversalGarbage_disconnect(garbage,UniversalGarbage_cast(value));\



#define UniversalGarbage_reallocate(garbage,value) \
    rawUniversalGarbage_reallocate(garbage,UniversalGarbage_cast(value))

#define UniversalGarbage_resset(garbage,value) \
    rawUniversalGarbage_resset(garbage,UniversalGarbage_cast(value))

#endif

#ifndef UniversalGarbage_types
#define UniversalGarbage_types
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct privateUniversalGarbageElement{
    void **pointer;
    void (*deallocator_callback)(void *element);
    void *pointed_value;
}privateUniversalGarbageElement;

#endif

#ifndef UniversalGarbage_typesB
#define UniversalGarbage_typesB
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef  struct UniversalGarbage{

    struct UniversalGarbage *return_values;
    privateUniversalGarbageElement **elements;
    int  elements_size;
    bool is_the_root;

}UniversalGarbage;

#endif

#ifndef UniversalGarbage_fdeclare
#define UniversalGarbage_fdeclare
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


UniversalGarbage * newUniversalGarbage();

UniversalGarbage * private_new_MainUniversalGarbage();



bool  rawUniversalGarbage_resset(UniversalGarbage *self, void **pointer);

bool  rawUniversalGarbage_remove(UniversalGarbage *self, void **pointer);

bool  rawUniversalGarbage_disconnect(UniversalGarbage *self, void **pointer);

bool rawUniversalGarbage_reallocate(UniversalGarbage *self, void **pointer);

bool  rawUniversalGarbage_add(UniversalGarbage *self,  void (*dealocator_callback)(void *element), void **pointer);

void private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self);

void UniversalGarbage_free_including_return(UniversalGarbage *self);

void UniversalGarbage_free(UniversalGarbage *self);
//silver_chain_scope_start
//DONT MODIFY THIS COMMENT
//this import is computationally generated
//mannaged by SilverChain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



void private_UniversalGarbageSimpleElement_free_pointed_value(privateUniversalGarbageElement *self);


void private_UniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self);

privateUniversalGarbageElement * private_newUniversalGarbageSimpleElement(void (*dealocator_callback)(void *element), void **pointer);
#endif

#define CWEB_UNIVERSAL_GARBAGE_DECLARATED
#endif

#if defined (CWEB_LINUX_EMULATION)
#undef __linux__
#undef __linux
#endif

#endif

#ifndef CWebStudio_macros
#define CWebStudio_macros
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end
#define CWEB_HYDRATION_DEFAULT_BODY_SIZE 5000
#define CWEB_HYDRATION_CALBACK_HANDLER_ROUTE "/private_cweb_hydration_main_callback_handler"

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end
#define PRIVATE_CWEB_HYDRATION_CALLBACK_KEY "callback"
#define PRIVATE_CWEB_HYDRATION_ARGS_KEY "args"
#define PRIVATE_CWEB_HYDRATION_ID_KEY "id"
#define PRIVATE_CWEB_HYDRATION_HTML_KEY "html"
#define PRIVATE_CWEB_HYDRATION_MENSSAGE_KEY "menssage"


#define PRIVATE_CWEB_HYDRATION_ALERT "private_cweb_alert"
#define PRIVATE_CWEB_HYDRATION_DESTROY_BY_ID "private_cweb_destroy_by_id"
#define PRIVATE_CWEB_HYDRATION_REPLACE_BY_ID "private_cweb_hydration_replace_by_id"

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end
#define CWEB_HYDRATION_NOT_BODY_JSON_PROVIDED 1
#define CWEB_HYDRATION_NOT_BODY_JSON_PROVIDED_MSG "json body not provided"

#define CWEB_HYDRATION_NOT_BODY_IS_NOT_OBJECT 2
#define CWEB_HYDRATION_NOT_BODY_IS_NOT_OBJECT_MSG  "json body not not object"


#define CWEB_HYDRATION_NAME_NOT_PROVIDED 3
#define CWEB_HYDRATION_NAME_NOT_PROVIDED_MSG  "body['name'] not provided"

#define CWEB_HYDRATION_NAME_NOT_STRING 4
#define CWEB_HYDRATION_NAME_NOT_STRING_MSG  "body['name'] its not string"


#define CWEB_HYDRATION_ARGS_NOT_PROVIDED 5
#define CWEB_HYDRATION_ARGS_NOT_PROVIDED_MSG  "body['args'] not provided"

#define CWEB_HYDRATION_ARGS_NOT_ARRAY 6
#define CWEB_HYDRATION_ARGS_NOT_ARRAY_MSG  "body['args'] its not array"


#define CWEB_HYDRATION_CONTENT_NOT_PROVIDED 7
#define CWEB_HYDRATION_CONTENT_NOT_PROVIDED_MSG  "body['content'] not provided"

#define CWEB_HYDRATION_CONTENT_NOT_OBJECT 8
#define CWEB_HYDRATION_CONTENT_NOT_OBJECT_MSG  "body['content'] not a object"


#define CWEB_HYDRATION_CONTENT_KEY_NOT_PROVIDED 9
#define CWEB_HYDRATION_CONTENT_KEY_NOT_PROVIDED_MSG  "body['content']['%s'] not provided at content"

#define CWEB_HYDRATION_CONTENT_SEARCH_NOT_ARRAY 10
#define CWEB_HYDRATION_CONTENT_SEARCH_NOT_ARRAY_MSG "body['content']['%s']   is not of array"



#define CWEB_HYDRATION_CONTENT_SEARCH_NOT_EXIST 11
#define CWEB_HYDRATION_CONTENT_SEARCH_NOT_EXIST_MSG "search at index %d  not exist"


#define CWEB_HYDRATION_SEARCH_ITEM_NOT_EXIST 12
#define CWEB_HYDRATION_SEARCH_ITEM_NOT_EXIST_MSG "body['content']['%s'][%d] not exist"


#define CWEB_HYDRATION_SEARCH_ITEM_WRONG_TYPE 13
#define CWEB_HYDRATION_SEARCH_ITEM_WRONG_TYPE_MSG "body['content']['%s'][%d] its not of type %s"


#define CWEB_HYDRATION_INDEX_ARGS_NOT_PROVIDED  14
#define CWEB_HYDRATION_INDEX_ARGS_NOT_PROVIDED_MSG  "body['args'][%d]  not provided"

#define CWEB_HYDRATION_INDEX_ARGS_WRONG_TYPE 15
#define CWEB_HYDRATION_INDEX_ARGS_WRONG_TYPE_MSG  "body['args'][%d] is not of type %s"



#define CWEB_BRIDGE_NOT_FOUND 16
#define CWEB_BRIDGE_NOT_FOUND_MSG  "bridge of name %s not found"

#define CWEB_SEARCH_NOT_EXIST 17
#define CWEB_SEARCH_NOT_EXIST_MSG "search at index %d not exist"

#define CWEB_HYDRATION_STRING "string"
#define CWEB_HYDRATION_BOOL  "bool"
#define CWEB_HYDRATION_NUMBER "number"

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end



#define CWEB_HYDRATION_JSON_ERROR_CODE_KEY "error_code"
#define CWEB_HYDRATION_JSON_ERROR_MENSSAGE "error_menssage"
#define CWEB_HYDRATON_JSON_DATA "data"

#define CWEB_HYDRATON_JSON_NAME "name"
#define CWEB_HYDRATON_JSON_HTML "html"
#define CWEB_HYDRATON_JSON_MSG "msg"
#define CWEB_HYDRATON_JSON_CODE "code"
#define CWEB_HYDRATON_JSON_KEY "key"
#define CWEB_HYDRATON_JSON_QUERY_SELECTOR "query_selector"

#define CWEB_HYDRATON_JSON_VALUE "value"
#define CWEB_HYDRATION_JSON_URL "url"

#define CWEB_HYDRATON_JSON_ARGS "args"
#define CWEB_HYDRATON_JSON_CONTENT "content"

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end
#define INVALID_HTTP -1
#define MAX_HEADER_SIZE_CODE -2
#define MAX_HEADER_LEN 20000
#define MAX_LINE_LEN MAX_HEADER_LEN /2
#define READ_ERROR -3
#define MAX_CONTENT_SIZE -4
#define UNDEFINED_CONTENT -5
#define INVALID_JSON -6
#define CWEB_UTF_DECREMENTER  64
#define CWEB_C_NON_ASSCI_SIGIN -61

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

#define CWEB_AUTO_SET_CONTENT NULL
#define CWEB_OK  200
#define CWEB_NOT_FOUND 404
#define CWEB_BAD_REQUEST 400
#define CWEB_FORBIDDEN 403
#define CWEB_INTERNAL_SERVER_ERROR 500

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end
#ifdef CWEB_DEBUG
#define cweb_print(...) printf(__VA_ARGS__);
#else
#define cweb_print(...);
#endif

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


#endif

#ifndef CWebStudio_types
#define CWebStudio_types
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CwebKeyVal{
    char *key;
     char *value;

}CwebKeyVal;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct {
    char  *file;
    char *included;

}privateCwebRecursionElement;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CwebStringArray {
  int size;         

  char **strings;       

}CwebStringArray; // End the structure with a semicolon


#endif

#ifndef CWebStudio_typesB
#define CWebStudio_typesB
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CwebDict {
  int size;
  CwebKeyVal **keys_vals;

}CwebDict;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct  CWebHyDrationBridge {
    char *name;
    void  *hydration;
    void  (*callback)(struct CWebHyDrationBridge *bridge);

    CwebStringArray *requirements_code;

    void *extra_args;

}CWebHyDrationBridge;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct{

    privateCwebRecursionElement **elements;
    int size;

}privateCwebRecursionList;

#endif

#ifndef CWebStudio_typesC
#define CWebStudio_typesC
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct privateCWebHyDrationBridgeArray {
    CWebHyDrationBridge **elments;
    int size;

}privateCWebHyDrationBridgeArray;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef  struct{
    char *name;
    CWebHyDrationBridge *bridge;
} CWebHyDrationSearchRequirements;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct{
    CWebHyDrationBridge *bridge;
    cJSON *search;
    const char *name;
} CWebHyDrationSearchResult;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CwebHttpRequest{

    char *url;
    int socket;
    char *route;
    char *method;
    char *client_ip;
    int content_error;
    CwebDict *params;
    CwebDict *headers;
    int content_length;
    unsigned char *content;
    cJSON *json;
    void *hydratation;
    void *extra_args;
    UniversalGarbage *garbage;

}CwebHttpRequest;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CwebHttpResponse{
    int status_code;
    struct CwebDict *headers;
    int content_length;
    bool exist_content;
    unsigned char *content;

}CwebHttpResponse;


#endif

#ifndef CWebStudio_typesD
#define CWebStudio_typesD
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CWebHyDration {
    CwebHttpRequest *request;
   const  char *error_bridge_name;
    char *error_msg;
    cJSON *response;
    cJSON *args;
    cJSON *content;

    int error_code;
   // CwebStringArray *stack_elements;
    CTextStack *script_text;
    long max_content_size;
    privateCWebHyDrationBridgeArray *all_bridges;

}CWebHyDration;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

 typedef struct CwebServer{
    int port;
    int function_timeout;
    double client_timeout;
    int max_queue;

    #if defined(__linux__) || defined(__APPLE__)
        bool single_process;
    #endif

    long max_requests;
    bool allow_cors;
    bool use_static;
    const char *static_folder;
    bool use_cache;

    //methods
    CwebHttpResponse *(*request_handler)(CwebHttpRequest *request);

}CwebServer;


#endif

#ifndef CWebStudio_typesG
#define CWebStudio_typesG
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CwebKeyValModule{
    void (*represent)(CwebKeyVal *key_val);
    void (*free)(CwebKeyVal *key_val);
}CwebKeyValModule;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct CWebHydrationResponseNamespace {
    void (*replace_element_by_query_selector)(
        CWebHyDrationBridge *self,
        const char *query_selector,
        const char *code,
        ...
    );
    void (*remove_session_storage_data)(CWebHyDrationBridge *self,const char*key);

    void (*append_by_query_selector)(
        CWebHyDrationBridge *self,
        const char *query_selector,
        const char *code,
        ...
    );


    void (*destroy_by_query_selector)(
        CWebHyDrationBridge *self,
        const char * query_selecor
    );



    void (*hide_element_by_query_selector)(
    CWebHyDrationBridge *self,
    const char *query_selecor);

    void (*unhide_element_by_query_selector)(
        CWebHyDrationBridge *self,
        const char *query_selector
    );
    void (*hide_element_by_id)(CWebHyDrationBridge *self,const char *id);
    void (*unhide_element_by_id)(CWebHyDrationBridge *self,const char *id);
    void (*append_by_id)(CWebHyDrationBridge *self,const char *id, const char *code,...);

    void (*set_session_storage_data)(CWebHyDrationBridge *self,const char*key, const char *value,...);
    void (*alert)(CWebHyDrationBridge *self,const char *menssage,...);
    void (*execute_script)(CWebHyDrationBridge *self,const char *code,...);
    void (*replace_element_by_id)(CWebHyDrationBridge *self,const char *id, const char *code,...);
    void (*destroy_by_id)(CWebHyDrationBridge *self,const char * id);
    void (*redirect)(CWebHyDrationBridge *self, const char *url);
    void (*add_cookie_with_time)(CWebHyDrationBridge *self, const char *key, long time, const char *value, ...);
    void (*add_cookie)(CWebHyDrationBridge *self, const char *key, const char *value, ...);
    void (*delet_cookie)(CWebHyDrationBridge *self, const char *key);
    void (*console_log)(CWebHyDrationBridge *self,const char *menssage,...);
    void (*console_warn)(CWebHyDrationBridge *self,const char *menssage,...);
    void (*console_error)(CWebHyDrationBridge *self,const char *menssage,...);
    void (*console_clear)(CWebHyDrationBridge *self);
    void (*add_class_by_query_selector)(CWebHyDrationBridge *self, const char *element, const char *class_name, ...);
    void (*remove_class_by_query_selector)(CWebHyDrationBridge *self, const char *element, const char *class_name, ...);
    void (*remove_class_by_id)(CWebHyDrationBridge *self, const char *id, const char *class_name, ...);
    void (*add_class_by_id)(CWebHyDrationBridge *self, const char *id, const char *class_name, ...);



}CWebHydrationActionsNamespace;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CWebHydrationArgsNamespace {

    bool   (*is_arg_null)(CWebHyDrationBridge *self,int index);
    int   (*get_args_size)(CWebHyDrationBridge *self);
    bool   (*is_arg_number)(CWebHyDrationBridge *self,int index);
    bool   (*is_arg_bool)(CWebHyDrationBridge *self,int index);
    bool   (*is_arg_string)(CWebHyDrationBridge *self,int index);
    double  (*get_double_arg)(CWebHyDrationBridge *self,int index);
    long  (*get_long_arg)(CWebHyDrationBridge *self,int index);
    bool  (*get_bool_arg)(CWebHyDrationBridge *self,int index);
    char* (*get_str_arg)(CWebHyDrationBridge *self,int index);
    cJSON * (*get_cJSON_arg)(CWebHyDrationBridge *self,int index);

}CWebHydrationArgsNamespace;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CWebHydrationBridgeNamespace{

    CWebHyDrationBridge * (*create_bridge)(CWebHyDration *self,const char *name,void (*callback)(CWebHyDrationBridge *));
    char *(*call_trigger)(
        CWebHyDrationBridge *self,
        const char *trigger,
        const char *func_args,
        ...
    );

    char *(*call)(CWebHyDrationBridge *self,const char *func_args,...);
    char *(*onclick)(CWebHyDrationBridge *self,const char *func_args,...);
    char *(*onfoccusout)(CWebHyDrationBridge *self,const char *func_args,...);

    CTextStack * (*create_stack)(CWebHyDrationBridge *self);
    CTextStack * (*create_empty_stack)(CWebHyDrationBridge *self);

    bool (*has_errors)(CWebHyDrationBridge *self);
    CWebHyDrationBridge * (*get_child_bridge)(CWebHyDration *self,const char *name);
    CWebHyDrationBridge * (*get_brother_bridge)(CWebHyDrationBridge *self,const char *name);

}CWebHydrationBridgeNamespace;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct CWebHydrationSearchRequirementsNamespace {




    CWebHyDrationSearchRequirements * (*newSearchRequirements)(CWebHyDrationBridge *self, const char *name,...);

    void (*add_function)(CWebHyDrationSearchRequirements *self,const char *function,...);
    void (*add_elements_by_query_selector)(
        CWebHyDrationSearchRequirements *self,
        const char *query_selector,
        ...
    );
    void (*add_elements_by_query_selector_not_auto_converting)(
        CWebHyDrationSearchRequirements *self,
        const char *query_selector,
        ...
    );
    void (*add_elements_by_attribute)(
        CWebHyDrationSearchRequirements *self,
       const char *attribute,
       const char*attribute_value,
       ...
    );
    void (*add_elements_by_attribute_not_auto_converting)(
        CWebHyDrationSearchRequirements *self,
        const char *attribute,
        const char*attribute_value,
        ...
    );

    void (*add_elements_by_class_name)(
        CWebHyDrationSearchRequirements *self,
        const char*class_value,
        ...
    );

    void (*add_elements_by_class_name_not_auto_converting)(
        CWebHyDrationSearchRequirements *self,
        const char*class_value,...
    );

    void (*add_elements_by_id)(
        CWebHyDrationSearchRequirements *self,
        const char*id_values,
        ...
    );

    void (*add_elements_by_id_not_auto_converting)(
        CWebHyDrationSearchRequirements *self,
        const char*id_values,
        ...
    );

    void (*add_session_storage_item_not_converting)(
        CWebHyDrationSearchRequirements *self,
        const char *name,
        ...
    );

    void (*add_elements_by_id_setting_search_as_same_name)(
        CWebHyDrationBridge *self, const char *id
    );


    void (*add_elements_by_id_setting_search_as_same_name_not_auto_converting)(
        CWebHyDrationBridge *self, const char *id
    );


    void (*add_elements_by_class_name_setting_search_as_same_name)(
        CWebHyDrationBridge *self, const char *class_name
    );

    void (*add_elements_by_class_name_setting_search_as_same_name_not_auto_converting)(
        CWebHyDrationBridge *self, const char *class_name
    );

    void (*add_session_storage_item)(
        CWebHyDrationSearchRequirements *self,
        const char *name,
        ...
    );

    void (*add_value_cookie_by_key)(CWebHyDrationSearchRequirements *self, const char *key);
    void (*add_confirm)(CWebHyDrationSearchRequirements *self, const char*message, ...);
    void (*add_prompt)(CWebHyDrationSearchRequirements *self, const char *message, ...);

}CWebHydrationSearchRequirementsNamespace;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct CWebHydrationSearchResultNamespace {

    int  (*get_total_avaialible_searchs)(CWebHyDrationBridge *self);
    CWebHyDrationSearchResult * (*get_search_by_index)(CWebHyDrationBridge *self,int index);
    CWebHyDrationSearchResult * (*get_search_by_name)(CWebHyDrationBridge *self,const char *name,...);
    bool (*search_exist)(CWebHyDrationBridge *self,const char *name,...);
    double (*get_double_from_first_element_of_search)(CWebHyDrationBridge *self,const char *name,...);
    long (*get_long_from_first_element_of_search)(CWebHyDrationBridge *self,const char *name,...);
    bool (*get_bool_from_first_element_of_search)(CWebHyDrationBridge *self,const char *name,...);
    char* (*get_string_from_first_element_of_search)(CWebHyDrationBridge *self,const char *name,...);
    cJSON* (*get_cJSON_from_first_element_of_search)(CWebHyDrationBridge *self,const char *name,...);
    int  (*get_total_itens)(CWebHyDrationSearchResult *self);
    bool  (*search_item_exist)(CWebHyDrationSearchResult *self,int index);
    bool  (*is_search_item_number)(CWebHyDrationSearchResult *self,int index);
    bool  (*is_search_item_bool)(CWebHyDrationSearchResult *self,int index);
    bool  (*is_search_item_string)(CWebHyDrationSearchResult *self,int index);
    double (*get_double)(CWebHyDrationSearchResult *self,int  index);
    long (*get_long)(CWebHyDrationSearchResult *self,int  index);
    bool (*get_bool)(CWebHyDrationSearchResult *self,int  index);
    char*  (*get_string)(CWebHyDrationSearchResult *self,int  index);
    cJSON *  (*get_cJSON)(CWebHyDrationSearchResult *self,int  index);

}CWebHydrationSearchResultNamespace;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CwebHttpRequestModule{
    CwebHttpRequest *(*newCwebHttpRequest)(int socket);
    unsigned char*(*read_content)(struct CwebHttpRequest *self,long max_content_size);
    cJSON * (*read_cJSON)(CwebHttpRequest *self, long max_content_size);

    void (*set_url)(struct CwebHttpRequest *self,const char *url);
    void (*set_route)(struct CwebHttpRequest *self,const char *route);
    void (*set_method)(struct CwebHttpRequest *self,const char *method);

    void (*add_header)(struct CwebHttpRequest *self,const char *key,const char *value);
    void (*add_param)(struct CwebHttpRequest *self,const char *key,const char *value);
    void (*set_content_string)(struct CwebHttpRequest *self,const char *content);


    char *(*get_header)(struct CwebHttpRequest *self,const char *key);
    char *(*get_header_by_normalized_key)(
            struct CwebHttpRequest *self,
            const char *key,
            const char *chars_to_remove
    );

    char *(*get_param)(struct CwebHttpRequest *self,const char *key);
    char *(*get_param_by_sanitized_key)(struct CwebHttpRequest *self,const char *key,
                                        const char *chars_to_remove);


    int (*parse_http_request)(struct CwebHttpRequest *self);

    CTextStack *(*create_empty_stack)(CwebHttpRequest *self);
    CTextStack *(*create_stack)(CwebHttpRequest *self);


    void (*free)(struct CwebHttpRequest *request);
    void (*represent)(struct CwebHttpRequest *request);
}CwebHttpRequestModule;

//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CwebHttpResponseModule{

    CwebHttpResponse  * (*newHttpResponse)();

    CwebHttpResponse * (*send_any)(
            const char *content_type,
            size_t content_length,
            unsigned char *content,
            int status_code
    );
    CwebHttpResponse * (*send_json_string)(
            const char *content,
            int status_code
    );
    CwebHttpResponse * (*send_json_string_cleaning_memory)(
            char *content,
            int status_code
    );
    CwebHttpResponse * (*send_cJSON)(
            cJSON *content,
            int status_code
    );


    CwebHttpResponse * (*send_cJSON_cleaning_memory)(
            cJSON *content,
            int status_code
    );


    CwebHttpResponse * (*send_text)(
            const char *content,
            int status_code
    );

    CwebHttpResponse * (*send_text_cleaning_memory)(
            char *content,
            int status_code
    );

    CwebHttpResponse* (*send_rendered_CTextStack)(struct CTextStack *stack,int status_code);

    CwebHttpResponse* (*send_var_html)(const char *content,int status_code);

    CwebHttpResponse* (*send_var_html_cleaning_memory)(
            char *content,
            int status_code
    );

    CwebHttpResponse * (*send_file)(
            const char *file_path,
            const char *content_type,
            int status_code
    );



    void (*set_content)(CwebHttpResponse *response, unsigned char *content, int content_length);
    void (*add_header)(CwebHttpResponse *response,const char *key,const  char *value);
    char *(*generate_response)(CwebHttpResponse *response);
    void (*free)(CwebHttpResponse *response);

}CwebHttpResponseModule;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct CwebServerModule{
    CwebServer (*newServer)(int port , CwebHttpResponse *(*request_handler)(CwebHttpRequest *request));
    int (*start)(struct  CwebServer *self);
}CwebServerModule;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CwebStringArrayModule{
    CwebStringArray *(*newStringArray)();
    void (*set)( CwebStringArray *self,int index,const char *value);
    void (*add)( CwebStringArray *self,const char *string);
    void (*merge)(CwebStringArray *self, CwebStringArray *other);
    void (*represent)(CwebStringArray *self);
    int (*find)(CwebStringArray *self,const char *string);

    void (*free)(CwebStringArray *self);
}CwebStringArrayModule;


#endif

#ifndef CWebStudio_typesH
#define CWebStudio_typesH
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CwebDictModule{


    CwebDict *(*newDict)();
    void  (*set)(CwebDict *dict,const char *key,const char *value);
    char* (*get)(CwebDict *dict,const char *key);
    char* (*get_by_normalized_key)(CwebDict *dict,const char *key,const char *chars_to_remove);
    void  (*free)(CwebDict *dict);
    void  (*represent)(CwebDict *dict);

    CwebKeyValModule keyval;

}CwebDictModule;


//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end

typedef struct CWebHydrationNamespace{
    CWebHyDration *(*newCWebHyDration)(CwebHttpRequest *request);
    bool (*is_the_trigger)(CWebHyDration *self);
    char *(*create_script)(CWebHyDration *self);
    CwebHttpResponse *(*generate_response)(CWebHyDration *self);
    CTextStack  * (*create_stack)(CWebHyDration *self);
    CTextStack  * (*create_empty_stack)(CWebHyDration *self);
    CWebHydrationBridgeNamespace bridge;
    CWebHydrationActionsNamespace actions;
    CWebHydrationSearchRequirementsNamespace search_requirements;
    CWebHydrationSearchResultNamespace search_result;
    CWebHydrationArgsNamespace args;
}CWebHydrationNamespace;


#endif

#ifndef CWebStudio_typesO
#define CWebStudio_typesO
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end


typedef struct CwebNamespace{
    CwebDictModule dict;
    CwebHttpRequestModule request;
    CwebHttpResponseModule response;
    CwebServerModule server;
    CwebStringArrayModule  string_array;
    CWebHydrationNamespace hydration;
}CwebNamespace;


#endif

#ifndef CWebStudio_fdeclare
#define CWebStudio_fdeclare
//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain

//silver_chain_scope_end
//fdefine.extras.c



unsigned char *cweb_load_any_content(const char * path,int *size,bool *is_binary);


char *cweb_load_string_file_content(const char * path);


unsigned char *cweb_load_binary_content(const char * path,int *size);


const char *cweb_generate_content_type(const char *file_name, bool is_binary) ;


char *private_cweb_convert_url_encoded_text(const char *text);
/*
bool private_cweb_is_string_from_point(const char *content, long content_size, const char *test_string, long test_string_size, long point){

    long  end_point = point + test_string_size;

    if(content_size < end_point){
        return  false;
    ;

    for(long i = 0; i < test_string_size; i++){
        char current_char = test_string[i];
        char test_char = content[i+point];
        if(current_char != test_char){
            return  false;
        ;
    ;
    return true;
;
 */

 char * private_CWeb_format_vaarg(const char *expresion, va_list args);

 char * private_CWeb_format(const char *expresion, ...);

 char *private_cweb_convert_to_hexa(const char *data);


 CTextStack  *private_cweb_create_assci_code(const char *msg);//fdefine.strings.c


char *cweb_parse_string_to_lower(const char *old_string);


char *cweb_parse_string_to_upper(const char *old_string);

char *cweb_normalize_string(const char *old_string,const char *invalid_chars);



bool cweb_starts_with(const char *string, const char *prefix);


char *private_cweb_replace_string_once(const char *target, const char *old_element, const char *new_element) ;


char* cweb_replace_string(const char *target, const char *old_element, const char *new_element) ;
//string_array/fdefine.string_array.c


struct CwebStringArray * newCwebStringArray();

int CwebStringArray_find(struct CwebStringArray *self, const char *string);
void CwebStringArray_set(struct CwebStringArray *self, int index, const char *value);

// Function prototypes
void CwebStringArray_add(struct CwebStringArray *self, const char *string);

void CwebStringArray_add_getting_ownership(struct CwebStringArray *self,  char *string);


void CwebStringArray_merge(struct CwebStringArray *self, struct CwebStringArray *other);


void CwebStringArray_represent(struct CwebStringArray *self);
void CwebStringArray_free(struct CwebStringArray *self);
//static/fdefine.static.c

CTextStack * private_cweb_format_filename(CTextStack *src);

CwebHttpResponse * private_cweb_treat_five_icon();
char * private_cweb_aply_macro_modifiers_in_content(const char *content, long content_size);

char * cweb_aply_macro_modifiers_in_content(const char *content);

char * cweb_aply_macro_modifiers_in_file(const char *filename);



CwebHttpResponse * private_cweb_generate_static_response(struct CwebHttpRequest *request,bool use_cache);
//static/fdefine.smart_cache.c

char * private_cweb_smart_static_ref(CTextStack *src);

char * cweb_smart_static_ref(const char *src);

CTextStack * private_cweb_change_smart_cache(CTextStack *content);
//dict/fdefine.dict.c
CwebDict *newCwebDict();

char *CwebDict_get_by_normalized_key(CwebDict *self, const char *key, const char *chars_to_remove);
void CwebDict_set(CwebDict *self, const char *key, const char *value);

char * CwebDict_get(CwebDict *self, const  char *key);

void CwebDict_represent(CwebDict *dict);

void CwebDict_free(CwebDict *self);//request/fdefine.request_parser.c


void private_CwebHttpRequest_interpret_query_params(struct CwebHttpRequest *self, const char *query_params);

void CwebHttpRequest_set_url(struct CwebHttpRequest *self, const char *url);

int private_CwebHttpRequest_interpret_first_line(struct CwebHttpRequest *self, char *first_line);


int private_CwebHttpRequest_interpret_headders(struct CwebHttpRequest *self, struct CwebStringArray *line_headers);


bool private_cweb_is_valid_utf8(const unsigned char *data, size_t length) ;

int  CwebHttpRequest_parse_http_request(struct CwebHttpRequest *self);
//response/fdefine.response_functions.c



 CwebHttpResponse* cweb_send_any(const char *content_type,size_t content_length,unsigned char *content,int status_code);

CwebHttpResponse * cweb_send_json_string(const char *content,int status_code);


CwebHttpResponse * cweb_send_json_string_cleaning_memory(char *content,int status_code);

CwebHttpResponse * cweb_send_cJSON(cJSON *content,int status_code);



CwebHttpResponse * cweb_send_cJSON_cleaning_memory(cJSON *content,int status_code);


CwebHttpResponse* cweb_send_any_cleaning_memory(const char *content_type,size_t content_length,unsigned char *content,int status_code);


CwebHttpResponse* cweb_send_rendered_CTextStack(struct CTextStack *stack,int status_code);


CwebHttpResponse* cweb_send_text(const char *content,int status_code);


CwebHttpResponse* cweb_send_text_cleaning_memory(char *content,int status_code);


CwebHttpResponse* cweb_send_var_html(const char *content,int status_code);


 CwebHttpResponse* cweb_send_var_html_cleaning_memory(char *content,int status_code);



CwebHttpResponse* cweb_send_file(const char *file_path,const char *content_type,int status_code);
//keyval/fdefine.key_val.c
CwebKeyVal* newCwebKeyVal(const char *key, const  char *value);

void CwebKeyVal_represent( CwebKeyVal *self);

void CwebKeyVal_free( CwebKeyVal *self);//namespace/namespace/fdefine.namespace.c

CwebNamespace newCwebNamespace();

//namespace/server_module/fdefine.server_module.c

CwebServerModule newCwebServerModule();
//namespace/request_module/fdefine.request_module.c


CwebHttpRequestModule newCwebRequestModule();
//namespace/string_array_module/fdefine.string_array_module.c


CwebStringArrayModule newCwebStringArrayModule();
//namespace/response_module/fdefine.response_module.c



CwebHttpResponseModule newCwebHttpResponseModule();
//static/inline_inclusion/fdefine.inline_inclusion.c

void private_cweb_load_file_and_include(
        CTextStack *code,
        CTextStack *src,
        privateCwebRecursionList * recursion_listage);

void private_cweb_generate_inline_inclusion(
        CTextStack *code,
        const char *content,
        long content_size,
        privateCwebRecursionList *recursion_listage,
        const char *filename) ;
//request/request/fdefine.request.c


 CwebHttpRequest *newCwebHttpRequest(int socket);



unsigned char * CwebHttpRequest_read_content( CwebHttpRequest *self, long max_content_size) ;


cJSON * CWebHttpRequest_read_cJSON(CwebHttpRequest *self, long max_content_size);



char * CwebHttpRequest_get_header( CwebHttpRequest *self, const char *key);

char * CwebHttpRequest_get_param_by_sanitized_key( CwebHttpRequest *self, const char *key, const char *chars_to_remove);

char * CwebHttpRequest_get_param( CwebHttpRequest *self, const char *key);
char * CwebHttpRequest_get_header_by_normalized_key( CwebHttpRequest *self, const char *key, const char *chars_to_remove);



void CwebHttpRequest_set_route( CwebHttpRequest *self, const char *route);

void CwebHttpRequest_add_header( CwebHttpRequest *self, const char *key, const char *value);
void CwebHttpRequest_add_param( CwebHttpRequest *self, const char *key, const char *value);

void CwebHttpRequest_set_method( CwebHttpRequest *self, const char *method);


void CwebHttpRequest_set_content_string( CwebHttpRequest *self, const char *content);


void CwebHttpRequest_represent( CwebHttpRequest *self);
CTextStack *CwebHttpRequest_create_empty_stack(CwebHttpRequest *self);

CTextStack *CwebHttpRequest_create_stack(CwebHttpRequest *self);


void CwebHttpRequest_free( CwebHttpRequest *self);
//response/response/fdefine.response.c

CwebHttpResponse *newCwebHttpResponse();

char *CwebHttpResponse_generate_response(struct CwebHttpResponse*self);

void CwebHttpResponse_free(struct CwebHttpResponse *self);

void CwebHttpResponse_set_content(struct CwebHttpResponse *self, unsigned char *content, int content_length);

void CwebHttpResponse_add_header(struct CwebHttpResponse *self, const char *key, const  char *value);
//server/server_functions/fdefine.server_functions.c
#if defined(__linux__) || defined(__APPLE__)


void private_cweb_treat_response(bool use_static,int new_socket);

void private_cweb_handle_child_termination(int signal) ;
#endif


void private_cweb_send_error_mensage( CwebHttpResponse *response, int socket);
void cweb_kill_single_process_server( );

void cweb_set_static_folder(const char *folder);
const char * cweb_get_static_folder();

long cweb_get_total_requests();//server/server/fdefine.single_process.c


int private_CWebServer_run_server_in_single_process(CwebServer *self) ;
//server/server/fdefine.constructors.c

 CwebServer  newCwebSever(int port , CwebHttpResponse *(*request_handler)(CwebHttpRequest *request));

#if defined(__linux__) || defined(__APPLE__)

int CwebServer_start(CwebServer *self);
#endif


#if defined(_WIN32)
int CwebServer_start(CwebServer *self);
#endif
//server/server/fdefine.request_execution.c



void private_CWebServer_execute_request(CwebServer *self,int socket,const char *client_ip);//server/server/fdefine.multi_process.c
#if defined(__linux__ ) || defined(__APPLE__)



void private_cweb_execute_request_in_safty_mode(CwebServer  *self,int new_socket, const char *client_ip);

int  private_CWebServer_run_server_in_multiprocess(CwebServer *self);
#endif
//hydratation/bridge/fdefine.calls.c


char *privateCWebHyDrationBridge_call_by_vaargss(CWebHyDrationBridge *self,const char *func_args,va_list  args);

char *CWebHyDrationBridge_call(CWebHyDrationBridge *self,const char *func_args,...);
char *privateCWebHyDrationBridge_call_trigger_by_vaarg(
    CWebHyDrationBridge *self,
    const char *trigger,
    const char *func_args,
    va_list  args
);



char *CWebHyDrationBridge_call_trigger(
    CWebHyDrationBridge *self,
    const char *trigger,
    const char *func_args,
    ...
);


char *CWebHyDrationBridge_onclick(CWebHyDrationBridge *self,const char *func_args,...);


char *CWebHyDrationBridge_onfoccusout(CWebHyDrationBridge *self,const char *func_args,...);
//hydratation/bridge/fdefine.search_result.c



int  CWebHyDrationBridge_get_total_avaialible_searchs(CWebHyDrationBridge *self);


CWebHyDrationSearchResult * CWebHyDrationBridge_get_search_by_index(CWebHyDrationBridge *self,int index);

CWebHyDrationSearchResult * CWebHyDrationBridge_get_search_by_name(CWebHyDrationBridge *self,const char *name,...);

bool CWebHyDrationBridge_search_exist(CWebHyDrationBridge *self,const char *name,...);

double CWebHyDrationBridge_get_double_from_first_element_of_search(CWebHyDrationBridge *self,const char *name,...);

long CWebHyDrationBridge_get_long_from_first_element_of_search(CWebHyDrationBridge *self,const char *name,...);


bool CWebHyDrationBridge_get_bool_from_first_element_of_search(CWebHyDrationBridge *self,const char *name,...);


char* CWebHyDrationBridge_get_string_from_first_element_of_search(CWebHyDrationBridge *self,const char *name,...);

cJSON* CWebHyDrationBridge_get_cJSON_from_first_element_of_search(CWebHyDrationBridge *self,const char *name,...);
//hydratation/bridge/fdefine.action.c


void privateCWebHyDrationBridge_add_response(CWebHyDrationBridge *self,const char *name,cJSON *data);

void CWebHyDrationBridge_set_session_storage_data(

    CWebHyDrationBridge *self,const char*key, const char *value,...);

void CWebHyDrationBridge_remove_session_storage_data(CWebHyDrationBridge *self,const char*key);


void CWebHyDrationBridge_alert(CWebHyDrationBridge *self,const char *menssage,...);

void CWebHydrationBridge_creatCookie_with_time(CWebHyDrationBridge *self, const char *key, long time, const char *value, ...);

void CWebHydrationBridge_creatCookie(CWebHyDrationBridge *self, const char *key, const char *value, ...);

void CWebHyDrationBridge_deletCookie(CWebHyDrationBridge *self, const char *key);

void CWebHyDrationBridge_execute_script(CWebHyDrationBridge *self,const char *code,...);

void CWebHyDrationBridge_replace_element_by_query_selector(
    CWebHyDrationBridge *self,
    const char *query_selector,
    const char *code,
    ...
);


void CWebHyDrationBridge_append_by_query_selector(
    CWebHyDrationBridge *self,
    const char *query_selector,
    const char *code,
    ...
);



void CWebHyDrationBridge_destroy_by_query_selector(
    CWebHyDrationBridge *self,
    const char * query_selecor
);


void CWebHyDrationBridge_hide_element_by_query_selector(
CWebHyDrationBridge *self,
const char *query_selecor);

void CWebHyDrationBridge_unhide_element_by_query_selector(
    CWebHyDrationBridge *self,
    const char *query_selector
);




void CWebHyDrationBridge_replace_element_by_id(CWebHyDrationBridge *self,const char *id, const char *code,...);

void CWebHyDrationBridge_append_by_id(CWebHyDrationBridge *self,const char *id, const char *code,...);


void CWebHyDrationBridge_hide_element_by_id(CWebHyDrationBridge *self,const char *id);

void CWebHyDrationBridge_unhide_element_by_id(CWebHyDrationBridge *self,const char *id);


void CWebHyDrationBridge_destroy_by_id(CWebHyDrationBridge *self,const char * id);

void CWebHydration_redirect(CWebHyDrationBridge *self, const char *url);

void CWebHyDration_console_log(CWebHyDrationBridge *self, const char *menssage, ...);
void CWebHyDration_console_warn(CWebHyDrationBridge *self, const char *menssage, ...);
void CWebHyDration_console_error(CWebHyDrationBridge *self, const char *menssage, ...);
void CWebHyDration_console_clear(CWebHyDrationBridge *self);

void CWebHyDrationBridge_remove_class_by_id(CWebHyDrationBridge *self, const char *id, const char *class_name, ...);

void CWebHyDrationBridge_add_class_by_id(CWebHyDrationBridge *self, const char *id, const char *class_name, ...);

void CWebHyDrationBridge_remove_class_by_query_selector(CWebHyDrationBridge *self, const char *element, const char *class_name, ...);

void CWebHyDrationBridge_add_class_by_query_selector(CWebHyDrationBridge *self, const char *element, const char *class_name, ...);
//hydratation/bridge/fdefine.args.c


int   CWebHyDrationBridge_get_args_size(CWebHyDrationBridge *self);


bool private_cweb_hydration_type_verifier(CWebHyDrationBridge *self,int index,cJSON_bool (*callback_verifier)( cJSON *item));

bool   CWebHyDrationBridge_is_arg_number(CWebHyDrationBridge *self,int index);

bool   CWebHyDrationBridge_is_arg_null(CWebHyDrationBridge *self,int index);

bool   CWebHyDrationBridge_is_arg_bool(CWebHyDrationBridge *self,int index);
bool   CWebHyDrationBridge_is_arg_string(CWebHyDrationBridge *self,int index);


cJSON *privateCWebHyDration_get_arg_index(
    CWebHyDrationBridge *self,
    int index,
    cJSON_bool (*callback_verifier)( cJSON *  item),
    const char *expected_type
);

double  CWebHyDrationBridge_get_double_arg(CWebHyDrationBridge *self,int index);

long  CWebHyDrationBridge_get_long_arg(CWebHyDrationBridge *self,int index);



bool  CWebHyDrationBridge_get_bool_arg(CWebHyDrationBridge *self,int index);

char* CWebHyDrationBridge_get_str_arg(CWebHyDrationBridge *self,int index);
cJSON * CWebHyDrationBridge_get_cJSON_arg(CWebHyDrationBridge *self,int index);
//hydratation/bridge/fdefine.basic.c




CWebHyDrationBridge * CWebHyDrationBridge_get_brother_bridge(CWebHyDrationBridge *self,const char *name);

CWebHyDrationBridge *private_newCWebHyDrationBridge(
    const char *name,
    void (*callback)(CWebHyDrationBridge *),CWebHyDration *hydration
) ;



CTextStack * CWebHyDrationBridge_create_stack(CWebHyDrationBridge *self);

CTextStack * CWebHyDrationBridge_create_empty_stack(CWebHyDrationBridge *self);

CWebHyDrationSearchRequirements * CWebHyDrationBridge_newSearchRequirements(
    CWebHyDrationBridge *self, const char *name,...)
;



CTextStack*  private_CWebHyDrationBridge_create_script(CWebHyDrationBridge *self) ;
bool CWebHyDrationBridge_has_errors(CWebHyDrationBridge *self);



void private_CWebHyDrationBridge_free(CWebHyDrationBridge *self) ;
//hydratation/bridge/fdefine.search_requirements.c

void CWebHyDrationBridge_add_elements_by_id_setting_search_as_same_name(
    CWebHyDrationBridge *self, const char *id
);


void CWebHyDrationBridge_add_elements_by_id_setting_search_as_same_name_not_auto_converting(
    CWebHyDrationBridge *self, const char *id
);

void CWebHyDrationBridge_add_elements_by_class_name_setting_search_as_same_name(
    CWebHyDrationBridge *self, const char *class_name
);


void CWebHyDrationBridge_add_elements_by_class_name_setting_search_as_same_name_not_auto_converting(
    CWebHyDrationBridge *self, const char *class_name
);
//hydratation/search_result/fdefine.search_result.c


CWebHyDrationSearchResult * private_newCWebHyDrationSearchResult(CWebHyDrationBridge *bridge,cJSON *search);

void privateCWebHyDrationSearchResult_free(CWebHyDrationSearchResult *self);

int  CWebHyDrationSearchResult_get_total_itens(CWebHyDrationSearchResult *self);

bool  privateCWebHyDrationSearchResult_has_erorrs(CWebHyDrationSearchResult *self);

bool  CWebHyDrationSearchResult_search_item_exist(CWebHyDrationSearchResult *self,int index);



bool  CWebHyDrationSearchResult_is_search_item_number(CWebHyDrationSearchResult *self,int index);

bool  CWebHyDrationSearchResult_is_search_item_bool(CWebHyDrationSearchResult *self,int index);




bool  CWebHyDrationSearchResult_is_search_item_string(CWebHyDrationSearchResult *self,int index);


cJSON * private_CWebHyDrationSearchResult_get_cJSON_item_verifying_type(

    CWebHyDrationSearchResult *self,
    int index,
    cJSON_bool  (*callback_verifier)( cJSON *  item),
    const char *expected_type
);

double CWebHyDrationSearchResult_get_double(CWebHyDrationSearchResult *self,int  index);

long CWebHyDrationSearchResult_get_long(CWebHyDrationSearchResult *self,int  index);

bool CWebHyDrationSearchResult_get_bool(CWebHyDrationSearchResult *self,int  index);


char*  CWebHyDrationSearchResult_get_string(CWebHyDrationSearchResult *self,int  index);

cJSON *  CWebHyDrationSearchResult_get_cJSON(CWebHyDrationSearchResult *self,int  index);//hydratation/bridge_array/fdefine.bridge_array.c

privateCWebHyDrationBridgeArray * private_new_privateCWebHyDrationBridgeArray() ;

void privateCWebHyDrationBridgeArray_append(privateCWebHyDrationBridgeArray *self,CWebHyDrationBridge *element) ;

void privateCWebHyDrationBridgeArray_free(privateCWebHyDrationBridgeArray *self) ;
//hydratation/hydration/fdefine.hydration.c


CWebHyDration *newCWebHyDration(CwebHttpRequest *request) ;

CWebHyDrationBridge * CWebHyDration_get_child_bridge(CWebHyDration *self,const char *name);


CTextStack  * CWebHyDration_create_stack(CWebHyDration *self);

CTextStack  * CWebHyDration_create_empty_stack(CWebHyDration *self);


CWebHyDrationBridge * CWebHyDration_create_bridge(CWebHyDration *self,const char *name,void (*callback)(CWebHyDrationBridge *));

bool CWebHyDration_is_the_trigger(CWebHyDration *self);

void privateCWebHydration_raise_error(CWebHyDration *self,CWebHyDrationBridge *bridge, int error_code, const char *format,...);


CwebHttpResponse *CWebHydration_generate_response(CWebHyDration *self);
CwebHttpResponse *private_CWebHydration_formmat_error_response(CWebHyDration *self);


char *CWebHyDration_create_script(CWebHyDration *self) ;

void private_CWebHyDration_free(CWebHyDration *self) ;//hydratation/search_requirements/fdefine.search_requirements.c



CWebHyDrationSearchRequirements * private_newCWebHyDrationSearchRequirements_getting_name_ownership(
    CWebHyDrationBridge *bridge, char *name
);


void private_CWebHyDrationSearchRequirements_free(CWebHyDrationSearchRequirements *self);


void CWebHyDrationSearchRequirements_add_function(CWebHyDrationSearchRequirements *self,const char *function,...);

void private_CWebHyDrationSearchRequirements_add_elements_by_query_selector(
    CWebHyDrationSearchRequirements *self,
    const char *query_selector,bool auto_convert
);



void CWebHyDrationSearchRequirements_add_elements_by_query_selector(
    CWebHyDrationSearchRequirements *self,
    const char *query_selector,
    ...
);





void CWebHyDrationSearchRequirements_add_elements_by_query_selector_not_auto_converting(
    CWebHyDrationSearchRequirements *self,const char *query_selector,...);





void CWebHyDrationSearchRequirements_add_elements_by_attribute(
    CWebHyDrationSearchRequirements *self,
   const char *attribute,
   const char*attribute_value,
   ...
);

void CWebHyDrationSearchRequirements_add_elements_by_attribute_not_auto_converting(
    CWebHyDrationSearchRequirements *self,
    const char *attribute,
    const char*attribute_value,
    ...
);



void CWebHyDrationSearchRequirements_add_elements_by_class_name(
    CWebHyDrationSearchRequirements *self,
    const char*class_value,
    ...
);

void CWebHyDrationSearchRequirements_add_elements_by_class_name_not_auto_converting(
    CWebHyDrationSearchRequirements *self,
    const char*class_value,...
);


void CWebHyDrationSearchRequirements_add_elements_by_id(
    CWebHyDrationSearchRequirements *self,
    const char*id_values,
    ...
);

void CWebHyDrationSearchRequirements_add_elements_by_id_not_auto_converting(
    CWebHyDrationSearchRequirements *self,
    const char*id_values,
    ...
);

void CWebHyDrationSearchRequirements_add_session_storage_item_not_converting(
    CWebHyDrationSearchRequirements *self,
    const char *name,
    ...
);


void CWebHyDrationSearchRequirements_add_session_storage_item(
    CWebHyDrationSearchRequirements *self,
    const char *name,
    ...
);

void CWebHyDrationSearchRequirements_add_cookie_item(CWebHyDrationSearchRequirements *self, const char *name);

void CWebHyDrationSearchRequirements_add_confirm(CWebHyDrationSearchRequirements *self, const char *message, ...);

void CWebHyDrationSearchRequirements_add_prompt(CWebHyDrationSearchRequirements *self, const char *message, ...);//namespace/dict_module/keyval_module/fdefine.keyval_module.c



CwebKeyValModule newCwebKeyValModule();
//namespace/dict_module/dict_module/fdefine.dict_module.c

CwebDictModule newCwebDictModule();
//namespace/hydratation_module/bridge/fdefine.bridge.c

CWebHydrationBridgeNamespace newCWebHydrationBridgetNamespace();
//namespace/hydratation_module/search_result/fdefine.search_result.c

CWebHydrationSearchResultNamespace newCWebHydrationSearchResultNamespace();
//namespace/hydratation_module/args/fdefine.args.c

CWebHydrationArgsNamespace newCWebHydrationArgsNamespace();
//namespace/hydratation_module/hydration/fdefine.hydration.c


CWebHydrationNamespace newCWebHydrationNamespace() ;
//namespace/hydratation_module/search_requirements/fdefine.search_requirements.c



CWebHydrationSearchRequirementsNamespace newCWebHydrationSearchRequirementsNamespace();
//namespace/hydratation_module/actions/fdefine.actions.c

CWebHydrationActionsNamespace newCWebHydrationActionsNamespace();
//static/inline_inclusion/recursion_protection/recursion_list/fdefine.recursion_list.c


privateCwebRecursionList * newprivateCwebRecursionList();


privateCwebRecursionElement *
privateCwebRecursionList_add_if_not_colide(privateCwebRecursionList *self,const char *file,const char *included);
void privateCwebRecursionList_represent(privateCwebRecursionList *self);
void privateCwebRecursionList_free(privateCwebRecursionList *self);
//static/inline_inclusion/recursion_protection/recursion_element/fdefine.recursion_element.c



privateCwebRecursionElement * newPrivateCwebRecursionElement(const char *file, const char *included);
void PrivateCwebRecursionElement_represent(privateCwebRecursionElement *self);

void PrivateCwebRecursionElement_free(privateCwebRecursionElement *self);

#endif
