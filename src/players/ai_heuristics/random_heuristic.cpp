#include "players/ai_heuristics/random_heuristic.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

RandomHeuristic::RandomHeuristic() {
    srand(time(NULL));
}

RandomHeuristic::~RandomHeuristic() {

}

double RandomHeuristic::calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type) {
    return ((rand() % 200) - 100) / 100.0;
}

void RandomHeuristic::_bind_methods() {

}