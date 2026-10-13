#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <sstream>
#include <iostream>

// ============================================================
// STAGE 0 Tests
// ============================================================

/// Create a LegacyData union with an int (42). Call printLegacyData.
/// Verify the returned string matches "42".
void test_printLegacyData_int(void) 
{
    LegacyData data;
    data.i = 42;

    
    TEST_ASSERT_TRUE_MESSAGE(printLegacyData(data, 'i') == "42", "ERROR: returned string != 42");
}

/// Create a LegacyData union with a double (3.14). Call printLegacyData.
/// Verify the returned string matches "3.14".
void test_printLegacyData_double(void) 
{
    LegacyData data;
    data.d = 3.14;
    TEST_ASSERT_TRUE_MESSAGE(printLegacyData(data, 'd') == "3.14", "ERROR: returned string != 3.14");
}

// ============================================================
// STAGE 1 Tests
// ============================================================

/// Call createTwoStructNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoStructNodes_links_correctly(void) 
{
    structNode* head = createTwoStructNodes();
    TEST_ASSERT_TRUE_MESSAGE(head->value.i == 5, "ERROR: head->value != 5");
   

    if (head != nullptr) {
        delete head->nextPtr;
        delete head;

        head = nullptr;
    }
}

// ============================================================
// STAGE 2 Tests
// ============================================================

/// Call createTwoClassNodes().
/// Verify head->value contains int 5 with type 'i', and head->nextPtr->value contains double ~3.14 with type 'd'.
/// Clean up allocated memory.
void test_createTwoClassNodes_links_correctly(void) 
{
    classNode *head = createTwoClassNodes();

    TEST_ASSERT_TRUE_MESSAGE(head->value.i == 5, "ERROR: head->value != 5");


    if (head != nullptr) {
        delete head->nextPtr;
        delete head;

        head = nullptr;
    }

    
}

// ============================================================
// STAGE 3 Tests
// ============================================================

/// Call createTwoTemplateNodes().
/// Verify head->value is 5 and head->nextPtr->value is 3.
/// Clean up allocated memory.
void test_createTwoTemplateNodes_links_correctly(void) 
{
    classNodeT<int>* head = createTwoTemplateNodes();
    TEST_ASSERT_TRUE_MESSAGE(head->value == 5, "ERROR: head->value != 5");
    TEST_ASSERT_TRUE_MESSAGE(head->nextPtr->value == 3, "ERROR: head->nextPtr->value != 3");

    if (head != nullptr) {
        delete head->nextPtr;
        delete head;

        head = nullptr;
    }
}

// ============================================================
// STAGE 4: LinkedList Tests
// ============================================================

/// Create a LinkedList. Add two nodes using addFirst.
/// Verify listLength() returns 2 after insertions.
void test_linkedList_addFirst_updates_counter(void) 
{

    LinkedList* head = new LinkedList();
    classNodeVariant* node1 = new classNodeVariant(5);
    classNodeVariant* node2 = new classNodeVariant(7);
    head->addFirst(node1);
    head->addFirst(node2);
    int count = head->listLength();

    TEST_ASSERT_TRUE_MESSAGE(count == 2, "ERROR: count != 2");
}

/// Create a LinkedList. Add nodes (10, then 20) using addLast.
/// Capture std::cout and verify elements appear in order ("10" before "20").
void test_linkedList_addLast_places_at_end(void) 
{
    LinkedList* list = new LinkedList();
    classNodeVariant* node1 = new classNodeVariant(10);
    classNodeVariant* node2 = new classNodeVariant(20);
    list->addLast(node1);
    list->addLast(node2);

    std::stringstream buff;
    std::streambuf* old_buffer = std::cout.rdbuf(buff.rdbuf());

    list->printList();

    std::cout.rdbuf(old_buffer);

    std::string output = buff.str();
    size_t pos10 = output.find("10");
    size_t pos20 = output.find("20");

    
    TEST_ASSERT_TRUE_MESSAGE(pos10 != std::string::npos, "ERROR: output 1 != 10");
    TEST_ASSERT_TRUE_MESSAGE(pos20 != std::string::npos, "ERROR: output 2 != 20");
    TEST_ASSERT_TRUE_MESSAGE(pos10 < pos20, "ERROR: 20 comes before 10");

}

/// Create a LinkedList with an int, double, and string.
/// Call deleteValue() with the double value (3.14).
/// Verify list length decreases to 2 and second call returns -1.
void test_linkedList_deleteValue_removes_variant(void) 
{
    LinkedList* list = new LinkedList();
    classNodeVariant* node1 = new classNodeVariant(5);
    classNodeVariant* node2 = new classNodeVariant(3.14);
    classNodeVariant* node3 = new classNodeVariant("hello");
    list->addLast(node1);
    list->addLast(node2);
    list->addLast(node3);

    list->deleteValue(3.14);

    int count = list->listLength();
    list->printList();

    TEST_ASSERT_TRUE_MESSAGE(count == 2, "ERROR: count != 2");
}

/// Create a LinkedList and insert three nodes.
/// Call destroyList().
/// Verify listLength() becomes 0.
void test_linkedList_destroyList_clears_all(void) 
{
    LinkedList* list = new LinkedList();

    classNodeVariant* node1 = new classNodeVariant(1);
    classNodeVariant* node2 = new classNodeVariant(2);
    classNodeVariant* node3 = new classNodeVariant(3);

    list->addLast(node1);
    list->addLast(node2);
    list->addLast(node3);

    list->destroyList();

    int count = list->listLength();
    
    TEST_ASSERT_TRUE_MESSAGE(count == 0, "ERROR: count != 0");
}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteFirst().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteFirst(void) 
{
    LinkedList* list = new LinkedList();

    classNodeVariant* node1 = new classNodeVariant(10);
    classNodeVariant* node2 = new classNodeVariant(20);
    classNodeVariant* node3 = new classNodeVariant(30);

    list->addLast(node1);
    list->addLast(node2);
    list->addLast(node3);

    int status = list->deleteFirst();

    int count = list->listLength();
    std::cout << count;

    TEST_ASSERT_TRUE_MESSAGE(count == 2, "Count != 0");
    TEST_ASSERT_TRUE_MESSAGE(status == 0, "Return status != 0");

}

/// Create a LinkedList with nodes (10, 20, 30).
/// Call deleteLast().
/// Verify listLength() becomes 2 and operation returns 0.
void test_linkedList_deleteLast(void) 
{
    LinkedList* list = new LinkedList();

    classNodeVariant* node1 = new classNodeVariant(10);
    classNodeVariant* node2 = new classNodeVariant(20);
    classNodeVariant* node3 = new classNodeVariant(30);

    list->addLast(node1);
    list->addLast(node2);
    list->addLast(node3);

    int status = list->deleteLast();
    int count = list->listLength();

    TEST_ASSERT_TRUE_MESSAGE(count == 2, "Count != 2");
    TEST_ASSERT_TRUE_MESSAGE(status == 0, "Return status != 0");

}

/// Create a LinkedList with nodes (1, 2.5, "test").
/// Redirect std::cout buffer and call printList().
/// Verify printed output contains "1", "2.5" (or "2.50"), and "test".
void test_linkedList_printList(void) 
{
    LinkedList* list = new LinkedList();

    classNodeVariant* node1 = new classNodeVariant(10);
    classNodeVariant* node2 = new classNodeVariant(2.5);
    classNodeVariant* node3 = new classNodeVariant("test");

    list->addLast(node1);
    list->addLast(node2);
    list->addLast(node3);

    std::stringstream buff;
    std::streambuf* old_buffer = std::cout.rdbuf(buff.rdbuf());

    list->printList();

    std::cout.rdbuf(old_buffer);

    std::string output = buff.str();
    size_t pos10 = output.find("10");
    size_t pos20 = output.find("2.5");
    size_t pos30 = output.find("test");


    TEST_ASSERT_TRUE_MESSAGE(pos10 != std::string::npos, "ERROR: output 1 != 10");
    TEST_ASSERT_TRUE_MESSAGE(pos20 != std::string::npos, "ERROR: output 2 != 2.5");
    TEST_ASSERT_TRUE_MESSAGE(pos30 != std::string::npos, "ERROR: output 3 != test");
}