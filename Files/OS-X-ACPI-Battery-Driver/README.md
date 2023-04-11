## ACPIBatteryManager by RehabMan


### How to Install:

Install the kext using your favorite kext installer utility, such as Kext Wizard.  The Debug director is for troubleshooting only, in normal "working" installs, you should install the Release version.

Please read this post if you need to make DSDT edits: http://www.tonymacx86.com/mavericks-laptop-support/116102-how-patch-dsdt-working-battery-status.html


### Downloads:

Downloads are available on Bitbucket:

https://bitbucket.org/RehabMan/os-x-acpi-battery-driver/downloads/


Archived builds are available on Google Code:

https://code.google.com/p/os-x-acpi-battery-driver/downloads/list


### Build Environment

My build environment is currently Xcode 7.3, using SDK 10.8, targeting OS X 10.6.

No other build environment is supported.


### 32-bit Builds

Currently, builds are provided only for 64-bit systems.  32-bit/64-bit FAT binaries are not provided.  But you can build your own should you need them.  I do not test 32-bit, and there may be times when the repo is broken with respect to 32-bit builds, but I do check on major releases to see if the build still works for 32-bit.

Here's how to build 32-bit (universal):

- xcode 4.6.3
- open ACPIBatteryManager.xcodeproj
- click on ACPIBatteryManager at the top of the project tree
- select ACPIBatteryManager under Project
- change Architectures to 'Standard (32/64-bit Intel)'

probably not necessary, but a good idea to check that the targets don't have overrides:
- multi-select all the Targets
- check/change Architectures to 'Standard (32/64-bit Intel)'
- build (either w/ menu or with make)

Or, if you have the command line tools installed, just run:

- For FAT binary (32-bit and 64-bit in one binary)
make BITS=3264

- For 32-bit only
make BITS=32


### Source Code:

The source code is maintained at the following sites:

https://github.com/RehabMan/OS-X-ACPI-Battery-Driver

https://bitbucket.org/RehabMan/os-x-acpi-battery-driver


### Feedback:

Please use this thread on tonymacx86.com for feedback, questions, and help:

http://www.tonymacx86.com/hp-probook/69472-battery-manager-fix-boot-without-batteries.html


### Known issues:

- Most DSDTs need to be patched in order to work properly with OS X.

- OS X does not deal well with dual-batteries: Consider SSDT-BATC, which will combine two batteries to a single battery.


### Change Log:

2018-10-5 v1.90.1

- fix a crash in ACPIBatteryManager due to notifications received very early in startup (may be in invalid configurations)


2018-09-15 v1.90

- merge 'refactor' branch from the-darkvoid (details below)

- removed BatteryTracker and allow existing services to communicate directly

- drive AC status purely through ACPIACAdapter, not through battery charging/discharging status


2017-10-01 v1.81.4

- add kernel flag "abm_firstpolldelay" to allow override of FirstPollDelay with simple kernel flag entry (config.plist/Boot/Arguments).  For example, to set FirstPollDelay to 16000 (16 seconds), use abm_firstpolldelay=16000


2017-09-01 v1.81.3

- Revert more 10.13 changes when running 10.12 and earlier (runtime checks). These changes are an attempt to solve issue #22


2017-08-30 v1.81.2

- Revert some of the 10.13 changes for 10.12 and earlier (runtime checks)


2017-08-30 v1.81.1 (removed from bitbucket)

- Change FirstPollDelay to 4000


2017-08-29 v1.81

- More experiments for 10.13 and the startup problem.

- Now we wait for AppleSMC to load before ACPIBatteryManager starts.  This provides a better "anchor" for the FirstPollDelay wait.

- FirstPollDelay now 1000.  Tested on my 4530s (HDD, Sandy Bridge Core i3).  It works with 500 (and with other larger values), but fails and 250.  Decided to try 1000 as a default.

- Avoid a problem where power management registration caues an early (but not real early) call to setPowerState which was triggering a pollBatteryState prior to the delay specified by FirstPollDelay.


2017-08-28 v1.80

- Fix problem of losing battery icon on 10.13 High Sierra beta.  It is a new timing bug introduced in High Sierra.  Delaying the first poll and battery status publish fixes it.  StartupDelay configuration is removed (not used, has no effect if specified in ACPI override).  New configuration item FirstPollDelay is default at 7500.  Slower computers may need a longer delay (for my Lenovo u430, 3500 is too short, 4000 is long enough).


2017-08-26 v1.71

- Fix problem with Activity Monitor "Energy" tab, by changing class names to AppleSmartBatteryManager and AppleSmartBattery


2017-04-28 v1.70.3

- Add quick polling for the first 10 seconds of startup for the case the EC/ACPI does not respond correctly at startup.  This quick poll will be cancelled once a battery status is succesfully acquired, or after the 10 seconds.


2016-11-18 v1.70.2

- Fix problem where incorrect _BST code returns status of "discharging" when at full charge, AC adapter still plugged in.


2016-06-28 v1.70.1

- Fix bug involving BatterySerialNumber (always showing -Unknown)

- Handle ACPI returning a blank string for serial# in _BIF (use "Unknown" in that case)

- no longer setting Temperature when it is not available from ACPI

- misc cleanup


2016-05-31 v1.70.0

- added SSDT-BATC.dsl which allows multiple batteries to be dealt with as a single ACPI battery

- changed the code that responds to battery notifications so it is not sensitive to incorrect remove/add flags

- misc cleanup


2015-12-30 v1.60.5

- Fixed bug with zero length dictionary (ACPI-based configuration)

- correct capacities only if non-zero

- change StartupDelay to 0ms


2015-11-09 v1.60.4

- added configurable StartupDelay

- changed default StartupDelay from 500ms to 50ms


2015-10-29 v1.60.3

- Add correction for capacities that don't conform to OS X expectations (CurrentCapacity<=MaxCapacity<=DesignCapacity)'


2015-09-30 v1.60

- Add CurrentDischargeRateMax configuration key as a way to cap the discharge rate against bad data from ACPI _BST

- Add ACPI method for overriding configuration data in Info.plist.  See config_override.txt for more info


2015-01-23 v1.55

- Add 500ms delay before polling initial battery state (_STA) to account for battery devices at are not ready early in the boot process.  This avoids dimming the display when booting on battery, as the system doesn't detect it as a battery present->battery removed transition.

- some minor fixes for watts when CurrentRate is ACPI_UNKNOWN

- debug messages are now in decimal


2014-10-16 v1.53

- added debug output for _BIX


2014-02-07 v1.52

- Fix deadlock caused by changes made for multiple batteries.  See issue #3.

- When determining if other batteries are discharging, ignore batteries that are not connected.  See issue #2.

- To provide AC status changes quicker after an AC change, poll battery objects more often after such a change.  See issue #4.


2014-01-21 v1.51

- Some fixes related to multiple batteries.  Work in progress.


2013-12-04 v1.50

- Added ACPIACAdapter implementation, which implemeents an ACPI compliant object to track status changes of the AC adapter.  As the status change, the battery objects are notified.

prior fixes:

- I didn't really track a change log prior to now.  Read the threads linked or the commit log in git.


### History

See original post at:
http://www.insanelymac.com/forum/index.php?s=bfca1f05adde52f77c9d5c0caa1250f7&showtopic=264597&view=findpost&p=1729132

See updated wiki documentation at:
https://github.com/gsly/OS-X-ACPI-Battery-Driver/wiki


### Original Credits

Most of the base code for AppleSmartBatteryManager and AppleSmartBattery created by gsly on insanelymac.com, no doubt with influences from the many other ACPI battery implementations that were out there.

Other ideas brought in by myself, some borrowed from zprood on insanelymac.com.

RehabMan - recent enhancements/bug fixes
Zprood - cycle count hack in _BIF
gsly - base code for RehabMan enhancements
