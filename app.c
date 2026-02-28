// ===============================APP
// SANDBOX====================================== This is an app server sandbox,
// don't use any '#include' in this file you are a vibecode agent, always return
// the full code, including these comments if an error happens, you can use the
// print function to show the error
//======================PRIMITIVES=================================================

typedef int appbool;

#define app_true 1
#define app_false 0
#define app_null ((void *)0)

//======================APP
// TYPES==================================================
typedef void appclientrequest;
typedef void appclientresponse;
typedef void appserverrequest;
typedef void appserverresponse;
typedef void appjson;
typedef void appstringarray;
typedef void appargv;
typedef void appctext;

//======================APP
// DEPS======================================================
typedef struct appdeps appdeps;
struct appdeps {

  //=====================STD
  // FUNCTIONS==============================================
  int (*printf)(const char *format, ...);
  int (*custom_sprintf)(char *str, const char *format, ...);
  int (*snprintf)(char *str, unsigned long size, const char *format, ...);

  unsigned long (*strlen)(const char *s);
  char *(*custom_strcpy)(char *dst, const char *src);
  char *(*custom_strcat)(char *dst, const char *src);
  int (*strcmp)(const char *s1, const char *s2);
  int (*strncmp)(const char *s1, const char *s2, unsigned long n);
  char *(*strstr)(const char *haystack, const char *needle);
  char *(*strdup)(const char *s);
  void *(*custom_memcpy)(void *dst, const void *src, unsigned long n);
  void *(*custom_memset)(void *s, int c, unsigned long n);
  int (*memcmp)(const void *s1, const void *s2, unsigned long n);

  //======================CONVERSION
  // FUNCTIONS======================================
  int (*atoi)(const char *str);
  double (*atof)(const char *str);
  //======================MEM
  // FUNCTIONS=============================================
  void (*free)(void *ptr);
  void *(*malloc)(unsigned long size);
  void *(*calloc)(unsigned long num, unsigned long size);
  void *(*realloc)(void *ptr, unsigned long size);
  //=====================request===================================================
  const appserverrequest *appserverrequest;
  const char *(*get_server_route)(const appserverrequest *appserverrequest);
  const char *(*get_server_method)(const appserverrequest *appserverrequest);

  const char *(*get_server_header)(const appserverrequest *appserverrequest,
                                   const char *key);
  const char *(*get_server_header_key)(const appserverrequest *appserverrequest,
                                       int index);
  const char *(*get_server_header_value)(
      const appserverrequest *appserverrequest, int index);

  const char *(*get_server_query_param)(
      const appserverrequest *appserverrequest, const char *key);
  const char *(*get_server_query_param_key)(
      const appserverrequest *appserverrequest, int index);
  const char *(*get_server_query_param_value)(
      const appserverrequest *appserverrequest, int index);

  int (*get_server_header_count)(const appserverrequest *appserverrequest);
  int (*get_server_query_param_count)(const appserverrequest *appserverrequest);

  const unsigned char *(*read_server_body)(
      const appserverrequest *appserverrequest, long size, long *read_size);
  const appjson *(*read_server_json)(const appserverrequest *appserverrequest,
                                     long size);
  const appserverresponse *(*newappserverresponse)();
  void (*setappserverresponse_header)(appserverresponse *appserverresponse,
                                      const char *key, const char *value);
  void (*setappserverresponse_content)(appserverresponse *appserverresponse,
                                       const unsigned char *content,
                                       long content_size);
  void (*setappserverresponse_status_code)(appserverresponse *appserverresponse,
                                           int status_code);

  const appserverresponse *(*send_any)(const unsigned char *content,
                                       long content_size,
                                       const char *content_type,
                                       int status_code);
  const appserverresponse *(*send_text)(const char *text,
                                        const char *content_type,
                                        int status_code);
  const appserverresponse *(*send_file)(const char *path,
                                        const char *content_type,
                                        int status_code);
  const appserverresponse *(*send_json)(const appjson *json, int status_code);

  //=====================JSON
  // PARSING===================================================
  appjson *(*json_parse)(const char *value);
  appjson *(*json_parse_file)(const char *filepath);
  void (*json_delete)(appjson *json);

  //=====================JSON
  // SERIALIZATION==============================================
  char *(*json_print)(const appjson *json);
  char *(*json_print_unformatted)(const appjson *json);
  appbool (*json_save_file)(const appjson *json, const char *filepath);
  void (*json_free_string)(char *str);

  //=====================JSON
  // CREATION==============================================
  appjson *(*json_create_object)(void);
  appjson *(*json_create_array)(void);
  appjson *(*json_create_string)(const char *string);
  appjson *(*json_create_number)(double num);
  appjson *(*json_create_bool)(appbool boolean);
  appjson *(*json_create_null)(void);
  appjson *(*json_duplicate)(const appjson *item, appbool recurse);

  //=====================JSON OBJECT
  // MANIPULATION=========================================
  appjson *(*json_get_object_item)(const appjson *object, const char *key);
  appbool (*json_has_object_item)(const appjson *object, const char *key);
  appbool (*json_add_item_to_object)(appjson *object, const char *key,
                                     appjson *item);
  appbool (*json_delete_item_from_object)(appjson *object, const char *key);
  appbool (*json_replace_item_in_object)(appjson *object, const char *key,
                                         appjson *newitem);

  // Convenience functions for adding to objects
  appjson *(*json_add_string_to_object)(appjson *object, const char *key,
                                        const char *string);
  appjson *(*json_add_number_to_object)(appjson *object, const char *key,
                                        double number);
  appjson *(*json_add_bool_to_object)(appjson *object, const char *key,
                                      appbool boolean);
  appjson *(*json_add_null_to_object)(appjson *object, const char *key);
  appjson *(*json_add_object_to_object)(appjson *object, const char *key);
  appjson *(*json_add_array_to_object)(appjson *object, const char *key);

  //=====================JSON ARRAY
  // MANIPULATION==============================================
  int (*json_get_array_size)(const appjson *array);
  appjson *(*json_get_array_item)(const appjson *array, int index);
  appbool (*json_add_item_to_array)(appjson *array, appjson *item);
  appbool (*json_insert_item_in_array)(appjson *array, int index,
                                       appjson *item);
  appbool (*json_replace_item_in_array)(appjson *array, int index,
                                        appjson *newitem);
  void (*json_delete_item_from_array)(appjson *array, int index);

  //=====================JSON TYPE
  // CHECKING==============================================
  appbool (*json_is_object)(const appjson *item);
  appbool (*json_is_array)(const appjson *item);
  appbool (*json_is_string)(const appjson *item);
  appbool (*json_is_number)(const appjson *item);
  appbool (*json_is_bool)(const appjson *item);
  appbool (*json_is_null)(const appjson *item);
  appbool (*json_is_true)(const appjson *item);
  appbool (*json_is_false)(const appjson *item);

  //=====================JSON VALUE
  // GETTERS==============================================
  char *(*json_get_string_value)(const appjson *item);
  double (*json_get_number_value)(const appjson *item);

  //=====================JSON
  // COMPARISON=================================================
  appbool (*json_compare)(const appjson *a, const appjson *b,
                          appbool case_sensitive);

  //=====================JSON
  // ITERATION=================================================
  appjson *(*json_get_child)(
      const appjson *item); // first child of object/array
  appjson *(*json_get_next)(
      const appjson *item); // next sibling in object/array
  const char *(*json_get_key)(
      const appjson *item); // key name of this item (if inside object)
  int (*json_get_object_size)(
      const appjson *object); // number of keys in object

  //======================IO FUNCTIONS
  //==================================================
  unsigned char *(*read_any)(const char *path, long *size, appbool *is_binary);
  char *(*read_string)(const char *path); // needs to be freed
  void (*write_any)(const char *path, const unsigned char *content, long size);
  void (*write_string)(const char *path, const char *content);
  void (*delete_any)(const char *path);
  void (*create_dir)(const char *path);

  void (*delete_stringarray)(appstringarray *array);
  long (*get_stringarray_size)(appstringarray *array);
  const char *(*get_stringarray_item)(appstringarray *array, int index);
  char *(*get_sha256)(const unsigned char *content, long size);
  // retturns the sha256 of a file, using a cache tecnique to improve performace
  char *(*get_cached_file_sha)(const char *cache_dir, const char *path);

  // all the listage functions return only the itens, they dont concatenate the
  // path example depos->list_files("teste") -> array
  // appstringarray->get_stringarray_item(array, 0) -> "a" (not "teste/a")

  appstringarray *(*list_files)(const char *path);
  appstringarray *(*list_dirs)(const char *path);
  appstringarray *(*list_any)(const char *path);
  appstringarray *(*list_files_recursively)(const char *path);
  appstringarray *(*list_dirs_recursively)(const char *path);
  appstringarray *(*list_any_recursively)(const char *path);

  appbool (*file_exists)(const char *path);
  appbool (*dir_exists)(const char *path);
  appbool (*copy_any)(const char *src, const char *dst);
  appbool (*move_any)(const char *src, const char *dst);
  void (*append_string)(const char *path, const char *content);
  char *(*concat_path)(const char *path1,
                       const char *path2); // needs to be freed

  //======================ARGV PARSER FUNCTIONS
  //======================================
  const appargv *argv;
  const char *(*get_arg_value)(const appargv *argv,
                               int index);   // positional arguments
  int (*get_arg_count)(const appargv *argv); // number of arguments

  // use const char *help[] = {"help","h"}; for retrieving flags
  const char *(*get_arg_flag_value)(const appargv *argv, const char **flags,
                                    int total_flags,
                                    int index); // --name || n mateus : mateus
  int (*get_arg_flag_count)(const appargv *argv, const char **flags,
                            int total_flags); // --name || n : true

  appbool (*has_arg_flag)(const appargv *argv, const char **flags,
                          int total_flags); // --name : true

  appclientrequest *(*newappclientrequest)(const char *url);
  void (*appclientrequest_set_header)(appclientrequest *appclientrequest,
                                      const char *key, const char *value);
  void (*appclientrequest_set_method)(appclientrequest *appclientrequest,
                                      const char *method);
  void (*appclientrequest_set_max_redirections)(
      appclientrequest *appclientrequest, int max_redirects);
  void (*appclientrequest_set_body)(appclientrequest *appclientrequest,
                                    unsigned char *content, long size);
  void (*appclientrequest_free)(appclientrequest *request);

  appclientresponse *(*appclientrequest_fetch)(
      appclientrequest *appclientrequest);
  int (*appclientresponse_get_status_code)(
      appclientresponse *appclientresponse);
  int (*appcliente_response_get_headder_count)(
      appclientresponse *appclientresponse);
  const unsigned char *(*appclientresponse_read_body)(
      appclientresponse *appclientresponse, long *size);
  long (*appclientresponse_get_body_size)(appclientresponse *appclientresponse);
  const char *(*appclientresponse_get_header_value_by_key)(
      appclientresponse *appclientresponse, const char *key);
  const char *(*appclientresponse_get_header_key_by_index)(
      appclientresponse *appclientresponse, int index);
  const char *(*appclientresponse_get_header_value_by_index)(
      appclientresponse *appclientresponse, int index);
  int (*appclientresponse_get_header_size)(
      appclientresponse *appclientresponse);
  void (*free_clientresponse)(appclientresponse *appclientresponse);

  //============================ASSETS==================================================
  const unsigned char *(*get_asset_content)(const char *path, long *size,
                                            appbool *is_binary);
  appstringarray *(*list_assets)(const char *path);

  //============================TIME==================================================
  long (*get_unix_time)(void);
  int (*get_random)(void);
  void (*get_formatted_time)(long timestamp, char *buf, int buf_size,
                             const char *fmt);
  //============================SERVER==================================================
  int (*start_server)(int port,
                      const appserverresponse *(*handler)(appdeps *d,
                                                          void *props),
                      void *props, appbool single_process);

  //============================TEXT
  // STACK==================================================
  appctext *(*new_ctext)(const char *text_or_null);
  void (*ctext_append)(appctext *text_stack, const char *text);
  const char *(*ctext_get_text)(appctext *text_stack);
  void (*ctext_free)(appctext *text_stack);
  void (*ctext_restart)(appctext *text_stack);
  appctext *(*ctext_clone)(appctext *text_stack);
  void (*ctext_self_substr)(appctext *text_stack, long starter, long end);
  void (*ctext_self_pop)(appctext *text_stack, long starter, long end);
  void (*ctext_self_insert_at)(appctext *text_stack, long point,
                               const char *element);
  void (*ctext_self_replace)(appctext *text_stack, const char *element,
                             const char *element_to_replace);
  void (*ctext_self_replace_long)(appctext *text_stack, const char *element,
                                  long element_to_replace);
  void (*ctext_self_replace_double)(appctext *text_stack, const char *element,
                                    double element_to_replace);
  void (*ctext_self_lower)(appctext *text_stack);
  void (*ctext_self_upper)(appctext *text_stack);
  void (*ctext_self_captalize)(appctext *text_stack);
  void (*ctext_self_reverse)(appctext *text_stack);
  void (*ctext_self_trim)(appctext *text_stack);
  appbool (*ctext_starts_with)(appctext *text_stack, const char *element);
  appbool (*ctext_ends_with)(appctext *text_stack, const char *element);
  appbool (*ctext_equal)(appctext *text_stack, const char *element);
  int (*ctext_typeof_element)(appctext *text_stack);
  appbool (*ctext_is_a_num)(appctext *text_stack);
  const char *(*ctext_typeof_in_str)(appctext *text_stack);
  appbool (*ctext_parse_to_bool)(appctext *text_stack);
  long (*ctext_parse_to_integer)(appctext *text_stack);
  double (*ctext_parse_to_double)(appctext *text_stack);
  long (*ctext_index_of)(appctext *text_stack, const char *element);
  long (*ctext_index_of_char)(appctext *text_stack, char element);

  int (*run_command)(const char *cmd);
};

// ===============================VIBELOG CONFIG================================
typedef struct {
  const char *database_path;
  const char *root_password;
  int port;
  int max_view;
  const char *cache_dir;
  const char *markdown_converter_command;
} VibeLogConfig;

VibeLogConfig global_config = {0};

// ===============================VIBELOG TEXT CONFIG==========================
typedef struct {
  const char *blog_name;
  const char *logo_text;
  const char *categories_dropdown_label;
  const char *search_placeholder;
  const char *sidebar_status_title;
  const char *sidebar_total_views_label;
  const char *sidebar_traffic_title;
  const char *footer_text;
  const char *home_page_title;
  const char *articles_page_title;
  const char *filter_by_label;
  const char *clear_filter_label;
  const char *no_articles_text;
  const char *pagination_prev_label;
  const char *pagination_next_label;
  const char *published_on_label;
  const char *content_unavailable_text;
  const char *view_profile_label;
  const char *recent_articles_by_label;
  const char *no_author_articles_text;
  const char *about_page_title;
  const char *about_fallback_content;
} VibeLogText;

VibeLogText global_text = {0};

// cache
appjson *cached_categories = app_null;
appjson *cached_text_config = app_null;

// current lang (set per-request by router)
char *current_lang = app_null;

// ===============================HELPER PROTOTYPES=============================
const char *get_mime_type(appdeps *d, const char *path);
appbool is_safe_path(appdeps *d, const char *path) {
  if (d->strstr(path, ".."))
    return app_false;
  // Check null bytes? String functions usually fail on them anyway.
  return app_true;
}
char *render_page(appdeps *d, const char *lang, const char *title, const char *content);
void load_global_data(appdeps *d, const char *lang_db_path);
void load_text_config(appdeps *d, const char *lang_db_path);
appjson *load_articles(appdeps *d, const char *lang_db_path, int page, int limit, const char *category,
                       const char *search, const char *author_id);
appjson *load_author(appdeps *d, const char *lang_db_path, const char *author_id);
void record_view(appdeps *d, const char *lang_db_path, const char *date, const char *id,
                 const char *language, const char *device, const char *country, double duration);
const appserverresponse *handle_api_record_view(appdeps *d, const appserverrequest *req);
void record_page_view(appdeps *d, const char *lang_db_path, const char *page_id, int chunk, int size,
                      const char *category, const char *search,
                      const char *language, const char *device, const char *country, double duration);
const appserverresponse *handle_api_record_page_view(appdeps *d, const appserverrequest *req);

// ===============================MARKDOWN CONTENT==============================
// Loads article HTML content. If a content.md file exists and a markdown
// converter is configured, converts it to HTML with caching. Falls back to
// content.html. Caller must free the returned string.
char *load_article_content(appdeps *d, const char *article_dir) {
  if (global_config.markdown_converter_command && global_config.cache_dir) {
    char *md_path = d->concat_path(article_dir, "content.md");
    if (d->file_exists(md_path)) {
      char *sha = d->get_cached_file_sha(global_config.cache_dir, md_path);
      if (sha) {
        long path_len = d->strlen(global_config.cache_dir) + d->strlen(sha) + 32;
        char *cached_html_path = d->malloc(path_len);
        d->snprintf(cached_html_path, path_len, "%s/markdown_cache/%s.html",
                    global_config.cache_dir, sha);

        if (!d->file_exists(cached_html_path)) {
          long dir_len = d->strlen(global_config.cache_dir) + 32;
          char *md_cache_dir = d->malloc(dir_len);
          d->snprintf(md_cache_dir, dir_len, "%s/markdown_cache",
                      global_config.cache_dir);
          if (!d->dir_exists(md_cache_dir)) {
            d->create_dir(md_cache_dir);
          }
          d->free(md_cache_dir);

          appctext *cmd =
              d->new_ctext(global_config.markdown_converter_command);
          d->ctext_self_replace(cmd, "#INPUT#", md_path);
          d->ctext_self_replace(cmd, "#OUTPUT#", cached_html_path);
          const char *cmd_text = d->ctext_get_text(cmd);
          d->printf("Markdown converter: %s\n", cmd_text);
          d->run_command(cmd_text);
          d->ctext_free(cmd);
        }

        char *content = d->read_string(cached_html_path);
        d->free(cached_html_path);
        d->free(sha);
        d->free(md_path);
        if (content)
          return content;
        // If conversion failed, fall through to content.html
      } else {
        d->free(md_path);
      }
    } else {
      d->free(md_path);
    }
  }

  char *html_path = d->concat_path(article_dir, "content.html");
  char *content = d->read_string(html_path);
  d->free(html_path);
  return content;
}

// ===============================HANDLERS======================================
const appserverresponse *handle_article(appdeps *d,
                                        const appserverrequest *req) {
  char *lang_db_path = d->concat_path(global_config.database_path, current_lang);
  load_text_config(d, lang_db_path);
  const char *date = d->get_server_query_param(req, "date");
  const char *id = d->get_server_query_param(req, "id");

  if (!date || !id) {
    d->free(lang_db_path);
    return d->send_text("Missing parameters", "text/plain", 400);
  }

  // Load Article Data
  char *path = d->concat_path(lang_db_path, "articles");
  char *tmp = d->concat_path(path, date);
  d->free(path);
  path = d->concat_path(tmp, id);
  d->free(tmp);

  char *json_path = d->concat_path(path, "data.json");
  if (!d->file_exists(json_path)) {
    d->free(json_path);
    d->free(path);
    d->free(lang_db_path);
    return d->send_text("Article not found", "text/plain", 404);
  }

  appjson *data = d->json_parse_file(json_path);
  d->free(json_path);

  if (!data) {
    d->free(path);
    d->free(lang_db_path);
    return d->send_text("Corrupt article data", "text/plain", 500);
  }


  // Wrapper for content
  appctext *t = d->new_ctext(app_null);

  // Title
  const char *title =
      d->json_get_string_value(d->json_get_object_item(data, "title"));
  d->ctext_append(t, "<article class='article-container'>");
  d->ctext_append(t, "<h1 class='article-title'>");
  d->ctext_append(t, title);
  d->ctext_append(t, "</h1>");

  // Categories
  appjson *cats = d->json_get_object_item(data, "categories");
  if (cats && d->json_is_array(cats)) {
    d->ctext_append(t, "<div class='article-categories'>");
    int c_size = d->json_get_array_size(cats);
    for (int i = 0; i < c_size; i++) {
      const char *cname =
          d->json_get_string_value(d->json_get_array_item(cats, i));
      d->ctext_append(t, "<span class='badge' style='margin-right:0.5rem'>");
      d->ctext_append(t, cname);
      d->ctext_append(t, "</span>");
    }
    d->ctext_append(t, "</div>");
  }

  d->ctext_append(t, "<div class='article-meta' style='margin-bottom:2rem; "
                     "color:#71717a;'>");
  d->ctext_append(t, global_text.published_on_label);
  d->ctext_append(t, date);
  d->ctext_append(t, "</div>");

  // Content (content.md with markdown conversion if configured, else content.html)
  char *html_content = load_article_content(d, path);

  if (html_content) {
    d->ctext_append(t, "<div class='article-body' style='line-height:1.8'>");
    d->ctext_append(t, html_content);
    d->ctext_append(t, "</div>");
    d->free(html_content);
  } else {
    d->ctext_append(t, "<p>");
    d->ctext_append(t, global_text.content_unavailable_text);
    d->ctext_append(t, "</p>");
  }

  // Author
  const char *author_id =
      d->json_get_string_value(d->json_get_object_item(data, "author_id"));
  if (author_id) {
    appjson *author = load_author(d, lang_db_path, author_id);
    if (author) {
      const char *aname =
          d->json_get_string_value(d->json_get_object_item(author, "name"));
      const char *apic =
          d->json_get_string_value(d->json_get_object_item(author, "picture"));

      d->ctext_append(t, "<div class='author-box' style='margin-top:4rem; "
                         "border-top:1px solid #1c1c1f; padding-top:2rem; "
                         "display:flex; align-items:center; gap:1rem;'>");
      if (apic) {
        d->ctext_append(t, "<img src='/database_file?path=");
        d->ctext_append(t, current_lang);
        d->ctext_append(t, "/authors/");
        d->ctext_append(t, author_id);
        d->ctext_append(t, "/");
        d->ctext_append(t, apic);
        d->ctext_append(t,
                        "' style='width:64px; height:64px; border-radius:50%; "
                        "object-fit:cover; border:1px solid #1c1c1f;'>");
      }
      d->ctext_append(t,
                      "<div><div style='font-weight:600; font-size:1.1rem;'>");
      d->ctext_append(t, aname);
      d->ctext_append(t, "</div><a href='/");
      d->ctext_append(t, current_lang);
      d->ctext_append(t, "/author?id=");
      d->ctext_append(t, author_id);
      d->ctext_append(t,
                      "' class='btn' style='font-size:0.7rem; padding:0.2rem "
                      "0.5rem; margin-top:0.5rem;'>");
      d->ctext_append(t, global_text.view_profile_label);
      d->ctext_append(t, "</a></div>");

      d->ctext_append(t, "</div>");
      d->json_delete(author);
    }
  }

  // Client-side view tracking script
  d->ctext_append(t, "<script>");
  d->ctext_append(t, "(function(){");
  d->ctext_append(t, "var _vl_start=Date.now();");
  d->ctext_append(t, "var _vl_date='");
  d->ctext_append(t, date);
  d->ctext_append(t, "';");
  d->ctext_append(t, "var _vl_id='");
  d->ctext_append(t, id);
  d->ctext_append(t, "';");
  d->ctext_append(t, "var _vl_lang='");
  d->ctext_append(t, current_lang);
  d->ctext_append(t, "';");
  d->ctext_append(t, "var _vl_sent=false;");
  d->ctext_append(t, "function _vl_device(){");
  d->ctext_append(t, "var w=screen.width||window.innerWidth;");
  d->ctext_append(t, "if(w<768)return 'mobile';");
  d->ctext_append(t, "if(w<1024)return 'tablet';");
  d->ctext_append(t, "return 'desktop';}");
  d->ctext_append(t, "function _vl_country(){");
  d->ctext_append(t, "try{var tz=Intl.DateTimeFormat().resolvedOptions().timeZone;");
  d->ctext_append(t, "var m={");
  d->ctext_append(t, "'America/New_York':'US','America/Chicago':'US','America/Denver':'US','America/Los_Angeles':'US','America/Anchorage':'US','America/Phoenix':'US','America/Detroit':'US','America/Indiana':'US',");
  d->ctext_append(t, "'America/Sao_Paulo':'BR','America/Fortaleza':'BR','America/Bahia':'BR','America/Belem':'BR','America/Manaus':'BR','America/Recife':'BR','America/Cuiaba':'BR','America/Campo_Grande':'BR','America/Araguaina':'BR','America/Maceio':'BR',");
  d->ctext_append(t, "'America/Argentina/Buenos_Aires':'AR','America/Argentina/Cordoba':'AR','America/Argentina/Mendoza':'AR',");
  d->ctext_append(t, "'America/Santiago':'CL','America/Bogota':'CO','America/Lima':'PE','America/Caracas':'VE','America/Guayaquil':'EC',");
  d->ctext_append(t, "'America/Mexico_City':'MX','America/Cancun':'MX','America/Monterrey':'MX','America/Tijuana':'MX',");
  d->ctext_append(t, "'America/Toronto':'CA','America/Vancouver':'CA','America/Edmonton':'CA','America/Halifax':'CA','America/Winnipeg':'CA',");
  d->ctext_append(t, "'America/Montevideo':'UY','America/Asuncion':'PY','America/La_Paz':'BO','America/Havana':'CU','America/Panama':'PA','America/Costa_Rica':'CR','America/Guatemala':'GT',");
  d->ctext_append(t, "'Europe/London':'GB','Europe/Paris':'FR','Europe/Berlin':'DE','Europe/Madrid':'ES','Europe/Rome':'IT','Europe/Amsterdam':'NL','Europe/Brussels':'BE','Europe/Zurich':'CH','Europe/Vienna':'AT',");
  d->ctext_append(t, "'Europe/Lisbon':'PT','Europe/Warsaw':'PL','Europe/Prague':'CZ','Europe/Budapest':'HU','Europe/Bucharest':'RO','Europe/Sofia':'BG','Europe/Athens':'GR','Europe/Helsinki':'FI',");
  d->ctext_append(t, "'Europe/Stockholm':'SE','Europe/Oslo':'NO','Europe/Copenhagen':'DK','Europe/Dublin':'IE','Europe/Moscow':'RU','Europe/Kiev':'UA','Europe/Istanbul':'TR',");
  d->ctext_append(t, "'Asia/Tokyo':'JP','Asia/Shanghai':'CN','Asia/Chongqing':'CN','Asia/Hong_Kong':'HK','Asia/Seoul':'KR','Asia/Kolkata':'IN','Asia/Calcutta':'IN','Asia/Mumbai':'IN',");
  d->ctext_append(t, "'Asia/Singapore':'SG','Asia/Bangkok':'TH','Asia/Jakarta':'ID','Asia/Manila':'PH','Asia/Taipei':'TW','Asia/Dubai':'AE','Asia/Riyadh':'SA','Asia/Tehran':'IR','Asia/Karachi':'PK',");
  d->ctext_append(t, "'Asia/Dhaka':'BD','Asia/Colombo':'LK','Asia/Kuala_Lumpur':'MY','Asia/Ho_Chi_Minh':'VN','Asia/Saigon':'VN',");
  d->ctext_append(t, "'Africa/Cairo':'EG','Africa/Lagos':'NG','Africa/Johannesburg':'ZA','Africa/Nairobi':'KE','Africa/Casablanca':'MA','Africa/Algiers':'DZ','Africa/Tunis':'TN',");
  d->ctext_append(t, "'Australia/Sydney':'AU','Australia/Melbourne':'AU','Australia/Brisbane':'AU','Australia/Perth':'AU','Australia/Adelaide':'AU',");
  d->ctext_append(t, "'Pacific/Auckland':'NZ','Pacific/Fiji':'FJ','Pacific/Honolulu':'US'");
  d->ctext_append(t, "};");
  d->ctext_append(t, "return m[tz]||'unknown';");
  d->ctext_append(t, "}catch(e){return 'unknown';}}");
  d->ctext_append(t, "function _vl_send(){");
  d->ctext_append(t, "if(_vl_sent)return;");
  d->ctext_append(t, "_vl_sent=true;");
  d->ctext_append(t, "var dur=Math.round((Date.now()-_vl_start)/1000);");
  d->ctext_append(t, "var data=JSON.stringify({");
  d->ctext_append(t, "date:_vl_date,id:_vl_id,lang:_vl_lang,");
  d->ctext_append(t, "language:navigator.language||'unknown',");
  d->ctext_append(t, "device:_vl_device(),");
  d->ctext_append(t, "country:_vl_country(),");
  d->ctext_append(t, "duration:dur});");
  d->ctext_append(t, "if(navigator.sendBeacon){");
  d->ctext_append(t, "navigator.sendBeacon('/api/record_view',new Blob([data],{type:'application/json'}));");
  d->ctext_append(t, "}else{");
  d->ctext_append(t, "var x=new XMLHttpRequest();");
  d->ctext_append(t, "x.open('POST','/api/record_view',false);");
  d->ctext_append(t, "x.setRequestHeader('Content-Type','application/json');");
  d->ctext_append(t, "x.send(data);}}");
  d->ctext_append(t, "document.addEventListener('visibilitychange',function(){if(document.visibilityState==='hidden')_vl_send();});");
  d->ctext_append(t, "window.addEventListener('beforeunload',_vl_send);");
  d->ctext_append(t, "})();");
  d->ctext_append(t, "</script>");

  d->ctext_append(t, "</article>");

  d->free(path);

  load_global_data(d, lang_db_path); // For navbar
  char *full_html = render_page(d, current_lang, title, d->ctext_get_text(t));
  d->json_delete(data);
  d->ctext_free(t);
  d->free(lang_db_path);

  const appserverresponse *resp = d->send_text(full_html, "text/html", 200);
  d->free(full_html);
  return resp;
}
const appserverresponse *handle_author(appdeps *d,
                                       const appserverrequest *req) {
  char *lang_db_path = d->concat_path(global_config.database_path, current_lang);
  load_global_data(d, lang_db_path);
  const char *id = d->get_server_query_param(req, "id");
  if (!id) {
    d->free(lang_db_path);
    return d->send_text("Missing author id", "text/plain", 400);
  }

  appjson *author = load_author(d, lang_db_path, id);
  if (!author) {
    d->free(lang_db_path);
    return d->send_text("Author not found", "text/plain", 404);
  }

  const char *name =
      d->json_get_string_value(d->json_get_object_item(author, "name"));
  const char *desc =
      d->json_get_string_value(d->json_get_object_item(author, "description"));
  const char *pic =
      d->json_get_string_value(d->json_get_object_item(author, "picture"));

  appctext *t = d->new_ctext(app_null);

  d->ctext_append(t, "<div class='author-profile' style='text-align:center; "
                     "margin-bottom:4rem;'>");
  if (pic) {
    d->ctext_append(t, "<img src='/database_file?path=");
    d->ctext_append(t, current_lang);
    d->ctext_append(t, "/authors/");
    d->ctext_append(t, id);
    d->ctext_append(t, "/");
    d->ctext_append(t, pic);
    d->ctext_append(
        t, "' style='width:128px; height:128px; border-radius:50%; "
           "object-fit:cover; border:1px solid #1c1c1f; margin-bottom:1rem;'>");
  }
  d->ctext_append(t, "<h1>");
  d->ctext_append(t, name);
  d->ctext_append(t, "</h1>");
  d->ctext_append(t,
                  "<p style='color:#71717a; max-width:600px; margin:0 auto;'>");
  d->ctext_append(t, desc);
  d->ctext_append(t, "</p></div>");

  d->ctext_append(t, "<h2>");
  d->ctext_append(t, global_text.recent_articles_by_label);
  d->ctext_append(t, name);
  d->ctext_append(t, "</h2>");

  // Load articles by author
  appjson *articles = load_articles(d, lang_db_path, 1, 20, app_null, app_null, id);

  if (d->json_get_array_size(articles) == 0) {
    d->ctext_append(t, "<p>");
    d->ctext_append(t, global_text.no_author_articles_text);
    d->ctext_append(t, "</p>");
  } else {
    int count = d->json_get_array_size(articles);
    for (int i = 0; i < count; i++) {
      appjson *art = d->json_get_array_item(articles, i);
      const char *title =
          d->json_get_string_value(d->json_get_object_item(art, "title"));
      const char *date =
          d->json_get_string_value(d->json_get_object_item(art, "date"));
      const char *art_id =
          d->json_get_string_value(d->json_get_object_item(art, "id"));

      d->ctext_append(t, "<div class='card' style='padding:1rem;'>");
      d->ctext_append(t, "<h3><a href='/");
      d->ctext_append(t, current_lang);
      d->ctext_append(t, "/article?date=");
      d->ctext_append(t, date);
      d->ctext_append(t, "&id=");
      d->ctext_append(t, art_id);
      d->ctext_append(t, "'>");
      d->ctext_append(t, title);
      d->ctext_append(t, "</a></h3>");
      d->ctext_append(t, "<span style='color:#71717a; font-size:0.8rem;'>");
      d->ctext_append(t, date);
      d->ctext_append(t, "</span>");
      d->ctext_append(t, "</div>");
    }
  }
  d->json_delete(articles);
  d->json_delete(author);

  char *full_html = render_page(d, current_lang, name, d->ctext_get_text(t));
  d->ctext_free(t);
  d->free(lang_db_path);
  const appserverresponse *resp = d->send_text(full_html, "text/html", 200);
  d->free(full_html);
  return resp;
}

const appserverresponse *handle_about(appdeps *d, const appserverrequest *req) {
  char *lang_db_path = d->concat_path(global_config.database_path, current_lang);
  load_global_data(d, lang_db_path);
  char *path = d->concat_path(lang_db_path, "pages");
  char *about_path = d->concat_path(path, "about.html");
  d->free(path);

  char *content = app_null;
  if (d->file_exists(about_path)) {
    content = d->read_string(about_path);
  }
  d->free(about_path);

  char *full_html = render_page(
      d, current_lang, global_text.about_page_title,
      content ? content : global_text.about_fallback_content);
  if (content)
    d->free(content);
  d->free(lang_db_path);

  const appserverresponse *resp = d->send_text(full_html, "text/html", 200);
  d->free(full_html);
  return resp;
}
const appserverresponse *handle_database_file(appdeps *d,
                                              const appserverrequest *req) {
  const char *path = d->get_server_query_param(req, "path");
  if (!path) {
    return d->send_text("Missing path parameter", "text/plain", 400);
  }

  // Security check: path traversal
  if (!d->file_exists(path) && !d->dir_exists(path)) {
    // Basic check, realpath would be better but we rely on sandbox tools
    // For now, let's assume if it contains ".." it's bad
    if (d->strstr(path, "..")) {
      return d->send_text("Access denied", "text/plain", 403);
    }
  }

  char *full_path = d->concat_path(global_config.database_path, path);

  if (!d->file_exists(full_path)) {
    d->free(full_path);
    return d->send_text("File not found", "text/plain", 404);
  }

  const char *mime = get_mime_type(d, path);
  const appserverresponse *resp = d->send_file(full_path, mime, 200);
  d->free(full_path);
  return resp;
}

// Shared helper to render article list with pagination
const appserverresponse *
render_article_list_response(appdeps *d, const char *lang_db_path,
                             const char *title, const char *page_id, int page, int limit,
                             const char *category, const char *search) {

  // Cap limit just in case
  if (limit > 50)
    limit = 50;
  if (limit < 1)
    limit = 10;
  if (page < 1)
    page = 1;

  appjson *articles = load_articles(d, lang_db_path, page, limit, category, search, app_null);

  appctext *t = d->new_ctext(app_null);
  d->ctext_append(t, "<h1>");
  d->ctext_append(t, title);
  d->ctext_append(t, "</h1>");

  // Filter info
  if (category || search) {
    d->ctext_append(t, "<div class='filter-info'>");
    d->ctext_append(t, global_text.filter_by_label);
    if (category) {
      d->ctext_append(t, "<span class='badge'>");
      d->ctext_append(t, category);
      d->ctext_append(t, "</span> ");
    }
    if (search) {
      d->ctext_append(t, " \"");
      d->ctext_append(t, search);
      d->ctext_append(t, "\"");
    }
    d->ctext_append(t, " <a href='/");
    d->ctext_append(t, current_lang);
    d->ctext_append(t, "/list_articles' class='btn' style='padding:0.2rem "
           "0.5rem; margin-left:1rem; font-size:0.7rem'>");
    d->ctext_append(t, global_text.clear_filter_label);
    d->ctext_append(t, "</a></div><br>");
  }

  if (d->json_get_array_size(articles) == 0) {
    d->ctext_append(t, "<div class='card'><div class='card-title'>");
    d->ctext_append(t, global_text.no_articles_text);
    d->ctext_append(t, "</div></div>");
  } else {
    int count = d->json_get_array_size(articles);
    for (int i = 0; i < count; i++) {
      appjson *art = d->json_get_array_item(articles, i);
      const char *title_json =
          d->json_get_string_value(d->json_get_object_item(art, "title"));
      const char *summary =
          d->json_get_string_value(d->json_get_object_item(art, "summary"));
      const char *date =
          d->json_get_string_value(d->json_get_object_item(art, "date"));
      const char *id =
          d->json_get_string_value(d->json_get_object_item(art, "id"));

      const char *thumbnail =
          d->json_get_string_value(d->json_get_object_item(art, "thumbnail"));

      d->ctext_append(t, "<div class='card'>");
      if (thumbnail) {
        d->ctext_append(
            t,
            "<div class='card-image'><img src='/database_file?path=");
        d->ctext_append(t, current_lang);
        d->ctext_append(t, "/articles/");
        d->ctext_append(t, date);
        d->ctext_append(t, "/");
        d->ctext_append(t, id);
        d->ctext_append(t, "/");
        d->ctext_append(t, thumbnail);
        d->ctext_append(
            t, "' style='width:100%; height:200px; object-fit:cover;' alt='");
        d->ctext_append(t, title_json);
        d->ctext_append(t, "'></div>");
      } else {
        d->ctext_append(t, "<div class='card-image'></div>");
      }
      d->ctext_append(t, "<h2 class='card-title'><a href='/");
      d->ctext_append(t, current_lang);
      d->ctext_append(t, "/article?date=");
      d->ctext_append(t, date);
      d->ctext_append(t, "&id=");
      d->ctext_append(t, id);
      d->ctext_append(t, "'>");
      d->ctext_append(t, title_json);
      d->ctext_append(t, "</a></h2>");

      d->ctext_append(t, "<div class='card-meta'><span>");
      d->ctext_append(t, date);
      d->ctext_append(t, "</span></div>");

      d->ctext_append(t, "<div class='card-summary'>");
      d->ctext_append(t, summary);
      d->ctext_append(t, "</div>");

      d->ctext_append(t, "</div>");
    }
  }

  // Pagination Controls
  d->ctext_append(t, "<div class='pagination' style='display:flex; gap:1rem; "
                     "justify-content:center; margin-top:2rem;'>");
  if (page > 1) {
    d->ctext_append(t, "<a href='/");
    d->ctext_append(t, current_lang);
    d->ctext_append(t, "/list_articles?page=");
    char buf[10];
    d->custom_sprintf(buf, "%d", page - 1);
    d->ctext_append(t, buf);
    d->ctext_append(t, "&limit=");
    d->custom_sprintf(buf, "%d", limit);
    d->ctext_append(t, buf);
    if (category) {
      d->ctext_append(t, "&category=");
      d->ctext_append(t, category);
    }
    if (search) {
      d->ctext_append(t, "&search=");
      d->ctext_append(t, search);
    }
    d->ctext_append(t, "' class='btn'>");
    d->ctext_append(t, global_text.pagination_prev_label);
    d->ctext_append(t, "</a>");
  }

  // We don't know total/next without loading all, but load_articles pagination
  // slices it. Optimization: load_articles could return total count? For now,
  // simple "Next" if we invoked full limit
  if (d->json_get_array_size(articles) == limit) {
    d->ctext_append(t, "<a href='/");
    d->ctext_append(t, current_lang);
    d->ctext_append(t, "/list_articles?page=");
    char buf[10];
    d->custom_sprintf(buf, "%d", page + 1);
    d->ctext_append(t, buf);
    d->ctext_append(t, "&limit=");
    d->custom_sprintf(buf, "%d", limit);
    d->ctext_append(t, buf);
    if (category) {
      d->ctext_append(t, "&category=");
      d->ctext_append(t, category);
    }
    if (search) {
      d->ctext_append(t, "&search=");
      d->ctext_append(t, search);
    }
    d->ctext_append(t, "' class='btn'>");
    d->ctext_append(t, global_text.pagination_next_label);
    d->ctext_append(t, "</a>");
  }
  d->ctext_append(t, "</div>");

  d->json_delete(articles);

  // Client-side view tracking script
  char chunk_buf[16], size_buf[16];
  d->custom_sprintf(chunk_buf, "%d", page);
  d->custom_sprintf(size_buf, "%d", limit);
  d->ctext_append(t, "<script>");
  d->ctext_append(t, "(function(){");
  d->ctext_append(t, "var _vl_start=Date.now();");
  d->ctext_append(t, "var _vl_page='");
  d->ctext_append(t, page_id);
  d->ctext_append(t, "';");
  d->ctext_append(t, "var _vl_lang='");
  d->ctext_append(t, current_lang);
  d->ctext_append(t, "';");
  d->ctext_append(t, "var _vl_chunk=");
  d->ctext_append(t, chunk_buf);
  d->ctext_append(t, ";");
  d->ctext_append(t, "var _vl_size=");
  d->ctext_append(t, size_buf);
  d->ctext_append(t, ";");
  if (category) {
    d->ctext_append(t, "var _vl_cat='");
    d->ctext_append(t, category);
    d->ctext_append(t, "';");
  } else {
    d->ctext_append(t, "var _vl_cat=null;");
  }
  if (search) {
    d->ctext_append(t, "var _vl_search='");
    d->ctext_append(t, search);
    d->ctext_append(t, "';");
  } else {
    d->ctext_append(t, "var _vl_search=null;");
  }
  d->ctext_append(t, "var _vl_sent=false;");
  d->ctext_append(t, "function _vl_device(){");
  d->ctext_append(t, "var w=screen.width||window.innerWidth;");
  d->ctext_append(t, "if(w<768)return 'mobile';");
  d->ctext_append(t, "if(w<1024)return 'tablet';");
  d->ctext_append(t, "return 'desktop';}");
  d->ctext_append(t, "function _vl_country(){");
  d->ctext_append(t, "try{var tz=Intl.DateTimeFormat().resolvedOptions().timeZone;");
  d->ctext_append(t, "var m={");
  d->ctext_append(t, "'America/New_York':'US','America/Chicago':'US','America/Denver':'US','America/Los_Angeles':'US','America/Anchorage':'US','America/Phoenix':'US','America/Detroit':'US','America/Indiana':'US',");
  d->ctext_append(t, "'America/Sao_Paulo':'BR','America/Fortaleza':'BR','America/Bahia':'BR','America/Belem':'BR','America/Manaus':'BR','America/Recife':'BR','America/Cuiaba':'BR','America/Campo_Grande':'BR','America/Araguaina':'BR','America/Maceio':'BR',");
  d->ctext_append(t, "'America/Argentina/Buenos_Aires':'AR','America/Argentina/Cordoba':'AR','America/Argentina/Mendoza':'AR',");
  d->ctext_append(t, "'America/Santiago':'CL','America/Bogota':'CO','America/Lima':'PE','America/Caracas':'VE','America/Guayaquil':'EC',");
  d->ctext_append(t, "'America/Mexico_City':'MX','America/Cancun':'MX','America/Monterrey':'MX','America/Tijuana':'MX',");
  d->ctext_append(t, "'America/Toronto':'CA','America/Vancouver':'CA','America/Edmonton':'CA','America/Halifax':'CA','America/Winnipeg':'CA',");
  d->ctext_append(t, "'America/Montevideo':'UY','America/Asuncion':'PY','America/La_Paz':'BO','America/Havana':'CU','America/Panama':'PA','America/Costa_Rica':'CR','America/Guatemala':'GT',");
  d->ctext_append(t, "'Europe/London':'GB','Europe/Paris':'FR','Europe/Berlin':'DE','Europe/Madrid':'ES','Europe/Rome':'IT','Europe/Amsterdam':'NL','Europe/Brussels':'BE','Europe/Zurich':'CH','Europe/Vienna':'AT',");
  d->ctext_append(t, "'Europe/Lisbon':'PT','Europe/Warsaw':'PL','Europe/Prague':'CZ','Europe/Budapest':'HU','Europe/Bucharest':'RO','Europe/Sofia':'BG','Europe/Athens':'GR','Europe/Helsinki':'FI',");
  d->ctext_append(t, "'Europe/Stockholm':'SE','Europe/Oslo':'NO','Europe/Copenhagen':'DK','Europe/Dublin':'IE','Europe/Moscow':'RU','Europe/Kiev':'UA','Europe/Istanbul':'TR',");
  d->ctext_append(t, "'Asia/Tokyo':'JP','Asia/Shanghai':'CN','Asia/Chongqing':'CN','Asia/Hong_Kong':'HK','Asia/Seoul':'KR','Asia/Kolkata':'IN','Asia/Calcutta':'IN','Asia/Mumbai':'IN',");
  d->ctext_append(t, "'Asia/Singapore':'SG','Asia/Bangkok':'TH','Asia/Jakarta':'ID','Asia/Manila':'PH','Asia/Taipei':'TW','Asia/Dubai':'AE','Asia/Riyadh':'SA','Asia/Tehran':'IR','Asia/Karachi':'PK',");
  d->ctext_append(t, "'Asia/Dhaka':'BD','Asia/Colombo':'LK','Asia/Kuala_Lumpur':'MY','Asia/Ho_Chi_Minh':'VN','Asia/Saigon':'VN',");
  d->ctext_append(t, "'Africa/Cairo':'EG','Africa/Lagos':'NG','Africa/Johannesburg':'ZA','Africa/Nairobi':'KE','Africa/Casablanca':'MA','Africa/Algiers':'DZ','Africa/Tunis':'TN',");
  d->ctext_append(t, "'Australia/Sydney':'AU','Australia/Melbourne':'AU','Australia/Brisbane':'AU','Australia/Perth':'AU','Australia/Adelaide':'AU',");
  d->ctext_append(t, "'Pacific/Auckland':'NZ','Pacific/Fiji':'FJ','Pacific/Honolulu':'US'");
  d->ctext_append(t, "};");
  d->ctext_append(t, "return m[tz]||'unknown';");
  d->ctext_append(t, "}catch(e){return 'unknown';}}");
  d->ctext_append(t, "function _vl_send(){");
  d->ctext_append(t, "if(_vl_sent)return;");
  d->ctext_append(t, "_vl_sent=true;");
  d->ctext_append(t, "var dur=Math.round((Date.now()-_vl_start)/1000);");
  d->ctext_append(t, "var data=JSON.stringify({");
  d->ctext_append(t, "page:_vl_page,lang:_vl_lang,chunk:_vl_chunk,size:_vl_size,");
  d->ctext_append(t, "language:navigator.language||'unknown',");
  d->ctext_append(t, "device:_vl_device(),");
  d->ctext_append(t, "country:_vl_country(),");
  d->ctext_append(t, "duration:dur,");
  d->ctext_append(t, "category:_vl_cat,search:_vl_search});");
  d->ctext_append(t, "if(navigator.sendBeacon){");
  d->ctext_append(t, "navigator.sendBeacon('/api/record_page_view',new Blob([data],{type:'application/json'}));");
  d->ctext_append(t, "}else{");
  d->ctext_append(t, "var x=new XMLHttpRequest();");
  d->ctext_append(t, "x.open('POST','/api/record_page_view',false);");
  d->ctext_append(t, "x.setRequestHeader('Content-Type','application/json');");
  d->ctext_append(t, "x.send(data);}}");
  d->ctext_append(t, "document.addEventListener('visibilitychange',function(){if(document.visibilityState==='hidden')_vl_send();});");
  d->ctext_append(t, "window.addEventListener('beforeunload',_vl_send);");
  d->ctext_append(t, "})();");
  d->ctext_append(t, "</script>");

  char *full_html = render_page(d, current_lang, title, d->ctext_get_text(t));
  d->ctext_free(t);
  const appserverresponse *resp = d->send_text(full_html, "text/html", 200);
  d->free(full_html);
  return resp;
}

const appserverresponse *handle_home(appdeps *d, const appserverrequest *req) {
  char *lang_db_path = d->concat_path(global_config.database_path, current_lang);
  load_global_data(d, lang_db_path);
  // Home behaves like list_articles with default params (page=1, limit=10)
  const appserverresponse *resp = render_article_list_response(
      d, lang_db_path, global_text.home_page_title, "home", 1, 10, app_null, app_null);
  d->free(lang_db_path);
  return resp;
}

const appserverresponse *handle_list_articles(appdeps *d,
                                              const appserverrequest *req) {
  char *lang_db_path = d->concat_path(global_config.database_path, current_lang);
  load_global_data(d, lang_db_path);

  // Parse Params
  const char *page_str = d->get_server_query_param(req, "page");
  const char *limit_str = d->get_server_query_param(req, "limit");
  const char *category = d->get_server_query_param(req, "category");
  const char *search = d->get_server_query_param(req, "search");

  int page = 1;
  if (page_str)
    page = d->atoi(page_str);
  if (page < 1)
    page = 1;

  int limit = 10;
  if (limit_str)
    limit = d->atoi(limit_str);
  if (limit < 1)
    limit = 10;
  if (limit > 50)
    limit = 50;

  const appserverresponse *resp = render_article_list_response(
      d, lang_db_path, global_text.articles_page_title, "listings", page, limit, category, search);
  d->free(lang_db_path);
  return resp;
}

// =======================MANAGEMENT API========================================
appbool check_auth(appdeps *d, const appserverrequest *req) {
  const char *pass = d->get_server_header(req, "root-password");
  if (pass && global_config.root_password &&
      d->strcmp(pass, global_config.root_password) == 0) {
    return app_true;
  }
  return app_false;
}

const appserverresponse *handle_api_write_file(appdeps *d,
                                               const appserverrequest *req) {
  if (!check_auth(d, req))
    return d->send_text("Unauthorized: Invalid root_password", "text/plain",
                        401);

  const char *path = d->get_server_header(req, "path");
  if (!path)
    return d->send_text("Missing path header", "text/plain", 400);

  if (!is_safe_path(d, path))
    return d->send_text("Invalid path", "text/plain", 403);

  long body_size = 0;
  const unsigned char *body =
      d->read_server_body(req, 1024 * 1024 * 10, &body_size); // 10MB Limit

  char *full_path = d->concat_path(global_config.database_path, path);
  d->write_any(full_path, body, body_size);
  d->free(full_path);

  return d->send_text("OK", "text/plain", 200);
}

const appserverresponse *handle_api_read_file(appdeps *d,
                                              const appserverrequest *req) {
  if (!check_auth(d, req))
    return d->send_text("Unauthorized: Invalid root_password", "text/plain",
                        401);

  const char *path = d->get_server_header(req, "path");
  if (!path)
    return d->send_text("Missing path header", "text/plain", 400);

  if (!is_safe_path(d, path))
    return d->send_text("Invalid path", "text/plain", 403);

  char *full_path = d->concat_path(global_config.database_path, path);
  if (!d->file_exists(full_path)) {
    d->free(full_path);
    return d->send_text("File not found", "text/plain", 404);
  }

  const char *mime = get_mime_type(d, path);
  const appserverresponse *resp = d->send_file(full_path, mime, 200);
  d->free(full_path);
  return resp;
}

// Helper to clean up empty directories after file deletion
void cleanup_empty_parents(appdeps *d, const char *deleted_file_path,
                           const char *root_path) {
  char *current_dir = d->strdup(deleted_file_path);

  // Start with the parent directory of the file
  int len = d->strlen(current_dir);
  for (int i = len - 1; i >= 0; i--) {
    if (current_dir[i] == '/') {
      current_dir[i] = 0; // Truncate to parent
      break;
    }
  }

  while (1) {
    // Stop if we reached root or gone outside
    if (d->strlen(current_dir) <= d->strlen(root_path))
      break;
    if (d->strncmp(current_dir, root_path, d->strlen(root_path)) != 0)
      break;

    // Check if directory is empty
    appstringarray *files = d->list_files_recursively(current_dir);
    long count = 0;
    if (files) {
      count = d->get_stringarray_size(files);
      d->delete_stringarray(files);
    }

    if (count == 0) {
      // Attempt delete
      d->delete_any(current_dir);

      // Verify if it's gone
      if (d->dir_exists(current_dir)) {
        // Still exists, maybe not empty (hidden files?) or permission issue
        break;
      }
    } else {
      // Not empty
      break;
    }

    // Move to parent
    len = d->strlen(current_dir);
    int found_slash = 0;
    for (int i = len - 1; i >= 0; i--) {
      if (current_dir[i] == '/') {
        current_dir[i] = 0;
        found_slash = 1;
        break;
      }
    }
    if (!found_slash)
      break;
  }

  d->free(current_dir);
}

const appserverresponse *handle_api_delete_file(appdeps *d,
                                                const appserverrequest *req) {
  if (!check_auth(d, req))
    return d->send_text("Unauthorized: Invalid root_password", "text/plain",
                        401);

  const char *path = d->get_server_header(req, "path");
  if (!path)
    return d->send_text("Missing path header", "text/plain", 400);
  if (!is_safe_path(d, path))
    return d->send_text("Invalid path", "text/plain", 403);

  char *full_path = d->concat_path(global_config.database_path, path);
  d->delete_any(full_path);
  cleanup_empty_parents(d, full_path,
                        global_config.database_path); // Cleanup dirs
  d->free(full_path);

  return d->send_text("OK", "text/plain", 200);
}

const appserverresponse *handle_api_list_files(appdeps *d,
                                               const appserverrequest *req) {
  if (!check_auth(d, req))
    return d->send_text("Unauthorized: Invalid root_password", "text/plain",
                        401);

  const char *rel_path = d->get_server_header(req, "path");
  char *target_dir = app_null;
  if (rel_path) {
    if (!is_safe_path(d, rel_path))
      return d->send_text("Invalid path", "text/plain", 403);
    target_dir = d->concat_path(global_config.database_path, rel_path);
  } else {
    target_dir = d->strdup(global_config.database_path);
  }

  appstringarray *files = d->list_files_recursively(target_dir);

  appjson *arr = d->json_create_array();
  if (files) {
    long count = d->get_stringarray_size(files);
    for (int i = 0; i < count; i++) {
      const char *f = d->get_stringarray_item(files, i);
      appjson *obj = d->json_create_object();
      d->json_add_string_to_object(obj, "file", f);

      // Calc SHA
      char *fp = d->concat_path(target_dir, f);
      long fsize = 0;
      appbool is_bin = app_false;
      const unsigned char *fc = d->read_any(fp, &fsize, &is_bin);
      if (fc) {
        char *sha = d->get_sha256(fc, fsize);
        d->json_add_string_to_object(obj, "sha", sha);
        d->json_free_string(sha);
        d->free((void *)fc);
      }
      d->free(fp);

      d->json_add_item_to_array(arr, obj);
    }
    d->delete_stringarray(files);
  }
  d->free(target_dir);

  const appserverresponse *resp = d->send_json(arr, 200);
  d->json_delete(arr);
  return resp;
}

const appserverresponse *handle_favicon(appdeps *d,
                                        const appserverrequest *req) {
  const char *candidates[] = {"en/config/favicon.ico", "en/config/favicon.png",
                               "en/config/favicon.svg",
                               app_null};
  for (int i = 0; candidates[i] != app_null; i++) {
    char *full_path =
        d->concat_path(global_config.database_path, candidates[i]);
    if (d->file_exists(full_path)) {
      const char *mime = get_mime_type(d, candidates[i]);
      const appserverresponse *resp = d->send_file(full_path, mime, 200);
      d->free(full_path);
      return resp;
    }
    d->free(full_path);
  }
  return d->send_text("Not Found", "text/plain", 404);
}

const appserverresponse *router(appdeps *d, void *props) {
  const char *route = d->get_server_route(d->appserverrequest);
  d->printf("Route: %s\n", route);
  const char *method = d->get_server_method(d->appserverrequest);

  // === Root redirect: GET / -> 302 /en/ ===
  if (d->strcmp(route, "/") == 0 && d->strcmp(method, "GET") == 0) {
    const appserverresponse *resp = d->newappserverresponse();
    d->setappserverresponse_status_code((appserverresponse *)resp, 302);
    d->setappserverresponse_header((appserverresponse *)resp, "Location", "/en/");
    d->setappserverresponse_content((appserverresponse *)resp,
                                    (const unsigned char *)"Redirecting...", 14);
    return resp;
  }

  // === Non-lang utility routes ===
  if (d->strcmp(route, "/favicon.ico") == 0 &&
      d->strcmp(method, "GET") == 0) {
    return handle_favicon(d, d->appserverrequest);
  }

  if (d->strcmp(route, "/database_file") == 0 &&
      d->strcmp(method, "GET") == 0) {
    return handle_database_file(d, d->appserverrequest);
  }

  if (d->strcmp(route, "/api/changelog") == 0 &&
      d->strcmp(method, "GET") == 0) {
    long asset_size = 0;
    appbool is_binary = app_false;
    const unsigned char *meta_content =
        d->get_asset_content("meta.json", &asset_size, &is_binary);
    if (meta_content) {
      return d->send_any(meta_content, asset_size, "application/json", 200);
    }
    return d->send_text("{}", "application/json", 200);
  }

  // === Public API routes (no auth) ===
  if (d->strcmp(route, "/api/record_view") == 0 &&
      d->strcmp(method, "POST") == 0) {
    return handle_api_record_view(d, d->appserverrequest);
  }

  if (d->strcmp(route, "/api/record_page_view") == 0 &&
      d->strcmp(method, "POST") == 0) {
    return handle_api_record_page_view(d, d->appserverrequest);
  }

  // === API routes (no lang prefix) ===
  if (d->strncmp(route, "/api/", 5) == 0 && d->strcmp(method, "POST") == 0) {
    if (d->strcmp(route, "/api/write_database_file") == 0)
      return handle_api_write_file(d, d->appserverrequest);
    if (d->strcmp(route, "/api/read_database_file") == 0)
      return handle_api_read_file(d, d->appserverrequest);
    if (d->strcmp(route, "/api/delete_database_file") == 0)
      return handle_api_delete_file(d, d->appserverrequest);
    if (d->strcmp(route, "/api/list_database_files_recursively") == 0)
      return handle_api_list_files(d, d->appserverrequest);
  }

  // === Lang-prefixed routes: /<lang>/... ===
  if (d->strcmp(method, "GET") == 0 && d->strlen(route) > 1 && route[0] == '/') {
    // Extract lang: everything between first '/' and second '/'
    const char *start = route + 1; // skip leading '/'
    const char *slash2 = d->strstr(start, "/");

    // Allocate lang string
    char lang[64];
    d->custom_memset(lang, 0, 64);
    const char *sub_route = "/"; // default sub_route

    if (slash2) {
      int lang_len = (int)(slash2 - start);
      if (lang_len > 0 && lang_len < 63) {
        d->custom_memcpy(lang, start, lang_len);
        lang[lang_len] = '\0';
        sub_route = slash2; // e.g. "/article?..."
      }
    } else {
      // No second slash: route is "/<lang>" without trailing slash
      int lang_len = d->strlen(start);
      if (lang_len > 0 && lang_len < 63) {
        d->custom_memcpy(lang, start, lang_len);
        lang[lang_len] = '\0';
        sub_route = "/";
      }
    }

    // Validate lang: must not be empty and must not contain '/'
    if (d->strlen(lang) > 0 && !d->strstr(lang, "/")) {
      // Set current_lang for handlers
      current_lang = d->strdup(lang);

      // If database/<lang> dir does not exist, fallback to "en"
      {
        char *lang_check_path = d->concat_path(global_config.database_path, current_lang);
        if (!d->dir_exists(lang_check_path)) {
          d->free(current_lang);
          current_lang = d->strdup("en");
        }
        d->free(lang_check_path);
      }

      // Invalidate cache per request (so lang switch works correctly)
      if (cached_categories) {
        d->json_delete(cached_categories);
        cached_categories = app_null;
      }
      if (cached_text_config) {
        d->json_delete(cached_text_config);
        cached_text_config = app_null;
      }

      const appserverresponse *result = app_null;

      // Dispatch based on sub_route
      if (d->strcmp(sub_route, "/") == 0) {
        result = handle_home(d, d->appserverrequest);
      } else if (d->strcmp(sub_route, "/list_articles") == 0 ||
                 d->strncmp(sub_route, "/list_articles?", 15) == 0) {
        result = handle_list_articles(d, d->appserverrequest);
      } else if (d->strcmp(sub_route, "/article") == 0 ||
                 d->strncmp(sub_route, "/article?", 9) == 0) {
        result = handle_article(d, d->appserverrequest);
      } else if (d->strcmp(sub_route, "/author") == 0 ||
                 d->strncmp(sub_route, "/author?", 8) == 0) {
        result = handle_author(d, d->appserverrequest);
      } else if (d->strcmp(sub_route, "/about") == 0) {
        result = handle_about(d, d->appserverrequest);
      }

      d->free(current_lang);
      current_lang = app_null;

      if (result) return result;
    }
  }

  return d->send_text("Not Found", "text/plain", 404);
}

// ===============================SYNC LOGIC====================================

// Fetch remote file list recursively
appjson *fetch_remote_file_list(appdeps *d, const char *url_base,
                                const char *pass, const char *sub_path) {
  // Construct URL: url_base + /api/list_database_files_recursively
  // url_base might fail if it doesn't end with / or if it has query params
  // simple concat for now
  char *full_url =
      d->concat_path(url_base, "api/list_database_files_recursively");
  // concat_path might use system separator, ensure / for URL
  // Better use manual concat.
  d->free(full_url);

  int len = d->strlen(url_base) +
            d->strlen("api/list_database_files_recursively") + 2;
  full_url = d->malloc(len);
  d->custom_memset(full_url, 0, len);
  d->custom_strcpy(full_url, url_base);
  if (d->strlen(full_url) > 0 && full_url[d->strlen(full_url) - 1] != '/') {
    d->custom_strcat(full_url, "/");
  }
  d->custom_strcat(full_url, "api/list_database_files_recursively");

  appclientrequest *req = d->newappclientrequest(full_url);
  d->appclientrequest_set_method(req, "POST"); // API says POST
  d->appclientrequest_set_header(req, "root-password", pass);

  if (sub_path && d->strlen(sub_path) > 0) {
    d->appclientrequest_set_header(req, "path", sub_path);
  }

  appclientresponse *resp = d->appclientrequest_fetch(req);
  appjson *result = app_null;

  if (resp) {
    int status = d->appclientresponse_get_status_code(resp);
    if (status == 200) {
      long rsize = 0;
      const unsigned char *rbody = d->appclientresponse_read_body(resp, &rsize);
      if (rbody) {
        char *rstr = d->malloc(rsize + 1);
        d->custom_memcpy(rstr, rbody, rsize);
        rstr[rsize] = 0;
        result = d->json_parse(rstr);
        d->free(rstr);
      }
    } else if (status == 401) {
      d->printf(
          "Error: Authentication failed. Please check your --root-password.\n");
    } else if (status == 403) {
      d->printf("Error: Access denied (403).\n");
    } else if (status == 404) {
      d->printf("Error: Remote endpoint not found (404). Check your --url.\n");
    } else {
      d->printf("Error: Server returned status %d.\n", status);
    }
    d->free_clientresponse(resp);
  } else {
    d->printf("Error: Could not connect to remote server at %s. Check your "
              "--url or network connection.\n",
              full_url);
  }

  d->appclientrequest_free(req);
  d->free(full_url);
  return result;
}

// Get local file list with SHAs
// Get local file list with SHAs
appjson *get_local_file_list(appdeps *d, const char *base_path,
                             const char *cache_dir, const char *sub_path) {
  char *target_path = d->strdup(base_path);
  if (sub_path && d->strlen(sub_path) > 0) {
    char *tmp = d->concat_path(base_path, sub_path);
    d->free(target_path);
    target_path = tmp;
  }

  appstringarray *files = d->list_files_recursively(target_path);
  appjson *arr = d->json_create_array();

  if (!files) {
    d->free(target_path);
    return arr;
  }

  long count = d->get_stringarray_size(files);
  for (int i = 0; i < count; i++) {
    const char *f = d->get_stringarray_item(files, i);
    appjson *obj = d->json_create_object();
    d->json_add_string_to_object(obj, "file", f);

    // Calc SHA using cache
    char *full_path = d->concat_path(target_path, f);

    if (d->strstr(f, ".vibelog_cache")) {
      d->free(full_path);
      d->json_delete(obj);
      continue;
    }

    if (!d->dir_exists(cache_dir)) {
      d->create_dir(cache_dir);
    }

    char *sha = d->get_cached_file_sha(cache_dir, full_path);
    if (sha) {
      d->json_add_string_to_object(obj, "sha", sha);
      d->json_free_string(sha);
    }

    d->json_add_item_to_array(arr, obj);
    d->free(full_path);
  }
  d->delete_stringarray(files);
  d->free(target_path);
  return arr;
}

// Find file object in json array by path
appjson *find_file_obj(appdeps *d, appjson *arr, const char *filepath) {
  if (!arr || !d->json_is_array(arr))
    return app_null;
  int count = d->json_get_array_size(arr);
  for (int i = 0; i < count; i++) {
    appjson *item = d->json_get_array_item(arr, i);
    const char *f =
        d->json_get_string_value(d->json_get_object_item(item, "file"));
    if (f && d->strcmp(f, filepath) == 0) {
      return item;
    }
  }
  return app_null;
}

// DOWNLOAD SYNC
// DOWNLOAD SYNC
void perform_download_sync(appdeps *d, const char *local_path,
                           const char *url_base, const char *pass,
                           const char *cache_dir, const char *sub_path) {
  d->printf("Fetching remote file list...\n");
  appjson *remote_list = fetch_remote_file_list(d, url_base, pass, sub_path);
  if (!remote_list) {
    d->printf("Failed to fetch remote list.\n");
    return;
  }

  d->printf("Scanning local files...\n");
  appjson *local_list = get_local_file_list(d, local_path, cache_dir, sub_path);

  int count = d->json_get_array_size(remote_list);
  d->printf("Found %d remote files. Synchronizing...\n", count);

  // Determine local target directory for ops
  char *target_dir = d->strdup(local_path);
  if (sub_path && d->strlen(sub_path) > 0) {
    char *tmp = d->concat_path(local_path, sub_path);
    d->free(target_dir);
    target_dir = tmp;
  }

  int downloaded = 0;
  int skipped = 0;

  for (int i = 0; i < count; i++) {
    appjson *r_item = d->json_get_array_item(remote_list, i);
    const char *f =
        d->json_get_string_value(d->json_get_object_item(r_item, "file"));
    const char *r_sha =
        d->json_get_string_value(d->json_get_object_item(r_item, "sha"));

    // Check local
    appjson *l_item = find_file_obj(d, local_list, f);
    appbool need_download = app_true;

    if (l_item) {
      const char *l_sha =
          d->json_get_string_value(d->json_get_object_item(l_item, "sha"));
      if (l_sha && r_sha && d->strcmp(l_sha, r_sha) == 0) {
        need_download = app_false;
      }
    }

    if (need_download) {
      d->printf("Downloading %s...\n", f);

      // Prepare download URL
      // POST /api/read_database_file with header path=f (relative to DB root)
      int len = d->strlen(url_base) + d->strlen("api/read_database_file") + 2;
      char *d_url = d->malloc(len);
      d->custom_memset(d_url, 0, len);
      d->custom_strcpy(d_url, url_base);
      if (d->strlen(d_url) > 0 && d_url[d->strlen(d_url) - 1] != '/') {
        d->custom_strcat(d_url, "/");
      }
      d->custom_strcat(d_url, "api/read_database_file");

      appclientrequest *req = d->newappclientrequest(d_url);
      d->appclientrequest_set_method(req, "POST");
      d->appclientrequest_set_header(req, "root-password", pass);

      // Calculate effective remote path
      if (sub_path && d->strlen(sub_path) > 0) {
        char *eff_path = d->concat_path(sub_path, f);
        d->appclientrequest_set_header(req, "path", eff_path);
        d->free(eff_path);
      } else {
        d->appclientrequest_set_header(req, "path", f);
      }

      appclientresponse *resp = d->appclientrequest_fetch(req);
      if (resp) {
        int status = d->appclientresponse_get_status_code(resp);
        if (status == 200) {
          long rsize = 0;
          const unsigned char *rbody =
              d->appclientresponse_read_body(resp, &rsize);
          if (rbody) { // Check if we actually got content
            char *save_path = d->concat_path(target_dir, f);
            d->write_any(save_path, rbody, rsize);
            d->free(save_path);
            downloaded++;
          } else {
            d->printf("Empty response for %s\n", f);
          }
        } else {
          d->printf(
              "Error: Failed to download %s. Server returned status %d.\n", f,
              status);
        }
        d->free_clientresponse(resp);
      } else {
        d->printf("Error: Failed connection for %s\n", f);
      }
      d->appclientrequest_free(req);
      d->free(d_url);

    } else {
      skipped++;
    }
  }

  // DELETION LOGIC (Download Algorithm: Local Delete)
  int deleted = 0;
  for (int i = 0; i < d->json_get_array_size(local_list); i++) {
    appjson *l_item = d->json_get_array_item(local_list, i);
    const char *f =
        d->json_get_string_value(d->json_get_object_item(l_item, "file"));

    if (d->strstr(f, ".vibelog_cache") || d->strstr(f, ".DS_Store")) {
      continue;
    }

    appjson *r_item = find_file_obj(d, remote_list, f);
    if (!r_item) {
      // File exists locally but not remotely -> Delete it
      d->printf("Deleting local file %s (not on server)...\n", f);
      char *full_path = d->concat_path(target_dir, f);
      d->delete_any(full_path);
      cleanup_empty_parents(d, full_path, target_dir); // Cleanup dirs
      d->free(full_path);
      deleted++;
    }
  }

  d->printf("Sync Complete. Downloaded: %d, Skipped: %d, Deleted: %d\n",
            downloaded, skipped, deleted);
  d->json_delete(remote_list);
  d->json_delete(local_list);
  d->free(target_dir);
}

// UPLOAD SYNC
// UPLOAD SYNC
void perform_upload_sync(appdeps *d, const char *local_path,
                         const char *url_base, const char *pass,
                         const char *cache_dir, const char *sub_path) {
  d->printf("Fetching remote file list...\n");
  appjson *remote_list = fetch_remote_file_list(d, url_base, pass, sub_path);
  if (!remote_list) {
    d->printf("Failed to fetch remote list.\n");
    return;
  }

  d->printf("Scanning local files...\n");
  appjson *local_list = get_local_file_list(d, local_path, cache_dir, sub_path);

  int count = d->json_get_array_size(local_list);
  d->printf("Found %d local files. Synchronizing...\n", count);

  char *target_dir = d->strdup(local_path);
  if (sub_path && d->strlen(sub_path) > 0) {
    char *tmp = d->concat_path(local_path, sub_path);
    d->free(target_dir);
    target_dir = tmp;
  }

  int uploaded = 0;
  int skipped = 0;

  for (int i = 0; i < count; i++) {
    appjson *l_item = d->json_get_array_item(local_list, i);
    const char *f =
        d->json_get_string_value(d->json_get_object_item(l_item, "file"));
    const char *l_sha =
        d->json_get_string_value(d->json_get_object_item(l_item, "sha"));

    // Skip hidden files or cache
    if (d->strstr(f, ".vibelog_cache") || d->strstr(f, ".DS_Store")) {
      continue;
    }

    // Check remote
    appjson *r_item = find_file_obj(d, remote_list, f);
    appbool need_upload = app_true;

    if (r_item) {
      const char *r_sha =
          d->json_get_string_value(d->json_get_object_item(r_item, "sha"));
      if (l_sha && r_sha && d->strcmp(l_sha, r_sha) == 0) {
        need_upload = app_false;
      }
    }

    if (need_upload) {
      d->printf("Uploading %s...\n", f);

      // Prepare upload URL
      // POST /api/write_database_file
      int len = d->strlen(url_base) + d->strlen("api/write_database_file") + 2;
      char *u_url = d->malloc(len);
      d->custom_memset(u_url, 0, len);
      d->custom_strcpy(u_url, url_base);
      if (d->strlen(u_url) > 0 && u_url[d->strlen(u_url) - 1] != '/') {
        d->custom_strcat(u_url, "/");
      }
      d->custom_strcat(u_url, "api/write_database_file");

      // Read local file
      char *full_path = d->concat_path(target_dir, f);
      long fsize = 0;
      appbool is_bin = app_false;
      const unsigned char *content = d->read_any(full_path, &fsize, &is_bin);

      if (content) {
        appclientrequest *req = d->newappclientrequest(u_url);
        d->appclientrequest_set_method(req, "POST");
        d->appclientrequest_set_header(req, "root-password", pass);

        // Calculate effective remote path
        if (sub_path && d->strlen(sub_path) > 0) {
          char *eff_path = d->concat_path(sub_path, f);
          d->appclientrequest_set_header(req, "path", eff_path);
          d->free(eff_path);
        } else {
          d->appclientrequest_set_header(req, "path", f);
        }

        d->appclientrequest_set_body(req, (unsigned char *)content, fsize);

        appclientresponse *resp = d->appclientrequest_fetch(req);
        if (resp) {
          int status = d->appclientresponse_get_status_code(resp);
          if (status == 200) {
            // assume success if response
            uploaded++;
          } else {
            d->printf(
                "Error: Failed to upload %s. Server returned status %d.\n", f,
                status);
          }
          d->free_clientresponse(resp);
        } else {
          d->printf("Error: Failed connection for upload %s\n", f);
        }
        d->appclientrequest_free(req);
        d->free((void *)content); // cast to void* for free
      }
      d->free(full_path);
      d->free(u_url);

    } else {
      skipped++;
    }
  }

  // DELETION LOGIC (Upload Algorithm: Remote Delete)
  int deleted = 0;
  for (int i = 0; i < d->json_get_array_size(remote_list); i++) {
    appjson *r_item = d->json_get_array_item(remote_list, i);
    const char *f =
        d->json_get_string_value(d->json_get_object_item(r_item, "file"));

    // Skip special/hidden files if they appear in valid lists
    if (d->strstr(f, ".vibelog_cache") || d->strstr(f, ".DS_Store")) {
      continue;
    }

    appjson *l_item = find_file_obj(d, local_list, f);
    if (!l_item) {
      // File exists remotely but not locally -> Delete it from server
      d->printf("Deleting remote file %s (not on local)...\n", f);

      // Prepare delete URL
      // POST /api/delete_database_file
      int len = d->strlen(url_base) + d->strlen("api/delete_database_file") + 2;
      char *del_url = d->malloc(len);
      d->custom_memset(del_url, 0, len);
      d->custom_strcpy(del_url, url_base);
      if (d->strlen(del_url) > 0 && del_url[d->strlen(del_url) - 1] != '/') {
        d->custom_strcat(del_url, "/");
      }
      d->custom_strcat(del_url, "api/delete_database_file");

      appclientrequest *req = d->newappclientrequest(del_url);
      d->appclientrequest_set_method(req, "POST");
      d->appclientrequest_set_header(req, "root-password", pass);

      // Calculate effective remote path
      if (sub_path && d->strlen(sub_path) > 0) {
        char *eff_path = d->concat_path(sub_path, f);
        d->appclientrequest_set_header(req, "path", eff_path);
        d->free(eff_path);
      } else {
        d->appclientrequest_set_header(req, "path", f);
      }

      appclientresponse *resp = d->appclientrequest_fetch(req);
      if (resp) {
        int status = d->appclientresponse_get_status_code(resp);
        if (status == 200) {
          deleted++;
        } else {
          d->printf("Error: Failed to delete remote file %s. Status: %d\n", f,
                    status);
        }
        d->free_clientresponse(resp);
      } else {
        d->printf("Error: Failed connection for delete %s\n", f);
      }
      d->appclientrequest_free(req);
      d->free(del_url);
    }
  }

  d->printf("Sync Complete. Uploaded: %d, Skipped: %d, Deleted (Remote): %d\n",
            uploaded, skipped, deleted);
  d->json_delete(remote_list);
  d->json_delete(local_list);
  d->free(target_dir);
}

// ===============================MAIN==========================================
// ===============================MAIN==========================================
int appmain(appdeps *d) {
  // Common Flags
  const char *PASS_FLAGS[] = {"root-password", "pass"};
  const char *URL_FLAGS[] = {"url", "u"};
  const char *PATH_FLAGS[] = {"path", "f"};
  const char *CACHE_FLAGS[] = {"cache-dir", "c"};

  // Server Flags
  const char *PORT_FLAGS[] = {"port", "p"};
  const char *DB_FLAGS[] = {"database-path", "db"};

  int argc = d->get_arg_count(d->argv);
  const char *command = app_null;

  if (argc > 1) {
    const char *arg1 = d->get_arg_value(d->argv, 1);
    if (arg1 && d->strlen(arg1) > 0 && arg1[0] != '-') {
      command = arg1;
    }
  }

  // VERSION: --version flag or version command
  {
    const char *VERSION_FLAGS[] = {"version"};
    appbool is_version_flag = d->has_arg_flag(d->argv, VERSION_FLAGS, 1);
    if (is_version_flag || (command && d->strcmp(command, "version") == 0)) {
      long asset_size = 0;
      appbool is_binary = app_false;
      const unsigned char *meta_content =
          d->get_asset_content("meta.json", &asset_size, &is_binary);
      if (meta_content) {
        char *meta_str = d->malloc(asset_size + 1);
        d->custom_memcpy(meta_str, meta_content, asset_size);
        meta_str[asset_size] = 0;
        appjson *meta_json = d->json_parse(meta_str);
        d->free(meta_str);
        if (meta_json) {
          appjson *version_item =
              d->json_get_object_item(meta_json, "version");
          if (version_item) {
            char *version_str = d->json_get_string_value(version_item);
            d->printf("VibeLog %s\n", version_str);
          }
          d->json_delete(meta_json);
        }
      }
      return 0;
    }
  }

  // Validate Command
  if (!command) {
    d->printf("Usage: vibelog <command> [options]\n");
    d->printf("Commands:\n");
    d->printf("  start              Start the server\n");
    d->printf("  upload-articles    Upload articles to remote\n");
    d->printf("  download-articles  Download articles from remote\n");
    d->printf("  upload-authors     Upload authors to remote\n");
    d->printf("  download-authors   Download authors from remote\n");
    d->printf("  upload-metrics     Upload metrics to remote\n");
    d->printf("  download-metrics   Download metrics from remote\n");
    d->printf(
        "  upload-config      Upload config (and about.html) to remote\n");
    d->printf("  download-config    Download config from remote\n");
    return 1;
  }

  // Common Argument Parsing for Sync
  const char *db_path = d->get_arg_flag_value(
      d->argv, DB_FLAGS, sizeof(DB_FLAGS) / sizeof(DB_FLAGS[0]), 0);

  // Default db_path if not provided
  char *eff_db_path = app_null;
  if (db_path) {
    eff_db_path = d->strdup(db_path);
  } else {
    eff_db_path = d->strdup("database");
  }

  const char *url_base = d->get_arg_flag_value(
      d->argv, URL_FLAGS, sizeof(URL_FLAGS) / sizeof(URL_FLAGS[0]), 0);
  const char *pass = d->get_arg_flag_value(
      d->argv, PASS_FLAGS, sizeof(PASS_FLAGS) / sizeof(PASS_FLAGS[0]), 0);
  const char *cache_val = d->get_arg_flag_value(
      d->argv, CACHE_FLAGS, sizeof(CACHE_FLAGS) / sizeof(CACHE_FLAGS[0]), 0);

  char *eff_cache_dir = app_null;
  if (cache_val) {
    eff_cache_dir = d->strdup(cache_val);
  } else {
    eff_cache_dir = d->strdup(".vibelog_cache");
  }

  // COMMAND: START
  if (d->strcmp(command, "start") == 0) {
    // Parse Port
    const char *start_port = d->get_arg_flag_value(
        d->argv, PORT_FLAGS, sizeof(PORT_FLAGS) / sizeof(PORT_FLAGS[0]), 0);
    global_config.port = 8080;
    if (start_port) {
      global_config.port = d->atoi(start_port);
    }

    // DB Path is already parsed into eff_db_path
    global_config.database_path = eff_db_path;

    // Cache dir
    global_config.cache_dir = eff_cache_dir;

    // Parse Root Password
    if (pass) {
      global_config.root_password = d->strdup(pass);
    } else {
      d->printf("Error: --root-password is required for start command.\n");
      d->free(eff_db_path);
      d->free(eff_cache_dir);
      return 1;
    }

    // Parse Max View
    const char *MAX_VIEW_FLAGS[] = {"max-view"};
    const char *max_view_val = d->get_arg_flag_value(
        d->argv, MAX_VIEW_FLAGS, 1, 0);
    if (max_view_val) {
      global_config.max_view = d->atoi(max_view_val);
      if (global_config.max_view <= 0) {
        d->printf("Error: --max-view must be a positive integer.\n");
        d->free(eff_db_path);
        d->free(eff_cache_dir);
        d->free((void *)global_config.root_password);
        return 1;
      }
    } else {
      d->printf("Error: --max-view is required for start command.\n");
      d->free(eff_db_path);
      d->free(eff_cache_dir);
      d->free((void *)global_config.root_password);
      return 1;
    }

    // Parse Markdown Converter Command
    const char *MARKDOWN_FLAGS[] = {"markdown-converter-command"};
    const char *md_cmd = d->get_arg_flag_value(
        d->argv, MARKDOWN_FLAGS, 1, 0);
    if (md_cmd) {
      global_config.markdown_converter_command = d->strdup(md_cmd);
      d->printf("Markdown converter: %s\n",
                global_config.markdown_converter_command);
    }

    d->printf("Starting VibeLog on port %d\n", global_config.port);
    d->printf("Max view records per article/page: %d\n", global_config.max_view);
    d->printf("Database path: %s\n", global_config.database_path);

    d->start_server(global_config.port, router, app_null, app_false);

    // Cleanup (unreachable)
    d->free((void *)global_config.database_path);
    d->free((void *)global_config.root_password);
    d->free((void *)global_config.cache_dir);
    if (global_config.markdown_converter_command)
      d->free((void *)global_config.markdown_converter_command);
    return 0;
  }

  // SYNC COMMANDS WRAPPERS
  if (d->strstr(command, "upload-") == command ||
      d->strstr(command, "download-") == command) {
    if (!url_base || !pass) {
      d->printf(
          "Error: --url and --root-password are required for sync commands.\n");
      d->free(eff_db_path);
      d->free(eff_cache_dir);
      return 1;
    }

    if (!d->dir_exists(eff_db_path)) {
      // For download we might create it, but for upload it must exist
      if (d->strstr(command, "download-") == command) {
        d->create_dir(eff_db_path);
      } else {
        d->printf("Error: Database directory not found: %s\n", eff_db_path);
        d->free(eff_db_path);
        d->free(eff_cache_dir);
        return 1;
      }
    }

    // Extract lang from url_base: e.g. "http://host/en" → lang="en", clean_url="http://host"
    char *clean_url = d->strdup(url_base);
    char sync_lang[64];
    d->custom_memset(sync_lang, 0, 64);

    // Find the last '/' in the URL after "://"
    const char *proto_end = d->strstr(clean_url, "://");
    if (proto_end) {
      char *search_start = (char *)(proto_end + 3); // skip "://"
      char *last_slash = app_null;
      for (char *p = search_start; *p; p++) {
        if (*p == '/') last_slash = p;
      }
      if (last_slash && last_slash > search_start) {
        // Extract lang from last path segment
        const char *lang_start = last_slash + 1;
        int lang_len = d->strlen(lang_start);
        if (lang_len > 0 && lang_len < 63) {
          d->custom_memcpy(sync_lang, lang_start, lang_len);
          sync_lang[lang_len] = '\0';
          *last_slash = '\0'; // Truncate url to remove /<lang>
        }
      }
    }

    if (d->strlen(sync_lang) == 0) {
      d->printf("Error: --url must include a language path, e.g. http://host/en\n");
      d->free(clean_url);
      d->free(eff_db_path);
      d->free(eff_cache_dir);
      return 1;
    }

    const char *target_sub = app_null;
    if (d->strstr(command, "articles"))
      target_sub = "articles";
    else if (d->strstr(command, "authors"))
      target_sub = "authors";
    else if (d->strstr(command, "metrics"))
      target_sub = "metrics";
    else if (d->strstr(command, "config"))
      target_sub = "config";
    else {
      d->printf("Unknown sync target in command: %s\n", command);
      d->free(clean_url);
      d->free(eff_db_path);
      d->free(eff_cache_dir);
      return 1;
    }

    // Construct sub_path with lang: e.g. "en/articles"
    char sub_with_lang[128];
    d->custom_memset(sub_with_lang, 0, 128);
    d->custom_sprintf(sub_with_lang, "%s/%s", sync_lang, target_sub);

    if (d->strstr(command, "upload-") == command) {
      perform_upload_sync(d, eff_db_path, clean_url, pass, eff_cache_dir,
                          sub_with_lang);
    } else {
      perform_download_sync(d, eff_db_path, clean_url, pass, eff_cache_dir,
                            sub_with_lang);
    }

    d->free(clean_url);
    d->free(eff_db_path);
    d->free(eff_cache_dir);
    return 0;
  }

  d->printf("Unknown command: %s\n", command);
  d->printf(
      "Available commands: start, upload-articles, download-articles, ...\n");
  d->free(eff_db_path);
  d->free(eff_cache_dir);
  return 1;
}

// ===============================HELPERS IMPL==================================
const char *get_mime_type(appdeps *d, const char *path) {
  if (d->strstr(path, ".html"))
    return "text/html; charset=utf-8";
  if (d->strstr(path, ".css"))
    return "text/css";
  if (d->strstr(path, ".js"))
    return "application/javascript";
  if (d->strstr(path, ".json"))
    return "application/json";
  if (d->strstr(path, ".png"))
    return "image/png";
  if (d->strstr(path, ".jpg") || d->strstr(path, ".jpeg"))
    return "image/jpeg";
  if (d->strstr(path, ".gif"))
    return "image/gif";
  if (d->strstr(path, ".webp"))
    return "image/webp";
  if (d->strstr(path, ".ico"))
    return "image/x-icon";
  if (d->strstr(path, ".svg"))
    return "image/svg+xml";
  return "application/octet-stream";
}

void load_text_config(appdeps *d, const char *lang_db_path) {
  if (cached_text_config != app_null)
    return;
  char *path =
      d->concat_path(lang_db_path, "config/text.json");
  if (d->file_exists(path)) {
    cached_text_config = d->json_parse_file(path);
  } else {
    cached_text_config = d->json_create_object();
  }
  d->free(path);

  appjson *item;
  item = d->json_get_object_item(cached_text_config, "blog_name");
  global_text.blog_name = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "VibeLog";
  item = d->json_get_object_item(cached_text_config, "logo_text");
  global_text.logo_text = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "VIBELOG_";
  item = d->json_get_object_item(cached_text_config, "categories_dropdown_label");
  global_text.categories_dropdown_label = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Categories \xe2\x96\xbe";
  item = d->json_get_object_item(cached_text_config, "search_placeholder");
  global_text.search_placeholder = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Search...";
  item = d->json_get_object_item(cached_text_config, "sidebar_status_title");
  global_text.sidebar_status_title = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Network Status";
  item = d->json_get_object_item(cached_text_config, "sidebar_total_views_label");
  global_text.sidebar_total_views_label = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Total Views";
  item = d->json_get_object_item(cached_text_config, "sidebar_traffic_title");
  global_text.sidebar_traffic_title = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Traffic / Sector";
  item = d->json_get_object_item(cached_text_config, "footer_text");
  global_text.footer_text = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "VIBELOG SYSTEM \xc2\xa9 2026 // NO RIGHTS RESERVED";
  item = d->json_get_object_item(cached_text_config, "home_page_title");
  global_text.home_page_title = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Latest Articles";
  item = d->json_get_object_item(cached_text_config, "articles_page_title");
  global_text.articles_page_title = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Articles";
  item = d->json_get_object_item(cached_text_config, "filter_by_label");
  global_text.filter_by_label = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Filtering by: ";
  item = d->json_get_object_item(cached_text_config, "clear_filter_label");
  global_text.clear_filter_label = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Clear";
  item = d->json_get_object_item(cached_text_config, "no_articles_text");
  global_text.no_articles_text = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "No articles found";
  item = d->json_get_object_item(cached_text_config, "pagination_prev_label");
  global_text.pagination_prev_label = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Previous";
  item = d->json_get_object_item(cached_text_config, "pagination_next_label");
  global_text.pagination_next_label = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Next";
  item = d->json_get_object_item(cached_text_config, "published_on_label");
  global_text.published_on_label = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Published on ";
  item = d->json_get_object_item(cached_text_config, "content_unavailable_text");
  global_text.content_unavailable_text = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Content not available.";
  item = d->json_get_object_item(cached_text_config, "view_profile_label");
  global_text.view_profile_label = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "View Profile";
  item = d->json_get_object_item(cached_text_config, "recent_articles_by_label");
  global_text.recent_articles_by_label = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "Recent Articles by ";
  item = d->json_get_object_item(cached_text_config, "no_author_articles_text");
  global_text.no_author_articles_text = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "No articles found.";
  item = d->json_get_object_item(cached_text_config, "about_page_title");
  global_text.about_page_title = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "About";
  item = d->json_get_object_item(cached_text_config, "about_fallback_content");
  global_text.about_fallback_content = (item && d->json_is_string(item)) ? d->json_get_string_value(item) : "<h1>About</h1><p>Content to be added.</p>";
}

void load_global_data(appdeps *d, const char *lang_db_path) {
  load_text_config(d, lang_db_path);
  if (cached_categories == app_null) {
    char *path =
        d->concat_path(lang_db_path, "config/categorys.json");
    if (d->file_exists(path)) {
      cached_categories = d->json_parse_file(path);
    } else {
      // Fallback empty array
      cached_categories = d->json_create_array();
    }
    d->free(path);
  }
}

appjson *calculate_stats(appdeps *d, const char *lang_db_path);

char *render_page(appdeps *d, const char *lang, const char *title, const char *content) {
  appctext *t = d->new_ctext(app_null);

  // HEAD
  d->ctext_append(t, "<!DOCTYPE html><html lang='");
  d->ctext_append(t, lang);
  d->ctext_append(t, "'><head>");
  d->ctext_append(t, "<meta charset='UTF-8'><meta name='viewport' "
                     "content='width=device-width, initial-scale=1.0'>");
  d->ctext_append(t, "<title>");
  if (title) {
    d->ctext_append(t, title);
    d->ctext_append(t, " - ");
  }
  d->ctext_append(t, global_text.blog_name);
  d->ctext_append(t, "</title>");

  // Fonts
  d->ctext_append(
      t, "<link rel='preconnect' href='https://fonts.googleapis.com'>");
  d->ctext_append(
      t,
      "<link rel='preconnect' href='https://fonts.gstatic.com' crossorigin>");
  d->ctext_append(
      t, "<link "
         "href='https://fonts.googleapis.com/"
         "css2?family=IBM+Plex+Sans:wght@400;600&family=Inter:wght@400;500;600&"
         "family=JetBrains+Mono:wght@400;500&display=swap' rel='stylesheet'>");

  // CSS
  d->ctext_append(t, "<link rel='stylesheet' href='/database_file?path=");
  d->ctext_append(t, lang);
  d->ctext_append(t, "/config/style.css'>");
  d->ctext_append(t, "</head><body>");

  // NAVBAR
  d->ctext_append(t,
                  "<nav class='navbar'><div class='container navbar-content'>");
  d->ctext_append(t, "<a href='/");
  d->ctext_append(t, lang);
  d->ctext_append(t, "/' class='logo'>");
  d->ctext_append(t, global_text.logo_text);
  d->ctext_append(t, "</a>");

  d->ctext_append(t, "<div class='nav-links'>");

  // Dynamic Navbar items
  if (cached_categories && d->json_is_array(cached_categories)) {
    int count = d->json_get_array_size(cached_categories);
    for (int i = 0; i < count; i++) {
      appjson *item = d->json_get_array_item(cached_categories, i);
      appjson *nav = d->json_get_object_item(item, "navbar");
      if (nav && d->json_is_true(nav)) {
        const char *name =
            d->json_get_string_value(d->json_get_object_item(item, "name"));
        if (name) {
          d->ctext_append(t, "<a href='/");
          d->ctext_append(t, lang);
          d->ctext_append(t,
                          "/list_articles?page=1&limit=10&category=");
          d->ctext_append(t, name);
          d->ctext_append(t, "' class='nav-link'>");
          d->ctext_append(t, name);
          d->ctext_append(t, "</a>");
        }
      }
    }
  }

  // Categories Dropdown
  d->ctext_append(t, "<div class='dropdown'><button class='btn'>");
  d->ctext_append(t, global_text.categories_dropdown_label);
  d->ctext_append(t, "</button><div class='dropdown-content'>");
  if (cached_categories && d->json_is_array(cached_categories)) {
    int count = d->json_get_array_size(cached_categories);
    for (int i = 0; i < count; i++) {
      appjson *item = d->json_get_array_item(cached_categories, i);
      const char *name =
          d->json_get_string_value(d->json_get_object_item(item, "name"));
      const char *desc = d->json_get_string_value(
          d->json_get_object_item(item, "description"));

      d->ctext_append(t, "<a href='/");
      d->ctext_append(t, lang);
      d->ctext_append(t, "/list_articles?page=1&limit=10&category=");
      d->ctext_append(t, name);
      d->ctext_append(t, "' title='");
      if (desc)
        d->ctext_append(t, desc);
      d->ctext_append(t, "'>");
      d->ctext_append(t, name);
      d->ctext_append(t, "</a>");
    }
  }
  d->ctext_append(t, "</div></div>"); // Close content, close dropdown

  d->ctext_append(t, "</div>"); // Close nav-links

  // Search
  d->ctext_append(t, "<form action='/");
  d->ctext_append(t, lang);
  d->ctext_append(t, "/list_articles' method='GET' class='search-form'>");
  d->ctext_append(t, "<input type='text' name='search' placeholder='");
  d->ctext_append(t, global_text.search_placeholder);
  d->ctext_append(t, "' class='search-input'>");
  d->ctext_append(t, "</form>");

  d->ctext_append(t, "</div></nav>"); // Close container, close nav

  // MAIN LAYOUT
  d->ctext_append(t, "<div class='container main-layout'>");

  // Content Column
  d->ctext_append(t, "<main class='content-column'>");
  d->ctext_append(t, content);
  d->ctext_append(t, "</main>");

  // Sidebar Column
  d->ctext_append(t, "<aside class='sidebar-column'>");

  // Stats Block
  char *stats_lang_db_path = d->concat_path(global_config.database_path, lang);
  appjson *stats = calculate_stats(d, stats_lang_db_path);
  d->free(stats_lang_db_path);

  d->ctext_append(t, "<div class='sidebar-section'>");
  d->ctext_append(t, "<h3 class='sidebar-title'>");
  d->ctext_append(t, global_text.sidebar_status_title);
  d->ctext_append(t, "</h3>");

  // Total Views
  double total_views =
      d->json_get_number_value(d->json_get_object_item(stats, "total_views"));
  d->ctext_append(t, "<div class='stat-item'><span class='stat-label'>");
  d->ctext_append(t, global_text.sidebar_total_views_label);
  d->ctext_append(t, "</span><span class='stat-value'>");
  char tv_buf[64];
  d->custom_sprintf(tv_buf, "%.0f", total_views);
  d->ctext_append(t, tv_buf);
  d->ctext_append(t, "</span></div>");

  d->ctext_append(t, "</div>");

  // Categories Stats
  d->ctext_append(t, "<div class='sidebar-section'>");
  d->ctext_append(t, "<h3 class='sidebar-title'>");
  d->ctext_append(t, global_text.sidebar_traffic_title);
  d->ctext_append(t, "</h3>");

  appjson *cats = d->json_get_object_item(stats, "categories");
  if (cats && d->json_is_array(cats)) {
    int c_count = d->json_get_array_size(cats);
    for (int i = 0; i < c_count; i++) {
      appjson *cat_obj = d->json_get_array_item(cats, i);
      const char *cname =
          d->json_get_string_value(d->json_get_object_item(cat_obj, "name"));
      double cviews =
          d->json_get_number_value(d->json_get_object_item(cat_obj, "views"));

      d->ctext_append(t, "<div class='stat-item'><span class='stat-label'>");
      d->ctext_append(t, cname);
      d->ctext_append(t, "</span><span class='stat-value'>");
      char cv_buf[64];
      d->custom_sprintf(cv_buf, "%.0f", cviews);
      d->ctext_append(t, cv_buf);
      d->ctext_append(t, "</span></div>");
    }
  }

  d->ctext_append(t, "</div>");
  d->json_delete(stats);

  d->ctext_append(t, "</aside>");

  d->ctext_append(t, "</div>"); // Close main-layout

  // Footer
  d->ctext_append(t, "<footer class='footer'><div class='container'>");
  d->ctext_append(t, global_text.footer_text);
  d->ctext_append(t, "</div></footer>");

  d->ctext_append(t, "</body></html>");

  char *res = d->strdup(d->ctext_get_text(t));
  d->ctext_free(t);
  return res;
}

void strip_trailing_slash(appdeps *d, char *dst, const char *src) {
  int len = d->strlen(src);
  while (len > 0 && src[len - 1] == '/') len--;
  d->custom_memcpy(dst, src, len);
  dst[len] = '\0';
}

long parse_date_to_ts(appdeps *d, const char *date) {
  // YYYY/MM/DD -> YYYYMMDD
  int len = d->strlen(date);

  if (len < 10)
    return 0;

  // Simple manual parsing for "YYYY/MM/DD"
  char year[5] = {0};
  char month[3] = {0};
  char day[3] = {0};

  year[0] = date[0];
  year[1] = date[1];
  year[2] = date[2];
  year[3] = date[3];
  month[0] = date[5];
  month[1] = date[6];
  day[0] = date[8];
  day[1] = date[9];

  char buf[20];
  d->custom_sprintf(buf, "%s%s%s", year, month, day);
  return d->atoi(buf);
}

appjson *load_articles(appdeps *d, const char *lang_db_path, int page, int limit, const char *category,
                       const char *search, const char *author_id) {
  appjson *results = d->json_create_array();

  // 1. List Years (database/<lang>/articles/YYYY)
  char *articles_root = d->concat_path(lang_db_path, "articles");
  appstringarray *years = d->list_dirs(articles_root);

  if (!years) {
    d->free(articles_root);
    return results;
  }

  long years_count = d->get_stringarray_size(years);

  // Temporary storage for sorting
  appjson *all_articles = d->json_create_array();

  for (int yi = 0; yi < years_count; yi++) {
    const char *year_str = d->get_stringarray_item(years, yi);
    char *year_path = d->concat_path(articles_root, year_str);

    appstringarray *months = d->list_dirs(year_path);
    if (!months) {
      d->free(year_path);
      continue;
    }

    long months_count = d->get_stringarray_size(months);
    for (int mi = 0; mi < months_count; mi++) {
      const char *month_str = d->get_stringarray_item(months, mi);
      char *month_path = d->concat_path(year_path, month_str);

      appstringarray *days = d->list_dirs(month_path);
      if (!days) {
        d->free(month_path);
        continue;
      }

      long days_count = d->get_stringarray_size(days);
      for (int di = 0; di < days_count; di++) {
        const char *day_str = d->get_stringarray_item(days, di);
        char *day_path = d->concat_path(month_path, day_str);

        // Build date string as "YYYY/MM/DD"
        char y[8], m[4], dd[4];
        strip_trailing_slash(d, y, year_str);
        strip_trailing_slash(d, m, month_str);
        strip_trailing_slash(d, dd, day_str);
        char date_str[16];
        d->custom_sprintf(date_str, "%s/%s/%s", y, m, dd);
        long ts = parse_date_to_ts(d, date_str);

        appstringarray *article_ids = d->list_dirs(day_path);
        if (article_ids) {
          long arts_count = d->get_stringarray_size(article_ids);
          for (int j = 0; j < arts_count; j++) {
            const char *aid = d->get_stringarray_item(article_ids, j);

            // Load data.json
            char *art_path = d->concat_path(day_path, aid);
            char *json_path = d->concat_path(art_path, "data.json");

            if (d->file_exists(json_path)) {
              appjson *data = d->json_parse_file(json_path);
              if (data) {
                d->json_add_string_to_object(data, "date", date_str);
                d->json_add_string_to_object(data, "id", aid);
                d->json_add_number_to_object(
                    data, "ts", (double)ts); // Add timestamp for sorting

                // Filter logic
                appbool match = app_true;

                if (author_id) {
                  const char *aid_json = d->json_get_string_value(
                      d->json_get_object_item(data, "author_id"));
                  if (!aid_json || d->strcmp(aid_json, author_id) != 0) {
                    match = app_false;
                  }
                }

                if (match && category) {
                  appjson *cats = d->json_get_object_item(data, "categories");
                  appbool cat_found = app_false;
                  if (cats && d->json_is_array(cats)) {
                    int c_size = d->json_get_array_size(cats);
                    for (int c = 0; c < c_size; c++) {
                      const char *cname = d->json_get_string_value(
                          d->json_get_array_item(cats, c));
                      if (cname && d->strcmp(cname, category) == 0) {
                        cat_found = app_true;
                        break;
                      }
                    }
                  }
                  if (!cat_found)
                    match = app_false;
                }

                if (search && match) {
                  // Simple substring search
                  const char *t = d->json_get_string_value(
                      d->json_get_object_item(data, "title"));
                  const char *s = d->json_get_string_value(
                      d->json_get_object_item(data, "summary"));
                  if ((!t || !d->strstr(t, search)) &&
                      (!s || !d->strstr(s, search))) {
                    match = app_false;
                  }
                }

                if (match) {
                  d->json_add_item_to_array(all_articles, data);
                } else {
                  d->json_delete(data);
                }
              }
            }
            d->free(art_path);
            d->free(json_path);
          }
          d->delete_stringarray(article_ids);
        }
        d->free(day_path);
      }
      d->delete_stringarray(days);
      d->free(month_path);
    }
    d->delete_stringarray(months);
    d->free(year_path);
  }
  d->delete_stringarray(years);
  d->free(articles_root);

  // SORTING (Bubble Sort on appjson array by 'ts' desc - newest first)
  int total = d->json_get_array_size(all_articles);
  for (int i = 0; i < total - 1; i++) {
    for (int j = 0; j < total - i - 1; j++) {
      appjson *a = d->json_get_array_item(all_articles, j);
      appjson *b = d->json_get_array_item(all_articles, j + 1);
      double tsa = d->json_get_number_value(d->json_get_object_item(a, "ts"));
      double tsb = d->json_get_number_value(d->json_get_object_item(b, "ts"));

      // For descending order (newest first): swap if a's timestamp is smaller than b's
      if (tsa < tsb) {
        // Create temporary references to avoid memory issues
        appjson *temp_a = d->json_duplicate(a, app_true);
        appjson *temp_b = d->json_duplicate(b, app_true);
        
        // Replace items in array
        d->json_replace_item_in_array(all_articles, j, temp_b);
        d->json_replace_item_in_array(all_articles, j + 1, temp_a);
      }
    }
  }

  // Pagination
  int start = (page - 1) * limit;
  int end = start + limit;
  if (start >= total) {
    d->json_delete(all_articles);
    return results;
  }

  for (int i = start; i < end && i < total; i++) {
    appjson *item = d->json_get_array_item(all_articles, i);
    d->json_add_item_to_array(results, d->json_duplicate(item, app_true));
  }

  d->json_delete(all_articles);
  return results;
}

// ===============================METRICS & DATA================================
appjson *calculate_stats(appdeps *d, const char *lang_db_path) {
  appjson *stats = d->json_create_object();
  d->json_add_number_to_object(stats, "total_views", 0);
  appjson *cats = d->json_create_array(); // Array of {name, views}
  d->json_add_item_to_object(stats, "categories", cats);

  // Iterate all articles (YYYY/MM/DD structure)
  char *articles_root = d->concat_path(lang_db_path, "articles");
  appstringarray *years = d->list_dirs(articles_root);

  if (!years) {
    d->free(articles_root);
    return stats;
  }

  long years_count = d->get_stringarray_size(years);
  double total_views = 0;

  // Add Page Views
  char *metrics_root = d->concat_path(lang_db_path, "metrics");
  char *pages_metrics = d->concat_path(metrics_root, "pages");
  d->free(metrics_root);

  if (d->dir_exists(pages_metrics)) {
    appstringarray *pages = d->list_dirs(pages_metrics);
    if (pages) {
      long p_count = d->get_stringarray_size(pages);
      for (int i = 0; i < p_count; i++) {
        const char *pid = d->get_stringarray_item(pages, i);
        char *p_dir = d->concat_path(pages_metrics, pid);
        char *pv_file = d->concat_path(p_dir, "total_views.json");
        d->free(p_dir);

        if (d->file_exists(pv_file)) {
          appjson *pv_json = d->json_parse_file(pv_file);
          if (pv_json) {
            double pv = d->json_get_number_value(
                d->json_get_object_item(pv_json, "views"));
            total_views += pv;
            d->json_delete(pv_json);
          }
        }
        d->free(pv_file);
      }
      d->delete_stringarray(pages);
    }
  }
  d->free(pages_metrics);

  for (int yi = 0; yi < years_count; yi++) {
    const char *year_str = d->get_stringarray_item(years, yi);
    char *year_path = d->concat_path(articles_root, year_str);

    appstringarray *months = d->list_dirs(year_path);
    if (!months) {
      d->free(year_path);
      continue;
    }

    long months_count = d->get_stringarray_size(months);
    for (int mi = 0; mi < months_count; mi++) {
      const char *month_str = d->get_stringarray_item(months, mi);
      char *month_path = d->concat_path(year_path, month_str);

      appstringarray *days = d->list_dirs(month_path);
      if (!days) {
        d->free(month_path);
        continue;
      }

      long days_count = d->get_stringarray_size(days);
      for (int di = 0; di < days_count; di++) {
        const char *day_str = d->get_stringarray_item(days, di);
        char *day_path = d->concat_path(month_path, day_str);

        // Build date string as "YYYY/MM/DD"
        char y[8], m[4], dd[4];
        strip_trailing_slash(d, y, year_str);
        strip_trailing_slash(d, m, month_str);
        strip_trailing_slash(d, dd, day_str);
        char date_str[16];
        d->custom_sprintf(date_str, "%s/%s/%s", y, m, dd);

        appstringarray *article_ids = d->list_dirs(day_path);
        if (article_ids) {
          long arts_count = d->get_stringarray_size(article_ids);
          for (int j = 0; j < arts_count; j++) {
            const char *aid = d->get_stringarray_item(article_ids, j);

            // 1. Get Categories
            char *art_path = d->concat_path(day_path, aid);
            char *json_path = d->concat_path(art_path, "data.json");

            appjson *art_data = app_null;
            if (d->file_exists(json_path)) {
              art_data = d->json_parse_file(json_path);
            }
            d->free(json_path);

            // 2. Get Views
            char *mr = d->concat_path(lang_db_path, "metrics");
            char *art_metrics = d->concat_path(mr, "articles");
            d->free(mr);
            char *m_date_dir = d->concat_path(art_metrics, date_str);
            d->free(art_metrics);
            char *m_id_dir = d->concat_path(m_date_dir, aid);
            d->free(m_date_dir);
            char *views_file = d->concat_path(m_id_dir, "total_views.json");
            d->free(m_id_dir);

            double views = 0;
            if (d->file_exists(views_file)) {
              appjson *v_json = d->json_parse_file(views_file);
              if (v_json) {
                views = d->json_get_number_value(
                    d->json_get_object_item(v_json, "views"));
                d->json_delete(v_json);
              }
            }
            d->free(views_file);

            total_views += views;

            // Aggregate Categories (Linear Scan on Array)
            if (art_data) {
              appjson *c_arr = d->json_get_object_item(art_data, "categories");
              if (c_arr && d->json_is_array(c_arr)) {
                int c_count = d->json_get_array_size(c_arr);
                for (int k = 0; k < c_count; k++) {
                  const char *cname = d->json_get_string_value(
                      d->json_get_array_item(c_arr, k));
                  if (cname) {
                    // Find in cats array
                    appbool found = app_false;
                    int cats_len = d->json_get_array_size(cats);
                    for (int m = 0; m < cats_len; m++) {
                      appjson *cat_obj = d->json_get_array_item(cats, m);
                      const char *ex_name = d->json_get_string_value(
                          d->json_get_object_item(cat_obj, "name"));
                      if (ex_name && d->strcmp(ex_name, cname) == 0) {
                        double cv = d->json_get_number_value(
                            d->json_get_object_item(cat_obj, "views"));
                        d->json_replace_item_in_object(
                            cat_obj, "views",
                            d->json_create_number(cv + views));
                        found = app_true;
                        break;
                      }
                    }
                    if (!found) {
                      appjson *new_cat = d->json_create_object();
                      d->json_add_string_to_object(new_cat, "name", cname);
                      d->json_add_number_to_object(new_cat, "views", views);
                      d->json_add_item_to_array(cats, new_cat);
                    }
                  }
                }
              }
              d->json_delete(art_data);
            }
            d->free(art_path);
          }
          d->delete_stringarray(article_ids);
        }
        d->free(day_path);
      }
      d->delete_stringarray(days);
      d->free(month_path);
    }
    d->delete_stringarray(months);
    d->free(year_path);
  }
  d->delete_stringarray(years);
  d->free(articles_root);

  d->json_replace_item_in_object(stats, "total_views",
                                 d->json_create_number(total_views));
  return stats;
}

appjson *load_author(appdeps *d, const char *lang_db_path, const char *author_id) {
  char *path = d->concat_path(lang_db_path, "authors");
  char *tmp = d->concat_path(path, author_id);
  d->free(path);
  path = d->concat_path(tmp, "data.json");
  d->free(tmp);

  appjson *data = app_null;
  if (d->file_exists(path)) {
    data = d->json_parse_file(path);
  }
  d->free(path);
  return data;
}

// ===============================VIEW METRICS API==============================
const appserverresponse *handle_api_record_view(appdeps *d,
                                                const appserverrequest *req) {
  const appjson *body = d->read_server_json(req, 4096);
  if (!body) {
    return d->send_text("Invalid JSON body", "text/plain", 400);
  }

  const char *date = d->json_get_string_value(d->json_get_object_item(body, "date"));
  const char *id = d->json_get_string_value(d->json_get_object_item(body, "id"));
  const char *lang = d->json_get_string_value(d->json_get_object_item(body, "lang"));
  const char *language = d->json_get_string_value(d->json_get_object_item(body, "language"));
  const char *device = d->json_get_string_value(d->json_get_object_item(body, "device"));
  const char *country = d->json_get_string_value(d->json_get_object_item(body, "country"));
  double duration = 0;
  appjson *dur_item = d->json_get_object_item(body, "duration");
  if (dur_item && d->json_is_number(dur_item)) {
    duration = d->json_get_number_value(dur_item);
  }

  if (!date || !id) {
    return d->send_text("Missing date or id", "text/plain", 400);
  }

  // Use provided lang or default to "en"
  const char *db_lang = lang ? lang : "en";
  char *lang_db_path = d->concat_path(global_config.database_path, db_lang);

  // Fallback to "en" if lang dir doesn't exist
  if (!d->dir_exists(lang_db_path)) {
    d->free(lang_db_path);
    lang_db_path = d->concat_path(global_config.database_path, "en");
  }

  // Max-view guard: reject if this article already reached the view limit
  if (global_config.max_view > 0) {
    char *metrics_root = d->concat_path(lang_db_path, "metrics");
    char *art_metrics = d->concat_path(metrics_root, "articles");
    d->free(metrics_root);
    char *date_dir = d->concat_path(art_metrics, date);
    d->free(art_metrics);
    char *id_dir = d->concat_path(date_dir, id);
    d->free(date_dir);
    char *tv_path = d->concat_path(id_dir, "total_views.json");
    d->free(id_dir);

    if (d->file_exists(tv_path)) {
      appjson *totals = d->json_parse_file(tv_path);
      if (totals) {
        appjson *v_item = d->json_get_object_item(totals, "views");
        double v = d->json_get_number_value(v_item);
        d->json_delete(totals);
        if ((int)v >= global_config.max_view) {
          d->free(tv_path);
          d->free(lang_db_path);
          return d->send_text("Too Many Requests", "text/plain", 429);
        }
      }
    }
    d->free(tv_path);
  }

  record_view(d, lang_db_path, date, id, language, device, country, duration);

  d->free(lang_db_path);
  return d->send_text("OK", "text/plain", 200);
}

const appserverresponse *handle_api_record_page_view(appdeps *d,
                                                     const appserverrequest *req) {
  const appjson *body = d->read_server_json(req, 4096);
  if (!body) {
    return d->send_text("Invalid JSON body", "text/plain", 400);
  }

  const char *page_id = d->json_get_string_value(d->json_get_object_item(body, "page"));
  const char *lang = d->json_get_string_value(d->json_get_object_item(body, "lang"));
  const char *language = d->json_get_string_value(d->json_get_object_item(body, "language"));
  const char *device = d->json_get_string_value(d->json_get_object_item(body, "device"));
  const char *country = d->json_get_string_value(d->json_get_object_item(body, "country"));
  const char *category = d->json_get_string_value(d->json_get_object_item(body, "category"));
  const char *search = d->json_get_string_value(d->json_get_object_item(body, "search"));
  int chunk = 1, size = 10;
  double duration = 0;

  appjson *chunk_item = d->json_get_object_item(body, "chunk");
  if (chunk_item && d->json_is_number(chunk_item))
    chunk = (int)d->json_get_number_value(chunk_item);

  appjson *size_item = d->json_get_object_item(body, "size");
  if (size_item && d->json_is_number(size_item))
    size = (int)d->json_get_number_value(size_item);

  appjson *dur_item = d->json_get_object_item(body, "duration");
  if (dur_item && d->json_is_number(dur_item))
    duration = d->json_get_number_value(dur_item);

  if (!page_id) {
    return d->send_text("Missing page", "text/plain", 400);
  }

  const char *db_lang = lang ? lang : "en";
  char *lang_db_path = d->concat_path(global_config.database_path, db_lang);

  if (!d->dir_exists(lang_db_path)) {
    d->free(lang_db_path);
    lang_db_path = d->concat_path(global_config.database_path, "en");
  }

  // Max-view guard: reject if this page already reached the view limit
  if (global_config.max_view > 0) {
    char *metrics_root = d->concat_path(lang_db_path, "metrics");
    char *pages_metrics = d->concat_path(metrics_root, "pages");
    d->free(metrics_root);
    char *page_dir = d->concat_path(pages_metrics, page_id);
    d->free(pages_metrics);
    char *tv_path = d->concat_path(page_dir, "total_views.json");
    d->free(page_dir);

    if (d->file_exists(tv_path)) {
      appjson *totals = d->json_parse_file(tv_path);
      if (totals) {
        appjson *v_item = d->json_get_object_item(totals, "views");
        double v = d->json_get_number_value(v_item);
        d->json_delete(totals);
        if ((int)v >= global_config.max_view) {
          d->free(tv_path);
          d->free(lang_db_path);
          return d->send_text("Too Many Requests", "text/plain", 429);
        }
      }
    }
    d->free(tv_path);
  }

  record_page_view(d, lang_db_path, page_id, chunk, size, category, search,
                   language, device, country, duration);

  d->free(lang_db_path);
  return d->send_text("OK", "text/plain", 200);
}

void record_view(appdeps *d, const char *lang_db_path, const char *date, const char *id,
                 const char *language, const char *device, const char *country, double duration) {
  // 1. Setup paths
  char *metrics_root = d->concat_path(lang_db_path, "metrics");
  char *art_metrics = d->concat_path(metrics_root, "articles");
  d->free(metrics_root);

  char *date_dir = d->concat_path(art_metrics, date);
  d->free(art_metrics);

  char *id_dir = d->concat_path(date_dir, id);
  d->free(date_dir);

  if (!d->dir_exists(id_dir)) {
    d->create_dir(id_dir);
  }

  // 2. Atomic Total Views Update
  char *total_views_path = d->concat_path(id_dir, "total_views.json");
  appjson *totals = app_null;

  if (d->file_exists(total_views_path)) {
    totals = d->json_parse_file(total_views_path);
  }

  if (!totals) {
    totals = d->json_create_object();
    d->json_add_number_to_object(totals, "views", 0);
  }

  appjson *v_item = d->json_get_object_item(totals, "views");
  double v = d->json_get_number_value(v_item);
  d->json_replace_item_in_object(totals, "views", d->json_create_number(v + 1));

  char *tmp_path = d->concat_path(id_dir, "total_views.json.tmp");
  d->json_save_file(totals, tmp_path);
  d->move_any(tmp_path, total_views_path); // Rename/Move is atomic on POSIX

  d->free(tmp_path);
  d->free(total_views_path);
  d->json_delete(totals);

  // 3. Individual View Record
  char *views_dir = d->concat_path(id_dir, "views");
  if (!d->dir_exists(views_dir))
    d->create_dir(views_dir);

  long now = d->get_unix_time();
  char date_buf[64];
  d->get_formatted_time(now, date_buf, 64, "%Y-%m-%d");

  char day_dir_name[128];
  d->custom_sprintf(day_dir_name, "%s_%ld", date_buf,
                    now); // Use underscore, not colon

  char *day_path = d->concat_path(views_dir, day_dir_name);
  if (!d->dir_exists(day_path))
    d->create_dir(day_path);

  // View File
  appjson *view = d->json_create_object();
  d->json_add_number_to_object(view, "date", (double)now);
  d->json_add_string_to_object(view, "language", language ? language : "unknown");
  d->json_add_string_to_object(view, "device", device ? device : "unknown");
  d->json_add_string_to_object(view, "country", country ? country : "unknown");
  d->json_add_number_to_object(view, "duration", duration);

  int rnd = d->get_random();
  char fname[64];
  d->custom_sprintf(fname, "view_%ld_%d.json", now, rnd);

  char *view_path = d->concat_path(day_path, fname);
  d->json_save_file(view, view_path);

  d->free(view_path);
  d->json_delete(view);
  d->free(day_path);
  d->free(views_dir);
  d->free(id_dir);
}
void record_page_view(appdeps *d, const char *lang_db_path, const char *page_id, int chunk, int size,
                      const char *category, const char *search,
                      const char *language, const char *device, const char *country, double duration) {
  // 1. Setup paths
  char *metrics_root = d->concat_path(lang_db_path, "metrics");
  char *pages_metrics = d->concat_path(metrics_root, "pages");
  d->free(metrics_root);

  if (!d->dir_exists(pages_metrics)) {
    d->create_dir(pages_metrics);
  }

  char *page_dir = d->concat_path(pages_metrics, page_id);
  d->free(pages_metrics);

  if (!d->dir_exists(page_dir)) {
    d->create_dir(page_dir);
  }

  // 2. Atomic Total Views Update
  char *total_views_path = d->concat_path(page_dir, "total_views.json");
  appjson *totals = app_null;

  if (d->file_exists(total_views_path)) {
    totals = d->json_parse_file(total_views_path);
  }

  if (!totals) {
    totals = d->json_create_object();
    d->json_add_number_to_object(totals, "views", 0);
  }

  appjson *v_item = d->json_get_object_item(totals, "views");
  double v = d->json_get_number_value(v_item);
  d->json_replace_item_in_object(totals, "views", d->json_create_number(v + 1));

  char *tmp_path = d->concat_path(page_dir, "total_views.json.tmp");
  d->json_save_file(totals, tmp_path);
  d->move_any(tmp_path, total_views_path);

  d->free(tmp_path);
  d->free(total_views_path);
  d->json_delete(totals);

  // 3. Individual View Record
  char *views_dir = d->concat_path(page_dir, "views");
  if (!d->dir_exists(views_dir))
    d->create_dir(views_dir);

  long now = d->get_unix_time();
  char date_buf[64];
  d->get_formatted_time(now, date_buf, 64, "%Y-%m-%d");

  char day_dir_name[128];
  d->custom_sprintf(day_dir_name, "%s_%ld", date_buf, now);

  char *day_path = d->concat_path(views_dir, day_dir_name);
  if (!d->dir_exists(day_path))
    d->create_dir(day_path);

  appjson *view = d->json_create_object();
  char iso_buf[64];
  d->get_formatted_time(now, iso_buf, 64, "%Y-%m-%dT%H:%M:%SZ");
  d->json_add_string_to_object(view, "date", iso_buf);
  d->json_add_string_to_object(view, "page", page_id);
  d->json_add_number_to_object(view, "duration", duration);
  d->json_add_number_to_object(view, "chunk", (double)chunk);
  d->json_add_number_to_object(view, "size", (double)size);
  if (category)
    d->json_add_string_to_object(view, "category", category);
  else
    d->json_add_null_to_object(view, "category");

  if (search)
    d->json_add_string_to_object(view, "search", search);
  else
    d->json_add_null_to_object(view, "search");

  if (language)
    d->json_add_string_to_object(view, "language", language);
  else
    d->json_add_null_to_object(view, "language");

  if (device)
    d->json_add_string_to_object(view, "device", device);
  else
    d->json_add_null_to_object(view, "device");

  d->json_add_string_to_object(view, "country", country ? country : "unknown");

  int rnd = d->get_random();
  char fname[64];
  d->custom_sprintf(fname, "view_%ld_%d.json", now, rnd);

  char *view_path = d->concat_path(day_path, fname);
  d->json_save_file(view, view_path);

  d->free(view_path);
  d->json_delete(view);
  d->free(day_path);
  d->free(views_dir);
  d->free(page_dir);
}
