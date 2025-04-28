#ifndef LAYOUT_H
#define LAYOUT_H

#ifndef CLAY_IMPLEMENTATION
#include "clay.h"
#endif /* CLAY_IMPLEMENTATION */

typedef struct {
    Clay_Sizing layoutExpand;
    Clay_BorderElementConfig basicBorder;
    void* data;
} LayoutCommons;


LayoutCommons LayoutCommons_init(void* data);

void BaseLayout(LayoutCommons commons);
void InputArea(LayoutCommons commons);

#endif /* LAYOUT_H */
