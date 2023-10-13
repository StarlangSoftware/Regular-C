//
// Created by Olcay Taner YILDIZ on 9.10.2023.
//

#include <stdlib.h>
#include <StringUtils.h>
#include <Dictionary/Word.h>
#include <string.h>
#include <stdio.h>
#include <Stack.h>
#include "RegularExpression.h"

static char* keyboard_characters = "abcçdefgğhıijklmnoöpqrsştuüvwxyzABCÇDEFGĞHIİJKLMNOÖPQRSŞTUÜVWXYZ0123456789_:,;/=<>£#${}`@&%^!";
static char* special_characters = ".()[]|-\\?+*";

Regular_expression_ptr create_regular_expression(char *expression) {
    Regular_expression_ptr result = malloc(sizeof(Regular_expression));
    result->expression = str_copy(result->expression, expression);
    result->automaton = convert_to_nfa(expression);
    return result;
}

void free_regular_expression(Regular_expression_ptr regular_expression) {
    free(regular_expression->expression);
    free_automaton(regular_expression->automaton);
    free(regular_expression);
}

State_ptr create_new_state(Automaton_ptr automaton, int* index){
    char name[4];
    sprintf(name, "q%d", *index);
    (*index)++;
    State_ptr state = create_state(name, false);
    add_state(automaton, state);
    return state;
}

void add_transition(char* st, State_ptr from_state, State_ptr to_state){
    char* with;
    with = str_copy(with, st);
    add_transition_nfa(from_state, to_state, with);
}

void add_multiple_transitions(int index1, int index2, State_ptr from_state, State_ptr to_state){
    String_ptr st3;
    for (int j = index1; j <= index2; j++){
        st3 = char_at(keyboard_characters, j);
        add_transition(st3->s, from_state, to_state);
        free_string_ptr(st3);
    }
}

void add_transition_and_update_state(Automaton_ptr automaton,
                                     bool in_brackets,
                                     bool in_parentheses,
                                     char* s,
                                     int* index,
                                     State_ptr* previous,
                                     State_ptr* current,
                                     State_ptr next){
    if (!in_brackets){
        State_ptr  new_state = create_new_state(automaton, index);
        add_transition(s, *current, new_state);
        if (!in_parentheses){
            *previous = *current;
        }
        *current = new_state;
    } else {
        add_transition(s, *current, next);
    }
}

void add_multiple_transitions_and_update_state(Automaton_ptr automaton,
                                               bool in_brackets,
                                               bool in_parentheses,
                                               int *index,
                                               State_ptr* previous,
                                               State_ptr *current,
                                               State_ptr *next,
                                               int index1,
                                               int index2) {
    if (!in_brackets){
        State_ptr new_state = create_new_state(automaton, index);
        add_multiple_transitions(index1, index2, *current, new_state);
        if (!in_parentheses){
            *previous = *current;
            *next = NULL;
        }
        *current = new_state;
    } else {
        add_multiple_transitions(index1, index2, *current, *next);
    }
}

Automaton_ptr convert_to_nfa(char *expression) {
    State_ptr current, previous = NULL, next = NULL, new_state, previous_group, next_group;
    Stack_ptr previous_stack, next_stack;
    String_ptr st, st2;
    bool in_brackets = false, in_parentheses = false, done;
    int index = 1;
    previous_stack = create_stack();
    next_stack = create_stack();
    Automaton_ptr automaton = create_automaton();
    State_ptr start_state = create_state("q0", false);
    add_state(automaton, start_state);
    automaton->start_state = start_state;
    current = start_state;
    for (int i = 0; i < word_size(expression); i++){
        st = char_at(expression, i);
        if (strstr(keyboard_characters, st->s) != NULL){
            done = false;
            if (i + 2 < word_size(expression)){
                st2 = char_at(expression, i + 1);
                if (strcmp(st2->s, "-") == 0){
                    free_string_ptr(st2);
                    st2 = char_at(expression, i + 2);
                    add_multiple_transitions_and_update_state(automaton, in_brackets, in_parentheses, &index, &previous, &current, &next, str_find_c(keyboard_characters, st->s), str_find_c(keyboard_characters, st2->s));
                    i += 2;
                    done = true;
                }
                free_string_ptr(st2);
            }
            if (!done){
                add_transition_and_update_state(automaton, in_brackets, in_parentheses, st->s, &index, &previous, &current, next);
            }
        } else {
            if (strstr(special_characters, st->s) != NULL){
                if (strcmp(st->s, "(") == 0){
                    in_parentheses = true;
                    next = create_new_state(automaton, &index);
                    push(next_stack, next);
                    previous = current;
                    push(previous_stack, previous);
                } else {
                    if (strcmp(st->s, ")") == 0){
                        in_parentheses = false;
                        next_group = pop(next_stack);
                        previous_group = pop(previous_stack);
                        add_transition_nfa(current, next_group, "");
                        current = next_group;
                        if (i + 1 < word_size(expression)){
                            st2 = char_at(expression, i + 1);
                            if (strcmp(st2->s, "?") == 0 || strcmp(st2->s, "+") == 0 || strcmp(st2->s, "*") == 0){
                                if (strcmp(st2->s, "?") == 0){
                                    add_transition_nfa(previous_group, next_group, "");
                                } else {
                                    if (strcmp(st2->s, "*") == 0){
                                        add_transition_nfa(previous_group, next_group, "");
                                    }
                                    add_transition_nfa(next_group, previous_group, "");
                                }
                                i++;
                            }
                            free_string_ptr(st2);
                        }
                    } else {
                        if (strcmp(st->s, "[") == 0){
                            in_brackets = true;
                            next = create_new_state(automaton, &index);
                            previous = current;
                        } else {
                            if (strcmp(st->s, "]") == 0){
                                in_brackets = false;
                                previous = current;
                                current = next;
                            } else {
                                if (strcmp(st->s, "|") == 0){
                                    add_transition_nfa(current, peek(next_stack), "");
                                    current = peek(previous_stack);
                                } else {
                                    if (strcmp(st->s, ".") == 0){
                                        add_multiple_transitions_and_update_state(automaton, in_brackets, in_parentheses, &index, &previous, &current, &next, 0, word_size(keyboard_characters) - 1);
                                    } else {
                                        if (strcmp(st->s, "\\") == 0 && i + 1 < word_size(expression)){
                                            st2 = char_at(expression, i + 1);
                                            if (strstr(special_characters, st2->s) != NULL){
                                                add_transition_and_update_state(automaton, in_brackets, in_parentheses, st2->s, &index, &previous, &current, next);
                                                i++;
                                            } else {
                                                if (strcmp(st2->s, "d") == 0){
                                                    add_multiple_transitions_and_update_state(automaton, in_brackets, in_parentheses, &index, &previous, &current, &next, str_find_c(keyboard_characters, "0"), str_find_c(keyboard_characters, "9"));
                                                    i++;
                                                } else {
                                                    if (strcmp(st2->s, "w") == 0){
                                                        add_multiple_transitions_and_update_state(automaton, in_brackets, in_parentheses, &index, &previous, &current, &next, str_find_c(keyboard_characters, "a"), str_find_c(keyboard_characters, "_"));
                                                        i++;
                                                    }
                                                }
                                            }
                                            free_string_ptr(st2);
                                        } else {
                                            if (strcmp(st->s, "?") == 0){
                                                add_transition_nfa(previous, next != NULL ? next : current, "");
                                            } else {
                                                new_state = create_new_state(automaton, &index);
                                                if (strcmp(st->s, "*") == 0){
                                                    add_transition_nfa(previous, next != NULL ? next : current, "");
                                                }
                                                add_transition_nfa(next != NULL ? next : current, previous, "");
                                                add_transition_nfa(next != NULL ? next : current, new_state, "");
                                                previous = next != NULL ? next : current;
                                                current = new_state;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                printf("Invalid character %s in regular expression skipping it\n", st->s);
            }
        }
        free_string_ptr(st);
    }
    free_stack(previous_stack, NULL);
    free_stack(next_stack, NULL);
    current->is_final = true;
    return automaton;
}

bool full_matches(const Regular_expression *regex, const char *string) {
    return accepts_string_nfa(regex->automaton, string);
}
