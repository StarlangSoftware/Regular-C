//
// Created by Olcay Taner YILDIZ on 9.10.2023.
//

#include <stdio.h>
#include "../src/RegularExpression.h"

void check_match(char* expression, char* word){
    Regular_expression_ptr re = create_regular_expression(expression);
    if (!full_matches(re, word)){
        printf("Mismatch %s %s\n", re->expression, word);
    }
    free_regular_expression(re);
}

int main(){
    check_match("c*b*a*", "cba");
    check_match("s(a(b(cd(mn|öş)+[e\\df]+g)*r)*f)+t", "sabrfabcdmnöşmnef345ffegrft");
    check_match("s(a[lmr]+i|v[eaı]l[sdf]|ayse)m", "sammmim");
    check_match("s(a[lmr]*i|v[eaı]+l[sdf]*|ayse)+m", "saivaaaaalfdsaysem");
    check_match("[0-9,\\.]+", "345.234");
    check_match("[\\-\\+]?\\d+", "+34");
    check_match("[\\+\\-]?\\d*\\.\\d*", "-.4");
    check_match("\\d+/\\d+", "34/123");
    check_match(".*[0-9].*", "asdkaj3453kjsdlkfj34");
    check_match(".*[a-zA-Z].*", "33252b24234");
    check_match("(\\d\\d|\\d):(\\d\\d|\\d)", "3:3");
    check_match("(\\d\\d|\\d):(\\d\\d|\\d):(\\d\\d|\\d)", "3:3:33");
    check_match("c*b*a*d*", "");
    check_match(".*[ab].*", "dcb");
    check_match("ali", "ali");
    check_match("a[lrs]i[tvg]", "ariv");
    check_match("s(ali|veli|ayse)m", "svelim");
    check_match("....", "xyzç");
    check_match("b-kah0-9", "dah3");
    check_match("\\.\\+\\-\\?", ".+-?");
    check_match("[abc]?d[efg]?", "d");
}