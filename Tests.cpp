#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"
#include "ExtraTasks.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

static void printResult(const std::string& testName, bool passed) {
    std::cout << (passed ? "[PASSED] " : "[FAILED] ") << testName << std::endl;
}

template<typename T>
static bool sequencesEqual(const Sequence<T>* seq1, const Sequence<T>* seq2) {
    if (seq1->GetLength() != seq2->GetLength()) return false;
    for (int i = 0; i < seq1->GetLength(); i++) {
        if (seq1->Get(i) != seq2->Get(i)) return false;
    }
    return true;
}

//DynamicArray
static void testDynamicArray() {
    std::cout << "\n--- Testing DynamicArray ---\n";
    
    // Test 1: Create and basic access
    int arr1[] = {1, 2, 3, 4, 5};
    DynamicArray<int> da1(arr1, 5);
    bool test1 = (da1.GetSize() == 5) && (da1.Get(0) == 1) && (da1.Get(4) == 5);
    printResult("Create and access", test1);
    assert(test1);
    
    // Test 2: Set element
    da1.Set(2, 99);
    bool test2 = (da1.Get(2) == 99);
    printResult("Set element", test2);
    assert(test2);
    
    // Test 3: Resize larger
    da1.Resize(7);
    bool test3 = (da1.GetSize() == 7);
    printResult("Resize larger", test3);
    assert(test3);
    
    // Test 4: Resize smaller
    da1.Resize(3);
    bool test4 = (da1.GetSize() == 3) && (da1.Get(0) == 1) && (da1.Get(2) == 99);
    printResult("Resize smaller", test4);
    assert(test4);
    
    // Test 5: Copy constructor
    DynamicArray<int> da2 = da1;
    bool test5 = (da2.GetSize() == 3) && (da2.Get(0) == 1) && (da2.Get(2) == 99);
    printResult("Copy constructor", test5);
    assert(test5);
    
    // Test 6: GetSubArray
    DynamicArray<int>* subArray = da1.GetSubArray(0, 2);
    bool test6 = (subArray->GetSize() == 3);
    printResult("GetSubArray", test6);
    assert(test6);
    delete subArray;
    
    // Test 7: Exceptions
    try {
        da1.Get(10);
        printResult("Out of range exception", false);
    } catch (const IndexOutOfRangeException&) {
        printResult("Out of range exception", true);
    }
}

//LinkedList
static void testLinkedList() {
    std::cout << "\n--- Testing LinkedList ---\n";
    
    // Test 1: Create and basic access
    int arr1[] = {10, 20, 30, 40, 50};
    LinkedList<int> ll1(arr1, 5);
    bool test1 = (ll1.GetLength() == 5) && (ll1.GetFirst() == 10) && (ll1.GetLast() == 50);
    printResult("Create and access", test1);
    assert(test1);
    
    // Test 2: Get by index
    bool test2 = (ll1.Get(2) == 30) && (ll1.Get(0) == 10) && (ll1.Get(4) == 50);
    printResult("Get by index", test2);
    assert(test2);
    
    // Test 3: Append and Prepend
    ll1.Append(60);
    ll1.Prepend(0);
    bool test3 = (ll1.GetLength() == 7) && 
                (ll1.GetFirst() == 0) && 
                (ll1.GetLast() == 60);
    printResult("Append and Prepend", test3);
    assert(test3);

    // Test 4: InsertAt
    ll1.InsertAt(99, 3);
    bool test4 = (ll1.GetLength() == 8) && (ll1.Get(3) == 99);
    printResult("InsertAt", test4);
    assert(test4);
    
    // Test 5: GetSublist
    LinkedList<int>* subList = ll1.GetSubList(2, 5);
    bool test5 = (subList->GetLength() == 4);
    printResult("GetSublist", test5);
    assert(test5);
    delete subList;
    
    // Test 6: Concat
    int arr2[] = {100, 200};
    LinkedList<int> ll2(arr2, 2);
    LinkedList<int> concat = ll1.Concat(ll2);
    bool test6 = (concat.GetLength() == ll1.GetLength() + 2) && (concat.GetLast() == 200);
    printResult("Concat", test6);
    assert(test6);
    
    // Test 7: Exceptions
    try {
        ll1.Get(100);
        printResult("Out of range exception", false);
    } catch (const IndexOutOfRangeException&) {
        printResult("Out of range exception", true);
    }
}

//ArraySequence
static void testArraySequence() {
    std::cout << "\n--- Testing ArraySequence (mutable) ---\n";
    
    int data[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq1(data, 5);
    
    // Test 1: Basic access
    bool test1 = (seq1.GetLength() == 5) && 
                (seq1.GetFirst() == 1) && 
                (seq1.GetLast() == 5);
    printResult("Basic access", test1);
    assert(test1);
    
    // Test 2: Append and Prepend (chained)
    seq1.Append(6)->Prepend(0);
    bool test2 = (seq1.GetLength() == 7) && 
                (seq1.Get(0) == 0) && 
                (seq1.Get(6) == 6);
    printResult("Append and Prepend (chained)", test2);
    assert(test2);
    
    // Test 3: InsertAt
    seq1.InsertAt(99, 3);
    bool test3 = (seq1.GetLength() == 8) && (seq1.Get(3) == 99);
    printResult("InsertAt", test3);
    assert(test3);
    
    // Test 4: Set
    seq1.Set(2, 100);
    bool test4 = (seq1.Get(2) == 100);
    printResult("Set", test4);
    assert(test4);
    
    // Test 5: GetSubsequence
    Sequence<int>* subSeq = seq1.GetSubsequence(2, 5);
    bool test5 = (subSeq->GetLength() == 4);
    printResult("GetSubsequence", test5);
    assert(test5);
    delete subSeq;
    
    // Test 6: Concat
    int data2[] = {100, 200};
    ArraySequence<int> seq2(data2, 2);
    Sequence<int>* concatSeq = seq1.Concat(&seq2);
    bool test6 = (concatSeq->GetLength() == seq1.GetLength() + 2);
    printResult("Concat", test6);
    assert(test6);
    delete concatSeq;
    
    // Test 7: Clone
    Sequence<int>* cloned = seq1.Clone();
    bool test7 = (cloned->GetLength() == seq1.GetLength()) && 
                (cloned->Get(0) == seq1.Get(0));
    printResult("Clone", test7);
    assert(test7);
    delete cloned;
    
    // Test 8: Try methods
    Option<int> first = seq1.TryGetFirst();
    Option<int> notFound = seq1.TryFind([](int x) { return x > 1000; });
    bool test8 = first.IsSome() && (first.GetValue() == 0) && notFound.IsNone();
    printResult("Try methods", test8);
    assert(test8);
}

//ListSequence
static void testListSequence() {
    std::cout << "\n--- Testing ListSequence (mutable) ---\n";
    
    int data[] = {10, 20, 30, 40, 50};
    ListSequence<int> seq1(data, 5);
    
    // Test 1: Basic access
    bool test1 = (seq1.GetLength() == 5) && (seq1.GetFirst() == 10);
    printResult("Basic access", test1);
    assert(test1);
    
    // Test 2: Append and Prepend (chained)
    seq1.Append(60)->Prepend(0);
    bool test2 = (seq1.GetLength() == 7) && (seq1.GetFirst() == 0) && (seq1.GetLast() == 60);
    printResult("Append and Prepend (chained)", test2);
    assert(test2);
    
    // Test 3: InsertAt
    seq1.InsertAt(99, 3);
    bool test3 = (seq1.GetLength() == 8) && (seq1.Get(3) == 99);
    printResult("InsertAt", test3);
    assert(test3);
    
    // Test 4: Set
    seq1.Set(2, 100);
    bool test4 = (seq1.Get(2) == 100);
    printResult("Set", test4);
    assert(test4);
    
    // Test 5: GetSubsequence
    Sequence<int>* subSeq = seq1.GetSubsequence(2, 5);
    bool test5 = (subSeq->GetLength() == 4);
    printResult("GetSubsequence", test5);
    assert(test5);
    delete subSeq;
    
    // Test 6: Where
    Sequence<int>* filtered = seq1.Where([](int x) { return x > 30; });
    bool test6 = (filtered->GetLength() > 0);
    printResult("Where", test6);
    assert(test6);
    delete filtered;
}

//Bit sequence
static void testBitSequence() {
    std::cout << "\n--- Testing BitSequence ---\n";
    
    // Test 1: Create from bool array
    bool bits1[] = {1, 0, 1, 1, 0, 1};
    BitSequence bs1(bits1, 6);
    bool test1 = (bs1.GetLength() == 6) && 
                 (bs1.Get(0) == Bit(true)) && 
                 (bs1.Get(1) == Bit(false));
    printResult("Create from bool array", test1);
    assert(test1);
    
    // Test 2: Create from Bit array
    Bit bits2[] = {Bit(true), Bit(false), Bit(true)};
    BitSequence bs2(bits2, 3);
    bool test2 = (bs2.GetLength() == 3) && (bs2.Get(0) == Bit(true));
    printResult("Create from Bit array", test2);
    assert(test2);
    
    // Test 3: Append and Prepend
    bs1.Append(Bit(true));
    bs1.Prepend(Bit(false));
    bool test3 = (bs1.GetLength() == 8) && 
                 (bs1.GetFirst() == Bit(false)) && 
                 (bs1.GetLast() == Bit(true));
    printResult("Append and Prepend", test3);
    assert(test3);
    
    // Test 4: InsertAt
    bs1.InsertAt(Bit(true), 3);
    bool test4 = (bs1.GetLength() == 9) && (bs1.Get(3) == Bit(true));
    printResult("InsertAt", test4);
    assert(test4);
    
    // Test 5: Set
    bs1.Set(2, Bit(false));
    bool test5 = (bs1.Get(2) == Bit(false));
    printResult("Set", test5);
    assert(test5);
    
    // Test 6: Bitwise operations
    bool bitsA[] = {1, 1, 0, 0};
    bool bitsB[] = {1, 0, 1, 0};
    BitSequence bsA(bitsA, 4);
    BitSequence bsB(bitsB, 4);
    
    BitSequence andRes = bsA.And(bsB);
    BitSequence orRes = bsA.Or(bsB);
    BitSequence xorRes = bsA.Xor(bsB);
    BitSequence notRes = bsA.Not();
    
    bool test6 = (andRes.Get(0) == Bit(true)) && (andRes.Get(1) == Bit(false)) &&
                 (orRes.Get(0) == Bit(true)) && (orRes.Get(3) == Bit(false)) &&
                 (xorRes.Get(0) == Bit(false)) && (xorRes.Get(1) == Bit(true)) &&
                 (notRes.Get(0) == Bit(false)) && (notRes.Get(2) == Bit(true));
    printResult("Bitwise operations", test6);
    assert(test6);
    
    // Test 7: Bitwise operators &, |, ^, ~
    BitSequence opAnd = bsA & bsB;
    BitSequence opOr = bsA | bsB;
    BitSequence opXor = bsA ^ bsB;
    BitSequence opNot = ~bsA;
    
    bool test7 = true;
    for (int i = 0; i < 4; i++) {
        if (opAnd.Get(i) != andRes.Get(i) ||
            opOr.Get(i) != orRes.Get(i) ||
            opXor.Get(i) != xorRes.Get(i) ||
            opNot.Get(i) != notRes.Get(i)) {
            test7 = false;
            break;
        }
    }
    printResult("Bitwise operators", test7);
    assert(test7);
    
    // Test 8: Try methods
    Option<Bit> first = bs1.TryGetFirst();
    Option<Bit> notFound = bs1.TryFind([](const Bit& b) { return static_cast<bool>(b) == false; });
    bool test8 = first.IsSome() && (static_cast<bool>(first.GetValue()) == false) && notFound.IsSome();
    printResult("Try methods", test8);
    assert(test8);
    
    // Test 9: Slice
    bool bits3[] = {1, 0, 1, 1, 0, 1, 0, 0};
    BitSequence bs3(bits3, 8);
    Sequence<Bit>* sliced = bs3.Slice(2, 3);
    bool test9 = (sliced->GetLength() == 5);
    printResult("Slice", test9);
    assert(test9);
    delete sliced;
}

//Mutable/Immutable
static void testMutableImmutable() {
    std::cout << "\n--- Testing Mutable vs Immutable ---\n";
    
    int data[] = {1, 2, 3};
    
    // Mutable
    ArraySequence<int> mutableSeq(data, 3);
    mutableSeq.Append(4)->Prepend(0);
    mutableSeq.Set(2, 99);
    
    bool test1 = (mutableSeq.GetLength() == 5) && 
                (mutableSeq.GetFirst() == 0) && 
                (mutableSeq.Get(3) == 3) && 
                (mutableSeq.Get(2) == 99);
    printResult("Mutable sequence (in-place changes)", test1);
    assert(test1);
    
    // Immutable
    ImmutableArraySequence<int> immutableSeq(data, 3);
    Sequence<int>* newSeq1 = immutableSeq.Append(4);
    Sequence<int>* newSeq2 = immutableSeq.Prepend(0);
    Sequence<int>* newSeq3 = immutableSeq.Set(1, 99);
    
    bool test2 = (immutableSeq.GetLength() == 3) &&
                (newSeq1->GetLength() == 4) && 
                (newSeq2->GetLength() == 4) &&
                (newSeq3->GetLength() == 3) &&
                (newSeq3->Get(1) == 99);
    printResult("Immutable (original unchanged)", test2);
    assert(test2);
    
    delete newSeq1;
    delete newSeq2;
    delete newSeq3;
    
    // Test chaining for immutable
    Sequence<int>* chained = immutableSeq.Append(4)->Prepend(0);
    bool test3 = (chained->GetLength() == 5) && 
                (chained->GetFirst() == 0) && 
                (chained->GetLast() == 4);
    printResult("Immutable (chained operations)", test3);
    assert(test3);
    delete chained;
    
    // Try to modify immutable via []
    try {
        immutableSeq[1] = 99;
        printResult("Immutable operator[] disabled", false);
    } catch (const UnsupportedOperationException&) {
        printResult("Immutable operator[] disabled", true);
    }
}

//map-reduce
static void testMapReduce() {
    std::cout << "\n--- Testing Map-Reduce ---\n";
    
    int data[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(data, 5);
    
    // Map
    Sequence<int>* mapped = seq.Map<int>([](int x) { return x * 2; });
    bool test1 = (mapped->GetLength() == 5) && 
                (mapped->Get(0) == 2) && 
                (mapped->Get(4) == 10);
    printResult("Map", test1);
    assert(test1);
    delete mapped;
    
    // Where
    Sequence<int>* filtered = seq.Where([](int x) { return x % 2 == 0; });
    bool test2 = (filtered->GetLength() == 2) && 
                (filtered->Get(0) == 2) && 
                (filtered->Get(1) == 4);
    printResult("Where", test2);
    assert(test2);
    delete filtered;
    
    // Reduce
    int sum = seq.Reduce<int>(0, [](int acc, int x) { return acc + x; });
    bool test3 = (sum == 15);
    printResult("Reduce (sum)", test3);
    assert(test3);
}

//итераторы
static void testIterators() {
    std::cout << "\n--- Testing Iterators ---\n";
    
    int data[] = {10, 20, 30, 40, 50};
    ArraySequence<int> seq(data, 5);
    
    // Test ArrayEnumerator
    IEnumerator<int>* enum1 = seq.GetEnumerator();
    bool test1 = true;
    int expected[] = {10, 20, 30, 40, 50};
    int i = 0;
    while (enum1->MoveNext()) {
        if (enum1->GetCurrent() != expected[i]) {
            test1 = false;
            break;
        }
        i++;
    }
    test1 = test1 && (i == 5);
    printResult("ArrayEnumerator iteration", test1);
    assert(test1);
    delete enum1;
    
    // Test Reset
    IEnumerator<int>* enum2 = seq.GetEnumerator();
    enum2->MoveNext();
    enum2->MoveNext();
    int first = enum2->GetCurrent();
    enum2->Reset();
    enum2->MoveNext();
    int afterReset = enum2->GetCurrent();
    bool test2 = (first == 20) && (afterReset == 10);
    printResult("Enumerator Reset", test2);
    assert(test2);
    delete enum2;
}

//доп задания
static void testExtraTasks() {
    std::cout << "\n--- Testing Extra Tasks (P-1, P-6, P-8) ---\n";
    
    int data[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    ArraySequence<int> seq(data, 9);
    
    //п1
    auto mmResult = Task_MinMaxAvg<int>::compute(seq);
    bool test1 = (mmResult.min == 1) && (mmResult.max == 9) && 
                 (std::abs(mmResult.avg - 5.0) < 0.1) && 
                 (mmResult.count == 9);
    printResult("Task-1: Min, Max, Avg", test1);
    assert(test1);
    
    //п6
    ArraySequence<double>* maResult = Task_MovingAverage<int>::computeTripleAverage(seq);
    bool test2 = (maResult->GetLength() == 9);
    if (test2) {
        test2 = std::abs(maResult->Get(0) - 3.5) < 0.1;
    }
    printResult("Task-6: Moving Average", test2);
    assert(test2);
    delete maResult;
    
    //п8
    ArraySequence<int>* refResult = Task_ReflectionSum<int>::computeFullReflection(seq);
    bool test3 = (refResult->GetLength() == 9);
    if (test3) {
        test3 = (refResult->Get(0) == 11) && (refResult->Get(4) == 18);
    }
    printResult("Task-8: Reflection Sum", test3);
    assert(test3);
    delete refResult;
}

//граничные кейсы
static void testEdgeCases() {
    std::cout << "\n--- Testing Edge Cases ---\n";
    
    // Empty sequence
    ArraySequence<int> emptySeq;
    bool test1 = (emptySeq.GetLength() == 0);
    printResult("Empty sequence creation", test1);
    assert(test1);
    
    // Try methods on empty
    Option<int> first = emptySeq.TryGetFirst();
    bool test2 = first.IsNone();
    printResult("TryGetFirst on empty", test2);
    assert(test2);
    
    // Append to empty
    emptySeq.Append(42);
    bool test3 = (emptySeq.GetLength() == 1) && (emptySeq.GetFirst() == 42);
    printResult("Append to empty", test3);
    assert(test3);
    
    // Slice with negative index
    int data[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(data, 5);
    Sequence<int>* sliced = seq.Slice(-2, 2);
    bool test4 = (sliced->GetLength() == 3) && 
                (sliced->Get(0) == 1) && 
                (sliced->Get(1) == 2) && 
                (sliced->Get(2) == 3);
    printResult("Slice with negative index", test4);
    assert(test4);
    delete sliced;
    
    // Slice with replacement
    int replData[] = {99, 100};
    ArraySequence<int> replacement(replData, 2);
    Sequence<int>* slicedWithRepl = seq.Slice(2, 2, &replacement);
    bool test5 = (slicedWithRepl->GetLength() == 5) && 
                (slicedWithRepl->Get(2) == 99);
    printResult("Slice with replacement", test5);
    assert(test5);
    delete slicedWithRepl;

    // Slice out of range exception
    try {
        seq.Slice(10, 2);
        printResult("Slice out of range exception", false);
    } catch (const IndexOutOfRangeException&) {
        printResult("Slice out of range exception", true);
    }
}

//запуск всех
int main() {
    std::cout << "========================================\n";
    std::cout << "      RUNNING ALL TESTS\n";
    std::cout << "========================================\n";
    
    testDynamicArray();
    testLinkedList();
    testArraySequence();
    testListSequence();
    testBitSequence();
    testMutableImmutable();
    testMapReduce();
    testIterators();
    testExtraTasks();
    testEdgeCases();
    
    std::cout << "\n========================================\n";
    std::cout << "      ALL TESTS COMPLETED\n";
    std::cout << "========================================\n";
    
    return 0;
}