#ifndef WIN_HEURISTIC_H
#define WIN_HEURISTIC_H

#include "heuristics/heuristic.h"

namespace godot {

/**
 * Plays a winning action as soon as possible.
 */
class WinHeuristic: public Heuristic {
    GDCLASS(WinHeuristic, Heuristic)

public:

    WinHeuristic();    

    ~WinHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, ActionType action_type) override;

protected:

    static void _bind_methods();

private:
};

}

#endif