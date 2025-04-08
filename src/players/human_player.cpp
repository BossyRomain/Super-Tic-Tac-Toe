#include "players/human_player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/camera2d.hpp>

using namespace godot;

HumanPlayer::HumanPlayer(): m_action(Actions::PLACE_PAWN) {

}

HumanPlayer::~HumanPlayer() {

}

void HumanPlayer::_input(Ref<InputEvent> event) {
    if(event->is_action_pressed("action")) {
        Vector2 mouse_pos = get_viewport()->get_mouse_position();
        mouse_pos = get_viewport()->get_camera_2d()->get_canvas_transform().affine_inverse().xform(mouse_pos);
        set_process_input(false);
        emit_signal("action_choosed", m_get_cell_coords.call(mouse_pos), m_action);
    }
}

int HumanPlayer::get_action() const {
    return m_action;
}

Callable HumanPlayer::get_cell_coords_callable() const {
    return m_get_cell_coords;
}

void HumanPlayer::set_action(int action_type) {
    m_action = action_type;
}

void HumanPlayer::set_get_cell_coords_callable(Callable callable) {
    m_get_cell_coords = callable;
}

void HumanPlayer::play(Board *board) {
    set_process_input(true);
}

void HumanPlayer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("play", "board"), &HumanPlayer::play);

    ClassDB::bind_method(D_METHOD("get_action"), &HumanPlayer::get_action);
    ClassDB::bind_method(D_METHOD("set_action", "action"), &HumanPlayer::set_action);

    ClassDB::bind_method(D_METHOD("get_cell_coords_callable"), &HumanPlayer::get_cell_coords_callable);
    ClassDB::bind_method(D_METHOD("set_get_cell_coords_callable", "callable"), &HumanPlayer::set_get_cell_coords_callable);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "action"), "set_action", "get_action");
    ADD_PROPERTY(PropertyInfo(Variant::CALLABLE, "get_cell_coords"), "set_get_cell_coords_callable", "get_cell_coords_callable");
}