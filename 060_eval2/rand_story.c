#include "rand_story.h"
//=============================== Step 1 ====================================//
/*****************************************************************************
 * Function: Split a line into an array of strings by '_', and every string  *
 *           between two '_' includes the begin '_' only, no end '_'.        *
 * Parameters: (1)const char * const line: a pointer to a string.            *
 * Return value: a pointer to struct strs_t in heap, which includes an array *
 *               of strings and the size of the array.                       *
 *****************************************************************************/
str_arr_t * parse_story_line(const char * const line) {
  str_arr_t * ans = malloc(sizeof(*ans));
  ans->arr = NULL;
  ans->num = 0;
  size_t len = strlen(line);
  size_t i = 0;    // start position of each substring
  size_t blk = 0;  // single blank flag
  // extract substrings
  for (size_t j = 0; j <= len; j++) {
    if ((line[j] == '_') || (j == len)) {
      // check substring's length before reallocation
      if (j - i > 0) {
        ans->arr = realloc(ans->arr, (ans->num + 1) * sizeof(*ans->arr));
        ans->arr[ans->num] = strndup(&line[i], j - i);
        ans->num++;
      }
      // if read '\0', then finish the loop
      if (j == len) {
        break;
      }
      else if (blk == 0) {
        i = j;  // the substring after a begin '_' includes the '_'
        blk++;  // set single blank flag
      }
      else {
        i = j + 1;  // the substring after a end '_' doesn't include the '_'
        blk--;      // clear single blank flag
      }
    }
  }
  if (blk != 0) {
    fprintf(stderr, "ERROR_single_blank : %s\n", line);
    exit(EXIT_FAILURE);
  }
  return ans;
}

/*****************************************************************************
 * Function: Free the memory allocated to the str_arr.                       *
 * Parameters: (1)const char * const line: a pointer to a struct str_arr_t.  *            
 *****************************************************************************/
void free_string_array(str_arr_t * str_arr) {
  for (size_t i = 0; i < str_arr->num; i++) {
    free(str_arr->arr[i]);
  }
  free(str_arr->arr);
  free(str_arr);
}

/*****************************************************************************
 * Function: Print the strings in the array one by one and replace the       *
 *           strings that have a begin '_' using the catarray correctly.     *
 * Parameters: (1)const str_arr_t * const str_arr : a pointer to a str_arr.  *
 *             (2)catarray_t * cats : a pointer to a catarray_t.             *
 *             (3)category_t * const used_words_list : a pointer to a used_  *
 *                words_list.                                                *
 *             (4)const int flag_no_reuse : a flag indicating whether reuse  *
 *                words.                                                     *
 *****************************************************************************/
void print_string_array(const str_arr_t * const str_arr,
                        catarray_t * cats,
                        category_t * const used_words_list,
                        const int flag_no_reuse) {
  for (size_t i = 0; i < str_arr->num; i++) {
    // in strs_t, all the blanks(strings) which should be replaced start with a '_'
    if (*str_arr->arr[i] == '_') {
      // if cats = NULL, fill blank using chooseWord' default value directly
      if (cats == NULL) {
        printf("%s", chooseWord(str_arr->arr[i] + 1, cats));
      }
      // else, fill blank with appropriate word: used_word or chooseWord
      else {
        printf("%s",
               blank_filler(str_arr->arr[i] + 1, cats, used_words_list, flag_no_reuse));
      }
    }
    // non-blank strings, print it directly
    else {
      printf("%s", str_arr->arr[i]);
    }
  }
}

/*****************************************************************************
 * Function: Read a story template and use a catarray to fill blanks, gener- *
 *           ate a story at the end.                                         *
 * Parameters: (1)FILE * f : a stream to the opened file                     *
 *             (2)catarray_t * cats : a pointer to a catarray_t.             *
 *             (3)const int flag_no_reuse : a flag indicating whether reuse  *
 *                words.                                                     *
 *****************************************************************************/
void parse_story(FILE * f, catarray_t * cats, const int flag_no_reuse) {
  str_arr_t * str_arr = NULL;
  category_t * used_words_list = malloc(sizeof(*used_words_list));
  used_words_list->name = NULL;
  used_words_list->words = NULL;
  used_words_list->n_words = 0;
  char * curr = NULL;
  size_t sz = 0;
  while (getline(&curr, &sz, f) >= 0) {
    str_arr = parse_story_line(curr);  // split line into substrings
    print_string_array(str_arr, cats, used_words_list, flag_no_reuse);
    free_string_array(str_arr);
    free(curr);
    curr = NULL;
  }
  free(curr);
  free_used_words_list(used_words_list);  // free the used-words-list
}

//=============================== Step 2 ====================================//
/*****************************************************************************
 * Function: Split a line into a pair of name and word by ':'.               *
 * Parameters: (1)const char * const line: a pointer to a string.            *
 * Return value: a pointer to struct n_w_pair_t in heap, which includes a    *
 *               pair of name(string) and word(string)                       *
 *****************************************************************************/
n_w_pair_t * parse_words_line(const char * const line) {
  n_w_pair_t * pair = malloc(sizeof(*pair));
  char * end_ptr = strchr(line, '\n');
  char * colon_ptr = strchr(line, ':');
  if (colon_ptr == NULL) {
    fprintf(stderr, "ERROR_colon_absence : %s\n", line);
    exit(EXIT_FAILURE);
  }
  size_t copy_len_name = colon_ptr - line;
  size_t copy_len_word = end_ptr - (colon_ptr + 1);  // skip ':'
  pair->name = strndup(line, copy_len_name);
  pair->word = strndup(colon_ptr + 1, copy_len_word);
  return pair;
}

/*****************************************************************************
 * Function: Free the memory allocated to the name-word-pair.                *
 * Parameters: (1)n_w_pair_t * pair: a pointer to a struct n_w_pair_t.       *
 *****************************************************************************/
void free_n_w_pair(n_w_pair_t * pair) {
  free(pair->name);
  free(pair->word);
  free(pair);
}

/*****************************************************************************
 * Function: Scan the given catacarry to find a category matched with the    *
 *           given name, return the index of the category.                   *
 * Parameters: (1)const catarray_t const * cats : a pointer to a catarray_t. *
 *             (2)const char * const cat_name : a pointer to a name(string). *
 * Return value: the index of the matched category, return -1 if didn't find *
 *               a matched category.                                         *
 *****************************************************************************/
ssize_t find_category_index(const catarray_t * const cats, const char * const cat_name) {
  // declare a box to store the index of matched category(name)
  ssize_t idx_cat = -1;  // if didn't find a matched category, return -1
  // find the indices of the matched category(name) and word
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(cats->arr[i].name, cat_name) == 0) {
      idx_cat = i;  // store the idex of the matched category(name)
      break;
    }
  }
  return idx_cat;
}

/*****************************************************************************
 * Function: Add a new category into the given catarray.                     *
 * Parameters: (1)catarray_t * const cats : a pointer to a catarray_t.       *
 *             (2)const char * const cat_name : a pointer to a name(string). *
 *****************************************************************************/
void add_category(catarray_t * const cats, const char * const cat_name) {
  cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
  cats->arr[cats->n].name = strdup(cat_name);
  cats->arr[cats->n].words = NULL;
  cats->arr[cats->n].n_words = 0;
  cats->n++;
}

/*****************************************************************************
 * Function: Add a new word into the given category.                         *
 * Parameters: (1)category_t * const category : a pointer to a category_t.   *
 *             (2)const char * const word : a pointer to a word(string).     *
 *****************************************************************************/
void add_word_to_category(category_t * const category, const char * const word) {
  category->words =
      realloc(category->words, (category->n_words + 1) * sizeof(*category->words));
  category->words[category->n_words] = strdup(word);
  category->n_words++;
}

/*****************************************************************************
 * Function: Update the given catarray using category name and word in name- *
 *           word-pair.                                                      *
 * Parameters: (1)catarray_t * const cats : a pointer to a catarray_t.       *
 *             (2)n_w_pair_t * pair: a pointer to a struct n_w_pair_t.       *
 *****************************************************************************/
void update_catarray(catarray_t * const cats, const n_w_pair_t * const pair) {
  ssize_t idx_cat = 0;  // a box to store the index of matched category(name)
  // (1) find an identical category(name)
  idx_cat = find_category_index(cats, pair->name);
  // (2) if didn't find the category(name), append a new one
  if (idx_cat == -1) {
    add_category(cats, pair->name);
    idx_cat = cats->n - 1;
  }
  // (3) add a new word
  add_word_to_category(&cats->arr[idx_cat], pair->word);
}

/*****************************************************************************
 * Function: Free the memory allocated to the catarray.                      *
 * Parameters: (1)catarray_t * const cats : a pointer to a catarray_t.       *
 *****************************************************************************/
void free_catarray(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].name);
    free(cats->arr[i].words);
  }
  free(cats->arr);
  free(cats);
}

/*****************************************************************************
 * Function: Read a words file and create a catarray.                        *
 * Parameters: (1)FILE * f : a stream to the opened file                     *
 * Return value: a pointer to the catarray in heap.                          *
 *****************************************************************************/
catarray_t * parse_catarray(FILE * f) {
  catarray_t * cats = malloc(sizeof(*cats));
  cats->arr = NULL;
  cats->n = 0;
  char * curr = NULL;
  size_t sz = 0;
  while (getline(&curr, &sz, f) >= 0) {
    n_w_pair_t * pair = parse_words_line(curr);
    update_catarray(cats, pair);
    free_n_w_pair(pair);
    free(curr);
    curr = NULL;
  }
  free(curr);
  return cats;
}

//=============================== Step 3 ====================================//
/*****************************************************************************
 * Function: Check the input string and return the correct answer string by  *
 *           looking up the given catarray and used_words_list, and update   *
 *           used_words_list and the given catarray.                         *
 * Parameters: (1)char * cat_name : a pointer to a string.                   *
 *             (2)catarray_t * const cats : a pointer to a catarray_t.       *
 *             (3)category_t * const used_words_list : a pointer to the spe- *
 *                cial category_t -- used_words_list.                        *
 *             (4)const int flag_no_reuse : a flag indicating whether reuse  *
 *                words.                                                     * 
 * Return value: a pointer to the string in used_words_list.                 *
 *****************************************************************************/
const char * blank_filler(char * cat_name,
                          catarray_t * cats,
                          category_t * const used_words_list,
                          const int flag_no_reuse) {
  const char * word = NULL;
  const char * ans = NULL;
  int flag_chooseWord = 0;  // flag: whether the chooseWord() has been used
  // (0) convert char number into int, while checking overflow
  char * endptr = NULL;
  long long int n_back = strtoll(cat_name, &endptr, 10);
  if (n_back == LLONG_MAX) {
    fprintf(stderr, "ERROR_strtoll_overflow: %s\n", cat_name);
    exit(EXIT_FAILURE);
  }
  // conditional check:
  // (1) when the entire string is valid number and it's greater than the length of used-words
  if ((*endptr == '\0') && (n_back > (long long int)used_words_list->n_words)) {
    fprintf(stderr,
            "ERROR_backreference_out_of_range(%lu): %s\n",
            used_words_list->n_words,
            cat_name);
    exit(EXIT_FAILURE);
  }
  // (2) when the entire string is valid number and 0 < the number < the length of used-words
  else if ((*endptr == '\0') && (n_back > 0)) {
    word = used_words_list->words[used_words_list->n_words - n_back];
  }
  // (3) else, choose word from sturct catarray_t using the input string
  else {
    word = chooseWord(cat_name, cats);
    flag_chooseWord = 1;
  }
  // before return:
  // <1> append the new ans to the used-words
  ans = update_used_words_list(used_words_list, word);
  // <2> if flag_no_reuse is set AND the used word came from chooseWord(),
  //     remove it from struct catarr
  if ((flag_no_reuse == 1) && (flag_chooseWord == 1)) {
    remove_used_word(cats, cat_name, word);
  }
  return ans;
}

/*****************************************************************************
 * Function: Append the given string to the used_words_list, then return a   *
 *           pointer to the newest word of the used_words_list.              *
 * Parameters: (1)category_t * const used_words_list : a pointer to the spe- *
 *                cial category_t -- used_words_list.                        *
 *             (2)const char * const word : a pointer to a string.           *
 * Return value: a pointer to the newest word of the used_words_list.        *
 *****************************************************************************/
const char * update_used_words_list(category_t * const used_words_list,
                                    const char * const word) {
  used_words_list->words =
      realloc(used_words_list->words,
              (used_words_list->n_words + 1) * sizeof(*used_words_list->words));
  used_words_list->words[used_words_list->n_words] = strdup(word);
  used_words_list->n_words++;
  // return a pointer the newest word in used_words
  return used_words_list->words[used_words_list->n_words - 1];
}

/*****************************************************************************
 * Function: Free the memory allocated to the special category_t--used_word- *    
 *           s_list.                                                         *
 * Parameters: (1)category_t * const used_words_list : a pointer to the spe- *
 *                cial category_t -- used_words_list.                        *
 *****************************************************************************/
void free_used_words_list(category_t * used_words) {
  for (size_t i = 0; i < used_words->n_words; i++) {
    free(used_words->words[i]);
  }
  free(used_words->name);
  free(used_words->words);
  free(used_words);
}

//=============================== Step 4 ====================================//
/*****************************************************************************
 * Function: Remove a word from the given category.                          *
 * Parameters: (1)category_t * const category : a pointer to a category_t.   *
 *             (2)const char * const word : a pointer to a word(string).     *
 *****************************************************************************/
void remove_word_from_category(category_t * const category, const char * const word) {
  // find the index of the matched word
  ssize_t idx_word = -1;
  for (size_t j = 0; j < category->n_words; j++) {
    if (strcmp(category->words[j], word) == 0) {
      idx_word = j;  // store the idex of the first matched word
      break;
    }
  }
  // free the matched word
  free(category->words[idx_word]);
  // redirect pointers(from idx_word to end) to point to the next pointer's destination
  for (size_t k = idx_word; k < category->n_words - 1; k++) {
    category->words[k] = category->words[k + 1];
  }
  // update length
  category->n_words--;
  // reallocate the array of words
  if (category->n_words != 0) {
    category->words =
        realloc(category->words, (category->n_words) * sizeof(*category->words));
  }
  // if no words in this category, free the array.
  else {
    free(category->words);
    category->words = NULL;
  }
}

/*****************************************************************************
 * Function: Remove used word from the given catarray in case reuse.         *
 * Parameters: (1)catarray_t * const cats : a pointer to a catarray_t.       *
 *             (2)const char * const cat_name : a pointer to a anme(string). *
 *             (3)const char * const word : a pointer to a word(string).     *
 *****************************************************************************/
void remove_used_word(catarray_t * const cats,
                      const char * const cat_name,
                      const char * const word) {
  ssize_t idx_cat = find_category_index(cats, cat_name);
  remove_word_from_category(&cats->arr[idx_cat], word);
}

//================================  EOF  ====================================//
