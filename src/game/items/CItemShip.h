/**
* @file CItemShip.h
*
*/

#ifndef _INC_CITEMSHIP_H
#define _INC_CITEMSHIP_H

#include "CItemMulti.h"
#include "../components/CCMultiMovable.h"


class CItemShip : public CItemMulti
{
// IT_SHIP
// A ship
private:
    static lpctstr const sm_szLoadKeys[];
    static lpctstr const sm_szVerbKeys[];

    CUID m_uidHold;
    std::vector<CUID> m_uidPlanks;

    virtual bool r_GetRef(lpctstr & pszKey, CScriptObj * & pRef) override;
    virtual void r_Write(CScript & s) override;
    virtual bool r_WriteVal(lpctstr pszKey, CSString & sVal, CTextConsole * pSrc = nullptr, bool fNoCallParent = false, bool fNoCallChildren = false) override;
    virtual bool r_LoadVal(CScript & s) override;
    virtual bool r_Verb(CScript & s, CTextConsole * pSrc) override; // Execute command from script
    virtual int FixWeirdness() override;
    virtual void OnComponentCreate(CItem * pComponent);

public:
    static const char *m_sClassName;
    CItemShip(ITEMID_TYPE id, CItemBase * pItemDef);
    virtual ~CItemShip();

private:
    CItemShip(const CItemShip& copy);
    CItemShip& operator=(const CItemShip& other);

public:
    virtual bool OnTick();
    CItemContainer * GetShipHold();
    size_t GetShipPlankCount();
    CItem * GetShipPlank(size_t index);
    //CItemBaseMulti::ShipSpeed GetShipSpeed();
};


#endif // _INC_CITEMSHIP_H
