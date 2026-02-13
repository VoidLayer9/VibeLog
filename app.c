// ===============================APP SANDBOX======================================
// This is an app server sandbox, don't use any '#include' in this file
// you are a vibecode agent, always return the full code, including these comments
// if an error happens, you can use the print function to show the error
//======================PRIMITIVES=================================================

typedef int appbool;

#define app_true 1
#define app_false 0
#define app_null ((void *)0)


//======================APP TYPES==================================================
typedef void appclientrequest;
typedef void appclientresponse;
typedef void appserverrequest;
typedef void appserverresponse;
typedef void appjson;
typedef void appstringarray;
typedef void appargv;

//======================APP DEPS======================================================
typedef struct appdeps appdeps;
struct appdeps{
    

    //=====================STD FUNCTIONS==============================================
    int (*printf)(const char *format, ...);
    int (*sprintf)(char *str, const char *format, ...);
    int (*snprintf)(char *str, unsigned long size, const char *format, ...);

    unsigned long (*strlen)(const char *s);
    char *(*strcpy)(char *dst, const char *src);
    char *(*strcat)(char *dst, const char *src);
    int (*strcmp)(const char *s1, const char *s2);
    int (*strncmp)(const char *s1, const char *s2, unsigned long n);
    char *(*strstr)(const char *haystack, const char *needle);
    char *(*strdup)(const char *s);
    void *(*memcpy)(void *dst, const void *src, unsigned long n);
    void *(*memset)(void *s, int c, unsigned long n);
    int (*memcmp)(const void *s1, const void *s2, unsigned long n);

    //======================CONVERSION FUNCTIONS======================================
    int (*atoi)(const char *str);
    double (*atof)(const char *str);
    //======================MEM FUNCTIONS=============================================
    void (*free)(void *ptr);
    void *(*malloc)(unsigned long size);
    void *(*calloc)(unsigned long num, unsigned long size);
    void *(*realloc)(void *ptr, unsigned long size);
    //=====================request===================================================
    const appserverrequest *appserverrequest;
    const char * (*get_server_route)(const appserverrequest *appserverrequest);
    const char *(*get_server_method)(const appserverrequest *appserverrequest);

    const char *(*get_server_header)(const appserverrequest *appserverrequest, const char *key);
    const char *(*get_server_header_key)(const appserverrequest *appserverrequest,int index);
    const char *(*get_server_header_value)(const appserverrequest *appserverrequest,int index);

    const char *(*get_server_query_param)(const appserverrequest *appserverrequest, const char *key);
    const char *(*get_server_query_param_key)(const appserverrequest *appserverrequest,int index);
    const char *(*get_server_query_param_value)(const appserverrequest *appserverrequest,int index);

    int (*get_server_header_count)(const appserverrequest *appserverrequest);
    int (*get_server_query_param_count)(const appserverrequest *appserverrequest);

    const unsigned char *(*read_server_body)(const appserverrequest *appserverrequest, long size, long *read_size);
    const appjson * (*read_server_json)(const appserverrequest *appserverrequest,long size);
    const appserverresponse *(*newappserverresponse)();
    void (*setappserverresponse_header)(appserverresponse *appserverresponse, const char *key, const char *value);
    void (*setappserverresponse_content)(appserverresponse *appserverresponse, const unsigned char *content, long content_size);
    void (*setappserverresponse_status_code)(appserverresponse *appserverresponse, int status_code);


    const appserverresponse *(*send_any)(const unsigned char *content,long content_size,const char *content_type, int status_code);
    const appserverresponse *(*send_text)(const char *text,const char *content_type, int status_code);
    const appserverresponse *(*send_file)(const char *path,const char *content_type, int status_code);
    const appserverresponse *(*send_json)(const appjson *json, int status_code);

    //=====================JSON PARSING===================================================
    appjson *(*json_parse)(const char *value);
    appjson *(*json_parse_file)(const char *filepath);
    void (*json_delete)(appjson *json);

    //=====================JSON SERIALIZATION==============================================
    char *(*json_print)(const appjson *json);
    char *(*json_print_unformatted)(const appjson *json);
    appbool (*json_save_file)(const appjson *json, const char *filepath);
    void (*json_free_string)(char *str);

    //=====================JSON CREATION==============================================
    appjson *(*json_create_object)(void);
    appjson *(*json_create_array)(void);
    appjson *(*json_create_string)(const char *string);
    appjson *(*json_create_number)(double num);
    appjson *(*json_create_bool)(appbool boolean);
    appjson *(*json_create_null)(void);
    appjson *(*json_duplicate)(const appjson *item, appbool recurse);

    //=====================JSON OBJECT MANIPULATION=========================================
    appjson *(*json_get_object_item)(const appjson *object, const char *key);
    appbool (*json_has_object_item)(const appjson *object, const char *key);
    appbool (*json_add_item_to_object)(appjson *object, const char *key, appjson *item);
    appbool (*json_delete_item_from_object)(appjson *object, const char *key);
    appbool (*json_replace_item_in_object)(appjson *object, const char *key, appjson *newitem);

    // Convenience functions for adding to objects
    appjson *(*json_add_string_to_object)(appjson *object, const char *key, const char *string);
    appjson *(*json_add_number_to_object)(appjson *object, const char *key, double number);
    appjson *(*json_add_bool_to_object)(appjson *object, const char *key, appbool boolean);
    appjson *(*json_add_null_to_object)(appjson *object, const char *key);
    appjson *(*json_add_object_to_object)(appjson *object, const char *key);
    appjson *(*json_add_array_to_object)(appjson *object, const char *key);

    //=====================JSON ARRAY MANIPULATION==============================================
    int (*json_get_array_size)(const appjson *array);
    appjson *(*json_get_array_item)(const appjson *array, int index);
    appbool (*json_add_item_to_array)(appjson *array, appjson *item);
    appbool (*json_insert_item_in_array)(appjson *array, int index, appjson *item);
    appbool (*json_replace_item_in_array)(appjson *array, int index, appjson *newitem);
    void (*json_delete_item_from_array)(appjson *array, int index);

    //=====================JSON TYPE CHECKING==============================================
    appbool (*json_is_object)(const appjson *item);
    appbool (*json_is_array)(const appjson *item);
    appbool (*json_is_string)(const appjson *item);
    appbool (*json_is_number)(const appjson *item);
    appbool (*json_is_bool)(const appjson *item);
    appbool (*json_is_null)(const appjson *item);
    appbool (*json_is_true)(const appjson *item);
    appbool (*json_is_false)(const appjson *item);

    //=====================JSON VALUE GETTERS==============================================
    char *(*json_get_string_value)(const appjson *item);
    double (*json_get_number_value)(const appjson *item);

    //=====================JSON COMPARISON=================================================
    appbool (*json_compare)(const appjson *a, const appjson *b, appbool case_sensitive);

    //=====================JSON ITERATION=================================================
    appjson *(*json_get_child)(const appjson *item);     // first child of object/array
    appjson *(*json_get_next)(const appjson *item);      // next sibling in object/array
    const char *(*json_get_key)(const appjson *item);    // key name of this item (if inside object)
    int (*json_get_object_size)(const appjson *object);  // number of keys in object

    //======================IO FUNCTIONS ==================================================
    unsigned char * (*read_any)(const char *path,long *size,appbool *is_binary);
    char * (*read_string)(const char *path); // needs to be freed
    void (*write_any)(const char *path,const unsigned char *content, long size);
    void (*write_string)(const char *path,const char *content);
    void (*delete_any)(const char *path);
    void (*create_dir)(const char *path);

    void (*delete_stringarray)(appstringarray *array); 
    long (*get_stringarray_size)(appstringarray *array);
    const char *(*get_stringarray_item)(appstringarray *array, int index);


    appstringarray *  (*list_files)(const char *path);
    appstringarray *  (*list_dirs)(const char *path);
    appstringarray *  (*list_any)(const char *path);
    appstringarray *  (*list_files_recursively)(const char *path);
    appstringarray *  (*list_dirs_recursively)(const char *path);
    appstringarray *  (*list_any_recursively)(const char *path);
   
    appbool (*file_exists)(const char *path);
    appbool (*dir_exists)(const char *path);
    appbool (*copy_any)(const char *src, const char *dst);
    appbool (*move_any)(const char *src, const char *dst);
    void (*append_string)(const char *path, const char *content);
    char *(*concat_path)(const char *path1, const char *path2); // needs to be freed

    //======================ARGV PARSER FUNCTIONS ======================================
    const appargv *argv;
    const char *(*get_arg_value)(const appargv *argv,int index); // positional arguments
    int (*get_arg_count)(const appargv *argv); // number of arguments

    // use const char *help[] = {"--help","-h"}; for retrieving flags
    const char *(*get_arg_flag_value)(const appargv *argv,const char **flags,int total_flags,int index); // --name || n mateus : mateus
    int (*get_arg_flag_count)(const appargv *argv,const char **flags,int total_flags); // --name || n : true

    appbool (*has_arg_flag)(const appargv *argv,const char **flags,int total_flags); // --name : true
    
    appclientrequest *(*newappclientrequest)(const char *url);
    void (*appclientrequest_set_header)(appclientrequest *appclientrequest,const char *key, const char *value);
    void (*appclientrequest_set_method)(appclientrequest *appclientrequest,const char *method);
    void (*appclientrequest_set_max_redirections)(appclientrequest *appclientrequest,int max_redirects);
    void (*appclientrequest_set_body)(appclientrequest *appclientrequest,unsigned char *content ,long size);
    void (*appclientrequest_free)(appclientrequest *request);
    
    appclientresponse *(*appclientrequest_fetch)(appclientrequest *appclientrequest);
    unsigned char *(*appclientresponse_read_body)(appclientresponse *appclientresponse,long *size);
    long  (*appclientresponse_get_body_size)(appclientresponse *appclientresponse);
    char * (*appclientresponse_get_header_value_by_key)(appclientresponse *appclientresponse,const char *key);
    const char * (*appclientresponse_get_header_key_by_index)(appclientresponse *appclientresponse ,int index);
    const char * (*appclientresponse_get_header_value_by_index)(appclientresponse *appclientresponse ,int index);
    int (*appclientresponse_get_header_size)(appclientresponse *appclientresponse);
    void (*free_clientresponse)(appclientresponse *appclientresponse);

    //============================ASSETS==================================================
    const unsigned char * (*get_asset_content)(const char *path,long *size,appbool *is_binary);
    appstringarray * (*list_assets)(const char *path);

    //============================TIME==================================================
    long (*get_unix_time)(void);
    int (*get_random)(void);
    void (*get_formatted_time)(long timestamp, char *buf, int buf_size, const char *fmt);
    //============================SERVER==================================================
    int (*start_server)(int port, const appserverresponse *(*handler)(appdeps *d, void *props), void *props, appbool single_process);


};

// ===================== STRING BUFFER =====================
typedef struct { char *data; unsigned long len; unsigned long cap; } appbuf;

void buf_init(appdeps *d, appbuf *b) { b->cap = 4096; b->len = 0; b->data = (char*)d->malloc(b->cap); b->data[0] = '\0'; }
void buf_append(appdeps *d, appbuf *b, const char *s) {
    unsigned long sl = d->strlen(s);
    while (b->len + sl + 1 > b->cap) { b->cap *= 2; b->data = (char*)d->realloc(b->data, b->cap); }
    d->memcpy(b->data + b->len, s, sl); b->len += sl; b->data[b->len] = '\0';
}
void buf_free(appdeps *d, appbuf *b) { d->free(b->data); b->data = app_null; b->len = 0; b->cap = 0; }

// ===================== CASE-INSENSITIVE HELPERS =====================
char app_tolower(char c) { return (c >= 'A' && c <= 'Z') ? c + 32 : c; }
int app_strcasecmp(const char *a, const char *b) { while (*a && *b) { char la = app_tolower(*a), lb = app_tolower(*b); if (la != lb) return la - lb; a++; b++; } return app_tolower(*a) - app_tolower(*b); }
int app_strcasestr(const char *hay, const char *needle, appdeps *d) {
    unsigned long nl = d->strlen(needle); if (!nl) return 1;
    unsigned long hl = d->strlen(hay);
    for (unsigned long i = 0; i + nl <= hl; i++) { int ok = 1; for (unsigned long j = 0; j < nl; j++) { if (app_tolower(hay[i+j]) != app_tolower(needle[j])) { ok = 0; break; } } if (ok) return 1; } return 0;
}

// ===================== DATE PARSING =====================
// Parse DD-MM-YYYY to a sortable integer YYYYMMDD
int parse_date_sortkey(const char *dstr) {
    int d=0,m=0,y=0,i=0; char c;
    while((c=dstr[i])&&c!='-'){d=d*10+(c-'0');i++;} i++;
    while((c=dstr[i])&&c!='-'){m=m*10+(c-'0');i++;} i++;
    while((c=dstr[i])){y=y*10+(c-'0');i++;}
    return y*10000+m*100+d;
}

// ===================== SIDEBAR CACHE =====================
#define MAX_CATS 64
typedef struct { char name[64]; int views; } cat_view;
static int sidebar_total_views = 0;
static cat_view sidebar_cats[MAX_CATS];
static int sidebar_cat_count = 0;
static long sidebar_last_calc = 0;

void sidebar_calc(appdeps *d) {
    sidebar_total_views = 0; sidebar_cat_count = 0;
    appstringarray *dates = d->list_dirs("database/articles");
    if (!dates) return;
    long ndate = d->get_stringarray_size(dates);
    for (long di = 0; di < ndate; di++) {
        const char *datename = d->get_stringarray_item(dates, di);
        char *datepath = d->concat_path("database/articles", datename);
        appstringarray *arts = d->list_dirs(datepath);
        if (!arts) { d->free(datepath); continue; }
        long nart = d->get_stringarray_size(arts);
        for (long ai = 0; ai < nart; ai++) {
            const char *artname = d->get_stringarray_item(arts, ai);
            char *artpath = d->concat_path(datepath, artname);
            // Load data.json for categories
            char *djp = d->concat_path(artpath, "data.json");
            appjson *aj = d->json_parse_file(djp);
            d->free(djp);
            if (!aj) { d->free(artpath); continue; }
            appjson *cats = d->json_get_object_item(aj, "categories");
            // Load total_views
            char mp[512]; d->snprintf(mp, 512, "database/metrics/articles/%s/%s/total_views.json", datename, artname);
            int views = 0;
            if (d->file_exists(mp)) { appjson *vj = d->json_parse_file(mp); if(vj){views=(int)d->json_get_number_value(d->json_get_object_item(vj,"views"));d->json_delete(vj);} }
            sidebar_total_views += views;
            // Add to per-category
            if (cats) { int nc = d->json_get_array_size(cats); for(int ci=0;ci<nc;ci++){ char *cn=d->json_get_string_value(d->json_get_array_item(cats,ci)); int found=-1; for(int si=0;si<sidebar_cat_count;si++){if(app_strcasecmp(sidebar_cats[si].name,cn)==0){found=si;break;}} if(found>=0){sidebar_cats[found].views+=views;}else if(sidebar_cat_count<MAX_CATS){int k=0;while(cn[k]&&k<63){sidebar_cats[sidebar_cat_count].name[k]=cn[k];k++;}sidebar_cats[sidebar_cat_count].name[k]='\0';sidebar_cats[sidebar_cat_count].views=views;sidebar_cat_count++;} } }
            d->json_delete(aj);
            d->free(artpath);
        }
        d->delete_stringarray(arts);
        d->free(datepath);
    }
    d->delete_stringarray(dates);
    // Sort cats descending by views
    for(int i=0;i<sidebar_cat_count-1;i++) for(int j=i+1;j<sidebar_cat_count;j++) if(sidebar_cats[j].views>sidebar_cats[i].views){cat_view t=sidebar_cats[i];sidebar_cats[i]=sidebar_cats[j];sidebar_cats[j]=t;}
    sidebar_last_calc = d->get_unix_time();
}

void sidebar_ensure(appdeps *d) {
    long now = d->get_unix_time();
    if (sidebar_last_calc == 0 || (now - sidebar_last_calc) >= 300) sidebar_calc(d);
}

// ===================== CSS =====================
static const char *APP_CSS =
"@import url('https://fonts.googleapis.com/css2?family=IBM+Plex+Sans:wght@400;500;600;700&family=Space+Grotesk:wght@500;700&family=Inter:wght@400;500&family=JetBrains+Mono&display=swap');"
"*{margin:0;padding:0;box-sizing:border-box;}"
"body{background:#09090b;color:#d4d4d8;font-family:'Inter','IBM Plex Sans',sans-serif;line-height:1.6;}"
"a{color:#0d9488;text-decoration:none;transition:color .2s;}a:hover{color:#14b8a6;}"
".wrap{max-width:1200px;margin:0 auto;padding:0 24px;}"
/* NAVBAR */
".navbar{background:#111113;border-bottom:1px solid #1c1c1f;padding:0 24px;display:flex;align-items:center;gap:20px;height:56px;position:sticky;top:0;z-index:100;}"
".navbar .logo{font-family:'Space Grotesk',sans-serif;font-weight:700;font-size:1.3rem;color:#d4d4d8;letter-spacing:1px;}"
".navbar .nav-links{display:flex;gap:4px;align-items:center;}"
".navbar .nav-btn{background:transparent;border:1px solid transparent;color:#71717a;padding:6px 14px;font-size:.82rem;font-family:'IBM Plex Sans',sans-serif;cursor:pointer;transition:all .2s;}"
".navbar .nav-btn:hover{color:#14b8a6;border-color:#1c1c1f;}"
/* DROPDOWN */
".dropdown{position:relative;}"
".dropdown-menu{display:none;position:absolute;top:100%;left:0;background:#111113;border:1px solid #1c1c1f;min-width:200px;box-shadow:0 4px 12px rgba(0,0,0,.6);z-index:200;}"
".dropdown-menu.open{display:block;}"
".dropdown-menu a{display:block;padding:8px 16px;color:#71717a;font-size:.82rem;border-bottom:1px solid #1c1c1f;transition:all .15s;}"
".dropdown-menu a:last-child{border-bottom:none;}"
".dropdown-menu a:hover{color:#14b8a6;background:#16161a;}"
/* SEARCH */
".search-form{margin-left:auto;display:flex;}"
".search-form input{background:#16161a;border:1px solid #1c1c1f;color:#d4d4d8;padding:6px 12px;font-size:.82rem;font-family:'Inter',sans-serif;width:180px;outline:none;}"
".search-form input:focus{border-color:#0d9488;}"
".search-form button{background:#0d9488;border:none;color:#09090b;padding:6px 14px;font-size:.82rem;cursor:pointer;font-weight:600;}"
/* LAYOUT */
".main-grid{display:grid;grid-template-columns:1fr 300px;gap:32px;padding:32px 0;}"
".main-grid.full{grid-template-columns:1fr;}"
/* CARDS */
".card{background:#111113;border:1px solid #1c1c1f;box-shadow:0 1px 2px rgba(0,0,0,.5);margin-bottom:16px;overflow:hidden;transition:border-color .2s;}"
".card:hover{border-color:#27272a;}"
".card img{width:100%;height:180px;object-fit:cover;display:block;}"
".card-body{padding:16px;}"
".card-body h3{font-family:'Space Grotesk',sans-serif;font-size:1.1rem;margin-bottom:6px;}"
".card-body h3 a{color:#d4d4d8;}.card-body h3 a:hover{color:#14b8a6;}"
".card-body p{color:#71717a;font-size:.85rem;margin-bottom:8px;}"
".card-body .meta{color:#52525b;font-size:.75rem;font-family:'JetBrains Mono',monospace;}"
".badge{display:inline-block;background:#16161a;color:#0d9488;padding:2px 8px;font-size:.7rem;margin-right:4px;border:1px solid #1c1c1f;font-family:'JetBrains Mono',monospace;}"
/* SIDEBAR */
".sidebar .sb-card{background:#111113;border:1px solid #1c1c1f;padding:16px;margin-bottom:16px;}"
".sidebar .sb-card h4{font-family:'Space Grotesk',sans-serif;font-size:.9rem;color:#d4d4d8;margin-bottom:12px;border-bottom:1px solid #1c1c1f;padding-bottom:8px;}"
".sidebar .stat-row{display:flex;justify-content:space-between;padding:4px 0;font-size:.82rem;color:#71717a;border-bottom:1px solid #0f0f11;}"
".sidebar .stat-row span:last-child{color:#0d9488;font-family:'JetBrains Mono',monospace;}"
/* PAGINATION */
".pagination{display:flex;gap:8px;justify-content:center;padding:24px 0;}"
".pagination a{padding:8px 18px;border:1px solid #1c1c1f;color:#71717a;font-size:.82rem;transition:all .2s;}"
".pagination a:hover{border-color:#0d9488;color:#14b8a6;}"
/* ARTICLE PAGE */
".article-header{padding:32px 0 16px;border-bottom:1px solid #1c1c1f;margin-bottom:24px;}"
".article-header h1{font-family:'Space Grotesk',sans-serif;font-size:2rem;font-weight:700;}"
".article-content{max-width:800px;margin:0 auto;padding-bottom:32px;font-size:.95rem;line-height:1.8;}"
".article-content h1,.article-content h2,.article-content h3{font-family:'Space Grotesk',sans-serif;margin:24px 0 12px;}"
".article-content pre{background:#111113;border:1px solid #1c1c1f;padding:16px;overflow-x:auto;font-family:'JetBrains Mono',monospace;font-size:.85rem;margin:16px 0;}"
".article-content code{font-family:'JetBrains Mono',monospace;background:#16161a;padding:2px 6px;font-size:.85rem;}"
".article-content img{max-width:100%;}"
".article-footer{border-top:1px solid #1c1c1f;padding:24px 0;display:flex;align-items:center;gap:16px;max-width:800px;margin:0 auto;}"
".article-footer img{width:56px;height:56px;border-radius:0;border:1px solid #1c1c1f;object-fit:cover;}"
".article-footer .af-info{font-size:.85rem;color:#71717a;}"
".article-footer .af-info a{font-weight:600;}"
/* AUTHOR PAGE */
".author-header{display:flex;gap:24px;align-items:flex-start;padding:32px 0;border-bottom:1px solid #1c1c1f;margin-bottom:24px;}"
".author-header img{width:120px;height:120px;object-fit:cover;border:1px solid #1c1c1f;}"
".author-header h1{font-family:'Space Grotesk',sans-serif;font-size:1.6rem;}"
".author-header p{color:#71717a;margin-top:8px;}"
/* EMPTY */
".empty-state{text-align:center;padding:64px 0;color:#52525b;font-size:1rem;}"
".empty-state a{color:#0d9488;}"
/* ABOUT  */
".about-section{max-width:800px;margin:0 auto;padding:32px 0;}"
".about-section h2,.about-section h3{font-family:'Space Grotesk',sans-serif;margin:20px 0 10px;}"
".about-section ul{padding-left:20px;color:#71717a;margin-bottom:12px;}"
".about-section p{color:#a1a1aa;margin-bottom:12px;}"
/* FOOTER */
".site-footer{border-top:1px solid #1c1c1f;padding:24px 0;text-align:center;color:#52525b;font-size:.75rem;font-family:'JetBrains Mono',monospace;}"
;

// ===================== HTML HEAD =====================
void render_head(appdeps *d, appbuf *b, const char *title) {
    buf_append(d,b,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\"><title>");
    buf_append(d,b,title);
    buf_append(d,b," — VibeLog</title><style>");
    buf_append(d,b,APP_CSS);
    buf_append(d,b,"</style></head><body>");
}

// ===================== NAVBAR =====================
void render_navbar(appdeps *d, appbuf *b) {
    appjson *cats = d->json_parse_file("database/categorys.json");
    buf_append(d,b,"<nav class=\"navbar\"><a class=\"logo\" href=\"/\">VibeLog</a><div class=\"nav-links\">");
    int nc = cats ? d->json_get_array_size(cats) : 0;
    // Navbar buttons (navbar:true)
    for(int i=0;i<nc;i++){appjson *c=d->json_get_array_item(cats,i);if(d->json_is_true(d->json_get_object_item(c,"navbar"))){char *n=d->json_get_string_value(d->json_get_object_item(c,"name"));char *desc=d->json_get_string_value(d->json_get_object_item(c,"description"));char link[256];d->snprintf(link,256,"<a class=\"nav-btn\" href=\"/list_articles?page=1&amp;category=%s&amp;limit=10\" title=\"%s\">%s</a>",n,desc?desc:"",n);buf_append(d,b,link);}}
    // Dropdown for ALL categories
    buf_append(d,b,"<div class=\"dropdown\"><button class=\"nav-btn\" onclick=\"var m=this.nextElementSibling;m.classList.toggle('open');event.stopPropagation();\">Categories ▾</button><div class=\"dropdown-menu\">");
    for(int i=0;i<nc;i++){appjson *c=d->json_get_array_item(cats,i);char *n=d->json_get_string_value(d->json_get_object_item(c,"name"));char *desc=d->json_get_string_value(d->json_get_object_item(c,"description"));char link[256];d->snprintf(link,256,"<a href=\"/list_articles?page=1&amp;category=%s&amp;limit=10\" title=\"%s\">%s</a>",n,desc?desc:"",n);buf_append(d,b,link);}
    buf_append(d,b,"</div></div></div>");
    // Search
    buf_append(d,b,"<form class=\"search-form\" action=\"/list_articles\" method=\"GET\"><input type=\"hidden\" name=\"page\" value=\"1\"><input type=\"hidden\" name=\"limit\" value=\"10\"><input type=\"text\" name=\"search\" placeholder=\"Search...\"><button type=\"submit\">→</button></form>");
    buf_append(d,b,"</nav><script>document.addEventListener('click',function(){var els=document.querySelectorAll('.dropdown-menu');for(var i=0;i<els.length;i++)els[i].classList.remove('open');});</script>");
    if(cats) d->json_delete(cats);
}

void render_footer(appdeps *d, appbuf *b) { buf_append(d,b,"<footer class=\"site-footer\">// vibes compiled successfully</footer></body></html>"); }

// ===================== ERROR PAGE =====================
const appserverresponse *send_error(appdeps *d, int code, const char *msg) {
    appbuf b; buf_init(d,&b);
    char t[64]; d->snprintf(t,64,"%d Error",code);
    render_head(d,&b,t); render_navbar(d,&b);
    buf_append(d,&b,"<div class=\"wrap\"><div class=\"empty-state\" style=\"padding:80px 0;\"><h2 style=\"font-family:'Space Grotesk',sans-serif;font-size:3rem;color:#1c1c1f;margin-bottom:12px;\">");
    d->snprintf(t,64,"%d",code); buf_append(d,&b,t);
    buf_append(d,&b,"</h2><p>"); buf_append(d,&b,msg);
    buf_append(d,&b,"</p><p style=\"margin-top:16px;\"><a href=\"/\">← Back to home</a></p></div></div>");
    render_footer(d,&b);
    const appserverresponse *r = d->send_text(b.data,"text/html; charset=utf-8",code);
    buf_free(d,&b); return r;
}

// ===================== ARTICLE STRUCT =====================
#define MAX_ARTICLES 256
typedef struct { char date[16]; char id[128]; char title[256]; char summary[512]; char author_id[64]; char thumbnail[256]; char categories[16][64]; int cat_count; int sortkey; } article_entry;

int load_articles(appdeps *d, article_entry *out) {
    int count = 0;
    appstringarray *dates = d->list_dirs("database/articles");
    if (!dates) return 0;
    long nd = d->get_stringarray_size(dates);
    for (long di = 0; di < nd && count < MAX_ARTICLES; di++) {
        const char *dname = d->get_stringarray_item(dates, di);
        char *dp = d->concat_path("database/articles", dname);
        appstringarray *arts = d->list_dirs(dp);
        if (!arts) { d->free(dp); continue; }
        long na = d->get_stringarray_size(arts);
        for (long ai = 0; ai < na && count < MAX_ARTICLES; ai++) {
            const char *aname = d->get_stringarray_item(arts, ai);
            char *ap = d->concat_path(dp, aname);
            char *djp = d->concat_path(ap, "data.json");
            appjson *aj = d->json_parse_file(djp); d->free(djp);
            if (!aj) { d->free(ap); continue; }
            article_entry *e = &out[count];
            d->snprintf(e->date, 16, "%s", dname);
            d->snprintf(e->id, 128, "%s", aname);
            char *v;
            v = d->json_get_string_value(d->json_get_object_item(aj,"title")); d->snprintf(e->title,256,"%s",v?v:"");
            v = d->json_get_string_value(d->json_get_object_item(aj,"summary")); d->snprintf(e->summary,512,"%s",v?v:"");
            v = d->json_get_string_value(d->json_get_object_item(aj,"author_id")); d->snprintf(e->author_id,64,"%s",v?v:"");
            v = d->json_get_string_value(d->json_get_object_item(aj,"thumbnail")); d->snprintf(e->thumbnail,256,"%s",v?v:"");
            e->sortkey = parse_date_sortkey(dname);
            e->cat_count = 0;
            appjson *ca = d->json_get_object_item(aj,"categories");
            if(ca){int nc=d->json_get_array_size(ca);for(int ci=0;ci<nc&&ci<16;ci++){char *cn=d->json_get_string_value(d->json_get_array_item(ca,ci));d->snprintf(e->categories[ci],64,"%s",cn?cn:"");e->cat_count++;}}
            d->json_delete(aj);
            d->free(ap);
            count++;
        }
        d->delete_stringarray(arts);
        d->free(dp);
    }
    d->delete_stringarray(dates);
    // Sort descending by date
    for(int i=0;i<count-1;i++) for(int j=i+1;j<count;j++) if(out[j].sortkey>out[i].sortkey){article_entry t=out[i];out[i]=out[j];out[j]=t;}
    return count;
}

// ===================== RENDER ARTICLE CARD =====================
void render_card(appdeps *d, appbuf *b, article_entry *e) {
    buf_append(d,b,"<div class=\"card\">");
    char tmp[512];
    d->snprintf(tmp,512,"<a href=\"/article?date=%s&amp;id=%s\"><img src=\"/database_file?path=articles/%s/%s/%s\" alt=\"\"></a>",e->date,e->id,e->date,e->id,e->thumbnail);
    buf_append(d,b,tmp);
    buf_append(d,b,"<div class=\"card-body\">");
    d->snprintf(tmp,512,"<h3><a href=\"/article?date=%s&amp;id=%s\">%s</a></h3>",e->date,e->id,e->title);
    buf_append(d,b,tmp);
    // Truncate summary at 200 chars
    char summ[204]; int sl = d->strlen(e->summary); if(sl>200){d->memcpy(summ,e->summary,200);summ[200]='.';summ[201]='.';summ[202]='.';summ[203]='\0';}else{d->snprintf(summ,204,"%s",e->summary);}
    buf_append(d,b,"<p>"); buf_append(d,b,summ); buf_append(d,b,"</p>");
    // Date display
    char datebuf[32]; int sk = e->sortkey; int dy=sk/10000,dm=(sk%10000)/100,dd=sk%100;
    long ts_approx = 0; // reconstruct timestamp roughly
    // Use snprintf to format DD Mon YYYY from the date string
    // Parse date dir name DD-MM-YYYY and use get_formatted_time with "display"
    // Actually we can build a rough unix timestamp: days since epoch
    // Simpler: just reformat the date string DD-MM-YYYY -> display
    d->snprintf(datebuf,32,"%02d-%02d-%04d",dd,dm,dy);
    buf_append(d,b,"<div class=\"meta\">"); buf_append(d,b,datebuf);
    buf_append(d,b," · ");
    for(int i=0;i<e->cat_count;i++){d->snprintf(tmp,512,"<span class=\"badge\">%s</span>",e->categories[i]);buf_append(d,b,tmp);}
    buf_append(d,b,"</div></div></div>");
}

// ===================== RENDER SIDEBAR =====================
void render_sidebar(appdeps *d, appbuf *b) {
    sidebar_ensure(d);
    buf_append(d,b,"<aside class=\"sidebar\">");
    buf_append(d,b,"<div class=\"sb-card\"><h4>Total Views</h4>");
    char tmp[128]; d->snprintf(tmp,128,"<div class=\"stat-row\"><span>All articles</span><span>%d</span></div>",sidebar_total_views);
    buf_append(d,b,tmp);
    buf_append(d,b,"</div><div class=\"sb-card\"><h4>Views by Category</h4>");
    for(int i=0;i<sidebar_cat_count;i++){d->snprintf(tmp,128,"<div class=\"stat-row\"><span>%s</span><span>%d</span></div>",sidebar_cats[i].name,sidebar_cats[i].views);buf_append(d,b,tmp);}
    buf_append(d,b,"</div></aside>");
}

// ===================== ROUTE: HOME =====================
const appserverresponse *handle_home(appdeps *d) {
    article_entry arts[MAX_ARTICLES];
    int total = load_articles(d, arts);
    appbuf b; buf_init(d,&b);
    render_head(d,&b,"Home"); render_navbar(d,&b);
    buf_append(d,&b,"<div class=\"wrap\"><div class=\"main-grid\"><div class=\"articles\">");
    int show = total < 5 ? total : 5;
    for(int i=0;i<show;i++) render_card(d,&b,&arts[i]);
    if(total==0) buf_append(d,&b,"<div class=\"empty-state\">No articles yet.</div>");
    buf_append(d,&b,"</div>");
    render_sidebar(d,&b);
    buf_append(d,&b,"</div></div>");
    render_footer(d,&b);
    const appserverresponse *r = d->send_text(b.data,"text/html; charset=utf-8",200);
    buf_free(d,&b); return r;
}

// ===================== ROUTE: LIST ARTICLES =====================
const appserverresponse *handle_list_articles(appdeps *d) {
    const char *p_page = d->get_server_query_param(d->appserverrequest,"page");
    const char *p_limit = d->get_server_query_param(d->appserverrequest,"limit");
    const char *p_cat = d->get_server_query_param(d->appserverrequest,"category");
    const char *p_search = d->get_server_query_param(d->appserverrequest,"search");
    int page = p_page ? d->atoi(p_page) : 1; if(page<1) page=1;
    int limit = p_limit ? d->atoi(p_limit) : 10; if(limit<1) limit=1; if(limit>50) limit=50;

    article_entry all[MAX_ARTICLES];
    int total = load_articles(d, all);
    // Filter
    article_entry filtered[MAX_ARTICLES]; int fc=0;
    for(int i=0;i<total;i++){
        int match=1;
        if(p_cat && p_cat[0]){int cm=0;for(int ci=0;ci<all[i].cat_count;ci++){if(app_strcasecmp(all[i].categories[ci],p_cat)==0){cm=1;break;}}if(!cm) match=0;}
        if(match && p_search && p_search[0]){if(!app_strcasestr(all[i].title,p_search,d) && !app_strcasestr(all[i].summary,p_search,d)) match=0;}
        if(match) filtered[fc++]=all[i];
    }
    int start=(page-1)*limit; int end=start+limit; if(end>fc)end=fc;
    appbuf b; buf_init(d,&b);
    render_head(d,&b,"Articles"); render_navbar(d,&b);
    buf_append(d,&b,"<div class=\"wrap\"><div class=\"main-grid full\"><div class=\"articles\">");
    if(fc==0){buf_append(d,&b,"<div class=\"empty-state\"><p>No articles found.</p><p><a href=\"/\">← Back to home</a></p></div>");}
    else{for(int i=start;i<end;i++) render_card(d,&b,&filtered[i]);}
    // Pagination
    if(fc>0){
        buf_append(d,&b,"<div class=\"pagination\">");
        char link[512];
        if(page>1){d->snprintf(link,512,"<a href=\"/list_articles?page=%d&amp;limit=%d%s%s%s%s\">← Previous</a>",page-1,limit,p_cat?"&amp;category=":"",p_cat?p_cat:"",p_search?"&amp;search=":"",p_search?p_search:"");buf_append(d,&b,link);}
        if(end<fc){d->snprintf(link,512,"<a href=\"/list_articles?page=%d&amp;limit=%d%s%s%s%s\">Next →</a>",page+1,limit,p_cat?"&amp;category=":"",p_cat?p_cat:"",p_search?"&amp;search=":"",p_search?p_search:"");buf_append(d,&b,link);}
        buf_append(d,&b,"</div>");
    }
    buf_append(d,&b,"</div></div></div>");
    render_footer(d,&b);
    const appserverresponse *r = d->send_text(b.data,"text/html; charset=utf-8",200);
    buf_free(d,&b); return r;
}

// ===================== ROUTE: DATABASE FILE =====================
const char *get_extension(const char *path, appdeps *d) {
    const char *dot = app_null; const char *p = path;
    while(*p){if(*p=='.')dot=p;p++;}
    return dot ? dot : "";
}

const appserverresponse *handle_database_file(appdeps *d) {
    const char *path = d->get_server_query_param(d->appserverrequest,"path");
    if(!path || !path[0]) return send_error(d,400,"Invalid request");
    // Security: reject .., leading /, null bytes
    if(d->strstr(path,"..") || path[0]=='/' ) return send_error(d,403,"Access denied");
    for(const char *p=path;*p;p++){if(*p=='\0') return send_error(d,403,"Access denied");}
    char *full = d->concat_path("database", path);
    if(!d->file_exists(full)){d->free(full);return send_error(d,404,"Page not found");}
    // Determine content type
    const char *ext = get_extension(path,d);
    const char *ct = "application/octet-stream";
    int is_image = 0;
    if(app_strcasecmp(ext,".jpg")==0||app_strcasecmp(ext,".jpeg")==0){ct="image/jpeg";is_image=1;}
    else if(app_strcasecmp(ext,".png")==0){ct="image/png";is_image=1;}
    else if(app_strcasecmp(ext,".gif")==0){ct="image/gif";is_image=1;}
    else if(app_strcasecmp(ext,".webp")==0){ct="image/webp";is_image=1;}
    else if(app_strcasecmp(ext,".html")==0) ct="text/html; charset=utf-8";
    else if(app_strcasecmp(ext,".json")==0) ct="application/json";
    else if(app_strcasecmp(ext,".css")==0) ct="text/css";
    else if(app_strcasecmp(ext,".js")==0) ct="application/javascript";
    // Read and send
    long size=0; appbool is_bin=app_false;
    unsigned char *data = d->read_any(full,&size,&is_bin);
    d->free(full);
    if(!data) return send_error(d,500,"Internal server error");
    appserverresponse *resp = (appserverresponse*)d->newappserverresponse();
    d->setappserverresponse_content(resp,data,size);
    d->setappserverresponse_status_code(resp,200);
    d->setappserverresponse_header(resp,"Content-Type",ct);
    if(is_image) d->setappserverresponse_header(resp,"Cache-Control","public, max-age=86400");
    else d->setappserverresponse_header(resp,"Cache-Control","no-cache");
    d->free(data);
    return (const appserverresponse*)resp;
}

// ===================== ROUTE: ARTICLE =====================
void record_metrics(appdeps *d, const char *date, const char *id) {
    char mp[512];
    d->snprintf(mp,512,"database/metrics/articles/%s/%s",date,id);
    if(!d->dir_exists(mp)){d->create_dir(mp);char vp[512];d->snprintf(vp,512,"%s/views",mp);d->create_dir(vp);d->snprintf(vp,512,"%s/total_views.json",mp);d->write_string(vp,"{\"views\":0}");}
    // Atomic increment total_views
    char tvp[512]; d->snprintf(tvp,512,"%s/total_views.json",mp);
    appjson *vj = d->json_parse_file(tvp);
    int views = 0;
    if(vj){views=(int)d->json_get_number_value(d->json_get_object_item(vj,"views"));d->json_delete(vj);}
    views++;
    appjson *nj = d->json_create_object(); d->json_add_number_to_object(nj,"views",(double)views);
    char tmp_path[512]; d->snprintf(tmp_path,512,"%s/total_views.json.tmp",mp);
    d->json_save_file(nj,tmp_path); d->json_delete(nj);
    d->move_any(tmp_path,tvp);
    // Individual view
    long now = d->get_unix_time();
    long midnight = now - (now % 86400);
    char daybuf[32]; d->get_formatted_time(midnight,daybuf,32,"date");
    char daydir[512]; d->snprintf(daydir,512,"%s/views/%s:%ld",mp,daybuf,midnight);
    if(!d->dir_exists(daydir)) d->create_dir(daydir);
    int r1=d->get_random(),r2=d->get_random();
    if(r1<0)r1=-r1; if(r2<0)r2=-r2;
    char uuid[64]; d->snprintf(uuid,64,"%08x%08x",r1,r2);
    char vfp[512]; d->snprintf(vfp,512,"%s/%s.json",daydir,uuid);
    char iso[64]; d->get_formatted_time(now,iso,64,"iso");
    // Detect device
    const char *ua = d->get_server_header(d->appserverrequest,"User-Agent");
    const char *device = "desktop";
    if(ua && (d->strstr(ua,"Mobile")||d->strstr(ua,"Android")||d->strstr(ua,"iPhone"))) device="mobile";
    // Country
    const char *country = d->get_server_header(d->appserverrequest,"CF-IPCountry");
    if(!country) country = "unknown";
    appjson *view = d->json_create_object();
    d->json_add_string_to_object(view,"date",iso);
    d->json_add_string_to_object(view,"country",country);
    d->json_add_number_to_object(view,"duration",0);
    d->json_add_string_to_object(view,"device",device);
    d->json_save_file(view,vfp); d->json_delete(view);
}

const appserverresponse *handle_article(appdeps *d) {
    const char *date = d->get_server_query_param(d->appserverrequest,"date");
    const char *id = d->get_server_query_param(d->appserverrequest,"id");
    if(!date||!date[0]||!id||!id[0]) return send_error(d,400,"Invalid request");
    char adir[512]; d->snprintf(adir,512,"database/articles/%s/%s",date,id);
    char djp[512]; d->snprintf(djp,512,"%s/data.json",adir);
    if(!d->file_exists(djp)) return send_error(d,404,"Page not found");
    appjson *aj = d->json_parse_file(djp);
    if(!aj) return send_error(d,500,"Internal server error");
    // Language detection
    const char *al = d->get_server_header(d->appserverrequest,"Accept-Language");
    char lang[8]; lang[0]='e';lang[1]='n';lang[2]='\0';
    if(al){int i=0;while(al[i]&&al[i]!='-'&&al[i]!=','&&al[i]!=';'&&i<7){lang[i]=app_tolower(al[i]);i++;}lang[i]='\0';}
    char cpath[512]; d->snprintf(cpath,512,"%s/content/%s.html",adir,lang);
    if(!d->file_exists(cpath)) d->snprintf(cpath,512,"%s/content/en.html",adir);
    if(!d->file_exists(cpath)){d->json_delete(aj);return send_error(d,404,"Page not found");}
    char *html = d->read_string(cpath);
    if(!html){d->json_delete(aj);return send_error(d,500,"Internal server error");}
    // Record metrics
    record_metrics(d,date,id);
    // Build page
    char *title = d->json_get_string_value(d->json_get_object_item(aj,"title"));
    appbuf b; buf_init(d,&b);
    render_head(d,&b,title?title:"Article"); render_navbar(d,&b);
    buf_append(d,&b,"<div class=\"wrap\">");
    buf_append(d,&b,"<div class=\"article-header\"><h1>"); buf_append(d,&b,title?title:""); buf_append(d,&b,"</h1>");
    // Categories
    appjson *cats = d->json_get_object_item(aj,"categories");
    if(cats){int nc=d->json_get_array_size(cats);buf_append(d,&b,"<div style=\"margin-top:8px;\">");for(int i=0;i<nc;i++){char tmp[128];d->snprintf(tmp,128,"<span class=\"badge\">%s</span>",d->json_get_string_value(d->json_get_array_item(cats,i)));buf_append(d,&b,tmp);}buf_append(d,&b,"</div>");}
    buf_append(d,&b,"</div><div class=\"article-content\">");
    buf_append(d,&b,html); d->free(html);
    buf_append(d,&b,"</div>");
    // Footer with author
    char *aid = d->json_get_string_value(d->json_get_object_item(aj,"author_id"));
    if(aid){
        char adp[256]; d->snprintf(adp,256,"database/authors/%s/data.json",aid);
        appjson *auj = d->json_parse_file(adp);
        if(auj){
            char *aname=d->json_get_string_value(d->json_get_object_item(auj,"name"));
            char *apic=d->json_get_string_value(d->json_get_object_item(auj,"picture"));
            buf_append(d,&b,"<div class=\"article-footer\">");
            char tmp[512];
            if(apic){d->snprintf(tmp,512,"<img src=\"/database_file?path=authors/%s/%s\">",aid,apic);buf_append(d,&b,tmp);}
            buf_append(d,&b,"<div class=\"af-info\">");
            d->snprintf(tmp,512,"<a href=\"/author?id=%s\">%s</a>",aid,aname?aname:"");buf_append(d,&b,tmp);
            buf_append(d,&b,"<br>"); buf_append(d,&b,date);
            buf_append(d,&b,"</div></div>");
            d->json_delete(auj);
        }
    }
    buf_append(d,&b,"</div>"); render_footer(d,&b);
    d->json_delete(aj);
    const appserverresponse *r = d->send_text(b.data,"text/html; charset=utf-8",200);
    buf_free(d,&b); return r;
}

// ===================== ROUTE: AUTHOR =====================
const appserverresponse *handle_author(appdeps *d) {
    const char *id = d->get_server_query_param(d->appserverrequest,"id");
    if(!id||!id[0]) return send_error(d,400,"Invalid request");
    char adp[256]; d->snprintf(adp,256,"database/authors/%s/data.json",id);
    if(!d->file_exists(adp)) return send_error(d,404,"Page not found");
    appjson *aj = d->json_parse_file(adp);
    if(!aj) return send_error(d,500,"Internal server error");
    char *name=d->json_get_string_value(d->json_get_object_item(aj,"name"));
    char *desc=d->json_get_string_value(d->json_get_object_item(aj,"description"));
    char *pic=d->json_get_string_value(d->json_get_object_item(aj,"picture"));
    appbuf b; buf_init(d,&b);
    render_head(d,&b,name?name:"Author"); render_navbar(d,&b);
    buf_append(d,&b,"<div class=\"wrap\"><div class=\"author-header\">");
    char tmp[512];
    if(pic){d->snprintf(tmp,512,"<img src=\"/database_file?path=authors/%s/%s\">",id,pic);buf_append(d,&b,tmp);}
    buf_append(d,&b,"<div><h1>"); buf_append(d,&b,name?name:""); buf_append(d,&b,"</h1>");
    if(desc){buf_append(d,&b,"<p>");buf_append(d,&b,desc);buf_append(d,&b,"</p>");}
    buf_append(d,&b,"</div></div>");
    // Author's articles
    article_entry arts[MAX_ARTICLES]; int total = load_articles(d,arts);
    buf_append(d,&b,"<h3 style=\"font-family:'Space Grotesk',sans-serif;margin-bottom:16px;\">Articles</h3>");
    int found=0;
    for(int i=0;i<total;i++){if(app_strcasecmp(arts[i].author_id,id)==0){render_card(d,&b,&arts[i]);found++;}}
    if(!found) buf_append(d,&b,"<p style=\"color:#52525b;\">No articles yet.</p>");
    buf_append(d,&b,"</div>"); render_footer(d,&b);
    d->json_delete(aj);
    const appserverresponse *r = d->send_text(b.data,"text/html; charset=utf-8",200);
    buf_free(d,&b); return r;
}

// ===================== ROUTE: ABOUT =====================
const appserverresponse *handle_about(appdeps *d) {
    char *html = d->read_string("database/pages/about.html");
    appbuf b; buf_init(d,&b);
    render_head(d,&b,"About"); render_navbar(d,&b);
    buf_append(d,&b,"<div class=\"wrap\">");
    if(html){buf_append(d,&b,html);d->free(html);}
    else buf_append(d,&b,"<div class=\"empty-state\">About page not found.</div>");
    buf_append(d,&b,"</div>"); render_footer(d,&b);
    const appserverresponse *r = d->send_text(b.data,"text/html; charset=utf-8",200);
    buf_free(d,&b); return r;
}

// ===================== MAIN SERVER =====================
int app_route_match(const char *route, const char *target, appdeps *d) {
    return d->strcmp(route, target) == 0;
}

const appserverresponse *private_mainserver(appdeps *d, void *props) {
    const char *route = d->get_server_route(d->appserverrequest);
    const char *method = d->get_server_method(d->appserverrequest);

    // Only GET
    if(d->strcmp(method,"GET")!=0) return send_error(d,400,"Invalid request");

    if(app_route_match(route,"/",d)) return handle_home(d);
    if(app_route_match(route,"/list_articles",d)) return handle_list_articles(d);
    if(app_route_match(route,"/article",d)) return handle_article(d);
    if(app_route_match(route,"/database_file",d)) return handle_database_file(d);
    if(app_route_match(route,"/author",d)) return handle_author(d);
    if(app_route_match(route,"/about",d)) return handle_about(d);

    return send_error(d,404,"Page not found");
}

int appmain(appdeps *d) {
    const char *PORT_FLAGS[] = {"port", "p"};
    const char *start_port = d->get_arg_flag_value(d->argv, PORT_FLAGS, sizeof(PORT_FLAGS) / sizeof(PORT_FLAGS[0]), 0);
    int port = 8080;
    if (start_port) {
        port = d->atoi(start_port);
        if (port <= 0) { d->printf("Invalid port number: %s\n", start_port); return 1; }
    }
    d->printf("VibeLog starting on port %d...\n", port);
    d->start_server(port, private_mainserver, app_null, app_false);
    return 0;
}
