
#ifndef TEST_BUFFER_H
#define TEST_BUFFER_H

#include <cxxtest/TestSuite.h>
#include <vector>
#include <climits>
#include <cfloat>
#include "paroc_buffer.h"
#include "paroc_buffer_raw.h"
#include "paroc_buffer_xdr.h"

template<typename T>void testByVect(paroc_buffer* xp_buffer, const std::vector<T>& x_vect){
    for(const auto& elem : x_vect)
    {
        // Pack/unpack each element of the vector
        T test;
        xp_buffer->Pack(&elem,1);
        xp_buffer->UnPack(&test,1);
        TS_ASSERT(elem == test);
    }

    // Pack/unpack the vector as a whole
    std::vector<T> vectTest;
    T test;
    vectTest.push_back(test); // to check that this gets deleted
    xp_buffer->Pack(&x_vect,1);
    xp_buffer->UnPack(&vectTest,1);

    TS_ASSERT(x_vect.size() == vectTest.size());
    auto it = vectTest.begin();
    for(const auto& elem : x_vect)
    {
        TS_ASSERT(elem == *it);
        it++;
    }
}

template<typename T>void testByType(paroc_buffer* xp_buffer, const T& x_min, const T& x_max, const T& x_incr){
    std::vector<T> vectTest;
    for(T elem = x_min ; elem < x_max ; elem += x_incr)
    {
        vectTest.push_back(elem);
    }
    testByVect<T>(xp_buffer, vectTest);
}

class BufferTestSuite : public CxxTest::TestSuite
{
    protected:
        paroc_buffer_raw*   m_bufferRaw;
        paroc_buffer_xdr*   m_bufferXdr;
        std::vector<bool>        m_vectBool;
        std::vector<std::string> m_vectString;
        std::vector<const char*> m_vectCharArr;

    public:
        void setUp()
        {
            m_bufferRaw = new paroc_buffer_raw();
            m_bufferXdr = new paroc_buffer_xdr();

            m_vectBool   = {0,1};
            m_vectString = {"Etenim si attendere diligenter, existimare vere de omni hac causa ",
            "volueritis, sic constituetis, iudices, nec descensurum quemquam ad hanc accusationem fuisse, cui, utrum vellet, liceret, nec, ",
            "cum descendisset, quicquam habiturum spei fuisse, nisi alicuius intolerabili libidine et nimis acerbo odio n",
            "iteretur. ",
            "Sed ego Atratino, humanissimo atque optimo adulescenti meo necessario, ignosco, qui habet excusationem vel pietatis vel necessitatis ",
            "vel aetatis. Si voluit accusare, pietati tribuo, si iussus est, necessitati, si speravit aliquid, pueritiae. Ceteris ",
            "non modo nihil ignoscendum, sed etiam acriter est resistendum."};

            for(const auto& elem : m_vectString)
                m_vectCharArr.push_back(elem.c_str());

        }
        void tearDown()
        {
            delete m_bufferRaw;
            delete m_bufferXdr;
        }

        // Test packing of data in buffer
        void testBuffer(paroc_buffer* xp_buffer){
            // testByType<short>(xp_buffer, 4, 59, 1);

            //return; // TODO
            TS_TRACE("pack int");
            int myint1 = 1000000000;
            int myint2 = 0;
            xp_buffer->Pack(&myint1,1);
            xp_buffer->UnPack(&myint2,1);
            TS_ASSERT(myint1 == myint2);

            TS_TRACE("test int");
            testByType<int>(xp_buffer, -INT_MAX, INT_MAX / 2, 23456999);
            TS_TRACE("test uint");
            testByType<unsigned int>(xp_buffer, 0, INT_MAX, 23456999);
            TS_TRACE("test long");
            testByType<long>(xp_buffer, -INT_MAX, INT_MAX / 2, 23456);
            TS_TRACE("test ulong");
            testByType<unsigned long>(xp_buffer, 0, INT_MAX, 23456);
            TS_TRACE("test short TODO fix");
            // testByType<short>(xp_buffer, -SHRT_MAX / 2, SHRT_MAX / 2, 23456);
            TS_TRACE("test ushort TODO fix");
            // testByType<unsigned short>(xp_buffer, 0, SHRT_MAX / 2, 26);
            TS_TRACE("test char");
            testByType<char>(xp_buffer, -127, 128, 1);
            TS_TRACE("test uchar");
            testByType<unsigned char>(xp_buffer, 0, 255, 1);

            TS_TRACE("test float");
            testByType<float>(xp_buffer, - 1e10, 1e10, 43e4);
            TS_TRACE("test double");
            testByType<double>(xp_buffer, - 1e15, 1e15, 43e8);



            // TS_TRACE("test bool");
            // testByVect<bool>(xp_buffer, m_vectBool);
            TS_TRACE("test string");
            testByVect<std::string>(xp_buffer, m_vectString);
            // TS_TRACE("test char array");
            // testByVect<const char*>(xp_buffer, m_vectCharArr);
        }

        void testBufferRaw(){
            TS_TRACE("Test buffer raw");
            testBuffer(m_bufferRaw);
        }

        void testBufferXdr(){
            TS_TRACE("Test buffer xdr");
            testBuffer(m_bufferXdr);
        }



/*
    virtual void Pack(const unsigned *data, int n)=0;
    virtual void UnPack(unsigned *data, int n)=0;

    virtual void Pack(const long *data, int n)=0;
    virtual void UnPack(long *data, int n)=0;

    virtual void Pack(const unsigned long *data, int n)=0;
    virtual void UnPack(unsigned long *data, int n)=0;

    virtual void Pack(const short *data, int n)=0;
    virtual void UnPack(short *data, int n)=0;
    */
};

#endif
