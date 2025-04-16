#ifndef MAX_LINES_HEURISTIC_H
#define MAX_LINES_HEURISTIC_H

#include "heuristics/heuristic.h"

namespace godot {

class MaxLinesHeuristic: public Heuristic {
    GDCLASS(MaxLinesHeuristic, Heuristic)

public:

    MaxLinesHeuristic();

    ~MaxLinesHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, ActionType action_type);

protected:

    static void _bind_methods();

private:
};

}

#endif