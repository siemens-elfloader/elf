// CSMSwaper.h: interface for the CCSMSwaper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSMSWAPER_H__3D1F46A7_10F8_4893_8B82_4D1530A5FEFD__INCLUDED_)
#define AFX_CSMSWAPER_H__3D1F46A7_10F8_4893_8B82_4D1530A5FEFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSMSwaper  
{
public:
	static void InitUnderIdleCSM(void);
	static void CSMtoTop(int id, int top_id);
private:
	static CSM_RAM * under_idle;
	static void LLaddToEnd(LLQ *ll, void *data);
	static int do_CSMtoTop(CSMQ *csm_q, void *_cmd);
	CSMSwaper();
	virtual ~CSMSwaper();

};

#endif // !defined(AFX_CSMSWAPER_H__3D1F46A7_10F8_4893_8B82_4D1530A5FEFD__INCLUDED_)
