#include "../../button_controller/button_controller.hpp"
#include "../../button_controller/button_controller_heat.cpp"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <functional>

using ::testing::_;
using ::testing::SaveArg;

class MockInterruptPin : public IInterruptPin {
public:
    MOCK_METHOD(void, on_fall, (std::function<void()> cb), (override));
};

TEST(ButtonHeatTest, RegistersFallingEdgeCallbackOnConstruction) {
    MockInterruptPin mock_pin;

    EXPECT_CALL(mock_pin, on_fall(_)).Times(1);

    ButtonHeat button(mock_pin);
}

TEST(ButtonHeatTest, SimulatedPressTurnsFanOffWhenFanIsOn) {
    fan = ON;

    MockInterruptPin mock_pin;
    std::function<void()> fall_callback;

    EXPECT_CALL(mock_pin, on_fall(_))
        .Times(1)
        .WillOnce(SaveArg<0>(&fall_callback));

    ButtonHeat button(mock_pin);

    ASSERT_TRUE(static_cast<bool>(fall_callback));

    // Simulate a falling-edge button press
    fall_callback();

    EXPECT_EQ(fan, OFF);
}

TEST(ButtonHeatTest, SimulatedPressLeavesFanOffWhenAlreadyOff) {
    fan = OFF;

    MockInterruptPin mock_pin;
    std::function<void()> fall_callback;

    EXPECT_CALL(mock_pin, on_fall(_))
        .Times(1)
        .WillOnce(SaveArg<0>(&fall_callback));

    ButtonHeat button(mock_pin);

    ASSERT_TRUE(static_cast<bool>(fall_callback));

    fall_callback();

    EXPECT_EQ(fan, OFF);
}

TEST(ButtonHeatTest, DirectIsrCallTurnsFanOffWhenFanIsOn) {
    fan = ON;

    MockInterruptPin mock_pin;
    EXPECT_CALL(mock_pin, on_fall(_)).Times(1);

    ButtonHeat button(mock_pin);
    button.ISR();

    EXPECT_EQ(fan, OFF);
}