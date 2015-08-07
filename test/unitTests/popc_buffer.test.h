
#ifndef TEST_BUFFER_H
#define TEST_BUFFER_H

#include <cxxtest/TestSuite.h>
#include <vector>
#include <climits>
#include <cfloat>
#include "pop_buffer.h"
#include "pop_buffer_raw.h"
#include "pop_buffer_xdr.h"
#include "pop_exception.h"

#define ITER 100

// Note: XDR only supports (8 bytes long) and for compatibility with 32 bits we use (4 bytes long)
#define _LONG_MAX 2147483647L
#define _LONG_MIN -2147483648L
#define _ULONG_MAX 4294967295UL

/// Test the serialization of all values in vector
template <typename T>
void testByVect(pop_buffer* xp_bufferOut, pop_buffer* xp_bufferIn, const std::vector<T>& x_vect, bool x_testArray) {
    for (const auto& elem : x_vect) {
        // Pack/unpack each element of the vector
        T test;
        xp_bufferOut->Pack(&elem, 1);
        xp_bufferIn->UnPack(&test, 1);
        // std::cout<<elem<<" == "<<test<<std::endl;
        TS_ASSERT(elem == test);
    }

    // Pack/unpack the vector as a whole
    std::vector<T> vectTest;
    T test;
    vectTest.push_back(test);  // to check that this gets deleted
    xp_bufferOut->Pack(&x_vect, 1);
    xp_bufferIn->UnPack(&vectTest, 1);

    TS_ASSERT(!x_vect.empty());  // check if a problem occured while serializing size
    TS_ASSERT(x_vect.size() == vectTest.size());
    auto it = vectTest.begin();
    for (const auto& elem : x_vect) {
        TS_ASSERT(elem == *it);
        it++;
    }

    if (x_testArray) {
        // Test with old-school arrays
        T* arr1 = static_cast<T*>(malloc(x_vect.size() * sizeof(T)));
        T* arr2 = static_cast<T*>(malloc(x_vect.size() * sizeof(T)));
        T* parr = arr1;
        for (const auto& elem : x_vect) {
            *parr = elem;
            parr++;
        }
        xp_bufferOut->Pack(arr1, x_vect.size());
        xp_bufferIn->UnPack(arr2, x_vect.size());
        free(arr1);
        free(arr2);
    }
}

/// Fill a vector and test
template <typename T>
void testByType(pop_buffer* xp_bufferOut, pop_buffer* xp_bufferIn, const T& x_min, const T& x_max, const T& x_incr) {
    std::vector<T> vectTest;
    for (T elem = x_min; elem < x_max - x_incr;
         elem += x_incr)  // this break condition avoids inf loops due to overflows
    {
        xp_bufferOut->Pack(&elem, 1);
        T tmp;
        std::cout << tmp << std::endl;
        xp_bufferIn->UnPack(&tmp, 1);
        TS_ASSERT(elem == tmp);

        vectTest.push_back(elem);
    }
    testByVect<T>(xp_bufferOut, xp_bufferIn, vectTest, true);
}

class BufferTestSuite : public CxxTest::TestSuite {
protected:
    pop_buffer_raw* m_bufferRaw;
    pop_buffer_xdr* m_bufferXdr;
    std::vector<bool> m_vectBool;
    std::vector<std::string> m_vectString;
    std::vector<const char*> m_vectCharArr;

public:
    void setUp() {
        m_bufferRaw = new pop_buffer_raw();
        m_bufferXdr = new pop_buffer_xdr();

        m_vectBool = {0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1};
        m_vectString = {
            "Etenim si attendere diligenter, existimare vere de omni hac causa ",
            "volueritis, sic constituetis, iudices, nec descensurum quemquam ad hanc accusationem fuisse, cui, utrum "
            "vellet, liceret, nec, ",
            "cum descendisset, quicquam habiturum spei fuisse, nisi alicuius intolerabili libidine et nimis acerbo "
            "odio n",
            "iteretur. ", "éajkdf+°&%&}{\n\n\rasdfjéasdf */$£äàààöällélk",
            "' !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~'",
            "Sed ego Atratino, humanissimo atque optimo adulescenti meo necessario, ignosco, qui habet excusationem "
            "vel pietatis vel necessitatis ",
            "vel aetatis. Si voluit accusare, pietati tribuo, si iussus est, necessitati, si speravit aliquid, "
            "pueritiae. Ceteris ",
            "non modo nihil ignoscendum, sed etiam acriter est resistendum."};

        for (const auto& elem : m_vectString)
            m_vectCharArr.push_back(elem.c_str());
    }
    void tearDown() {
        delete m_bufferRaw;
        delete m_bufferXdr;
    }

    // Test packing of data in buffer
    void testBuffer(pop_buffer* xp_bufferOut, pop_buffer* xp_bufferIn) {
        TS_TRACE("test int");
        testByType<int>(xp_bufferOut, xp_bufferIn, INT_MIN, INT_MAX, INT_MAX / ITER);
        TS_TRACE("test uint");
        testByType<unsigned int>(xp_bufferOut, xp_bufferIn, 0, UINT_MAX, UINT_MAX / ITER);
        TS_TRACE("test long");
        testByType<long>(xp_bufferOut, xp_bufferIn, _LONG_MIN, _LONG_MAX, _LONG_MAX / ITER);
        TS_TRACE("test ulong");
        testByType<unsigned long>(xp_bufferOut, xp_bufferIn, 0, _ULONG_MAX, _ULONG_MAX / ITER);
        TS_TRACE("test short");
        testByType<short>(xp_bufferOut, xp_bufferIn, SHRT_MIN, SHRT_MAX, SHRT_MAX / ITER);
        TS_TRACE("test ushort");
        testByType<unsigned short>(xp_bufferOut, xp_bufferIn, 0, USHRT_MAX, USHRT_MAX / ITER);
        TS_TRACE("test char");
        testByType<signed char>(xp_bufferOut, xp_bufferIn, -128, 127, 1);
        TS_TRACE("test uchar");
        testByType<unsigned char>(xp_bufferOut, xp_bufferIn, 0, 255, 1);

        TS_TRACE("test float");
        testByType<float>(xp_bufferOut, xp_bufferIn, -1e10, 1e10, 43e5);
        TS_TRACE("test double");
        testByType<double>(xp_bufferOut, xp_bufferIn, -1e15, 1e15, 43e9);

        TS_TRACE("test string");
        testByVect<std::string>(xp_bufferOut, xp_bufferIn, m_vectString, false);

        TS_TRACE("test bool");
        // testByVect<bool>(xp_bufferOut, xp_bufferIn,
        // m_vectBool, true);
        for (const auto& elem : m_vectBool) {
            // Pack/unpack each element of the vector
            // http://stackoverflow.com/questions/17794569/why-is-vectorbool-not-a-stl-container
            bool orig = elem;
            bool test;
            xp_bufferOut->Pack(&orig, 1);
            xp_bufferIn->UnPack(&test, 1);
            TS_ASSERT(elem == test);
        }
    }

    void testBufferRaw() {
        // Test: pack/unpack in the same buffer
        TS_TRACE("Test buffer raw");
        testBuffer(m_bufferRaw, m_bufferRaw);
    }

    void testBufferXdr() {
        TS_TRACE("Test buffer xdr");
        testBuffer(m_bufferXdr, m_bufferXdr);
    }
};

#endif
