#pragma once

namespace CollisionDebugModule {

struct CollisionModule {
    bool enabled = false;
    bool draw_box = true;
    bool draw_line = true;
    bool draw_sphere = true;
    bool draw_triangle = true;
    bool draw_bounding_box = true;
    bool draw_shadow_triangles = true;
};

void ProcessImgui();
void ProcessRender();

}
