//
// Created by Olcay Taner YILDIZ on 9.10.2023.
//

#ifndef REGULAR_REGULAREXPRESSION_H
#define REGULAR_REGULAREXPRESSION_H

#include "Automaton.h"
#include "Status.h"

struct regular_expression{
    char* expression;
    Automaton_ptr automaton;
};

typedef struct regular_expression Regular_expression;

typedef Regular_expression *Regular_expression_ptr;

Regular_expression_ptr create_regular_expression(char* expression);

void free_regular_expression(Regular_expression_ptr regular_expression);

Automaton_ptr convert_to_nfa(char* expression);

bool full_matches(const Regular_expression* regex, const char* string);

void add_multiple_transitions(int index1, int index2, State_ptr from_state, State_ptr to_state);

void add_transition_and_update_state(Automaton_ptr automaton, Status_ptr status, char* s);

void add_multiple_transitions_and_update_state(Automaton_ptr automaton, Status_ptr status, int index1, int index2);

#endif //REGULAR_REGULAREXPRESSION_H
