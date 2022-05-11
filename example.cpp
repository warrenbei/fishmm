//Solution to https://dmoj.ca/problem/dp1p1
//(if the header is put in and the filestreams are commented out)
#include "./><>--2.0.hpp"
int main()
{
    const char *p[] = {
"000> i:55+=&vv",
"   ^+*+55$-# <",
"v:i<0-1v?:<~< ",
"5      >~n ;  ",
">5+ =&v:0= &vv",
"v+* +5 5$- # <",
">  ^v~<     < ",
"v:+{< >$  ^ < ",
">{:})&^~$:@$^ "
};
    std::vector<std::string> program(p,p+sizeof(p)/sizeof(p[0]));
    fishmm2(program,stdIN,stdOUT,stdLOG,100,true,true,true);
}
