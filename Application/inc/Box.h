/* ====================================================================
 * File: Box.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BOX_H
#define C_BOX_H

// INCLUDES
#include <e32base.h>
#include "TriggerBehavior.h"
#include "DrawerBehavior.h"

// FORWARD DECLARATIONS
class MBoxObserver;
class MBoxHelper;

// CLASS DECLARATION

/**
 *  CBox class
 */
class CBox : public CBase, 
          public MTriggerBehavior, public MDrawerBehavior
    {
public:   // Destructor
    virtual ~CBox(){}

public: // New methods
    TPoint Position() const;
    static TBool Compare( const CBox& aFirst, const CBox& aSecond );

public: // Interface methods
    virtual void UpdateStateL( TInt aState ) = 0;
    virtual TInt State() const = 0;

protected:   // Symbian 2nd Constructors
    void ConstructL();
    CBox( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos );

protected: // Data
    MBoxObserver& iObserver;
    MBoxHelper& iHelper;
    TPoint iPosition;
    };

#endif // C_BOX_H


// End of File
