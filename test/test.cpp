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

void testIndexableSetInsert(){
    IndexableSet<int> is{};
    ASSERT_EQUAL(0,is.size());
    is.insert(42);
    ASSERT_EQUAL(1,is.size());
    ASSERT_EQUAL(42,is[0]);
    ASSERT_THROWS(is[1],std::out_of_range);
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

void testIndexableSetCaselessCompare() {
    struct caselessCompare {
        bool operator ()(const std::string & left, const std::string & right) {
            return std::lexicographical_compare(
                    left.begin(), left.end(),
                    right.begin(), right.end(),
                    [](const char l, const char r){
                return std::tolower(l) < std::tolower(r);
            });
        }
    };

    IndexableSet<std::string,caselessCompare> cl_is {"H", "i", "I", "h"};
    ASSERT_EQUAL(2, cl_is.size());
    ASSERT_EQUAL("H", cl_is[0]);
    ASSERT_EQUAL("i", cl_is[1]);
    IndexableSet<std::string> is {"H", "i", "I", "h"};
    ASSERT_EQUAL(4, is.size());
    ASSERT_EQUAL("H", is[0]);
    ASSERT_EQUAL("I", is[1]);
    ASSERT_EQUAL("h", is[2]);
    ASSERT_EQUAL("i", is[3]);
}

void testRangeConstructor(){
    const std::string str{"glass"};
    IndexableSet<char> is(str.begin(), str.end());
    std::string t(is.begin(),is.end());
    ASSERT_EQUAL(4, is.size());
    ASSERT_EQUAL('a', is.at(0));
    ASSERT_EQUAL('g', is.at(1));
    ASSERT_EQUAL('l', is.at(2));
    ASSERT_EQUAL('s', is.at(3));
}

void testCopyConstructor() {
    const IndexableSet<std::string> constSet { "g", "l", "s", "s", "s" };
    IndexableSet<std::string> set { constSet };
    ASSERT_EQUAL(constSet.size(), set.size());
    ASSERT_EQUAL(constSet.at(1), set.at(1));
}

void testMoveConstructor() {
    IndexableSet<std::string> setToMove { "w", "h", "i", "t", "e" };
    IndexableSet<std::string> set { std::move(setToMove) };
    ASSERT(setToMove.empty());
    ASSERT_EQUAL(0, setToMove.size());
    ASSERT_EQUAL(5, set.size());
}

void runAllTests(int argc, char const *argv[]){
    cute::suite s;
    s.push_back(CUTE(testIndexableSetAccess));
    s.push_back(CUTE(testEmptyIndexableSet));
    s.push_back(CUTE(testIndexableSetInsert));
    s.push_back(CUTE(testIndexableSetFrontBack));
    s.push_back(CUTE(testIndexableSetNegativeIndexAccessFromBack));
    s.push_back(CUTE(testIndexableSetOverflowCapture));
    s.push_back(CUTE(testIndexableSetCaselessCompare));
    s.push_back(CUTE(testRangeConstructor));
    s.push_back(CUTE(testCopyConstructor));
    s.push_back(CUTE(testMoveConstructor));

    cute::xml_file_opener xmlfile(argc,argv);
    cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
    cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}