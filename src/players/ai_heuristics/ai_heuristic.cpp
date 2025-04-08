#include "players/ai_heuristics/ai_heuristic.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

AIHeuristic::AIHeuristic(): m_weight(1.0) {

}

AIHeuristic::~AIHeuristic() {

}

double AIHeuristic::get_weight() const {
    return m_weight;
}

void AIHeuristic::set_weight(double weight) {
    m_weight = weight;
}

double AIHeuristic::calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type) {
    return 0.0;
}

void AIHeuristic::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_weight"), &AIHeuristic::get_weight);
    ClassDB::bind_method(D_METHOD("set_weight", "weight"), &AIHeuristic::set_weight);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "weight"), "set_weight", "get_weight");
}