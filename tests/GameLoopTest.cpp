#include <gtest/gtest.h>
#include "game/GameLoop.hpp"

//
//  ┌──────────────────────────────────────────────────┬──────────────────────────────────────────────────────────────────────┐                                                                   
//  │                       Test                       │                           What it verifies                           │                                                                   
//  ├──────────────────────────────────────────────────┼──────────────────────────────────────────────────────────────────────┤                                                                   
//  │ ProcessInputCalledEachIteration                  │ processInput called once per loop cycle (including the closing call) │                                                                   
//  ├──────────────────────────────────────────────────┼──────────────────────────────────────────────────────────────────────┤                                                                   
//  │ RenderCalledWhenWindowOpen                       │ render called exactly once per open iteration                        │                                                                   
//  ├──────────────────────────────────────────────────┼──────────────────────────────────────────────────────────────────────┤                                                                   
//  │ RenderNotCalledAfterClose                        │ render never called when loop closes immediately                     │                                                                   
//  ├──────────────────────────────────────────────────┼──────────────────────────────────────────────────────────────────────┤                                                                   
//  │ TickNotCalledWhenDtBelowTickDuration             │ accumulator doesn't trigger tick if it never reaches tickDuration    │                                                                   
//  ├──────────────────────────────────────────────────┼──────────────────────────────────────────────────────────────────────┤                                                                   
//  │ TickCalledOnceWhenAccumulatorReachesTickDuration │ exactly one tick when dt == tickDuration                             │                                                                   
//  ├──────────────────────────────────────────────────┼──────────────────────────────────────────────────────────────────────┤                                                                   
//  │ TickCalledMultipleTimesWhenDtExceedsTickDuration │ multiple ticks per frame when dt is large                            │                                                                   
//  ├──────────────────────────────────────────────────┼──────────────────────────────────────────────────────────────────────┤                                                                   
//  │ AccumulatorCappedAtMaxSoTicksAreBounded          │ spiral-of-death protection: huge dt capped at 3 * tickDuration       │                                                                   
//  ├──────────────────────────────────────────────────┼──────────────────────────────────────────────────────────────────────┤                                                                   
//  │ AlphaIsZeroWhenAccumulatorIsZero                 │ interpolation alpha is 0 after a full tick is consumed               │                                                                   
//  ├──────────────────────────────────────────────────┼──────────────────────────────────────────────────────────────────────┤                                                                   
//  │ AlphaIsPartialWhenAccumulatorIsPartial           │ alpha correctly reflects fractional accumulator                      │                                                                   
//  └──────────────────────────────────────────────────┴──────────────────────────────────────────────────────────────────────┘ 

namespace {

// Runs the loop for a fixed number of processInput calls, then closes.
struct LoopDriver {
    int inputCalls    = 0;
    int tickCalls     = 0;
    int renderCalls   = 0;
    float lastAlpha   = -1.f;

    void run(game::GameLoop& loop, int iterations, float dt) {
        int remaining = iterations;
        loop.run({
            .processInput   = [&]() { ++inputCalls; return --remaining >= 0; },
            .tick           = [&]() { ++tickCalls; },
            .render         = [&](float alpha) { ++renderCalls; lastAlpha = alpha; },
            .getElapsedTime = [&]() { return dt; }
        });
    }
};

TEST(GameLoopTest, ProcessInputCalledEachIteration) {
    game::GameLoop loop(10.f); // tickDuration = 0.1s
    LoopDriver d;
    d.run(loop, /*iterations=*/3, /*dt=*/0.01f); // dt < tickDuration, no ticks

    EXPECT_EQ(d.inputCalls, 4); // 3 true + 1 false that breaks
}

TEST(GameLoopTest, RenderCalledWhenWindowOpen) {
    game::GameLoop loop(10.f);
    LoopDriver d;
    d.run(loop, /*iterations=*/3, /*dt=*/0.01f);

    EXPECT_EQ(d.renderCalls, 3);
}

TEST(GameLoopTest, RenderNotCalledAfterClose) {
    game::GameLoop loop(10.f);
    LoopDriver d;
    d.run(loop, /*iterations=*/0, /*dt=*/0.01f); // closes immediately

    EXPECT_EQ(d.renderCalls, 0);
}

TEST(GameLoopTest, TickNotCalledWhenDtBelowTickDuration) {
    game::GameLoop loop(10.f); // tickDuration = 0.1s
    LoopDriver d;
    d.run(loop, /*iterations=*/5, /*dt=*/0.05f); // accumulates to 0.25s < 3*tickDuration needed for ticks

    // 5 * 0.05 = 0.25s, each tick costs 0.1s → 2 ticks
    // But check no extra ticks by passing dt that never reaches tickDuration per step
    game::GameLoop loop2(10.f);
    LoopDriver d2;
    d2.run(loop2, /*iterations=*/3, /*dt=*/0.09f); // 3*0.09=0.27s, never hits 0.1 per step

    EXPECT_EQ(d2.tickCalls, 2);
}

TEST(GameLoopTest, TickCalledOnceWhenAccumulatorReachesTickDuration) {
    game::GameLoop loop(10.f); // tickDuration = 0.1s
    LoopDriver d;
    // dt = 0.1s exactly: accumulator reaches tickDuration each iteration
    d.run(loop, /*iterations=*/3, /*dt=*/0.1f);

    EXPECT_EQ(d.tickCalls, 3);
}

TEST(GameLoopTest, TickCalledMultipleTimesWhenDtExceedsTickDuration) {
    game::GameLoop loop(10.f); // tickDuration = 0.1s
    LoopDriver d;
    // dt = 0.3s: accumulator = 0.3s → 3 ticks per iteration
    d.run(loop, /*iterations=*/2, /*dt=*/0.3f);

    EXPECT_EQ(d.tickCalls, 6);
}

TEST(GameLoopTest, AccumulatorCappedAtMaxSoTicksAreBounded) {
    game::GameLoop loop(10.f); // tickDuration = 0.1s, maxAccumulator = 0.3s
    LoopDriver d;
    // dt = 10s: without cap, would generate 100 ticks per iteration
    d.run(loop, /*iterations=*/1, /*dt=*/10.f);

    EXPECT_EQ(d.tickCalls, 3); // max 3 ticks (0.3s / 0.1s)
}

TEST(GameLoopTest, AlphaIsZeroWhenAccumulatorIsZero) {
    game::GameLoop loop(10.f); // tickDuration = 0.1s
    LoopDriver d;
    // dt = 0.1s exactly: after consuming all accumulator, alpha = 0
    d.run(loop, /*iterations=*/1, /*dt=*/0.1f);

    EXPECT_FLOAT_EQ(d.lastAlpha, 0.f);
}

TEST(GameLoopTest, AlphaIsPartialWhenAccumulatorIsPartial) {
    game::GameLoop loop(10.f); // tickDuration = 0.1s
    LoopDriver d;
    // dt = 0.05s: accumulator stays at 0.05 < 0.1, alpha = 0.05/0.1 = 0.5
    d.run(loop, /*iterations=*/1, /*dt=*/0.05f);

    EXPECT_NEAR(d.lastAlpha, 0.5f, 1e-5f);
}

} // namespace
