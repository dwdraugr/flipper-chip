#include <furi.h>
#include <furi-hal.h>
#include <gui/gui.h>
#include <input/input.h>
#include <lib/toolbox/args.h>
#include <storage/storage.h>
#include "chip8.h"

#define TAG "Chip8Emulator"
#define WORKER_TAG TAG "Worker"
#define FILE_BUFFER_LEN 16

typedef enum {
    WorkerEvtToggle = (1 << 1),
    WorkerEvtEnd = (1 << 2),
} WorkerEvtFlags;

struct Chip8Emulator {
    Chip8State st;
    string_t file_path;
    FuriThread* thread;
};


static int32_t chip8_worker(void* context) {
    Chip8Emulator* chip8 = context;

    FURI_LOG_I(WORKER_TAG, "Start furi record open");
    Storage* furi_storage_record = furi_record_open("storage");
    FURI_LOG_I(WORKER_TAG, "furi record opened");



    while(1) {
        // chip8_internall_process();
        // chip8->st.screen = chip8_internal_get();
        if (chip8->st.worker_state == WorkerStateBackPressed) {
            break;
        }

        if (chip8->st.worker_state == WorkerStateLoadingRom) {
            FURI_LOG_I(WORKER_TAG, "Start storage file alloc");
            File* rom_file = storage_file_alloc(furi_storage_record);
            FURI_LOG_I(WORKER_TAG, "Start storage file open, path = %s", chip8->file_path);
            bool is_file_opened = storage_file_open(
                                rom_file,
                                string_get_cstr(chip8->file_path),
                                FSAM_READ,
                                FSOM_OPEN_EXISTING
                        );


            if (!is_file_opened) {
                FURI_LOG_I(WORKER_TAG, "Cannot open storage");
                storage_file_close(rom_file);
                storage_file_free(rom_file);
                chip8->st.worker_state = WorkerStateRomLoadError;
                return 0;
            }

            FURI_LOG_I(WORKER_TAG, "File was opened, try read this");

            chip8->st.worker_state = WorkerStateRomLoaded;

            uint8_t rom_data[2048];
            FURI_LOG_I(WORKER_TAG, "2048 array gotten");

            read_rom_data(rom_file, rom_data);

            FURI_LOG_I(WORKER_TAG, "Rom data finished reading");


            // uint16_t rom_size = read_rom_data(rom_file, rom_data);
            // chip8->st.screen = furi_alloc(64);
            // for (int y = 0; y < 64; y++) {
            //     chip8->st.screen[y] = furi_alloc(32);
            // }
        }
        
    }


    // storage_file_close(rom_file);
    // storage_file_free(rom_file);

    return 0;
}

Chip8Emulator* chip8_make_emulator(string_t file_path) {
    furi_assert(file_path);

    Chip8Emulator* chip8 = furi_alloc(sizeof(Chip8Emulator));
    string_init(chip8->file_path);
    string_set(chip8->file_path, file_path);
    chip8->st.worker_state = WorkerStateLoadingRom;

    chip8->thread = furi_thread_alloc();
    furi_thread_set_name(chip8->thread, "Chip8Worker");
    furi_thread_set_stack_size(chip8->thread, 2048);
    furi_thread_set_context(chip8->thread, chip8);
    furi_thread_set_callback(chip8->thread, chip8_worker);

    furi_thread_start(chip8->thread);
    return chip8;
}

void chip8_close_emulator(Chip8Emulator* chip8) {
    furi_assert(chip8);
    osThreadFlagsSet(furi_thread_get_thread_id(chip8->thread), WorkerEvtEnd);
    furi_thread_join(chip8->thread);
    furi_thread_free(chip8->thread);
    string_clear(chip8->file_path);
    free(chip8);
}

void chip8_toggle(Chip8Emulator* chip8) {
    furi_assert(chip8);
    osThreadFlagsSet(furi_thread_get_thread_id(chip8->thread), WorkerEvtToggle);
}

Chip8State* chip8_get_state(Chip8Emulator* chip8) {
    furi_assert(chip8);
    return &(chip8->st);
}

uint16_t read_rom_data(File* file, uint8_t* data) {
    furi_assert(file);
    furi_assert(data);

    const uint8_t buffer_size = 32;
    uint16_t file_pointer = 0;
    uint8_t buff[buffer_size];

    while(1) {
        uint16_t bytes_were_read = storage_file_read(file, buff, buffer_size);
        if (bytes_were_read == 0) {
            break;
        }

        for (uint16_t i = 0; i < bytes_were_read; i++) {
            data[file_pointer] = buff[i];
            file_pointer++;
        }
    }

    return file_pointer;
}