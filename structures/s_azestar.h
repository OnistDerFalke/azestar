#ifndef AZESTAR_S_AZESTAR_H
#define AZESTAR_S_AZESTAR_H

#include "imgui/imgui.h"
#include "structure.h"
#include <cmath>

class s_azestar : public structure {
public:
    s_azestar();
    void run_base();

private:
    float t_;
    float angle_;
    float line_radius;
    float line_factor;
    int line_number;
    float offset_x;
    float offset_y;
    float rotation_speed;
    ImVec2 sws;

    void show_settings_window() override;
    void show_simulation_window() override;
    void draw_structure(ImDrawList* draw_list, ImVec2 center);
};


#endif
