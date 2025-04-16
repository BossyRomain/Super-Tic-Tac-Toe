#include "heuristics/max_pawns_heuristic.h"

using namespace godot;

MaxPawnsHeuristic::MaxPawnsHeuristic() {

}

MaxPawnsHeuristic::~MaxPawnsHeuristic() {

}

double MaxPawnsHeuristic::calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, ActionType action_type) {
    return action_type == ActionType::PLACE_PAWN || action_type == ActionType::REPLACE_PAWN ? 1.0 : 0.0;
}

void MaxPawnsHeuristic::_bind_methods() {
    
}