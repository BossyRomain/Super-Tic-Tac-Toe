#ifndef MAX_PAWNS_HEURISTIC_H
#define MAX_PAWNS_HEURISTIC_H

#include "heuristics/heuristic.h"

namespace godot {

/**
 * Maximise the number of pawns the player has on the board.
 */
class MaxPawnsHeuristic: public Heuristic {
    GDCLASS(MaxPawnsHeuristic, Heuristic)

public:

    MaxPawnsHeuristic();

    ~MaxPawnsHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, ActionType action_type);

protected:

    static void _bind_methods();

private:
};

}

#endif