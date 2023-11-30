//
// Created by Olcay Taner YILDIZ on 8.10.2023.
//

#include <stdio.h>
#include <Memory/Memory.h>
#include "../src/Automaton.h"

int main(){
    Automaton_ptr dfa = create_automaton();
    State_ptr q1 = create_state("q1", false);
    State_ptr q2 = create_state("q2", true);
    add_state(dfa, q1);
    add_state(dfa, q2);
    dfa->start_state = q1;
    add_transition_dfa(q1, q1, "0");
    add_transition_dfa(q1, q2, "1");
    add_transition_dfa(q2, q1, "0");
    add_transition_dfa(q2, q2, "1");
    if (!accepts_string_dfa(dfa, "01")){
        printf("Error for string 01\n");
    }
    if (accepts_string_dfa(dfa, "1111110")){
        printf("Error for string 1111110\n");
    }
    free_dfa_automaton(dfa);
}