/*++ BUILD Version: 0000    // Increment this if a change has global effects

The  Telephony  API  is jointly copyrighted by Intel and Microsoft.  You are
granted  a royalty free worldwide, unlimited license to make copies, and use
the   API/SPI  for  making  applications/drivers  that  interface  with  the
specification provided that this paragraph and the Intel/Microsoft copyright
statement is maintained as is in the text and source code files.

Copyright (c) Microsoft Corporation, All rights reserved.
Portions copyright 1992, 1993 Intel/Microsoft, all rights reserved.

Module Name:

    tapi.h

Notes:

    Additions to the Telephony Application Programming Interface (TAPI) since
    version 1.0 are noted by version number (e.g. "TAPI v1.4").

--*/

#ifndef TAPI_H
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#define TAPI_H



//
//  -- TAPI VERSION INFO -- TAPI VERSION INFO -- TAPI VERSION INFO --
//
// To build  a TAPI 1.4 application put a define as below in your source
// file before you include TAPI.H:
//
// #define TAPI_CURRENT_VERSION 0x00010004
//
//

#ifndef TAPI_CURRENT_VERSION
#define TAPI_CURRENT_VERSION 0x00020002
#endif

#include <windows.h>
#if WIN32
#include <basetsd.h>
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020002)
#include <oaidl.h>
#endif

#pragma pack(1)
// Type definitions of the data types used in tapi

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */


//
// TAPI type definitions
//

#define DECLARE_OPAQUE32(name)  typedef DWORD name

DECLARE_OPAQUE32(HCALL);
typedef HCALL FAR * LPHCALL;

#if (TAPI_CURRENT_VERSION >= 0x00030000)
DECLARE_OPAQUE32(HCALLHUB);                                     // TAPI v3.0
typedef HCALLHUB FAR * LPHCALLHUB;                              // TAPI v3.0
#endif

DECLARE_OPAQUE32(HLINE);
typedef HLINE FAR * LPHLINE;

DECLARE_OPAQUE32(HPHONE);
typedef HPHONE FAR * LPHPHONE;

DECLARE_OPAQUE32(HLINEAPP);
typedef HLINEAPP FAR * LPHLINEAPP;

DECLARE_OPAQUE32(HPHONEAPP);
typedef HPHONEAPP FAR * LPHPHONEAPP;

#if (TAPI_CURRENT_VERSION >= 0x00020002)
DECLARE_OPAQUE32(HAGENTSESSION);                                // TAPI v2.2
typedef HAGENTSESSION FAR * LPHAGENTSESSION;                    // TAPI v2.2

DECLARE_OPAQUE32(HAGENT);                                       // TAPI v2.2
typedef HAGENT FAR * LPHAGENT;                                  // TAPI v2.2
#endif

#if (TAPI_CURRENT_VERSION >= 0x00030000)
DECLARE_OPAQUE32(HPRIVATECHANNEL);                              // TAPI v3.0
typedef HPRIVATECHANNEL FAR * LPHPRIVATECHANNEL;                // TAPI v3.0
#endif

typedef HICON FAR * LPHICON;

typedef void (CALLBACK * LINECALLBACK)(
    DWORD               hDevice,
    DWORD               dwMessage,
    DWORD_PTR           dwInstance,
    DWORD_PTR           dwParam1,
    DWORD_PTR           dwParam2,
    DWORD_PTR           dwParam3
    );

typedef void (CALLBACK * PHONECALLBACK)(
    DWORD               hDevice,
    DWORD               dwMessage,
    DWORD_PTR           dwInstance,
    DWORD_PTR           dwParam1,
    DWORD_PTR           dwParam2,
    DWORD_PTR           dwParam3
    );


// Messages for Phones and Lines

#define LINE_ADDRESSSTATE                       0L
#define LINE_CALLINFO                           1L
#define LINE_CALLSTATE                          2L
#define LINE_CLOSE                              3L
#define LINE_DEVSPECIFIC                        4L
#define LINE_DEVSPECIFICFEATURE                 5L
#define LINE_GATHERDIGITS                       6L
#define LINE_GENERATE                           7L
#define LINE_LINEDEVSTATE                       8L
#define LINE_MONITORDIGITS                      9L
#define LINE_MONITORMEDIA                       10L
#define LINE_MONITORTONE                        11L
#define LINE_REPLY                              12L
#define LINE_REQUEST                            13L
#define PHONE_BUTTON                            14L
#define PHONE_CLOSE                             15L
#define PHONE_DEVSPECIFIC                       16L
#define PHONE_REPLY                             17L
#define PHONE_STATE                             18L
#define LINE_CREATE                             19L             // TAPI v1.4
#define PHONE_CREATE                            20L             // TAPI v1.4

#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINE_AGENTSPECIFIC                      21L             // TAPI v2.0
#define LINE_AGENTSTATUS                        22L             // TAPI v2.0
#define LINE_APPNEWCALL                         23L             // TAPI v2.0
#define LINE_PROXYREQUEST                       24L             // TAPI v2.0
#define LINE_REMOVE                             25L             // TAPI v2.0
#define PHONE_REMOVE                            26L             // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020002)
#define LINE_AGENTSESSIONSTATUS                 27L             // TAPI v2.2
#define LINE_QUEUESTATUS                        28L             // TAPI v2.2
#define LINE_AGENTSTATUSEX                      29L             // TAPI v2.2
#define LINE_GROUPSTATUS                        30L             // TAPI v2.2
#define LINE_PROXYSTATUS                        31L             // TAPI v2.2
#endif

#if (TAPI_CURRENT_VERSION >= 0x00030000)
#define LINE_APPNEWCALLHUB                      32L             // TAPI v3.0
#define LINE_CALLHUBCLOSE                       33L             // TAPI v3.0
#define LINE_DEVSPECIFICEX                      34L             // TAPI v3.0
#endif

#define INITIALIZE_NEGOTIATION                  0xFFFFFFFFUL

#define LINEADDRCAPFLAGS_FWDNUMRINGS            0x00000001
#define LINEADDRCAPFLAGS_PICKUPGROUPID          0x00000002
#define LINEADDRCAPFLAGS_SECURE                 0x00000004
#define LINEADDRCAPFLAGS_BLOCKIDDEFAULT         0x00000008
#define LINEADDRCAPFLAGS_BLOCKIDOVERRIDE        0x00000010
#define LINEADDRCAPFLAGS_DIALED                 0x00000020
#define LINEADDRCAPFLAGS_ORIGOFFHOOK            0x00000040
#define LINEADDRCAPFLAGS_DESTOFFHOOK            0x00000080
#define LINEADDRCAPFLAGS_FWDCONSULT             0x00000100
#define LINEADDRCAPFLAGS_SETUPCONFNULL          0x00000200
#define LINEADDRCAPFLAGS_AUTORECONNECT          0x00000400
#define LINEADDRCAPFLAGS_COMPLETIONID           0x00000800
#define LINEADDRCAPFLAGS_TRANSFERHELD           0x00001000
#define LINEADDRCAPFLAGS_TRANSFERMAKE           0x00002000
#define LINEADDRCAPFLAGS_CONFERENCEHELD         0x00004000
#define LINEADDRCAPFLAGS_CONFERENCEMAKE         0x00008000
#define LINEADDRCAPFLAGS_PARTIALDIAL            0x00010000
#define LINEADDRCAPFLAGS_FWDSTATUSVALID         0x00020000
#define LINEADDRCAPFLAGS_FWDINTEXTADDR          0x00040000
#define LINEADDRCAPFLAGS_FWDBUSYNAADDR          0x00080000
#define LINEADDRCAPFLAGS_ACCEPTTOALERT          0x00100000
#define LINEADDRCAPFLAGS_CONFDROP               0x00200000
#define LINEADDRCAPFLAGS_PICKUPCALLWAIT         0x00400000
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINEADDRCAPFLAGS_PREDICTIVEDIALER       0x00800000      // TAPI v2.0
#define LINEADDRCAPFLAGS_QUEUE                  0x01000000      // TAPI v2.0
#define LINEADDRCAPFLAGS_ROUTEPOINT             0x02000000      // TAPI v2.0
#define LINEADDRCAPFLAGS_HOLDMAKESNEW           0x04000000      // TAPI v2.0
#define LINEADDRCAPFLAGS_NOINTERNALCALLS        0x08000000      // TAPI v2.0
#define LINEADDRCAPFLAGS_NOEXTERNALCALLS        0x10000000      // TAPI v2.0
#define LINEADDRCAPFLAGS_SETCALLINGID           0x20000000      // TAPI v2.0
#endif
#if (TAPI_CURRENT_VERSION >= 0x00020002)
#define LINEADDRCAPFLAGS_ACDGROUP               0x40000000      // TAPI v2.2
#endif
#if (TAPI_CURRENT_VERSION >= 0x00030000)
#define LINEADDRCAPFLAGS_NOPSTNADDRESSTRANSLATION 0x80000000    // TAPI v3.0
#endif

#define LINEADDRESSMODE_ADDRESSID               0x00000001
#define LINEADDRESSMODE_DIALABLEADDR            0x00000002

#define LINEADDRESSSHARING_PRIVATE              0x00000001
#define LINEADDRESSSHARING_BRIDGEDEXCL          0x00000002
#define LINEADDRESSSHARING_BRIDGEDNEW           0x00000004
#define LINEADDRESSSHARING_BRIDGEDSHARED        0x00000008
#define LINEADDRESSSHARING_MONITORED            0x00000010

#define LINEADDRESSSTATE_OTHER                  0x00000001
#define LINEADDRESSSTATE_DEVSPECIFIC            0x00000002
#define LINEADDRESSSTATE_INUSEZERO              0x00000004
#define LINEADDRESSSTATE_INUSEONE               0x00000008
#define LINEADDRESSSTATE_INUSEMANY              0x00000010
#define LINEADDRESSSTATE_NUMCALLS               0x00000020
#define LINEADDRESSSTATE_FORWARD                0x00000040
#define LINEADDRESSSTATE_TERMINALS              0x00000080
#define LINEADDRESSSTATE_CAPSCHANGE             0x00000100      // TAPI v1.4

#if (TAPI_CURRENT_VERSION >= 0x00030000)
#define LINEADDRESSTYPE_PHONENUMBER             0x00000001
#define LINEADDRESSTYPE_SDP                     0x00000002
#define LINEADDRESSTYPE_EMAILNAME               0x00000004
#define LINEADDRESSTYPE_DOMAINNAME              0x00000008
#define LINEADDRESSTYPE_IPADDRESS               0x00000010
#endif

#define LINEADDRFEATURE_FORWARD                 0x00000001
#define LINEADDRFEATURE_MAKECALL                0x00000002
#define LINEADDRFEATURE_PICKUP                  0x00000004
#define LINEADDRFEATURE_SETMEDIACONTROL         0x00000008
#define LINEADDRFEATURE_SETTERMINAL             0x00000010
#define LINEADDRFEATURE_SETUPCONF               0x00000020
#define LINEADDRFEATURE_UNCOMPLETECALL          0x00000040
#define LINEADDRFEATURE_UNPARK                  0x00000080
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINEADDRFEATURE_PICKUPHELD              0x00000100      // TAPI v2.0
#define LINEADDRFEATURE_PICKUPGROUP             0x00000200      // TAPI v2.0
#define LINEADDRFEATURE_PICKUPDIRECT            0x00000400      // TAPI v2.0
#define LINEADDRFEATURE_PICKUPWAITING           0x00000800      // TAPI v2.0
#define LINEADDRFEATURE_FORWARDFWD              0x00001000      // TAPI v2.0
#define LINEADDRFEATURE_FORWARDDND              0x00002000      // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINEAGENTFEATURE_SETAGENTGROUP          0x00000001      // TAPI v2.0
#define LINEAGENTFEATURE_SETAGENTSTATE          0x00000002      // TAPI v2.0
#define LINEAGENTFEATURE_SETAGENTACTIVITY       0x00000004      // TAPI v2.0
#define LINEAGENTFEATURE_AGENTSPECIFIC          0x00000008      // TAPI v2.0
#define LINEAGENTFEATURE_GETAGENTACTIVITYLIST   0x00000010      // TAPI v2.0
#define LINEAGENTFEATURE_GETAGENTGROUP          0x00000020      // TAPI v2.0

#define LINEAGENTSTATE_LOGGEDOFF                0x00000001      // TAPI v2.0
#define LINEAGENTSTATE_NOTREADY                 0x00000002      // TAPI v2.0
#define LINEAGENTSTATE_READY                    0x00000004      // TAPI v2.0
#define LINEAGENTSTATE_BUSYACD                  0x00000008      // TAPI v2.0
#define LINEAGENTSTATE_BUSYINCOMING             0x00000010      // TAPI v2.0
#define LINEAGENTSTATE_BUSYOUTBOUND             0x00000020      // TAPI v2.0
#define LINEAGENTSTATE_BUSYOTHER                0x00000040      // TAPI v2.0
#define LINEAGENTSTATE_WORKINGAFTERCALL         0x00000080      // TAPI v2.0
#define LINEAGENTSTATE_UNKNOWN                  0x00000100      // TAPI v2.0
#define LINEAGENTSTATE_UNAVAIL                  0x00000200      // TAPI v2.0

#define LINEAGENTSTATUS_GROUP                   0x00000001      // TAPI v2.0
#define LINEAGENTSTATUS_STATE                   0x00000002      // TAPI v2.0
#define LINEAGENTSTATUS_NEXTSTATE               0x00000004      // TAPI v2.0
#define LINEAGENTSTATUS_ACTIVITY                0x00000008      // TAPI v2.0
#define LINEAGENTSTATUS_ACTIVITYLIST            0x00000010      // TAPI v2.0
#define LINEAGENTSTATUS_GROUPLIST               0x00000020      // TAPI v2.0
#define LINEAGENTSTATUS_CAPSCHANGE              0x00000040      // TAPI v2.0
#define LINEAGENTSTATUS_VALIDSTATES             0x00000080      // TAPI v2.0
#define LINEAGENTSTATUS_VALIDNEXTSTATES         0x00000100      // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020002)
#define LINEAGENTSTATEEX_NOTREADY               0x00000001      // TAPI v2.2
#define LINEAGENTSTATEEX_READY                  0x00000002      // TAPI v2.2
#define LINEAGENTSTATEEX_BUSYACD                0x00000004      // TAPI v2.2
#define LINEAGENTSTATEEX_BUSYINCOMING           0x00000008      // TAPI v2.2
#define LINEAGENTSTATEEX_BUSYOUTGOING           0x00000010      // TAPI v2.2
#define LINEAGENTSTATEEX_UNKNOWN                0x00000020      // TAPI v2.2
#define LINEAGENTSTATEEX_RELEASED               0x00000040      // TAPI v2.2

#define LINEAGENTSTATUSEX_NEWAGENT              0x00000001      // TAPI v2.2
#define LINEAGENTSTATUSEX_STATE                 0x00000002      // TAPI v2.2
#define LINEAGENTSTATUSEX_UPDATEINFO            0x00000004      // TAPI v2.2
//#define LINEAGENTSTATUSEX_DESTROYED             0x00000004      // TAPI v2.2

#define LINEAGENTSESSIONSTATE_NOTREADY          0x00000001      // TAPI v2.2
#define LINEAGENTSESSIONSTATE_READY             0x00000002      // TAPI v2.2
#define LINEAGENTSESSIONSTATE_BUSYONCALL        0x00000004      // TAPI v2.2
#define LINEAGENTSESSIONSTATE_BUSYWRAPUP        0x00000008      // TAPI v2.2
#define LINEAGENTSESSIONSTATE_ENDED             0x00000010      // TAPI v2.2
#define LINEAGENTSESSIONSTATE_RELEASED          0x00000020      // TAPI v2.2

#define LINEAGENTSESSIONSTATUS_NEWSESSION       0x00000001      // TAPI v2.2
#define LINEAGENTSESSIONSTATUS_STATE            0x00000002      // TAPI v2.2
#define LINEAGENTSESSIONSTATUS_UPDATEINFO       0x00000004      // TAPI v2.2
//#define LINEAGENTSESSIONSTATUS_DESTROYED        0x00000008      // TAPI v2.2

#define LINEQUEUESTATUS_UPDATEINFO              0x00000001      // TAPI v2.2
#define LINEQUEUESTATUS_NEWQUEUE                0x00000002      // TAPI v2.2
#define LINEQUEUESTATUS_QUEUEREMOVED            0x00000004      // TAPI v2.2

#define LINEGROUPSTATUS_NEWGROUP                0x00000001      // TAPI v2.2
#define LINEGROUPSTATUS_GROUPREMOVED            0x00000002      // TAPI v2.2

#define LINEPROXYSTATUS_OPEN                    0x00000001      // TAPI v2.2
#define LINEPROXYSTATUS_CLOSE                   0x00000002      // TAPI v2.2
#define LINEPROXYSTATUS_ALLOPENFORACD           0x00000004      // TAPI v2.2
#endif

#define LINEANSWERMODE_NONE                     0x00000001
#define LINEANSWERMODE_DROP                     0x00000002
#define LINEANSWERMODE_HOLD                     0x00000004

#define LINEBEARERMODE_VOICE                    0x00000001
#define LINEBEARERMODE_SPEECH                   0x00000002
#define LINEBEARERMODE_MULTIUSE                 0x00000004
#define LINEBEARERMODE_DATA                     0x00000008
#define LINEBEARERMODE_ALTSPEECHDATA            0x00000010
#define LINEBEARERMODE_NONCALLSIGNALING         0x00000020
#define LINEBEARERMODE_PASSTHROUGH              0x00000040      // TAPI v1.4
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINEBEARERMODE_RESTRICTEDDATA           0x00000080      // TAPI v2.0
#endif

#define LINEBUSYMODE_STATION                    0x00000001
#define LINEBUSYMODE_TRUNK                      0x00000002
#define LINEBUSYMODE_UNKNOWN                    0x00000004
#define LINEBUSYMODE_UNAVAIL                    0x00000008

#define LINECALLCOMPLCOND_BUSY                  0x00000001
#define LINECALLCOMPLCOND_NOANSWER              0x00000002

#define LINECALLCOMPLMODE_CAMPON                0x00000001
#define LINECALLCOMPLMODE_CALLBACK              0x00000002
#define LINECALLCOMPLMODE_INTRUDE               0x00000004
#define LINECALLCOMPLMODE_MESSAGE               0x00000008

#define LINECALLFEATURE_ACCEPT                  0x00000001
#define LINECALLFEATURE_ADDTOCONF               0x00000002
#define LINECALLFEATURE_ANSWER                  0x00000004
#define LINECALLFEATURE_BLINDTRANSFER           0x00000008
#define LINECALLFEATURE_COMPLETECALL            0x00000010
#define LINECALLFEATURE_COMPLETETRANSF          0x00000020
#define LINECALLFEATURE_DIAL                    0x00000040
#define LINECALLFEATURE_DROP                    0x00000080
#define LINECALLFEATURE_GATHERDIGITS            0x00000100
#define LINECALLFEATURE_GENERATEDIGITS          0x00000200
#define LINECALLFEATURE_GENERATETONE            0x00000400
#define LINECALLFEATURE_HOLD                    0x00000800
#define LINECALLFEATURE_MONITORDIGITS           0x00001000
#define LINECALLFEATURE_MONITORMEDIA            0x00002000
#define LINECALLFEATURE_MONITORTONES            0x00004000
#define LINECALLFEATURE_PARK                    0x00008000
#define LINECALLFEATURE_PREPAREADDCONF          0x00010000
#define LINECALLFEATURE_REDIRECT                0x00020000
#define LINECALLFEATURE_REMOVEFROMCONF          0x00040000
#define LINECALLFEATURE_SECURECALL              0x00080000
#define LINECALLFEATURE_SENDUSERUSER            0x00100000
#define LINECALLFEATURE_SETCALLPARAMS           0x00200000
#define LINECALLFEATURE_SETMEDIACONTROL         0x00400000
#define LINECALLFEATURE_SETTERMINAL             0x00800000
#define LINECALLFEATURE_SETUPCONF               0x01000000
#define LINECALLFEATURE_SETUPTRANSFER           0x02000000
#define LINECALLFEATURE_SWAPHOLD                0x04000000
#define LINECALLFEATURE_UNHOLD                  0x08000000
#define LINECALLFEATURE_RELEASEUSERUSERINFO     0x10000000      // TAPI v1.4
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINECALLFEATURE_SETTREATMENT            0x20000000      // TAPI v2.0
#define LINECALLFEATURE_SETQOS                  0x40000000      // TAPI v2.0
#define LINECALLFEATURE_SETCALLDATA             0x80000000      // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINECALLFEATURE2_NOHOLDCONFERENCE       0x00000001      // TAPI v2.0
#define LINECALLFEATURE2_ONESTEPTRANSFER        0x00000002      // TAPI v2.0
#define LINECALLFEATURE2_COMPLCAMPON            0x00000004      // TAPI v2.0
#define LINECALLFEATURE2_COMPLCALLBACK          0x00000008      // TAPI v2.0
#define LINECALLFEATURE2_COMPLINTRUDE           0x00000010      // TAPI v2.0
#define LINECALLFEATURE2_COMPLMESSAGE           0x00000020      // TAPI v2.0
#define LINECALLFEATURE2_TRANSFERNORM           0x00000040      // TAPI v2.0
#define LINECALLFEATURE2_TRANSFERCONF           0x00000080      // TAPI v2.0
#define LINECALLFEATURE2_PARKDIRECT             0x00000100      // TAPI v2.0
#define LINECALLFEATURE2_PARKNONDIRECT          0x00000200      // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00030000)
#define LINECALLHUBTRACKING_NONE                0x00000000      // TAPI v3.0
#define LINECALLHUBTRACKING_PROVIDERLEVEL       0x00000001      // TAPI v3.0
#define LINECALLHUBTRACKING_ALLCALLS            0x00000002      // TAPI v3.0
#endif

#define LINECALLINFOSTATE_OTHER                 0x00000001
#define LINECALLINFOSTATE_DEVSPECIFIC           0x00000002
#define LINECALLINFOSTATE_BEARERMODE            0x00000004
#define LINECALLINFOSTATE_RATE                  0x00000008
#define LINECALLINFOSTATE_MEDIAMODE             0x00000010
#define LINECALLINFOSTATE_APPSPECIFIC           0x00000020
#define LINECALLINFOSTATE_CALLID                0x00000040
#define LINECALLINFOSTATE_RELATEDCALLID         0x00000080
#define LINECALLINFOSTATE_ORIGIN                0x00000100
#define LINECALLINFOSTATE_REASON                0x00000200
#define LINECALLINFOSTATE_COMPLETIONID          0x00000400
#define LINECALLINFOSTATE_NUMOWNERINCR          0x00000800
#define LINECALLINFOSTATE_NUMOWNERDECR          0x00001000
#define LINECALLINFOSTATE_NUMMONITORS           0x00002000
#define LINECALLINFOSTATE_TRUNK                 0x00004000
#define LINECALLINFOSTATE_CALLERID              0x00008000
#define LINECALLINFOSTATE_CALLEDID              0x00010000
#define LINECALLINFOSTATE_CONNECTEDID           0x00020000
#define LINECALLINFOSTATE_REDIRECTIONID         0x00040000
#define LINECALLINFOSTATE_REDIRECTINGID         0x00080000
#define LINECALLINFOSTATE_DISPLAY               0x00100000
#define LINECALLINFOSTATE_USERUSERINFO          0x00200000
#define LINECALLINFOSTATE_HIGHLEVELCOMP         0x00400000
#define LINECALLINFOSTATE_LOWLEVELCOMP          0x00800000
#define LINECALLINFOSTATE_CHARGINGINFO          0x01000000
#define LINECALLINFOSTATE_TERMINAL              0x02000000
#define LINECALLINFOSTATE_DIALPARAMS            0x04000000
#define LINECALLINFOSTATE_MONITORMODES          0x08000000
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINECALLINFOSTATE_TREATMENT             0x10000000      // TAPI v2.0
#define LINECALLINFOSTATE_QOS                   0x20000000      // TAPI v2.0
#define LINECALLINFOSTATE_CALLDATA              0x40000000      // TAPI v2.0
#endif

#define LINECALLORIGIN_OUTBOUND                 0x00000001
#define LINECALLORIGIN_INTERNAL                 0x00000002
#define LINECALLORIGIN_EXTERNAL                 0x00000004
#define LINECALLORIGIN_UNKNOWN                  0x00000010
#define LINECALLORIGIN_UNAVAIL                  0x00000020
#define LINECALLORIGIN_CONFERENCE               0x00000040
#define LINECALLORIGIN_INBOUND                  0x00000080      // TAPI v1.4

#define LINECALLPARAMFLAGS_SECURE               0x00000001
#define LINECALLPARAMFLAGS_IDLE                 0x00000002
#define LINECALLPARAMFLAGS_BLOCKID              0x00000004
#define LINECALLPARAMFLAGS_ORIGOFFHOOK          0x00000008
#define LINECALLPARAMFLAGS_DESTOFFHOOK          0x00000010
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINECALLPARAMFLAGS_NOHOLDCONFERENCE     0x00000020      // TAPI v2.0
#define LINECALLPARAMFLAGS_PREDICTIVEDIAL       0x00000040      // TAPI v2.0
#define LINECALLPARAMFLAGS_ONESTEPTRANSFER      0x00000080      // TAPI v2.0
#endif

#define LINECALLPARTYID_BLOCKED                 0x00000001
#define LINECALLPARTYID_OUTOFAREA               0x00000002
#define LINECALLPARTYID_NAME                    0x00000004
#define LINECALLPARTYID_ADDRESS                 0x00000008
#define LINECALLPARTYID_PARTIAL                 0x00000010
#define LINECALLPARTYID_UNKNOWN                 0x00000020
#define LINECALLPARTYID_UNAVAIL                 0x00000040

#define LINECALLPRIVILEGE_NONE                  0x00000001
#define LINECALLPRIVILEGE_MONITOR               0x00000002
#define LINECALLPRIVILEGE_OWNER                 0x00000004

#define LINECALLREASON_DIRECT                   0x00000001
#define LINECALLREASON_FWDBUSY                  0x00000002
#define LINECALLREASON_FWDNOANSWER              0x00000004
#define LINECALLREASON_FWDUNCOND                0x00000008
#define LINECALLREASON_PICKUP                   0x00000010
#define LINECALLREASON_UNPARK                   0x00000020
#define LINECALLREASON_REDIRECT                 0x00000040
#define LINECALLREASON_CALLCOMPLETION           0x00000080
#define LINECALLREASON_TRANSFER                 0x00000100
#define LINECALLREASON_REMINDER                 0x00000200
#define LINECALLREASON_UNKNOWN                  0x00000400
#define LINECALLREASON_UNAVAIL                  0x00000800
#define LINECALLREASON_INTRUDE                  0x00001000      // TAPI v1.4
#define LINECALLREASON_PARKED                   0x00002000      // TAPI v1.4
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINECALLREASON_CAMPEDON                 0x00004000      // TAPI v2.0
#define LINECALLREASON_ROUTEREQUEST             0x00008000      // TAPI v2.0
#endif

#define LINECALLSELECT_LINE                     0x00000001
#define LINECALLSELECT_ADDRESS                  0x00000002
#define LINECALLSELECT_CALL                     0x00000004
#if (TAPI_CURRENT_VERSION >= 0x00020001)
#define LINECALLSELECT_DEVICEID                 0x00000008      // TAPI v2.1
#endif
#if (TAPI_CURRENT_VERSION >= 0x00030000)
#define LINECALLSELECT_CALLID                   0x00000010      // TAPI v3.0
#endif

#define LINECALLSTATE_IDLE                      0x00000001
#define LINECALLSTATE_OFFERING                  0x00000002
#define LINECALLSTATE_ACCEPTED                  0x00000004
#define LINECALLSTATE_DIALTONE                  0x00000008
#define LINECALLSTATE_DIALING                   0x00000010
#define LINECALLSTATE_RINGBACK                  0x00000020
#define LINECALLSTATE_BUSY                      0x00000040
#define LINECALLSTATE_SPECIALINFO               0x00000080
#define LINECALLSTATE_CONNECTED                 0x00000100
#define LINECALLSTATE_PROCEEDING                0x00000200
#define LINECALLSTATE_ONHOLD                    0x00000400
#define LINECALLSTATE_CONFERENCED               0x00000800
#define LINECALLSTATE_ONHOLDPENDCONF            0x00001000
#define LINECALLSTATE_ONHOLDPENDTRANSFER        0x00002000
#define LINECALLSTATE_DISCONNECTED              0x00004000
#define LINECALLSTATE_UNKNOWN                   0x00008000

#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINECALLTREATMENT_SILENCE               0x00000001      // TAPI v2.0
#define LINECALLTREATMENT_RINGBACK              0x00000002      // TAPI v2.0
#define LINECALLTREATMENT_BUSY                  0x00000003      // TAPI v2.0
#define LINECALLTREATMENT_MUSIC                 0x00000004      // TAPI v2.0
#endif

#define LINECARDOPTION_PREDEFINED               0x00000001      // TAPI v1.4
#define LINECARDOPTION_HIDDEN                   0x00000002      // TAPI v1.4

#define LINECONNECTEDMODE_ACTIVE                0x00000001      // TAPI v1.4
#define LINECONNECTEDMODE_INACTIVE              0x00000002      // TAPI v1.4
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINECONNECTEDMODE_ACTIVEHELD            0x00000004      // TAPI v2.0
#define LINECONNECTEDMODE_INACTIVEHELD          0x00000008      // TAPI v2.0
#define LINECONNECTEDMODE_CONFIRMED             0x00000010      // TAPI v2.0
#endif

#define LINEDEVCAPFLAGS_CROSSADDRCONF           0x00000001
#define LINEDEVCAPFLAGS_HIGHLEVCOMP             0x00000002
#define LINEDEVCAPFLAGS_LOWLEVCOMP              0x00000004
#define LINEDEVCAPFLAGS_MEDIACONTROL            0x00000008
#define LINEDEVCAPFLAGS_MULTIPLEADDR            0x00000010
#define LINEDEVCAPFLAGS_CLOSEDROP               0x00000020
#define LINEDEVCAPFLAGS_DIALBILLING             0x00000040
#define LINEDEVCAPFLAGS_DIALQUIET               0x00000080
#define LINEDEVCAPFLAGS_DIALDIALTONE            0x00000100
#if (TAPI_CURRENT_VERSION >= 0x00030000)
#define LINEDEVCAPFLAGS_MSP                     0x00000200      // TAPI v3.0
#define LINEDEVCAPFLAGS_CALLHUB                 0x00000400      // TAPI v3.0
#define LINEDEVCAPFLAGS_CALLHUBTRACKING         0x00000800      // TAPI v3.0
#define LINEDEVCAPFLAGS_PRIVATEOBJECTS          0x00001000      // TAPI v3.0
#endif
#define LINEDEVCAPFLAGS_LOCAL                   0x00002000

#define LINEDEVSTATE_OTHER                      0x00000001
#define LINEDEVSTATE_RINGING                    0x00000002
#define LINEDEVSTATE_CONNECTED                  0x00000004
#define LINEDEVSTATE_DISCONNECTED               0x00000008
#define LINEDEVSTATE_MSGWAITON                  0x00000010
#define LINEDEVSTATE_MSGWAITOFF                 0x00000020
#define LINEDEVSTATE_INSERVICE                  0x00000040
#define LINEDEVSTATE_OUTOFSERVICE               0x00000080
#define LINEDEVSTATE_MAINTENANCE                0x00000100
#define LINEDEVSTATE_OPEN                       0x00000200
#define LINEDEVSTATE_CLOSE                      0x00000400
#define LINEDEVSTATE_NUMCALLS                   0x00000800
#define LINEDEVSTATE_NUMCOMPLETIONS             0x00001000
#define LINEDEVSTATE_TERMINALS                  0x00002000
#define LINEDEVSTATE_ROAMMODE                   0x00004000
#define LINEDEVSTATE_BATTERY                    0x00008000
#define LINEDEVSTATE_SIGNAL                     0x00010000
#define LINEDEVSTATE_DEVSPECIFIC                0x00020000
#define LINEDEVSTATE_REINIT                     0x00040000
#define LINEDEVSTATE_LOCK                       0x00080000
#define LINEDEVSTATE_CAPSCHANGE                 0x00100000      // TAPI v1.4
#define LINEDEVSTATE_CONFIGCHANGE               0x00200000      // TAPI v1.4
#define LINEDEVSTATE_TRANSLATECHANGE            0x00400000      // TAPI v1.4
#define LINEDEVSTATE_COMPLCANCEL                0x00800000      // TAPI v1.4
#define LINEDEVSTATE_REMOVED                    0x01000000      // TAPI v1.4

#define LINEDEVSTATUSFLAGS_CONNECTED            0x00000001
#define LINEDEVSTATUSFLAGS_MSGWAIT              0x00000002
#define LINEDEVSTATUSFLAGS_INSERVICE            0x00000004
#define LINEDEVSTATUSFLAGS_LOCKED               0x00000008

#define LINEDIALTONEMODE_NORMAL                 0x00000001
#define LINEDIALTONEMODE_SPECIAL                0x00000002
#define LINEDIALTONEMODE_INTERNAL               0x00000004
#define LINEDIALTONEMODE_EXTERNAL               0x00000008
#define LINEDIALTONEMODE_UNKNOWN                0x00000010
#define LINEDIALTONEMODE_UNAVAIL                0x00000020

#define LINEDIGITMODE_PULSE                     0x00000001
#define LINEDIGITMODE_DTMF                      0x00000002
#define LINEDIGITMODE_DTMFEND                   0x00000004

#define LINEDISCONNECTMODE_NORMAL               0x00000001
#define LINEDISCONNECTMODE_UNKNOWN              0x00000002
#define LINEDISCONNECTMODE_REJECT               0x00000004
#define LINEDISCONNECTMODE_PICKUP               0x00000008
#define LINEDISCONNECTMODE_FORWARDED            0x00000010
#define LINEDISCONNECTMODE_BUSY                 0x00000020
#define LINEDISCONNECTMODE_NOANSWER             0x00000040
#define LINEDISCONNECTMODE_BADADDRESS           0x00000080
#define LINEDISCONNECTMODE_UNREACHABLE          0x00000100
#define LINEDISCONNECTMODE_CONGESTION           0x00000200
#define LINEDISCONNECTMODE_INCOMPATIBLE         0x00000400
#define LINEDISCONNECTMODE_UNAVAIL              0x00000800
#define LINEDISCONNECTMODE_NODIALTONE           0x00001000      // TAPI v1.4
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINEDISCONNECTMODE_NUMBERCHANGED        0x00002000      // TAPI v2.0
#define LINEDISCONNECTMODE_OUTOFORDER           0x00004000      // TAPI v2.0
#define LINEDISCONNECTMODE_TEMPFAILURE          0x00008000      // TAPI v2.0
#define LINEDISCONNECTMODE_QOSUNAVAIL           0x00010000      // TAPI v2.0
#define LINEDISCONNECTMODE_BLOCKED              0x00020000      // TAPI v2.0
#define LINEDISCONNECTMODE_DONOTDISTURB         0x00040000      // TAPI v2.0
#define LINEDISCONNECTMODE_CANCELLED            0x00080000      // TAPI v2.0
#endif

#define LINEERR_ALLOCATED                       0x80000001
#define LINEERR_BADDEVICEID                     0x80000002
#define LINEERR_BEARERMODEUNAVAIL               0x80000003
#define LINEERR_CALLUNAVAIL                     0x80000005
#define LINEERR_COMPLETIONOVERRUN               0x80000006
#define LINEERR_CONFERENCEFULL                  0x80000007
#define LINEERR_DIALBILLING                     0x80000008
#define LINEERR_DIALDIALTONE                    0x80000009
#define LINEERR_DIALPROMPT                      0x8000000A
#define LINEERR_DIALQUIET                       0x8000000B
#define LINEERR_INCOMPATIBLEAPIVERSION          0x8000000C
#define LINEERR_INCOMPATIBLEEXTVERSION          0x8000000D
#define LINEERR_INIFILECORRUPT                  0x8000000E
#define LINEERR_INUSE                           0x8000000F
#define LINEERR_INVALADDRESS                    0x80000010
#define LINEERR_INVALADDRESSID                  0x80000011
#define LINEERR_INVALADDRESSMODE                0x80000012
#define LINEERR_INVALADDRESSSTATE               0x80000013
#define LINEERR_INVALAPPHANDLE                  0x80000014
#define LINEERR_INVALAPPNAME                    0x80000015
#define LINEERR_INVALBEARERMODE                 0x80000016
#define LINEERR_INVALCALLCOMPLMODE              0x80000017
#define LINEERR_INVALCALLHANDLE                 0x80000018
#define LINEERR_INVALCALLPARAMS                 0x80000019
#define LINEERR_INVALCALLPRIVILEGE              0x8000001A
#define LINEERR_INVALCALLSELECT                 0x8000001B
#define LINEERR_INVALCALLSTATE                  0x8000001C
#define LINEERR_INVALCALLSTATELIST              0x8000001D
#define LINEERR_INVALCARD                       0x8000001E
#define LINEERR_INVALCOMPLETIONID               0x8000001F
#define LINEERR_INVALCONFCALLHANDLE             0x80000020
#define LINEERR_INVALCONSULTCALLHANDLE          0x80000021
#define LINEERR_INVALCOUNTRYCODE                0x80000022
#define LINEERR_INVALDEVICECLASS                0x80000023
#define LINEERR_INVALDEVICEHANDLE               0x80000024
#define LINEERR_INVALDIALPARAMS                 0x80000025
#define LINEERR_INVALDIGITLIST                  0x80000026
#define LINEERR_INVALDIGITMODE                  0x80000027
#define LINEERR_INVALDIGITS                     0x80000028
#define LINEERR_INVALEXTVERSION                 0x80000029
#define LINEERR_INVALGROUPID                    0x8000002A
#define LINEERR_INVALLINEHANDLE                 0x8000002B
#define LINEERR_INVALLINESTATE                  0x8000002C
#define LINEERR_INVALLOCATION                   0x8000002D
#define LINEERR_INVALMEDIALIST                  0x8000002E
#define LINEERR_INVALMEDIAMODE                  0x8000002F
#define LINEERR_INVALMESSAGEID                  0x80000030
#define LINEERR_INVALPARAM                      0x80000032
#define LINEERR_INVALPARKID                     0x80000033
#define LINEERR_INVALPARKMODE                   0x80000034
#define LINEERR_INVALPOINTER                    0x80000035
#define LINEERR_INVALPRIVSELECT                 0x80000036
#define LINEERR_INVALRATE                       0x80000037
#define LINEERR_INVALREQUESTMODE                0x80000038
#define LINEERR_INVALTERMINALID                 0x80000039
#define LINEERR_INVALTERMINALMODE               0x8000003A
#define LINEERR_INVALTIMEOUT                    0x8000003B
#define LINEERR_INVALTONE                       0x8000003C
#define LINEERR_INVALTONELIST                   0x8000003D
#define LINEERR_INVALTONEMODE                   0x8000003E
#define LINEERR_INVALTRANSFERMODE               0x8000003F
#define LINEERR_LINEMAPPERFAILED                0x80000040
#define LINEERR_NOCONFERENCE                    0x80000041
#define LINEERR_NODEVICE                        0x80000042
#define LINEERR_NODRIVER                        0x80000043
#define LINEERR_NOMEM                           0x80000044
#define LINEERR_NOREQUEST                       0x80000045
#define LINEERR_NOTOWNER                        0x80000046
#define LINEERR_NOTREGISTERED                   0x80000047
#define LINEERR_OPERATIONFAILED                 0x80000048
#define LINEERR_OPERATIONUNAVAIL                0x80000049
#define LINEERR_RATEUNAVAIL                     0x8000004A
#define LINEERR_RESOURCEUNAVAIL                 0x8000004B
#define LINEERR_REQUESTOVERRUN                  0x8000004C
#define LINEERR_STRUCTURETOOSMALL               0x8000004D
#define LINEERR_TARGETNOTFOUND                  0x8000004E
#define LINEERR_TARGETSELF                      0x8000004F
#define LINEERR_UNINITIALIZED                   0x80000050
#define LINEERR_USERUSERINFOTOOBIG              0x80000051
#define LINEERR_REINIT                          0x80000052
#define LINEERR_ADDRESSBLOCKED                  0x80000053
#define LINEERR_BILLINGREJECTED                 0x80000054
#define LINEERR_INVALFEATURE                    0x80000055
#define LINEERR_NOMULTIPLEINSTANCE              0x80000056
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINEERR_INVALAGENTID                    0x80000057      // TAPI v2.0
#define LINEERR_INVALAGENTGROUP                 0x80000058      // TAPI v2.0
#define LINEERR_INVALPASSWORD                   0x80000059      // TAPI v2.0
#define LINEERR_INVALAGENTSTATE                 0x8000005A      // TAPI v2.0
#define LINEERR_INVALAGENTACTIVITY              0x8000005B      // TAPI v2.0
#define LINEERR_DIALVOICEDETECT                 0x8000005C      // TAPI v2.0
#endif
#if (TAPI_CURRENT_VERSION >= 0x00020002)
#define LINEERR_USERCANCELLED                   0x8000005D      // TAPI v2.2
#endif
#if (TAPI_CURRENT_VERSION >= 0x00030000)
#define LINEERR_INVALADDRESSTYPE                0x8000005E      // TAPI v3.0
#endif
#if (TAPI_CURRENT_VERSION >= 0x00020002)
#define LINEERR_INVALAGENTSESSIONSTATE          0x8000005F      // TAPI v2.2
#define LINEERR_DISCONNECTED                    0X80000060
#define LINEERR_SERVICE_NOT_RUNNING             0x80000061
#endif

#define LINEFEATURE_DEVSPECIFIC                 0x00000001
#define LINEFEATURE_DEVSPECIFICFEAT             0x00000002
#define LINEFEATURE_FORWARD                     0x00000004
#define LINEFEATURE_MAKECALL                    0x00000008
#define LINEFEATURE_SETMEDIACONTROL             0x00000010
#define LINEFEATURE_SETTERMINAL                 0x00000020
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINEFEATURE_SETDEVSTATUS                0x00000040      // TAPI v2.0
#define LINEFEATURE_FORWARDFWD                  0x00000080      // TAPI v2.0
#define LINEFEATURE_FORWARDDND                  0x00000100      // TAPI v2.0
#endif

#define LINEFORWARDMODE_UNCOND                  0x00000001
#define LINEFORWARDMODE_UNCONDINTERNAL          0x00000002
#define LINEFORWARDMODE_UNCONDEXTERNAL          0x00000004
#define LINEFORWARDMODE_UNCONDSPECIFIC          0x00000008
#define LINEFORWARDMODE_BUSY                    0x00000010
#define LINEFORWARDMODE_BUSYINTERNAL            0x00000020
#define LINEFORWARDMODE_BUSYEXTERNAL            0x00000040
#define LINEFORWARDMODE_BUSYSPECIFIC            0x00000080
#define LINEFORWARDMODE_NOANSW                  0x00000100
#define LINEFORWARDMODE_NOANSWINTERNAL          0x00000200
#define LINEFORWARDMODE_NOANSWEXTERNAL          0x00000400
#define LINEFORWARDMODE_NOANSWSPECIFIC          0x00000800
#define LINEFORWARDMODE_BUSYNA                  0x00001000
#define LINEFORWARDMODE_BUSYNAINTERNAL          0x00002000
#define LINEFORWARDMODE_BUSYNAEXTERNAL          0x00004000
#define LINEFORWARDMODE_BUSYNASPECIFIC          0x00008000
#define LINEFORWARDMODE_UNKNOWN                 0x00010000      // TAPI v1.4
#define LINEFORWARDMODE_UNAVAIL                 0x00020000      // TAPI v1.4

#define LINEGATHERTERM_BUFFERFULL               0x00000001
#define LINEGATHERTERM_TERMDIGIT                0x00000002
#define LINEGATHERTERM_FIRSTTIMEOUT             0x00000004
#define LINEGATHERTERM_INTERTIMEOUT             0x00000008
#define LINEGATHERTERM_CANCEL                   0x00000010

#define LINEGENERATETERM_DONE                   0x00000001
#define LINEGENERATETERM_CANCEL                 0x00000002

#if (TAPI_CURRENT_VERSION >= 0x00020000)
//
// These constants are mutually exclusive - there's no way to specify more
// than one at a time (and it doesn't make sense, either) so they're
// ordinal rather than bits.
//
#define LINEINITIALIZEEXOPTION_USEHIDDENWINDOW      0x00000001  // TAPI v2.0
#define LINEINITIALIZEEXOPTION_USEEVENT             0x00000002  // TAPI v2.0
#define LINEINITIALIZEEXOPTION_USECOMPLETIONPORT    0x00000003  // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00030000)
#define LINEINITIALIZEEXOPTION_CALLHUBTRACKING      0x80000000  // TAPI v3.0
#endif

#define LINELOCATIONOPTION_PULSEDIAL            0x00000001      // TAPI v1.4

#define LINEMAPPER                              0xFFFFFFFF

#define LINEMEDIACONTROL_NONE                   0x00000001
#define LINEMEDIACONTROL_START                  0x00000002
#define LINEMEDIACONTROL_RESET                  0x00000004
#define LINEMEDIACONTROL_PAUSE                  0x00000008
#define LINEMEDIACONTROL_RESUME                 0x00000010
#define LINEMEDIACONTROL_RATEUP                 0x00000020
#define LINEMEDIACONTROL_RATEDOWN               0x00000040
#define LINEMEDIACONTROL_RATENORMAL             0x00000080
#define LINEMEDIACONTROL_VOLUMEUP               0x00000100
#define LINEMEDIACONTROL_VOLUMEDOWN             0x00000200
#define LINEMEDIACONTROL_VOLUMENORMAL           0x00000400

#define LINEMEDIAMODE_UNKNOWN                   0x00000002
#define LINEMEDIAMODE_INTERACTIVEVOICE          0x00000004
#define LINEMEDIAMODE_AUTOMATEDVOICE            0x00000008
#define LINEMEDIAMODE_DATAMODEM                 0x00000010
#define LINEMEDIAMODE_G3FAX                     0x00000020
#define LINEMEDIAMODE_TDD                       0x00000040
#define LINEMEDIAMODE_G4FAX                     0x00000080
#define LINEMEDIAMODE_DIGITALDATA               0x00000100
#define LINEMEDIAMODE_TELETEX                   0x00000200
#define LINEMEDIAMODE_VIDEOTEX                  0x00000400
#define LINEMEDIAMODE_TELEX                     0x00000800
#define LINEMEDIAMODE_MIXED                     0x00001000
#define LINEMEDIAMODE_ADSI                      0x00002000
#define LINEMEDIAMODE_VOICEVIEW                 0x00004000      // TAPI v1.4
#if (TAPI_CURRENT_VERSION >= 0x00020001)
#define LINEMEDIAMODE_VIDEO                     0x00008000      // TAPI v2.1
#endif
#define LAST_LINEMEDIAMODE                      0x00008000

#define LINEOFFERINGMODE_ACTIVE                 0x00000001      // TAPI v1.4
#define LINEOFFERINGMODE_INACTIVE               0x00000002      // TAPI v1.4

#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINEOPENOPTION_SINGLEADDRESS            0x80000000      // TAPI v2.0
#define LINEOPENOPTION_PROXY                    0x40000000      // TAPI v2.0
#endif

#define LINEPARKMODE_DIRECTED                   0x00000001
#define LINEPARKMODE_NONDIRECTED                0x00000002

#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINEPROXYREQUEST_SETAGENTGROUP          0x00000001      // TAPI v2.0
#define LINEPROXYREQUEST_SETAGENTSTATE          0x00000002      // TAPI v2.0
#define LINEPROXYREQUEST_SETAGENTACTIVITY       0x00000003      // TAPI v2.0
#define LINEPROXYREQUEST_GETAGENTCAPS           0x00000004      // TAPI v2.0
#define LINEPROXYREQUEST_GETAGENTSTATUS         0x00000005      // TAPI v2.0
#define LINEPROXYREQUEST_AGENTSPECIFIC          0x00000006      // TAPI v2.0
#define LINEPROXYREQUEST_GETAGENTACTIVITYLIST   0x00000007      // TAPI v2.0
#define LINEPROXYREQUEST_GETAGENTGROUPLIST      0x00000008      // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020002)
#define LINEPROXYREQUEST_CREATEAGENT                0x00000009  // TAPI v2.2
#define LINEPROXYREQUEST_SETAGENTMEASUREMENTPERIOD  0x0000000A  // TAPI v2.2
#define LINEPROXYREQUEST_GETAGENTINFO               0x0000000B  // TAPI v2.2
#define LINEPROXYREQUEST_CREATEAGENTSESSION         0x0000000C  // TAPI v2.2
#define LINEPROXYREQUEST_GETAGENTSESSIONLIST        0x0000000D  // TAPI v2.2
#define LINEPROXYREQUEST_SETAGENTSESSIONSTATE       0x0000000E  // TAPI v2.2
#define LINEPROXYREQUEST_GETAGENTSESSIONINFO        0x0000000F  // TAPI v2.2
#define LINEPROXYREQUEST_GETQUEUELIST               0x00000010  // TAPI v2.2
#define LINEPROXYREQUEST_SETQUEUEMEASUREMENTPERIOD  0x00000011  // TAPI v2.2
#define LINEPROXYREQUEST_GETQUEUEINFO               0x00000012  // TAPI v2.2
#define LINEPROXYREQUEST_GETGROUPLIST               0x00000013  // TAPI v2.2
#define LINEPROXYREQUEST_SETAGENTSTATEEX            0x00000014  // TAPI v2.2
#endif

#define LINEREMOVEFROMCONF_NONE                 0x00000001
#define LINEREMOVEFROMCONF_LAST                 0x00000002
#define LINEREMOVEFROMCONF_ANY                  0x00000003

#define LINEREQUESTMODE_MAKECALL                0x00000001
#define LINEREQUESTMODE_MEDIACALL               0x00000002
#define LINEREQUESTMODE_DROP                    0x00000004
#define LAST_LINEREQUESTMODE                    LINEREQUESTMODE_MEDIACALL

#define LINEROAMMODE_UNKNOWN                    0x00000001
#define LINEROAMMODE_UNAVAIL                    0x00000002
#define LINEROAMMODE_HOME                       0x00000004
#define LINEROAMMODE_ROAMA                      0x00000008
#define LINEROAMMODE_ROAMB                      0x00000010

#define LINESPECIALINFO_NOCIRCUIT               0x00000001
#define LINESPECIALINFO_CUSTIRREG               0x00000002
#define LINESPECIALINFO_REORDER                 0x00000004
#define LINESPECIALINFO_UNKNOWN                 0x00000008
#define LINESPECIALINFO_UNAVAIL                 0x00000010

#define LINETERMDEV_PHONE                       0x00000001
#define LINETERMDEV_HEADSET                     0x00000002
#define LINETERMDEV_SPEAKER                     0x00000004

#define LINETERMMODE_BUTTONS                    0x00000001
#define LINETERMMODE_LAMPS                      0x00000002
#define LINETERMMODE_DISPLAY                    0x00000004
#define LINETERMMODE_RINGER                     0x00000008
#define LINETERMMODE_HOOKSWITCH                 0x00000010
#define LINETERMMODE_MEDIATOLINE                0x00000020
#define LINETERMMODE_MEDIAFROMLINE              0x00000040
#define LINETERMMODE_MEDIABIDIRECT              0x00000080

#define LINETERMSHARING_PRIVATE                 0x00000001
#define LINETERMSHARING_SHAREDEXCL              0x00000002
#define LINETERMSHARING_SHAREDCONF              0x00000004

#define LINETOLLLISTOPTION_ADD                  0x00000001
#define LINETOLLLISTOPTION_REMOVE               0x00000002

#define LINETONEMODE_CUSTOM                     0x00000001
#define LINETONEMODE_RINGBACK                   0x00000002
#define LINETONEMODE_BUSY                       0x00000004
#define LINETONEMODE_BEEP                       0x00000008
#define LINETONEMODE_BILLING                    0x00000010

#define LINETRANSFERMODE_TRANSFER               0x00000001
#define LINETRANSFERMODE_CONFERENCE             0x00000002

#define LINETRANSLATEOPTION_CARDOVERRIDE        0x00000001
#define LINETRANSLATEOPTION_CANCELCALLWAITING   0x00000002      // TAPI v1.4
#define LINETRANSLATEOPTION_FORCELOCAL          0x00000004      // TAPI v1.4
#define LINETRANSLATEOPTION_FORCELD             0x00000008      // TAPI v1.4

#define LINETRANSLATERESULT_CANONICAL           0x00000001
#define LINETRANSLATERESULT_INTERNATIONAL       0x00000002
#define LINETRANSLATERESULT_LONGDISTANCE        0x00000004
#define LINETRANSLATERESULT_LOCAL               0x00000008
#define LINETRANSLATERESULT_INTOLLLIST          0x00000010
#define LINETRANSLATERESULT_NOTINTOLLLIST       0x00000020
#define LINETRANSLATERESULT_DIALBILLING         0x00000040
#define LINETRANSLATERESULT_DIALQUIET           0x00000080
#define LINETRANSLATERESULT_DIALDIALTONE        0x00000100
#define LINETRANSLATERESULT_DIALPROMPT          0x00000200
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define LINETRANSLATERESULT_VOICEDETECT         0x00000400      // TAPI v2.0
#endif
#if (TAPI_CURRENT_VERSION >= 0x00030000)
#define LINETRANSLATERESULT_NOTRANSLATION       0x00000800      // TAPI v3.0
#endif

#define PHONEBUTTONFUNCTION_UNKNOWN             0x00000000
#define PHONEBUTTONFUNCTION_CONFERENCE          0x00000001
#define PHONEBUTTONFUNCTION_TRANSFER            0x00000002
#define PHONEBUTTONFUNCTION_DROP                0x00000003
#define PHONEBUTTONFUNCTION_HOLD                0x00000004
#define PHONEBUTTONFUNCTION_RECALL              0x00000005
#define PHONEBUTTONFUNCTION_DISCONNECT          0x00000006
#define PHONEBUTTONFUNCTION_CONNECT             0x00000007
#define PHONEBUTTONFUNCTION_MSGWAITON           0x00000008
#define PHONEBUTTONFUNCTION_MSGWAITOFF          0x00000009
#define PHONEBUTTONFUNCTION_SELECTRING          0x0000000A
#define PHONEBUTTONFUNCTION_ABBREVDIAL          0x0000000B
#define PHONEBUTTONFUNCTION_FORWARD             0x0000000C
#define PHONEBUTTONFUNCTION_PICKUP              0x0000000D
#define PHONEBUTTONFUNCTION_RINGAGAIN           0x0000000E
#define PHONEBUTTONFUNCTION_PARK                0x0000000F
#define PHONEBUTTONFUNCTION_REJECT              0x00000010
#define PHONEBUTTONFUNCTION_REDIRECT            0x00000011
#define PHONEBUTTONFUNCTION_MUTE                0x00000012
#define PHONEBUTTONFUNCTION_VOLUMEUP            0x00000013
#define PHONEBUTTONFUNCTION_VOLUMEDOWN          0x00000014
#define PHONEBUTTONFUNCTION_SPEAKERON           0x00000015
#define PHONEBUTTONFUNCTION_SPEAKEROFF          0x00000016
#define PHONEBUTTONFUNCTION_FLASH               0x00000017
#define PHONEBUTTONFUNCTION_DATAON              0x00000018
#define PHONEBUTTONFUNCTION_DATAOFF             0x00000019
#define PHONEBUTTONFUNCTION_DONOTDISTURB        0x0000001A
#define PHONEBUTTONFUNCTION_INTERCOM            0x0000001B
#define PHONEBUTTONFUNCTION_BRIDGEDAPP          0x0000001C
#define PHONEBUTTONFUNCTION_BUSY                0x0000001D
#define PHONEBUTTONFUNCTION_CALLAPP             0x0000001E
#define PHONEBUTTONFUNCTION_DATETIME            0x0000001F
#define PHONEBUTTONFUNCTION_DIRECTORY           0x00000020
#define PHONEBUTTONFUNCTION_COVER               0x00000021
#define PHONEBUTTONFUNCTION_CALLID              0x00000022
#define PHONEBUTTONFUNCTION_LASTNUM             0x00000023
#define PHONEBUTTONFUNCTION_NIGHTSRV            0x00000024
#define PHONEBUTTONFUNCTION_SENDCALLS           0x00000025
#define PHONEBUTTONFUNCTION_MSGINDICATOR        0x00000026
#define PHONEBUTTONFUNCTION_REPDIAL             0x00000027
#define PHONEBUTTONFUNCTION_SETREPDIAL          0x00000028
#define PHONEBUTTONFUNCTION_SYSTEMSPEED         0x00000029
#define PHONEBUTTONFUNCTION_STATIONSPEED        0x0000002A
#define PHONEBUTTONFUNCTION_CAMPON              0x0000002B
#define PHONEBUTTONFUNCTION_SAVEREPEAT          0x0000002C
#define PHONEBUTTONFUNCTION_QUEUECALL           0x0000002D
#define PHONEBUTTONFUNCTION_NONE                0x0000002E
#if (TAPI_CURRENT_VERSION >= 0x00030001)
#define PHONEBUTTONFUNCTION_SEND                0x0000002F      // TAPI v3.1
#endif

#define PHONEBUTTONMODE_DUMMY                   0x00000001
#define PHONEBUTTONMODE_CALL                    0x00000002
#define PHONEBUTTONMODE_FEATURE                 0x00000004
#define PHONEBUTTONMODE_KEYPAD                  0x00000008
#define PHONEBUTTONMODE_LOCAL                   0x00000010
#define PHONEBUTTONMODE_DISPLAY                 0x00000020

#define PHONEBUTTONSTATE_UP                     0x00000001
#define PHONEBUTTONSTATE_DOWN                   0x00000002
#define PHONEBUTTONSTATE_UNKNOWN                0x00000004      // TAPI v1.4
#define PHONEBUTTONSTATE_UNAVAIL                0x00000008      // TAPI v1.4

#define PHONEERR_ALLOCATED                      0x90000001
#define PHONEERR_BADDEVICEID                    0x90000002
#define PHONEERR_INCOMPATIBLEAPIVERSION         0x90000003
#define PHONEERR_INCOMPATIBLEEXTVERSION         0x90000004
#define PHONEERR_INIFILECORRUPT                 0x90000005
#define PHONEERR_INUSE                          0x90000006
#define PHONEERR_INVALAPPHANDLE                 0x90000007
#define PHONEERR_INVALAPPNAME                   0x90000008
#define PHONEERR_INVALBUTTONLAMPID              0x90000009
#define PHONEERR_INVALBUTTONMODE                0x9000000A
#define PHONEERR_INVALBUTTONSTATE               0x9000000B
#define PHONEERR_INVALDATAID                    0x9000000C
#define PHONEERR_INVALDEVICECLASS               0x9000000D
#define PHONEERR_INVALEXTVERSION                0x9000000E
#define PHONEERR_INVALHOOKSWITCHDEV             0x9000000F
#define PHONEERR_INVALHOOKSWITCHMODE            0x90000010
#define PHONEERR_INVALLAMPMODE                  0x90000011
#define PHONEERR_INVALPARAM                     0x90000012
#define PHONEERR_INVALPHONEHANDLE               0x90000013
#define PHONEERR_INVALPHONESTATE                0x90000014
#define PHONEERR_INVALPOINTER                   0x90000015
#define PHONEERR_INVALPRIVILEGE                 0x90000016
#define PHONEERR_INVALRINGMODE                  0x90000017
#define PHONEERR_NODEVICE                       0x90000018
#define PHONEERR_NODRIVER                       0x90000019
#define PHONEERR_NOMEM                          0x9000001A
#define PHONEERR_NOTOWNER                       0x9000001B
#define PHONEERR_OPERATIONFAILED                0x9000001C
#define PHONEERR_OPERATIONUNAVAIL               0x9000001D
#define PHONEERR_RESOURCEUNAVAIL                0x9000001F
#define PHONEERR_REQUESTOVERRUN                 0x90000020
#define PHONEERR_STRUCTURETOOSMALL              0x90000021
#define PHONEERR_UNINITIALIZED                  0x90000022
#define PHONEERR_REINIT                         0x90000023
#define PHONEERR_DISCONNECTED                   0x90000024
#define PHONEERR_SERVICE_NOT_RUNNING            0x90000025

#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define PHONEFEATURE_GETBUTTONINFO              0x00000001      // TAPI v2.0
#define PHONEFEATURE_GETDATA                    0x00000002      // TAPI v2.0
#define PHONEFEATURE_GETDISPLAY                 0x00000004      // TAPI v2.0
#define PHONEFEATURE_GETGAINHANDSET             0x00000008      // TAPI v2.0
#define PHONEFEATURE_GETGAINSPEAKER             0x00000010      // TAPI v2.0
#define PHONEFEATURE_GETGAINHEADSET             0x00000020      // TAPI v2.0
#define PHONEFEATURE_GETHOOKSWITCHHANDSET       0x00000040      // TAPI v2.0
#define PHONEFEATURE_GETHOOKSWITCHSPEAKER       0x00000080      // TAPI v2.0
#define PHONEFEATURE_GETHOOKSWITCHHEADSET       0x00000100      // TAPI v2.0
#define PHONEFEATURE_GETLAMP                    0x00000200      // TAPI v2.0
#define PHONEFEATURE_GETRING                    0x00000400      // TAPI v2.0
#define PHONEFEATURE_GETVOLUMEHANDSET           0x00000800      // TAPI v2.0
#define PHONEFEATURE_GETVOLUMESPEAKER           0x00001000      // TAPI v2.0
#define PHONEFEATURE_GETVOLUMEHEADSET           0x00002000      // TAPI v2.0
#define PHONEFEATURE_SETBUTTONINFO              0x00004000      // TAPI v2.0
#define PHONEFEATURE_SETDATA                    0x00008000      // TAPI v2.0
#define PHONEFEATURE_SETDISPLAY                 0x00010000      // TAPI v2.0
#define PHONEFEATURE_SETGAINHANDSET             0x00020000      // TAPI v2.0
#define PHONEFEATURE_SETGAINSPEAKER             0x00040000      // TAPI v2.0
#define PHONEFEATURE_SETGAINHEADSET             0x00080000      // TAPI v2.0
#define PHONEFEATURE_SETHOOKSWITCHHANDSET       0x00100000      // TAPI v2.0
#define PHONEFEATURE_SETHOOKSWITCHSPEAKER       0x00200000      // TAPI v2.0
#define PHONEFEATURE_SETHOOKSWITCHHEADSET       0x00400000      // TAPI v2.0
#define PHONEFEATURE_SETLAMP                    0x00800000      // TAPI v2.0
#define PHONEFEATURE_SETRING                    0x01000000      // TAPI v2.0
#define PHONEFEATURE_SETVOLUMEHANDSET           0x02000000      // TAPI v2.0
#define PHONEFEATURE_SETVOLUMESPEAKER           0x04000000      // TAPI v2.0
#define PHONEFEATURE_SETVOLUMEHEADSET           0x08000000      // TAPI v2.0
#endif
#if (TAPI_CURRENT_VERSION >= 0x00030001)
#define PHONEFEATURE_GENERICPHONE               0x10000000      // TAPI v3.1
#endif

#define PHONEHOOKSWITCHDEV_HANDSET              0x00000001
#define PHONEHOOKSWITCHDEV_SPEAKER              0x00000002
#define PHONEHOOKSWITCHDEV_HEADSET              0x00000004

#define PHONEHOOKSWITCHMODE_ONHOOK              0x00000001
#define PHONEHOOKSWITCHMODE_MIC                 0x00000002
#define PHONEHOOKSWITCHMODE_SPEAKER             0x00000004
#define PHONEHOOKSWITCHMODE_MICSPEAKER          0x00000008
#define PHONEHOOKSWITCHMODE_UNKNOWN             0x00000010

#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define PHONEINITIALIZEEXOPTION_USEHIDDENWINDOW     0x00000001  // TAPI v2.0
#define PHONEINITIALIZEEXOPTION_USEEVENT            0x00000002  // TAPI v2.0
#define PHONEINITIALIZEEXOPTION_USECOMPLETIONPORT   0x00000003  // TAPI v2.0
#endif

#define PHONELAMPMODE_DUMMY                     0x00000001
#define PHONELAMPMODE_OFF                       0x00000002
#define PHONELAMPMODE_STEADY                    0x00000004
#define PHONELAMPMODE_WINK                      0x00000008
#define PHONELAMPMODE_FLASH                     0x00000010
#define PHONELAMPMODE_FLUTTER                   0x00000020
#define PHONELAMPMODE_BROKENFLUTTER             0x00000040
#define PHONELAMPMODE_UNKNOWN                   0x00000080

#define PHONEPRIVILEGE_MONITOR                  0x00000001
#define PHONEPRIVILEGE_OWNER                    0x00000002

#define PHONESTATE_OTHER                        0x00000001
#define PHONESTATE_CONNECTED                    0x00000002
#define PHONESTATE_DISCONNECTED                 0x00000004
#define PHONESTATE_OWNER                        0x00000008
#define PHONESTATE_MONITORS                     0x00000010
#define PHONESTATE_DISPLAY                      0x00000020
#define PHONESTATE_LAMP                         0x00000040
#define PHONESTATE_RINGMODE                     0x00000080
#define PHONESTATE_RINGVOLUME                   0x00000100
#define PHONESTATE_HANDSETHOOKSWITCH            0x00000200
#define PHONESTATE_HANDSETVOLUME                0x00000400
#define PHONESTATE_HANDSETGAIN                  0x00000800
#define PHONESTATE_SPEAKERHOOKSWITCH            0x00001000
#define PHONESTATE_SPEAKERVOLUME                0x00002000
#define PHONESTATE_SPEAKERGAIN                  0x00004000
#define PHONESTATE_HEADSETHOOKSWITCH            0x00008000
#define PHONESTATE_HEADSETVOLUME                0x00010000
#define PHONESTATE_HEADSETGAIN                  0x00020000
#define PHONESTATE_SUSPEND                      0x00040000
#define PHONESTATE_RESUME                       0x00080000
#define PHONESTATE_DEVSPECIFIC                  0x00100000
#define PHONESTATE_REINIT                       0x00200000
#define PHONESTATE_CAPSCHANGE                   0x00400000      // TAPI v1.4
#define PHONESTATE_REMOVED                      0x00800000      // TAPI v1.4

#define PHONESTATUSFLAGS_CONNECTED              0x00000001
#define PHONESTATUSFLAGS_SUSPENDED              0x00000002

#define STRINGFORMAT_ASCII                      0x00000001
#define STRINGFORMAT_DBCS                       0x00000002
#define STRINGFORMAT_UNICODE                    0x00000003
#define STRINGFORMAT_BINARY                     0x00000004

#define TAPI_REPLY                              WM_USER + 99

#define TAPIERR_CONNECTED                       0L
#define TAPIERR_DROPPED                         -1L
#define TAPIERR_NOREQUESTRECIPIENT              -2L
#define TAPIERR_REQUESTQUEUEFULL                -3L
#define TAPIERR_INVALDESTADDRESS                -4L
#define TAPIERR_INVALWINDOWHANDLE               -5L
#define TAPIERR_INVALDEVICECLASS                -6L
#define TAPIERR_INVALDEVICEID                   -7L
#define TAPIERR_DEVICECLASSUNAVAIL              -8L
#define TAPIERR_DEVICEIDUNAVAIL                 -9L
#define TAPIERR_DEVICEINUSE                     -10L
#define TAPIERR_DESTBUSY                        -11L
#define TAPIERR_DESTNOANSWER                    -12L
#define TAPIERR_DESTUNAVAIL                     -13L
#define TAPIERR_UNKNOWNWINHANDLE                -14L
#define TAPIERR_UNKNOWNREQUESTID                -15L
#define TAPIERR_REQUESTFAILED                   -16L
#define TAPIERR_REQUESTCANCELLED                -17L
#define TAPIERR_INVALPOINTER                    -18L
#define TAPIERR_NOTADMIN                        -19L
#define TAPIERR_MMCWRITELOCKED                  -20L
#define TAPIERR_PROVIDERALREADYINSTALLED        -21L
#define TAPIERR_SCP_ALREADY_EXISTS		-22L
#define TAPIERR_SCP_DOES_NOT_EXIST		-23L


#define TAPIMAXDESTADDRESSSIZE                  80L
#define TAPIMAXAPPNAMESIZE                      40L
#define TAPIMAXCALLEDPARTYSIZE                  40L
#define TAPIMAXCOMMENTSIZE                      80L
#define TAPIMAXDEVICECLASSSIZE                  40L
#define TAPIMAXDEVICEIDSIZE                     40L


#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID
{
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
} GUID;

#endif /* GUID_DEFINED */

#ifndef __LPGUID_DEFINED__
#define __LPGUID_DEFINED__
typedef GUID *LPGUID;
#endif

typedef struct lineaddresscaps_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwLineDeviceID;
    DWORD       dwAddressSize;
    DWORD       dwAddressOffset;
    DWORD       dwDevSpecificSize;
    DWORD       dwDevSpecificOffset;
    DWORD       dwAddressSharing;
    DWORD       dwAddressStates;
    DWORD       dwCallInfoStates;
    DWORD       dwCallerIDFlags;
    DWORD       dwCalledIDFlags;
    DWORD       dwConnectedIDFlags;
    DWORD       dwRedirectionIDFlags;
    DWORD       dwRedirectingIDFlags;
    DWORD       dwCallStates;
    DWORD       dwDialToneModes;
    DWORD       dwBusyModes;
    DWORD       dwSpecialInfo;
    DWORD       dwDisconnectModes;
    DWORD       dwMaxNumActiveCalls;
    DWORD       dwMaxNumOnHoldCalls;
    DWORD       dwMaxNumOnHoldPendingCalls;
    DWORD       dwMaxNumConference;
    DWORD       dwMaxNumTransConf;
    DWORD       dwAddrCapFlags;
    DWORD       dwCallFeatures;
    DWORD       dwRemoveFromConfCaps;
    DWORD       dwRemoveFromConfState;
    DWORD       dwTransferModes;
    DWORD       dwParkModes;
    DWORD       dwForwardModes;
    DWORD       dwMaxForwardEntries;
    DWORD       dwMaxSpecificEntries;
    DWORD       dwMinFwdNumRings;
    DWORD       dwMaxFwdNumRings;
    DWORD       dwMaxCallCompletions;
    DWORD       dwCallCompletionConds;
    DWORD       dwCallCompletionModes;
    DWORD       dwNumCompletionMessages;
    DWORD       dwCompletionMsgTextEntrySize;
    DWORD       dwCompletionMsgTextSize;
    DWORD       dwCompletionMsgTextOffset;

    DWORD       dwAddressFeatures;                              // TAPI v1.4

#if (TAPI_CURRENT_VERSION >= 0x00020000)
    DWORD       dwPredictiveAutoTransferStates;                 // TAPI v2.0
    DWORD       dwNumCallTreatments;                            // TAPI v2.0
    DWORD       dwCallTreatmentListSize;                        // TAPI v2.0
    DWORD       dwCallTreatmentListOffset;                      // TAPI v2.0
    DWORD       dwDeviceClassesSize;                            // TAPI v2.0
    DWORD       dwDeviceClassesOffset;                          // TAPI v2.0
    DWORD       dwMaxCallDataSize;                              // TAPI v2.0
    DWORD       dwCallFeatures2;                                // TAPI v2.0
    DWORD       dwMaxNoAnswerTimeout;                           // TAPI v2.0
    DWORD       dwConnectedModes;                               // TAPI v2.0
    DWORD       dwOfferingModes;                                // TAPI v2.0
    DWORD       dwAvailableMediaModes;                          // TAPI v2.0
#endif

} LINEADDRESSCAPS, FAR *LPLINEADDRESSCAPS;

typedef struct lineaddressstatus_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwNumInUse;
    DWORD       dwNumActiveCalls;
    DWORD       dwNumOnHoldCalls;
    DWORD       dwNumOnHoldPendCalls;
    DWORD       dwAddressFeatures;
    DWORD       dwNumRingsNoAnswer;
    DWORD       dwForwardNumEntries;
    DWORD       dwForwardSize;
    DWORD       dwForwardOffset;
    DWORD       dwTerminalModesSize;
    DWORD       dwTerminalModesOffset;
    DWORD       dwDevSpecificSize;
    DWORD       dwDevSpecificOffset;

} LINEADDRESSSTATUS, FAR *LPLINEADDRESSSTATUS;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
typedef struct lineagentactivityentry_tag
{
    DWORD       dwID;                                           // TAPI v2.0
    DWORD       dwNameSize;                                     // TAPI v2.0
    DWORD       dwNameOffset;                                   // TAPI v2.0

} LINEAGENTACTIVITYENTRY, *LPLINEAGENTACTIVITYENTRY;

typedef struct lineagentactivitylist_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.0
    DWORD       dwNeededSize;                                   // TAPI v2.0
    DWORD       dwUsedSize;                                     // TAPI v2.0
    DWORD       dwNumEntries;                                   // TAPI v2.0
    DWORD       dwListSize;                                     // TAPI v2.0
    DWORD       dwListOffset;                                   // TAPI v2.0

} LINEAGENTACTIVITYLIST, *LPLINEAGENTACTIVITYLIST;

typedef struct lineagentcaps_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.0
    DWORD       dwNeededSize;                                   // TAPI v2.0
    DWORD       dwUsedSize;                                     // TAPI v2.0
    DWORD       dwAgentHandlerInfoSize;                         // TAPI v2.0
    DWORD       dwAgentHandlerInfoOffset;                       // TAPI v2.0
    DWORD       dwCapsVersion;                                  // TAPI v2.0
    DWORD       dwFeatures;                                     // TAPI v2.0
    DWORD       dwStates;                                       // TAPI v2.0
    DWORD       dwNextStates;                                   // TAPI v2.0
    DWORD       dwMaxNumGroupEntries;                           // TAPI v2.0
    DWORD       dwAgentStatusMessages;                          // TAPI v2.0
    DWORD       dwNumAgentExtensionIDs;                         // TAPI v2.0
    DWORD       dwAgentExtensionIDListSize;                     // TAPI v2.0
    DWORD       dwAgentExtensionIDListOffset;                   // TAPI v2.0

#if (TAPI_CURRENT_VERSION >= 0x00020002)
    GUID        ProxyGUID;                                      // TAPI v2.2
#endif

} LINEAGENTCAPS, *LPLINEAGENTCAPS;

typedef struct lineagentgroupentry_tag
{
    struct
    {
        DWORD   dwGroupID1;                                     // TAPI v2.0
        DWORD   dwGroupID2;                                     // TAPI v2.0
        DWORD   dwGroupID3;                                     // TAPI v2.0
        DWORD   dwGroupID4;                                     // TAPI v2.0

    } GroupID;

    DWORD       dwNameSize;                                     // TAPI v2.0
    DWORD       dwNameOffset;                                   // TAPI v2.0

} LINEAGENTGROUPENTRY, *LPLINEAGENTGROUPENTRY;

typedef struct lineagentgrouplist_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.0
    DWORD       dwNeededSize;                                   // TAPI v2.0
    DWORD       dwUsedSize;                                     // TAPI v2.0
    DWORD       dwNumEntries;                                   // TAPI v2.0
    DWORD       dwListSize;                                     // TAPI v2.0
    DWORD       dwListOffset;                                   // TAPI v2.0

} LINEAGENTGROUPLIST, *LPLINEAGENTGROUPLIST;

typedef struct lineagentstatus_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.0
    DWORD       dwNeededSize;                                   // TAPI v2.0
    DWORD       dwUsedSize;                                     // TAPI v2.0
    DWORD       dwNumEntries;                                   // TAPI v2.0
    DWORD       dwGroupListSize;                                // TAPI v2.0
    DWORD       dwGroupListOffset;                              // TAPI v2.0
    DWORD       dwState;                                        // TAPI v2.0
    DWORD       dwNextState;                                    // TAPI v2.0
    DWORD       dwActivityID;                                   // TAPI v2.0
    DWORD       dwActivitySize;                                 // TAPI v2.0
    DWORD       dwActivityOffset;                               // TAPI v2.0
    DWORD       dwAgentFeatures;                                // TAPI v2.0
    DWORD       dwValidStates;                                  // TAPI v2.0
    DWORD       dwValidNextStates;                              // TAPI v2.0

} LINEAGENTSTATUS, *LPLINEAGENTSTATUS;

typedef struct lineappinfo_tag
{
    DWORD       dwMachineNameSize;                              // TAPI v2.0
    DWORD       dwMachineNameOffset;                            // TAPI v2.0
    DWORD       dwUserNameSize;                                 // TAPI v2.0
    DWORD       dwUserNameOffset;                               // TAPI v2.0
    DWORD       dwModuleFilenameSize;                           // TAPI v2.0
    DWORD       dwModuleFilenameOffset;                         // TAPI v2.0
    DWORD       dwFriendlyNameSize;                             // TAPI v2.0
    DWORD       dwFriendlyNameOffset;                           // TAPI v2.0
    DWORD       dwMediaModes;                                   // TAPI v2.0
    DWORD       dwAddressID;                                    // TAPI v2.0

} LINEAPPINFO, *LPLINEAPPINFO;
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020002)
typedef struct lineagententry_tag
{
    HAGENT      hAgent;                                         // TAPI v2.2
    DWORD       dwNameSize;                                     // TAPI v2.2
    DWORD       dwNameOffset;                                   // TAPI v2.2
    DWORD       dwIDSize;                                       // TAPI v2.2
    DWORD       dwIDOffset;                                     // TAPI v2.2
    DWORD       dwPINSize;                                      // TAPI v2.2
    DWORD       dwPINOffset;                                    // TAPI v2.2

} LINEAGENTENTRY, *LPLINEAGENTENTRY;

typedef struct lineagentlist_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.2
    DWORD       dwNeededSize;                                   // TAPI v2.2
    DWORD       dwUsedSize;                                     // TAPI v2.2
    DWORD       dwNumEntries;                                   // TAPI v2.2
    DWORD       dwListSize;                                     // TAPI v2.2
    DWORD       dwListOffset;                                   // TAPI v2.2

} LINEAGENTLIST, *LPLINEAGENTLIST;

typedef struct lineagentinfo_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.2
    DWORD       dwNeededSize;                                   // TAPI v2.2
    DWORD       dwUsedSize;                                     // TAPI v2.2
    DWORD       dwAgentState;                                   // TAPI v2.2
    DWORD       dwNextAgentState;                               // TAPI v2.2
    DWORD       dwMeasurementPeriod;                            // TAPI v2.2
    CURRENCY    cyOverallCallRate;                              // TAPI v2.2
    DWORD       dwNumberOfACDCalls;                             // TAPI v2.2
    DWORD       dwNumberOfIncomingCalls;                        // TAPI v2.2
    DWORD       dwNumberOfOutgoingCalls;                        // TAPI v2.2
    DWORD       dwTotalACDTalkTime;                             // TAPI v2.2
    DWORD       dwTotalACDCallTime;                             // TAPI v2.2
    DWORD       dwTotalACDWrapUpTime;                           // TAPI v2.2

} LINEAGENTINFO, *LPLINEAGENTINFO;

typedef struct lineagentsession_tag
{
    HAGENTSESSION   hAgentSession;                              // TAPI v2.2
    HAGENT          hAgent;                                     // TAPI v2.2
    GUID            GroupID;                                    // TAPI v2.2
    DWORD           dwWorkingAddressID;                         // TAPI v2.2

} LINEAGENTSESSIONENTRY  , *LPLINEAGENTSESSIONENTRY;

typedef struct lineagentsessionlist_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.2
    DWORD       dwNeededSize;                                   // TAPI v2.2
    DWORD       dwUsedSize;                                     // TAPI v2.2
    DWORD       dwNumEntries;                                   // TAPI v2.2
    DWORD       dwListSize;                                     // TAPI v2.2
    DWORD       dwListOffset;                                   // TAPI v2.2

} LINEAGENTSESSIONLIST, *LPLINEAGENTSESSIONLIST;

typedef struct lineagentsessioninfo_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.2
    DWORD       dwNeededSize;                                   // TAPI v2.2
    DWORD       dwUsedSize;                                     // TAPI v2.2
    DWORD       dwAgentSessionState;                            // TAPI v2.2
    DWORD       dwNextAgentSessionState;                        // TAPI v2.2
    DATE        dateSessionStartTime;                           // TAPI v2.2
    DWORD       dwSessionDuration;                              // TAPI v2.2
    DWORD       dwNumberOfCalls;                                // TAPI v2.2
    DWORD       dwTotalTalkTime;                                // TAPI v2.2
    DWORD       dwAverageTalkTime;                              // TAPI v2.2
    DWORD       dwTotalCallTime;                                // TAPI v2.2
    DWORD       dwAverageCallTime;                              // TAPI v2.2
    DWORD       dwTotalWrapUpTime;                              // TAPI v2.2
    DWORD       dwAverageWrapUpTime;                            // TAPI v2.2
    CURRENCY    cyACDCallRate;                                  // TAPI v2.2
    DWORD       dwLongestTimeToAnswer;                          // TAPI v2.2
    DWORD       dwAverageTimeToAnswer;                          // TAPI v2.2

} LINEAGENTSESSIONINFO, *LPLINEAGENTSESSIONINFO;

typedef struct linequeueentry_tag
{
    DWORD       dwQueueID;                                      // TAPI v2.2
    DWORD       dwNameSize;                                     // TAPI v2.2
    DWORD       dwNameOffset;                                   // TAPI v2.2

} LINEQUEUEENTRY, *LPLINEQUEUEENTRY;

typedef struct linequeuelist_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.2
    DWORD       dwNeededSize;                                   // TAPI v2.2
    DWORD       dwUsedSize;                                     // TAPI v2.2
    DWORD       dwNumEntries;                                   // TAPI v2.2
    DWORD       dwListSize;                                     // TAPI v2.2
    DWORD       dwListOffset;                                   // TAPI v2.2

} LINEQUEUELIST, *LPLINEQUEUELIST;

typedef struct linequeueinfo_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.2
    DWORD       dwNeededSize;                                   // TAPI v2.2
    DWORD       dwUsedSize;                                     // TAPI v2.2
    DWORD       dwMeasurementPeriod;                            // TAPI v2.2
    DWORD       dwTotalCallsQueued;                             // TAPI v2.2
    DWORD       dwCurrentCallsQueued;                           // TAPI v2.2
    DWORD       dwTotalCallsAbandoned;                          // TAPI v2.2
    DWORD       dwTotalCallsFlowedIn;                           // TAPI v2.2
    DWORD       dwTotalCallsFlowedOut;                          // TAPI v2.2
    DWORD       dwLongestEverWaitTime;                          // TAPI v2.2
    DWORD       dwCurrentLongestWaitTime;                       // TAPI v2.2
    DWORD       dwAverageWaitTime;                              // TAPI v2.2
    DWORD       dwFinalDisposition;                             // TAPI v2.2

} LINEQUEUEINFO, *LPLINEQUEUEINFO;

typedef struct lineproxyrequestlist_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.2
    DWORD       dwNeededSize;                                   // TAPI v2.2
    DWORD       dwUsedSize;                                     // TAPI v2.2
    DWORD       dwNumEntries;                                   // TAPI v2.2
    DWORD       dwListSize;                                     // TAPI v2.2
    DWORD       dwListOffset;                                   // TAPI v2.2

} LINEPROXYREQUESTLIST, *LPLINEPROXYREQUESTLIST;
#endif

#if (TAPI_CURRENT_VERSION >= 0x00030000)
typedef struct linecallhubtrackinginfo_tag
{
    DWORD       dwTotalSize;                                    // TAPI v3.0
    DWORD       dwNeededSize;                                   // TAPI v3.0
    DWORD       dwUsedSize;                                     // TAPI v3.0
    DWORD       dwAvailableTracking;                            // TAPI v3.0
    DWORD       dwCurrentTracking;                              // TAPI v3.0

} LINECALLHUBTRACKINGINFO, FAR *LPLINECALLHUBTRACKINGINFO;
#endif

typedef struct linedialparams_tag
{
    DWORD       dwDialPause;
    DWORD       dwDialSpeed;
    DWORD       dwDigitDuration;
    DWORD       dwWaitForDialtone;

} LINEDIALPARAMS, FAR *LPLINEDIALPARAMS;

typedef struct linecallinfo_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    HLINE       hLine;
    DWORD       dwLineDeviceID;
    DWORD       dwAddressID;
    DWORD       dwBearerMode;
    DWORD       dwRate;
    DWORD       dwMediaMode;
    DWORD       dwAppSpecific;
    DWORD       dwCallID;
    DWORD       dwRelatedCallID;
    DWORD       dwCallParamFlags;
    DWORD       dwCallStates;
    DWORD       dwMonitorDigitModes;
    DWORD       dwMonitorMediaModes;
    LINEDIALPARAMS  DialParams;
    DWORD       dwOrigin;
    DWORD       dwReason;
    DWORD       dwCompletionID;
    DWORD       dwNumOwners;
    DWORD       dwNumMonitors;
    DWORD       dwCountryCode;
    DWORD       dwTrunk;
    DWORD       dwCallerIDFlags;
    DWORD       dwCallerIDSize;
    DWORD       dwCallerIDOffset;
    DWORD       dwCallerIDNameSize;
    DWORD       dwCallerIDNameOffset;
    DWORD       dwCalledIDFlags;
    DWORD       dwCalledIDSize;
    DWORD       dwCalledIDOffset;
    DWORD       dwCalledIDNameSize;
    DWORD       dwCalledIDNameOffset;
    DWORD       dwConnectedIDFlags;
    DWORD       dwConnectedIDSize;
    DWORD       dwConnectedIDOffset;
    DWORD       dwConnectedIDNameSize;
    DWORD       dwConnectedIDNameOffset;
    DWORD       dwRedirectionIDFlags;
    DWORD       dwRedirectionIDSize;
    DWORD       dwRedirectionIDOffset;
    DWORD       dwRedirectionIDNameSize;
    DWORD       dwRedirectionIDNameOffset;
    DWORD       dwRedirectingIDFlags;
    DWORD       dwRedirectingIDSize;
    DWORD       dwRedirectingIDOffset;
    DWORD       dwRedirectingIDNameSize;
    DWORD       dwRedirectingIDNameOffset;
    DWORD       dwAppNameSize;
    DWORD       dwAppNameOffset;
    DWORD       dwDisplayableAddressSize;
    DWORD       dwDisplayableAddressOffset;
    DWORD       dwCalledPartySize;
    DWORD       dwCalledPartyOffset;
    DWORD       dwCommentSize;
    DWORD       dwCommentOffset;
    DWORD       dwDisplaySize;
    DWORD       dwDisplayOffset;
    DWORD       dwUserUserInfoSize;
    DWORD       dwUserUserInfoOffset;
    DWORD       dwHighLevelCompSize;
    DWORD       dwHighLevelCompOffset;
    DWORD       dwLowLevelCompSize;
    DWORD       dwLowLevelCompOffset;
    DWORD       dwChargingInfoSize;
    DWORD       dwChargingInfoOffset;
    DWORD       dwTerminalModesSize;
    DWORD       dwTerminalModesOffset;
    DWORD       dwDevSpecificSize;
    DWORD       dwDevSpecificOffset;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
    DWORD       dwCallTreatment;                                // TAPI v2.0
    DWORD       dwCallDataSize;                                 // TAPI v2.0
    DWORD       dwCallDataOffset;                               // TAPI v2.0
    DWORD       dwSendingFlowspecSize;                          // TAPI v2.0
    DWORD       dwSendingFlowspecOffset;                        // TAPI v2.0
    DWORD       dwReceivingFlowspecSize;                        // TAPI v2.0
    DWORD       dwReceivingFlowspecOffset;                      // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00030000)
    DWORD       dwCallerIDAddressType;                          // TAPI v3.0
    DWORD       dwCalledIDAddressType;                          // TAPI v3.0
    DWORD       dwConnectedIDAddressType;                       // TAPI v3.0
    DWORD       dwRedirectionIDAddressType;                     // TAPI v3.0
    DWORD       dwRedirectingIDAddressType;                     // TAPI v3.0
#endif

} LINECALLINFO, FAR *LPLINECALLINFO;

typedef struct linecalllist_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwCallsNumEntries;
    DWORD       dwCallsSize;
    DWORD       dwCallsOffset;

} LINECALLLIST, FAR *LPLINECALLLIST;

typedef struct linecallparams_tag               // Defaults:
{
    DWORD       dwTotalSize;                    // ---------
    DWORD       dwBearerMode;                   // voice
    DWORD       dwMinRate;                      // (3.1kHz)
    DWORD       dwMaxRate;                      // (3.1kHz)
    DWORD       dwMediaMode;                    // interactiveVoice
    DWORD       dwCallParamFlags;               // 0
    DWORD       dwAddressMode;                  // addressID
    DWORD       dwAddressID;                    // (any available)
    LINEDIALPARAMS  DialParams;                 // (0, 0, 0, 0)
    DWORD       dwOrigAddressSize;              // 0
    DWORD       dwOrigAddressOffset;
    DWORD       dwDisplayableAddressSize;
    DWORD       dwDisplayableAddressOffset;
    DWORD       dwCalledPartySize;              // 0
    DWORD       dwCalledPartyOffset;
    DWORD       dwCommentSize;                  // 0
    DWORD       dwCommentOffset;
    DWORD       dwUserUserInfoSize;             // 0
    DWORD       dwUserUserInfoOffset;
    DWORD       dwHighLevelCompSize;            // 0
    DWORD       dwHighLevelCompOffset;
    DWORD       dwLowLevelCompSize;             // 0
    DWORD       dwLowLevelCompOffset;
    DWORD       dwDevSpecificSize;              // 0
    DWORD       dwDevSpecificOffset;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
    DWORD       dwPredictiveAutoTransferStates;                 // TAPI v2.0
    DWORD       dwTargetAddressSize;                            // TAPI v2.0
    DWORD       dwTargetAddressOffset;                          // TAPI v2.0
    DWORD       dwSendingFlowspecSize;                          // TAPI v2.0
    DWORD       dwSendingFlowspecOffset;                        // TAPI v2.0
    DWORD       dwReceivingFlowspecSize;                        // TAPI v2.0
    DWORD       dwReceivingFlowspecOffset;                      // TAPI v2.0
    DWORD       dwDeviceClassSize;                              // TAPI v2.0
    DWORD       dwDeviceClassOffset;                            // TAPI v2.0
    DWORD       dwDeviceConfigSize;                             // TAPI v2.0
    DWORD       dwDeviceConfigOffset;                           // TAPI v2.0
    DWORD       dwCallDataSize;                                 // TAPI v2.0
    DWORD       dwCallDataOffset;                               // TAPI v2.0
    DWORD       dwNoAnswerTimeout;                              // TAPI v2.0
    DWORD       dwCallingPartyIDSize;                           // TAPI v2.0
    DWORD       dwCallingPartyIDOffset;                         // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00030000)
    DWORD       dwAddressType;                                  // TAPI v3.0
#endif

} LINECALLPARAMS, FAR *LPLINECALLPARAMS;

typedef struct linecallstatus_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwCallState;
    DWORD       dwCallStateMode;
    DWORD       dwCallPrivilege;
    DWORD       dwCallFeatures;
    DWORD       dwDevSpecificSize;
    DWORD       dwDevSpecificOffset;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
    DWORD       dwCallFeatures2;                                // TAPI v2.0
#if WIN32
    SYSTEMTIME  tStateEntryTime;                                // TAPI v2.0
#else
    WORD        tStateEntryTime[8];                             // TAPI v2.0
#endif
#endif

} LINECALLSTATUS, FAR *LPLINECALLSTATUS;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
typedef struct linecalltreatmententry_tag
{
    DWORD       dwCallTreatmentID;                              // TAPI v2.0
    DWORD       dwCallTreatmentNameSize;                        // TAPI v2.0
    DWORD       dwCallTreatmentNameOffset;                      // TAPI v2.0

} LINECALLTREATMENTENTRY, FAR *LPLINECALLTREATMENTENTRY;
#endif

typedef struct linecardentry_tag
{
    DWORD       dwPermanentCardID;
    DWORD       dwCardNameSize;
    DWORD       dwCardNameOffset;
    DWORD       dwCardNumberDigits;                             // TAPI v1.4
    DWORD       dwSameAreaRuleSize;                             // TAPI v1.4
    DWORD       dwSameAreaRuleOffset;                           // TAPI v1.4
    DWORD       dwLongDistanceRuleSize;                         // TAPI v1.4
    DWORD       dwLongDistanceRuleOffset;                       // TAPI v1.4
    DWORD       dwInternationalRuleSize;                        // TAPI v1.4
    DWORD       dwInternationalRuleOffset;                      // TAPI v1.4
    DWORD       dwOptions;                                      // TAPI v1.4

} LINECARDENTRY, FAR *LPLINECARDENTRY;

typedef struct linecountryentry_tag
{
    DWORD       dwCountryID;                                    // TAPI v1.4
    DWORD       dwCountryCode;                                  // TAPI v1.4
    DWORD       dwNextCountryID;                                // TAPI v1.4
    DWORD       dwCountryNameSize;                              // TAPI v1.4
    DWORD       dwCountryNameOffset;                            // TAPI v1.4
    DWORD       dwSameAreaRuleSize;                             // TAPI v1.4
    DWORD       dwSameAreaRuleOffset;                           // TAPI v1.4
    DWORD       dwLongDistanceRuleSize;                         // TAPI v1.4
    DWORD       dwLongDistanceRuleOffset;                       // TAPI v1.4
    DWORD       dwInternationalRuleSize;                        // TAPI v1.4
    DWORD       dwInternationalRuleOffset;                      // TAPI v1.4

} LINECOUNTRYENTRY, FAR *LPLINECOUNTRYENTRY;

typedef struct linecountrylist_tag
{
    DWORD       dwTotalSize;                                    // TAPI v1.4
    DWORD       dwNeededSize;                                   // TAPI v1.4
    DWORD       dwUsedSize;                                     // TAPI v1.4
    DWORD       dwNumCountries;                                 // TAPI v1.4
    DWORD       dwCountryListSize;                              // TAPI v1.4
    DWORD       dwCountryListOffset;                            // TAPI v1.4

} LINECOUNTRYLIST, FAR *LPLINECOUNTRYLIST;

typedef struct linedevcaps_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwProviderInfoSize;
    DWORD       dwProviderInfoOffset;
    DWORD       dwSwitchInfoSize;
    DWORD       dwSwitchInfoOffset;
    DWORD       dwPermanentLineID;
    DWORD       dwLineNameSize;
    DWORD       dwLineNameOffset;
    DWORD       dwStringFormat;
    DWORD       dwAddressModes;
    DWORD       dwNumAddresses;
    DWORD       dwBearerModes;
    DWORD       dwMaxRate;
    DWORD       dwMediaModes;
    DWORD       dwGenerateToneModes;
    DWORD       dwGenerateToneMaxNumFreq;
    DWORD       dwGenerateDigitModes;
    DWORD       dwMonitorToneMaxNumFreq;
    DWORD       dwMonitorToneMaxNumEntries;
    DWORD       dwMonitorDigitModes;
    DWORD       dwGatherDigitsMinTimeout;
    DWORD       dwGatherDigitsMaxTimeout;
    DWORD       dwMedCtlDigitMaxListSize;
    DWORD       dwMedCtlMediaMaxListSize;
    DWORD       dwMedCtlToneMaxListSize;
    DWORD       dwMedCtlCallStateMaxListSize;
    DWORD       dwDevCapFlags;
    DWORD       dwMaxNumActiveCalls;
    DWORD       dwAnswerMode;
    DWORD       dwRingModes;
    DWORD       dwLineStates;
    DWORD       dwUUIAcceptSize;
    DWORD       dwUUIAnswerSize;
    DWORD       dwUUIMakeCallSize;
    DWORD       dwUUIDropSize;
    DWORD       dwUUISendUserUserInfoSize;
    DWORD       dwUUICallInfoSize;
    LINEDIALPARAMS  MinDialParams;
    LINEDIALPARAMS  MaxDialParams;
    LINEDIALPARAMS  DefaultDialParams;
    DWORD       dwNumTerminals;
    DWORD       dwTerminalCapsSize;
    DWORD       dwTerminalCapsOffset;
    DWORD       dwTerminalTextEntrySize;
    DWORD       dwTerminalTextSize;
    DWORD       dwTerminalTextOffset;
    DWORD       dwDevSpecificSize;
    DWORD       dwDevSpecificOffset;

    DWORD       dwLineFeatures;                                 // TAPI v1.4

#if (TAPI_CURRENT_VERSION >= 0x00020000)
    DWORD       dwSettableDevStatus;                            // TAPI v2.0
    DWORD       dwDeviceClassesSize;                            // TAPI v2.0
    DWORD       dwDeviceClassesOffset;                          // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020002)
    GUID        PermanentLineGuid;                              // TAPI v2.2
#endif

#if (TAPI_CURRENT_VERSION >= 0x00030000)
    DWORD       dwAddressTypes;                                 // TAPI v3.0
    GUID        ProtocolGuid;                                   // TAPI v3.0
    DWORD       dwAvailableTracking;                            // TAPI v3.0
#endif

} LINEDEVCAPS, FAR *LPLINEDEVCAPS;

typedef struct linedevstatus_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwNumOpens;
    DWORD       dwOpenMediaModes;
    DWORD       dwNumActiveCalls;
    DWORD       dwNumOnHoldCalls;
    DWORD       dwNumOnHoldPendCalls;
    DWORD       dwLineFeatures;
    DWORD       dwNumCallCompletions;
    DWORD       dwRingMode;
    DWORD       dwSignalLevel;
    DWORD       dwBatteryLevel;
    DWORD       dwRoamMode;
    DWORD       dwDevStatusFlags;
    DWORD       dwTerminalModesSize;
    DWORD       dwTerminalModesOffset;
    DWORD       dwDevSpecificSize;
    DWORD       dwDevSpecificOffset;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
    DWORD       dwAvailableMediaModes;                          // TAPI v2.0
    DWORD       dwAppInfoSize;                                  // TAPI v2.0
    DWORD       dwAppInfoOffset;                                // TAPI v2.0
#endif

} LINEDEVSTATUS, FAR *LPLINEDEVSTATUS;

typedef struct lineextensionid_tag
{
    DWORD       dwExtensionID0;
    DWORD       dwExtensionID1;
    DWORD       dwExtensionID2;
    DWORD       dwExtensionID3;

} LINEEXTENSIONID, FAR *LPLINEEXTENSIONID;

typedef struct lineforward_tag
{
    DWORD       dwForwardMode;
    DWORD       dwCallerAddressSize;
    DWORD       dwCallerAddressOffset;
    DWORD       dwDestCountryCode;
    DWORD       dwDestAddressSize;
    DWORD       dwDestAddressOffset;

#if (TAPI_CURRENT_VERSION >= 0x00030001)
    DWORD       dwCallerAddressType;
    DWORD       dwDestAddressType;
#endif

} LINEFORWARD, FAR *LPLINEFORWARD;

typedef struct lineforwardlist_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNumEntries;
    LINEFORWARD ForwardList[1];

} LINEFORWARDLIST, FAR *LPLINEFORWARDLIST;

typedef struct linegeneratetone_tag
{
    DWORD       dwFrequency;
    DWORD       dwCadenceOn;
    DWORD       dwCadenceOff;
    DWORD       dwVolume;

} LINEGENERATETONE, FAR *LPLINEGENERATETONE;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
typedef struct lineinitializeexparams_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.0
    DWORD       dwNeededSize;                                   // TAPI v2.0
    DWORD       dwUsedSize;                                     // TAPI v2.0
    DWORD       dwOptions;                                      // TAPI v2.0

    union
    {
        HANDLE  hEvent;                                         // TAPI v2.0
        HANDLE  hCompletionPort;                                // TAPI v2.0

    } Handles;

    DWORD       dwCompletionKey;                                // TAPI v2.0

} LINEINITIALIZEEXPARAMS, FAR *LPLINEINITIALIZEEXPARAMS;
#endif

typedef struct linelocationentry_tag
{
    DWORD       dwPermanentLocationID;
    DWORD       dwLocationNameSize;
    DWORD       dwLocationNameOffset;
    DWORD       dwCountryCode;
    DWORD       dwCityCodeSize;
    DWORD       dwCityCodeOffset;
    DWORD       dwPreferredCardID;

    DWORD       dwLocalAccessCodeSize;                          // TAPI v1.4
    DWORD       dwLocalAccessCodeOffset;                        // TAPI v1.4
    DWORD       dwLongDistanceAccessCodeSize;                   // TAPI v1.4
    DWORD       dwLongDistanceAccessCodeOffset;                 // TAPI v1.4
    DWORD       dwTollPrefixListSize;                           // TAPI v1.4
    DWORD       dwTollPrefixListOffset;                         // TAPI v1.4
    DWORD       dwCountryID;                                    // TAPI v1.4
    DWORD       dwOptions;                                      // TAPI v1.4
    DWORD       dwCancelCallWaitingSize;                        // TAPI v1.4
    DWORD       dwCancelCallWaitingOffset;                      // TAPI v1.4

} LINELOCATIONENTRY, FAR *LPLINELOCATIONENTRY;

typedef struct linemediacontrolcallstate_tag
{
    DWORD       dwCallStates;
    DWORD       dwMediaControl;

} LINEMEDIACONTROLCALLSTATE, FAR *LPLINEMEDIACONTROLCALLSTATE;

typedef struct linemediacontroldigit_tag
{
    DWORD       dwDigit;
    DWORD       dwDigitModes;
    DWORD       dwMediaControl;

} LINEMEDIACONTROLDIGIT, FAR *LPLINEMEDIACONTROLDIGIT;

typedef struct linemediacontrolmedia_tag
{
    DWORD       dwMediaModes;
    DWORD       dwDuration;
    DWORD       dwMediaControl;

} LINEMEDIACONTROLMEDIA, FAR *LPLINEMEDIACONTROLMEDIA;

typedef struct linemediacontroltone_tag
{
    DWORD       dwAppSpecific;
    DWORD       dwDuration;
    DWORD       dwFrequency1;
    DWORD       dwFrequency2;
    DWORD       dwFrequency3;
    DWORD       dwMediaControl;

} LINEMEDIACONTROLTONE, FAR *LPLINEMEDIACONTROLTONE;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
typedef struct linemessage_tag
{
    DWORD       hDevice;                                        // TAPI v2.0
    DWORD       dwMessageID;                                    // TAPI v2.0
    DWORD_PTR   dwCallbackInstance;                             // TAPI v2.0
    DWORD_PTR   dwParam1;                                       // TAPI v2.0
    DWORD_PTR   dwParam2;                                       // TAPI v2.0
    DWORD_PTR   dwParam3;                                       // TAPI v2.0

} LINEMESSAGE, FAR *LPLINEMESSAGE;
#endif

typedef struct linemonitortone_tag
{
    DWORD       dwAppSpecific;
    DWORD       dwDuration;
    DWORD       dwFrequency1;
    DWORD       dwFrequency2;
    DWORD       dwFrequency3;

} LINEMONITORTONE, FAR *LPLINEMONITORTONE;

typedef struct lineproviderentry_tag
{
    DWORD       dwPermanentProviderID;                          // TAPI v1.4
    DWORD       dwProviderFilenameSize;                         // TAPI v1.4
    DWORD       dwProviderFilenameOffset;                       // TAPI v1.4

} LINEPROVIDERENTRY, FAR *LPLINEPROVIDERENTRY;

typedef struct lineproviderlist_tag
{
    DWORD       dwTotalSize;                                    // TAPI v1.4
    DWORD       dwNeededSize;                                   // TAPI v1.4
    DWORD       dwUsedSize;                                     // TAPI v1.4
    DWORD       dwNumProviders;                                 // TAPI v1.4
    DWORD       dwProviderListSize;                             // TAPI v1.4
    DWORD       dwProviderListOffset;                           // TAPI v1.4

} LINEPROVIDERLIST, FAR *LPLINEPROVIDERLIST;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
typedef struct lineproxyrequest_tag
{
    DWORD       dwSize;                                         // TAPI v2.0
    DWORD       dwClientMachineNameSize;                        // TAPI v2.0
    DWORD       dwClientMachineNameOffset;                      // TAPI v2.0
    DWORD       dwClientUserNameSize;                           // TAPI v2.0
    DWORD       dwClientUserNameOffset;                         // TAPI v2.0
    DWORD       dwClientAppAPIVersion;                          // TAPI v2.0
    DWORD       dwRequestType;                                  // TAPI v2.0

    union
    {
    struct
    {
        DWORD                   dwAddressID;                    // TAPI v2.0
        LINEAGENTGROUPLIST      GroupList;                      // TAPI v2.0

    } SetAgentGroup;

    struct
    {
        DWORD                   dwAddressID;                    // TAPI v2.0
        DWORD                   dwAgentState;                   // TAPI v2.0
        DWORD                   dwNextAgentState;               // TAPI v2.0

    } SetAgentState;

    struct
    {
        DWORD                   dwAddressID;                    // TAPI v2.0
        DWORD                   dwActivityID;                   // TAPI v2.0

    } SetAgentActivity;

    struct
    {
        DWORD                   dwAddressID;                    // TAPI v2.0
        LINEAGENTCAPS           AgentCaps;                      // TAPI v2.0

    } GetAgentCaps;

    struct
    {
        DWORD                   dwAddressID;                    // TAPI v2.0
        LINEAGENTSTATUS         AgentStatus;                    // TAPI v2.0

    } GetAgentStatus;

    struct
    {
        DWORD                   dwAddressID;                    // TAPI v2.0
        DWORD                   dwAgentExtensionIDIndex;        // TAPI v2.0
        DWORD                   dwSize;                         // TAPI v2.0
        BYTE                    Params[1];                      // TAPI v2.0

    } AgentSpecific;

    struct
    {
        DWORD                   dwAddressID;                    // TAPI v2.0
        LINEAGENTACTIVITYLIST   ActivityList;                   // TAPI v2.0

    } GetAgentActivityList;

    struct
    {
        DWORD                   dwAddressID;                    // TAPI v2.0
        LINEAGENTGROUPLIST      GroupList;                      // TAPI v2.0

    } GetAgentGroupList;

#if (TAPI_CURRENT_VERSION >= 0x00020002)

    struct
    {
        HAGENT                  hAgent;                         // TAPI v2.2
        DWORD                   dwAgentIDSize;                  // TAPI v2.2
        DWORD                   dwAgentIDOffset;                // TAPI v2.2
        DWORD                   dwAgentPINSize;                 // TAPI v2.2
        DWORD                   dwAgentPINOffset;

    } CreateAgent;

    struct
    {
        HAGENT                  hAgent;                         // TAPI v2.2
        DWORD                   dwAgentState;                   // TAPI v2.2
        DWORD                   dwNextAgentState;               // TAPI v2.2

    } SetAgentStateEx;

    struct
    {
        HAGENT                  hAgent;                         // TAPI v2.2
        DWORD                   dwMeasurementPeriod;            // TAPI v2.2

    } SetAgentMeasurementPeriod;

    struct
    {
        HAGENT                  hAgent;                         // TAPI v2.2
        LINEAGENTINFO           AgentInfo;                      // TAPI v2.2

    } GetAgentInfo;

    struct
    {
        HAGENTSESSION           hAgentSession;                  // TAPI v2.2
        DWORD                   dwAgentPINSize;
        DWORD                   dwAgentPINOffset;
        HAGENT                  hAgent;                         // TAPI v2.2
        GUID                    GroupID;                        // TAPI v2.2
        DWORD                   dwWorkingAddressID;             // TAPI v2.2

    } CreateAgentSession;

    struct
    {
        HAGENT                  hAgent;                         // TAPI v2.2
        LINEAGENTSESSIONLIST    SessionList;                    // TAPI v2.2

    } GetAgentSessionList;

    struct
    {
        HAGENTSESSION           hAgentSession;                  // TAPI v2.2
        LINEAGENTSESSIONINFO    SessionInfo;                    // TAPI v2.2

    } GetAgentSessionInfo;

    struct
    {
        HAGENTSESSION           hAgentSession;                  // TAPI v2.2
        DWORD                   dwAgentSessionState;            // TAPI v2.2
        DWORD                   dwNextAgentSessionState;        // TAPI v2.2

    } SetAgentSessionState;

    struct
    {
        GUID                    GroupID;                        // TAPI v2.2
        LINEQUEUELIST           QueueList;                      // TAPI v2.2

    } GetQueueList;

    struct
    {
        DWORD                   dwQueueID;                      // TAPI v2.2
        DWORD                   dwMeasurementPeriod;            // TAPI v2.2

    } SetQueueMeasurementPeriod;


    struct
    {
        DWORD                   dwQueueID;                      // TAPI v2.2
        LINEQUEUEINFO           QueueInfo;                      // TAPI v2.2

    } GetQueueInfo;

    struct
    {
        LINEAGENTGROUPLIST      GroupList;                      // TAPI v2.2

    } GetGroupList;

#endif

    }; //ProxyRequestType;


} LINEPROXYREQUEST, *LPLINEPROXYREQUEST;
#endif

typedef struct linereqmakecall_tag
{
    char        szDestAddress[TAPIMAXDESTADDRESSSIZE];
    char        szAppName[TAPIMAXAPPNAMESIZE];
    char        szCalledParty[TAPIMAXCALLEDPARTYSIZE];
    char        szComment[TAPIMAXCOMMENTSIZE];

} LINEREQMAKECALL, FAR *LPLINEREQMAKECALL;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
typedef struct linereqmakecallW_tag
{
    WCHAR       szDestAddress[TAPIMAXDESTADDRESSSIZE];
    WCHAR       szAppName[TAPIMAXAPPNAMESIZE];
    WCHAR       szCalledParty[TAPIMAXCALLEDPARTYSIZE];
    WCHAR       szComment[TAPIMAXCOMMENTSIZE];

} LINEREQMAKECALLW, FAR *LPLINEREQMAKECALLW;
#endif

#ifdef UNICODE
#define LINEREQMAKECALL LINEREQMAKECALLW
#endif

typedef struct linereqmediacall_tag
{
    HWND        hWnd;
    WPARAM      wRequestID;
    char        szDeviceClass[TAPIMAXDEVICECLASSSIZE];
    unsigned char   ucDeviceID[TAPIMAXDEVICEIDSIZE];
    DWORD       dwSize;
    DWORD       dwSecure;
    char        szDestAddress[TAPIMAXDESTADDRESSSIZE];
    char        szAppName[TAPIMAXAPPNAMESIZE];
    char        szCalledParty[TAPIMAXCALLEDPARTYSIZE];
    char        szComment[TAPIMAXCOMMENTSIZE];

} LINEREQMEDIACALL, FAR *LPLINEREQMEDIACALL;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
typedef struct linereqmediacallW_tag
{
    HWND        hWnd;
    WPARAM      wRequestID;
    WCHAR       szDeviceClass[TAPIMAXDEVICECLASSSIZE];
    unsigned char   ucDeviceID[TAPIMAXDEVICEIDSIZE];
    DWORD       dwSize;
    DWORD       dwSecure;
    WCHAR       szDestAddress[TAPIMAXDESTADDRESSSIZE];
    WCHAR       szAppName[TAPIMAXAPPNAMESIZE];
    WCHAR       szCalledParty[TAPIMAXCALLEDPARTYSIZE];
    WCHAR       szComment[TAPIMAXCOMMENTSIZE];

} LINEREQMEDIACALLW, FAR *LPLINEREQMEDIACALLW;
#endif

#ifdef UNICODE
#define LINEREQMEDIACALL LINEREQMEDIACALLW
#endif

typedef struct linetermcaps_tag
{
    DWORD       dwTermDev;
    DWORD       dwTermModes;
    DWORD       dwTermSharing;

} LINETERMCAPS, FAR *LPLINETERMCAPS;

typedef struct linetranslatecaps_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwNumLocations;
    DWORD       dwLocationListSize;
    DWORD       dwLocationListOffset;
    DWORD       dwCurrentLocationID;
    DWORD       dwNumCards;
    DWORD       dwCardListSize;
    DWORD       dwCardListOffset;
    DWORD       dwCurrentPreferredCardID;

} LINETRANSLATECAPS, FAR *LPLINETRANSLATECAPS;

typedef struct linetranslateoutput_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwDialableStringSize;
    DWORD       dwDialableStringOffset;
    DWORD       dwDisplayableStringSize;
    DWORD       dwDisplayableStringOffset;
    DWORD       dwCurrentCountry;
    DWORD       dwDestCountry;
    DWORD       dwTranslateResults;

} LINETRANSLATEOUTPUT, FAR *LPLINETRANSLATEOUTPUT;

typedef struct phonebuttoninfo_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwButtonMode;
    DWORD       dwButtonFunction;
    DWORD       dwButtonTextSize;
    DWORD       dwButtonTextOffset;
    DWORD       dwDevSpecificSize;
    DWORD       dwDevSpecificOffset;

    DWORD       dwButtonState;                                  // TAPI v1.4

} PHONEBUTTONINFO, FAR *LPPHONEBUTTONINFO;

typedef struct phonecaps_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwProviderInfoSize;
    DWORD       dwProviderInfoOffset;
    DWORD       dwPhoneInfoSize;
    DWORD       dwPhoneInfoOffset;
    DWORD       dwPermanentPhoneID;
    DWORD       dwPhoneNameSize;
    DWORD       dwPhoneNameOffset;
    DWORD       dwStringFormat;
    DWORD       dwPhoneStates;
    DWORD       dwHookSwitchDevs;
    DWORD       dwHandsetHookSwitchModes;
    DWORD       dwSpeakerHookSwitchModes;
    DWORD       dwHeadsetHookSwitchModes;
    DWORD       dwVolumeFlags;
    DWORD       dwGainFlags;
    DWORD       dwDisplayNumRows;
    DWORD       dwDisplayNumColumns;
    DWORD       dwNumRingModes;
    DWORD       dwNumButtonLamps;
    DWORD       dwButtonModesSize;
    DWORD       dwButtonModesOffset;
    DWORD       dwButtonFunctionsSize;
    DWORD       dwButtonFunctionsOffset;
    DWORD       dwLampModesSize;
    DWORD       dwLampModesOffset;
    DWORD       dwNumSetData;
    DWORD       dwSetDataSize;
    DWORD       dwSetDataOffset;
    DWORD       dwNumGetData;
    DWORD       dwGetDataSize;
    DWORD       dwGetDataOffset;
    DWORD       dwDevSpecificSize;
    DWORD       dwDevSpecificOffset;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
    DWORD       dwDeviceClassesSize;                            // TAPI v2.0
    DWORD       dwDeviceClassesOffset;                          // TAPI v2.0
    DWORD       dwPhoneFeatures;                                // TAPI v2.0
    DWORD       dwSettableHandsetHookSwitchModes;               // TAPI v2.0
    DWORD       dwSettableSpeakerHookSwitchModes;               // TAPI v2.0
    DWORD       dwSettableHeadsetHookSwitchModes;               // TAPI v2.0
    DWORD       dwMonitoredHandsetHookSwitchModes;              // TAPI v2.0
    DWORD       dwMonitoredSpeakerHookSwitchModes;              // TAPI v2.0
    DWORD       dwMonitoredHeadsetHookSwitchModes;              // TAPI v2.0
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020002)
    GUID        PermanentPhoneGuid;                             // TAPI v2.2
#endif

} PHONECAPS, FAR *LPPHONECAPS;

typedef struct phoneextensionid_tag
{
    DWORD       dwExtensionID0;
    DWORD       dwExtensionID1;
    DWORD       dwExtensionID2;
    DWORD       dwExtensionID3;

} PHONEEXTENSIONID, FAR *LPPHONEEXTENSIONID;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
typedef struct phoneinitializeexparams_tag
{
    DWORD       dwTotalSize;                                    // TAPI v2.0
    DWORD       dwNeededSize;                                   // TAPI v2.0
    DWORD       dwUsedSize;                                     // TAPI v2.0
    DWORD       dwOptions;                                      // TAPI v2.0

    union
    {
        HANDLE  hEvent;                                         // TAPI v2.0
        HANDLE  hCompletionPort;                                // TAPI v2.0

    } Handles;

    DWORD       dwCompletionKey;                                // TAPI v2.0

} PHONEINITIALIZEEXPARAMS, FAR *LPPHONEINITIALIZEEXPARAMS;

typedef struct phonemessage_tag
{
    DWORD       hDevice;                                        // TAPI v2.0
    DWORD       dwMessageID;                                    // TAPI v2.0
    DWORD_PTR   dwCallbackInstance;                             // TAPI v2.0
    DWORD_PTR   dwParam1;                                       // TAPI v2.0
    DWORD_PTR   dwParam2;                                       // TAPI v2.0
    DWORD_PTR   dwParam3;                                       // TAPI v2.0

} PHONEMESSAGE, FAR *LPPHONEMESSAGE;
#endif

typedef struct phonestatus_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwStatusFlags;
    DWORD       dwNumOwners;
    DWORD       dwNumMonitors;
    DWORD       dwRingMode;
    DWORD       dwRingVolume;
    DWORD       dwHandsetHookSwitchMode;
    DWORD       dwHandsetVolume;
    DWORD       dwHandsetGain;
    DWORD       dwSpeakerHookSwitchMode;
    DWORD       dwSpeakerVolume;
    DWORD       dwSpeakerGain;
    DWORD       dwHeadsetHookSwitchMode;
    DWORD       dwHeadsetVolume;
    DWORD       dwHeadsetGain;
    DWORD       dwDisplaySize;
    DWORD       dwDisplayOffset;
    DWORD       dwLampModesSize;
    DWORD       dwLampModesOffset;
    DWORD       dwOwnerNameSize;
    DWORD       dwOwnerNameOffset;
    DWORD       dwDevSpecificSize;
    DWORD       dwDevSpecificOffset;

#if (TAPI_CURRENT_VERSION >= 0x00020000)
    DWORD       dwPhoneFeatures;                                // TAPI v2.0
#endif

} PHONESTATUS, FAR *LPPHONESTATUS;

typedef struct varstring_tag
{
    DWORD       dwTotalSize;
    DWORD       dwNeededSize;
    DWORD       dwUsedSize;
    DWORD       dwStringFormat;
    DWORD       dwStringSize;
    DWORD       dwStringOffset;

} VARSTRING, FAR *LPVARSTRING;



LONG
WINAPI
lineAccept(
    HCALL               hCall,
    LPCSTR              lpsUserUserInfo,
    DWORD               dwSize
    );

LONG
WINAPI
lineAddProvider(                                                // TAPI v1.4
    LPCSTR              lpszProviderFilename,
    HWND                hwndOwner,
    LPDWORD             lpdwPermanentProviderID
    );

#if WIN32
LONG
WINAPI
lineAddProviderA(                                               // TAPI v1.4
    LPCSTR              lpszProviderFilename,
    HWND                hwndOwner,
    LPDWORD             lpdwPermanentProviderID
    );

LONG
WINAPI
lineAddProviderW(
    LPCWSTR             lpszProviderFilename,
    HWND                hwndOwner,
    LPDWORD             lpdwPermanentProviderID
    );

#ifdef UNICODE
#define lineAddProvider lineAddProviderW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineAddProvider lineAddProviderA
#endif
#endif

#endif


LONG
WINAPI
lineAddToConference(
    HCALL               hConfCall,
    HCALL               hConsultCall
    );

#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
lineAgentSpecific(                                              // TAPI v2.0
    HLINE               hLine,
    DWORD               dwAddressID,
    DWORD               dwAgentExtensionIDIndex,
    LPVOID              lpParams,
    DWORD               dwSize
    );
#endif

LONG
WINAPI
lineAnswer(
    HCALL               hCall,
    LPCSTR              lpsUserUserInfo,
    DWORD               dwSize
    );

LONG
WINAPI
lineBlindTransfer(
    HCALL               hCall,
    LPCSTR              lpszDestAddress,
    DWORD               dwCountryCode
    );

#if WIN32
LONG
WINAPI
lineBlindTransferA(
    HCALL               hCall,
    LPCSTR              lpszDestAddress,
    DWORD               dwCountryCode
    );

LONG
WINAPI
lineBlindTransferW(
    HCALL               hCall,
    LPCWSTR             lpszDestAddressW,
    DWORD               dwCountryCode
    );

#ifdef UNICODE
#define lineBlindTransfer lineBlindTransferW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineBlindTransfer lineBlindTransferA
#endif
#endif
#endif

LONG
WINAPI
lineClose(
    HLINE               hLine
    );

LONG
WINAPI
lineCompleteCall(
    HCALL               hCall,
    LPDWORD             lpdwCompletionID,
    DWORD               dwCompletionMode,
    DWORD               dwMessageID
    );

LONG
WINAPI
lineCompleteTransfer(
    HCALL               hCall,
    HCALL               hConsultCall,
    LPHCALL             lphConfCall,
    DWORD               dwTransferMode
    );

LONG
WINAPI
lineConfigDialog(
    DWORD               dwDeviceID,
    HWND                hwndOwner,
    LPCSTR              lpszDeviceClass
    );

#if WIN32
LONG
WINAPI
lineConfigDialogA(
    DWORD               dwDeviceID,
    HWND                hwndOwner,
    LPCSTR              lpszDeviceClass
    );

LONG
WINAPI
lineConfigDialogW(
    DWORD               dwDeviceID,
    HWND                hwndOwner,
    LPCWSTR             lpszDeviceClass
    );

#ifdef UNICODE
#define lineConfigDialog lineConfigDialogW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineConfigDialog lineConfigDialogA
#endif
#endif
#endif

LONG
WINAPI
lineConfigDialogEdit(                                           // TAPI v1.4
    DWORD               dwDeviceID,
    HWND                hwndOwner,
    LPCSTR              lpszDeviceClass,
    LPVOID              const lpDeviceConfigIn,
    DWORD               dwSize,
    LPVARSTRING         lpDeviceConfigOut
    );

#if WIN32
LONG
WINAPI
lineConfigDialogEditA(                                          // TAPI v1.4
    DWORD               dwDeviceID,
    HWND                hwndOwner,
    LPCSTR              lpszDeviceClass,
    LPVOID              const lpDeviceConfigIn,
    DWORD               dwSize,
    LPVARSTRING         lpDeviceConfigOut
    );

LONG
WINAPI
lineConfigDialogEditW(
    DWORD               dwDeviceID,
    HWND                hwndOwner,
    LPCWSTR             lpszDeviceClass,
    LPVOID              const lpDeviceConfigIn,
    DWORD               dwSize,
    LPVARSTRING         lpDeviceConfigOut
    );

#ifdef UNICODE
#define lineConfigDialogEdit lineConfigDialogEditW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineConfigDialogEdit lineConfigDialogEditA
#endif
#endif
#endif

LONG
WINAPI
lineConfigProvider(                                             // TAPI v1.4
    HWND                hwndOwner,
    DWORD               dwPermanentProviderID
    );

#if (TAPI_CURRENT_VERSION >= 0x00020002)
LONG
WINAPI
lineCreateAgentW(                                               // TAPI v2.2
    HLINE               hLine,
    LPWSTR              lpszAgentID,
    LPWSTR              lpszAgentPIN,
    LPHAGENT            lphAgent
    );

LONG
WINAPI
lineCreateAgentA(                                               // TAPI v2.2
    HLINE               hLine,
    LPSTR               lpszAgentID,
    LPSTR               lpszAgentPIN,
    LPHAGENT            lphAgent
    );

#ifdef UNICODE
#define lineCreateAgent lineCreateAgentW
#else
#define lineCreateAgent lineCreateAgentA
#endif

LONG
WINAPI
lineCreateAgentSessionW(                                        // TAPI v2.2
    HLINE               hLine,
    HAGENT              hAgent,
    LPWSTR              lpszAgentPIN,
    DWORD               dwWorkingAddressID,
    LPGUID              lpGroupID,
    LPHAGENTSESSION     lphAgentSession
    );

LONG
WINAPI
lineCreateAgentSessionA(                                        // TAPI v2.2
    HLINE               hLine,
    HAGENT              hAgent,
    LPSTR               lpszAgentPIN,
    DWORD               dwWorkingAddressID,
    LPGUID              lpGroupID,
    LPHAGENTSESSION     lphAgentSession
    );

#ifdef UNICODE
#define lineCreateAgent lineCreateAgentW
#else
#define lineCreateAgent lineCreateAgentA
#endif
#endif

LONG
WINAPI
lineDeallocateCall(
    HCALL               hCall
    );

LONG
WINAPI
lineDevSpecific(
    HLINE               hLine,
    DWORD               dwAddressID,
    HCALL               hCall,
    LPVOID              lpParams,
    DWORD               dwSize
    );

LONG
WINAPI
lineDevSpecificFeature(
    HLINE               hLine,
    DWORD               dwFeature,
    LPVOID              lpParams,
    DWORD               dwSize
    );

LONG
WINAPI
lineDial(
    HCALL               hCall,
    LPCSTR              lpszDestAddress,
    DWORD               dwCountryCode
    );

#if WIN32
LONG
WINAPI
lineDialA(
    HCALL               hCall,
    LPCSTR              lpszDestAddress,
    DWORD               dwCountryCode
    );

LONG
WINAPI
lineDialW(
    HCALL               hCall,
    LPCWSTR             lpszDestAddress,
    DWORD               dwCountryCode
    );

#ifdef UNICODE
#define lineDial lineDialW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineDial lineDialA
#endif
#endif
#endif

LONG
WINAPI
lineDrop(
    HCALL               hCall,
    LPCSTR              lpsUserUserInfo,
    DWORD               dwSize
    );

LONG
WINAPI
lineForward(
    HLINE               hLine,
    DWORD               bAllAddresses,
    DWORD               dwAddressID,
    LPLINEFORWARDLIST   const lpForwardList,
    DWORD               dwNumRingsNoAnswer,
    LPHCALL             lphConsultCall,
    LPLINECALLPARAMS    const lpCallParams
    );

#if WIN32
LONG
WINAPI
lineForwardA(
    HLINE               hLine,
    DWORD               bAllAddresses,
    DWORD               dwAddressID,
    LPLINEFORWARDLIST   const lpForwardList,
    DWORD               dwNumRingsNoAnswer,
    LPHCALL             lphConsultCall,
    LPLINECALLPARAMS    const lpCallParams
    );

LONG
WINAPI
lineForwardW(
    HLINE               hLine,
    DWORD               bAllAddresses,
    DWORD               dwAddressID,
    LPLINEFORWARDLIST   const lpForwardList,
    DWORD               dwNumRingsNoAnswer,
    LPHCALL             lphConsultCall,
    LPLINECALLPARAMS    const lpCallParams
    );

#ifdef UNICODE
#define lineForward lineForwardW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineForward lineForwardA
#endif
#endif
#endif

LONG
WINAPI
lineGatherDigits(
    HCALL               hCall,
    DWORD               dwDigitModes,
    LPSTR               lpsDigits,
    DWORD               dwNumDigits,
    LPCSTR              lpszTerminationDigits,
    DWORD               dwFirstDigitTimeout,
    DWORD               dwInterDigitTimeout
    );

#if WIN32
LONG
WINAPI
lineGatherDigitsA(
    HCALL               hCall,
    DWORD               dwDigitModes,
    LPSTR               lpsDigits,
    DWORD               dwNumDigits,
    LPCSTR              lpszTerminationDigits,
    DWORD               dwFirstDigitTimeout,
    DWORD               dwInterDigitTimeout
    );

LONG
WINAPI
lineGatherDigitsW(
    HCALL               hCall,
    DWORD               dwDigitModes,
    LPWSTR              lpsDigits,
    DWORD               dwNumDigits,
    LPCWSTR             lpszTerminationDigits,
    DWORD               dwFirstDigitTimeout,
    DWORD               dwInterDigitTimeout
    );

#ifdef UNICODE
#define lineGatherDigits lineGatherDigitsW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGatherDigits lineGatherDigitsA
#endif
#endif
#endif

LONG
WINAPI
lineGenerateDigits(
    HCALL               hCall,
    DWORD               dwDigitMode,
    LPCSTR              lpszDigits,
    DWORD               dwDuration
    );

#if WIN32
LONG
WINAPI
lineGenerateDigitsA(
    HCALL               hCall,
    DWORD               dwDigitMode,
    LPCSTR              lpszDigits,
    DWORD               dwDuration
    );

LONG
WINAPI
lineGenerateDigitsW(
    HCALL               hCall,
    DWORD               dwDigitMode,
    LPCWSTR             lpszDigits,
    DWORD               dwDuration
    );

#ifdef UNICODE
#define lineGenerateDigits lineGenerateDigitsW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGenerateDigits lineGenerateDigitsA
#endif
#endif
#endif

LONG
WINAPI
lineGenerateTone(
    HCALL               hCall,
    DWORD               dwToneMode,
    DWORD               dwDuration,
    DWORD               dwNumTones,
    LPLINEGENERATETONE  const lpTones
    );

LONG
WINAPI
lineGetAddressCaps(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAddressID,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    LPLINEADDRESSCAPS   lpAddressCaps
    );

#if WIN32
LONG
WINAPI
lineGetAddressCapsA(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAddressID,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    LPLINEADDRESSCAPS   lpAddressCaps
    );

LONG
WINAPI
lineGetAddressCapsW(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAddressID,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    LPLINEADDRESSCAPS   lpAddressCaps
    );

#ifdef UNICODE
#define lineGetAddressCaps lineGetAddressCapsW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetAddressCaps lineGetAddressCapsA
#endif
#endif
#endif

LONG
WINAPI
lineGetAddressID(
    HLINE               hLine,
    LPDWORD             lpdwAddressID,
    DWORD               dwAddressMode,
    LPCSTR              lpsAddress,
    DWORD               dwSize
    );

#if WIN32
LONG
WINAPI
lineGetAddressIDA(
    HLINE               hLine,
    LPDWORD             lpdwAddressID,
    DWORD               dwAddressMode,
    LPCSTR              lpsAddress,
    DWORD               dwSize
    );

LONG
WINAPI
lineGetAddressIDW(
    HLINE               hLine,
    LPDWORD             lpdwAddressID,
    DWORD               dwAddressMode,
    LPCWSTR             lpsAddress,
    DWORD               dwSize
    );

#ifdef UNICODE
#define lineGetAddressID lineGetAddressIDW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetAddressID lineGetAddressIDA
#endif
#endif
#endif

LONG
WINAPI
lineGetAddressStatus(
    HLINE               hLine,
    DWORD               dwAddressID,
    LPLINEADDRESSSTATUS lpAddressStatus
    );

#if WIN32
LONG
WINAPI
lineGetAddressStatusA(
    HLINE               hLine,
    DWORD               dwAddressID,
    LPLINEADDRESSSTATUS lpAddressStatus
    );

LONG
WINAPI
lineGetAddressStatusW(
    HLINE               hLine,
    DWORD               dwAddressID,
    LPLINEADDRESSSTATUS lpAddressStatus
    );

#ifdef UNICODE
#define lineGetAddressStatus lineGetAddressStatusW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetAddressStatus lineGetAddressStatusA
#endif
#endif
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
lineGetAgentActivityListA(                                      // TAPI v2.0
    HLINE                   hLine,
    DWORD                   dwAddressID,
    LPLINEAGENTACTIVITYLIST lpAgentActivityList
    );

LONG
WINAPI
lineGetAgentActivityListW(                                      // TAPI v2.0
    HLINE                   hLine,
    DWORD                   dwAddressID,
    LPLINEAGENTACTIVITYLIST lpAgentActivityList
    );

#ifdef UNICODE
#define lineGetAgentActivityList lineGetAgentActivityListW
#else
#define lineGetAgentActivityList lineGetAgentActivityListA
#endif


LONG
WINAPI
lineGetAgentCapsA(                                              // TAPI v2.0
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAddressID,
    DWORD               dwAppAPIVersion,
    LPLINEAGENTCAPS     lpAgentCaps
    );

LONG
WINAPI
lineGetAgentCapsW(                                              // TAPI v2.0
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAddressID,
    DWORD               dwAppAPIVersion,
    LPLINEAGENTCAPS     lpAgentCaps
    );

#ifdef UNICODE
#define lineGetAgentCaps lineGetAgentCapsW
#else
#define lineGetAgentCaps lineGetAgentCapsA
#endif


LONG
WINAPI
lineGetAgentGroupListA(                                         // TAPI v2.0
    HLINE                   hLine,
    DWORD                   dwAddressID,
    LPLINEAGENTGROUPLIST    lpAgentGroupList
    );

LONG
WINAPI
lineGetAgentGroupListW(                                         // TAPI v2.0
    HLINE                   hLine,
    DWORD                   dwAddressID,
    LPLINEAGENTGROUPLIST    lpAgentGroupList
    );

#ifdef UNICODE
#define lineGetAgentGroupList lineGetAgentGroupListW
#else
#define lineGetAgentGroupList lineGetAgentGroupListA
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020002)
LONG
WINAPI
lineGetAgentInfo(                                               // TAPI v2.2
    HLINE               hLine,
    HAGENT              hAgent,
    LPLINEAGENTINFO     lpAgentInfo
    );

LONG
WINAPI
lineGetAgentSessionInfo(                                        // TAPI v2.2
    HLINE                   hLine,
    HAGENTSESSION           hAgentSession,
    LPLINEAGENTSESSIONINFO  lpAgentSessionInfo
    );

LONG
WINAPI
lineGetAgentSessionList(                                        // TAPI v2.2
    HLINE                   hLine,
    HAGENT                  hAgent,
    LPLINEAGENTSESSIONLIST  lpAgentSessionList
    );
#endif

LONG
WINAPI
lineGetAgentStatusA(                                            // TAPI v2.0
    HLINE               hLine,
    DWORD               dwAddressID,
    LPLINEAGENTSTATUS   lpAgentStatus
    );

LONG
WINAPI
lineGetAgentStatusW(                                            // TAPI v2.0
    HLINE               hLine,
    DWORD               dwAddressID,
    LPLINEAGENTSTATUS   lpAgentStatus
    );

#ifdef UNICODE
#define lineGetAgentStatus lineGetAgentStatusW
#else
#define lineGetAgentStatus lineGetAgentStatusA
#endif
#endif

LONG
WINAPI
lineGetAppPriority(                                             // TAPI v1.4
    LPCSTR              lpszAppFilename,
    DWORD               dwMediaMode,
    LPLINEEXTENSIONID   lpExtensionID,
    DWORD               dwRequestMode,
    LPVARSTRING         lpExtensionName,
    LPDWORD             lpdwPriority
    );

#if WIN32
LONG
WINAPI
lineGetAppPriorityA(                                            // TAPI v1.4
    LPCSTR              lpszAppFilename,
    DWORD               dwMediaMode,
    LPLINEEXTENSIONID   lpExtensionID,
    DWORD               dwRequestMode,
    LPVARSTRING         lpExtensionName,
    LPDWORD             lpdwPriority
    );

LONG
WINAPI
lineGetAppPriorityW(                                            // TAPI v1.4
    LPCWSTR             lpszAppFilename,
    DWORD               dwMediaMode,
    LPLINEEXTENSIONID   lpExtensionID,
    DWORD               dwRequestMode,
    LPVARSTRING         lpExtensionName,
    LPDWORD             lpdwPriority
    );

#ifdef UNICODE
#define lineGetAppPriority lineGetAppPriorityW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetAppPriority lineGetAppPriorityA
#endif
#endif
#endif

LONG
WINAPI
lineGetCallInfo(
    HCALL               hCall,
    LPLINECALLINFO      lpCallInfo
    );

#if WIN32
LONG
WINAPI
lineGetCallInfoA(
    HCALL               hCall,
    LPLINECALLINFO      lpCallInfo
    );

LONG
WINAPI
lineGetCallInfoW(
    HCALL               hCall,
    LPLINECALLINFO      lpCallInfo
    );

#ifdef UNICODE
#define lineGetCallInfo lineGetCallInfoW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetCallInfo lineGetCallInfoA
#endif
#endif
#endif

LONG
WINAPI
lineGetCallStatus(
    HCALL               hCall,
    LPLINECALLSTATUS    lpCallStatus
    );

LONG
WINAPI
lineGetConfRelatedCalls(
    HCALL               hCall,
    LPLINECALLLIST      lpCallList
    );

LONG
WINAPI
lineGetCountry(                                                 // TAPI v1.4
    DWORD               dwCountryID,
    DWORD               dwAPIVersion,
    LPLINECOUNTRYLIST   lpLineCountryList
    );

#if WIN32
LONG
WINAPI
lineGetCountryA(                                                // TAPI v1.4
    DWORD               dwCountryID,
    DWORD               dwAPIVersion,
    LPLINECOUNTRYLIST   lpLineCountryList
    );

LONG
WINAPI
lineGetCountryW(                                                // TAPI v1.4
    DWORD               dwCountryID,
    DWORD               dwAPIVersion,
    LPLINECOUNTRYLIST   lpLineCountryList
    );

#ifdef UNICODE
#define lineGetCountry lineGetCountryW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetCountry lineGetCountryA
#endif
#endif
#endif

LONG
WINAPI
lineGetDevCaps(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    LPLINEDEVCAPS       lpLineDevCaps
    );

#if WIN32
LONG
WINAPI
lineGetDevCapsA(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    LPLINEDEVCAPS       lpLineDevCaps
    );

LONG
WINAPI
lineGetDevCapsW(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    LPLINEDEVCAPS       lpLineDevCaps
    );

#ifdef UNICODE
#define lineGetDevCaps lineGetDevCapsW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetDevCaps lineGetDevCapsA
#endif
#endif
#endif

LONG
WINAPI
lineGetDevConfig(
    DWORD               dwDeviceID,
    LPVARSTRING         lpDeviceConfig,
    LPCSTR              lpszDeviceClass
    );

#if WIN32
LONG
WINAPI
lineGetDevConfigA(
    DWORD               dwDeviceID,
    LPVARSTRING         lpDeviceConfig,
    LPCSTR              lpszDeviceClass
    );

LONG
WINAPI
lineGetDevConfigW(
    DWORD               dwDeviceID,
    LPVARSTRING         lpDeviceConfig,
    LPCWSTR             lpszDeviceClass
    );

#ifdef UNICODE
#define lineGetDevConfig lineGetDevConfigW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetDevConfig lineGetDevConfigA
#endif
#endif
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020002)
LONG
WINAPI
lineGetGroupListA(                                              // TAPI v2.2
    HLINE                   hLine,
    LPLINEAGENTGROUPLIST    lpGroupList
    );

LONG
WINAPI
lineGetGroupListW(                                              // TAPI v2.2
    HLINE                   hLine,
    LPLINEAGENTGROUPLIST    lpGroupList
    );

#ifdef UNICODE
#define lineGetGroupList lineGetGroupListW
#else
#define lineGetGroupList lineGetGroupListA
#endif
#endif

LONG
WINAPI
lineGetIcon(
    DWORD               dwDeviceID,
    LPCSTR              lpszDeviceClass,
    LPHICON             lphIcon
    );

#if WIN32
LONG
WINAPI
lineGetIconA(
    DWORD               dwDeviceID,
    LPCSTR              lpszDeviceClass,
    LPHICON             lphIcon
    );

LONG
WINAPI
lineGetIconW(
    DWORD               dwDeviceID,
    LPCWSTR             lpszDeviceClass,
    LPHICON             lphIcon
    );

#ifdef UNICODE
#define lineGetIcon lineGetIconW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetIcon lineGetIconA
#endif
#endif
#endif

LONG
WINAPI
lineGetID(
    HLINE               hLine,
    DWORD               dwAddressID,
    HCALL               hCall,
    DWORD               dwSelect,
    LPVARSTRING         lpDeviceID,
    LPCSTR              lpszDeviceClass
    );

#if WIN32
LONG
WINAPI
lineGetIDA(
    HLINE               hLine,
    DWORD               dwAddressID,
    HCALL               hCall,
    DWORD               dwSelect,
    LPVARSTRING         lpDeviceID,
    LPCSTR              lpszDeviceClass
    );

LONG
WINAPI
lineGetIDW(
    HLINE               hLine,
    DWORD               dwAddressID,
    HCALL               hCall,
    DWORD               dwSelect,
    LPVARSTRING         lpDeviceID,
    LPCWSTR             lpszDeviceClass
    );

#ifdef UNICODE
#define lineGetID lineGetIDW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetID lineGetIDA
#endif
#endif
#endif

LONG
WINAPI
lineGetLineDevStatus(
    HLINE               hLine,
    LPLINEDEVSTATUS     lpLineDevStatus
    );

#if WIN32
LONG
WINAPI
lineGetLineDevStatusA(
    HLINE               hLine,
    LPLINEDEVSTATUS     lpLineDevStatus
    );

LONG
WINAPI
lineGetLineDevStatusW(
    HLINE               hLine,
    LPLINEDEVSTATUS     lpLineDevStatus
    );

#ifdef UNICODE
#define lineGetDevStatus lineGetDevStatusW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetDevStatus lineGetDevStatusA
#endif
#endif
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
lineGetMessage(                                                 // TAPI v2.0
    HLINEAPP        hLineApp,
    LPLINEMESSAGE   lpMessage,
    DWORD           dwTimeout
    );
#endif

LONG
WINAPI
lineGetNewCalls(
    HLINE               hLine,
    DWORD               dwAddressID,
    DWORD               dwSelect,
    LPLINECALLLIST      lpCallList
    );

LONG
WINAPI
lineGetNumRings(
    HLINE               hLine,
    DWORD               dwAddressID,
    LPDWORD             lpdwNumRings
    );

LONG
WINAPI
lineGetProviderList(                                            // TAPI v1.4
    DWORD               dwAPIVersion,
    LPLINEPROVIDERLIST  lpProviderList
    );

#if WIN32
LONG
WINAPI
lineGetProviderListA(
    DWORD               dwAPIVersion,
    LPLINEPROVIDERLIST  lpProviderList
    );

LONG
WINAPI
lineGetProviderListW(
    DWORD               dwAPIVersion,
    LPLINEPROVIDERLIST  lpProviderList
    );

#ifdef UNICODE
#define lineGetProviderList lineGetProviderListW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetProviderList lineGetProviderListA
#endif
#endif
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020002)
LONG
WINAPI
lineGetProxyStatus(                                             // TAPI v2.2
    HLINEAPP                hLineApp,
    DWORD                   dwDeviceID,
    DWORD                   dwAppAPIVersion,
    LPLINEPROXYREQUESTLIST  lpLineProxyReqestList
    );

LONG
WINAPI
lineGetQueueInfo(                                               // TAPI v2.2
    HLINE               hLine,
    DWORD               dwQueueID,
    LPLINEQUEUEINFO     lpLineQueueInfo
    );

LONG
WINAPI
lineGetQueueListA(                                              // TAPI v2.2
    HLINE               hLine,
    LPGUID              lpGroupID,
    LPLINEQUEUELIST     lpQueueList
    );

LONG
WINAPI
lineGetQueueListW(                                              // TAPI v2.2
    HLINE               hLine,
    LPGUID              lpGroupID,
    LPLINEQUEUELIST     lpQueueList
    );

#ifdef UNICODE
#define lineGetQueueList lineGetQueueListW
#else
#define lineGetQueueList lineGetQueueListA
#endif
#endif

LONG
WINAPI
lineGetRequest(
    HLINEAPP            hLineApp,
    DWORD               dwRequestMode,
    LPVOID              lpRequestBuffer
    );

#if WIN32
LONG
WINAPI
lineGetRequestA(
    HLINEAPP            hLineApp,
    DWORD               dwRequestMode,
    LPVOID              lpRequestBuffer
    );

LONG
WINAPI
lineGetRequestW(
    HLINEAPP            hLineApp,
    DWORD               dwRequestMode,
    LPVOID              lpRequestBuffer
    );

#ifdef UNICODE
#define lineGetRequest lineGetRequestW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetRequest lineGetRequestA
#endif
#endif
#endif

LONG
WINAPI
lineGetStatusMessages(
    HLINE               hLine,
    LPDWORD             lpdwLineStates,
    LPDWORD             lpdwAddressStates
    );

LONG
WINAPI
lineGetTranslateCaps(
    HLINEAPP hLineApp,
    DWORD dwAPIVersion,
    LPLINETRANSLATECAPS lpTranslateCaps
    );

#if WIN32
LONG
WINAPI
lineGetTranslateCapsA(
    HLINEAPP hLineApp,
    DWORD dwAPIVersion,
    LPLINETRANSLATECAPS lpTranslateCaps
    );

LONG
WINAPI
lineGetTranslateCapsW(
    HLINEAPP hLineApp,
    DWORD dwAPIVersion,
    LPLINETRANSLATECAPS lpTranslateCaps
    );

#ifdef UNICODE
#define lineGetTranslateCaps lineGetTranslateCapsW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineGetTranslateCaps lineGetTranslateCapsA
#endif
#endif
#endif

LONG
WINAPI
lineHandoff(
    HCALL               hCall,
    LPCSTR              lpszFileName,
    DWORD               dwMediaMode
    );

#if WIN32
LONG
WINAPI
lineHandoffA(
    HCALL               hCall,
    LPCSTR              lpszFileName,
    DWORD               dwMediaMode
    );

LONG
WINAPI
lineHandoffW(
    HCALL               hCall,
    LPCWSTR             lpszFileName,
    DWORD               dwMediaMode
    );

#ifdef UNICODE
#define lineHandoff lineHandoffW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineHandoff lineHandoffA
#endif
#endif
#endif

LONG
WINAPI
lineHold(
    HCALL               hCall
    );

LONG
WINAPI
lineInitialize(
    LPHLINEAPP          lphLineApp,
    HINSTANCE           hInstance,
    LINECALLBACK        lpfnCallback,
    LPCSTR              lpszAppName,
    LPDWORD             lpdwNumDevs
    );

#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
lineInitializeExA(                                               // TAPI v2.0
    LPHLINEAPP                  lphLineApp,
    HINSTANCE                   hInstance,
    LINECALLBACK                lpfnCallback,
    LPCSTR                      lpszFriendlyAppName,
    LPDWORD                     lpdwNumDevs,
    LPDWORD                     lpdwAPIVersion,
    LPLINEINITIALIZEEXPARAMS    lpLineInitializeExParams
    );

LONG
WINAPI
lineInitializeExW(                                               // TAPI v2.0
    LPHLINEAPP                  lphLineApp,
    HINSTANCE                   hInstance,
    LINECALLBACK                lpfnCallback,
    LPCWSTR                     lpszFriendlyAppName,
    LPDWORD                     lpdwNumDevs,
    LPDWORD                     lpdwAPIVersion,
    LPLINEINITIALIZEEXPARAMS    lpLineInitializeExParams
    );

#ifdef UNICODE
#define lineInitializeEx lineInitializeExW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineInitializeEx lineInitializeExA
#endif
#endif
#endif

LONG
WINAPI
lineMakeCall(
    HLINE               hLine,
    LPHCALL             lphCall,
    LPCSTR              lpszDestAddress,
    DWORD               dwCountryCode,
    LPLINECALLPARAMS    const lpCallParams
    );

#if WIN32
LONG
WINAPI
lineMakeCallA(
    HLINE               hLine,
    LPHCALL             lphCall,
    LPCSTR              lpszDestAddress,
    DWORD               dwCountryCode,
    LPLINECALLPARAMS    const lpCallParams
    );

LONG
WINAPI
lineMakeCallW(
    HLINE               hLine,
    LPHCALL             lphCall,
    LPCWSTR             lpszDestAddress,
    DWORD               dwCountryCode,
    LPLINECALLPARAMS    const lpCallParams
    );

#ifdef UNICODE
#define lineMakeCall lineMakeCallW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineMakeCall lineMakeCallA
#endif
#endif
#endif

LONG
WINAPI
lineMonitorDigits(
    HCALL               hCall,
    DWORD               dwDigitModes
    );

LONG
WINAPI
lineMonitorMedia(
    HCALL               hCall,
    DWORD               dwMediaModes
    );

LONG
WINAPI
lineMonitorTones(
    HCALL               hCall,
    LPLINEMONITORTONE   const lpToneList,
    DWORD               dwNumEntries
    );

LONG
WINAPI
lineNegotiateAPIVersion(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAPILowVersion,
    DWORD               dwAPIHighVersion,
    LPDWORD             lpdwAPIVersion,
    LPLINEEXTENSIONID   lpExtensionID
    );

LONG
WINAPI
lineNegotiateExtVersion(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    DWORD               dwExtLowVersion,
    DWORD               dwExtHighVersion,
    LPDWORD             lpdwExtVersion
    );

LONG
WINAPI
lineOpen(
    HLINEAPP hLineApp,
    DWORD dwDeviceID,
    LPHLINE lphLine,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    DWORD_PTR           dwCallbackInstance,
    DWORD               dwPrivileges,
    DWORD               dwMediaModes,
    LPLINECALLPARAMS    const lpCallParams
    );

#if WIN32
LONG
WINAPI
lineOpenA(
    HLINEAPP hLineApp,
    DWORD dwDeviceID,
    LPHLINE lphLine,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    DWORD_PTR           dwCallbackInstance,
    DWORD               dwPrivileges,
    DWORD               dwMediaModes,
    LPLINECALLPARAMS    const lpCallParams
    );

LONG
WINAPI
lineOpenW(
    HLINEAPP hLineApp,
    DWORD dwDeviceID,
    LPHLINE lphLine,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    DWORD_PTR           dwCallbackInstance,
    DWORD               dwPrivileges,
    DWORD               dwMediaModes,
    LPLINECALLPARAMS    const lpCallParams
    );

#ifdef UNICODE
#define lineOpen lineOpenW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineOpen lineOpenA
#endif
#endif
#endif

LONG
WINAPI
linePark(
    HCALL               hCall,
    DWORD               dwParkMode,
    LPCSTR              lpszDirAddress,
    LPVARSTRING         lpNonDirAddress
    );

#if WIN32
LONG
WINAPI
lineParkA(
    HCALL               hCall,
    DWORD               dwParkMode,
    LPCSTR              lpszDirAddress,
    LPVARSTRING         lpNonDirAddress
    );

LONG
WINAPI
lineParkW(
    HCALL               hCall,
    DWORD               dwParkMode,
    LPCWSTR             lpszDirAddress,
    LPVARSTRING         lpNonDirAddress
    );

#ifdef UNICODE
#define linePark lineParkW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define linePark lineParkA
#endif
#endif
#endif

LONG
WINAPI
linePickup(
    HLINE               hLine,
    DWORD               dwAddressID,
    LPHCALL             lphCall,
    LPCSTR              lpszDestAddress,
    LPCSTR              lpszGroupID
    );

#if WIN32
LONG
WINAPI
linePickupA(
    HLINE               hLine,
    DWORD               dwAddressID,
    LPHCALL             lphCall,
    LPCSTR              lpszDestAddress,
    LPCSTR              lpszGroupID
    );

LONG
WINAPI
linePickupW(
    HLINE               hLine,
    DWORD               dwAddressID,
    LPHCALL             lphCall,
    LPCWSTR             lpszDestAddress,
    LPCWSTR             lpszGroupID
    );

#ifdef UNICODE
#define linePickup linePickupW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define linePickup linePickupA
#endif
#endif
#endif

LONG
WINAPI
linePrepareAddToConference(
    HCALL               hConfCall,
    LPHCALL             lphConsultCall,
    LPLINECALLPARAMS    const lpCallParams
    );

#if WIN32
LONG
WINAPI
linePrepareAddToConferenceA(
    HCALL               hConfCall,
    LPHCALL             lphConsultCall,
    LPLINECALLPARAMS    const lpCallParams
    );

LONG
WINAPI
linePrepareAddToConferenceW(
    HCALL               hConfCall,
    LPHCALL             lphConsultCall,
    LPLINECALLPARAMS    const lpCallParams
    );

#ifdef UNICODE
#define linePrepareAddToConference linePrepareAddToConferenceW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define linePrepareAddToConference linePrepareAddToConferenceA
#endif
#endif
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
lineProxyMessage(                                               // TAPI v2.0
    HLINE               hLine,
    HCALL               hCall,
    DWORD               dwMsg,
    DWORD               dwParam1,
    DWORD               dwParam2,
    DWORD               dwParam3
    );

LONG
WINAPI
lineProxyResponse(                                              // TAPI v2.0
    HLINE               hLine,
    LPLINEPROXYREQUEST  lpProxyRequest,
    DWORD               dwResult
    );
#endif

LONG
WINAPI
lineRedirect(
    HCALL               hCall,
    LPCSTR              lpszDestAddress,
    DWORD               dwCountryCode
    );

#if WIN32
LONG
WINAPI
lineRedirectA(
    HCALL               hCall,
    LPCSTR              lpszDestAddress,
    DWORD               dwCountryCode
    );

LONG
WINAPI
lineRedirectW(
    HCALL               hCall,
    LPCWSTR             lpszDestAddress,
    DWORD               dwCountryCode
    );

#ifdef UNICODE
#define lineRedirect lineRedirectW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineRedirect lineRedirectA
#endif
#endif
#endif

LONG
WINAPI
lineRegisterRequestRecipient(
    HLINEAPP            hLineApp,
    DWORD               dwRegistrationInstance,
    DWORD               dwRequestMode,
    DWORD               bEnable
    );

LONG
WINAPI
lineReleaseUserUserInfo(                                        // TAPI v1.4
    HCALL               hCall
    );

LONG
WINAPI
lineRemoveFromConference(
    HCALL               hCall
    );

LONG
WINAPI
lineRemoveProvider(                                             // TAPI v1.4
    DWORD               dwPermanentProviderID,
    HWND                hwndOwner
    );

LONG
WINAPI
lineSecureCall(
    HCALL               hCall
    );

LONG
WINAPI
lineSendUserUserInfo(
    HCALL               hCall,
    LPCSTR              lpsUserUserInfo,
    DWORD               dwSize
    );

#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
lineSetAgentActivity(                                           // TAPI v2.0
    HLINE               hLine,
    DWORD               dwAddressID,
    DWORD               dwActivityID
    );

LONG
WINAPI
lineSetAgentGroup(                                              // TAPI v2.0
    HLINE                   hLine,
    DWORD                   dwAddressID,
    LPLINEAGENTGROUPLIST    lpAgentGroupList
    );

#if (TAPI_CURRENT_VERSION >= 0x00020002)
LONG
WINAPI
lineSetAgentMeasurementPeriod(                                  // TAPI v2.2
    HLINE               hLine,
    HAGENT              hAgent,
    DWORD               dwMeasurementPeriod
    );

LONG
WINAPI
lineSetAgentSessionState(                                       // TAPI v2.2
    HLINE               hLine,
    HAGENTSESSION       hAgentSession,
    DWORD               dwAgentSessionState,
    DWORD               dwNextAgentSessionState
    );

LONG
WINAPI
lineSetAgentStateEx(                                            // TAPI v2.2
    HLINE               hLine,
    HAGENT              hAgent,
    DWORD               dwAgentState,
    DWORD               dwNextAgentState
    );
#endif

LONG
WINAPI
lineSetAgentState(                                              // TAPI v2.0
    HLINE               hLine,
    DWORD               dwAddressID,
    DWORD               dwAgentState,
    DWORD               dwNextAgentState
    );
#endif

LONG
WINAPI
lineSetAppPriority(                                             // TAPI v1.4
    LPCSTR              lpszAppFilename,
    DWORD               dwMediaMode,
    LPLINEEXTENSIONID   lpExtensionID,
    DWORD               dwRequestMode,
    LPCSTR              lpszExtensionName,
    DWORD               dwPriority
    );

#if WIN32
LONG
WINAPI
lineSetAppPriorityA(                                             // TAPI v1.4
    LPCSTR              lpszAppFilename,
    DWORD               dwMediaMode,
    LPLINEEXTENSIONID   lpExtensionID,
    DWORD               dwRequestMode,
    LPCSTR              lpszExtensionName,
    DWORD               dwPriority
    );

LONG
WINAPI
lineSetAppPriorityW(                                             // TAPI v1.4
    LPCWSTR             lpszAppFilename,
    DWORD               dwMediaMode,
    LPLINEEXTENSIONID   lpExtensionID,
    DWORD               dwRequestMode,
    LPCWSTR             lpszExtensionName,
    DWORD               dwPriority
    );

#ifdef UNICODE
#define lineSetAppPriority lineSetAppPriorityW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineSetAppPriority lineSetAppPriorityA
#endif
#endif
#endif

LONG
WINAPI
lineSetAppSpecific(
    HCALL               hCall,
    DWORD               dwAppSpecific
    );

#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
lineSetCallData(                                                // TAPI v2.0
    HCALL               hCall,
    LPVOID              lpCallData,
    DWORD               dwSize
    );
#endif

LONG
WINAPI
lineSetCallParams(
    HCALL               hCall,
    DWORD               dwBearerMode,
    DWORD               dwMinRate,
    DWORD               dwMaxRate,
    LPLINEDIALPARAMS    const lpDialParams
    );

LONG
WINAPI
lineSetCallPrivilege(
    HCALL               hCall,
    DWORD               dwCallPrivilege
    );

#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
lineSetCallQualityOfService(                                    // TAPI v2.0
    HCALL               hCall,
    LPVOID              lpSendingFlowspec,
    DWORD               dwSendingFlowspecSize,
    LPVOID              lpReceivingFlowspec,
    DWORD               dwReceivingFlowspecSize
    );

LONG
WINAPI
lineSetCallTreatment(                                           // TAPI v2.0
    HCALL               hCall,
    DWORD               dwTreatment
    );
#endif

LONG
WINAPI
lineSetCurrentLocation(
    HLINEAPP            hLineApp,
    DWORD               dwLocation
    );

LONG
WINAPI
lineSetDevConfig(
    DWORD               dwDeviceID,
    LPVOID              const lpDeviceConfig,
    DWORD               dwSize,
    LPCSTR              lpszDeviceClass
    );

#if WIN32
LONG
WINAPI
lineSetDevConfigA(
    DWORD               dwDeviceID,
    LPVOID              const lpDeviceConfig,
    DWORD               dwSize,
    LPCSTR              lpszDeviceClass
    );

LONG
WINAPI
lineSetDevConfigW(
    DWORD               dwDeviceID,
    LPVOID              const lpDeviceConfig,
    DWORD               dwSize,
    LPCWSTR             lpszDeviceClass
    );

#ifdef UNICODE
#define lineSetDevConfig lineSetDevConfigW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineSetDevConfig lineSetDevConfigA
#endif
#endif
#endif

#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
lineSetLineDevStatus(                                           // TAPI v2.0
    HLINE               hLine,
    DWORD               dwStatusToChange,
    DWORD               fStatus
    );
#endif

LONG
WINAPI
lineSetMediaControl(
    HLINE                       hLine,
    DWORD                       dwAddressID,
    HCALL                       hCall,
    DWORD                       dwSelect,
    LPLINEMEDIACONTROLDIGIT     const lpDigitList,
    DWORD                       dwDigitNumEntries,
    LPLINEMEDIACONTROLMEDIA     const lpMediaList,
    DWORD                       dwMediaNumEntries,
    LPLINEMEDIACONTROLTONE      const lpToneList,
    DWORD                       dwToneNumEntries,
    LPLINEMEDIACONTROLCALLSTATE const lpCallStateList,
    DWORD                       dwCallStateNumEntries
    );

LONG
WINAPI
lineSetMediaMode(
    HCALL               hCall,
    DWORD               dwMediaModes
    );

#if (TAPI_CURRENT_VERSION >= 0x00020002)
LONG
WINAPI
lineSetQueueMeasurementPeriod(                                  // TAPI v2.2
    HLINE               hLine,
    DWORD               dwQueueID,
    DWORD               dwMeasurementPeriod
    );
#endif

LONG
WINAPI
lineSetNumRings(
    HLINE               hLine,
    DWORD               dwAddressID,
    DWORD               dwNumRings
    );

LONG
WINAPI
lineSetStatusMessages(
    HLINE               hLine,
    DWORD               dwLineStates,
    DWORD               dwAddressStates
    );

LONG
WINAPI
lineSetTerminal(
    HLINE               hLine,
    DWORD               dwAddressID,
    HCALL               hCall,
    DWORD               dwSelect,
    DWORD               dwTerminalModes,
    DWORD               dwTerminalID,
    DWORD               bEnable
    );

LONG
WINAPI
lineSetTollList(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    LPCSTR              lpszAddressIn,
    DWORD               dwTollListOption
    );

#if WIN32
LONG
WINAPI
lineSetTollListA(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    LPCSTR              lpszAddressIn,
    DWORD               dwTollListOption
    );

LONG
WINAPI
lineSetTollListW(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    LPCWSTR             lpszAddressInW,
    DWORD               dwTollListOption
    );

#ifdef UNICODE
#define lineSetTollList lineSetTollListW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineSetTollList lineSetTollListA
#endif
#endif
#endif

LONG
WINAPI
lineSetupConference(
    HCALL               hCall,
    HLINE               hLine,
    LPHCALL             lphConfCall,
    LPHCALL             lphConsultCall,
    DWORD               dwNumParties,
    LPLINECALLPARAMS    const lpCallParams
    );

#if WIN32
LONG
WINAPI
lineSetupConferenceA(
    HCALL               hCall,
    HLINE               hLine,
    LPHCALL             lphConfCall,
    LPHCALL             lphConsultCall,
    DWORD               dwNumParties,
    LPLINECALLPARAMS    const lpCallParams
    );

LONG
WINAPI
lineSetupConferenceW(
    HCALL               hCall,
    HLINE               hLine,
    LPHCALL             lphConfCall,
    LPHCALL             lphConsultCall,
    DWORD               dwNumParties,
    LPLINECALLPARAMS    const lpCallParams
    );

#ifdef UNICODE
#define lineSetupConference lineSetupConferenceW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineSetupConference lineSetupConferenceA
#endif
#endif
#endif

LONG
WINAPI
lineSetupTransfer(
    HCALL               hCall,
    LPHCALL             lphConsultCall,
    LPLINECALLPARAMS    const lpCallParams
    );

#if WIN32
LONG
WINAPI
lineSetupTransferA(
    HCALL               hCall,
    LPHCALL             lphConsultCall,
    LPLINECALLPARAMS    const lpCallParams
    );

LONG
WINAPI
lineSetupTransferW(
    HCALL               hCall,
    LPHCALL             lphConsultCall,
    LPLINECALLPARAMS    const lpCallParams
    );

#ifdef UNICODE
#define lineSetupTransfer lineSetupTransferW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineSetupTransfer lineSetupTransferA
#endif
#endif
#endif

LONG
WINAPI
lineShutdown(
    HLINEAPP            hLineApp
    );

LONG
WINAPI
lineSwapHold(
    HCALL               hActiveCall,
    HCALL               hHeldCall
    );

LONG
WINAPI
lineTranslateAddress(
    HLINEAPP                hLineApp,
    DWORD                   dwDeviceID,
    DWORD                   dwAPIVersion,
    LPCSTR                  lpszAddressIn,
    DWORD                   dwCard,
    DWORD                   dwTranslateOptions,
    LPLINETRANSLATEOUTPUT   lpTranslateOutput
    );

#if WIN32
LONG
WINAPI
lineTranslateAddressA(
    HLINEAPP                hLineApp,
    DWORD                   dwDeviceID,
    DWORD                   dwAPIVersion,
    LPCSTR                  lpszAddressIn,
    DWORD                   dwCard,
    DWORD                   dwTranslateOptions,
    LPLINETRANSLATEOUTPUT   lpTranslateOutput
    );

LONG
WINAPI
lineTranslateAddressW(
    HLINEAPP                hLineApp,
    DWORD                   dwDeviceID,
    DWORD                   dwAPIVersion,
    LPCWSTR                 lpszAddressIn,
    DWORD                   dwCard,
    DWORD                   dwTranslateOptions,
    LPLINETRANSLATEOUTPUT   lpTranslateOutput
    );

#ifdef UNICODE
#define lineTranslateAddress lineTranslateAddressW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineTranslateAddress lineTranslateAddressA
#endif
#endif
#endif

LONG
WINAPI
lineTranslateDialog(                                            // TAPI v1.4
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    HWND                hwndOwner,
    LPCSTR              lpszAddressIn
    );

#if WIN32
LONG
WINAPI
lineTranslateDialogA(                                            // TAPI v1.4
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    HWND                hwndOwner,
    LPCSTR              lpszAddressIn
    );

LONG
WINAPI
lineTranslateDialogW(
    HLINEAPP            hLineApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    HWND                hwndOwner,
    LPCWSTR             lpszAddressIn
    );

#ifdef UNICODE
#define lineTranslateDialog lineTranslateDialogW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineTranslateDialog lineTranslateDialogA
#endif
#endif
#endif

LONG
WINAPI
lineUncompleteCall(
    HLINE               hLine,
    DWORD               dwCompletionID
    );

LONG
WINAPI
lineUnhold(
    HCALL               hCall
    );

LONG
WINAPI
lineUnpark(
    HLINE               hLine,
    DWORD               dwAddressID,
    LPHCALL             lphCall,
    LPCSTR              lpszDestAddress
    );

#if WIN32
LONG
WINAPI
lineUnparkA(
    HLINE               hLine,
    DWORD               dwAddressID,
    LPHCALL             lphCall,
    LPCSTR              lpszDestAddress
    );

LONG
WINAPI
lineUnparkW(
    HLINE               hLine,
    DWORD               dwAddressID,
    LPHCALL             lphCall,
    LPCWSTR             lpszDestAddress
    );

#ifdef UNICODE
#define lineUnpark lineUnparkW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define lineUnpark lineUnparkA
#endif
#endif
#endif



LONG
WINAPI
phoneClose(
    HPHONE              hPhone
    );

LONG
WINAPI
phoneConfigDialog(
    DWORD               dwDeviceID,
    HWND                hwndOwner,
    LPCSTR              lpszDeviceClass
    );

#if WIN32
LONG
WINAPI
phoneConfigDialogA(
    DWORD               dwDeviceID,
    HWND                hwndOwner,
    LPCSTR              lpszDeviceClass
    );

LONG
WINAPI
phoneConfigDialogW(
    DWORD               dwDeviceID,
    HWND                hwndOwner,
    LPCWSTR             lpszDeviceClass
    );

#ifdef UNICODE
#define phoneConfigDialog phoneConfigDialogW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define phoneConfigDialog phoneConfigDialogA
#endif
#endif
#endif

LONG
WINAPI
phoneDevSpecific(
    HPHONE              hPhone,
    LPVOID              lpParams,
    DWORD               dwSize
    );

LONG
WINAPI
phoneGetButtonInfo(
    HPHONE              hPhone,
    DWORD               dwButtonLampID,
    LPPHONEBUTTONINFO   lpButtonInfo
    );

#if WIN32
LONG
WINAPI
phoneGetButtonInfoA(
    HPHONE              hPhone,
    DWORD               dwButtonLampID,
    LPPHONEBUTTONINFO   lpButtonInfo
    );

LONG
WINAPI
phoneGetButtonInfoW(
    HPHONE              hPhone,
    DWORD               dwButtonLampID,
    LPPHONEBUTTONINFO   lpButtonInfo
    );

#ifdef UNICODE
#define phoneGetButtonInfo phoneGetButtonInfoW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define phoneGetButtonInfo phoneGetButtonInfoA
#endif
#endif
#endif

LONG
WINAPI
phoneGetData(
    HPHONE              hPhone,
    DWORD               dwDataID,
    LPVOID              lpData,
    DWORD               dwSize
    );

LONG
WINAPI
phoneGetDevCaps(
    HPHONEAPP           hPhoneApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    LPPHONECAPS         lpPhoneCaps
    );

#if WIN32
LONG
WINAPI
phoneGetDevCapsA(
    HPHONEAPP           hPhoneApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    LPPHONECAPS         lpPhoneCaps
    );

LONG
WINAPI
phoneGetDevCapsW(
    HPHONEAPP           hPhoneApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    LPPHONECAPS         lpPhoneCaps
    );

#ifdef UNICODE
#define phoneGetDevCaps phoneGetDevCapsW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define phoneGetDevCaps phoneGetDevCapsA
#endif
#endif
#endif

LONG
WINAPI
phoneGetDisplay(
    HPHONE              hPhone,
    LPVARSTRING         lpDisplay
    );

LONG
WINAPI
phoneGetGain(
    HPHONE              hPhone,
    DWORD               dwHookSwitchDev,
    LPDWORD             lpdwGain
    );

LONG
WINAPI
phoneGetHookSwitch(
    HPHONE              hPhone,
    LPDWORD             lpdwHookSwitchDevs
    );

LONG
WINAPI
phoneGetIcon(
    DWORD               dwDeviceID,
    LPCSTR              lpszDeviceClass,
    LPHICON             lphIcon
    );

#if WIN32
LONG
WINAPI
phoneGetIconA(
    DWORD               dwDeviceID,
    LPCSTR              lpszDeviceClass,
    LPHICON             lphIcon
    );

LONG
WINAPI
phoneGetIconW(
    DWORD               dwDeviceID,
    LPCWSTR             lpszDeviceClass,
    LPHICON             lphIcon
    );

#ifdef UNICODE
#define phoneGetIcon phoneGetIconW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define phoneGetIcon phoneGetIconA
#endif
#endif
#endif

LONG
WINAPI
phoneGetID(
    HPHONE              hPhone,
    LPVARSTRING         lpDeviceID,
    LPCSTR              lpszDeviceClass
    );

#if WIN32
LONG
WINAPI
phoneGetIDA(
    HPHONE              hPhone,
    LPVARSTRING         lpDeviceID,
    LPCSTR              lpszDeviceClass
    );

LONG
WINAPI
phoneGetIDW(
    HPHONE              hPhone,
    LPVARSTRING         lpDeviceID,
    LPCWSTR             lpszDeviceClass
    );

#ifdef UNICODE
#define phoneGetID phoneGetIDW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define phoneGetID phoneGetIDA
#endif
#endif
#endif

LONG
WINAPI
phoneGetLamp(
    HPHONE              hPhone,
    DWORD               dwButtonLampID,
    LPDWORD             lpdwLampMode
    );

#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
phoneGetMessage(                                                // TAPI v2.0
    HPHONEAPP       hPhoneApp,
    LPPHONEMESSAGE  lpMessage,
    DWORD           dwTimeout
    );
#endif

LONG
WINAPI
phoneGetRing(
    HPHONE              hPhone,
    LPDWORD             lpdwRingMode,
    LPDWORD             lpdwVolume
    );

LONG
WINAPI
phoneGetStatus(
    HPHONE              hPhone,
    LPPHONESTATUS       lpPhoneStatus
    );

#if WIN32
LONG
WINAPI
phoneGetStatusA(
    HPHONE              hPhone,
    LPPHONESTATUS       lpPhoneStatus
    );

LONG
WINAPI
phoneGetStatusW(
    HPHONE              hPhone,
    LPPHONESTATUS       lpPhoneStatus
    );


#ifdef UNICODE
#define phoneGetStatus phoneGetStatusW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define phoneGetStatus phoneGetStatusA
#endif
#endif
#endif

LONG
WINAPI
phoneGetStatusMessages(
    HPHONE              hPhone,
    LPDWORD             lpdwPhoneStates,
    LPDWORD             lpdwButtonModes,
    LPDWORD             lpdwButtonStates
    );

LONG
WINAPI
phoneGetVolume(
    HPHONE              hPhone,
    DWORD               dwHookSwitchDev,
    LPDWORD             lpdwVolume
    );

LONG
WINAPI
phoneInitialize(
    LPHPHONEAPP         lphPhoneApp,
    HINSTANCE           hInstance,
    PHONECALLBACK       lpfnCallback,
    LPCSTR              lpszAppName,
    LPDWORD             lpdwNumDevs
    );


#if (TAPI_CURRENT_VERSION >= 0x00020000)
LONG
WINAPI
phoneInitializeExA(                                              // TAPI v2.0
    LPHPHONEAPP                 lphPhoneApp,
    HINSTANCE                   hInstance,
    PHONECALLBACK               lpfnCallback,
    LPCSTR                      lpszFriendlyAppName,
    LPDWORD                     lpdwNumDevs,
    LPDWORD                     lpdwAPIVersion,
    LPPHONEINITIALIZEEXPARAMS   lpPhoneInitializeExParams
    );

LONG
WINAPI
phoneInitializeExW(                                              // TAPI v2.0
    LPHPHONEAPP                 lphPhoneApp,
    HINSTANCE                   hInstance,
    PHONECALLBACK               lpfnCallback,
    LPCWSTR                     lpszFriendlyAppName,
    LPDWORD                     lpdwNumDevs,
    LPDWORD                     lpdwAPIVersion,
    LPPHONEINITIALIZEEXPARAMS   lpPhoneInitializeExParams
    );

#ifdef UNICODE
#define phoneInitializeEx phoneInitializeExW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define phoneInitializeEx phoneInitializeExA
#endif
#endif
#endif

LONG
WINAPI
phoneNegotiateAPIVersion(
    HPHONEAPP           hPhoneApp,
    DWORD               dwDeviceID,
    DWORD               dwAPILowVersion,
    DWORD               dwAPIHighVersion,
    LPDWORD             lpdwAPIVersion,
    LPPHONEEXTENSIONID  lpExtensionID
    );

LONG
WINAPI
phoneNegotiateExtVersion(
    HPHONEAPP           hPhoneApp,
    DWORD               dwDeviceID,
    DWORD               dwAPIVersion,
    DWORD               dwExtLowVersion,
    DWORD               dwExtHighVersion,
    LPDWORD             lpdwExtVersion
    );

LONG
WINAPI
phoneOpen(
    HPHONEAPP           hPhoneApp,
    DWORD               dwDeviceID,
    LPHPHONE            lphPhone,
    DWORD               dwAPIVersion,
    DWORD               dwExtVersion,
    DWORD_PTR           dwCallbackInstance,
    DWORD               dwPrivilege
    );

LONG
WINAPI
phoneSetButtonInfo(
    HPHONE              hPhone,
    DWORD               dwButtonLampID,
    LPPHONEBUTTONINFO   const lpButtonInfo
    );

#if WIN32
LONG
WINAPI
phoneSetButtonInfoA(
    HPHONE              hPhone,
    DWORD               dwButtonLampID,
    LPPHONEBUTTONINFO   const lpButtonInfo
    );

LONG
WINAPI
phoneSetButtonInfoW(
    HPHONE              hPhone,
    DWORD               dwButtonLampID,
    LPPHONEBUTTONINFO   const lpButtonInfo
    );

#ifdef UNICODE
#define phoneSetButtonInfo phoneSetButtonInfoW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define phoneSetButtonInfo phoneSetButtonInfoA
#endif
#endif
#endif

LONG
WINAPI
phoneSetData(
    HPHONE              hPhone,
    DWORD               dwDataID,
    LPVOID              const lpData,
    DWORD               dwSize
    );

LONG
WINAPI
phoneSetDisplay(
    HPHONE              hPhone,
    DWORD               dwRow,
    DWORD               dwColumn,
    LPCSTR              lpsDisplay,
    DWORD               dwSize
    );

LONG
WINAPI
phoneSetGain(
    HPHONE              hPhone,
    DWORD               dwHookSwitchDev,
    DWORD               dwGain
    );

LONG
WINAPI
phoneSetHookSwitch(
    HPHONE              hPhone,
    DWORD               dwHookSwitchDevs,
    DWORD               dwHookSwitchMode
    );

LONG
WINAPI
phoneSetLamp(
    HPHONE              hPhone,
    DWORD               dwButtonLampID,
    DWORD               dwLampMode
    );

LONG
WINAPI
phoneSetRing(
    HPHONE              hPhone,
    DWORD               dwRingMode,
    DWORD               dwVolume
    );

LONG
WINAPI
phoneSetStatusMessages(
    HPHONE              hPhone,
    DWORD               dwPhoneStates,
    DWORD               dwButtonModes,
    DWORD               dwButtonStates
    );

LONG
WINAPI
phoneSetVolume(
    HPHONE              hPhone,
    DWORD               dwHookSwitchDev,
    DWORD               dwVolume
    );

LONG
WINAPI
phoneShutdown(
    HPHONEAPP           hPhoneApp
    );



LONG
WINAPI
tapiGetLocationInfo(
    LPSTR               lpszCountryCode,
    LPSTR               lpszCityCode
    );

#if WIN32
LONG
WINAPI
tapiGetLocationInfoA(
    LPSTR               lpszCountryCode,
    LPSTR               lpszCityCode
    );

LONG
WINAPI
tapiGetLocationInfoW(
    LPWSTR               lpszCountryCodeW,
    LPWSTR               lpszCityCodeW
    );

#ifdef UNICODE
#define tapiGetLocationInfo tapiGetLocationInfoW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define tapiGetLocationInfo tapiGetLocationInfoA
#endif
#endif
#endif

LONG
WINAPI
tapiRequestDrop(
    HWND                hwnd,
    WPARAM              wRequestID
    );

LONG
WINAPI
tapiRequestMakeCall(
    LPCSTR              lpszDestAddress,
    LPCSTR              lpszAppName,
    LPCSTR              lpszCalledParty,
    LPCSTR              lpszComment
    );

#if WIN32
LONG
WINAPI
tapiRequestMakeCallA(
    LPCSTR              lpszDestAddress,
    LPCSTR              lpszAppName,
    LPCSTR              lpszCalledParty,
    LPCSTR              lpszComment
    );

LONG
WINAPI
tapiRequestMakeCallW(
    LPCWSTR              lpszDestAddress,
    LPCWSTR              lpszAppName,
    LPCWSTR              lpszCalledParty,
    LPCWSTR              lpszComment
    );

#ifdef UNICODE
#define tapiRequestMakeCall tapiRequestMakeCallW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define tapiRequestMakeCall tapiRequestMakeCallA
#endif
#endif
#endif

LONG
WINAPI
tapiRequestMediaCall(
    HWND                hwnd,
    WPARAM              wRequestID,
    LPCSTR              lpszDeviceClass,
    LPCSTR              lpDeviceID,
    DWORD               dwSize,
    DWORD               dwSecure,
    LPCSTR              lpszDestAddress,
    LPCSTR              lpszAppName,
    LPCSTR              lpszCalledParty,
    LPCSTR              lpszComment
    );

#if WIN32
LONG
WINAPI
tapiRequestMediaCallA(
    HWND                hwnd,
    WPARAM              wRequestID,
    LPCSTR              lpszDeviceClass,
    LPCSTR              lpDeviceID,
    DWORD               dwSize,
    DWORD               dwSecure,
    LPCSTR              lpszDestAddress,
    LPCSTR              lpszAppName,
    LPCSTR              lpszCalledParty,
    LPCSTR              lpszComment
    );

LONG
WINAPI
tapiRequestMediaCallW(
    HWND                hwnd,
    WPARAM              wRequestID,
    LPCWSTR             lpszDeviceClass,
    LPCWSTR             lpDeviceID,
    DWORD               dwSize,
    DWORD               dwSecure,
    LPCWSTR             lpszDestAddress,
    LPCWSTR             lpszAppName,
    LPCWSTR             lpszCalledParty,
    LPCWSTR             lpszComment
    );

#ifdef UNICODE
#define tapiRequestMediaCall tapiRequestMediaCallW
#else
#if (TAPI_CURRENT_VERSION >= 0x00020000)
#define tapiRequestMediaCall tapiRequestMediaCallA
#endif
#endif
#endif

/*

TAPIERROR_FORMATMESSAGE - macro to convert a TAPI error constant
    into a constant that FormatMessage will accept

        TAPIERR : Negative numbers and 0
            Map to : strip off high WORD
            Example: 0xFFFFFFFF (-1) becomes 0x0000FFFF
        LINEERR : Start at 0x80000000
            Map to : strip off 0x80000000 and add 0xE000
            Example: 0x80000004 becomes 0x0000E004
        PHONEERR: Start at 0x90000000
            Map to : strip off 0x90000000 and add 0xF000
            Example: 0x9000000A becomes 0x0000F00A

        pseudocode:

        if (__ErrCode__ is a TAPIERR)
            strip off high word

            else if (__ErrCode__ is a PHONEERR)
                strip off 0x90000000
                add 0xE000

                else
                    strip off 0x80000000
                    add 0xF000

*/

#define TAPIERROR_FORMATMESSAGE(__ErrCode__)                                                   \
                                                                                               \
                    ( ( (__ErrCode__) > 0xFFFF0000 ) ?                                         \
                                                                                               \
                            ( (__ErrCode__) & 0x0000FFFF ) :                                   \
                                                                                               \
                            ( ( (__ErrCode__) & 0x10000000 ) ?                                 \
                                                                                               \
                              ( (__ErrCode__) - 0x90000000 + 0xF000 ) :                        \
                                                                                               \
                              ( (__ErrCode__) - 0x80000000 + 0xE000 ) ) )



#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif  /* __cplusplus */

#pragma pack()


#pragma option pop /*P_O_Pop*/
#endif // TAPI_H

