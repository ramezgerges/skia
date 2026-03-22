/*
 * Copyright 2026 Microsoft Corporation. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef graphite_context_DEFINED
#define graphite_context_DEFINED

#include "include/c/sk_types.h"

SK_C_PLUS_PLUS_BEGIN_GUARD

// Graphite Context

SK_C_API graphite_context_t* graphite_context_make_vulkan(const gr_vk_backendcontext_t* vkBackendContext);
SK_C_API graphite_context_t* graphite_context_make_vulkan_with_options(const gr_vk_backendcontext_t* vkBackendContext, const graphite_context_options_t* options);
SK_C_API void graphite_context_unref(graphite_context_t* context);
SK_C_API bool graphite_context_is_device_lost(graphite_context_t* context);
SK_C_API int graphite_context_max_texture_size(graphite_context_t* context);
SK_C_API bool graphite_context_insert_recording(graphite_context_t* context, graphite_recording_t* recording);
SK_C_API bool graphite_context_submit(graphite_context_t* context, bool syncToCpu);
SK_C_API void graphite_context_free_gpu_resources(graphite_context_t* context);
SK_C_API size_t graphite_context_current_budgeted_bytes(graphite_context_t* context);
SK_C_API size_t graphite_context_max_budgeted_bytes(graphite_context_t* context);

// Graphite Recorder

SK_C_API graphite_recorder_t* graphite_context_make_recorder(graphite_context_t* context);
SK_C_API sk_surface_t* graphite_recorder_make_render_target(graphite_recorder_t* recorder, const sk_imageinfo_t* imageInfo, bool mipmapped);
SK_C_API graphite_recording_t* graphite_recorder_snap(graphite_recorder_t* recorder);
SK_C_API void graphite_recorder_unref(graphite_recorder_t* recorder);
SK_C_API void graphite_recorder_free_gpu_resources(graphite_recorder_t* recorder);

// Graphite Recording

SK_C_API void graphite_recording_unref(graphite_recording_t* recording);

SK_C_PLUS_PLUS_END_GUARD

#endif
