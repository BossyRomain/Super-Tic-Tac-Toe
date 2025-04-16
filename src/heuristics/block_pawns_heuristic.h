#ifndef BLOCK_PAWNS_HEURISTIC_H
#define BLOCK_PAWNS_HEURISTIC_H

#include "heuristics/heuristic.h"

namespace godot {

/**
 * Try to place pawns next to the maximum amount of others players pawns.
*/
class BlockPawnsHeuristic: public Heuristic {
    GDCLASS(BlockPawnsHeuristic, Heuristic)

public:

    BlockPawnsHeuristic();

    ~BlockPawnsHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, ActionType action_type);

protected:

    static void _bind_methods();

private:
};

}

#endif