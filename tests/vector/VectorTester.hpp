#ifndef VECTORTESTER_HPP
#define VECTORTESTER_HPP

#include <iostream>
#include "common.hpp"

template <class T>
class VectorTester
{
public:
    VectorTester(ft::vector<T> &vec): originalVec(vec) {}
    ~VectorTester() {}
    void test_all()
    {
        test_constructor();
        test_max_size();
        test_empty();
        test_reserve();
        test_subscript_operator();
        test_at();
        test_front_back();
        test_assign();
        test_push_back();
        test_pop_back();
        test_insert();
        test_erase();
        test_swap();
        test_clear();
    }

private:
    ft::vector<T> originalVec;

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
        std::cout << "size()=" << vec.size() << " capacity()=" << vec.capacity() << std::endl;
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
            ft::vector<T> vec(10, *originalVec.begin());
            std::cout << "vector(10, " << *originalVec.begin() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(originalVec.begin(), originalVec.end());
            std::cout << "vector(begin, end): ";
            print_vector_info(vec);
            print_vector_elements(vec);
        }
        {
            ft::vector<T> vec(originalVec);
            print_vector(vec, "vector(otherVec)");
        }
    }

    void test_max_size()
    {
        print_test_case("vector::max_size()");
        ft::vector<T> vec;
        std::cout << vec.max_size() << std::endl;
    }

    void test_empty()
    {
        print_test_case("vector::empty()");
        ft::vector<T> vecEmpty;
        std::cout << std::boolalpha << "vector().empty()=" << vecEmpty.empty() << std::endl;
        ft::vector<T> vecOne(1);
        std::cout << std::boolalpha << "vector(1).empty()=" << vecOne.empty() << std::endl;
    }

    void test_reserve()
    {
        print_test_case("vector::reserve()");
        {
            ft::vector<T> vec = originalVec;
            std::cout << "vec.reserve(" << originalVec.size() - 1 << "): ";
            vec.reserve(originalVec.size() - 1);
            print_vector(vec);
        }
        {
            ft::vector<T> vec = originalVec;
            std::cout << "vec.reserve(" << originalVec.size() + 1 << "): ";
            vec.reserve(originalVec.size() + 1);
            print_vector(vec);
        }
        {
            ft::vector<T> vec;
            vec.reserve(42);
            print_vector(vec, "vector().reserve(42)");
        }
        {
            ft::vector<T> vec = originalVec;
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
        for (size_t i = 0; i < originalVec.size(); i++)
        {
            std::cout << "vec[" << i << "]=" << originalVec[i] << " ";
        }
        std::cout << std::endl;
    }

    void test_at()
    {
        print_test_case("vector::at()");
        for (size_t i = 0; i < originalVec.size() + 1; i++)
        {
            try
            {
                std::cout << "vec.at(" << i << ")=";
                std::cout << originalVec.at(i) << " ";
            }
            catch(const std::out_of_range &e)
            {
                std::cout << e.what() << " ";
            }
        }
        std::cout << std::endl;
    }

    void test_front_back()
    {
        print_test_case("vector::front(), back()");
        std::cout << "vec.front()=" << originalVec.front() << std::endl;
        std::cout << "vec.back() =" << originalVec.back() << std::endl;
    }

    void test_assign()
    {
        print_test_case("vector::assign()");
        test_assign_range(originalVec.begin(), originalVec.end());
        test_assign_range(originalVec.begin(), originalVec.begin());
        test_assign_range(originalVec.begin(), originalVec.end()-1);
        test_assign_fill(0);
        test_assign_fill(2);
        test_assign_fill(5);
        test_assign_fill(10);
    }

    template <class InputIterator>
    void test_assign_range(InputIterator first, InputIterator last)
    {
        ft::vector<T> vec(originalVec.size());
        std::cout << "vec.assign(first=iter(" << (*first) << "), iter(first+" << last - first << ")): ";
        vec.assign(first, last);
        print_vector(vec);
    }

    void test_assign_fill(typename ft::vector<T>::size_type count)
    {
        ft::vector<T> vec = originalVec;
        std::cout << "vec.assign(" << count << ", " << vec.back() << "): ";
        vec.assign(count, vec.back());
        print_vector(vec);
    }

    void test_push_back()
    {
        print_test_case("vector::push_back()");
        ft::vector<T> vec;
        print_vector(vec);
        for (size_t i = 0; i < originalVec.size(); i++)
        {
            vec.push_back(originalVec[i]);
            print_vector(vec);
        }
    }

    void test_pop_back()
    {
        print_test_case("vector::pop_back()");
        ft::vector<T> vec = originalVec;
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
            ft::vector<T> vec(5, 42);
            vec.insert(vec.begin() + 2, originalVec.front());
            std::cout << "vector(5, 42).insert(begin()+2, " << originalVec.front() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec;
            vec.insert(vec.begin(), originalVec.front());
            std::cout << "vector().insert(begin(), " << originalVec.front() << "): ";
            print_vector(vec);
        }
    }

    void test_insert_fill()
    {
        {
            ft::vector<T> vec(5, 42);
            vec.insert(vec.begin(), 5, originalVec.back());
            std::cout << "vector(5, 42).insert(begin(), 5, " << originalVec.back() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, 42);
            vec.insert(vec.begin() + 1, 5, originalVec.back());
            std::cout << "vector(5, 42).insert(begin()+1, 5, " << originalVec.back() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, 42);
            vec.insert(vec.end() - 1, 5, originalVec.front());
            std::cout << "vec.insert(end()-1, 5, " << originalVec.front() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec(5, 42);
            vec.insert(vec.end(), 5, originalVec.front());
            std::cout << "vector(5, 42).insert(end(), 5, " << originalVec.front() << "): ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec;
            vec.insert(vec.begin(), 5, originalVec.front());
            std::cout << "vector().insert(end(), 5, " << originalVec.front() << "): ";
            print_vector(vec);
        }
    }

    void test_insert_range()
    {
        {
            ft::vector<T> vec(5, 42);
            vec.insert(vec.begin(), originalVec.begin(), originalVec.end());
            print_vector(vec, "vector(5, 42).insert(begin(), origVec.begin(), origVec.end())");
        }
        {
            ft::vector<T> vec(5, 42);
            vec.insert(vec.begin() + 1, originalVec.begin(), originalVec.end());
            print_vector(vec, "vector(5, 42).insert(begin()+1, origVec.begin(), origVec.end())");
        }
        {
            ft::vector<T> vec(5, 42);
            vec.insert(vec.end() - 1, originalVec.begin(), originalVec.end());
            print_vector(vec, "vector(5, 42).insert(end()-1, origVec.begin(), origVec.end())");
        }
        {
            ft::vector<T> vec(5, 42);
            vec.insert(vec.end(), originalVec.begin(), originalVec.end());
            print_vector(vec, "vector(5, 42).insert(end(), origVec.begin(), origVec.end())");
        }
        {
            ft::vector<T> vec;
            vec.insert(vec.begin(), originalVec.begin(), originalVec.end());
            print_vector(vec, "vector().insert(begin(), origVec.begin(), origVec.end())");
        }
    }

    void test_erase()
    {
        print_test_case("vector::erase()");
        test_erase_one();
        test_erase_range();
    }

    void test_erase_one()
    {
        for (size_t i = 0; i < originalVec.size(); i++)
        {
            ft::vector<T> vec = originalVec;
            std::cout << "vec.erase(" << *(vec.begin() + i) << "): ";
            std::cout << "result=iter(begin()+" << (vec.erase(vec.begin() + i) - vec.begin()) << ") ";
            print_vector(vec);
        }
    }

    void test_erase_range()
    {
        {
            ft::vector<T> vec = originalVec;
            typename ft::vector<T>::iterator first = vec.begin();
            typename ft::vector<T>::iterator last = vec.end();
            std::cout << "vec.erase(first=iter(" << *first << "), iter(first+" << last - first << ")): ";
            std::cout << "result=iter(begin()+" << (vec.erase(first, last) - vec.begin()) << ") ";
            print_vector(vec);
        }
        {
            ft::vector<T> vec = originalVec;
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
            ft::vector<T> vec1(4, originalVec.front());
            ft::vector<T> vec2(2, originalVec.back());
            print_vector(vec1, "orig vec1    ");
            print_vector(vec2, "orig vec2    ");
            vec1.swap(vec2);
            print_vector(vec1, "swapped vec1");
            print_vector(vec2, "swapped vec2");
        }
        {
            ft::vector<T> vec1(4, originalVec.front());
            ft::vector<T> vec2(2, originalVec.back());
            print_vector(vec1, "orig vec1    ");
            print_vector(vec2, "orig vec2    ");
            ft::swap(vec1, vec2);
            print_vector(vec1, "swapped vec1");
            print_vector(vec2, "swapped vec2");
        }
    }

    void test_clear()
    {
        print_test_case("vector::clear()");
        ft::vector<T> vec = originalVec;
        vec.clear();
        print_vector_info(vec);
    }
};

#endif /* VECTORTESTER_HPP */
