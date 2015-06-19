parclass TestMethod {
public:
    TestMethod()@{od.url("localhost");};

    seq void TestSeq1(std::string test);
    seq void TestSeq2(std::string& test);
    seq std::string TestSeq3();

    classuid(1001);
};
