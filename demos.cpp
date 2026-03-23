#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"
#include "ExtraTasks.hpp"
#include <iostream>
#include <limits>

class ConsoleUI {
private:
    static void clearInput() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    static void printHeader(const std::string& title) {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "   " << title << std::endl;
        std::cout << std::string(50, '=') << std::endl;
    }

    static void printMenu() {
        std::cout << "\nMAIN MENU:" << std::endl;
        std::cout << "1. Work with DynamicArray" << std::endl;
        std::cout << "2. Work with LinkedList" << std::endl;
        std::cout << "3. Work with MutableArraySequence" << std::endl;
        std::cout << "4. Work with ImmutableArraySequence" << std::endl;
        std::cout << "5. Work with MutableListSequence" << std::endl;
        std::cout << "6. Work with ImmutableListSequence" << std::endl;
        std::cout << "7. Work with BitSequence" << std::endl;
        std::cout << "8. Additional Tasks (P-1, P-6, P-8)" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose option: ";
    }

    // ============= HELPER FUNCTIONS =============
    
    template<typename T>
    static void printSequence(const Sequence<T>* seq, const std::string& name) {
        if (!seq) {
            std::cout << name << " = nullptr" << std::endl;
            return;
        }
        std::cout << name << " [" << seq->GetLength() << "]: [";
        for (int i = 0; i < seq->GetLength(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << (*seq)[i];
        }
        std::cout << "]" << std::endl;
    }

    static void printBitSequence(const BitSequence* bs, const std::string& name) {
        if (!bs) {
            std::cout << name << " = nullptr" << std::endl;
            return;
        }
        std::cout << name << " [" << bs->GetLength() << " bits]: ";
        for (int i = 0; i < bs->GetLength(); ++i) {
            std::cout << ((*bs)[i] ? "1" : "0");
            if ((i + 1) % 8 == 0 && i + 1 < bs->GetLength()) std::cout << " ";
        }
        std::cout << std::endl;
    }

    static int readInt(const std::string& prompt) {
        int value;
        std::cout << prompt;
        while (!(std::cin >> value)) {
            std::cout << "Error! Please enter an integer: ";
            clearInput();
        }
        clearInput();
        return value;
    }

    // ============= DYNAMIC ARRAY DEMO =============
    
    static void demoDynamicArray() {
        printHeader("DynamicArray Demonstration");
        
        int data[] = {10, 20, 30, 40, 50};
        DynamicArray<int> da(data, 5);
        
        std::cout << "Created DynamicArray: ";
        for (int i = 0; i < da.GetSize(); ++i) std::cout << da[i] << " ";
        std::cout << std::endl;
        
        da.Set(2, 99);
        std::cout << "After Set(2, 99): ";
        for (int i = 0; i < da.GetSize(); ++i) std::cout << da[i] << " ";
        std::cout << std::endl;
        
        da.Resize(7);
        std::cout << "After Resize(7): ";
        for (int i = 0; i < da.GetSize(); ++i) std::cout << da[i] << " ";
        std::cout << std::endl;
        
        da.Resize(3);
        std::cout << "After Resize(3): ";
        for (int i = 0; i < da.GetSize(); ++i) std::cout << da[i] << " ";
        std::cout << std::endl;
        
        DynamicArray<int>* sub = da.GetSubArray(0, 2);
        std::cout << "GetSubArray(0,2): ";
        for (int i = 0; i < sub->GetSize(); ++i) std::cout << (*sub)[i] << " ";
        std::cout << std::endl;
        delete sub;
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // ============= LINKED LIST DEMO =============
    
    static void demoLinkedList() {
        printHeader("LinkedList Demonstration");
        
        int data[] = {10, 20, 30, 40, 50};
        LinkedList<int> ll(data, 5);
        
        std::cout << "Created LinkedList: ";
        for (int i = 0; i < ll.GetLength(); ++i) std::cout << ll.Get(i) << " ";
        std::cout << std::endl;
        
        ll.Append(60);
        ll.Prepend(0);
        std::cout << "After Append(60) and Prepend(0): ";
        for (int i = 0; i < ll.GetLength(); ++i) std::cout << ll.Get(i) << " ";
        std::cout << std::endl;
        
        ll.InsertAt(99, 3);
        std::cout << "After InsertAt(99, 3): ";
        for (int i = 0; i < ll.GetLength(); ++i) std::cout << ll.Get(i) << " ";
        std::cout << std::endl;
        
        LinkedList<int>* sub = ll.GetSubList(2, 5);
        std::cout << "GetSubList(2,5): ";
        for (int i = 0; i < sub->GetLength(); ++i) std::cout << sub->Get(i) << " ";
        std::cout << std::endl;
        delete sub;
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // ============= MUTABLE ARRAY SEQUENCE DEMO =============
    
    static void demoMutableArraySequence() {
        printHeader("MutableArraySequence Demonstration");
        
        int data[] = {1, 2, 3, 4, 5};
        MutableArraySequence<int> seq(data, 5);
        
        std::cout << "Original: ";
        printSequence(&seq, "seq");
        
        seq.Append(6)->Prepend(0);
        std::cout << "After Append(6)->Prepend(0): ";
        printSequence(&seq, "seq");
        
        seq.InsertAt(99, 3);
        std::cout << "After InsertAt(99, 3): ";
        printSequence(&seq, "seq");
        
        seq.Set(2, 100);
        std::cout << "After Set(2, 100): ";
        printSequence(&seq, "seq");
        
        Sequence<int>* subSeq = seq.GetSubsequence(2, 5);
        std::cout << "GetSubsequence(2,5): ";
        printSequence(subSeq, "sub");
        delete subSeq;
        
        Sequence<int>* cloned = seq.Clone();
        std::cout << "Clone(): ";
        printSequence(cloned, "cloned");
        delete cloned;
        
        Option<int> first = seq.TryGetFirst();
        if (first.IsSome()) {
            std::cout << "TryGetFirst(): " << first.GetValue() << std::endl;
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // ============= IMMUTABLE ARRAY SEQUENCE DEMO =============
    
    static void demoImmutableArraySequence() {
        printHeader("ImmutableArraySequence Demonstration");
        
        int data[] = {1, 2, 3};
        ImmutableArraySequence<int> seq(data, 3);
        
        std::cout << "Original: ";
        printSequence(&seq, "immutable");
        
        Sequence<int>* appended = seq.Append(4);
        Sequence<int>* prepended = seq.Prepend(0);
        
        std::cout << "Original (unchanged): ";
        printSequence(&seq, "immutable");
        std::cout << "After Append(4): ";
        printSequence(appended, "new");
        std::cout << "After Prepend(0): ";
        printSequence(prepended, "new");
        
        delete appended;
        delete prepended;
        
        Sequence<int>* chained = seq.Append(4)->Prepend(0);
        std::cout << "Chained Append(4)->Prepend(0): ";
        printSequence(chained, "chained");
        delete chained;
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // ============= MUTABLE LIST SEQUENCE DEMO =============
    
    static void demoMutableListSequence() {
        printHeader("MutableListSequence Demonstration");
        
        int data[] = {10, 20, 30, 40, 50};
        MutableListSequence<int> seq(data, 5);
        
        std::cout << "Original: ";
        printSequence(&seq, "seq");
        
        seq.Append(60)->Prepend(0);
        std::cout << "After Append(60)->Prepend(0): ";
        printSequence(&seq, "seq");
        
        seq.InsertAt(99, 3);
        std::cout << "After InsertAt(99, 3): ";
        printSequence(&seq, "seq");
        
        seq.Set(2, 100);
        std::cout << "After Set(2, 100): ";
        printSequence(&seq, "seq");
        
        Sequence<int>* subSeq = seq.GetSubsequence(2, 5);
        std::cout << "GetSubsequence(2,5): ";
        printSequence(subSeq, "sub");
        delete subSeq;
        
        Sequence<int>* filtered = seq.Where([](int x) { return x > 30; });
        std::cout << "Where(x > 30): ";
        printSequence(filtered, "filtered");
        delete filtered;
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // ============= IMMUTABLE LIST SEQUENCE DEMO =============
    
    static void demoImmutableListSequence() {
        printHeader("ImmutableListSequence Demonstration");
        
        int data[] = {10, 20, 30};
        ImmutableListSequence<int> seq(data, 3);
        
        std::cout << "Original: ";
        printSequence(&seq, "immutable");
        
        Sequence<int>* appended = seq.Append(40);
        Sequence<int>* prepended = seq.Prepend(0);
        
        std::cout << "Original (unchanged): ";
        printSequence(&seq, "immutable");
        std::cout << "After Append(40): ";
        printSequence(appended, "new");
        std::cout << "After Prepend(0): ";
        printSequence(prepended, "new");
        
        delete appended;
        delete prepended;
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // ============= BIT SEQUENCE DEMO =============
    
    static void demoBitSequence() {
        printHeader("BitSequence Demonstration");
        
        bool bits1[] = {1, 0, 1, 1, 0, 1, 0, 0};
        BitSequence bs1(bits1, 8);
        
        std::cout << "Original: ";
        printBitSequence(&bs1, "bs1");
        
        bs1.Append(Bit(true));
        bs1.Prepend(Bit(false));
        std::cout << "After Append(1) and Prepend(0): ";
        printBitSequence(&bs1, "bs1");
        
        bs1.InsertAt(Bit(true), 3);
        std::cout << "After InsertAt(1, 3): ";
        printBitSequence(&bs1, "bs1");
        
        bool bits2[] = {1, 1, 0, 0};
        bool bits3[] = {1, 0, 1, 0};
        BitSequence bs2(bits2, 4);
        BitSequence bs3(bits3, 4);
        
        std::cout << "\nBitwise operations:" << std::endl;
        std::cout << "bs2: ";
        printBitSequence(&bs2, "");
        std::cout << "bs3: ";
        printBitSequence(&bs3, "");
        
        BitSequence andRes = bs2.And(bs3);
        BitSequence orRes = bs2.Or(bs3);
        BitSequence xorRes = bs2.Xor(bs3);
        BitSequence notRes = bs2.Not();
        
        std::cout << "bs2 & bs3: ";
        printBitSequence(&andRes, "");
        std::cout << "bs2 | bs3: ";
        printBitSequence(&orRes, "");
        std::cout << "bs2 ^ bs3: ";
        printBitSequence(&xorRes, "");
        std::cout << "~bs2:       ";
        printBitSequence(&notRes, "");
        
        Sequence<Bit>* sliced = bs1.Slice(2, 3);
        std::cout << "\nSlice(2,3) from bs1: ";
        printBitSequence(dynamic_cast<BitSequence*>(sliced), "");
        delete sliced;
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // ============= EXTRA TASKS DEMO =============
    
    static void demoExtraTasks() {
        printHeader("Additional Tasks (P-1, P-6, P-8)");
        
        int data[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
        MutableArraySequence<int> seq(data, 9);
        
        std::cout << "Sequence: ";
        for (int i = 0; i < seq.GetLength(); ++i) std::cout << seq[i] << " ";
        std::cout << std::endl;
        
        // P-1: Min, Max, Avg
        auto mmResult = Task_MinMaxAvg<int>::compute(seq);
        std::cout << "\nP-1 (Min, Max, Avg):" << std::endl;
        mmResult.print();
        
        // P-6: Moving Average
        ArraySequence<double>* maResult = Task_MovingAverage<int>::computeTripleAverage(seq);
        std::cout << "\nP-6 (Moving Average by three):" << std::endl;
        std::cout << "Result: ";
        for (int i = 0; i < maResult->GetLength(); ++i) {
            std::cout << (*maResult)[i] << " ";
        }
        std::cout << std::endl;
        delete maResult;
        
        // P-8: Reflection Sum
        ArraySequence<int>* refResult = Task_ReflectionSum<int>::computeFullReflection(seq);
        std::cout << "\nP-8 (Reflection Sum a_i + a_{n-i}):" << std::endl;
        std::cout << "Result: ";
        for (int i = 0; i < refResult->GetLength(); ++i) {
            std::cout << (*refResult)[i] << " ";
        }
        std::cout << std::endl;
        delete refResult;
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

public:
    static void run() {
        int choice;
        do {
            // system("cls");
            
            printHeader("LABORATORY WORK #2");
            printMenu();
            
            choice = readInt("");
            
            switch (choice) {
                case 1: demoDynamicArray(); break;
                case 2: demoLinkedList(); break;
                case 3: demoMutableArraySequence(); break;
                case 4: demoImmutableArraySequence(); break;
                case 5: demoMutableListSequence(); break;
                case 6: demoImmutableListSequence(); break;
                case 7: demoBitSequence(); break;
                case 8: demoExtraTasks(); break;
                case 0: std::cout << "Exiting program...\n"; break;
                default: std::cout << "Invalid choice! Press Enter to continue...\n";
                         std::cin.get(); break;
            }
        } while (choice != 0);
    }
};

int main() {
    try {
        ConsoleUI::run();
    } catch (const std::exception& e) {
        std::cerr << "\n Unhandled exception: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}