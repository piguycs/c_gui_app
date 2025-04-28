// doing this so my LSP stops shouting at me

#include "palette.h"
#include "consts.h"

#ifndef CLAY_IMPLEMENTATION
#include "clay.h"
#endif

void Button(Clay_String text) {
    CLAY({
        .layout = { .padding = { 16, 16, 16, 16 }},
        .backgroundColor = ROSE_PINE_FOAM,
        .cornerRadius = { 8, 8, 8, 8 },
    }) {
        CLAY_TEXT(text, CLAY_TEXT_CONFIG({
            .fontId = FIRA_CODE_BOLD,
            .fontSize = 18,
            .textColor = ROSE_PINE_BASE,
        }));
    }
}
