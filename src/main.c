#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "renderers/raylib/clay_renderer_raylib.c"

#include "consts.h"
#include "layout.h"

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
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

    int key, index;
    char value[MAX_INPUT_LEN] = "\0";

    LayoutCommons commons = LayoutCommons_init(NULL);

    while (!WindowShouldClose()) {
        Clay_Vector2 clayMouseVecs = (Clay_Vector2) { GetMouseX(), GetMouseY() };

        Clay_SetPointerState(clayMouseVecs, IsMouseButtonDown(MOUSE_BUTTON_LEFT));
        Clay_UpdateScrollContainers(true, clayMouseVecs, GetFrameTime());

        Clay_SetLayoutDimensions((Clay_Dimensions) {
            .width = GetScreenWidth(),
            .height = GetScreenHeight(),
        });
        Clay_BeginLayout();

        commons.data = &((Clay_String) { .chars = value, .length = index });
        BaseLayout(commons);

        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(BLACK);
        Clay_Raylib_Render(renderCommands, fonts);
        EndDrawing();

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_D)) {
            Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
        } else {
            if ((key = GetCharPressed()) && index < MAX_INPUT_LEN) {
                value[index] = key;
                index++;
            } else {
                key = GetKeyPressed();
                if (key == KEY_ENTER) {
                    // TODO: connect this up to some event system
                    printf("%s\n", value);
                    index = 0;
                    value[0] = '\0';
                } else if (key == KEY_BACKSPACE && index > 0) {
                    index--;
                    value[index] = '\0';
                }
            }
        }
    }

    return 0;
}
