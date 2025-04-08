#ifndef MAX_PAWNS_HEURISTIC_H
#define MAX_PAWNS_HEURISTIC_H

#include "players/ai_heuristics/ai_heuristic.h"

namespace godot {

/**
 * Maximise the number of pawns the player has on the board.
 */
class MaxPawnsHeuristic: public AIHeuristic {
    GDCLASS(MaxPawnsHeuristic, AIHeuristic)

public:

    MaxPawnsHeuristic();

    ~MaxPawnsHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type);

protected:

    static void _bind_methods();

private:
};

}

#endif