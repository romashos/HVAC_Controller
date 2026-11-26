// This is a test harness for the buzzer controller. It checks for the correct 
// implementation of the signal being played by calculating frequency and ms duration 
// and comparing these to the expected numbers

#include "../../buzzer_controller/tunes.hpp"
#include <cassert>
#include <cstdio>
#include <vector>

Signal test_alarm = {
    "Alarm",
    2,
    {1200.0f, 0.0f}, // first note
    {0.25f, 0.5f}    // second note
};

struct ToneEvent {
    float freq;
    int duration_ms;
};

class MockSpeaker {
    public:
    std::vector<ToneEvent> events;

    void play_note(float freq, int duration_ms) {
        events.push_back({freq, duration_ms});
    }

    void stop() {
        events.push_back({0.0f, 0});
    }
};

void simulate_signal(MockSpeaker &speaker, Signal *signal_ptr) {
    if (signal_ptr == nullptr || signal_ptr->length <= 0) {
        speaker.stop();
        return;
    }

    int count = signal_ptr->length;
    if (count > 30) {
        count = 30;
    }

    for (int i = 0; i < count; ++i) {
        float freq = signal_ptr->freq[i];
        float beat = signal_ptr->beat[i];

        int ms = static_cast<int>(beat * 250.0f);
        if (ms < 1) {
            ms = 1;
        }

        if (freq > 0.0f && beat > 0.0f) {
            speaker.play_note(freq, ms);
            } else {
                speaker.stop();
            }

        speaker.stop();
    }

    speaker.stop();
}

int main() {
    int failures = 0;

    auto check = [&](bool condition, const char* message) {
        if (!condition) {
            std::printf("FAIL: %s\n", message);
            ++failures;
        }
    };

    MockSpeaker speaker;
    simulate_signal(speaker, &test_alarm);

    check(speaker.events.size() == 5, "expected speaker.events.size() == 5");
    check(speaker.events[0].freq == 1200.0f, "expected speaker.events[0].freq == 1200.0f");
    check(speaker.events[0].duration_ms == 62, "expected speaker.events[0].duration_ms == 62");

    simulate_signal(speaker, nullptr);

    if (failures > 0) {
        std::printf("%d test check(s) failed\n", failures);
        return 1;
    }

    std::printf("Event, frequency and beat tests passed\n");
    return 0;
}