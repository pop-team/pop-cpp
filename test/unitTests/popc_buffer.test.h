
#ifndef TEST_BUFFER_H
#define TEST_BUFFER_H

#include <cxxtest/TestSuite.h>
#include <vector>
#include <climits>
#include <cfloat>
#include "paroc_buffer.h"
#include "paroc_buffer_raw.h"
#include "paroc_buffer_xdr.h"
#include "paroc_combox_factory.h"
#include "paroc_exception.h"

#define ITER 100

// Note: XDR only supports these limits (8 bytes long)
#define _LONG_MAX     2147483647L
#define _LONG_MIN      (-_LONG_MAX - 1L)
#define _ULONG_MAX    4294967295UL

// TODO: See if we keep the combox test here (and fix)

/// Test the serialization of all values in vector
template<typename T>void testByVect(paroc_buffer* xp_bufferOut, paroc_combox* xp_comboxOut, paroc_connection* xp_connectionOut, 
                                    paroc_buffer* xp_bufferIn,  paroc_combox* xp_comboxIn,  paroc_connection* xp_connectionIn, const std::vector<T>& x_vect, bool x_testArray){

    for(const auto& elem : x_vect)
    {
        // Pack/unpack each element of the vector
        T test;
        xp_bufferOut->Pack(&elem,1);
        if(xp_bufferOut != xp_bufferIn){
            xp_bufferOut->Send(*xp_comboxOut, xp_connectionOut);
            std::cout<<__LINE__<<std::endl;
            xp_bufferIn->Recv(*xp_comboxIn, xp_connectionIn);
            std::cout<<__LINE__<<std::endl;
        }
        xp_bufferIn->UnPack(&test,1);
        // std::cout<<elem<<" == "<<test<<std::endl;
        TS_ASSERT(elem == test);
    }

    // Pack/unpack the vector as a whole
    std::vector<T> vectTest;
    T test;
    vectTest.push_back(test); // to check that this gets deleted
    xp_bufferOut->Pack(&x_vect,1);
    xp_bufferIn->UnPack(&vectTest,1);

    TS_ASSERT(x_vect.size() == vectTest.size());
    auto it = vectTest.begin();
    for(const auto& elem : x_vect)
    {
        TS_ASSERT(elem == *it);
        it++;
    }


    if(x_testArray)
    {
        // Test with old-school arrays
        T* arr1 = static_cast<T*>(malloc(x_vect.size() * sizeof(T)));
        T* arr2 = static_cast<T*>(malloc(x_vect.size() * sizeof(T)));
        T* parr = arr1;
        for(const auto& elem : x_vect)
        {
            *parr = elem;
            parr++;
        }
        xp_bufferOut->Pack(arr1,x_vect.size());
        xp_bufferIn->UnPack(arr2,x_vect.size());
        free(arr1);
        free(arr2);
    }
}

/// Fill a vector and test
template<typename T>void testByType(paroc_buffer* xp_bufferOut, paroc_combox* xp_comboxOut, paroc_connection* xp_connectionOut, 
                                    paroc_buffer* xp_bufferIn,  paroc_combox* xp_comboxIn,  paroc_connection* xp_connectionIn, const T& x_min, const T& x_max, const T& x_incr){
    std::vector<T> vectTest;
    for(T elem = x_min ; elem < x_max - 2 * x_incr ; elem += x_incr) // this break condition avoids inf loops due to overflows
    {
        vectTest.push_back(elem);
    }
    testByVect<T>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, vectTest, true);
}

class BufferTestSuite : public CxxTest::TestSuite
{
    protected:
        paroc_buffer_raw*   m_bufferRaw;
        paroc_buffer_xdr*   m_bufferXdr;
        paroc_combox*       m_comboxSocketOut;
        paroc_combox*       m_comboxSocketIn;
        paroc_connection*   m_connectionSocket;
        std::vector<bool>        m_vectBool;
        std::vector<std::string> m_vectString;
        std::vector<const char*> m_vectCharArr;

    public:
        void setUp()
        {
            m_bufferRaw = new paroc_buffer_raw();
            m_bufferXdr = new paroc_buffer_xdr();

            m_vectBool   = {0,1,1,0,1,1,1,1,0,0,1};
            m_vectString = {"Etenim si attendere diligenter, existimare vere de omni hac causa ",
            "volueritis, sic constituetis, iudices, nec descensurum quemquam ad hanc accusationem fuisse, cui, utrum vellet, liceret, nec, ",
            "cum descendisset, quicquam habiturum spei fuisse, nisi alicuius intolerabili libidine et nimis acerbo odio n",
            "iteretur. ",
            "éajkdf+°&%&}{\n\n\rasdfjéasdf */$£äàààöällélk",
            "' !\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~'",
            "Sed ego Atratino, humanissimo atque optimo adulescenti meo necessario, ignosco, qui habet excusationem vel pietatis vel necessitatis ",
            "vel aetatis. Si voluit accusare, pietati tribuo, si iussus est, necessitati, si speravit aliquid, pueritiae. Ceteris ",
            "non modo nihil ignoscendum, sed etiam acriter est resistendum."};

            for(const auto& elem : m_vectString)
                m_vectCharArr.push_back(elem.c_str());

            // Create combox factory
            paroc_combox_factory *fact = paroc_combox_factory::GetInstance();
            TS_ASSERT(fact != nullptr);

            // Create combox
            m_comboxSocketOut = fact->Create("socket");
            TS_ASSERT(m_comboxSocketOut != nullptr);
            m_comboxSocketIn = fact->Create("socket");
            TS_ASSERT(m_comboxSocketIn != nullptr);
            //delete fact; // TODO LW: GetInstance must return a reference not a pointer

            m_connectionSocket = m_comboxSocketOut->get_connection();
        }
        void tearDown()
        {
            delete m_bufferRaw;
            delete m_bufferXdr;
            delete m_comboxSocketOut;
            delete m_comboxSocketIn;
        }

        // Test packing of data in buffer
        void testBuffer(paroc_buffer* xp_bufferOut,  paroc_combox* xp_comboxOut, paroc_connection* xp_connectionOut,
                        paroc_buffer* xp_bufferIn,   paroc_combox* xp_comboxIn,  paroc_connection* xp_connectionIn){


            TS_TRACE("test int");
            testByType<int>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, INT_MIN, INT_MAX, INT_MAX / ITER);
            TS_TRACE("test uint");
            testByType<unsigned int>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, 0, UINT_MAX, UINT_MAX / ITER);
            TS_TRACE("test long");
            testByType<long>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, _LONG_MIN, _LONG_MAX, _LONG_MAX / ITER);
            TS_TRACE("test ulong");
            testByType<unsigned long>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, 0, _ULONG_MAX, _ULONG_MAX / ITER);
            TS_TRACE("test short");
            testByType<short>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, SHRT_MIN, SHRT_MAX, SHRT_MAX / ITER);
            TS_TRACE("test ushort");
            testByType<unsigned short>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, 0, USHRT_MAX, USHRT_MAX / ITER);
            TS_TRACE("test char");
            testByType<char>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, -127, 128, 1);
            TS_TRACE("test uchar");
            testByType<unsigned char>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, 0, 255, 1);

            TS_TRACE("test float");
            testByType<float>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, - 1e10, 1e10, 43e4);
            TS_TRACE("test double");
            testByType<double>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, - 1e15, 1e15, 43e8);



            // TS_TRACE("test bool");
            // testByVect<bool>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, m_vectBool, true);
            TS_TRACE("test string");
            testByVect<std::string>(xp_bufferOut, xp_comboxOut, xp_connectionOut, xp_bufferIn, xp_comboxIn, xp_connectionIn, m_vectString, false);
        }

        void testBufferRaw(){
            // Test: pack/unpack in the same buffer
            TS_TRACE("Test buffer raw");
            testBuffer(m_bufferRaw, m_comboxSocketOut, m_connectionSocket, m_bufferRaw, NULL, NULL);


            // Test: pack/unpack in a different buffer
            /* TODO
            TS_TRACE("Test pack/unpack in a different buffer");

            TS_ASSERT(m_comboxSocketOut->Create(12345, true)); // port, server
            TS_ASSERT(m_comboxSocketIn->Create(12349, false)); // port, server
            TS_ASSERT(m_comboxSocketIn->Connect("socket://localhost:12345"));

            paroc_buffer& bufIn(*m_comboxSocketIn->GetBufferFactory()->CreateBuffer());
            paroc_buffer& bufOut(*m_comboxSocketOut->GetBufferFactory()->CreateBuffer());
            paroc_connection& connOut(*m_comboxSocketOut->get_connection());
            paroc_connection& connIn(*m_comboxSocketIn->get_connection());
            // testBuffer(&bufOut, m_comboxSocketOut, &connOut, &bufIn, m_comboxSocketIn, &connIn);
            testBuffer(&bufIn, m_comboxSocketIn, &connIn, &bufOut, m_comboxSocketOut, &connOut);
            */
        }

        void testBufferXdr(){
            TS_TRACE("Test buffer xdr");
            testBuffer(m_bufferXdr, m_comboxSocketOut, m_connectionSocket, m_bufferXdr, NULL, NULL);
        }
};

#endif
