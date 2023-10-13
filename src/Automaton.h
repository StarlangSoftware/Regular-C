//
// Created by Olcay Taner YILDIZ on 6.10.2023.
//

#ifndef REGULAR_AUTOMATON_H
#define REGULAR_AUTOMATON_H
#include "HashMap/HashSet.h"
#include "State.h"

struct automaton{
    Hash_set_ptr states;
    State_ptr start_state;
};

typedef struct automaton Automaton;

typedef Automaton *Automaton_ptr;

Automaton_ptr create_automaton();

void free_automaton(Automaton_ptr automaton);

void add_state(Automaton_ptr automaton, State_ptr state);

bool accepts_string_dfa(Automaton_ptr automaton, char* string);

bool check_string_nfa_recursive(Hash_set_ptr visited, State_ptr current, const char* string, int index);

bool accepts_string_nfa(Automaton_ptr automaton, const char* string);

bool check_available_transitions(Hash_set_ptr visited, const State* current, const char* with, const char* string, int next_index);

void print_automaton(Automaton_ptr automaton);

#endif //REGULAR_AUTOMATON_H
