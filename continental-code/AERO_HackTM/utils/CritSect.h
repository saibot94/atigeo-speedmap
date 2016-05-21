/******************************************************************************/
/* File:    CritSect.h                                                        */
/* purpose: some utilitys from handling CriticalSections                      */
/* created: 07.03.2008, Grotendorst (TZS, Continental Teves)                  */
/******************************************************************************/
#ifndef CRITSECT_H
#define CRITSECT_H

#if (LIBTG_USE_NAMESPACE)
namespace LibTG
{
#endif

class CCritSectImpl;

/**
* CCritSectLocker provides mutual exclusion.
* The common usage is like this:
* critSect.lock();
* // critical region
* critSect.unlock();
* You might want to use a CritSectLocker to lock() and unlock() a critSect.
* A CCritSectLocker unlocks the thread automatically, when the locker is deleted. */
class CCritSect
{
public:

    CCritSect();
    virtual ~CCritSect();

    /* Locks the critsect. If the critsect is already locked, this functions blocks until the critsect is unlocked again. */
    virtual void Lock();

    /* Try to lock the critsect. return true if the lock has been acquired, otherwise false */
    virtual bool TryLock();

    /* Unlocks the critsect again. */
    virtual void Unlock();

private:
    friend class CCritSectImpl;
    CCritSectImpl* mpImpl;
};


/**
* The CritSectLocker is a helper class to lock and unlock a CritSect.
*
* It can be used as follows:
* void func() {
*   CCritSectLocker locker(&critsect); // lock immediately
*   // now the critsect is locked
* } // locker is destroyed and unlocks the critsect automatically
* After func() the CCritSectLocker is destroyed, as it leaves the valid scope.
* This is especially useful if you use a critsect in a thread that can be
* canceled. A corresponding unlock() could then be missing.
* However, a local variable is always destroyed, that is, CCritSectLocker will
* always unlock the critsect. */
class CCritSectLocker
{
public:
    /* Constructor. Locks the critsect immediately. Param critsect critsect, which must not be null */
    CCritSectLocker(CCritSect *pCritSect);
    
    /* Destructor. On destruction, the critsect gets automatically unlocked. */
    ~CCritSectLocker();

private:
    CCritSect *mpCritSect;
};

#if (LIBTG_USE_NAMESPACE)
}
#endif

#endif
