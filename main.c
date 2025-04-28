#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "renderers/raylib/clay_renderer_raylib.c"

#include "palette.h"
#include "consts.h"
#include "components/button.h"

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

void InputArea(void) {
    Clay_Sizing layoutExpand = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) };
    Clay_BorderElementConfig basicBorder = { ROSE_PINE_OVERLAY, {2,2,2,2,0} };

    CLAY({
        .id = CLAY_ID("ChatArea"),
        //.backgroundColor = ROSE_PINE_SUBTLE,
        .cornerRadius = { 8, 8, 8, 8 },
        .layout = { .sizing = layoutExpand },
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
            .layout = { .sizing = layoutExpand },
            .border = basicBorder,
        }) { }

        Button(CLAY_STRING("SEND"));
    }
}

void BaseLayout(void) {
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
        }) { InputArea(); }
    };
}

int main(void) {
    Clay_Raylib_Initialize(1200, 800, "Clay", FLAG_WINDOW_RESIZABLE);

    uint64_t clayRequiredMemory = Clay_MinMemorySize();
    Clay_Arena clayMemory = (Clay_Arena) {
        .memory = malloc(clayRequiredMemory),
        .capacity = clayRequiredMemory,
    };

    Clay_Initialize(clayMemory, (Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight(),
    }, (Clay_ErrorHandler) { HandleClayErrors, NULL });

    Font fonts[3];

    // HACK: relative to the build dir, I will look into embedding this in the binary
    fonts[FIRA_CODE_REG] = LoadFontEx("../resources/fonts/FiraCode-Regular.ttf", 48, 0, 400);
    fonts[FIRA_CODE_BOLD] = LoadFontEx("../resources/fonts/FiraCode-Bold.ttf", 48, 0, 400);
    fonts[FIRA_CODE_RET] = LoadFontEx("../resources/fonts/FiraCode-Retina.ttf", 48, 0, 400);
    SetTextureFilter(fonts[FIRA_CODE_REG].texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fonts[FIRA_CODE_BOLD].texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(fonts[FIRA_CODE_RET].texture, TEXTURE_FILTER_BILINEAR);

    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    while (!WindowShouldClose()) {
        Clay_SetLayoutDimensions((Clay_Dimensions) {
            .width = GetScreenWidth(),
            .height = GetScreenHeight(),
        });
        Clay_BeginLayout();

        BaseLayout();

        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(BLACK);
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();
    }

    return 0;
}
