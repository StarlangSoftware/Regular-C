//
// Created by Olcay Taner YILDIZ on 14.10.2023.
//

#ifndef REGULAR_STATUS_H
#define REGULAR_STATUS_H

#include <stdbool.h>
#include "State.h"

struct status{
    bool in_brackets;
    bool in_parentheses;
    State_ptr previous;
    State_ptr current;
    State_ptr next;
};

typedef struct status Status;

typedef struct status *Status_ptr;

Status_ptr create_status();

void free_status(Status_ptr status);

#endif //REGULAR_STATUS_H
