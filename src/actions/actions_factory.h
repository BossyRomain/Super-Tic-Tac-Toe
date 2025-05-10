#ifndef ACTIONS_FACTORY_H
#define ACTIONS_FACTORY_H

#include <godot_cpp/core/object.hpp>
#include "actions/action_place_pawn.h"
#include "actions/action_replace_pawn.h"
#include "actions/action_ban_cell.h"
#include "actions/action_switch_pawns.h"

namespace godot {

class ActionsFactory: public Object {
    GDCLASS(ActionsFactory, Object);

public:

    ActionsFactory();
    
    ~ActionsFactory();

    static Action* create_place_pawn_action(Vector2i coords);

    static Action* create_replace_pawn_action(Vector2i coords);

    static Action* create_ban_cell_action(Vector2i coords);

    static Action* create_switch_pawns_action();

protected:

    static void _bind_methods();
};

}

#endif