#include <bitset>
#include <cstdio>
#include <iostream>

using namespace std;

void printBits(int x) {
  int bits = sizeof(int) * 8;
  for (int k = bits - 1; k >= 0; k--) {
    if (x & (1 << k)) {
      cout << "1";
    } else {
      cout << "0";
    }
  }

  cout << "\n";
}

void printBitSet(int x) {
  for (int k = 0; k < 32; k++) {
    if (x & (1 << k)) {
      cout << k << " ";
    }
  }
}

// bitSet sets the kth bit
int bitSet(int x, int k) { return x | (1 << k); }

// bitSet resets the kth bit
int bitReset(int x, int k) { return x & ~(1 << k); }

// bitFlip flips the kth bit
int bitFlip(int x, int k) { return x ^ (1 << k); }

int main() {
  printf("Two's complement\n");
  int x = 43;
  int notX = ~x + 1;
  printf(" %d ", x);
  printBits(x);
  printf("%d ", notX);
  printBits(notX);

  printf("Shift 1 bit to the left\n");
  int y = 14;
  printf("%d ", y);
  printBits(y);
  y = y << 1;
  printf("%d ", y);
  printBits(y);

  printf("Shift 1 bit to the right\n");
  y = 49;
  printf("%d ", y);
  printBits(y);
  y = y >> 1;
  printf("%d ", y);
  printBits(y);

  printf("Check bit #2 via bit mask\n");
  int z = 4;
  printBits(z);
  printf("#2 bit is equal to ");
  if (z & (1 << 2)) {
    cout << "1";
  } else {
    cout << "0";
  }
  cout << "\n";

  printf("Bit set, reset, flip\n");
  int k = 31;
  x = 0;
  printBits(x);

  printf("Set %dst bit\n", k);
  x = bitSet(0, k);
  printBits(x);

  printf("Reset %dst bit\n", k);
  x = bitReset(0, k);
  printBits(x);

  printf("Flip %dst bit\n", k);
  x = bitFlip(0, k);
  printBits(x);

  // long long bit mask
  long long _ = 1LL << k;

  printf("Set last one bit to zero\n");
  printBits(~0 & (~0 - 1));

  printf("Set all one bit to zero, except last bit\n");
  printBits(~0 & -~0);

  printf("Invert all bits after the last one bit (to the right)\n");
  printBits(4 | (4 - 1));

  printf("Bit sets\n");
  int s1 = (1 << 1) | (1 << 3) | (1 << 4) | (1 << 8);
  int s2 = (1 << 3) | (1 << 6) | (1 << 8) | (1 << 9);

  cout << "s1:\n";
  printBitSet(s1);
  cout << "\n";

  cout << "s2:\n";
  printBitSet(s2);
  cout << "\n";

  cout << "Union:\n";
  printBitSet(s1 | s2);
  cout << "\n";

  cout << "Itersection:\n";
  printBitSet(s1 & s2);
  cout << "\n";

  cout << "Difference:\n";
  printBitSet(s1 & ~s2);
  cout << "\n";

  cout << "Complement:\n";
  printBitSet(~s1);
  cout << "\n\n";

  const int n = 4;
  printf("Generate subsets of length %d", n);
  for (int b = 0; b < (1 << n); b++) {
    printBitSet(b);
    cout << "\n";
  }

  printf("Built-in bitset\n");
  bitset<10> s;
  s[1] = s[3] = s[4] = s[7] = 1;

  // All above operations on sets also apply to std::bitset
  printf("Set count: %lu\n", s.count());
  for (int k = 0; k < 10; k++) {
    if (s[k]) {
      printf("%d ", k);
    }
  }
}
