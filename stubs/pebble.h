// Minimal Pebble SDK stub for clang-tidy analysis
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

// Basic types
typedef struct Window Window;
typedef struct Layer Layer;
typedef struct TextLayer TextLayer;
typedef struct GContext GContext;

typedef struct {
    struct { int16_t x, y; } origin;
    struct { int16_t w, h; } size;
} GRect;

typedef struct {
    int16_t x, y;
} GPoint;

// Compound literal constructors (C99 style)
#define GRect(x_, y_, w_, h_) ((GRect){.origin = {(x_), (y_)}, .size = {(w_), (h_)}})
#define GPoint(x_, y_) ((GPoint){.x = (x_), .y = (y_)})

typedef enum { GColorClear = 0, GColorBlack = 1 } GColor;
typedef enum { GCornerNone = 0 } GCorner;
typedef enum { APP_LOG_LEVEL_ERROR, APP_LOG_LEVEL_WARNING, APP_LOG_LEVEL_INFO, APP_LOG_LEVEL_DEBUG } AppLogLevel;
typedef enum { MINUTE_UNIT = 1 } TimeUnits;
typedef enum { APP_MSG_OK = 0 } AppMessageResult;
typedef struct DictionaryIterator DictionaryIterator;
typedef struct Tuple { union { uint32_t uint32; uint8_t uint8; char *cstring; uint8_t *data; } *value; uint32_t length; } Tuple;
typedef struct WindowHandlers { void (*load)(Window *); void (*unload)(Window *); } WindowHandlers;
typedef struct ConnectionHandlers { void (*pebble_app_connection_handler)(bool); } ConnectionHandlers;

// Display constants
#define PBL_DISPLAY_WIDTH 144
#define PBL_DISPLAY_HEIGHT 168

// Font keys
#define FONT_KEY_BITHAM_42_BOLD "BITHAM_42_BOLD"
#define FONT_KEY_GOTHIC_24_BOLD "GOTHIC_24_BOLD"

// Function declarations (to make clang-tidy happy)
void app_log(AppLogLevel level, const char *src_filename, int src_line_number, const char *fmt, ...);
#define APP_LOG(level, fmt, ...) app_log(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

Window *window_create(void);
void window_destroy(Window *window);
void window_set_window_handlers(Window *window, WindowHandlers handlers);
void window_stack_push(Window *window, bool animated);
Layer *window_get_root_layer(Window *window);

TextLayer *text_layer_create(GRect frame);
void text_layer_destroy(TextLayer *layer);
void text_layer_set_background_color(TextLayer *layer, GColor color);
void text_layer_set_text_color(TextLayer *layer, GColor color);
void text_layer_set_font(TextLayer *layer, const char *font);
void text_layer_set_text_alignment(TextLayer *layer, int alignment);
void text_layer_set_text(TextLayer *layer, const char *text);
Layer *text_layer_get_layer(TextLayer *layer);

Layer *layer_create(GRect frame);
void layer_destroy(Layer *layer);
void layer_add_child(Layer *parent, Layer *child);
void layer_mark_dirty(Layer *layer);
void layer_set_update_proc(Layer *layer, void (*update_proc)(Layer *, GContext *));
GRect layer_get_bounds(Layer *layer);

void graphics_context_set_fill_color(GContext *ctx, GColor color);
void graphics_context_set_stroke_width(GContext *ctx, uint8_t width);
void graphics_fill_rect(GContext *ctx, GRect rect, uint16_t corner_radius, GCorner corners);
void graphics_draw_line(GContext *ctx, GPoint p0, GPoint p1);
void graphics_draw_rect(GContext *ctx, GRect rect);

const char *fonts_get_system_font(const char *key);
bool clock_is_24h_style(void);

void app_message_register_inbox_received(void (*callback)(DictionaryIterator *, void *));
void app_message_register_inbox_dropped(void (*callback)(AppMessageResult, void *));
void app_message_deregister_callbacks(void);
AppMessageResult app_message_open(uint32_t inbox_size, uint32_t outbox_size);
AppMessageResult app_message_outbox_begin(DictionaryIterator **iter);
AppMessageResult app_message_outbox_send(void);

void tick_timer_service_subscribe(TimeUnits units, void (*callback)(struct tm *, TimeUnits));
void tick_timer_service_unsubscribe(void);

void connection_service_subscribe(ConnectionHandlers handlers);
void connection_service_unsubscribe(void);

void app_event_loop(void);

Tuple *dict_find(DictionaryIterator *iter, uint32_t key);
uint32_t dict_size(DictionaryIterator *iter);
void dict_write_uint8(DictionaryIterator *iter, uint32_t key, uint8_t value);
void dict_write_uint32(DictionaryIterator *iter, uint32_t key, uint32_t value);

#define GTextAlignmentCenter 1
#define GTextAlignmentLeft 0
