//
// Created by Olcay Taner YILDIZ on 9.10.2023.
//

#ifndef REGULAR_REGULAREXPRESSION_H
#define REGULAR_REGULAREXPRESSION_H

#include "Automaton.h"

struct regular_expression{
    char* expression;
    Automaton_ptr automaton;
};

typedef struct regular_expression Regular_expression;

typedef Regular_expression *Regular_expression_ptr;

Regular_expression_ptr create_regular_expression(char* expression);

void free_regular_expression(Regular_expression_ptr regular_expression);

Automaton_ptr convert_to_nfa(char* expression);

bool matches(const Regular_expression* regex, const char* string);

State_ptr create_new_state(Automaton_ptr automaton, int index);

void add_transition(char* st, State_ptr from_state, State_ptr to_state);

void add_multiple_transitions(int index1, int index2, State_ptr from_state, State_ptr to_state);

void add_transition_and_update_state(Automaton_ptr automaton,
                                     bool in_brackets,
                                     bool in_parentheses,
                                     char* s,
                                     int* index,
                                     State_ptr* previous,
                                     State_ptr* current,
                                     State_ptr next);

void add_multiple_transitions_and_update_state(Automaton_ptr automaton,
                                               bool in_brackets,
                                               bool in_parentheses,
                                               int* index,
                                               State_ptr* previous,
                                               State_ptr* current,
                                               State_ptr* next,
                                               int index1,
                                               int index2);

#endif //REGULAR_REGULAREXPRESSION_H
