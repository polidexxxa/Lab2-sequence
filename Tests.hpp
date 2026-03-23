#ifndef _TESTS_HPP_
#define _TESTS_HPP_

#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"
#include "ExtraTasks.hpp"
#include <iostream>
#include <cassert>

class Tests {
private:
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

public:

    // ============= ТЕСТЫ DYNAMIC ARRAY =============

    static void testDynamicArray() {
        std::cout << "\n--- Testing DynamicArray ---\n";
        
        // Тест 1: Создание и базовый доступ
        int arr1[] = {1, 2, 3, 4, 5};
        DynamicArray<int> da1(arr1, 5);
        bool test1 = (da1.GetSize() == 5) && (da1.Get(0) == 1) && (da1.Get(4) == 5);
        printResult("Create and access", test1);
        assert(test1);
        
        // Тест 2: Изменение элементов
        da1.Set(2, 99);
        bool test2 = (da1.Get(2) == 99);
        printResult("Set element", test2);
        assert(test2);
        
        // Тест 3: Resize с увеличением
        da1.Resize(7);
        bool test3 = (da1.GetSize() == 7) && (da1.Get(5) == 0);
        printResult("Resize larger", test3);
        assert(test3);
        
        // Тест 4: Resize с уменьшением
        da1.Resize(3);
        bool test4 = (da1.GetSize() == 3) && (da1.Get(0) == 1) && (da1.Get(2) == 99);
        printResult("Resize smaller", test4);
        assert(test4);
        
        // Тест 5: Копирование
        DynamicArray<int> da2 = da1;
        bool test5 = (da2.GetSize() == 3) && (da2.Get(0) == 1) && (da2.Get(2) == 99);
        printResult("Copy constructor", test5);
        assert(test5);
        
        // Тест 6: GetSubArray
        DynamicArray<int>* subArray = da1.GetSubArray(0, 2);
        bool test6 = (subArray->GetSize() == 3) && 
                    (subArray->Get(0) == da1.Get(0)) && 
                    (subArray->Get(1) == da1.Get(1)) && 
                    (subArray->Get(2) == da1.Get(2));
        printResult("GetSubArray", test6);
        assert(test6);
        delete subArray;
        
        // Тест 7: Исключения
        try {
            da1.Get(10);
            printResult("Out of range exception", false);
        } catch (const IndexOutOfRangeException&) {
            printResult("Out of range exception", true);
        }
    }

    // ============= ТЕСТЫ LINKED LIST =============
    
    static void testLinkedList() {
        std::cout << "\n--- Testing LinkedList ---\n";
        
        // Тест 1: Создание и базовый доступ
        int arr1[] = {10, 20, 30, 40, 50};
        LinkedList<int> ll1(arr1, 5);
        bool test1 = (ll1.GetLength() == 5) && (ll1.GetFirst() == 10) && (ll1.GetLast() == 50);
        printResult("Create and access", test1);
        assert(test1);
        
        // Тест 2: Доступ по индексу
        bool test2 = (ll1.Get(2) == 30) && (ll1.Get(0) == 10) && (ll1.Get(4) == 50);
        printResult("Get by index", test2);
        assert(test2);
        
        // Тест 3: Append и Prepend
        ll1.Append(60);
        ll1.Prepend(0);
        bool test3 = (ll1.GetLength() == 7) && 
                    (ll1.GetFirst() == 0) && 
                    (ll1.GetLast() == 60) &&
                    (ll1.Get(1) == 10);
        printResult("Append and Prepend", test3);
        assert(test3);

        // Тест 4: InsertAt
        ll1.InsertAt(99, 3);
        bool test4 = (ll1.GetLength() == 8) && (ll1.Get(3) == 99);
        printResult("InsertAt", test4);
        assert(test4);
        
        // Тест 5: GetSublist
        LinkedList<int>* subList = ll1.GetSubList(2, 5);
        bool test5 = (subList->GetLength() == 4) && 
                    (subList->Get(0) == ll1.Get(2)) && 
                    (subList->Get(3) == ll1.Get(5));
        printResult("GetSublist", test5);
        assert(test5);
        delete subList;
        
        // Тест 6: Concat
        int arr2[] = {100, 200};
        LinkedList<int> ll2(arr2, 2);
        LinkedList<int> concat = ll1.Concat(ll2);
        bool test6 = (concat.GetLength() == ll1.GetLength() + 2) && 
                    (concat.GetLast() == 200);
        printResult("Concat", test6);
        assert(test6);
        
        // Тест 7: Исключения
        try {
            ll1.Get(100);
            printResult("Out of range exception", false);
        } catch (const IndexOutOfRangeException&) {
            printResult("Out of range exception", true);
        }
    }

    // ============= ТЕСТЫ ARRAY SEQUENCE =============
    
    static void testArraySequence() {
        std::cout << "\n--- Testing ArraySequence ---\n";
        
        int data[] = {1, 2, 3, 4, 5};
        MutableArraySequence<int> seq1(data, 5);
        
        // Тест 1: Базовый доступ
        bool test1 = (seq1.GetLength() == 5) && 
                    (seq1.GetFirst() == 1) && 
                    (seq1.GetLast() == 5);
        printResult("Basic access", test1);
        assert(test1);
        
        // Тест 2: Append и Prepend (теперь возвращают Sequence*)
        seq1.Append(6)->Prepend(0);
        bool test2 = (seq1.GetLength() == 7) && 
                    (seq1.Get(0) == 0) && 
                    (seq1.Get(6) == 6);
        printResult("Append and Prepend (chained)", test2);
        assert(test2);
        
        // Тест 3: InsertAt
        seq1.InsertAt(99, 3);
        bool test3 = (seq1.GetLength() == 8) && (seq1.Get(3) == 99);
        printResult("InsertAt", test3);
        assert(test3);
        
        // Тест 4: GetSubsequence
        Sequence<int>* subSeq = seq1.GetSubsequence(2, 5);
        bool test4 = (subSeq->GetLength() == 4) && 
                    (subSeq->Get(0) == seq1.Get(2)) && 
                    (subSeq->Get(3) == seq1.Get(5));
        printResult("GetSubsequence", test4);
        assert(test4);
        delete subSeq;
        
        // Тест 5: Concat
        int data2[] = {100, 200};
        MutableArraySequence<int> seq2(data2, 2);
        Sequence<int>* concatSeq = seq1.Concat(&seq2);
        bool test5 = (concatSeq->GetLength() == seq1.GetLength() + 2) && 
                    (concatSeq->Get(seq1.GetLength()) == 100);
        printResult("Concat", test5);
        assert(test5);
        delete concatSeq;
        
        // Тест 6: Clone
        Sequence<int>* cloned = seq1.Clone();
        bool test6 = (cloned->GetLength() == seq1.GetLength()) && 
                    (cloned->Get(0) == seq1.Get(0));
        printResult("Clone", test6);
        assert(test6);
        delete cloned;
        
        // Тест 7: Try-методы
        Option<int> first = seq1.TryGetFirst();
        Option<int> notFound = seq1.TryFind([](int x) { return x > 1000; });
        bool test7 = first.IsSome() && (first.GetValue() == 0) && notFound.IsNone();
        assert(test7);
        printResult("Try methods", test7);
    }

    // ============= ТЕСТЫ LIST SEQUENCE =============
    
    static void testListSequence() {
        std::cout << "\n--- Testing ListSequence ---\n";
        
        int data[] = {10, 20, 30, 40, 50};
        MutableListSequence<int> seq1(data, 5);
        
        bool test1 = (seq1.GetLength() == 5) && (seq1.GetFirst() == 10);
        printResult("Basic access", test1);
        assert(test1);
        
        // Тест цепочек
        seq1.Append(60)->Prepend(0);
        bool test2 = (seq1.GetLength() == 7) && (seq1.GetFirst() == 0) && (seq1.GetLast() == 60);
        printResult("Append and Prepend (chained)", test2);
        assert(test2);
        
        seq1.InsertAt(99, 3);
        bool test3 = (seq1.GetLength() == 8) && (seq1.Get(3) == 99);
        printResult("InsertAt", test3);
        assert(test3);
        
        Sequence<int>* subSeq = seq1.GetSubsequence(2, 5);
        bool test4 = (subSeq->GetLength() == 4);
        printResult("GetSubsequence", test4);
        assert(test4);
        delete subSeq;
        
        // Where
        Sequence<int>* filtered = seq1.Where([](int x) { return x > 30; });
        bool test5 = (filtered->GetLength() > 0);
        printResult("Where", test5);
        assert(test5);
        delete filtered;
    }

    // ============= ТЕСТЫ BIT SEQUENCE =============
    
    static void testBitSequence() {
        std::cout << "\n--- Testing BitSequence ---\n";
        
        // Тест 1: Создание из булевого массива
        bool bits1[] = {1, 0, 1, 1, 0, 1};
        BitSequence bs1(bits1, 6);
        bool test1 = (bs1.GetLength() == 6) && 
                     (bs1.Get(0) == Bit(true)) && 
                     (bs1.Get(1) == Bit(false));
        printResult("Create from bool array", test1);
        assert(test1);
        
        // Тест 2: Создание из строки (через Bit массив)
        Bit bits2[] = {Bit(true), Bit(false), Bit(true)};
        BitSequence bs2(bits2, 3);
        bool test2 = (bs2.GetLength() == 3) && (bs2.Get(0) == Bit(true));
        printResult("Create from Bit array", test2);
        assert(test2);
        
        // Тест 3: Append и Prepend
        bs1.Append(Bit(true));
        bs1.Prepend(Bit(false));
        bool test3 = (bs1.GetLength() == 8) && 
                     (bs1.GetFirst() == Bit(false)) && 
                     (bs1.GetLast() == Bit(true));
        printResult("Append and Prepend", test3);
        assert(test3);
        
        // Тест 4: InsertAt
        bs1.InsertAt(Bit(true), 3);
        bool test4 = (bs1.GetLength() == 9) && (bs1.Get(3) == Bit(true));
        printResult("InsertAt", test4);
        assert(test4);
        
        // Тест 5: Побитовые операции
        bool bitsA[] = {1, 1, 0, 0};
        bool bitsB[] = {1, 0, 1, 0};
        BitSequence bsA(bitsA, 4);
        BitSequence bsB(bitsB, 4);
        
        BitSequence andRes = bsA.And(bsB);
        BitSequence orRes = bsA.Or(bsB);
        BitSequence xorRes = bsA.Xor(bsB);
        BitSequence notRes = bsA.Not();
        
        bool test5 = (andRes.Get(0) == Bit(true)) && (andRes.Get(1) == Bit(false)) &&
                     (orRes.Get(0) == Bit(true)) && (orRes.Get(3) == Bit(false)) &&
                     (xorRes.Get(0) == Bit(false)) && (xorRes.Get(1) == Bit(true)) &&
                     (notRes.Get(0) == Bit(false)) && (notRes.Get(2) == Bit(true));
        printResult("Bitwise operations", test5);
        assert(test5);
        
        // Тест 6: Операторы &, |, ^, ~
        BitSequence opAnd = bsA & bsB;
        BitSequence opOr = bsA | bsB;
        BitSequence opXor = bsA ^ bsB;
        BitSequence opNot = ~bsA;
        
        bool test6 = true;
        for (int i = 0; i < 4; i++) {
            if (opAnd.Get(i) != andRes.Get(i) ||
                opOr.Get(i) != orRes.Get(i) ||
                opXor.Get(i) != xorRes.Get(i) ||
                opNot.Get(i) != notRes.Get(i)) {
                test6 = false;
                break;
            }
        }
        printResult("Bitwise operators", test6);
        assert(test6);
        
        // Тест 7: Попытка модификации через operator[] (должна кидать исключение)
        try {
            bs1[2] = Bit(false);  // Должно кинуть исключение
            printResult("Mutable operator[] exception", false);
        } catch (const UnsupportedOperationException&) {
            printResult("Mutable operator[] exception", true);
        }
        
        // Тест 8: Slice
        bool bits3[] = {1, 0, 1, 1, 0, 1, 0, 0};
        BitSequence bs3(bits3, 8);
        Sequence<Bit>* sliced = bs3.Slice(2, 3);
        bool test8 = (sliced->GetLength() == 5); // 8-3+? = 5
        printResult("Slice", test8);
        assert(test8);
        delete sliced;
    }

    // ============= ТЕСТЫ MUTABLE/IMMUTABLE =============
    
    static void testMutableImmutable() {
        std::cout << "\n--- Testing Mutable/Immutable ---\n";
        
        int data[] = {1, 2, 3};
        
        // Mutable - изменения in-place
        MutableArraySequence<int> mutableSeq(data, 3);
        mutableSeq.Append(4)->Prepend(0);
        mutableSeq.Set(2, 99);

        bool test1 = (mutableSeq.GetLength() == 5) && 
                    (mutableSeq.GetFirst() == 0) && 
                    (mutableSeq.Get(3) == 3) && 
                    (mutableSeq[2] == 99);
        printResult("Mutable sequence (in-place changes)", test1);
        assert(test1);
        
        // Immutable - каждый раз новый объект
        ImmutableArraySequence<int> immutableSeq(data, 3);
        ImmutableArraySequence<int>* newSeq1 = 
            static_cast<ImmutableArraySequence<int>*>(immutableSeq.Append(4));
        ImmutableArraySequence<int>* newSeq2 = 
            static_cast<ImmutableArraySequence<int>*>(immutableSeq.Prepend(0));
        
        bool test2 = (immutableSeq.GetLength() == 3) &&  // исходная не изменилась
                    (newSeq1->GetLength() == 4) && 
                    (newSeq2->GetLength() == 4);
        printResult("Immutable (original unchanged)", test2);
        assert(test2);
        
        delete newSeq1;
        delete newSeq2;
        
        // Тест цепочки для immutable
        ImmutableArraySequence<int>* chained = 
            static_cast<ImmutableArraySequence<int>*>(immutableSeq.Append(4)->Prepend(0));
        bool test3 = (chained->GetLength() == 5) && 
                    (chained->GetFirst() == 0) && 
                    (chained->GetLast() == 4);
        printResult("Immutable (chained operations)", test3);
        assert(test3);
        delete chained;
        
        // Попытка модификации через operator[] у immutable
        try {
            immutableSeq[1] = 99;
        } 
        catch (const UnsupportedOperationException&) {
            printResult("Immutable operator[] disabled", true);
        }
    }

    // ============= ТЕСТЫ MAP-REDUCE =============
    
    static void testMapReduce() {
        std::cout << "\n--- Testing Map-Reduce ---\n";
        
        int data[] = {1, 2, 3, 4, 5};
        MutableArraySequence<int> seq(data, 5);
        
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

    // ============= ТЕСТЫ ИТЕРАТОРОВ =============
    
    static void testIterators() {
        std::cout << "\n--- Testing Iterators ---\n";
        
        int data[] = {10, 20, 30, 40, 50};
        MutableArraySequence<int> seq(data, 5);
        
        // Тест ArrayEnumerator
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
        
        // Тест Reset
        IEnumerator<int>* enum2 = seq.GetEnumerator();
        enum2->MoveNext();
        enum2->MoveNext();
        int first = enum2->GetCurrent(); // должно быть 20
        enum2->Reset();
        enum2->MoveNext();
        int afterReset = enum2->GetCurrent(); // должно быть 10
        bool test2 = (first == 20) && (afterReset == 10);
        printResult("Enumerator Reset", test2);
        assert(test2);
        delete enum2;
        
    }

    // ============= ТЕСТЫ ДОПОЛНИТЕЛЬНЫХ ЗАДАЧ =============
    
    static void testExtraTasks() {
        std::cout << "\n--- Testing Extra Tasks (T-1, T-6, T-8) ---\n";
        
        int data[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
        MutableArraySequence<int> seq(data, 9);
        
        // П-1: Min, Max, Avg
        auto mmResult = Task_MinMaxAvg<int>::compute(seq);
        bool test1 = (mmResult.min == 1) && (mmResult.max == 9) && 
                     (mmResult.avg > 4.9 && mmResult.avg < 5.1) && 
                     (mmResult.count == 9);
        printResult("Task-1: Min, Max, Avg", test1);
        assert(test1);
        
        // П-6: Moving Average
        ArraySequence<double>* maResult = Task_MovingAverage<int>::computeTripleAverage(seq);
        bool test2 = (maResult->GetLength() == 9);
        if (test2) {
            // Проверяем несколько значений
            double expected[] = {3.5, 5, 3.6667, 6, 4.3333, 6.3333, 4.6667, 6.5, 5};
            test2 = (abs(maResult->Get(0) - 3.5) < 0.1);
        }
        printResult("Task-6: Moving Average", test2);
        assert(test2);
        delete maResult;
        
        // П-8: Reflection Sum
        ArraySequence<int>* refResult = Task_ReflectionSum<int>::computeFullReflection(seq);
        bool test3 = (refResult->GetLength() == 9);
        if (test3) {
            // Для последовательности [5,2,8,1,9,3,7,4,6]
            // Отражение: [5+6, 2+4, 8+7, 1+3, 9+9, 3+1, 7+8, 4+2, 6+5] = [11,6,15,4,18,4,15,6,11]
            test3 = (refResult->Get(0) == 11) && (refResult->Get(4) == 18);
        }
        printResult("Task-8: Reflection Sum", test3);
        assert(test3);
        delete refResult;
    }

    // ============= ТЕСТЫ ГРАНИЧНЫХ СЛУЧАЕВ =============
    
    static void testEdgeCases() {
        std::cout << "\n--- Testing Edge Cases ---\n";
        
        // Пустая последовательность
        MutableArraySequence<int> emptySeq;
        bool test1 = (emptySeq.GetLength() == 0);
        printResult("Empty sequence creation", test1);
        assert(test1);
        
        // Try методы на пустой
        Option<int> first = emptySeq.TryGetFirst();
        bool test2 = first.IsNone();
        printResult("TryGetFirst on empty", test2);
        assert(test2);
        
        // Append к пустой (возвращает указатель)
        emptySeq.Append(42);
        bool test3 = (emptySeq.GetLength() == 1) && (emptySeq.GetFirst() == 42);
        printResult("Append to empty", test3);
        assert(test3);
        
        // Slice с отрицательным индексом
        int data[] = {1, 2, 3, 4, 5};
        MutableArraySequence<int> seq(data, 5);
        Sequence<int>* sliced = seq.Slice(-2, 2);
        bool test4 = (sliced->GetLength() == 3) && 
                    (sliced->Get(0) == 1) && 
                    (sliced->Get(1) == 2) && 
                    (sliced->Get(2) == 3);
        printResult("Slice with negative index", test4);
        assert(test4);
        delete sliced;
        
        // Slice с заменой
        int replData[] = {99, 100};
        MutableArraySequence<int> replacement(replData, 2);
        Sequence<int>* slicedWithRepl = seq.Slice(2, 2, &replacement);
        bool test5 = (slicedWithRepl->GetLength() == 5) && 
                    (slicedWithRepl->Get(2) == 99);
        printResult("Slice with replacement", test5);
        assert(test5);
        delete slicedWithRepl;

        try {
            seq.Slice(10, 2);
            printResult("Slice out of range exception", false);
        } catch (const IndexOutOfRangeException&) {
            printResult("Slice out of range exception", true);
        }
    }

    // ============= ЗАПУСК ВСЕХ ТЕСТОВ =============
    
    static void runAllTests() {
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
    }
};

#endif // _TESTS_HPP_