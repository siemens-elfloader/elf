
#ifndef __CRSCLSID_H__
#pragma option push -b -a8 -pc -A- /*P_O_Push*/
#define __CRSCLSID_H__

//====================================================================
//                                                                     
//   Microsoft Site Server v3.00                                   
//                                                                     
//   Copyright (c) 1997-98 Microsoft Corporation.  All rights reserved.   
//   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
//   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//   PARTICULAR PURPOSE.
//=====================================================================

//
// CLSIDs for the Content Deployment (aka CRS) COM Objects (ProgId = CrsApi)
//

// {66D6D7ED-22D2-11D0-9B98-00C04FD5CD09}
DEFINE_GUID(CLSID_ReplicationServer, 
0x66D6D7ED, 0x22D2, 0x11D0, 0x9B, 0x98, 0x00, 0xC0, 0x4F, 0xD5, 0xCD, 0x09);

// {66D6D7F2-22D2-11D0-9B98-00C04FD5CD09}
DEFINE_GUID(CLSID_ReplicationProject, 
0x66D6D7F2, 0x22D2, 0x11D0, 0x9B, 0x98, 0x00, 0xC0, 0x4F, 0xD5, 0xCD, 0x09);

// {66D6D7F7-22D2-11D0-9B98-00C04FD5CD09}};
DEFINE_GUID(CLSID_ReplicationInstance, 
0x66D6D7F7, 0x22D2, 0x11D0, 0x9B, 0x98, 0x00, 0xC0, 0x4F, 0xD5, 0xCD, 0x09);

// {66D6D7FC-22D2-11D0-9B98-00C04FD5CD09}
DEFINE_GUID(CLSID_ReplicationRoute,
0x66D6D7FC, 0x22D2, 0x11D0, 0x9B, 0x98, 0x00, 0xC0, 0x4F, 0xD5, 0xCD, 0x09);

// {66D6D7FE-22D2-11D0-9B98-00C04FD5CD09}
DEFINE_GUID( CLSID_ReplicationItem,
0x66D6D7FE, 0x22D2, 0x11D0, 0x9B, 0x98, 0x00, 0xC0, 0x4F, 0xD5, 0xCD, 0x09);

// {66D6D7FD-22D2-11D0-9B98-00C04FD5CD09}
DEFINE_GUID( CLSID_ReplicationEventSinkConfig,
0x66D6D7FD, 0x22D2, 0x11D0, 0x9B, 0x98, 0x00, 0xC0, 0x4F, 0xD5, 0xCD, 0x09);


// {B24F0373-9692-11D0-BAD5-00C04FD7082F}
DEFINE_GUID(CLSID_ReplicationClient,
0xB24F0373, 0x9692, 0x11D0, 0xBA, 0xD5, 0x00, 0xC0, 0x4F, 0xD7, 0x08, 0x2F);

// {6AF9D110-9F37-11d0-BADA-00C04FD7082F}
DEFINE_GUID(CLSID_ReplicationClientError, 
0x6AF9D110, 0x9F37, 0x11d0, 0xBA, 0xDA, 0x00, 0xC0, 0x4F, 0xD7, 0x08, 0x2F);

// {055f638a-1d77-11d1-a32b-0000f8014963}
DEFINE_GUID(CLSID_ReplicationPostingAcceptor, 
0x055f638A, 0x1D77, 0x11D1, 0xA3, 0x2B, 0x00, 0x00, 0xF8, 0x01, 0x49, 0x63);

//{4E28F5F0-1B3C-11d1-8C8C-00C04FC2D3B9}
DEFINE_GUID(CLSID_ReplicationSchedule, 
0x4E28F5F0, 0x1B3C, 0x11d1, 0x8C, 0x8C, 0x00, 0xC0, 0x4F, 0xC2, 0xD3, 0xB9);



//
// Interface IDs
//

// {ABEB9802-DB7A-11d0-A800-00C04FC9DAA5}
DEFINE_GUID(IID_IReplicationServer, 
0xABEB9802,0xDB7A,0x11d0,0xA8,0x00,0x00,0xC0,0x4F,0xC9,0xDA,0xA5);

// {ABEB9803-DB7A-11d0-A800-00C04FC9DAA5}
DEFINE_GUID(IID_IReplicationProject, 
0xABEB9803,0xDB7A,0x11d0,0xA8,0x00,0x00,0xC0,0x4F,0xC9,0xDA,0xA5);

// {ABEB9807-DB7A-11d0-A800-00C04FC9DAA5}
DEFINE_GUID(IID_IReplicationInstance, 
0xABEB9807,0xDB7A,0x11d0,0xA8,0x00,0x00,0xC0,0x4F,0xC9,0xDA,0xA5);

// {ABEB9804-DB7A-11d0-A800-00C04FC9DAA5}
DEFINE_GUID(IID_IReplicationRoute,
0xABEB9804,0xDB7A,0x11d0,0xA8,0x00,0x00,0xC0,0x4F,0xC9,0xDA,0xA5);

// {B24F0372-9692-11D0-BAD5-00C04FD7082F}
DEFINE_GUID(IID_IReplicationClient,
0xB24F0372,0x9692,0x11D0,0xBA,0xD5,0x00,0xC0,0x4F,0xD7,0x08,0x2F);

// {414CC9F0-9F37-11d0-BADA-00C04FD7082F}
DEFINE_GUID(IID_IReplicationClientError, 
0x414CC9F0, 0x9F37, 0x11d0, 0xBA, 0xDA, 0x00, 0xC0, 0x4F, 0xD7, 0x08, 0x2F);

// {ABEB9808-DB7A-11d0-A800-00C04FC9DAA5}
DEFINE_GUID(IID_IReplicationItem,
0xABEB9808,0xDB7A,0x11d0,0xA8,0x00,0x00,0xC0,0x4F,0xC9,0xDA,0xA5);

// {ABEB980A-DB7A-11d0-A800-00C04FC9DAA5}
DEFINE_GUID(IID_IReplicationEventSinkConfig,
0xABEB980A,0xDB7A,0x11d0,0xA8,0x00,0x00,0xC0,0x4F,0xC9,0xDA,0xA5);

// {541eaaf0-717b-11cf-86cb-00aa00b4e1b8}
DEFINE_GUID(IID_IAcceptNotify,
0x541eaaf0, 0x717b, 0x11cf, 0x86, 0xcb, 0x00, 0xaa, 0x00, 0xb4, 0xe1, 0xb8);

// {5163ce6b-1d76-11d1-a32b-0000f8014963}
DEFINE_GUID(IID_IReplicationPostingAcceptor, 
0x5163ce6b, 0x1D76, 0x11D1, 0xA3, 0x2B, 0x00, 0x00, 0xF8, 0x01, 0x49, 0x63);

// {82D36BA0-1B37-11d1-8C8C-00C04FC2D3B9}
DEFINE_GUID(IID_IReplicationSchedule, 
0x82d36ba0, 0x1B37, 0x11d1, 0x8C, 0x8C, 0x00, 0xC0, 0x4F, 0xC2, 0xD3, 0xB9);

#pragma option pop /*P_O_Pop*/
#endif