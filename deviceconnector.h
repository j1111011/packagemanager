#ifndef DEVICECONNECTOR_H
#define DEVICECONNECTOR_H

class Device;
class DeviceConnector
{
public:
    enum DeviceType
    {
        AndroidByAdb,
        AndroidByNetwork,
        iPhoneByiDevice
    };
    DeviceConnector();
    static Device* create(DeviceType type);
};

#endif // DEVICECONNECTOR_H
