#ifndef ACTION_SWITCH_PAWNS_H
#define ACTION_SWITCH_PAWNS_H

#include "actions/action.h"

namespace godot {

class ActionSwitchPawns: public Action {
    GDCLASS(ActionSwitchPawns, Action);

public:

    ActionSwitchPawns();

    ~ActionSwitchPawns();

    bool execute(GameState *game_state) override;
    
    virtual Action* duplicate() const override;

protected:

    static void _bind_methods();
};

}

#endif