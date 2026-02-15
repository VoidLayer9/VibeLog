//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.globals.h"
//silver_chain_scope_end


void *wrapper_new_text_stack(const char *text) {
  if (text == NULL) {
    return newCTextStack_string_empty();
  }
  return newCTextStack_string(text);
}

void wrapper_text_stack_append(void *text_stack, const char *text) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_text(stack, text);
}

const char *wrapper_text_stack_text(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  return stack->rendered_text;
}

void wrapper_text_stack_free(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_free(stack);
}

void wrapper_text_stack_restart(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_restart(stack);
}

void *wrapper_text_stack_clone(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  return CTextStack_clone(stack);
}

void wrapper_text_stack_self_substr(void *text_stack, long starter, long end) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_substr(stack, starter, end);
}

void wrapper_text_stack_self_pop(void *text_stack, long starter, long end) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_pop(stack, starter, end);
}

void wrapper_text_stack_self_insert_at(void *text_stack, long point,
                                       const char *element) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_insert_at(stack, point, element);
}

void wrapper_text_stack_self_replace(void *text_stack, const char *element,
                                     const char *element_to_replace) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_replace(stack, element, element_to_replace);
}

void wrapper_text_stack_self_replace_long(void *text_stack, const char *element,
                                          long element_to_replace) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_replace_long(stack, element, element_to_replace);
}

void wrapper_text_stack_self_replace_double(void *text_stack,
                                            const char *element,
                                            double element_to_replace) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_replace_double(stack, element, element_to_replace);
}

void wrapper_text_stack_self_lower(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_lower(stack);
}

void wrapper_text_stack_self_upper(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_upper(stack);
}

void wrapper_text_stack_self_captalize(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_captalize(stack);
}

void wrapper_text_stack_self_reverse(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_reverse(stack);
}

void wrapper_text_stack_self_trim(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  CTextStack_self_trim(stack);
}

int wrapper_text_stack_starts_with(void *text_stack, const char *element) {
  CTextStack *stack = (CTextStack *)text_stack;
  return (int)CTextStack_starts_with(stack, element);
}

int wrapper_text_stack_ends_with(void *text_stack, const char *element) {
  CTextStack *stack = (CTextStack *)text_stack;
  return (int)CTextStack_ends_with(stack, element);
}

int wrapper_text_stack_equal(void *text_stack, const char *element) {
  CTextStack *stack = (CTextStack *)text_stack;
  return (int)CTextStack_equal(stack, element);
}

int wrapper_text_stack_typeof_element(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  return CTextStack_typeof(stack);
}

int wrapper_text_stack_is_a_num(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  return (int)CTextStack_is_a_num(stack);
}

const char *wrapper_text_stack_typeof_in_str(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  return CTextStack_typeof_in_str(stack);
}

int wrapper_text_stack_parse_to_bool(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  return (int)CTextStack_parse_to_bool(stack);
}

long wrapper_text_stack_parse_to_integer(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  return CTextStack_parse_to_integer(stack);
}

double wrapper_text_stack_parse_to_double(void *text_stack) {
  CTextStack *stack = (CTextStack *)text_stack;
  return CTextStack_parse_to_double(stack);
}

long wrapper_text_stack_index_of(void *text_stack, const char *element) {
  CTextStack *stack = (CTextStack *)text_stack;
  return CTextStack_index_of(stack, element);
}

long wrapper_text_stack_index_of_char(void *text_stack, char element) {
  CTextStack *stack = (CTextStack *)text_stack;
  return CTextStack_index_of_char(stack, element);
}
