//
//  ACAdapter.h
//  ACPIBatteryManager
//
//  Created by RehabMan on 11/16/13.
//
//

#ifndef ACPIBatteryManager_ACAdapter_h
#define ACPIBatteryManager_ACAdapter_h

#include "AppleSmartBatteryManager.h"

class EXPORT ACPIACAdapter : public IOService
{
    OSDeclareDefaultStructors(ACPIACAdapter)
    
private:
    IOACPIPlatformDevice*   fProvider;
    IOWorkLoop*             fWorkloop;
    IOCommandGate*          fCommandGate;
    IORecursiveLock*        fLock;
    
    IONotifier*             fPublishNotify;
    IONotifier*             fTerminateNotify;
    
    OSSet*                  fBatteryServices;
    
    bool                    fACConnected;

    void                    gatedHandler(IOService* newService, IONotifier * notifier);
    bool                    notificationHandler(void * refCon, IOService * newService, IONotifier * notifier);
    void                    pollState();
public:
    virtual bool            init(OSDictionary* dict);
    virtual bool            start(IOService* provider);
    virtual void            stop(IOService* provider);
    virtual IOReturn        setPowerState(unsigned long state, IOService* device);
    virtual IOReturn        message(UInt32 type, IOService* provider, void* argument);
};

#endif
