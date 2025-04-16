#ifndef BLOCK_LINES_HEURISTIC_H
#define BLOCK_LINES_HEURISTIC_H

#include "heuristics/heuristic.h"

namespace godot {

class BlockLinesHeuristic: public Heuristic {
    GDCLASS(BlockLinesHeuristic, Heuristic)

public:

    BlockLinesHeuristic();

    ~BlockLinesHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, ActionType action_type);

protected:

    static void _bind_methods();

private:
};

}

#endif