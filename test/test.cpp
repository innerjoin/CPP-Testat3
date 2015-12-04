#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "indexableSet.h"

void testIndexableSetAccess() {
    IndexableSet<char> is{'b', 'e', 'e', 'r'};
    ASSERT_EQUAL(3, is.size());
    ASSERT_EQUAL('b', is[0]);
    ASSERT_EQUAL('e', is[1]);
    ASSERT_EQUAL('r', is[2]);
}

void testEmptyIndexableSet() {
    IndexableSet<int> is{};
    ASSERT_EQUAL(0, is.size());
    ASSERT(is.empty());
}

void testIndexableSetFrontBack() {
    IndexableSet<int> is{88, -10, 23, 6};
    ASSERT_EQUAL(4, is.size());
    ASSERT_EQUAL(-10, is.front());
    ASSERT_EQUAL(88, is.back());
}

void testIndexableSetNegativeIndexAccessFromBack() {
    IndexableSet<char> is{'b', 'e', 'e', 'r'};
    ASSERT_EQUAL('r', is.at(-1));
    ASSERT_EQUAL('e', is.at(-2));
    ASSERT_EQUAL('b', is.at(-3));
}

void testIndexableSetOverflowCapture() {
    IndexableSet<int> is{1, 2, 3, 4};
    ASSERT_THROWS(is.at(4), std::out_of_range);
    ASSERT_THROWS(is.at(-5), std::out_of_range);

    IndexableSet<char> is2{};
    ASSERT_THROWS(is2.at(0), std::out_of_range);
    ASSERT_THROWS(is2.at(-1), std::out_of_range);
}

void runAllTests(int argc, char const *argv[]){
    cute::suite s;
    s.push_back(CUTE(testIndexableSetAccess));
    s.push_back(CUTE(testEmptyIndexableSet));
    s.push_back(CUTE(testIndexableSetFrontBack));
    s.push_back(CUTE(testIndexableSetNegativeIndexAccessFromBack));
    s.push_back(CUTE(testIndexableSetOverflowCapture));

    cute::xml_file_opener xmlfile(argc,argv);
    cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
    cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}