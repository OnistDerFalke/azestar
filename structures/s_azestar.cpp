#include "s_azestar.h"

s_azestar::s_azestar() {
    this->sws = ImVec2(500, 500);;
    this->t_ = 0;
    this->angle_= 0;
    this->line_radius = 75.0f;
    this->line_factor = 6.0f;
    this->line_number = 370;
    this->offset_x = sws.x/2;
    this->offset_y = sws.y/2;
    this->rotation_speed = 0.1f;
}

void s_azestar::run_base() {
    show_settings_window();
    show_simulation_window();
}

void s_azestar::show_settings_window() {
    ImGui::Begin("Simulation Settings");

    ImGui::Text("LINES");
    ImGui::SliderFloat("Line radius", &line_radius, 0.0f, 100.0f);
    ImGui::SliderFloat("Rotation speed", &rotation_speed, 0.0f, 50.0f);
    ImGui::SliderInt("Line number", &line_number, 0, 1000);
    ImGui::SliderFloat("Line factor", &line_factor, 0.0f, 100.0f);

    ImGui::Text("\nTRANSFORM");
    ImGui::SliderFloat("Horizontal offset", &offset_x, 0.0f, sws.x);
    ImGui::SliderFloat("Vertical offset", &offset_y, 0.0f, sws.y);
    ImGui::End();
}

void s_azestar::show_simulation_window() {
    ImGui::SetNextWindowSize(sws, ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Generated Structure");
    ImVec2 center = ImVec2(ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y);
    angle_ = fmodf(angle_ + rotation_speed * ImGui::GetIO().DeltaTime, static_cast<float>(2*M_PI));
    draw_structure(ImGui::GetWindowDrawList(), center);
    ImGui::End();
}

void s_azestar::draw_structure(ImDrawList* draw_list, ImVec2 center) {
    for (int i = 0; i < line_number; i++) {
        float t = t_ + i;
        float x  = sin(t / 10.0f) * line_radius + cos(t / line_factor) * line_radius;
        float y  = cos(t / 10.0f) * line_radius + sin(t / line_factor) * line_radius;
        float x2 = sin(t / 10.0f) * line_radius / 10.0f + cos(t / line_factor) * line_radius;
        float y2 = cos(t / 10.0f) * line_radius / 11.0f + sin(t / line_factor) * line_radius;

        float px = x * cos(angle_) - y * cos(angle_) + offset_x;
        float py = x * cos(angle_) + y * cos(angle_) + offset_y;
        float px2 = x2 * cos(angle_) - y2 * sin(angle_) + offset_x;
        float py2 = x2 * sin(angle_) + y2 * cos(angle_) + offset_y;

        draw_list->AddLine({ center.x + px, center.y + py }, { center.x + px2, center.y + py2 }, IM_COL32(255, 255, 255, 200));
        draw_list->AddCircleFilled({ center.x + px, center.y + py }, 1.0f, IM_COL32(255, 255, 255, 200));
        draw_list->AddCircleFilled({ center.x + px2, center.y + py2 }, 1.0f, IM_COL32(255, 255, 255, 200));

        t_ += 0.0007f * ImGui::GetIO().DeltaTime;
    }
}