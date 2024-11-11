#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <cstddef>

namespace encryption {
void StartEncryption(int* keysArray, int keysCount);
void StartDecoding(int* keysArray, int keysCount);

void StartProgram();
}  // namespace encryption

#endif  // ENCRYPTION_HPP
