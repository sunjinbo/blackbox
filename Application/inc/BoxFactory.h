/* ====================================================================
 * File: BoxFactory.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BOXFACTORY_H
#define C_BOXFACTORY_H

// INCLUDES
#include <e32base.h>
#include "BlackboxSettings.h"

// FORWARD DECLARATIONS
class CSceneModel;
class CBox;
class CMirror;

// CLASS DECLARATION

/**
 *  CBoxFactory class
 */
class CBoxFactory : public CBase
    {
public:   // Constructor & Destructor
    static CBoxFactory* NewL( CSceneModel& aModel, TBlackboxSettings& aSettings );
    virtual ~CBoxFactory(){}

public: // New functions
    void GetBoxArrayL( RPointerArray<CBox>& aBoxArray );
    void GetMirrorArrayL( RPointerArray<CMirror>& aMirrorArray );
    void SetSettings( const TBlackboxSettings& aSettings );
    
private:   // Symbian 2nd Constructors
    void ConstructL();
    CBoxFactory( CSceneModel& aModel, TBlackboxSettings& aSettings );

private: // New data
    TInt Rand( TInt aRange ) const;

private: // Data
    CSceneModel& iModel;
    TBlackboxSettings& iSettings;
    };

#endif // C_BOXFACTORY_H


// End of File
