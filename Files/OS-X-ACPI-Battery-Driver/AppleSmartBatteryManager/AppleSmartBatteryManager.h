/*
 * Copyright (c) 2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef __AppleSmartBatteryManager__
#define __AppleSmartBatteryManager__

#define EXPORT __attribute__((visibility("default")))


#define AppleSmartBatteryManager AppleSmartBatteryManager // was rehab_ACPIBatteryManager
#define AppleSmartBattery AppleSmartBattery // was rehab_ACPIBattery
#define ACPIACAdapter ACPIACAdapter // was rehab_ACPIACAdapter

#include <IOKit/IOService.h>
#include <IOKit/acpi/IOACPIPlatformDevice.h>

#include <libkern/version.h>
#define MakeKernelVersion(maj,min,rev) (static_cast<uint32_t>((maj)<<16)|static_cast<uint16_t>((min)<<8)|static_cast<uint8_t>(rev))
#define RunningKernel() MakeKernelVersion(version_major,version_minor,version_revision)


#include "AppleSmartBattery.h"

#ifdef DEBUG_MSG
#define DebugLog(args...)  do { IOLog("ACPIBatteryManager: " args); } while (0)
#define DebugOnly(expr)     do { expr; } while (0)
#else
#define DebugLog(args...)  do { } while (0)
#define DebugOnly(expr)    do { } while (0)
#endif

#define AlwaysLog(args...) do { IOLog("ACPIBatteryManager: " args); } while (0)

class AppleSmartBattery;
class BatteryTracker;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class EXPORT AppleSmartBatteryManager : public IOService
{
    typedef IOService super;
	OSDeclareDefaultStructors(AppleSmartBatteryManager)
    friend class BatteryTracker;

public:
#ifdef DEBUG
	virtual bool init(OSDictionary *dictionary = 0);
    virtual void free(void);
    virtual IOService *probe(IOService *provider, SInt32 *score);
#endif
    bool start(IOService *provider);
	void stop(IOService *provider);

    IOReturn setPowerState(unsigned long which, IOService *whom);
    IOReturn message(UInt32 type, IOService *provider, void *argument);
    
    bool                    areBatteriesDischarging(AppleSmartBattery * except);

private:
	
    IOCommandGate           *fBatteryGate;
	IOACPIPlatformDevice    *fProvider;
	AppleSmartBattery       *fBattery;
    UInt32                  fBatterySTA;

	IOReturn setPollingInterval(int milliSeconds);
    
    IONotifier*             fPublishNotify;
    IONotifier*             fTerminateNotify;
    
    OSSet*                  fBatteryServices;
    
    void                    gatedHandler(IOService* newService, IONotifier * notifier);
    bool                    notificationHandler(void * refCon, IOService * newService, IONotifier * notifier);

public:
    OSDictionary* getConfigurationOverride(const char* method);
private:
    OSObject* translateArray(OSArray* array);
    OSObject* translateEntry(OSObject* obj);

public:
	
    // Methods that return ACPI data into above structures
    
	IOReturn getBatterySTA(void);
	IOReturn getBatteryBIF(void);
	IOReturn getBatteryBIX(void);
	IOReturn getBatteryBBIX(void);
	IOReturn getBatteryBST(void);
    
    // Methods to test whether optional ACPI methods exist
    
    IOReturn validateBatteryBIX(void);
    IOReturn validateBatteryBBIX(void);
};

#endif
