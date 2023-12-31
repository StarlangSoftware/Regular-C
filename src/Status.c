//
// Created by Olcay Taner YILDIZ on 14.10.2023.
//

#include <stdlib.h>
#include <Memory/Memory.h>
#include "Status.h"

Status_ptr create_status() {
    Status_ptr result = malloc_(sizeof(Status), "create_status");
    result->in_parentheses = false;
    result->in_brackets = false;
    result->previous = NULL;
    result->current = NULL;
    result->next = NULL;
    return result;
}

void free_status(Status_ptr status) {
    free_(status);
}
