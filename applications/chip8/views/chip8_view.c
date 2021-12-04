#include <gui/elements.h>
#include "chip8_view.h"
#include "../chip8.h"
#include "../emulator-core/flipper-chip.h"

struct Chip8View {
    View* view;
    Chip8ViewCallback callback;
    void* context;
};

typedef struct {
    char* file_name;
    Chip8State state;
} Chip8Model;

static void chip8_draw_callback(Canvas* canvas, void* _model) {
    Chip8Model* model = _model;

    if (model->state.worker_state == WorkerStateLoadingRom) {
        canvas_draw_icon(canvas, 4, 22, &I_Clock_18x18);
    }

    if (model->state.worker_state == WorkerStateRomLoaded) {
        t_chip8_toggle_rendering();
        uint8_t** screen = t_chip8_get_screen(model->state.t_chip8_state);

        for (int y = 0; y < CHIP8_SCREEN_H; y++) {
            for (int x = 0; x < CHIP8_SCREEN_W; x++) {
                if (screen[y][x] == 1) {
                    canvas_set_color(canvas, ColorBlack);
                } else {
                    canvas_set_color(canvas, ColorWhite);
                }

                canvas_draw_box(canvas, x * 2, y * 2, 2, 2);
                //canvas_draw_dot(canvas, x, y);
            }
        }
        t_chip8_toggle_rendering();
        FURI_LOG_I(WORKER_TAG, "ONE RENDER ITERATION");
    }

    if (model->state.worker_state == WorkerStateRomLoadError) {
        canvas_draw_icon(canvas, 4, 22, &I_Error_18x18);
    }

}

static bool chip8_input_callback(InputEvent* event, void* context) {
    FURI_LOG_I("Chip8", "received input");
    furi_assert(context);
    Chip8View* chip8 = context;
    bool consumed = false;

    if(event->type == InputTypeShort) {
        if(event->key == InputKeyOk) {
            consumed = true;
            furi_assert(chip8->callback);
            chip8->callback(InputTypeShort, chip8->context);
        }

        if(event->key == InputKeyBack) {
            consumed = true;
            furi_assert(chip8->callback);
            chip8->callback(InputTypeShort, chip8->context);
        }
    }

    return consumed;
}

Chip8View* chip8_alloc() {
    Chip8View* chip8 = furi_alloc(sizeof(Chip8View));

    chip8->view = view_alloc();
    view_allocate_model(chip8->view, ViewModelTypeLocking, sizeof(Chip8Model));
    view_set_context(chip8->view, chip8);
    view_set_draw_callback(chip8->view, chip8_draw_callback);
    view_set_input_callback(chip8->view, chip8_input_callback);

    return chip8;
}

void chip8_free(Chip8View* chip8) {
    furi_assert(chip8);
    view_free(chip8->view);
    free(chip8);
}

View* chip8_get_view(Chip8View* chip8) {
    furi_assert(chip8);
    return chip8->view;
}

void chip8_set_ok_callback(Chip8View* chip8, Chip8ViewCallback callback, void* context) {
    furi_assert(chip8);
    furi_assert(callback);
    with_view_model(
        chip8->view, (Chip8Model* model) {
            chip8->callback = callback;
            chip8->context = context;
            return false;
        });
}

void chip8_set_file_name(Chip8View* chip8, char* name) {
    furi_assert(name);
    with_view_model(
        chip8->view, (Chip8Model* model) {
            model->file_name = name;
            return false;
        });
}

void chip8_set_state(Chip8View* chip8, Chip8State* st) {
    furi_assert(st);
    with_view_model(
        chip8->view, (Chip8Model* model) {
            memcpy(&(model->state), st, sizeof(Chip8State));
            return true;
        });
}
