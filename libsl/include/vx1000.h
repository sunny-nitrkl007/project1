/*----------------------------------------------------------------------------
| File:
|   vx1000.h  
|
| Project:
|   VX1000 Code Instrumentation Library
|   Vector Informatik GmbH
|   V1.1 20.11.2009
|
| Description:
|   Program instrumentation for VX1000
|   Defines the functions VX1000_DATA, VX1000_INIT, VX1000_EVENT, VX1000_BYPASS
|   Don't modify this file
|   Define application specific parameters in VX1000_CFG.H
 ----------------------------------------------------------------------------*/


#include <vx1000_cfg.h>

extern boolean is_gVX1000_initialize;
//----------------------------------------------------------------------------------------------------
// Defaults
//----------------------------------------------------------------------------------------------------
// Default clock

#ifndef VX1000_CLOCK
  #if defined(VX1000_CLOCK_EMIOS_CHANNEL)
    #define VX1000_CLOCK_TICKS_PER_US  (256) 
    #define VX1000_CLOCK VX1000_Clock()
    extern unsigned int VX1000_Clock( void );
  #elif defined(VX1000_CLOCK_TB)
    #define VX1000_CLOCK VX1000_Clock()
    extern unsigned int VX1000_Clock( void );
    #ifndef VX1000_CLOCK_TICKS_PER_US
      #error Please define VX1000_CLOCK_TICKS_PER_US
    #endif
  #else
    #error Please define VX1000_CLOCK as a free runing 32 bit timer
  #endif
#endif
#define VX1000_CLOCK_TICKS_PER_MS  (1000UL*VX1000_CLOCK_TICKS_PER_US) 

//----------------------------------------------------------------------------------------------------

// If STUCK_TRACE_DATA_WORKAROUND is defined, VX1000_STIM_WAIT(e)
// will update the timestamp in the VX parameter structure while
// waiting for the STIM data. Thus stuck Nexus trace data will be
// flushed.
#define STUCK_TRACE_DATA_WORKAROUND

// Events
#define VX1000_EVENT_RAMZERO_START    0x00010000
#define VX1000_EVENT_RAMZERO_DONE     0x00010001
#define VX1000_EVENT_RAMSYNC_START    0x00010002
#define VX1000_EVENT_MAILBOX_INIT     0x00020000
#define VX1000_EVENT_MAILBOX_UPDATE   0x00020001
#define VX1000_EVENT_MAILBOX_RESETREQ 0x00020002
#define VX1000_EVENT_STIM_INIT        0x00030100
#define VX1000_EVENT_STIM_ACK         0x00030101
#define VX1000_EVENT_STIM_TIMEOUT(e)  (0x00030200|e)
#define VX1000_EVENT_STIM_ERR(e)      (0x00030300|e)
#define VX1000_EVENT_SPECIAL(e)       (0x00050000|e)


// States
#define VX1000_TDS_INIT              0x0001  // VX1000_INIT done
#define VX1000_TDS_DETECT            0x0002	 // VX1000_DETECT done
#define VX1000_TDS_DETECTED          0x0004	 // Result of VX1000_DETECT
#define VX1000_TDS_COLDSTART_DONE    0x0010	 // Coldstart done
#define VX1000_TDS_COLDSTART_TIMEOUT 0x0020	 // Coldstart timeout


//----------------------------------------------------------------------------------------------------
// VX1000 Mailbox

#ifdef VX1000_MAILBOX
  #define VX1000_MAILBOX_MAGIC  0xFEC70A06
  struct VX1000_mailbox {
    unsigned long  MagicId;
    unsigned long  Version;
    unsigned short SlotSize;
    unsigned char  MS_Slots;
    unsigned char  SM_Slots;
    unsigned long  MS_Ptr;
    unsigned long  SM_Ptr;
    unsigned char  MS_ReadIdx;
    unsigned char  MS_WriteIdx;
    unsigned char  SM_ReadIdx;
    unsigned char  SM_WriteIdx;
    unsigned short RstReq;
    unsigned short RstAck;
  };
  #define VX1000_MAILBOX_INIT \
    gVX1000_mailbox.MagicId = VX1000_MAILBOX_MAGIC; \
    gVX1000_mailbox.Version = 0; \
    gVX1000_mailbox.SlotSize = 0; \
    gVX1000_mailbox.MS_Slots = 0; \
    gVX1000_mailbox.SM_Slots = 0; \
    gVX1000_mailbox.MS_Ptr = 0; \
    gVX1000_mailbox.SM_Ptr = 0; \
    gVX1000_mailbox.MS_ReadIdx = 0; \
    gVX1000_mailbox.MS_WriteIdx = 0; \
    gVX1000_mailbox.SM_ReadIdx = 0; \
    gVX1000_mailbox.SM_WriteIdx = 0; \
    gVX1000_mailbox.RstReq = 0; \
    gVX1000_mailbox.RstAck = 0;
  #define VX1000_MAILBOX_DATA volatile struct VX1000_mailbox gVX1000_mailbox VX1000_MEMORY_SECTION;
  #define VX1000_MAILBOX_PTR (unsigned long)&gVX1000_mailbox
  extern volatile struct VX1000_mailbox gVX1000_mailbox;
#else
  #define VX1000_MAILBOX_INIT
  #define VX1000_MAILBOX_DATA
  #define VX1000_MAILBOX_PTR 0 
#endif



//----------------------------------------------------------------------------------------------------
// VX1000 Stim

#ifdef VX1000_STIM

  #define VX1000_STIM_MAGIC  0xFEC70A07
  
  struct VX1000_stim {
    unsigned long  MagicId;
    unsigned short Version;
    unsigned short Control;
    unsigned char EvtOffset;
    unsigned char EvtNumber;
    unsigned short reserved;
    struct VX1000_stim_event {
      unsigned char Ctr;
      unsigned char RqCtr;
      unsigned char Enable;
      unsigned char Copying;
    } Event[VX1000_STIM_EVENT_COUNT];
  };
  
  #define VX1000_STIM_INIT { \
    unsigned int i; \
    gVX1000_stim.Version = 0; \
    gVX1000_stim.Control = 0; \
    gVX1000_stim.EvtOffset = VX1000_STIM_EVENT_OFFSET; \
    gVX1000_stim.EvtNumber = VX1000_STIM_EVENT_COUNT; \
    gVX1000_stim.Control = 0; \
    for (i=0;i<VX1000_STIM_EVENT_COUNT;i++) { \
      gVX1000_stim.Event[i].Ctr = 0; \
      gVX1000_stim.Event[i].RqCtr = 0; \
      gVX1000_stim.Event[i].Enable = 0; \
      gVX1000_stim.Event[i].Copying = 0; \
    } \
    gVX1000_stim.MagicId = VX1000_STIM_MAGIC; \
    gVX1000.EventNumber = VX1000_EVENT_STIM_INIT; \
    gVX1000_stim_timeout = 0; \
    gVX1000_stim_enable = 0; \
  }
  
  #define VX1000_STIM_DATA \
    volatile struct VX1000_stim gVX1000_stim VX1000_MEMORY_SECTION; \
    volatile unsigned int gVX1000_stim_timeout VX1000_MEMORY_SECTION; \
    volatile unsigned int gVX1000_stim_enable VX1000_MEMORY_SECTION; \
    volatile unsigned int gVX1000_timeout VX1000_MEMORY_SECTION;
    
  #define VX1000_STIM_PTR (unsigned long)&gVX1000_stim
  
  extern volatile struct VX1000_stim gVX1000_stim;
  extern volatile unsigned int gVX1000_timeout;
  extern volatile unsigned int gVX1000_stim_timeout;
  extern volatile unsigned int gVX1000_stim_enable;

  #ifdef VX1000_STIM_BENCHMARK
    extern volatile unsigned int gVX1000_STIM_Duration[];
    #define VX1000_STIM_BENCHMARK_DATA volatile unsigned int gVX1000_STIM_Duration[VX1000_STIM_EVENT_COUNT];
  #else
    #define VX1000_STIM_BENCHMARK_DATA
  #endif

  #define VX1000_RESET_STIM_TIMEOUT(x) gVX1000_timeout = SetTimeoutUs(x) // Sets a timeout of 5 ms
  #define VX1000_CHECK_STIM_TIMEOUT CheckTimeout(gVX1000_timeout) // Return true if timeout

#else

  #define VX1000_STIM_INIT
  #define VX1000_STIM_DATA
  #define VX1000_STIM_BENCHMARK_DATA
  #define VX1000_STIM_PTR 0  
  
#endif

    
//----------------------------------------------------------------------------------------------------
// VX1000 ECU Id

#if defined(VX1000_ECUID) && defined(VX1000_ECUID_LEN)   
  #define VX1000_ECUID_DATA char gVX1000_ECU_ID[VX1000_ECUID_LEN] VX1000_MEMORY_SECTION = VX1000_ECUID;
  #define VX1000_ECUID_PTR (unsigned long)&gVX1000_ECU_ID[0]
#else
  #define VX1000_ECUID_DATA
  #define VX1000_ECUID_PTR 0
  #define VX1000_ECUID_LEN 0   
#endif   


//----------------------------------------------------------------------------------------------------
// OLDA

#ifdef VX1000_OLDA

  #define VX1000_OLDA_VERSION   0x0003
  #define VX1000_OLDA_MAGIC     0x2603

  #define VX1000_OLDA_EVENT_COUNT 32

  #ifndef VX1000_OLDA_MEMORY_SIZE
    #define VX1000_OLDA_MEMORY_SIZE 1024 // Default 1K
  #endif
    
  typedef struct {
    unsigned int   EventNumber;
    unsigned int   EventTimestamp;
    unsigned int   TransferDest;
    unsigned short TransferIndex;
    unsigned short TransferCount;
  } VX1000_OLDA_EVENT_T;

  typedef struct {
    unsigned short       MagicId;		     // 0x00
    unsigned char        Version;
    unsigned char        Runing;
    unsigned int         MemoryAddr;	   // 0x04
    unsigned short       Memorysize;	   // 0x08
    unsigned short       EventCount;	   
    VX1000_OLDA_EVENT_T *EventList;		   // 0x0C
    unsigned int        *TransferList;	 // 0x10
    #ifndef VX1000_OLDA_MEMORY_ADDR
      unsigned int         Data[VX1000_OLDA_MEMORY_SIZE/4];
    #endif
  } VX1000_OLDA_T;


  extern void vx1000_olda_init( void ); 
  extern void vx1000_olda_event( unsigned char event ); 

  #define VX1000_OLDA_INIT vx1000_olda_init();
  #define VX1000_OLDA_DATA VX1000_OLDA_T Olda;
  #define VX1000_OLDA_PTR (unsigned int)&gVX1000.Olda  
                     
  #ifdef VX1000_OLDA_BENCHMARK
    extern unsigned int gVX1000_OLDA_Duration[VX1000_OLDA_EVENT_COUNT];
    #define VX1000_OLDA_BENCHMARK_DATA unsigned int gVX1000_OLDA_Duration[VX1000_OLDA_EVENT_COUNT];
  #else
    #define VX1000_OLDA_BENCHMARK_DATA
  #endif

#else

  #define VX1000_OLDA_INITIALIZE() 
  #define VX1000_OLDA_EVENT(x)  

  #define VX1000_OLDA_INIT
  #define VX1000_OLDA_DATA
  #define VX1000_OLDA_PTR 0  

  #define VX1000_OLDA_BENCHMARK_DATA

#endif


//----------------------------------------------------------------------------------------------------
// VX1000 Struct

#define VX1000_STRUCT_VERSION 6 // New in version 4: OldaPtr, version 5: Olda integrated at fixed position 0x40, version 6: OldaEventNumber
#define VX1000_STRUCT_MAGIC 0xFEC70A08

struct VX1000 {
  unsigned int EventNumber;         // 00
  unsigned int EventTimestamp;
  unsigned int MagicId;
  unsigned int Version;             
  unsigned int GetIdPtr;            // 10  
  unsigned int GetIdLen;
  unsigned int XcpMailboxPtr;
  unsigned int StimCtrlPtr;
  unsigned int RamSynchField;       // 20
  unsigned int ToolDetectState;
  unsigned int OldaPtr;
  unsigned int OldaEventNumber;
  unsigned int res4;               // 30
  unsigned int res5;
  unsigned int res6;
  unsigned int res7;
                                   // 40
  #if defined(VX1000_OLDA)		     // Do not change the offset here, must be 0x40 !
   VX1000_OLDA_DATA
  #endif

};                                  


extern volatile struct VX1000 gVX1000;

#define VX1000_STRUCT_DATA volatile struct VX1000 gVX1000 VX1000_MEMORY_SECTION;
    
//----------------------------------------------------------------------------------------------------
// User macros for VX1000 initialisation

// Define the global data needed for VX1000
#define VX1000_DATA \
  VX1000_STRUCT_DATA \
  VX1000_MAILBOX_DATA \
  VX1000_STIM_DATA \
  VX1000_STIM_BENCHMARK_DATA \
  VX1000_ECUID_DATA \
  VX1000_OLDA_BENCHMARK_DATA

  
// Initialize the global data
extern void vx1000_init(void);    
#define VX1000_INIT() vx1000_init();
    


//----------------------------------------------------------------------------------------------------
// User macros for DAQ

#ifdef VX1000_OLDA

  // Trigger an event with VX1000 timestamp
  #define VX1000_EVENT(x) \
    vx1000_olda_event(x);

  // Trigger a special event (EventNumber=0..255,OldaEventNumber=31)
  #define VX1000_SPECIAL_EVENT(x) \
    gVX1000.EventTimestamp = VX1000_CLOCK; \
    gVX1000.EventNumber = (x); \
    gVX1000.OldaEventNumber ^= 0x80000000;


#else

  // Trigger an event 
  #define VX1000_EVENT(x) \
    gVX1000.EventTimestamp = VX1000_CLOCK; \
    gVX1000.EventNumber = (x); 

#endif

// Update the ECU timestamp with a given value
#define VX1000_TIMESTAMP_UPDATE(t) \
  gVX1000.EventTimestamp = (t); 
  
// Trigger an event with a given value for ECU timestamp
#define VX1000_TIMESTAMP_EVENT(x,t) \
  gVX1000.EventTimestamp = (t); \
  gVX1000.EventNumber = (x); 

//----------------------------------------------------------------------------------------------------
// User macros for STIM
 
// Stim Handler
#define VX1000_STIM_CONTROL() \
  if (gVX1000_stim.Control && gVX1000_stim_enable==0) { \
    gVX1000.EventNumber = VX1000_EVENT_STIM_ACK; \
    gVX1000_stim_enable = 1; \
  } \
  else if (gVX1000_stim.Control==0 && gVX1000_stim_enable==1) { \
    VX1000_STIM_INIT; \
  }


#define VX1000_IS_STIM_EVENT(e) ((e)>=VX1000_STIM_EVENT_OFFSET&&(e)<(VX1000_STIM_EVENT_OFFSET+VX1000_STIM_EVENT_COUNT))
#if !defined(VX1000_RESET_STIM_TIMEOUT) || !defined(VX1000_CHECK_STIM_TIMEOUT)
  #define VX1000_RESET_TIMEOUT
  #define VX1000_CHECK_TIMEOUT 0
#endif

// Stim Active Check
#define VX1000_STIM_ACTIVE(e) \
  (gVX1000_stim.Control && gVX1000_stim_enable && VX1000_IS_STIM_EVENT(e) && gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].Enable)

// Request a specific STIM data set assciated to event e
#define VX1000_STIM_REQUEST(e) \
   gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].RqCtr++; \
   gVX1000.EventNumber = e;

// Wait until a specific STIM request is fullfilled

#ifdef STUCK_TRACE_DATA_WORKAROUND  
// Cyclically write the timestamp field while waiting for the STIM in the polling loop. 
#define VX1000_STIM_WAIT(e,timeout) \
  VX1000_RESET_STIM_TIMEOUT(timeout); \
  while (gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].Ctr!=gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].RqCtr) { \
    VX1000_TIMESTAMP_UPDATE(VX1000_CLOCK); \
    if (VX1000_CHECK_STIM_TIMEOUT) { \
      gVX1000_stim_timeout++; \
      if (gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].Copying) { \
        VX1000_RESET_STIM_TIMEOUT(timeout); \
        while (gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].Ctr!=gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].RqCtr); { \
          if (VX1000_CHECK_STIM_TIMEOUT) gVX1000.EventNumber = VX1000_EVENT_STIM_ERR(e); goto VX1000_break; \
        } \
        break; \
      } \
      else { \
        if (VX1000_STIM_ACTIVE(e)) gVX1000.EventNumber = VX1000_EVENT_STIM_TIMEOUT(e); \
        goto VX1000_break; \
      } \
    } \
  } \
  VX1000_break:;

#else

#define VX1000_STIM_WAIT(e,timeout) \
  VX1000_RESET_STIM_TIMEOUT(timeout); \
  while (gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].Ctr!=gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].RqCtr) { \
    if (VX1000_CHECK_STIM_TIMEOUT) { \
      gVX1000_stim_timeout++; \
      if (gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].Copying) { \
        VX1000_RESET_STIM_TIMEOUT(timeout); \
        while (gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].Ctr!=gVX1000_stim.Event[e-VX1000_STIM_EVENT_OFFSET].RqCtr); { \
          if (VX1000_CHECK_STIM_TIMEOUT) gVX1000.EventNumber = VX1000_EVENT_STIM_ERR(e); goto VX1000_break; \
        } \
        break; \
      } \
      else { \
        if (VX1000_STIM_ACTIVE(e)) gVX1000.EventNumber = VX1000_EVENT_STIM_TIMEOUT(e); \
        goto VX1000_break; \
      } \
    } \
  } \
  VX1000_break:;

#endif    
extern unsigned char VX1000_BYPASS( unsigned char daq_event, unsigned char stim_event, unsigned int timeout);
  

