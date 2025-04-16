#include "heuristics/heuristic.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Heuristic::Heuristic(): m_weight(1.0) {

}

Heuristic::~Heuristic() {

}

double Heuristic::get_weight() const {
    return m_weight;
}

void Heuristic::set_weight(double weight) {
    m_weight = weight;
}

double Heuristic::calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, ActionType action_type) {
    return 0.0;
}

void Heuristic::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_weight"), &Heuristic::get_weight);
    ClassDB::bind_method(D_METHOD("set_weight", "weight"), &Heuristic::set_weight);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "weight"), "set_weight", "get_weight");
}