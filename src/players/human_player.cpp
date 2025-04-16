#include "players/human_player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <future>
#include <thread>

using namespace godot;

HumanPlayer::HumanPlayer(): m_action_type(ActionType::PLACE_PAWN) {

}

HumanPlayer::~HumanPlayer() {

}

void HumanPlayer::_input(Ref<InputEvent> event) {
    if(event->is_action_pressed("action")) {
        Vector2 mouse_pos = get_viewport()->get_mouse_position();
        mouse_pos = get_viewport()->get_camera_2d()->get_canvas_transform().affine_inverse().xform(mouse_pos);
        Vector2i cell_coords = m_get_cell_coords.call(mouse_pos);

        Action *action = memnew(Action);
        action->set_type(m_action_type);
        action->set_coords(cell_coords);
        action->set_player(this);

        set_process_input(false);
        emit_signal("action_choosed", action);
    }
}

void HumanPlayer::_ready() {
    set_process_input(false);
}

ActionType HumanPlayer::get_action_type() const {
    return m_action_type;
}

Callable HumanPlayer::get_cell_coords_callable() const {
    return m_get_cell_coords;
}

void HumanPlayer::set_action_type(ActionType action_type) {
    m_action_type = action_type;
}

void HumanPlayer::set_get_cell_coords_callable(Callable callable) {
    m_get_cell_coords = callable;
}

void HumanPlayer::choose_action(Board *board) {
    set_process_input(true);
}

void HumanPlayer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("choose_action", "board"), &HumanPlayer::choose_action);

    ClassDB::bind_method(D_METHOD("get_action_type"), &HumanPlayer::get_action_type);
    ClassDB::bind_method(D_METHOD("set_action_type", "action_type"), &HumanPlayer::set_action_type);

    ClassDB::bind_method(D_METHOD("get_cell_coords_callable"), &HumanPlayer::get_cell_coords_callable);
    ClassDB::bind_method(D_METHOD("set_get_cell_coords_callable", "callable"), &HumanPlayer::set_get_cell_coords_callable);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "action_type"), "set_action_type", "get_action_type");
    ADD_PROPERTY(PropertyInfo(Variant::CALLABLE, "get_cell_coords"), "set_get_cell_coords_callable", "get_cell_coords_callable");
}