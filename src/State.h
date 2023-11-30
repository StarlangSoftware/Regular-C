//
// Created by Olcay Taner YILDIZ on 6.10.2023.
//

#ifndef REGULAR_STATE_H
#define REGULAR_STATE_H

#include <HashMap/HashMap.h>

struct state{
    char* name;
    bool is_final;
    Hash_map_ptr transitions;
};

typedef struct state State;

typedef State * State_ptr;

State_ptr create_state(char* name, bool is_final);

void free_dfa_state(State_ptr state);

void free_nfa_state(State_ptr state);

void add_transition_nfa(State_ptr from_state, State_ptr to_state, char* with);

void add_transition_dfa(State_ptr from_state, State_ptr to_state, char* with);

void add_transition(State_ptr from_state, State_ptr to_state, char* st);

unsigned int hash_function_state(const State *state, int N);

int compare_state(const State *first, const State *second);

State_ptr transition_to_dfa(const State* from_state, const char* with);

Array_list_ptr transition_to_nfa(const State* from_state, const char* with);

#endif //REGULAR_STATE_H
