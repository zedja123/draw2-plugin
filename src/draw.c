//
// Created by HichTala on 24/06/25.
//

#include "draw.h"

#include "plugin-support.h"
#include <graphics/graphics.h>

struct obs_source_info draw_filter = {.id = "draw_filter",
				      .type = OBS_SOURCE_TYPE_FILTER,
				      .output_flags = OBS_SOURCE_VIDEO,
				      .get_name = draw_filter_get_name,
				      .create = draw_filter_create,
				      .destroy = draw_filter_destroy,
				      .get_defaults = draw_filter_get_defaults};

struct obs_source_info draw_source = {.id = "draw_source",
				      .type = OBS_SOURCE_TYPE_INPUT,
				      .output_flags = OBS_SOURCE_VIDEO,
				      .get_name = draw_source_get_name,
				      .create = draw_source_create,
				      .destroy = draw_filter_destroy,
				      .get_width = draw_source_get_width,
				      .get_height = draw_source_get_height,
				      .get_defaults = draw_filter_get_defaults,
				      // .video_render = draw_source_video_render,
				      .get_properties = draw_source_get_properties,
				      .icon_type = OBS_ICON_TYPE_COLOR};

const char *draw_filter_get_name(void *type_data)
{
	UNUSED_PARAMETER(type_data);
	return obs_module_text("Draw Filter");
}
const char *draw_source_get_name(void *type_data)
{
	UNUSED_PARAMETER(type_data);
	return obs_module_text("Draw Display");
}

void *draw_filter_create(obs_data_t *settings, obs_source_t *source)
{
	UNUSED_PARAMETER(settings);
	draw_filter_data_t *filter = (draw_filter_data_t *)(bzalloc(sizeof(draw_filter_data_t)));

	filter->source = source;

	return filter;
}
void *draw_source_create(obs_data_t *settings, obs_source_t *source)
{
	UNUSED_PARAMETER(settings);
	draw_source_data_t *source_data = (draw_source_data_t *)(bzalloc(sizeof(draw_source_data_t)));

	source_data->source = source;
	source_data->height = 391;
	source_data->width = 268;

	return source_data;
}
void draw_filter_destroy(void *data)
{
	draw_filter_data_t *filter = (draw_filter_data_t *)(data);

	bfree(filter);
}

uint32_t draw_source_get_height(void *data)
{
	draw_source_data_t *source_data = (draw_source_data_t *)(data);
	return source_data->height;
}
uint32_t draw_source_get_width(void *data)
{
	draw_source_data_t *source_data = (draw_source_data_t *)(data);
	return source_data->width;
}

void draw_filter_get_defaults(obs_data_t *settings)
{
	UNUSED_PARAMETER(settings);
	obs_log(LOG_INFO, "draw_filter_get_defaults", PLUGIN_VERSION);
}

void draw_source_video_render(void *data, gs_effect_t *effect)
{
	UNUSED_PARAMETER(data);
	UNUSED_PARAMETER(effect);
}
bool add_source_to_list(void *data, obs_source_t *source)
{
	obs_property_t *p = data;
	const char *name = obs_source_get_name(source);
	size_t count = obs_property_list_item_count(p);
	size_t idx = 0;
	while (idx < count &&
	       strcmp(name, obs_property_list_item_string(p, idx)) > 0)
		idx++;

	uint32_t flags = obs_source_get_output_flags(source);
	const char *source_id = obs_source_get_id(source);

	if (flags & OBS_SOURCE_VIDEO & (strcmp(source_id, "draw_source") != 0)) {
		obs_property_list_insert_string(p, idx, name, name);
	}
	return true;
}
static bool draw_source_type_changed(obs_properties_t *props, obs_property_t *list, obs_data_t *settings)
{
	UNUSED_PARAMETER(props);
	UNUSED_PARAMETER(list);
	UNUSED_PARAMETER(settings);


	const char *selected_type = obs_data_get_string(settings, "input_type");

	obs_property_t *input_selection = obs_properties_get(props, "input_selection");

	obs_property_list_clear(input_selection);

	if (strcmp(selected_type, "source") == 0) {
		obs_enum_sources(add_source_to_list, input_selection);
	} else if (strcmp(selected_type, "scene") == 0) {
		obs_enum_scenes(add_source_to_list, input_selection);
	}

	return true;  // Refresh UI
}
obs_properties_t *draw_source_get_properties(void *data)
{
	UNUSED_PARAMETER(data);
	// draw_source_data_t *source_data = (draw_source_data_t *)(data);
	obs_properties_t *source_properties = obs_properties_create();

	obs_property_t *input_type = obs_properties_add_list(
		source_properties, "input_type", "Input Type", OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);
	obs_property_list_add_string(input_type, "Scene", "scene");
	obs_property_list_add_string(input_type, "Source", "source");

	obs_properties_add_list(source_properties, "input_selection", "Input Selection", OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);
	obs_property_set_modified_callback(input_type, draw_source_type_changed);

	obs_properties_add_int(source_properties, "minimum_screen_time",
			       obs_module_text("Minimum Card Display Time (in sec)"), 1, 4096, 1);
	obs_properties_add_int(source_properties, "minimum_out_of_screen_time",
			       obs_module_text("Minimum Card Out Of Screen Time (in sec)"), 1, 4096, 1);
	obs_properties_add_int(source_properties, "threshold_confidence_score",
			       obs_module_text("Threshold for confidence score (in %)"), 1, 4096, 1);

	return source_properties;
}
