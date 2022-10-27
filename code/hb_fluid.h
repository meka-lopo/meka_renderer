#ifndef HB_FLUID_H
#define HB_FLUID_H

// NOTE(gh) Initial state for all of the elements is 0
struct FluidCube
{
    // Determines how resistent the fluid is to flow. High number means the fluid is very resistent.
    f32 viscosity; 

    v3u cell_count; // includes the boundary
    f32 cell_dim; // each cell is a uniform cube

    f32 *v_x_dest;
    f32 *v_x_source;
    f32 *v_y_dest;
    f32 *v_y_source;
    f32 *v_z_dest;
    f32 *v_z_source;
    f32 *density_dest;
    f32 *density_source;
    
    // 2*x*y*z cells
    // for velocity, bottom half will be used as source force at first 
    // TODO(gh) This is just screaming for optimization using SIMD ><
    f32 *v_x;
    f32 *v_y;
    f32 *v_z;
    f32 *densities;
    f32 *pressures; // Used implicitly by the projection
    u32 stride;
};

enum ElementTypeForBoundary
{
    // These values require the boundary to be an exact negative value of the neighbor.
    // For example, v0jk.x = -v1jk.x, vi0k.y = -vi1k.y, and so one.
    // This counteracts the fluid from going outside the boundary.
    ElementTypeForBoundary_x,
    ElementTypeForBoundary_y,
    ElementTypeForBoundary_z,

    // For these values, we are setting the same value as the neighbor.
    // For example, d0jk = d1jk
    ElementTypeForBoundary_Continuous,
};

#endif