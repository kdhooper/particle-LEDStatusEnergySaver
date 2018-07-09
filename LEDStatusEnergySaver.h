/** @file LEDStatusEnergySaver.h
 *  @brief A customized Particle.io status LED pattern for low-power.
 *
 *  This file implements a subclass of LEDStatus for use in low-power scenarios.
 *  It minimizes on-time while being relatively noticable for a user.
 *
 *  @author    Daniel Hooper
 *  @copyright Copyright Daniel Hooper 2017
 *  @date      2017
 *  @license   MIT. See LICENSE file.
 *
 *  @bug No known bugs.
 */

#ifndef __LEDSTATUSENERGYSAVER_H
#define __LEDSTATUSENERGYSAVER_H

#include <Particle.h>

/** @class An energy-conserving status LED pattern
 *
 *  This class implements a low-power blink pattern for Particle.io hardware
 *  devices. The pattern turns the LED on for 50ms every blinkPeriod for an
 *  effective duty cycle of 50/blinkPeriod.
 *
 *  @note 50ms is approximately the optimum time for the human eye to perceive
 *        the flash at full brightness.
 *
 */
class LEDStatusEnergySaver: public LEDStatus {
public:

  /** @brief Initialize parent class with given data
   *
   *  This constructor defaults to 1 second period and 1 blink.
   *
   *  @param priority         Priority of blink pattern. See Particle documentation.
   *  @param color            Color of LED. See Particle documentation.
   */
  explicit LEDStatusEnergySaver(LEDPriority priority, uint32_t color) :
      LEDStatus(LED_PATTERN_CUSTOM, priority),
      m_LEDcolor(color),
      m_blinkPeriod(1000),
      m_numFlashes(1),
      m_periodTicks(0),
      m_flashTicks(0),
      m_flashCount(0),
      m_state(state_init)
      {
  }

  /** @brief Initialize parent class with given data
   *
   *  @param priority         Priority of blink pattern. See Particle documentation.
   *  @param color            Color of LED. See Particle documentation.
   *  @param blinkPeriod      Cycle time (ms) of LED blink. blinkPeriod > 100 is recommended.
   */
  explicit LEDStatusEnergySaver(LEDPriority priority, uint32_t color, uint32_t blinkPeriod) :
      LEDStatus(LED_PATTERN_CUSTOM, priority),
      m_LEDcolor(color),
      m_periodTicks(0),
      m_flashTicks(0),
      m_flashCount(0),
      m_blinkPeriod(blinkPeriod),
      m_numFlashes(1),
      m_state(state_init)
      {
  }

    /** @brief Initialize parent class with given data
     *
     *  @param priority         Priority of blink pattern. See Particle documentation.
     *  @param color            Color of LED. See Particle documentation.
     *  @param blinkPeriod      Cycle time (ms) of LED blink. blinkPeriod > 100 is recommended.
     *  @param numFlashes       Number of strobes
     */
    explicit LEDStatusEnergySaver(LEDPriority priority, uint32_t color, uint32_t blinkPeriod, uint8_t numFlashes) :
        LEDStatus(LED_PATTERN_CUSTOM, priority),
        m_LEDcolor(color),
        m_periodTicks(0),
        m_flashTicks(0),
        m_flashCount(0),
        m_blinkPeriod(blinkPeriod),
        m_numFlashes(numFlashes),
        m_state(state_init)
        {
    }

protected:

    /** Update LED state
     *
     *  This function makes specific effort to ensure that the minimum on and off times are
     *  honored because when the CPU is severely throttled, the low update rate may cause the entire
     *  150ms flash period to 'gallop'.
     *
     *  @note setColor *must* be called in each update() call, otherwise the LED will default to off.
     *        Since this behavior is not documented it is presumed to be undefined and is explicitly set
     *        here to prevent future API changes from altering this class's behavior.
     *
     */
    virtual void update(system_tick_t ticks) override {

        m_periodTicks += ticks;


        if (m_flashCount < m_numFlashes) {
          switch(m_state) {
            case state_init:
              m_flashTicks = 0;
              m_state = state_flash;
              setColor(m_LEDcolor);

            break;

            case state_flash:
              m_flashTicks += ticks;
              if (m_flashTicks < 50)  {
                setColor(m_LEDcolor);
              }
              else {
                setColor(0);
                m_state = state_blank;
                m_flashTicks = 0;
              }
            break;

            case state_blank:
              m_flashTicks += ticks;
              setColor(0);
              if (m_flashTicks >= 100) {
                m_state = state_init;
                m_flashCount++;
              }
            break;

            default:
              // this should be unreachable
            break;
          }
        }
        else setColor(0);

        if (m_periodTicks >= m_blinkPeriod) {   // reset counts after period expires
          m_periodTicks = 0;
          m_flashCount = 0;
          m_state = state_init;

        }
    }

private:
    system_tick_t m_periodTicks;
    system_tick_t m_flashTicks;

    const uint32_t m_LEDcolor;
    const uint32_t m_blinkPeriod;
    const uint8_t  m_numFlashes;

    uint8_t m_flashCount;

    enum {state_init, state_flash, state_blank} m_state;

};

#endif
