#ifndef _POPDATA_H
#define _POPDATA_H

class POPData : public POPBase {
public:
    POPData();
    ~POPData();

    //
    void setIntData(int value);
    void setFloatData(float value);

    int getIntData();
    float getFloatData();

    // Inherited from POPBase
    virtual void Serialize(POPBuffer& buf, bool pack);

private:
    int intdata;
    float floatdata;
};
#endif /* _POPDATA_H */
