#pragma once
#include <raylib.h>

#include "Components.h"

#define NUM_RECS 4

struct Gui {
    void Init(State state);
    void ChangeLayout(State);
    State Draw(State);

    Rectangle layoutRecs[NUM_RECS];
};
