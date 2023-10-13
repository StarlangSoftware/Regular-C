//
// Created by Olcay Taner YILDIZ on 9.10.2023.
//

#include <stdio.h>
#include "../src/RegularExpression.h"

void check_match(Regular_expression_ptr re, char* word){
    if (!matches(re, word)){
        printf("Mismatch %s %s\n", re->expression, word);
    }
}

int main(){
    check_match(create_regular_expression("[0-9,\\.]+"), "345.234");
    check_match(create_regular_expression("[\\-\\+]?\\d+"), "+34");
    check_match(create_regular_expression("[\\+\\-]?\\d*\\.\\d*"), "-.4");
    check_match(create_regular_expression("\\d+/\\d+"), "34/123");
    check_match(create_regular_expression(".*[0-9].*"), "asdkaj3453kjsdlkfj34");
    check_match(create_regular_expression(".*[a-zA-Z].*"), "33252b24234");
    check_match(create_regular_expression("(\\d\\d|\\d):(\\d\\d|\\d)"), "3:3");
    check_match(create_regular_expression("(\\d\\d|\\d):(\\d\\d|\\d):(\\d\\d|\\d)"), "3:3:33");
    check_match(create_regular_expression("c*b*a*d*"), "");
    check_match(create_regular_expression(".*[ab].*"), "dcb");
    check_match(create_regular_expression("c*b*a*"), "cba");
    check_match(create_regular_expression("ali"), "ali");
    check_match(create_regular_expression("a[lrs]i[tvg]"), "ariv");
    check_match(create_regular_expression("s(ali|veli|ayse)m"), "svelim");
    check_match(create_regular_expression("...."), "xyzç");
    check_match(create_regular_expression("b-kah0-9"), "dah3");
    check_match(create_regular_expression("\\.\\+\\-\\?"), ".+-?");
    check_match(create_regular_expression("[abc]?d[efg]?"), "d");
}