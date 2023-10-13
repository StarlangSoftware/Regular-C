//
// Created by Olcay Taner YILDIZ on 6.10.2023.
//

#include <stdlib.h>
#include "State.h"
#include "StringUtils.h"

State_ptr create_state(char *name, bool is_final) {
    State_ptr result = malloc(sizeof(State));
    result->is_final = is_final;
    result->name = str_copy(result->name, name);
    result->transitions = create_string_hash_map();
    return result;
}

void free_state(State_ptr state) {
    free(state->name);
    free_hash_map(state->transitions, NULL);
}

void add_transition_nfa(State_ptr from_state, State_ptr to_state, char *with) {
    Array_list_ptr to_list = NULL;
    if (hash_map_contains(from_state->transitions, with)){
        to_list = hash_map_get(from_state->transitions, with);
    } else {
        to_list = create_array_list();
    }
    array_list_add(to_list, to_state);
    hash_map_insert(from_state->transitions, with, to_list);
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
