//
// Created by Olcay Taner YILDIZ on 8.10.2023.
//

#include <stdio.h>
#include <Memory/Memory.h>
#include "../src/Automaton.h"
#include "../src/RegularExpression.h"

int main(){
    Automaton_ptr nfa = create_automaton();
    State_ptr q1 = create_state("q1", false);
    State_ptr q2 = create_state("q2", true);
    add_state(nfa, q1);
    add_state(nfa, q2);
    nfa->start_state = q1;
    add_transition(q1, q1, "0");
    add_transition(q1, q2, "1");
    add_transition(q2, q1, "0");
    add_transition(q2, q2, "1");
    if (!accepts_string_nfa(nfa, "01")){
        printf("Error for string 01\n");
    }
    if (accepts_string_nfa(nfa, "1111110")){
        printf("Error for string 1111110\n");
    }
    free_nfa_automaton(nfa);
}