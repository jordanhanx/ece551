#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

// struct: array of substrings splitted by '_' from a line, and array's size
struct str_arr_tag {
  char ** arr;
  size_t num;
};
typedef struct str_arr_tag str_arr_t;

// struct: array of name-word-pair divided by ':' from a line
struct n_w_pair_tag {
  char * name;
  char * word;
};
typedef struct n_w_pair_tag n_w_pair_t;

//any functions you want your main to use

//=============================== Step 1 ====================================//
str_arr_t * parse_story_line(const char * const line);
void free_string_array(str_arr_t * str_arr);
void print_string_array(const str_arr_t * const str_arr,
                        catarray_t * cats,
                        category_t * const used_words_list,
                        const int flag_no_reuse);
void parse_story(FILE * f, catarray_t * cats, const int flag_no_reuse);

//=============================== Step 2 ====================================//
n_w_pair_t * parse_words_line(const char * const line);
void free_n_w_pair(n_w_pair_t * pair);
ssize_t find_category_index(const catarray_t * const cats, const char * const cat_name);
void add_category(catarray_t * const cats, const char * const cat_name);
void add_word_to_category(category_t * const category, const char * const word);
void update_catarray(catarray_t * const cats, const n_w_pair_t * const pair);
void free_catarray(catarray_t * cats);
catarray_t * parse_catarray(FILE * f);

//=============================== Step 3 ====================================//
const char * blank_filler(char * cat_name,
                          catarray_t * cats,
                          category_t * const used_words_list,
                          const int flag_no_reuse);
const char * update_used_words_list(category_t * const used_words_list,
                                    const char * const word);
void free_used_words_list(category_t * used_words_list);

//=============================== Step 4 ====================================//
void remove_word_from_category(category_t * const category, const char * const word);
void remove_used_word(catarray_t * const cats,
                      const char * const cat_name,
                      const char * const word);

#endif
