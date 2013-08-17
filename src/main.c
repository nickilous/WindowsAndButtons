#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x90, 0xD8, 0x3F, 0x82, 0xDA, 0x4C, 0x4E, 0xFB, 0xAD, 0xEC, 0x7F, 0xFE, 0xF0, 0x9D, 0x09, 0xB9 }
PBL_APP_INFO(MY_UUID,
             "Window & Button", "Tutorial",
             1, 0, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
static struct WindowData {
	Window	window;
	GColor	backgroundColor;
	bool	fullScreen;
} window_data;

void up_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
	switch(window_data.backgroundColor){
	case GColorBlack :
		window_data.backgroundColor = GColorClear;
		window_set_background_color(window, window_data.backgroundColor);
		layer_mark_dirty(window_get_root_layer(&window_data.window));
		//layer_mark_dirty(&window_data.window->layer);
		break;
	case GColorClear:
		window_data.backgroundColor = GColorWhite;
		window_set_background_color(window, window_data.backgroundColor);
		layer_mark_dirty(window_get_root_layer(&window_data.window));
		//layer_mark_dirty(&window_data.window->layer);
		break;
	case GColorWhite:
		window_data.backgroundColor = GColorBlack;
		window_set_background_color(window, window_data.backgroundColor);
		layer_mark_dirty(window_get_root_layer(&window_data.window));
		//layer_mark_dirty(&window_data.window->layer);
		break;
	}
		
}
void down_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
	
	switch(window_data.backgroundColor){
	case GColorBlack :
		window_data.backgroundColor = GColorWhite;
		window_set_background_color(window, window_data.backgroundColor);
		//layer_mark_dirty(window_get_root_layer(window));
		break;
	case GColorClear:
		window_data.backgroundColor = GColorBlack;
		layer_mark_dirty(window_get_root_layer(window));
		window_set_background_color(window, window_data.backgroundColor);
		//layer_mark_dirty(&window_data.window->layer);
		break;
	case GColorWhite:
		window_data.backgroundColor = GColorClear;
		window_set_background_color(window, window_data.backgroundColor);
		layer_mark_dirty(window_get_root_layer(window));
		//layer_mark_dirty(&window_data.window->layer);
		break;
	}

}
void select_single_click_handler(ClickRecognizerRef recognizer, Window *window) {
	switch(window_get_fullscreen(window)){
	case true:
		window_data.fullScreen = false;
		window_set_fullscreen(window, window_data.fullScreen);
		window_stack_push(window, true);
		//layer_mark_dirty(window_get_root_layer(window));
		break;
	case false:
		window_data.fullScreen = true;
		window_set_fullscreen(window, window_data.fullScreen);
		window_stack_push(window, true);
		//layer_mark_dirty(window_get_root_layer(window));
		break;
	default:
		window_set_fullscreen(window, false);
	}
}
void select_long_click_handler(ClickRecognizerRef recognizer, Window *window) {}

void click_config_provider(ClickConfig **config, Window *window) {
	config[BUTTON_ID_SELECT]->click.handler = (ClickHandler) select_single_click_handler;
	config[BUTTON_ID_SELECT]->long_click.handler = (ClickHandler) select_long_click_handler;

  	config[BUTTON_ID_UP]->click.handler = (ClickHandler) up_single_click_handler;
  	config[BUTTON_ID_UP]->click.repeat_interval_ms = 100;

  	config[BUTTON_ID_DOWN]->click.handler = (ClickHandler) down_single_click_handler;
  	config[BUTTON_ID_DOWN]->click.repeat_interval_ms = 100;
}

void handle_init(AppContextRef ctx) {
  (void)ctx;
	Window* window = &window_data.window;
	window_init(window, "Window Name");
	
	//set struct data member to color
	window_data.backgroundColor = GColorBlack;
	window_data.fullScreen = true;
	
	// Attach our desired button functionality
  	window_set_click_config_provider(window, (ClickConfigProvider) click_config_provider);
	
	//set window background color
	window_set_background_color(window, window_data.backgroundColor);
	window_set_fullscreen(window, window_data.fullScreen);

  	
  	window_stack_push(window, true /* Animated */);
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
  };
  app_event_loop(params, &handlers);
}
