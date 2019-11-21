#include "deviceconnector.h"
#include "adbdevice.h"

DeviceConnector::DeviceConnector()
{

}

Device *DeviceConnector::create(DeviceConnector::DeviceType type)
{
    Device* device;
    switch (type) {
    case AndroidByAdb:
        device = new AdbDevice();
        break;
    case AndroidByNetwork:

        break;
    case iPhoneByiDevice:

        break;
    default:
        break;
    }
    return device;
}
