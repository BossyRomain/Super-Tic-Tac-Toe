#ifndef CONTROL_CENTER_HEURISTIC_H
#define CONTROL_CENTER_HEURISTIC_H

#include "players/ai_heuristics/ai_heuristic.h"

namespace godot {

/**
 * Places the pawns of the player the nearest of the center of the board.
 */
class ControlCenterHeuristic: public AIHeuristic {
    GDCLASS(ControlCenterHeuristic, AIHeuristic)

public:

    ControlCenterHeuristic();

    ~ControlCenterHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type);

protected:

    static void _bind_methods();

private:
};

}

#endif