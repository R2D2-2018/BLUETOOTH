#ifndef UART_TEST_BENCH_HPP
#define UART_TEST_BENCH_HPP

#include "UART_LIB/io_stream.hpp"
#include "catch.hpp"

#include <functional>
#include <vector>

/**
 * @brief Behavior component for compile-time polymorphism for UARTTestBench
 *
 * @details
 * TxRoutine and rxRoutine are the routines called by putc and getc respectively.
 * That way it is possible to easily emulate UART hardware by programming a
 * UARTTestBenchBehavior component and injecting it into UARTTestBench.
 */
class UARTTestBenchBehavior {
  public:
    void txRoutine(char c);
    char rxRoutine();
};

/**
 * @brief ConstantRx behavioral component for UARTTestBench
 *
 * @details
 * This class proxies rxRoutine to an internal array of data.
 * Every getc call will consume an item from rxData.
 */
class ConstantRx : public UARTTestBenchBehavior {
    std::vector<char> rxData;
    uint32_t rxCount;

  public:
    /**
     * @brief Dummy function, no functionality
     *
     * @param c Unused
     */
    void txRoutine(char c) {
    }

    /**
     * @brief Returns the next char in buffer
     *
     * @details
     * Captures the next char in buffer, increments the buffer counter to keep track
     * of the sent characters. Then returns the captured char.
     *
     * @return char Next char in buffer
     */
    char rxRoutine() {
        return rxData.at(rxCount++);
    }

  public:
    /**
     * @brief Construct a new Constant Rx object
     *
     */
    ConstantRx() : rxData{}, rxCount(0) {
    }

    /**
     * @brief Construct a new Constant Rx object with rxData as data
     *
     * @param data Data to construct rxData with
     */
    ConstantRx(std::initializer_list<char> data) : rxData{data}, rxCount(0) {
    }
};

/**
 * @brief UARTTestBench connection for virtual uart testing
 *
 * @details
 * This class derives from IOStream, just like HardwareUART does.
 * If the tested classes refer to HardwareUART as a IOStream,
 * it will be possible to emulate hardware and use a virtual UART
 * interface to test classes.
 *
 * @tparam BEHAVIOR_COMPONENT_T Behavior component for this uart stream to use.
 */
template <class BEHAVIOR_COMPONENT_T>
class UARTTestBench : public IOStream {
    static_assert(std::is_base_of<UARTTestBenchBehavior, BEHAVIOR_COMPONENT_T>::value,
                  "BEHAVIOR_COMPONENT_T must derive from UARTTestBenchBehaviorComponent");
    BEHAVIOR_COMPONENT_T testBehavior;

    /**
     * @brief Runs the test behavior's txRoutine with the transmitted char
     *
     * @param c Character as determined by the tested code
     */
    void putc(char c) override {
        testBehavior.txRoutine(c);
    }

    /**
     * @brief Runs the test behavior's txRoutine with the transmitted string
     *
     * @param s Character as determined by the tested code
     */
    void puts(const char *s) override {
        for (int i = 0; s[i] != '\n'; ++i) {
            testBehavior.txRoutine(s[i]);
        }
    }

    /**
     * @brief Reports if this UART is working
     *
     * @return true
     */
    unsigned int count_available() override {
        static int i = 5;
        return i--;
    }

    /**
     * @brief Runs the test behavior's rxRoutine and returns the received char
     *
     * @return char Character as determined by testBehavior.rxRoutine()
     */
    char getc() override {
        return testBehavior.rxRoutine();
    }

  public:
    /**
     * @brief Construct a new UARTTestBench object
     *
     * @param testBehavior Behavior component to use for emulating hardware
     */
    UARTTestBench(BEHAVIOR_COMPONENT_T testBehavior) : testBehavior(testBehavior) {
    }

    /**
     * @brief Construct a new UARTTestBench and propagates the initializerList to the test behavior's constructor
     *
     * @param initializerList
     */
    UARTTestBench(std::initializer_list<char> initializerList) : testBehavior{initializerList} {
    }
};

/**
 * @brief Test UARTTestBench
 *
 * @details
 * This test case tests the ability of UARTTestBench to function using a constant series of rx data.
 */
TEST_CASE("Test UARTTestBench") {
    UARTTestBench<ConstantRx> uart{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
                                   0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F};

    char data[32] = {};

    for (int i = 0; i < 32; i++) {
        uart >> data[i];
    }

    REQUIRE(data[0] == 0x00);
    REQUIRE(data[1] == 0x01);
    REQUIRE(data[2] == 0x02);
    REQUIRE(data[3] == 0x03);
    REQUIRE(data[4] == 0x04);
    REQUIRE(data[5] == 0x05);
    REQUIRE(data[6] == 0x06);
    REQUIRE(data[7] == 0x07);
    REQUIRE(data[8] == 0x18);
    REQUIRE(data[9] == 0x19);
    REQUIRE(data[10] == 0x1A);
    REQUIRE(data[11] == 0x1B);
    REQUIRE(data[12] == 0x1C);
    REQUIRE(data[13] == 0x1D);
    REQUIRE(data[14] == 0x1E);
    REQUIRE(data[15] == 0x1F);
    REQUIRE(data[16] == 0x60);
    REQUIRE(data[17] == 0x61);
    REQUIRE(data[18] == 0x62);
    REQUIRE(data[19] == 0x63);
    REQUIRE(data[20] == 0x64);
    REQUIRE(data[21] == 0x65);
    REQUIRE(data[22] == 0x66);
    REQUIRE(data[23] == 0x67);
    REQUIRE(data[24] == 0x78);
    REQUIRE(data[25] == 0x79);
    REQUIRE(data[26] == 0x7A);
    REQUIRE(data[27] == 0x7B);
    REQUIRE(data[28] == 0x7C);
    REQUIRE(data[29] == 0x7D);
    REQUIRE(data[30] == 0x7E);
    REQUIRE(data[31] == 0x7F);
}

#endif // UART_TEST_BENCH_HPP