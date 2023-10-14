//
// Created by Olcay Taner YILDIZ on 6.10.2023.
//

#include <stdlib.h>
#include <StringUtils.h>
#include <string.h>
#include <stdio.h>
#include "Automaton.h"
#include "Dictionary/Word.h"

Automaton_ptr create_automaton() {
    Automaton_ptr result = malloc(sizeof(Automaton));
    result->start_state = NULL;
    result->states = create_hash_set((unsigned int (*)(const void *, int)) hash_function_state,
                                     (int (*)(const void *, const void *)) compare_state);
    result->index = 0;
    return result;
}

void free_automaton(Automaton_ptr automaton) {
    Array_list_ptr list = hash_set_key_list(automaton->states);
    for (int i = 0; i < list->size; i++){
        free_state(array_list_get(list, i));
    }
    free_array_list(list, free);
    free(automaton);
}

State_ptr create_new_state(Automaton_ptr automaton){
    char name[4];
    sprintf(name, "q%d", automaton->index);
    automaton->index++;
    State_ptr state = create_state(name, false);
    add_state(automaton, state);
    return state;
}

void add_state(Automaton_ptr automaton, State_ptr state) {
    hash_set_insert(automaton->states, state);
}

bool accepts_string_dfa(Automaton_ptr automaton, char *string) {
    State_ptr current = automaton->start_state;
    for (int i = 0; i < word_size(string); i++){
        String_ptr ch = char_at(string, i);
        current = transition_to_dfa(current, ch->s);
        free_string_ptr(ch);
    }
    return current->is_final;
}

bool accepts_string_nfa(Automaton_ptr automaton, const char *string) {
    Hash_set_ptr visited = create_hash_set((unsigned int (*)(const void *, int)) hash_function_string,
                                           (int (*)(const void *, const void *)) compare_string);
    bool result = check_string_nfa_recursive(visited, automaton->start_state, string, 0);
    free_hash_set(visited, NULL);
    return result;
}

bool check_string_nfa_recursive(Hash_set_ptr visited, State_ptr current, const char *string, int index) {
    if (index == word_size(string) && current->is_final){
        return true;
    }
    char name[10];
    sprintf(name, "%d%s", index, current->name);
    if (hash_set_contains(visited, name)){
        return false;
    }
    hash_set_insert(visited, name);
    if (index < word_size(string)){
        String_ptr ch = char_at(string, index);
        if (check_available_transitions(visited, current, ch->s, string, index + 1)){
            return true;
        }
        free_string_ptr(ch);
    }
    if (check_available_transitions(visited, current, "", string, index)){
        return true;
    }
    return false;
}

bool check_available_transitions(Hash_set_ptr visited, const State* current, const char* with, const char* string, int next_index) {
    Array_list_ptr current_transitions = transition_to_nfa(current, with);
    if (current_transitions != NULL){
        for (int i = 0; i < current_transitions->size; i++){
            State_ptr next = array_list_get(current_transitions, i);
            if (check_string_nfa_recursive(visited, next, string, next_index)){
                return true;
            }
        }
    }
    return false;
}

void print_automaton(Automaton_ptr automaton){
    Array_list_ptr list = hash_set_key_list(automaton->states);
    for (int i = 0; i < list->size; i++){
        State_ptr state = array_list_get(list, i);
        Array_list_ptr list2 = key_value_list(state->transitions);
        for (int j = 0; j < list2->size; j++){
            Hash_node_ptr node = array_list_get(list2, j);
            Array_list_ptr list3 = node->value;
            for (int k = 0; k < list3->size; k++){
                State_ptr to_state = array_list_get(list3, k);
                printf("Transition: %s->%s(%s)\n", state->name, to_state->name, (char*)node->key);
            }
        }
    }
}