/*
 * Copyright 2026 Microsoft Corporation. All rights reserved.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "include/c/graphite_context.h"
#include "src/c/sk_types_priv.h"

#if defined(SK_GRAPHITE)
#include "include/gpu/graphite/Context.h"
#include "include/gpu/graphite/ContextOptions.h"
#include "include/gpu/graphite/Recorder.h"
#include "include/gpu/graphite/Recording.h"
#include "include/gpu/graphite/Surface.h"
#include "include/gpu/graphite/GraphiteTypes.h"
#if SK_VULKAN
#include "include/gpu/graphite/vk/VulkanGraphiteUtils.h"
#endif
#endif

// Graphite Context

graphite_context_t* graphite_context_make_vulkan(const gr_vk_backendcontext_t* vkBackendContext) {
#if defined(SK_GRAPHITE) && SK_VULKAN
    auto ctx = AsGrVkBackendContext(vkBackendContext);
    skgpu::graphite::ContextOptions options;
    auto context = skgpu::graphite::ContextFactory::MakeVulkan(ctx, options);
    return ToGraphiteContext(context.release());
#else
    return nullptr;
#endif
}

graphite_context_t* graphite_context_make_vulkan_with_options(const gr_vk_backendcontext_t* vkBackendContext, const graphite_context_options_t* options) {
#if defined(SK_GRAPHITE) && SK_VULKAN
    auto ctx = AsGrVkBackendContext(vkBackendContext);
    skgpu::graphite::ContextOptions opts;
    if (options) {
        opts.fGpuBudgetInBytes = options->fGpuBudgetInBytes;
        opts.fInternalMultisampleCount = options->fInternalMultisampleCount;
        opts.fDisableDriverCorrectnessWorkarounds = options->fDisableDriverCorrectnessWorkarounds;
    }
    auto context = skgpu::graphite::ContextFactory::MakeVulkan(ctx, opts);
    return ToGraphiteContext(context.release());
#else
    return nullptr;
#endif
}

void graphite_context_unref(graphite_context_t* context) {
    SK_ONLY_GRAPHITE(delete AsGraphiteContext(context));
}

bool graphite_context_is_device_lost(graphite_context_t* context) {
    return SK_ONLY_GRAPHITE(AsGraphiteContext(context)->isDeviceLost(), true);
}

int graphite_context_max_texture_size(graphite_context_t* context) {
    return SK_ONLY_GRAPHITE(AsGraphiteContext(context)->maxTextureSize(), 0);
}

bool graphite_context_insert_recording(graphite_context_t* context, graphite_recording_t* recording) {
#if defined(SK_GRAPHITE)
    skgpu::graphite::InsertRecordingInfo info;
    info.fRecording = AsGraphiteRecording(recording);
    return AsGraphiteContext(context)->insertRecording(info);
#else
    return false;
#endif
}

bool graphite_context_submit(graphite_context_t* context, bool syncToCpu) {
    return SK_ONLY_GRAPHITE(
        AsGraphiteContext(context)->submit(syncToCpu ? skgpu::graphite::SyncToCpu::kYes : skgpu::graphite::SyncToCpu::kNo),
        false);
}

void graphite_context_free_gpu_resources(graphite_context_t* context) {
    SK_ONLY_GRAPHITE(AsGraphiteContext(context)->freeGpuResources());
}

size_t graphite_context_current_budgeted_bytes(graphite_context_t* context) {
    return SK_ONLY_GRAPHITE(AsGraphiteContext(context)->currentBudgetedBytes(), 0);
}

size_t graphite_context_max_budgeted_bytes(graphite_context_t* context) {
    return SK_ONLY_GRAPHITE(AsGraphiteContext(context)->maxBudgetedBytes(), 0);
}

// Graphite Recorder

graphite_recorder_t* graphite_context_make_recorder(graphite_context_t* context) {
    return SK_ONLY_GRAPHITE(ToGraphiteRecorder(AsGraphiteContext(context)->makeRecorder().release()), nullptr);
}

sk_surface_t* graphite_recorder_make_render_target(graphite_recorder_t* recorder, const sk_imageinfo_t* imageInfo, bool mipmapped) {
#if defined(SK_GRAPHITE)
    SkImageInfo info = AsImageInfo(imageInfo);
    auto surface = SkSurfaces::RenderTarget(
        AsGraphiteRecorder(recorder),
        info,
        mipmapped ? skgpu::Mipmapped::kYes : skgpu::Mipmapped::kNo);
    return ToSurface(surface.release());
#else
    return nullptr;
#endif
}

graphite_recording_t* graphite_recorder_snap(graphite_recorder_t* recorder) {
    return SK_ONLY_GRAPHITE(ToGraphiteRecording(AsGraphiteRecorder(recorder)->snap().release()), nullptr);
}

void graphite_recorder_unref(graphite_recorder_t* recorder) {
    SK_ONLY_GRAPHITE(delete AsGraphiteRecorder(recorder));
}

void graphite_recorder_free_gpu_resources(graphite_recorder_t* recorder) {
    SK_ONLY_GRAPHITE(AsGraphiteRecorder(recorder)->freeGpuResources());
}

// Graphite Recording

void graphite_recording_unref(graphite_recording_t* recording) {
    SK_ONLY_GRAPHITE(delete AsGraphiteRecording(recording));
}
