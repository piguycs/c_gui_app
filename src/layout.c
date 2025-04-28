#include "consts.h"
#include "layout.h"
#include "palette.h"
#include "components/button.h"

void InputArea(LayoutCommons commons) {
    Clay_String* string = (Clay_String*)commons.data;

    CLAY({
        .id = CLAY_ID("ChatArea"),
        //.backgroundColor = ROSE_PINE_SUBTLE,
        .cornerRadius = { 8, 8, 8, 8 },
        .layout = { .sizing = commons.layoutExpand },
    }) {}
    
    CLAY({
        .id = CLAY_ID("ChatInput"),
        .cornerRadius = { 8, 8, 8, 8 },
        .layout = {
            .sizing = { .height = CLAY_SIZING_FIT(0), .width = CLAY_SIZING_GROW(0) },
            .childGap = 16,
         },
    }) {
        CLAY({ 
            .layout = { .sizing = commons.layoutExpand, .padding = { 16, 16, 16, 16 } },
            .border = commons.basicBorder,
        }) {
            CLAY_TEXT(*string, CLAY_TEXT_CONFIG({
                .fontId = FIRA_CODE_RET,
                .fontSize = 18,
                .textColor = ROSE_PINE_TEXT,
            }));
        }

        Button(CLAY_STRING("SEND"));
    }
}

void BaseLayout(LayoutCommons commons) {
    Clay_Sizing layoutExpand = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) };
    Clay_BorderElementConfig basicBorder = { ROSE_PINE_OVERLAY, {2,2,2,2,0} };

    CLAY({
        .backgroundColor = ROSE_PINE_BASE,
        .layout = {
            .sizing = layoutExpand,
            .padding = { 16, 16, 16, 16 },
            .childGap = 16,
        },
    }){
        CLAY({
            .id = CLAY_ID("SideBar"),
            .backgroundColor = ROSE_PINE_BASE,
            .cornerRadius = { 8, 8, 8, 8 },
            .border = basicBorder,
            .layout = { .sizing = { .width = CLAY_SIZING_FIXED(280), .height = CLAY_SIZING_GROW(0) } },
        }) {}

        CLAY({
            .id = CLAY_ID("MainView"),
            .layout = { .sizing = layoutExpand, .childGap = 16, .layoutDirection = CLAY_TOP_TO_BOTTOM },
        }) { InputArea(commons); }
    };
}

LayoutCommons LayoutCommons_init(void* data) {
    LayoutCommons value = {
        .layoutExpand = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
        .basicBorder = { ROSE_PINE_OVERLAY, {2,2,2,2,0} },
        .data = data,
    };

    return value;
}
