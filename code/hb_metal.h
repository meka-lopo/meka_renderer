#ifndef HB_METAL_H
#define HB_METAL_H

// NOTE(joon) shared buffer between CPU and GPU, in a coherent way
struct MetalSharedBuffer
{
    u32 max_size;
    void *memory; // host memory

    id<MTLBuffer> buffer;
};

// NOTE(joon) shared buffer between CPU and GPU, but needs to be exclusively synchronized(flushed)
struct MetalManagedBuffer
{
    u32 max_size;
    void *memory; // host memory

    u32 used;
    id<MTLBuffer> buffer;
};

// TODO(gh) maybe this is a good idea?
struct MetalTexture2D
{
    id<MTLTexture> texture;
    i32 width;
    i32 height;
};

struct MetalRenderContext
{
    id<MTLDevice> device;
    MTKView *view;
    id<MTLCommandQueue> command_queue;

    id<MTLDepthStencilState> depth_state; // compare <=, write : enabled
    id<MTLDepthStencilState> disabled_depth_state; // write : disabled

    // Pipelines
    id<MTLRenderPipelineState> cube_pipeline;
    id<MTLRenderPipelineState> line_pipeline;
    id<MTLRenderPipelineState> deferred_lighting_pipeline;
    id<MTLRenderPipelineState> directional_light_shadowmap_pipeline;
    id<MTLRenderPipelineState> screen_space_triangle_pipeline;
    
    // Renderpasses
    MTLRenderPassDescriptor *directional_light_shadowmap_renderpass;

    // NOTE(gh) G buffer generation + lighting renderpass
    // TODO(gh) One downside of this single pass is that we don't have access to depth buffer
    MTLRenderPassDescriptor *single_lighting_renderpass; 

    // Textures
    id<MTLTexture> g_buffer_position_texture;
    id<MTLTexture> g_buffer_normal_texture;
    id<MTLTexture> g_buffer_color_texture;
    id<MTLTexture> g_buffer_depth_texture;

    i32 directional_light_shadowmap_depth_texture_width;
    i32 directional_light_shadowmap_depth_texture_height;
    id<MTLTexture> directional_light_shadowmap_depth_texture;

    // Buffers
    MetalManagedBuffer voxel_position_buffer;
    MetalManagedBuffer voxel_color_buffer;

    MetalManagedBuffer cube_inward_facing_index_buffer;
    MetalManagedBuffer cube_outward_facing_index_buffer;
};

#endif
