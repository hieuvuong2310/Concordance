/*
 * concord3.c
 *
 * Starter file provided to students for Assignment #3, SENG 265,
 * Summer 2021
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "emalloc.h"
#include "seng265-list.h"
node_t* filter_the_file(node_t* ,  node_t* );
int in_it(node_t* , char *);
void convert_to_lower(char* s);
void convert_to_upper(char* s);
int find_longest(node_t *);
int count_freq(char *, char *, char *, int );
void in_line(char *,  node_t *, node_t*, int );
void print_output(node_t*  , node_t *, node_t* , int );
void free_the_list(node_t *);
void print_word(node_t *node, void *arg)
{
    char *format = (char *)arg;
    printf(format, node->text);
}

#define MAX_LINE_LEN 100
#define MAX_WORD_LEN 40
int main(int argc, char *argv[])
{
    char *exception_file = NULL;
    char *input_file = NULL;
    int i;
    int nums1 = 0;
    int nums2 = 0;
    char *line_for_lang;
    char *line_handle;
    node_t *data_language = NULL;
    node_t *data_handle = NULL;
    node_t *temp = NULL;
    line_for_lang = (char *)emalloc(sizeof(char)*MAX_LINE_LEN);
    line_handle = (char *)emalloc(sizeof(char)*MAX_LINE_LEN);

    if(argc<2){
        fprintf(stderr, "You should provide a filename\n");
        exit(1);
    }
    if(argc==2){
        exception_file = "";
        input_file = argv[1];
    }else{
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i+i <= argc) {
            exception_file = argv[++i];
        } else {
            input_file = argv[i];
        }
    }
    }
    FILE *file_language = fopen(exception_file, "r");
    FILE *file_handle = fopen(input_file, "r");
    if(file_language==NULL){ // this is where we handle if there is no exclusion file
        temp = new_node("");
        data_language= add_end(data_language, temp);
    }else{
            while(fgets(line_for_lang, MAX_LINE_LEN, file_language)!=NULL){// store the words in exclusion file
                line_for_lang[strlen(line_for_lang)-1] = '\0'; // remove the new line at the end of each word
                temp = new_node(line_for_lang); 
                data_language = add_end(data_language, temp);// add the word to a list
                nums1++;
            }
        
    }
    if(file_handle == NULL){
        exit(1);
    }
    while(fgets(line_handle, MAX_LINE_LEN, file_handle)){//store the input file
        line_handle[strlen(line_handle)-1]='\0';//remove the new line at the end of each sentence
        temp = new_node(line_handle);
        data_handle = add_end(data_handle, temp);//add all the sentence to a list
        nums2++;
    }

    node_t *temp1 = NULL;
    node_t *temp2 = NULL;
    node_t *head = NULL;
    node_t *copy_list_from_file_input = NULL;
    node_t *cur = NULL;
    cur = data_handle;
    for(cur = data_handle; cur!=NULL; cur= cur->next){
        temp1 = new_node(cur->text);
        temp2 = new_node(cur->text);
        head = add_end(head, temp1);//copy a list to a new list named head
        copy_list_from_file_input = add_end(copy_list_from_file_input, temp2);//copy a list to a new list named copy_list_from_file_input
    }
    node_t *after_filter = NULL;
    after_filter = filter_the_file(head, data_language); //the list that contains accepted keywords
    int longest = 0;
    longest = find_longest(after_filter); // find the longest word in the after_filter list
    print_output(after_filter, copy_list_from_file_input, data_handle, longest); // print the output
    //free all lists after use
    free_the_list(head);
    free_the_list(data_language);
    free_the_list(data_handle);
    free_the_list(after_filter);
    free_the_list(copy_list_from_file_input);

    if(line_for_lang){free(line_for_lang);}
    if(line_handle){free(line_handle);}
    if(file_language != NULL){
        fclose(file_language); // close the exception file
    }
    fclose(file_handle);//close the input file
    exit(0);
}
void free_the_list(node_t *list){
    /*this function is to free all the list after use*/
    node_t *temp_node = list;
    while (temp_node != NULL) {
        assert(temp_node != NULL);
        list = remove_front(list);
        free(temp_node);
        temp_node = list;
    }
   
    assert(list == NULL);
}
int in_it(node_t* list, char *word){
    /*This function is to determine whether the word is already in the list or not
    if yes it will return 1, otherwise it will return 0
    */
    node_t *cur = NULL;
    for(cur =list; cur!=NULL; cur = cur->next){
        if(strcmp(word, cur->text)==0){
            return 1;
        }
    }
    return 0;
}
node_t* filter_the_file(node_t *head, node_t* content_language){
    /*This function is to get the accepted keywords. If the word is not in the exception file it 
    will be added to the list in order of alphabet. Each keyword will be only one in the list
    Then return the list has all accepted keyword in it
    */
    node_t* new_list = NULL;
    node_t* node = NULL;
    node_t* cur =NULL;
    char *s;
    for(cur = head; cur != NULL; cur= cur->next){
        s = strtok(cur->text, " ");
        while(s != NULL){
            convert_to_lower(s);
            if(in_it(content_language, s)==0){
                if(in_it(new_list, s)==0){
                    node =new_node(s);
                    new_list = add_inorder(new_list, node);//add the keyword into the list
                } 
            }
            s = strtok(NULL, " ");
        }
    }
    return new_list;
}
void convert_to_lower(char *s){
    /*This function is to convert the word to lowercase
    */
    for(int i = 0; s[i]!='\0'; i++){
        if(s[i]>='A' && s[i]<='Z'){
            s[i] += 32; // in the ascii code the lowercase word will be 32 number after the uppercase one
        }
    }
}
void convert_to_upper(char* s){
    /*This function is to conver the word to UPPERCASE
    */
    for(int i = 0; s[i]!='\0'; i++){
        if(s[i]>='a' && s[i]<='z'){
            s[i] -= 32; // the UPPERCASE will be 32 numbers before the lowercase
        }
    }
}
int find_longest(node_t *list){
    /* This function is to find the longest keyword in a keyword list, and return the length of the longest word
    */
    node_t* cur = NULL;
    int start = 0;
    for(cur = list; cur!=NULL; cur = cur->next){
        if(strlen(cur->text)>start){
            start = strlen(cur->text);
        }
    }
    return start;
}
void print_output(node_t* list_filtered, node_t *list_handle, node_t* data_handle, int longest){
    /*This function is to print the output. First it loop through to get the keyword and pass it to the in_line 
    function
    Note that list_handle and data_handle is the copy of each other
    */
    node_t *cur=NULL;
    for(cur = list_filtered; cur!=NULL; cur=cur->next){
        in_line(cur->text, list_handle, data_handle, longest);
    }
}
void in_line(char *filtered_word, node_t *list_handle, node_t* data_handle, int longest){
    /*This function is to determine the line number that the keyword appear and how many times it appears in the
    line. 
    */
    node_t *cur=NULL;
    node_t *curr = NULL;
    curr = data_handle;
    int i = 0;
    for(cur = list_handle; cur!=NULL; cur = cur->next){
        int counter = 0;
        counter = count_freq(filtered_word, cur->text, curr->text, longest);
        if(counter == 1){
            printf(" (%d)\n", i+1);
        }else if(counter >1){
            printf(" (%d%s)\n", i+1, "*\0");
        }
        curr = curr->next;
        i++;
    }
}
int count_freq(char *filtered_word, char *sentence, char *copy_sentence, int longest){
    /*This function is to count the frequency of the word appear in the line.
    It also print the output, if the word is in which line it will print the word in UPPERCASE separated by space
    with the sentence.
    This function will return a count of the frequency of that number, help us to determine whether should print 
    the * after the line number or not in the in_line function
    */
    int counter = 0; 
    char *elements;
    int w;
    elements = strtok(copy_sentence, " ");
    while(elements){
        convert_to_lower(elements);//convert the element to lower make it easy to compare word by word
        if(strcmp(filtered_word, elements)==0){
            convert_to_upper(filtered_word);// convert to upper to print
            w = longest+2-strlen(filtered_word);
            counter++;
            if(counter == 1){
                printf("%s", filtered_word);
                for(int j = 0; j<w; j++){
                    printf(" ");
                }
                printf("%s", sentence);
            }
        }
        convert_to_lower(filtered_word);//convert the word to lower again to make sure that the keyword remain the same after use
        elements = strtok(NULL, " ");
    }
    strncpy(copy_sentence, sentence, strlen(sentence));//make sure the copy_sentence remain the same after use
    return counter;
}
