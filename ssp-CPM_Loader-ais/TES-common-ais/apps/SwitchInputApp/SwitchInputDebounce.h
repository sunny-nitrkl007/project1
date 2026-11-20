#pragma once

#include <climits>

namespace switch_input
{
enum STG { OPEN = 0, CLOSED = 1, UNKNOWN = 2 };

template<class States>
void debounce(const int (&currentStates)[4], int (&counts_)[4], int (&previousStates_)[4],
              States& debouncedStates_, bool& publishState_, int openDebounceCount_,
              int closedDebounceCount_)
{
    for (int ii = 0; ii < 4; ++ii) {
        int currentState = currentStates[ii];

        if (currentState != previousStates_[ii]) {
            // Something changed, reset the counter
            counts_[ii] = 0;
            previousStates_[ii] = currentState;
        }
        else if (counts_[ii] < INT_MAX) {
            // Same state as last time, increment count.
            ++counts_[ii];
        }


        if (currentState == debouncedStates_.stg_values[ii].value) {
            // Already debounced
        }
        else if ((currentState == STG::OPEN) && (counts_[ii] >= openDebounceCount_)) {
            // Debounced to the OPEN state
            debouncedStates_.stg_values[ii].value = STG::OPEN;
            publishState_ = true;
        }
        else if ((currentState == STG::CLOSED) && (counts_[ii] >= closedDebounceCount_)) {
            // Debounced to the CLOSED state
            debouncedStates_.stg_values[ii].value = STG::CLOSED;
            publishState_ = true;
        }
    }
}
}
