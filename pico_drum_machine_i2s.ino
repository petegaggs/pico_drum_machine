/*
  Pico drum machine
  using sampled sounds and I2S DAC

MIT License

Copyright (c) 2023 petegaggs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <I2S.h>
#include "bd.h"
#include "sd.h"
#include "ch.h"
#include "oh.h"
#include "lt.h"
#include "ht.h"
#include "patterns.h"


#define TEMPO_PIN 26 //ADC0
#define PATTERN_PIN 28 //ADC2
#define RUN_PIN 16
#define I2S_DATA_PIN 9
#define I2S_BCK_PIN 10
#define I2S_WS_PIN 11
#define SAMPLE_RATE 32000
#define SAMPLE_DEPTH 16

uint8_t step_count = 0;
uint8_t pattern_length = 16;
uint8_t pattern_sel = 5;
uint32_t tempo = 125;
uint16_t sample_pnt_bd = 0;
uint16_t sample_cnt_bd = 0;
uint16_t sample_pnt_sd = 0;
uint16_t sample_cnt_sd = 0;
uint16_t sample_pnt_ch = 0;
uint16_t sample_cnt_ch = 0;
uint16_t sample_pnt_oh = 0;
uint16_t sample_cnt_oh = 0;
uint16_t sample_pnt_lt = 0;
uint16_t sample_cnt_lt = 0;
uint16_t sample_pnt_ht = 0;
uint16_t sample_cnt_ht = 0;
uint16_t out_sample;
uint8_t triggers;
bool running;
// sequencer stuff
uint32_t current_millis;
uint32_t previous_millis = 0;

// Create the I2S port using a PIO state machine
I2S i2s(OUTPUT);

void setup() {
  pinMode(RUN_PIN, INPUT_PULLUP);
  running =  get_run_mode();
  i2s.setBCLK(I2S_BCK_PIN);
  i2s.setDATA(I2S_DATA_PIN);
  i2s.setBitsPerSample(SAMPLE_DEPTH);
  i2s.begin(SAMPLE_RATE);
}

uint32_t get_tempo() {
  return ((1023 - analogRead(TEMPO_PIN)) >> 2) + 75;
}

uint8_t get_pattern() {
  return analogRead(PATTERN_PIN) >> 7;
}

bool get_run_mode() {
  return digitalRead(RUN_PIN);
}

void loop() {
  tempo = get_tempo();
  pattern_sel = get_pattern();
  current_millis = millis();
  if (current_millis - previous_millis > tempo) {
    previous_millis = current_millis;
    triggers = patterns[(pattern_sel * MAX_PATTERN_LENGTH) + step_count];
    if (triggers & BD_MASK) {
      sample_pnt_bd = 0;
      sample_cnt_bd = BD_SAMPLES;
    }
    if (triggers & SD_MASK) {
      sample_pnt_sd = 0;
      sample_cnt_sd = SD_SAMPLES;
    }
    if (triggers & CH_MASK) {
      sample_pnt_ch = 0;
      sample_cnt_ch = CH_SAMPLES;
    }
    if (triggers & OH_MASK) {
      sample_pnt_oh = 0;
      sample_cnt_oh = OH_SAMPLES;
    }
    if (triggers & LT_MASK) {
      sample_pnt_lt = 0;
      sample_cnt_lt = LT_SAMPLES;
    }
    if (triggers & HT_MASK) {
      sample_pnt_ht = 0;
      sample_cnt_ht = HT_SAMPLES;
    }
    step_count++;
    if (step_count == pattern_length) {
      step_count = 0;
    }
  }
  out_sample = 0;

  if (sample_cnt_bd) {
    out_sample += bd_raw[sample_pnt_bd++];
    sample_cnt_bd--;
  }
  if (sample_cnt_sd) {
    out_sample += sd_raw[sample_pnt_sd++];
    sample_cnt_sd--;
  }
  if (sample_cnt_ch) {
    out_sample += ch_raw[sample_pnt_ch++];
    sample_cnt_ch--;
  }
  if (sample_cnt_oh) {
    out_sample += oh_raw[sample_pnt_oh++];
    sample_cnt_oh--;
  }
  if (sample_cnt_lt) {
    out_sample += lt_raw[sample_pnt_lt++];
    sample_cnt_lt--;
  }
  if (sample_cnt_ht) {
    out_sample += ht_raw[sample_pnt_ht++];
    sample_cnt_ht--;
  }

  i2s.write(out_sample); // left
  i2s.write(out_sample); // right

}  
