//
// Created by Olcay Taner YILDIZ on 6.10.2023.
//

#include <Memory/Memory.h>
#include "State.h"
#include "StringUtils.h"

State_ptr create_state(char *name, bool is_final) {
    State_ptr result = malloc_(sizeof(State), "create_state");
    result->is_final = is_final;
    result->name = str_copy(result->name, name);
    result->transitions = create_string_hash_map();
    return result;
}

void free_dfa_state(State_ptr state) {
    free_(state->name);
    free_hash_map(state->transitions, NULL);
    free_(state);
}

void free_nfa_state(State_ptr state) {
    free_(state->name);
    Array_list_ptr list = key_list(state->transitions);
    for (int i = 0; i < list->size; i++){
        Array_list_ptr to_list = hash_map_get(state->transitions, array_list_get(list, i));
        free_array_list(to_list, NULL);
    }
    free_array_list(list, NULL);
    free_hash_map2(state->transitions, free_, NULL);
    free_(state);
}

void add_transition(State_ptr from_state, State_ptr to_state, char* st){
    char* with;
    with = str_copy(with, st);
    add_transition_nfa(from_state, to_state, with);
}

void add_transition_nfa(State_ptr from_state, State_ptr to_state, char *with) {
    Array_list_ptr to_list = NULL;
    if (hash_map_contains(from_state->transitions, with)){
        to_list = hash_map_get(from_state->transitions, with);
        array_list_add(to_list, to_state);
        free_(with);
    } else {
        to_list = create_array_list();
        array_list_add(to_list, to_state);
        hash_map_insert(from_state->transitions, with, to_list);
    }
}

void add_transition_dfa(State_ptr from_state, State_ptr to_state, char *with) {
    hash_map_insert(from_state->transitions, with, to_state);
}

unsigned int hash_function_state(const State *state, int N) {
    return hash_function_string(state->name, N);
}

int compare_state(const State *first, const State *second) {
    return compare_string(first->name, second->name);
}

State_ptr transition_to_dfa(const State *from_state, const char *with) {
    return hash_map_get(from_state->transitions, with);
}

Array_list_ptr transition_to_nfa(const State *from_state, const char *with) {
    return hash_map_get(from_state->transitions, with);
}
