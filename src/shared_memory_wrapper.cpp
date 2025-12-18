//
// Created by HichTala on 23/07/25.
//

// #include <boost/interprocess/shared_memory_object.hpp>
// #include <boost/interprocess/mapped_region.hpp>

#define OBS_SHM_NAME "obs_shared_memory"
#define PYTHON_SHM_NAME "python_shared_memory"

#include "shared_memory_wrapper.h"

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

struct shared_frame_header {
	uint32_t width;
	uint32_t height;
};
typedef struct shared_frame_header shared_frame_header_t;
extern "C" void write_message_to_shared_memory(
	draw_source_data_t *context,
	uint8_t *frame,
	uint32_t linesize,
	uint32_t width,
	uint32_t height)
{
	if (!context->shared_frame)
		return;

	auto *header = static_cast<shared_frame_header_t *>(context->shared_frame);

	header->width  = width;
	header->height = height;

	uint8_t *frame_data =
		static_cast<uint8_t *>(context->shared_frame) +
		sizeof(shared_frame_header_t);

	for (uint32_t y = 0; y < height; y++) {
		memcpy(
			frame_data + size_t(y) * width * 4,
			frame + size_t(y) * linesize,
			size_t(width) * 4
		);
	}
}


extern "C" void init_shared_memory(draw_source_data_t *context)
{
	using namespace boost::interprocess;

	// Guard against invalid sizes (VERY IMPORTANT)
	if (context->source_width == 0 || context->source_height == 0) {
		blog(LOG_WARNING, "Shared memory not initialized: invalid frame size");
		return;
	}

	// Compute size safely
	size_t pixel_bytes =
		size_t(context->source_width) *
		size_t(context->source_height) * 4;

	size_t required_size =
		sizeof(shared_frame_header_t) + pixel_bytes;

	// Cleanup previous mapping (if any)
	if (context->region) {
		delete static_cast<mapped_region *>(context->region);
		context->region = nullptr;
		context->shared_frame = nullptr;
	}

	try {
		// OBS MUST be the creator
		windows_shared_memory shm(
			create_only,
			OBS_SHM_NAME,
			read_write,
			required_size
		);

		auto *region = new mapped_region(shm, read_write);
		context->region = region;
		context->shared_frame = region->get_address();

		// Zero-init header (good hygiene)
		memset(context->shared_frame, 0, sizeof(shared_frame_header_t));

		blog(LOG_INFO, "Shared memory initialized (%zu bytes)", required_size);
	}
	catch (const interprocess_exception &e) {
		blog(LOG_ERROR, "Shared memory init failed: %s", e.what());
	}
}


extern "C" void destroy_shared_memory(draw_source_data_t *context)
{
	using namespace boost::interprocess;
	shared_memory_object::remove(OBS_SHM_NAME);
	shared_memory_object::remove(PYTHON_SHM_NAME);
	context->region = nullptr;
	context->shared_frame = nullptr;
}

extern "C" bool read_shared_memory(draw_source_data_t *context)
{
	using namespace boost::interprocess;
	
	try {
		windows_shared_memory shm(
			open_only,
			PYTHON_SHM_NAME,
			read_only
		);

		auto *region = new mapped_region(shm, read_only);
		context->region = region;

		auto *python_header =
			static_cast<shared_frame_header_t *>(region.get_address());

		blog(LOG_INFO, "Python shared memory attached");
	}
	catch (const interprocess_exception &e) {
		blog(LOG_ERROR, "Failed to open Python SHM: %s", e.what());
		return false;
	}

	// Validate header
	if (python_header->width == 0 || python_header->height == 0) {
		blog(LOG_ERROR, "Size of the image in the header are null");
		return false;
	}

	context->display_width  = header->width;
	context->display_height = header->height;

	if (context->display_texture)
		gs_texture_destroy(context->display_texture);

	context->display_texture = gs_texture_create(
		context->display_width,
		context->display_height,
		GS_RGBA,
		1,
		nullptr,
		GS_DYNAMIC
	);

	blog(LOG_INFO, "Display texture recreated (%ux%u)",
		 context->display_width,
		 context->display_height);


	uint8_t *image_data =
		static_cast<uint8_t *>(context->shared_frame) +
		sizeof(shared_frame_header_t);

	gs_texture_set_image(
		context->display_texture,
		image_data,
		context->display_width * 4,
		false
	);

	return true;
}


extern "C" void ensure_shared_memory_exists(draw_source_data_t *context)
{
	using namespace boost::interprocess;
	try {
		shared_memory_object shm(open_only, OBS_SHM_NAME, read_only);
	} catch (const interprocess_exception &ex) {
		(void)ex;
		init_shared_memory(context);
	}
}
