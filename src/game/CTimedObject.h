/**
* @file CTimedObject.h
*
*/

#ifndef _INC_CTIMEDOBJECT_H
#define _INC_CTIMEDOBJECT_H

#include "../sphere/ProfileData.h"


class CTimedObject
{
    friend class CWorldTicker;

private:
    THREAD_CMUTEX_DEF;
    int64 _iTimeout;
    PROFILE_TYPE _profileType;
    bool _fIsSleeping;

    /**
    * @brief clears the timeout.
    * Should not be used outside the tick's loop, use SetTimeout(0) instead.
    */
    inline void ClearTimeout();

public:
    CTimedObject(PROFILE_TYPE profile);
    virtual ~CTimedObject();

    inline bool IsSleeping() const;
    inline virtual void GoSleep();

    virtual void GoAwake();

    /**
    * @brief returns the profiler type.
    * @return the type.
    */
    inline PROFILE_TYPE GetProfileType() const noexcept;

    /**
     * @brief   Determine if the object is in a "tickable" state.
    */
    virtual bool CanTick() const;

    /**
     * @brief   Executes the tick action.
     * @return  true if it succeeds, false if it fails.
    */
    virtual bool OnTick();

    /*
    * @brief Check if IsDeleted();
    * @return true if it's deleted.
    */
    virtual bool IsDeleted() const = 0;

    /**
     * @brief   &lt; Gets raw Timeout.
     * @return  Delay in milliseconds.
     */
    inline int64 GetTimeoutRaw() const noexcept;

    /**
     * @brief   &lt; Set raw Timeout.
     * @param   iDelayInMsecs   Delay in milliseconds.
     */
    virtual void SetTimeout(int64 iDelayInMsecs);

    /**
    * @brief   &lt; Timer.
    * @param   iDelayInSecs   Delay in seconds.
    */
    void SetTimeoutS(int64 iSeconds);

    /**
    * @brief   &lt; Timer.
    * @param   iDelayInTenths   Delay in tenths of second.
    */
    void SetTimeoutD(int64 iTenths);

    /**
     * @brief   Query if this object is timer set.
     * @return  true if timer set, false if not.
     */
    inline bool IsTimerSet() const noexcept;

    /**
     * @brief   Gets timer difference between current time and stored time.
     * @return  The timer difference.
     */
    int64 GetTimerDiff() const;

    /**
     * @brief   Query if this object is timer expired.
     * @return  true if timer expired, false if not.
     */
    inline bool IsTimerExpired() const;

    /**
     * @brief   Gets timer (in milliseconds).
     * @return  The adjusted timer.
     */
    int64 GetTimerAdjusted() const;

    /**
    * @brief   Gets timer in tenths of seconds.
    * @return  The adjusted timer.
    */
    int64 GetTimerDAdjusted() const;

    /**
    * @brief    Gets timer in seconds.
    * @return   The adjusted timer.
    */
    int64 GetTimerSAdjusted() const;
};


/* Inlined methods are defined here */

int64 CTimedObject::GetTimeoutRaw() const noexcept
{
    return _iTimeout;
}

void CTimedObject::ClearTimeout()
{
    _iTimeout = 0;
}

bool CTimedObject::IsSleeping() const
{
    return _fIsSleeping;
}

void CTimedObject::GoSleep()
{
    _fIsSleeping = true;
}

bool CTimedObject::IsTimerSet() const noexcept
{
    return (_iTimeout > 0);
}

bool CTimedObject::IsTimerExpired() const
{
    return (GetTimerDiff() <= 0);
}

PROFILE_TYPE CTimedObject::GetProfileType() const noexcept
{
    return _profileType;
}

#endif //_INC_CTIMEDOBJECT_H