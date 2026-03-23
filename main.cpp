#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "BitSequence.hpp"
#include "ExtraTasks.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

// ============================================================================
//                           CONSOLE USER INTERFACE
// ============================================================================

class ConsoleUI {
private:
    // Текущие объекты для работы
    MutableArraySequence<int>* currentArraySeq;
    MutableListSequence<int>* currentListSeq;
    BitSequence* currentBitSeq;
    ImmutableArraySequence<int>* currentImmutableArraySeq;
    ImmutableListSequence<int>* currentImmutableListSeq;

    // ============= ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ =============

    static void clearInput() {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    static void waitForKey() {
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    static void printHeader(const char* title) {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "   " << title << std::endl;
        std::cout << std::string(50, '=') << std::endl;
    }

    static int readInt(const char* prompt) {
        int value;
        std::cout << prompt;
        while (!(std::cin >> value)) {
            std::cout << "Error! Please enter an integer: ";
            clearInput();
        }
        clearInput();
        return value;
    }

    static bool readBool(const char* prompt) {
        char input;
        std::cout << prompt << " (1/0 or y/n): ";
        std::cin >> input;
        clearInput();
        return (input == '1' || input == 'y' || input == 'Y' || input == 't');
    }

    template<typename T>
    static void printSequence(const Sequence<T>* seq, const char* name) {
        if (!seq) {
            std::cout << name << " = nullptr (not created)" << std::endl;
            return;
        }
        std::cout << name << " [" << seq->GetLength() << "]: [";
        for (int i = 0; i < seq->GetLength(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << (*seq)[i];
        }
        std::cout << "]" << std::endl;
    }

    static void printBitSequence(const BitSequence* bs, const char* name) {
        if (!bs) {
            std::cout << name << " = nullptr (not created)" << std::endl;
            return;
        }
        std::cout << name << " [" << bs->GetLength() << " bits]: ";
        for (int i = 0; i < bs->GetLength(); ++i) {
            std::cout << ((*bs)[i] ? "1" : "0");
            if ((i + 1) % 8 == 0 && i + 1 < bs->GetLength()) std::cout << " ";
        }
        std::cout << std::endl;
    }

    static int* readArray(int& size) {
        size = readInt("Enter number of elements: ");
        int* arr = new int[size];
        std::cout << "Enter " << size << " integers:\n";
        for (int i = 0; i < size; ++i) {
            arr[i] = readInt(("  [" + std::to_string(i) + "]: ").c_str());
        }
        return arr;
    }

    static bool* readBitArray(int& size) {
        size = readInt("Enter number of bits: ");
        bool* arr = new bool[size];
        std::cout << "Enter " << size << " bits (0/1):\n";
        for (int i = 0; i < size; ++i) {
            arr[i] = readBool(("  [" + std::to_string(i) + "]: ").c_str());
        }
        return arr;
    }

    static int* generateRandomArray(int& size) {
        size = readInt("Enter number of elements: ");
        int* arr = new int[size];
        for (int i = 0; i < size; ++i) {
            arr[i] = rand() % 100;
        }
        return arr;
    }

    static bool* generateRandomBits(int& size) {
        size = readInt("Enter number of bits: ");
        bool* arr = new bool[size];
        for (int i = 0; i < size; ++i) {
            arr[i] = rand() % 2;
        }
        return arr;
    }

    // ============= ОЧИСТКА ТЕКУЩИХ ОБЪЕКТОВ =============

    void clearCurrentObjects() {
        delete currentArraySeq;
        delete currentListSeq;
        delete currentBitSeq;
        delete currentImmutableArraySeq;
        delete currentImmutableListSeq;
        
        currentArraySeq = nullptr;
        currentListSeq = nullptr;
        currentBitSeq = nullptr;
        currentImmutableArraySeq = nullptr;
        currentImmutableListSeq = nullptr;
    }

    // ============= СОЗДАНИЕ ОБЪЕКТОВ =============

    void createMutableArraySequence() {
        printHeader("Create MutableArraySequence");
        std::cout << "1. From array (manual input)\n";
        std::cout << "2. From random array\n";
        std::cout << "3. Empty sequence\n";
        
        int choice = readInt("Choice: ");
        
        if (currentArraySeq) delete currentArraySeq;
        
        if (choice == 1) {
            int size;
            int* arr = readArray(size);
            currentArraySeq = new MutableArraySequence<int>(arr, size);
            delete[] arr;
        } else if (choice == 2) {
            int size;
            int* arr = generateRandomArray(size);
            currentArraySeq = new MutableArraySequence<int>(arr, size);
            delete[] arr;
        } else {
            currentArraySeq = new MutableArraySequence<int>();
        }
        std::cout << "Sequence created!\n";
        printSequence(currentArraySeq, "Current");
        waitForKey();
    }

    void createMutableListSequence() {
        printHeader("Create MutableListSequence");
        std::cout << "1. From array (manual input)\n";
        std::cout << "2. From random array\n";
        std::cout << "3. Empty sequence\n";
        
        int choice = readInt("Choice: ");
        
        if (currentListSeq) delete currentListSeq;
        
        if (choice == 1) {
            int size;
            int* arr = readArray(size);
            currentListSeq = new MutableListSequence<int>(arr, size);
            delete[] arr;
        } else if (choice == 2) {
            int size;
            int* arr = generateRandomArray(size);
            currentListSeq = new MutableListSequence<int>(arr, size);
            delete[] arr;
        } else {
            currentListSeq = new MutableListSequence<int>();
        }
        std::cout << "Sequence created!\n";
        printSequence(currentListSeq, "Current");
        waitForKey();
    }

    void createImmutableArraySequence() {
        printHeader("Create ImmutableArraySequence");
        std::cout << "1. From array (manual input)\n";
        std::cout << "2. From random array\n";
        std::cout << "3. Empty sequence\n";
        
        int choice = readInt("Choice: ");
        
        if (currentImmutableArraySeq) delete currentImmutableArraySeq;
        
        if (choice == 1) {
            int size;
            int* arr = readArray(size);
            currentImmutableArraySeq = new ImmutableArraySequence<int>(arr, size);
            delete[] arr;
        } else if (choice == 2) {
            int size;
            int* arr = generateRandomArray(size);
            currentImmutableArraySeq = new ImmutableArraySequence<int>(arr, size);
            delete[] arr;
        } else {
            currentImmutableArraySeq = new ImmutableArraySequence<int>();
        }
        std::cout << "Sequence created!\n";
        printSequence(currentImmutableArraySeq, "Current");
        waitForKey();
    }

    void createImmutableListSequence() {
        printHeader("Create ImmutableListSequence");
        std::cout << "1. From array (manual input)\n";
        std::cout << "2. From random array\n";
        std::cout << "3. Empty sequence\n";
        
        int choice = readInt("Choice: ");
        
        if (currentImmutableListSeq) delete currentImmutableListSeq;
        
        if (choice == 1) {
            int size;
            int* arr = readArray(size);
            currentImmutableListSeq = new ImmutableListSequence<int>(arr, size);
            delete[] arr;
        } else if (choice == 2) {
            int size;
            int* arr = generateRandomArray(size);
            currentImmutableListSeq = new ImmutableListSequence<int>(arr, size);
            delete[] arr;
        } else {
            currentImmutableListSeq = new ImmutableListSequence<int>();
        }
        std::cout << "Sequence created!\n";
        printSequence(currentImmutableListSeq, "Current");
        waitForKey();
    }

    void createBitSequence() {
        printHeader("Create BitSequence");
        std::cout << "1. From binary string (e.g., 101010)\n";
        std::cout << "2. From bits (manual input)\n";
        std::cout << "3. From random bits\n";
        std::cout << "4. Empty sequence\n";
        
        int choice = readInt("Choice: ");
        
        if (currentBitSeq) delete currentBitSeq;
        
        if (choice == 1) {
            std::cout << "Enter binary string: ";
            std::string bits;
            std::cin >> bits;
            clearInput();
            bool* boolBits = new bool[bits.length()];
            for (size_t i = 0; i < bits.length(); ++i) {
                boolBits[i] = (bits[i] == '1');
            }
            currentBitSeq = new BitSequence(boolBits, bits.length());
            delete[] boolBits;
        } else if (choice == 2) {
            int size;
            bool* bits = readBitArray(size);
            currentBitSeq = new BitSequence(bits, size);
            delete[] bits;
        } else if (choice == 3) {
            int size;
            bool* bits = generateRandomBits(size);
            currentBitSeq = new BitSequence(bits, size);
            delete[] bits;
        } else {
            currentBitSeq = new BitSequence(0);
        }
        std::cout << "Bit sequence created!\n";
        printBitSequence(currentBitSeq, "Current");
        waitForKey();
    }

    // ============= РАБОТА С MUTABLE ARRAY SEQUENCE =============

    void operateMutableArraySequence() {
        if (!currentArraySeq) {
            std::cout << "No sequence! Create one first.\n";
            waitForKey();
            return;
        }

        while (true) {
            printHeader("MutableArraySequence Operations");
            std::cout << "Current: ";
            printSequence(currentArraySeq, "");
            
            std::cout << "\nOperations:\n";
            std::cout << " 1. Append\n";
            std::cout << " 2. Prepend\n";
            std::cout << " 3. Insert at index\n";
            std::cout << " 4. Set at index\n";
            std::cout << " 5. Get at index\n";
            std::cout << " 6. Get subsequence\n";
            std::cout << " 7. Map (multiply by 2)\n";
            std::cout << " 8. Where (filter even)\n";
            std::cout << " 9. Reduce (sum)\n";
            std::cout << "10. Clone\n";
            std::cout << "11. Try methods\n";
            std::cout << "12. Slice\n";
            std::cout << "13. Print length\n";
            std::cout << "14. Create new sequence (replace)\n";
            std::cout << " 0. Back\n";
            
            int choice = readInt("Choice: ");
            
            switch (choice) {
                case 1: {
                    int val = readInt("Enter value: ");
                    currentArraySeq->Append(val);
                    break;
                }
                case 2: {
                    int val = readInt("Enter value: ");
                    currentArraySeq->Prepend(val);
                    break;
                }
                case 3: {
                    int idx = readInt("Enter index: ");
                    int val = readInt("Enter value: ");
                    try {
                        currentArraySeq->InsertAt(val, idx);
                    } catch (const IndexOutOfRangeException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                        waitForKey();
                    }
                    break;
                }
                case 4: {
                    int idx = readInt("Enter index: ");
                    int val = readInt("Enter value: ");
                    try {
                        currentArraySeq->Set(idx, val);
                    } catch (const IndexOutOfRangeException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                        waitForKey();
                    }
                    break;
                }
                case 5: {
                    int idx = readInt("Enter index: ");
                    try {
                        std::cout << "Value: " << (*currentArraySeq)[idx] << std::endl;
                    } catch (const IndexOutOfRangeException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    waitForKey();
                    continue;
                }
                case 6: {
                    int start = readInt("Start index: ");
                    int end = readInt("End index: ");
                    try {
                        Sequence<int>* sub = currentArraySeq->GetSubsequence(start, end);
                        printSequence(sub, "Subsequence");
                        delete sub;
                    } catch (const IndexOutOfRangeException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    waitForKey();
                    continue;
                }
                case 7: {
                    Sequence<int>* result = currentArraySeq->Map<int>([](int x) { return x * 2; });
                    printSequence(result, "Map result (x2)");
                    delete result;
                    waitForKey();
                    continue;
                }
                case 8: {
                    Sequence<int>* result = currentArraySeq->Where([](int x) { return x % 2 == 0; });
                    printSequence(result, "Where result (even)");
                    delete result;
                    waitForKey();
                    continue;
                }
                case 9: {
                    int sum = currentArraySeq->Reduce<int>(0, [](int acc, int x) { return acc + x; });
                    std::cout << "Sum: " << sum << std::endl;
                    waitForKey();
                    continue;
                }
                case 10: {
                    Sequence<int>* cloned = currentArraySeq->Clone();
                    printSequence(cloned, "Clone");
                    delete cloned;
                    waitForKey();
                    continue;
                }
                case 11: {
                    Option<int> first = currentArraySeq->TryGetFirst();
                    Option<int> last = currentArraySeq->TryGetLast();
                    Option<int> found = currentArraySeq->TryFind([](int x) { return x > 50; });
                    std::cout << "TryGetFirst: " << (first.IsSome() ? std::to_string(first.GetValue()) : "None") << std::endl;
                    std::cout << "TryGetLast: " << (last.IsSome() ? std::to_string(last.GetValue()) : "None") << std::endl;
                    std::cout << "TryFind(x>50): " << (found.IsSome() ? std::to_string(found.GetValue()) : "None") << std::endl;
                    waitForKey();
                    continue;
                }
                case 12: {
                    int start = readInt("Start index: ");
                    int cnt = readInt("Count: ");
                    try {
                        Sequence<int>* result = currentArraySeq->Slice(start, cnt);
                        printSequence(result, "Slice result");
                        delete result;
                    } catch (const IndexOutOfRangeException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    waitForKey();
                    continue;
                }
                case 13: {
                    std::cout << "Length: " << currentArraySeq->GetLength() << std::endl;
                    waitForKey();
                    continue;
                }
                case 14:
                    createMutableArraySequence();
                    break;
                case 0:
                    return;
                default:
                    std::cout << "Invalid choice!\n";
                    waitForKey();
                    continue;
            }
            std::cout << "Operation completed.\n";
            waitForKey();
        }
    }

    // ============= РАБОТА С BIT SEQUENCE =============

    void operateBitSequence() {
        if (!currentBitSeq) {
            std::cout << "No sequence! Create one first.\n";
            waitForKey();
            return;
        }

        while (true) {
            printHeader("BitSequence Operations");
            std::cout << "Current: ";
            printBitSequence(currentBitSeq, "");
            
            std::cout << "\nOperations:\n";
            std::cout << " 1. Append bit\n";
            std::cout << " 2. Prepend bit\n";
            std::cout << " 3. Insert at index\n";
            std::cout << " 4. Get at index\n";
            std::cout << " 5. Get subsequence\n";
            std::cout << " 6. Bitwise AND\n";
            std::cout << " 7. Bitwise OR\n";
            std::cout << " 8. Bitwise XOR\n";
            std::cout << " 9. Bitwise NOT\n";
            std::cout << "10. Slice\n";
            std::cout << "11. Print length\n";
            std::cout << "12. Create new sequence (replace)\n";
            std::cout << " 0. Back\n";
            
            int choice = readInt("Choice: ");
            
            switch (choice) {
                case 1: {
                    bool val = readBool("Enter bit value");
                    currentBitSeq->Append(Bit(val));
                    break;
                }
                case 2: {
                    bool val = readBool("Enter bit value");
                    currentBitSeq->Prepend(Bit(val));
                    break;
                }
                case 3: {
                    int idx = readInt("Enter index: ");
                    bool val = readBool("Enter bit value");
                    try {
                        currentBitSeq->InsertAt(Bit(val), idx);
                    } catch (const IndexOutOfRangeException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                        waitForKey();
                    }
                    break;
                }
                case 4: {
                    int idx = readInt("Enter index: ");
                    try {
                        std::cout << "Bit: " << ((*currentBitSeq)[idx] ? "1" : "0") << std::endl;
                    } catch (const IndexOutOfRangeException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    waitForKey();
                    continue;
                }
                case 5: {
                    int start = readInt("Start index: ");
                    int end = readInt("End index: ");
                    try {
                        Sequence<Bit>* sub = currentBitSeq->GetSubsequence(start, end);
                        printBitSequence(dynamic_cast<BitSequence*>(sub), "Subsequence");
                        delete sub;
                    } catch (const IndexOutOfRangeException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    waitForKey();
                    continue;
                }
                case 6: {  // Bitwise AND
                    std::cout << "\nCreate second bit sequence for AND operation:\n";
                    BitSequence* secondSeq = createSecondBitSequence();
                    printBitSequence(secondSeq, "");
                    if (secondSeq) {
                        try {
                            BitSequence result = (*currentBitSeq) & (*secondSeq);
                            std::cout << "\nResult of AND operation:\n";
                            printBitSequence(&result, "Result");
                        } catch (const DifferentLengthException& e) {
                            std::cout << "Error: " << e.what() << std::endl;
                            std::cout << "Sequences must have the same length for bitwise operations.\n";
                        }
                        delete secondSeq;
                    }
                    waitForKey();
                    continue;
                }
                case 7: {  // Bitwise OR
                    std::cout << "\nCreate second bit sequence for OR operation:\n";
                    BitSequence* secondSeq = createSecondBitSequence();
                    printBitSequence(secondSeq, "");
                    if (secondSeq) {
                        try {
                            BitSequence result = (*currentBitSeq) | (*secondSeq);
                            std::cout << "\nResult of OR operation:\n";
                            printBitSequence(&result, "Result");
                        } catch (const DifferentLengthException& e) {
                            std::cout << "Error: " << e.what() << std::endl;
                            std::cout << "Sequences must have the same length for bitwise operations.\n";
                        }
                        delete secondSeq;
                    }
                    waitForKey();
                    continue;
                }
                case 8: {  // Bitwise XOR
                    std::cout << "\nCreate second bit sequence for XOR operation:\n";
                    BitSequence* secondSeq = createSecondBitSequence();
                    printBitSequence(secondSeq, "");
                    if (secondSeq) {
                        try {
                            BitSequence result = (*currentBitSeq) ^ (*secondSeq);
                            std::cout << "\nResult of XOR operation:\n";
                            printBitSequence(&result, "Result");
                        } catch (const DifferentLengthException& e) {
                            std::cout << "Error: " << e.what() << std::endl;
                            std::cout << "Sequences must have the same length for bitwise operations.\n";
                        }
                        delete secondSeq;
                    }
                    waitForKey();
                    continue;
                }
                case 9: {
                    BitSequence result = ~(*currentBitSeq);
                    printBitSequence(&result, "NOT result");
                    waitForKey();
                    continue;
                }
                case 10: {
                    int start = readInt("Start index: ");
                    int cnt = readInt("Count: ");
                    try {
                        Sequence<Bit>* result = currentBitSeq->Slice(start, cnt);
                        printBitSequence(dynamic_cast<BitSequence*>(result), "Slice result");
                        delete result;
                    } catch (const IndexOutOfRangeException& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                    waitForKey();
                    continue;
                }
                case 11: {
                    std::cout << "Length: " << currentBitSeq->GetLength() << " bits" << std::endl;
                    waitForKey();
                    continue;
                }
                case 12:
                    createBitSequence();
                    break;
                case 0:
                    return;
                default:
                    std::cout << "Invalid choice!\n";
                    waitForKey();
                    continue;
            }
            std::cout << "Operation completed.\n";
            waitForKey();
        }
    }


    BitSequence* createSecondBitSequence() {
        std::cout << "Choose creation method5:\n";
        std::cout << "1. From binary string (e.g., 101010)\n";
        std::cout << "2. From bits (manual input)\n";
        std::cout << "3. From random bits\n";
        std::cout << "4. Empty sequence\n";
        
        int choice = readInt("Choice: ");
        
        if (choice == 1) {
            std::cout << "Enter binary string: ";
            std::string bits;
            std::cin >> bits;
            clearInput();
            bool* boolBits = new bool[bits.length()];
            for (size_t i = 0; i < bits.length(); ++i) {
                boolBits[i] = (bits[i] == '1');
            }
            BitSequence* result = new BitSequence(boolBits, bits.length());
            delete[] boolBits;
            return result;
        } else if (choice == 2) {
            int size;
            bool* bits = readBitArray(size);
            BitSequence* result = new BitSequence(bits, size);
            delete[] bits;
            return result;
        } else if (choice == 3) {
            int size;
            bool* bits = generateRandomBits(size);
            BitSequence* result = new BitSequence(bits, size);
            delete[] bits;
            return result;
        } else if (choice == 4) {
            return new BitSequence(0);
        } else {
            std::cout << "Invalid choice! Using empty sequence.\n";
            return new BitSequence(0);
        }
    }

    // ============= ОТОБРАЖЕНИЕ ВСЕХ ТЕКУЩИХ ОБЪЕКТОВ =============

    void showCurrentSequences() {
        printHeader("Current Sequences");
        std::cout << "MutableArraySequence: ";
        printSequence(currentArraySeq, "");
        std::cout << "MutableListSequence: ";
        printSequence(currentListSeq, "");
        std::cout << "ImmutableArraySequence: ";
        printSequence(currentImmutableArraySeq, "");
        std::cout << "ImmutableListSequence: ";
        printSequence(currentImmutableListSeq, "");
        std::cout << "BitSequence: ";
        printBitSequence(currentBitSeq, "");
        waitForKey();
    }

    // ============= ГЛАВНОЕ МЕНЮ =============

    void printMainMenu() {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "   LABORATORY WORK #2 - SEQUENCES" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        std::cout << "\nCREATE SEQUENCES:\n";
        std::cout << " 1. Create MutableArraySequence\n";
        std::cout << " 2. Create MutableListSequence\n";
        std::cout << " 3. Create ImmutableArraySequence\n";
        std::cout << " 4. Create ImmutableListSequence\n";
        std::cout << " 5. Create BitSequence\n";
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "WORK WITH SEQUENCES:\n";
        std::cout << " 6. Operate on MutableArraySequence\n";
        std::cout << " 7. Operate on BitSequence\n";
        std::cout << std::string(50, '-') << std::endl;
        std::cout << " 8. Show all current sequences\n";
        std::cout << " 0. Exit\n";
        std::cout << "Choose option: ";
    }

public:
    ConsoleUI() 
        : currentArraySeq(nullptr), currentListSeq(nullptr), currentBitSeq(nullptr),
          currentImmutableArraySeq(nullptr), currentImmutableListSeq(nullptr) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }
    
    ~ConsoleUI() {
        clearCurrentObjects();
    }

    void run() {
        int choice;
        do {
            printMainMenu();
            choice = readInt("");
            
            switch (choice) {
                case 1: createMutableArraySequence(); break;
                case 2: createMutableListSequence(); break;
                case 3: createImmutableArraySequence(); break;
                case 4: createImmutableListSequence(); break;
                case 5: createBitSequence(); break;
                case 6: operateMutableArraySequence(); break;
                case 7: operateBitSequence(); break;
                case 8: showCurrentSequences(); break;
                case 0: std::cout << "Exiting program...\n"; break;
                default: std::cout << "Invalid choice!\n"; waitForKey(); break;
            }
        } while (choice != 0);
    }
};

int main() {
    try {
        ConsoleUI ui;
        ui.run();
    } catch (const std::exception& e) {
        std::cerr << "\nUnhandled exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}