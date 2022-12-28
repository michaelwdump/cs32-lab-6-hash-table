#include <iostream>
#include <string>
#include <vector>
#include "WordCount.h"
#include "tddFuncs.h"
using namespace std;

int main() {
    WordCount wc3;
    wc3.incrWordCount("aa");
    wc3.incrWordCount("bb");
    wc3.incrWordCount("aA--");
    wc3.incrWordCount("ba");
    wc3.incrWordCount("cccc");
    wc3.incrWordCount("c'''ccc");
    wc3.incrWordCount("dd");

    wc3.dumpWordsSortedByWord(cout);
    wc3.dumpWordsSortedByOccurence(cout);




    return 0;
}