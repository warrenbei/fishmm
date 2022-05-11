# ><>--
><>-- is based on https://esolangs.org/wiki/Fish, but with fewer commands, while still Turing complete.
## Usage
Type 
#include "./><>--2.0.hpp"
(or wherever it is) and then use the functions, it is self-explanatory. (See example.cpp for an example usage.)
## Turing completeness
It is Turing complete even without the commands /\|_x!*,%)=@n{}, one of ?&, and all the constants (except 1). The main idea is that rl[] are enough to take an arbitrary element out of the memory if its location is written at the top of the stack: first compute how far it is from the end using l (requires fiddling with the exact constants), then [r:rl1-[r]r] is the trick.
