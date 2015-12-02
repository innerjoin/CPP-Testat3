#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "indexableSet.h"

void test() {
    //IndexableSet ix;
    ASSERT_EQUAL(1, 1);
}

void runAllTests(int argc, char const *argv[]){
    cute::suite s;
    // Word.h
    s.push_back(CUTE(test));

    cute::xml_file_opener xmlfile(argc,argv);
    cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
    cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



