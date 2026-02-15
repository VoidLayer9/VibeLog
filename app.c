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
};

// ===============================VIBELOG CONFIG================================
typedef struct {
  const char *database_path;
  const char *root_password;
  int port;
  const char *cache_dir;
} VibeLogConfig;

VibeLogConfig global_config = {0};

// cache
appjson *cached_categories = app_null;

// ===============================HELPER PROTOTYPES=============================
const char *get_mime_type(appdeps *d, const char *path);
appbool is_safe_path(appdeps *d, const char *path) {
  if (d->strstr(path, ".."))
    return app_false;
  // Check null bytes? String functions usually fail on them anyway.
  return app_true;
}
char *render_page(appdeps *d, const char *title, const char *content);
void load_global_data(appdeps *d);
appjson *load_articles(appdeps *d, int page, int limit, const char *category,
                       const char *search, const char *author_id);
appjson *load_author(appdeps *d, const char *author_id);
void record_view(appdeps *d, const char *date, const char *id);

// ===============================HANDLERS======================================
const appserverresponse *handle_article(appdeps *d,
                                        const appserverrequest *req) {
  const char *date = d->get_server_query_param(req, "date");
  const char *id = d->get_server_query_param(req, "id");

  if (!date || !id)
    return d->send_text("Missing parameters", "text/plain", 400);

  // Load Article Data
  char *path = d->concat_path(global_config.database_path, "articles");
  char *tmp = d->concat_path(path, date);
  d->free(path);
  path = d->concat_path(tmp, id);
  d->free(tmp);

  char *json_path = d->concat_path(path, "data.json");
  if (!d->file_exists(json_path)) {
    d->free(json_path);
    d->free(path);
    return d->send_text("Article not found", "text/plain", 404);
  }

  appjson *data = d->json_parse_file(json_path);
  d->free(json_path);

  if (!data) {
    d->free(path);
    return d->send_text("Corrupt article data", "text/plain", 500);
  }

  // Record View (Async? No, synchronous per prompt)
  record_view(d, date, id);

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
                     "color:#71717a;'>Published on ");
  d->ctext_append(t, date);
  d->ctext_append(t, "</div>");

  // Content (en.html default)
  char *content_dir = d->concat_path(path, "content");
  char *content_path =
      d->concat_path(content_dir, "en.html"); // TODO: Lang detection
  char *html_content = d->read_string(content_path);

  if (html_content) {
    d->ctext_append(t, "<div class='article-body' style='line-height:1.8'>");
    d->ctext_append(t, html_content);
    d->ctext_append(t, "</div>");
    d->free(html_content);
  } else {
    d->ctext_append(t, "<p>Content not available.</p>");
  }
  d->free(content_path);
  d->free(content_dir);

  // Author
  const char *author_id =
      d->json_get_string_value(d->json_get_object_item(data, "author_id"));
  if (author_id) {
    appjson *author = load_author(d, author_id);
    if (author) {
      const char *aname =
          d->json_get_string_value(d->json_get_object_item(author, "name"));
      const char *apic =
          d->json_get_string_value(d->json_get_object_item(author, "picture"));

      d->ctext_append(t, "<div class='author-box' style='margin-top:4rem; "
                         "border-top:1px solid #1c1c1f; padding-top:2rem; "
                         "display:flex; align-items:center; gap:1rem;'>");
      if (apic) {
        // TODO: Fix path resolution for images (author dir?)
        // database/authors/<id>/<pic>
        // Route: /database_file?path=authors/<id>/<pic>
        d->ctext_append(t, "<img src='/database_file?path=authors/");
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
      d->ctext_append(t, "</div><a href='/author?id=");
      d->ctext_append(t, author_id);
      d->ctext_append(t,
                      "' class='btn' style='font-size:0.7rem; padding:0.2rem "
                      "0.5rem; margin-top:0.5rem;'>View Profile</a></div>");

      d->ctext_append(t, "</div>");
      d->json_delete(author);
    }
  }

  d->ctext_append(t, "</article>");

  d->free(path);
  d->json_delete(data);

  load_global_data(d); // For navbar
  char *full_html = render_page(d, title, d->ctext_get_text(t));
  d->ctext_free(t);

  const appserverresponse *resp = d->send_text(full_html, "text/html", 200);
  d->free(full_html);
  return resp;
}
const appserverresponse *handle_author(appdeps *d,
                                       const appserverrequest *req) {
  const char *id = d->get_server_query_param(req, "id");
  if (!id)
    return d->send_text("Missing author id", "text/plain", 400);

  appjson *author = load_author(d, id);
  if (!author)
    return d->send_text("Author not found", "text/plain", 404);

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
    d->ctext_append(t, "<img src='/database_file?path=authors/");
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

  d->ctext_append(t, "<h2>Recent Articles by ");
  d->ctext_append(t, name);
  d->ctext_append(t, "</h2>");

  // Load articles by author
  appjson *articles = load_articles(d, 1, 20, app_null, app_null, id);

  if (d->json_get_array_size(articles) == 0) {
    d->ctext_append(t, "<p>No articles found.</p>");
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
      d->ctext_append(t, "<h3><a href='/article?date=");
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

  char *full_html = render_page(d, name, d->ctext_get_text(t));
  d->ctext_free(t);
  const appserverresponse *resp = d->send_text(full_html, "text/html", 200);
  d->free(full_html);
  return resp;
}

const appserverresponse *handle_about(appdeps *d, const appserverrequest *req) {
  char *path = d->concat_path(global_config.database_path, "pages");
  char *about_path = d->concat_path(path, "about.html");
  d->free(path);

  char *content = app_null;
  if (d->file_exists(about_path)) {
    content = d->read_string(about_path);
  }
  d->free(about_path);

  char *full_html = render_page(
      d, "About",
      content ? content : "<h1>About</h1><p>Content to be added.</p>");
  if (content)
    d->free(content);

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
render_article_list_response(appdeps *d, const char *title, int page, int limit,
                             const char *category, const char *search) {

  // Cap limit just in case
  if (limit > 50)
    limit = 50;
  if (limit < 1)
    limit = 10;
  if (page < 1)
    page = 1;

  appjson *articles = load_articles(d, page, limit, category, search, app_null);

  appctext *t = d->new_ctext(app_null);
  d->ctext_append(t, "<h1>");
  d->ctext_append(t, title);
  d->ctext_append(t, "</h1>");

  // Filter info
  if (category || search) {
    d->ctext_append(t, "<div class='filter-info'>Filtering by: ");
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
    d->ctext_append(
        t, " <a href='/list_articles' class='btn' style='padding:0.2rem "
           "0.5rem; margin-left:1rem; font-size:0.7rem'>Clear</a></div><br>");
  }

  if (d->json_get_array_size(articles) == 0) {
    d->ctext_append(t, "<div class='card'><div class='card-title'>No articles "
                       "found</div></div>");
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
            "<div class='card-image'><img src='/database_file?path=articles/");
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
      d->ctext_append(t, "<h2 class='card-title'><a href='/article?date=");
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
    d->ctext_append(t, "<a href='/list_articles?page=");
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
    d->ctext_append(t, "' class='btn'>Previous</a>");
  }

  // We don't know total/next without loading all, but load_articles pagination
  // slices it. Optimization: load_articles could return total count? For now,
  // simple "Next" if we invoked full limit
  if (d->json_get_array_size(articles) == limit) {
    d->ctext_append(t, "<a href='/list_articles?page=");
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
    d->ctext_append(t, "' class='btn'>Next</a>");
  }
  d->ctext_append(t, "</div>");

  d->json_delete(articles);

  char *full_html = render_page(d, title, d->ctext_get_text(t));
  d->ctext_free(t);
  const appserverresponse *resp = d->send_text(full_html, "text/html", 200);
  d->free(full_html);
  return resp;
}

const appserverresponse *handle_home(appdeps *d, const appserverrequest *req) {
  load_global_data(d);
  // Home behaves like list_articles with default params (page=1, limit=10)
  return render_article_list_response(d, "Latest Articles", 1, 10, app_null,
                                      app_null);
}

const appserverresponse *handle_list_articles(appdeps *d,
                                              const appserverrequest *req) {
  load_global_data(d);

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

  return render_article_list_response(d, "Articles", page, limit, category,
                                      search);
}

// =======================MANAGEMENT API========================================
appbool check_auth(appdeps *d, const appserverrequest *req) {
  const char *pass = d->get_server_header(req, "root_password");
  if (pass && global_config.root_password &&
      d->strcmp(pass, global_config.root_password) == 0) {
    return app_true;
  }
  return app_false;
}

const appserverresponse *handle_api_write_file(appdeps *d,
                                               const appserverrequest *req) {
  if (!check_auth(d, req))
    return d->send_text("Unauthorized", "text/plain", 401);

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
    return d->send_text("Unauthorized", "text/plain", 401);

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

const appserverresponse *handle_api_delete_file(appdeps *d,
                                                const appserverrequest *req) {
  if (!check_auth(d, req))
    return d->send_text("Unauthorized", "text/plain", 401);

  const char *path = d->get_server_header(req, "path");
  if (!path)
    return d->send_text("Missing path header", "text/plain", 400);
  if (!is_safe_path(d, path))
    return d->send_text("Invalid path", "text/plain", 403);

  char *full_path = d->concat_path(global_config.database_path, path);
  d->delete_any(full_path);
  d->free(full_path);

  return d->send_text("OK", "text/plain", 200);
}

const appserverresponse *handle_api_list_files(appdeps *d,
                                               const appserverrequest *req) {
  if (!check_auth(d, req))
    return d->send_text("Unauthorized", "text/plain", 401);

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

const appserverresponse *router(appdeps *d, void *props) {
  const char *route = d->get_server_route(d->appserverrequest);
  const char *method = d->get_server_method(d->appserverrequest);

  if (d->strcmp(route, "/") == 0 && d->strcmp(method, "GET") == 0) {
    return handle_home(d, d->appserverrequest);
  }

  if (d->strcmp(route, "/database_file") == 0 &&
      d->strcmp(method, "GET") == 0) {
    return handle_database_file(d, d->appserverrequest);
  }

  if (d->strcmp(route, "/list_articles") == 0 &&
      d->strcmp(method, "GET") == 0) {
    return handle_list_articles(d, d->appserverrequest);
  }

  if (d->strcmp(route, "/article") == 0 && d->strcmp(method, "GET") == 0) {
    return handle_article(d, d->appserverrequest);
  }

  if (d->strcmp(route, "/author") == 0 && d->strcmp(method, "GET") == 0) {
    return handle_author(d, d->appserverrequest);
  }

  if (d->strcmp(route, "/about") == 0 && d->strcmp(method, "GET") == 0) {
    return handle_about(d, d->appserverrequest);
  }

  // API
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

  return d->send_text("Not Found", "text/plain", 404);
}

// ===============================SYNC LOGIC====================================

// Fetch remote file list recursively
appjson *fetch_remote_file_list(appdeps *d, const char *url_base,
                                const char *pass) {
  // Construct URL: url_base + /api/list_database_files_recursively
  // url_base might fail if it doesn't end with / or if it has query params
  // simple concat for now
  char *full_url =
      d->concat_path(url_base, "api/list_database_files_recursively");
  // concat_path might use system separator, ensure / for URL
  // But wait, concat_path is system dependent.
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
  d->appclientrequest_set_header(req, "root_password", pass);
  // No path header needed for full recursive list from root

  appclientresponse *resp = d->appclientrequest_fetch(req);
  appjson *result = app_null;

  if (resp) {
    long rsize = 0;
    const unsigned char *rbody = d->appclientresponse_read_body(resp, &rsize);
    if (rbody) {
      char *rstr = d->malloc(rsize + 1);
      d->custom_memcpy(rstr, rbody, rsize);
      rstr[rsize] = 0;
      result = d->json_parse(rstr);
      d->free(rstr);
    }
    d->free_clientresponse(resp);
  }

  d->appclientrequest_free(req);
  d->free(full_url);
  return result;
}

// Get local file list with SHAs
// Get local file list with SHAs
appjson *get_local_file_list(appdeps *d, const char *base_path,
                             const char *cache_dir) {
  appstringarray *files = d->list_files_recursively(base_path);
  appjson *arr = d->json_create_array();

  if (!files)
    return arr;

  long count = d->get_stringarray_size(files);
  for (int i = 0; i < count; i++) {
    const char *f = d->get_stringarray_item(files, i);
    appjson *obj = d->json_create_object();
    d->json_add_string_to_object(obj, "file", f);

    // Calc SHA using cache
    char *full_path = d->concat_path(base_path, f);
    // Use .vibelog_cache in the same directory as the executable?
    // Or in the base_path's parent?
    // Let's use a fixed cache dir relative to base_path for now:
    // base_path/.vibelog_cache Actually the tool
    // char *sha = d->get_cached_file_sha(cache_dir, filepath)
    // char *cache_dir = d->concat_path(base_path, ".vibelog_cache");

    // We shouldn't list files inside .vibelog_cache though.
    // list_files_recursively might include them if not careful.
    // The problem is subsequent runs.
    // We should filter out .vibelog_cache if list_files_recursively returns it.

    if (d->strstr(f, ".vibelog_cache")) {
      d->free(full_path);
      // d->free(cache_dir); // cache_dir is passed in now, don't free it here
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

    // d->free(cache_dir);
    d->free(full_path);
  }
  d->delete_stringarray(files);
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
                           const char *cache_dir) {
  d->printf("Fetching remote file list...\n");
  appjson *remote_list = fetch_remote_file_list(d, url_base, pass);
  if (!remote_list) {
    d->printf("Failed to fetch remote list.\n");
    return;
  }

  d->printf("Scanning local files...\n");
  appjson *local_list = get_local_file_list(d, local_path, cache_dir);

  int count = d->json_get_array_size(remote_list);
  d->printf("Found %d remote files. Synchronizing...\n", count);

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
      // POST /api/read_database_file with header path=f
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
      d->appclientrequest_set_header(req, "root_password", pass);
      d->appclientrequest_set_header(req, "path", f);

      appclientresponse *resp = d->appclientrequest_fetch(req);
      if (resp) {
        long rsize = 0;
        const unsigned char *rbody =
            d->appclientresponse_read_body(resp, &rsize);
        if (rbody) { // Check if we actually got content
          char *save_path = d->concat_path(local_path, f);
          d->write_any(save_path, rbody, rsize);
          d->free(save_path);
          downloaded++;
        } else {
          d->printf("Empty response for %s\n", f);
        }
        d->free_clientresponse(resp);
      } else {
        d->printf("Failed query for %s\n", f);
      }
      d->appclientrequest_free(req);
      d->free(d_url);

    } else {
      skipped++;
    }
  }

  d->printf("Sync Complete. Downloaded: %d, Skipped: %d\n", downloaded,
            skipped);
  d->json_delete(remote_list);
  d->json_delete(local_list);
}

// UPLOAD SYNC
// UPLOAD SYNC
void perform_upload_sync(appdeps *d, const char *local_path,
                         const char *url_base, const char *pass,
                         const char *cache_dir) {
  d->printf("Fetching remote file list...\n");
  appjson *remote_list = fetch_remote_file_list(d, url_base, pass);
  if (!remote_list) {
    d->printf("Failed to fetch remote list.\n");
    return;
  }

  d->printf("Scanning local files...\n");
  appjson *local_list = get_local_file_list(d, local_path, cache_dir);

  int count = d->json_get_array_size(local_list);
  d->printf("Found %d local files. Synchronizing...\n", count);

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
      char *full_path = d->concat_path(local_path, f);
      long fsize = 0;
      appbool is_bin = app_false;
      const unsigned char *content = d->read_any(full_path, &fsize, &is_bin);

      if (content) {
        appclientrequest *req = d->newappclientrequest(u_url);
        d->appclientrequest_set_method(req, "POST");
        d->appclientrequest_set_header(req, "root_password", pass);
        d->appclientrequest_set_header(req, "path", f);
        d->appclientrequest_set_body(req, (unsigned char *)content, fsize);

        appclientresponse *resp = d->appclientrequest_fetch(req);
        if (resp) {
          // assume success if response
          d->free_clientresponse(resp);
          uploaded++;
        } else {
          d->printf("Failed upload for %s\n", f);
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

  d->printf("Sync Complete. Uploaded: %d, Skipped: %d\n", uploaded, skipped);
  d->json_delete(remote_list);
  d->json_delete(local_list);
}

// ===============================MAIN==========================================
// ===============================MAIN==========================================
int appmain(appdeps *d) {
  // Common Flags
  const char *PASS_FLAGS[] = {"root_password", "pass"};
  const char *URL_FLAGS[] = {"url", "u"};
  const char *PATH_FLAGS[] = {"path", "f"};
  const char *CACHE_FLAGS[] = {"cache_dir", "c"};

  // Server Flags
  const char *PORT_FLAGS[] = {"port", "p"};
  const char *DB_FLAGS[] = {"database_path", "db"};

  int argc = d->get_arg_count(d->argv);
  const char *command = app_null;

  if (argc > 1) {
    const char *arg1 = d->get_arg_value(d->argv, 1);
    if (arg1 && d->strlen(arg1) > 0 && arg1[0] != '-') {
      command = arg1;
    }
  }

  // Validate Command
  if (!command) {
    d->printf("Usage: vibelog <command> [options]\n");
    d->printf("Commands:\n");
    d->printf("  start     Start the server (requires --database_path and "
              "--root_password)\n");
    d->printf("  upload    Upload a file (requires --path, --url, "
              "--root_password, optional --cache_dir)\n");
    d->printf("  download  Download a file (requires --path, --url, "
              "--root_password, optional --cache_dir)\n");
    return 1;
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

    // Parse Database Path
    const char *db_path = d->get_arg_flag_value(
        d->argv, DB_FLAGS, sizeof(DB_FLAGS) / sizeof(DB_FLAGS[0]), 0);
    if (db_path) {
      global_config.database_path = d->strdup(db_path);
    } else {
      d->printf("Error: --database_path is required for start command.\n");
      return 1;
    }

    // Parse Root Password
    const char *root_pass = d->get_arg_flag_value(
        d->argv, PASS_FLAGS, sizeof(PASS_FLAGS) / sizeof(PASS_FLAGS[0]), 0);
    if (root_pass) {
      global_config.root_password = d->strdup(root_pass);
    } else {
      d->printf("Error: --root_password is required for start command.\n");
      // Clean up previously allocated db_path
      d->free((void *)global_config.database_path);
      return 1;
    }

    d->printf("Starting VibeLog on port %d\n", global_config.port);
    d->printf("Database path: %s\n", global_config.database_path);

    d->start_server(global_config.port, router, app_null, app_false);

    // Cleanup (unreachable)
    d->free((void *)global_config.database_path);
    d->free((void *)global_config.root_password);
    return 0;
  }

  // COMMAND: UPLOAD
  if (d->strcmp(command, "upload") == 0) {
    const char *db_path = d->get_arg_flag_value(
        d->argv, DB_FLAGS, sizeof(DB_FLAGS) / sizeof(DB_FLAGS[0]), 0);
    // Fallback to path flag if database_path is not set, for backward compat or
    // user convenience
    if (!db_path) {
      db_path = d->get_arg_flag_value(
          d->argv, PATH_FLAGS, sizeof(PATH_FLAGS) / sizeof(PATH_FLAGS[0]), 0);
    }

    const char *url_base = d->get_arg_flag_value(
        d->argv, URL_FLAGS, sizeof(URL_FLAGS) / sizeof(URL_FLAGS[0]), 0);
    const char *pass = d->get_arg_flag_value(
        d->argv, PASS_FLAGS, sizeof(PASS_FLAGS) / sizeof(PASS_FLAGS[0]), 0);

    if (!db_path || !url_base || !pass) {
      d->printf("Usage: vibelog upload --database_path <dir> --url <url> "
                "--root_password <pass>\n");
      return 1;
    }

    if (!d->dir_exists(db_path)) {
      d->printf("Error: Directory not found: %s\n", db_path);
      return 1;
    }

    const char *cache_val = d->get_arg_flag_value(
        d->argv, CACHE_FLAGS, sizeof(CACHE_FLAGS) / sizeof(CACHE_FLAGS[0]), 0);
    if (cache_val) {
      global_config.cache_dir = d->strdup(cache_val);
    } else {
      global_config.cache_dir = d->strdup(".vibelog_cache");
    }

    perform_upload_sync(d, db_path, url_base, pass, global_config.cache_dir);
    d->free((void *)global_config.cache_dir); // Cleanup
    return 0;
  }

  // COMMAND: DOWNLOAD
  if (d->strcmp(command, "download") == 0) {
    const char *db_path = d->get_arg_flag_value(
        d->argv, DB_FLAGS, sizeof(DB_FLAGS) / sizeof(DB_FLAGS[0]), 0);
    // Fallback
    if (!db_path) {
      db_path = d->get_arg_flag_value(
          d->argv, PATH_FLAGS, sizeof(PATH_FLAGS) / sizeof(PATH_FLAGS[0]), 0);
    }

    const char *url_base = d->get_arg_flag_value(
        d->argv, URL_FLAGS, sizeof(URL_FLAGS) / sizeof(URL_FLAGS[0]), 0);
    const char *pass = d->get_arg_flag_value(
        d->argv, PASS_FLAGS, sizeof(PASS_FLAGS) / sizeof(PASS_FLAGS[0]), 0);

    if (!db_path || !url_base || !pass) {
      d->printf("Usage: vibelog download --database_path <dir> --url <url> "
                "--root_password <pass>\n");
      return 1;
    }

    // Create dir if not exists?
    if (!d->dir_exists(db_path)) {
      d->create_dir(db_path);
    }

    const char *cache_val = d->get_arg_flag_value(
        d->argv, CACHE_FLAGS, sizeof(CACHE_FLAGS) / sizeof(CACHE_FLAGS[0]), 0);
    if (cache_val) {
      global_config.cache_dir = d->strdup(cache_val);
    } else {
      global_config.cache_dir = d->strdup(".vibelog_cache");
    }

    perform_download_sync(d, db_path, url_base, pass, global_config.cache_dir);
    d->free((void *)global_config.cache_dir); // Cleanup
    return 0;
  }

  d->printf("Unknown command: %s\n", command);
  d->printf("Available commands: start, upload, download\n");
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
  return "application/octet-stream";
}

void load_global_data(appdeps *d) {
  if (cached_categories == app_null) {
    char *path = d->concat_path(global_config.database_path, "categorys.json");
    if (d->file_exists(path)) {
      cached_categories = d->json_parse_file(path);
    } else {
      // Fallback empty array
      cached_categories = d->json_create_array();
    }
    d->free(path);
  }
}

appjson *calculate_stats(appdeps *d);

char *render_page(appdeps *d, const char *title, const char *content) {
  appctext *t = d->new_ctext(app_null);

  // HEAD
  d->ctext_append(t, "<!DOCTYPE html><html lang='en'><head>");
  d->ctext_append(t, "<meta charset='UTF-8'><meta name='viewport' "
                     "content='width=device-width, initial-scale=1.0'>");
  d->ctext_append(t, "<title>");
  if (title) {
    d->ctext_append(t, title);
    d->ctext_append(t, " - ");
  }
  d->ctext_append(t, "VibeLog</title>");

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
  d->ctext_append(
      t, "<link rel='stylesheet' href='/database_file?path=style.css'>");
  d->ctext_append(t, "</head><body>");

  // NAVBAR
  d->ctext_append(t,
                  "<nav class='navbar'><div class='container navbar-content'>");
  d->ctext_append(t, "<a href='/' class='logo'>VIBELOG_</a>");

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
          d->ctext_append(t,
                          "<a href='/list_articles?page=1&limit=10&category=");
          d->ctext_append(t, name);
          d->ctext_append(t, "' class='nav-link'>");
          d->ctext_append(t, name);
          d->ctext_append(t, "</a>");
        }
      }
    }
  }

  // Categories Dropdown
  d->ctext_append(t, "<div class='dropdown'><button class='btn'>Categories "
                     "▾</button><div class='dropdown-content'>");
  if (cached_categories && d->json_is_array(cached_categories)) {
    int count = d->json_get_array_size(cached_categories);
    for (int i = 0; i < count; i++) {
      appjson *item = d->json_get_array_item(cached_categories, i);
      const char *name =
          d->json_get_string_value(d->json_get_object_item(item, "name"));
      const char *desc = d->json_get_string_value(
          d->json_get_object_item(item, "description"));

      d->ctext_append(t, "<a href='/list_articles?page=1&limit=10&category=");
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
  d->ctext_append(
      t, "<form action='/list_articles' method='GET' class='search-form'>");
  d->ctext_append(t, "<input type='text' name='search' placeholder='Search...' "
                     "class='search-input'>");
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
  appjson *stats = calculate_stats(d);

  d->ctext_append(t, "<div class='sidebar-section'>");
  d->ctext_append(t, "<h3 class='sidebar-title'>Network Status</h3>");

  // Total Views
  double total_views =
      d->json_get_number_value(d->json_get_object_item(stats, "total_views"));
  d->ctext_append(t, "<div class='stat-item'><span class='stat-label'>Total "
                     "Views</span><span class='stat-value'>");
  char tv_buf[64];
  d->custom_sprintf(tv_buf, "%.0f", total_views);
  d->ctext_append(t, tv_buf);
  d->ctext_append(t, "</span></div>");

  d->ctext_append(t, "</div>");

  // Categories Stats
  d->ctext_append(t, "<div class='sidebar-section'>");
  d->ctext_append(t, "<h3 class='sidebar-title'>Traffic / Sector</h3>");

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
  d->ctext_append(t, "VIBELOG SYSTEM © 2026 // NO RIGHTS RESERVED");
  d->ctext_append(t, "</div></footer>");

  d->ctext_append(t, "</body></html>");

  char *res = d->strdup(d->ctext_get_text(t));
  d->ctext_free(t);
  return res;
}

long parse_date_to_ts(appdeps *d, const char *date) {
  // DD-MM-YYYY -> YYYYMMDD
  if (d->strlen(date) != 10)
    return 0;
  // Simple manual parsing
  char year[5] = {0};
  char month[3] = {0};
  char day[3] = {0};

  day[0] = date[0];
  day[1] = date[1];
  month[0] = date[3];
  month[1] = date[4];
  year[0] = date[6];
  year[1] = date[7];
  year[2] = date[8];
  year[3] = date[9];

  char buf[20];
  d->custom_sprintf(buf, "%s%s%s", year, month, day);
  return d->atoi(buf);
}

appjson *load_articles(appdeps *d, int page, int limit, const char *category,
                       const char *search, const char *author_id) {
  appjson *results = d->json_create_array();

  // 1. List Dates (database/articles/DD-MM-YYYY)
  char *articles_root = d->concat_path(global_config.database_path, "articles");
  appstringarray *dates = d->list_dirs(articles_root);
  d->free(articles_root);

  if (!dates)
    return results;

  long dates_count = d->get_stringarray_size(dates);

  // Temporary storage for sorting
  // Since we don't have a dynamic array struct, we will use appjson to store
  // them and then sort
  appjson *all_articles = d->json_create_array();

  for (int i = 0; i < dates_count; i++) {
    const char *date_str = d->get_stringarray_item(dates, i);
    long ts = parse_date_to_ts(d, date_str);

    // List Articles in that date
    char *date_path = d->concat_path(global_config.database_path, "articles");
    char *tmp = d->concat_path(date_path, date_str);
    d->free(date_path);
    date_path = tmp;

    appstringarray *article_ids = d->list_dirs(date_path);
    if (article_ids) {
      long arts_count = d->get_stringarray_size(article_ids);
      for (int j = 0; j < arts_count; j++) {
        const char *aid = d->get_stringarray_item(article_ids, j);

        // Load data.json
        char *art_path = d->concat_path(date_path, aid);
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
                  const char *cname =
                      d->json_get_string_value(d->json_get_array_item(cats, c));
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
    d->free(date_path);
  }
  d->delete_stringarray(dates);

  // SORTING (Bubble Sort on appjson array by 'ts' desc)
  int total = d->json_get_array_size(all_articles);
  for (int i = 0; i < total - 1; i++) {
    for (int j = 0; j < total - i - 1; j++) {
      appjson *a = d->json_get_array_item(all_articles, j);
      appjson *b = d->json_get_array_item(all_articles, j + 1);
      double tsa = d->json_get_number_value(d->json_get_object_item(a, "ts"));
      double tsb = d->json_get_number_value(d->json_get_object_item(b, "ts"));

      if (tsa < tsb) { // Descending
        appjson *a_clone = d->json_duplicate(a, app_true);
        appjson *b_clone = d->json_duplicate(b, app_true);
        d->json_replace_item_in_array(all_articles, j, b_clone);
        d->json_replace_item_in_array(all_articles, j + 1, a_clone);
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
appjson *calculate_stats(appdeps *d) {
  appjson *stats = d->json_create_object();
  d->json_add_number_to_object(stats, "total_views", 0);
  appjson *cats = d->json_create_array(); // Array of {name, views}
  d->json_add_item_to_object(stats, "categories", cats);

  // Iterate all articles
  char *articles_root = d->concat_path(global_config.database_path, "articles");
  d->printf("Debug: Articles root: %s\n", articles_root);
  appstringarray *dates = d->list_dirs(articles_root);
  d->free(articles_root);

  if (!dates) {
    d->printf("Debug: No dates found\n");
    return stats;
  }

  long dates_count = d->get_stringarray_size(dates);
  d->printf("Debug: Dates count: %ld\n", dates_count);
  double total_views = 0;

  for (int i = 0; i < dates_count; i++) {
    const char *date_str = d->get_stringarray_item(dates, i);
    char *date_path = d->concat_path(global_config.database_path, "articles");
    char *tmp = d->concat_path(date_path, date_str);
    d->free(date_path);
    date_path = tmp;

    appstringarray *article_ids = d->list_dirs(date_path);
    if (article_ids) {
      long arts_count = d->get_stringarray_size(article_ids);
      d->printf("Debug: Date %s has %ld articles\n", date_str, arts_count);
      for (int j = 0; j < arts_count; j++) {
        const char *aid = d->get_stringarray_item(article_ids, j);

        // 1. Get Categories
        char *art_path = d->concat_path(date_path, aid);
        char *json_path = d->concat_path(art_path, "data.json");

        appjson *art_data = app_null;
        if (d->file_exists(json_path)) {
          art_data = d->json_parse_file(json_path);
        }
        d->free(json_path);

        // 2. Get Views
        char *metrics_root =
            d->concat_path(global_config.database_path, "metrics");
        char *art_metrics = d->concat_path(metrics_root, "articles");
        d->free(metrics_root);
        char *m_date_dir = d->concat_path(art_metrics, date_str);
        d->free(art_metrics);
        char *m_id_dir = d->concat_path(m_date_dir, aid);
        d->free(m_date_dir);
        char *views_file = d->concat_path(m_id_dir, "total_views.json");
        d->free(m_id_dir);

        double views = 0;
        if (d->file_exists(views_file)) {
          d->printf("Debug: Found views file: %s\n", views_file);
          appjson *v_json = d->json_parse_file(views_file);
          if (v_json) {
            views = d->json_get_number_value(
                d->json_get_object_item(v_json, "views"));
            d->printf("Debug: Views: %f\n", views);
            d->json_delete(v_json);
          }
        } else {
          d->printf("Debug: Views file not found: %s\n", views_file);
        }
        d->free(views_file);

        total_views += views;

        // Aggregate Categories (Linear Scan on Array)
        if (art_data) {
          appjson *c_arr = d->json_get_object_item(art_data, "categories");
          if (c_arr && d->json_is_array(c_arr)) {
            int c_count = d->json_get_array_size(c_arr);
            for (int k = 0; k < c_count; k++) {
              const char *cname =
                  d->json_get_string_value(d->json_get_array_item(c_arr, k));
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
                        cat_obj, "views", d->json_create_number(cv + views));
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
    d->free(date_path);
  }
  d->delete_stringarray(dates);

  d->json_replace_item_in_object(stats, "total_views",
                                 d->json_create_number(total_views));
  return stats;
}

appjson *load_author(appdeps *d, const char *author_id) {
  char *path = d->concat_path(global_config.database_path, "authors");
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

void record_view(appdeps *d, const char *date, const char *id) {
  // 1. Setup paths
  char *metrics_root = d->concat_path(global_config.database_path, "metrics");
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
  d->get_formatted_time(now, date_buf, 64, "%d-%m-%Y");

  char day_dir_name[128];
  d->custom_sprintf(day_dir_name, "%s:%ld", date_buf,
                    now); // Just use current TS

  char *day_path = d->concat_path(views_dir, day_dir_name);
  if (!d->dir_exists(day_path))
    d->create_dir(day_path);

  // View File
  appjson *view = d->json_create_object();
  char iso_buf[64];
  d->get_formatted_time(now, iso_buf, 64, "%Y-%m-%dT%H:%M:%SZ");
  d->json_add_string_to_object(view, "date", iso_buf);
  d->json_add_string_to_object(view, "country", "unknown");
  d->json_add_string_to_object(view, "device", "unknown");
  d->json_add_number_to_object(view, "duration", 0);

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
