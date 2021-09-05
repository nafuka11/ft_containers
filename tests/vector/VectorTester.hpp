#ifndef VECTORTESTER_HPP
#define VECTORTESTER_HPP

#include <iostream>
#include "common.hpp"

template <class T>
class VectorTester
{
public:
    VectorTester(ft::vector<T> &vec) : original_vec(vec) {}
    ~VectorTester() {}
    void test_all()
    {
        test_constructor();
        test_assignment_operator();
        // Capacity
        test_max_size();
        test_resize();
        test_empty();
        test_reserve();
        // Element access
        test_subscript_operator();
        test_at();
        test_front_back();
        // Modifiers
        test_assign();
        test_push_back();
        test_pop_back();
        test_insert();
        test_erase();
        test_swap();
        test_clear();
        // Non-member function
        test_relational_operator();
    }

private:
    ft::vector<T> original_vec;

    void print_vector(ft::vector<T> &vec)
    {
        print_vector_info(vec);
        print_vector_elements(vec);
    }

    void print_vector(ft::vector<T> &vec, const std::string &name)
    {
        std::cout << name << ": ";
        print_vector_info(vec);
        print_vector_elements(vec);
    }

    void print_vector_info(ft::vector<T> &vec)
    {
        std::cout << "size()=" << vec.size()
                  << " capacity()=" << vec.capacity() << std::endl;
    }

    void print_vector_elements(ft::vector<T> &vec)
    {
        for (typename ft::vector<T>::iterator iter = vec.begin(); iter != vec.end(); ++iter)
        {
            std::cout << (*iter) << " ";
        }
        std::cout << std::endl;
    }

    void test_constructor()
    {
        print_test_case("vector::constructor");
        {
            ft::vector<T> vec;
            print_vector(vec, "vector()");
        }
        {
            ft::vector<T> vec(10);
            print_vector(vec, "vector(10)");
        }
        {
            ft::vector<T> vec(10, *original_vec.begin());
            std::cout << "vector(10, " << *original_vec.begin() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(original_vec.begin(), original_vec.end());
            std::cout << "vector(begin, end): ";
            print_vector_info(vec);
            print_vector_elements(vec);
        }
        {
            ft::vector<T> vec(original_vec);
            print_vector(vec, "vector(otherVec)");
        }
    }

    void test_assignment_operator()
    {
        print_test_case("vector::operator=");
        {
            ft::vector<T> dest(2, original_vec.front());
            ft::vector<T> src(5, original_vec.back());
            src.reserve(20);
            dest = src;
            print_vector(src, "src ");
            print_vector(dest, "dest");
        }
        {
            ft::vector<T> dest(6, original_vec.back());
            ft::vector<T> src(5, original_vec.front());
            dest = src;
            print_vector(src, "src ");
            print_vector(dest, "dest");
        }
        {
            ft::vector<T> dest;
            ft::vector<T> src(1, original_vec.front());
            dest = src;
            print_vector(src, "src ");
            print_vector(dest, "dest");
        }
        {
            ft::vector<T> dest(1, original_vec.back());
            ft::vector<T> src;
            dest = src;
            print_vector(src, "src ");
            print_vector(dest, "dest");
        }
    }

    void test_max_size()
    {
        print_test_case("vector::max_size()");
        ft::vector<T> vec;
        std::cout << vec.max_size() << std::endl;
    }

    void test_resize()
    {
        print_test_case("vector::resize()");
        {
            ft::vector<T> vec(5, original_vec.front());
            vec.resize(4);
            std::cout << "vector(5, " << original_vec.front() << ").resize(4): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, original_vec.front());
            vec.resize(6);
            std::cout << "vector(5, " << original_vec.front() << ").resize(6): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, original_vec.front());
            vec.resize(7, original_vec.back());
            std::cout << "vector(5, " << original_vec.front() << ").resize(7, " << original_vec.back() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, original_vec.front());
            vec.resize(0);
            std::cout << "vector(5, " << original_vec.front() << ").resize(0): ";
            print_vector(vec);
        }
    }

    void test_empty()
    {
        print_test_case("vector::empty()");
        ft::vector<T> vec_empty;
        std::cout << std::boolalpha << "vector().empty()=" << vec_empty.empty() << std::endl;
        ft::vector<T> vec_one(1);
        std::cout << std::boolalpha << "vector(1).empty()=" << vec_one.empty() << std::endl;
    }

    void test_reserve()
    {
        print_test_case("vector::reserve()");
        {
            ft::vector<T> vec = original_vec;
            std::cout << "vec.reserve(" << original_vec.size() - 1 << "): ";
            vec.reserve(original_vec.size() - 1);
            print_vector(vec);
        }
        {
            ft::vector<T> vec = original_vec;
            std::cout << "vec.reserve(" << original_vec.size() + 1 << "): ";
            vec.reserve(original_vec.size() + 1);
            print_vector(vec);
        }
        {
            ft::vector<T> vec;
            vec.reserve(42);
            print_vector(vec, "vector().reserve(42)");
        }
        {
            ft::vector<T> vec = original_vec;
            std::cout << "vec.reserve(" << vec.max_size() + 1 << "): ";
            try
            {
                vec.reserve(vec.max_size() + 1);
            }
            catch (const std::length_error &e)
            {
                std::cout << e.what();
            }
            std::cout << std::endl;
        }
    }

    void test_subscript_operator()
    {
        print_test_case("vector::operator[]");
        for (size_t i = 0; i < original_vec.size(); i++)
        {
            std::cout << "vec[" << i << "]=" << original_vec[i] << " ";
        }
        std::cout << std::endl;
    }

    void test_at()
    {
        print_test_case("vector::at()");
        for (size_t i = 0; i < original_vec.size() + 1; i++)
        {
            try
            {
                std::cout << "vec.at(" << i << ")=";
                std::cout << original_vec.at(i) << " ";
            }
            catch (const std::out_of_range &e)
            {
                std::cout << e.what() << " ";
            }
        }
        std::cout << std::endl;
    }

    void test_front_back()
    {
        print_test_case("vector::front(), back()");
        std::cout << "vec.front()=" << original_vec.front() << std::endl;
        std::cout << "vec.back() =" << original_vec.back() << std::endl;
    }

    void test_assign()
    {
        print_test_case("vector::assign()");
        test_assign_range(original_vec.begin(), original_vec.end());
        test_assign_range(original_vec.begin(), original_vec.begin());
        test_assign_range(original_vec.begin(), original_vec.end() - 1);
        test_assign_fill(0);
        test_assign_fill(2);
        test_assign_fill(5);
        test_assign_fill(10);
    }

    template <class InputIterator>
    void test_assign_range(InputIterator first, InputIterator last)
    {
        ft::vector<T> vec(original_vec.size());
        std::cout << "vec.assign(first=iter(" << (*first) << "), iter(first+" << last - first << ")): ";
        vec.assign(first, last);
        print_vector(vec);
    }

    void test_assign_fill(typename ft::vector<T>::size_type count)
    {
        ft::vector<T> vec = original_vec;
        std::cout << "vec.assign(" << count << ", " << original_vec.back() << "): ";
        vec.assign(count, original_vec.back());
        print_vector(vec);
    }

    void test_push_back()
    {
        print_test_case("vector::push_back()");
        ft::vector<T> vec;
        print_vector(vec);
        for (size_t i = 0; i < original_vec.size(); i++)
        {
            vec.push_back(original_vec[i]);
            print_vector(vec);
        }
    }

    void test_pop_back()
    {
        print_test_case("vector::pop_back()");
        ft::vector<T> vec = original_vec;
        vec.pop_back();
        print_vector(vec);
    }

    void test_insert()
    {
        print_test_case("vector::insert()");
        test_insert_single();
        test_insert_fill();
        test_insert_range();
    }

    void test_insert_single()
    {
        {
            ft::vector<T> vec(5, original_vec.front());
            vec.insert(vec.begin() + 2, original_vec.front());
            std::cout << "vector(5, 42).insert(begin()+2, " << original_vec.front() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec;
            vec.insert(vec.begin(), original_vec.front());
            std::cout << "vector().insert(begin(), " << original_vec.front() << "): ";
            print_vector(vec);
        }
    }

    void test_insert_fill()
    {
        {
            ft::vector<T> vec(5, original_vec.front());
            vec.insert(vec.begin(), 5, original_vec.back());
            std::cout << "vector(5, " << original_vec.front() << ").insert(begin(), 5, " << original_vec.back() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, original_vec.front());
            vec.insert(vec.begin() + 1, 5, original_vec.back());
            std::cout << "vector(5, " << original_vec.front() << ").insert(begin()+1, 5, " << original_vec.back() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, original_vec.back());
            vec.insert(vec.end() - 1, 5, original_vec.front());
            std::cout << "vec.insert(end()-1, 5, " << original_vec.front() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, original_vec.back());
            vec.insert(vec.end(), 5, original_vec.front());
            std::cout << "vector(5, " << original_vec.back() << ").insert(end(), 5, " << original_vec.front() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec;
            vec.insert(vec.begin(), 5, original_vec.front());
            std::cout << "vector().insert(end(), 5, " << original_vec.front() << "): ";
            print_vector(vec);
        }
    }

    void test_insert_range()
    {
        {
            ft::vector<T> vec(5, original_vec.back());
            vec.insert(vec.begin(), original_vec.begin(), original_vec.end());
            std::cout << "vector(5, " << original_vec.back() << ").insert(begin(), origVec.begin(), origVec.end()): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, original_vec.back());
            vec.insert(vec.begin() + 1, original_vec.begin(), original_vec.end());
            std::cout << "vector(5, " << original_vec.back() << ").insert(begin()+1, origVec.begin(), origVec.end()): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, original_vec.front());
            vec.insert(vec.end() - 1, original_vec.begin(), original_vec.end());
            std::cout << "vector(5, " << original_vec.front() << ").insert(end()-1, origVec.begin(), origVec.end()): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, original_vec.front());
            vec.insert(vec.end(), original_vec.begin(), original_vec.end());
            std::cout << "vector(5, " << original_vec.front() << ").insert(end(), origVec.begin(), origVec.end()): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec;
            vec.insert(vec.begin(), original_vec.begin(), original_vec.end());
            print_vector(vec, "vector().insert(begin(), origVec.begin(), origVec.end())");
        }
    }

    void test_erase()
    {
        print_test_case("vector::erase()");
        test_erase_single();
        test_erase_range();
    }

    void test_erase_single()
    {
        for (size_t i = 0; i < original_vec.size(); i++)
        {
            ft::vector<T> vec = original_vec;
            std::cout << "vec.erase(" << *(vec.begin() + i) << "): ";
            std::cout << "result=iter(begin()+" << (vec.erase(vec.begin() + i) - vec.begin()) << ") ";
            print_vector(vec);
        }
    }

    void test_erase_range()
    {
        {
            ft::vector<T> vec = original_vec;
            typename ft::vector<T>::iterator first = vec.begin();
            typename ft::vector<T>::iterator last = vec.end();
            std::cout << "vec.erase(first=iter(" << *first << "), iter(first+" << last - first << ")): ";
            std::cout << "result=iter(begin()+" << (vec.erase(first, last) - vec.begin()) << ") ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec = original_vec;
            typename ft::vector<T>::iterator first = vec.begin() + 1;
            typename ft::vector<T>::iterator last = vec.end() - 1;
            std::cout << "vec.erase(first=iter(" << *first << "), iter(first+" << last - first << ")): ";
            std::cout << "result=iter(begin()+" << (vec.erase(first, last) - vec.begin()) << ") ";
            print_vector(vec);
        }
    }

    void test_swap()
    {
        print_test_case("vector::swap()");
        {
            ft::vector<T> vec1(4, original_vec.front());
            ft::vector<T> vec2(2, original_vec.back());
            print_vector(vec1, "orig vec1   ");
            print_vector(vec2, "orig vec2   ");
            vec1.swap(vec2);
            print_vector(vec1, "swapped vec1");
            print_vector(vec2, "swapped vec2");
        }
        {
            ft::vector<T> vec1(4, original_vec.front());
            ft::vector<T> vec2(2, original_vec.back());
            print_vector(vec1, "orig vec1   ");
            print_vector(vec2, "orig vec2   ");
            ft::swap(vec1, vec2);
            print_vector(vec1, "swapped vec1");
            print_vector(vec2, "swapped vec2");
        }
    }

    void test_clear()
    {
        print_test_case("vector::clear()");
        ft::vector<T> vec = original_vec;
        vec.clear();
        print_vector_info(vec);
    }

    void test_relational_operator()
    {
        print_test_case("vector::operator==, !=, <, <=, >, >=");
        ft::vector<T> empty1;
        ft::vector<T> empty2;
        ft::vector<T> five1(5, original_vec.front());
        ft::vector<T> five2(5, original_vec.front());
        ft::vector<T> front_diff(5, original_vec.front());
        ft::vector<T> back_diff(5, original_vec.front());
        ft::vector<T> six(6, original_vec.front());
        front_diff[0] = original_vec.back();
        back_diff[back_diff.size() - 1] = original_vec.back();

        std::cout << std::boolalpha
                  << "empty == empty     : " << (empty1 == empty2) << std::endl
                  << "empty == five      : " << (empty1 == five1) << std::endl
                  << "five  == five      : " << (five1 == five2) << std::endl
                  << "five  == frontDiff : " << (five1 == front_diff) << std::endl
                  << "five  == backDiff  : " << (five2 == back_diff) << std::endl;
        std::cout << std::boolalpha
                  << "empty != empty     : " << (empty1 != empty2) << std::endl
                  << "empty != five      : " << (empty1 != five1) << std::endl
                  << "five  != five      : " << (five1 != five2) << std::endl
                  << "five  != frontDiff : " << (five1 != front_diff) << std::endl
                  << "five  != backDiff  : " << (five2 != back_diff) << std::endl;
        std::cout << std::boolalpha
                  << "empty    <  empty     : " << (empty1 < empty2) << std::endl
                  << "empty    <  five      : " << (empty1 < five1) << std::endl
                  << "five     <  empty     : " << (five1 < empty1) << std::endl
                  << "five     <  five      : " << (five1 < five2) << std::endl
                  << "six      <  five      : " << (six < five1) << std::endl
                  << "five     <  six       : " << (five1 < six) << std::endl
                  << "five     <  frontDiff : " << (five1 < front_diff) << std::endl
                  << "frontDiff<  five      : " << (front_diff < five1) << std::endl
                  << "five     <  backDiff  : " << (five2 < back_diff) << std::endl
                  << "backDiff <  five      : " << (back_diff < back_diff) << std::endl;
        std::cout << std::boolalpha
                  << "empty    <= empty     : " << (empty1 <= empty2) << std::endl
                  << "empty    <= five      : " << (empty1 <= five1) << std::endl
                  << "five     <= empty     : " << (five1 <= empty1) << std::endl
                  << "five     <= five      : " << (five1 <= five2) << std::endl
                  << "six      <= five      : " << (six <= five1) << std::endl
                  << "five     <= six       : " << (five1 <= six) << std::endl
                  << "five     <= frontDiff : " << (five1 <= front_diff) << std::endl
                  << "frontDiff<= five      : " << (front_diff <= five1) << std::endl
                  << "five     <= backDiff  : " << (five2 <= back_diff) << std::endl
                  << "backDiff <= five      : " << (back_diff <= back_diff) << std::endl;
        std::cout << std::boolalpha
                  << "empty    >  empty     : " << (empty1 > empty2) << std::endl
                  << "empty    >  five      : " << (empty1 > five1) << std::endl
                  << "five     >  empty     : " << (five1 > empty1) << std::endl
                  << "five     >  five      : " << (five1 > five2) << std::endl
                  << "six      >  five      : " << (six > five1) << std::endl
                  << "five     >  six       : " << (five1 > six) << std::endl
                  << "five     >  frontDiff : " << (five1 > front_diff) << std::endl
                  << "frontDiff>  five      : " << (front_diff > five1) << std::endl
                  << "five     >  backDiff  : " << (five2 > back_diff) << std::endl
                  << "backDiff >  five      : " << (back_diff > back_diff) << std::endl;
        std::cout << std::boolalpha
                  << "empty    >= empty     : " << (empty1 >= empty2) << std::endl
                  << "empty    >= five      : " << (empty1 >= five1) << std::endl
                  << "five     >= empty     : " << (five1 >= empty1) << std::endl
                  << "five     >= five      : " << (five1 >= five2) << std::endl
                  << "six      >= five      : " << (six >= five1) << std::endl
                  << "five     >= six       : " << (five1 >= six) << std::endl
                  << "five     >= frontDiff : " << (five1 >= front_diff) << std::endl
                  << "frontDiff>= five      : " << (front_diff >= five1) << std::endl
                  << "five     >= backDiff  : " << (five2 >= back_diff) << std::endl
                  << "backDiff >= five      : " << (back_diff >= back_diff) << std::endl;
    }
};

#endif /* VECTORTESTER_HPP */
