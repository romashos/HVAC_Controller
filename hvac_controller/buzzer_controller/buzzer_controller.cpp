#include "buzzer_controller.hpp"

namespace {
PwmOut *speaker_ptr = nullptr;
constexpr int MAX_NOTES = 30;
constexpr float BEAT_TO_MS = 250.0f;
}

void init_buzzer(PinName pin) {
    delete speaker_ptr;
    speaker_ptr = new PwmOut(pin);
    speaker_ptr->write(0.0f);
}

void play_signal(Signal *signal_ptr) {
    if (signal_ptr == nullptr || signal_ptr->length <= 0) {
        stop_signal();
        return;
    }

    int count = signal_ptr->length;
    if (count > MAX_NOTES) {
        count = MAX_NOTES;
    }

    for (int i = 0; i < count; ++i) {
        float freq = signal_ptr->freq[i];
        float beat = signal_ptr->beat[i];

        if (freq > 0.0f && beat > 0.0f) {
            speaker_ptr->period(1.0f / freq);
            speaker_ptr->write(0.5f);
            int note_ms = static_cast<int>(beat * BEAT_TO_MS);
            if (note_ms < 1) {
                note_ms = 1;
            }
            ThisThread::sleep_for(chrono::milliseconds(note_ms));
        } else {
            stop_signal();
            int rest_ms = static_cast<int>(beat * BEAT_TO_MS);
            if (rest_ms > 0) {
                ThisThread::sleep_for(chrono::milliseconds(rest_ms));
            }
        }

        stop_signal();
        ThisThread::sleep_for(20ms);
    }

    stop_signal();
}

void stop_signal() {
    speaker_ptr->write(0.0f);
}