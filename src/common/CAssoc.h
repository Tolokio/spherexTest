/*
* @file CAssoc.H
* @brief Simple shared useful base classes.
*/

#pragma once
#ifndef _INC_CASSOC_H
#define _INC_CASSOC_H

// #include <shellapi.h>
#include "CFile.h"
#include "CArray.h"
#include "graycom.h"

#ifndef PT_REG_STRMAX
	#define PT_REG_STRMAX		128
#endif
#ifndef PT_REG_ROOTKEY
	#define PT_REG_ROOTKEY		HKEY_LOCAL_MACHINE
#endif
#ifndef OFFSETOF			// stddef.h ?
	#define OFFSETOF(s,m)   	(int)( (byte *)&(((s *)0)->m) - (byte *)0 )
#endif


enum ELEM_TYPE	// define types of structure/record elements.
{
	ELEM_VOID = 0,	// unknown what this might be. (or just 'other') (must be handled manually)
	ELEM_CSTRING,	// Size prefix.
	ELEM_STRING,	// Assume max size of REG_SIZE. NULL TERM string.
	ELEM_BOOL,		// bool = just 1 byte i guess.
	ELEM_BYTE,		// 1 byte.
	ELEM_MASK_BYTE,	// bits in a byte
	ELEM_WORD,		// 2 bytes
	ELEM_MASK_WORD,	// bits in a word
	ELEM_INT,		// Whatever the int size is. 4 i assume
	ELEM_MASK_INT,
	ELEM_DWORD,		// 4 bytes.
	ELEM_MASK_DWORD,	// bits in a dword

	ELEM_QTY
};


struct CElementDef
{
	static const int sm_Lengths[ELEM_QTY];
	ELEM_TYPE m_type;
	UINT	m_offset;	// The offset into the class instance for this item.
	// ELEM_STRING = max size.
	// ELEM_MASK_WORD etc. = Extra masking info if needed. 
	dword   m_extra;

private:
	CElementDef& operator=(const CElementDef& other);

public:
	// get structure value.
	void * GetValPtr( const void * pBaseInst ) const;
	int GetValLength() const;

	bool GetValStr( const void * pBase, CGString & sVal ) const;
	bool SetValStr( void * pBase, LPCTSTR pszVal ) const;
};

class CAssocReg	// associate members of some class/structure with entries in the registry.
{
	// LAST = { NULL, 0, ELEM_VOID }
public:
	LPCTSTR m_pszKey;	// A single key identifier to be cat to a base key. NULL=last
	CElementDef m_elem;
public:
	static const char *m_sClassName;
private:
	CAssocReg& operator=(const CAssocReg& other);
public:
	operator LPCTSTR() const
	{
		return( m_pszKey );
	}
	// get structure value.
	void * GetValPtr( const void * pBaseInst ) const
	{
		return( m_elem.GetValPtr( pBaseInst ));
	}
};

////////////////////////////////////////////////////////////////////////

class CGStringListRec : public CGObListRec, public CGString
{
	friend class CGStringList;
public:
	static const char *m_sClassName;
	explicit CGStringListRec( LPCTSTR pszVal ) : CGString( pszVal )
	{
	}
private:
	CGStringListRec(const CGStringListRec& copy);
	CGStringListRec& operator=(const CGStringListRec& other);
public:
	CGStringListRec * GetNext() const
	{
		return STATIC_CAST<CGStringListRec *>( CGObListRec::GetNext() );
	}
};

class CGStringList : public CGObList 	// obviously a list of strings.
{
public:
	static const char *m_sClassName;
	CGStringList() { };
	virtual ~CGStringList() { };
private:
	CGStringList(const CGStringList& copy);
	CGStringList& operator=(const CGStringList& other);
public:
	CGStringListRec * GetHead() const
	{
		return STATIC_CAST<CGStringListRec *>( CGObList::GetHead() );
	}
	void AddHead( LPCTSTR pszVal )
	{
		InsertHead( new CGStringListRec( pszVal ));
	}
	void AddTail( LPCTSTR pszVal )
	{
		InsertTail( new CGStringListRec( pszVal ));
	}
};

#endif // _INC_CASSOC_H
