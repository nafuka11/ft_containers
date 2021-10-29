#ifndef VECTORBENCHMARK_HPP
#define VECTORBENCHMARK_HPP

class VectorBenchmark
{
public:
    VectorBenchmark();
    void test_all();
private:
    static const int loop_count;
    Timer timer;

    void test_clear();
    void test_insert();
    void test_erase();
    void test_push_back();
    void test_pop_back();
};

#endif /* VECTORBENCHMARK_HPP */
