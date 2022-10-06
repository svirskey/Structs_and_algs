

#include "Structures/forward_list.hpp"
#include <forward_list>

#include "Structures/string.hpp"
#include <string>

#include <iostream>


void test_forward_list()
{
    sv::forward_list<int> lst_my { 10, 20, 30, 40, 50};
    std::forward_list<int> lst_stl { 10, 20, 30, 40, 50};
    bool test_passed = true;
    
    std::cout << "<------forward_list testing------>" << std::endl;


    auto loop_checker = [&lst_my, &lst_stl]() -> void
    {
        auto it_my = lst_my.begin();
        auto it_stl = lst_stl.begin();

        for (; it_my != lst_my.end() && it_stl != lst_stl.end(); ++it_my, ++it_stl)
        {
            if (*it_my != *it_stl)
                throw std::exception("failed [wrong values]");
        }
        if (it_my != lst_my.end() || it_stl != lst_stl.end())
            throw std::exception("failed [wrong list size]");
        std::cout << "OK" << std::endl;
    };

    try
    {
        std::cout << "list_initialization\t: ";

        loop_checker();
    }
    catch (std::exception& ex)
    {
        test_passed = false;
        std::cout << ex.what() << std::endl;
    }

    try
    {
        std::cout << "push_front\t\t: ";

        lst_my.push_front(1);
        lst_my.push_front(2);
        lst_my.push_front(3);
        lst_stl.push_front(1);
        lst_stl.push_front(2);
        lst_stl.push_front(3);

        loop_checker();
    }
    catch (std::exception& ex)
    {
        test_passed = false;
        std::cout <<ex.what() << std::endl;
    }

    try
    {
        std::cout << "clear\t\t\t: ";

        lst_my.clear();
        lst_stl.clear();

        loop_checker();
    }
    catch (std::exception& ex)
    {
        test_passed = false;
        std::cout << ex.what() << std::endl;
    }

    try
    {
        std::cout << "pop_front\t\t: ";

        lst_my.push_front(2);
        lst_my.push_front(3);
        lst_my.pop_front();
        lst_my.pop_front();
        lst_my.push_front(1);

        lst_stl.push_front(2);
        lst_stl.push_front(3);
        lst_stl.pop_front(); // stl realization doesn`t check for empty list
        lst_stl.pop_front();
        lst_stl.push_front(1);

        loop_checker();
    }
    catch (std::exception& ex)
    {
        test_passed = false;
        std::cout << ex.what() << std::endl;
    }

    if (test_passed)
        std::cout << "<------forward_list tests passed------>" << std::endl;
    else
        std::cout << "<------forward_list tests failed------>" << std::endl;
}


void test_string()
{
    sv::String str{ "string here" };
    str += "1313";

    std::cout << str << std::endl;
}

int main()
{
    test_forward_list();
   // test_list(); // in progress
   // test_string(); // in progress

}