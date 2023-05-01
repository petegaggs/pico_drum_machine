// drum patterns
#define MAX_PATTERN_LENGTH 16
#define NUM_PATTERNS 6
#define BD_MASK 1 << 0
#define SD_MASK 1 << 1
#define CH_MASK 1 << 2
#define OH_MASK 1 << 3
#define LT_MASK 1 << 4
#define HT_MASK 1 << 5

const uint8_t patterns[MAX_PATTERN_LENGTH * NUM_PATTERNS] = {
  // Pattern 1: 8 beat Rock 1
  0b00000101, // step 1
  0b00000000, // step 2
  0b00000100, // step 3
  0b00000000, // step 4
  0b00000110, // step 5
  0b00000000, // step 6
  0b00000100, // step 7
  0b00000000, // step 8
  0b00000101, // step 9
  0b00000000, // step 10
  0b00000101, // step 11
  0b00000000, // step 12
  0b00000110, // step 13
  0b00000000, // step 14
  0b00000100, // step 15
  0b00000000, // step 16
  // Pattern 2: 8 beat Rock 2
  0b00000101, // step 1
  0b00000000, // step 2
  0b00000100, // step 3
  0b00000000, // step 4
  0b00000110, // step 5
  0b00000000, // step 6
  0b00000101, // step 7
  0b00000000, // step 8
  0b00000101, // step 9
  0b00000000, // step 10
  0b00000100, // step 11
  0b00000000, // step 12
  0b00000110, // step 13
  0b00000000, // step 14
  0b00000101, // step 15
  0b00000000, // step 16
  // Pattern 3: 8 beat Rock 3
  0b00000101, // step 1
  0b00000000, // step 2
  0b00000100, // step 3
  0b00000000, // step 4
  0b00000110, // step 5
  0b00000000, // step 6
  0b00000100, // step 7
  0b00000001, // step 8
  0b00000101, // step 9
  0b00000000, // step 10
  0b00000100, // step 11
  0b00000000, // step 12
  0b00000110, // step 13
  0b00000000, // step 14
  0b00000100, // step 15
  0b00000001, // step 16
  // Pattern 4: 8 beat Rock 4
  0b00000101, // step 1
  0b00000000, // step 2
  0b00000100, // step 3
  0b00000000, // step 4
  0b00100100, // step 5
  0b00000000, // step 6
  0b00000101, // step 7
  0b00000000, // step 8
  0b00000101, // step 9
  0b00000000, // step 10
  0b00000100, // step 11
  0b00000000, // step 12
  0b00100100, // step 13
  0b00000000, // step 14
  0b00000101, // step 15
  0b00000000, // step 16
  // Pattern 5: Disco
  0b00000101, // step 1
  0b00000000, // step 2
  0b00001000, // step 3
  0b00000000, // step 4
  0b00000111, // step 5
  0b00000000, // step 6
  0b00001000, // step 7
  0b00000000, // step 8
  0b00000101, // step 9
  0b00000000, // step 10
  0b00001000, // step 11
  0b00000000, // step 12
  0b00000111, // step 13
  0b00000000, // step 14
  0b00001000, // step 15
  0b00000000, // step 16
  // Pattern 6: Electro Pop
  0b00000101, // step 1
  0b00000000, // step 2
  0b00000100, // step 3
  0b00000100, // step 4
  0b00000111, // step 5
  0b00000000, // step 6
  0b00000100, // step 7
  0b00000100, // step 8
  0b00000101, // step 9
  0b00000000, // step 10
  0b00000100, // step 11
  0b00000100, // step 12
  0b00000111, // step 13
  0b00000000, // step 14
  0b00000100, // step 15
  0b00000100, // step 16
};