#include <iostream>
#include <string>

int GetValue() {
  return 0;
}

// if (init; condition)和switch (init; condition)
int main() {
  int a = GetValue();
  if (a < 1) {
      std::cout << a << std::endl;
  }

  if (int a = GetValue(), b = 1.0f; a < 1) {
      std::cout << "cpp17: " << a << std::endl;
  } else if (int c = 1; b == 1) {
      std::cout << "cpp17: " << b << std::endl;
  } else {
      std::cout << "cpp17: " << b << std::endl;
  }

  std::string str = "HellO WOrld";
  if (auto [pos, size] = std::pair(str.find("He"), str.size()); pos != std::string::npos) {
      std::cout << pos << " Hello, size is " << size << std::endl;
  }
  return 0;
}