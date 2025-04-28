#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "renderers/raylib/clay_renderer_raylib.c"

#include "palette.h"

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}

int main(void) {
    Clay_Raylib_Initialize(1400, 800, "Clay", FLAG_WINDOW_RESIZABLE);

    uint64_t clayRequiredMemory = Clay_MinMemorySize();
    Clay_Arena clayMemory = (Clay_Arena) {
        .memory = malloc(clayRequiredMemory),
        .capacity = clayRequiredMemory,
    };

    Clay_Initialize(clayMemory, (Clay_Dimensions) {
        .width = GetScreenWidth(),
        .height = GetScreenHeight(),
    }, (Clay_ErrorHandler) { HandleClayErrors, NULL });

    Clay_Sizing layoutExpand = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) };


    while (!WindowShouldClose()) {
        Clay_SetLayoutDimensions((Clay_Dimensions) {
            .width = GetScreenWidth(),
            .height = GetScreenHeight(),
        });
        Clay_BeginLayout();

        CLAY({
            .backgroundColor = ROSE_PINE_BASE,
            .layout = {
                .sizing = layoutExpand,
                .padding = { 16, 16, 16, 16 },
            },
        }){
            CLAY({
                .id = CLAY_ID("SideBar"),
                .backgroundColor = ROSE_PINE_BASE,
                .cornerRadius = { 8, 8, 8, 8 },
                .border = { ROSE_PINE_OVERLAY, {2,2,2,2,0} },
                .layout = {
                    .sizing = { .width = CLAY_SIZING_FIXED(280), .height = CLAY_SIZING_GROW(0) },
                },
            }) {}

            CLAY({
                .id = CLAY_ID("MainView"),
                .layout = { .sizing = layoutExpand },
            }) {}
        };

        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(BLACK);
        Clay_Raylib_Render(renderCommands, NULL);
        EndDrawing();
    }

    return 0;
}
