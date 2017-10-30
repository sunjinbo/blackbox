/* ====================================================================
 * File: Rays.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_RAYS_H
#define C_RAYS_H

// INCLUDES
#include <e32base.h>
#include "DrawerBehavior.h"
#include "RegistrationTimeout.h"

// ENUMS
enum TDirection
    {
    EDirTop,
    EDirBottom,
    EDirLeft,
    EDirRight,
    EDirTopLeft,
    EDirTopRight,
    EDirBottomLeft,
    EDirBottomRight,
    EDirCenter 
    };

// FORWARD DECLARATIONS
class CLightbox;

// CLASS DECLARATION

/*
 *  TLine class
 */
class TLine
    {
public: // Constructor
    TLine();
    TLine( const TPoint& aFrom, const TPoint& aTo );
    TDirection Direction() const;
    
public: // Data
    TPoint iFrom;
    TPoint iTo;
    };

/**
 *  MRaysObserver class
 */
class MRaysObserver
    {
public: // callback function
    virtual void AnimCompltedL() = 0;
    };

/**
 *  CRays class
 */
class CRays : public CBase, 
        public MDrawerBehavior, public MTimeoutCallback
    {
public:   // Constructors and destructor
    static CRays* NewL( CLightbox& aLightbox );
    virtual ~CRays();
    
public: // new methods
    void BuildRaysL();
    void Start();
    void SetVisible( TBool aVisible );
    TBool IsVisible() const;
    void SetObserver( MRaysObserver* aObserver );
    
public: // from MDrawerBehavior
    void OnDraw();

public: // from MTimeoutCallback
    void HandleTimeoutL();

private:   // Symbian 2nd Constructors
    void ConstructL();
    CRays( CLightbox& aLightbox );

private: // New methods
    void Forward( TDirection aDirection, TPoint& aNewPos );
    TBool SlopeTest( TDirection aDirection, const TPoint& aPos );
    TBool FrontTest( TDirection aDirection, const TPoint& aPos );
    TBool NeighbourTest( TDirection aDirection, const TPoint& aPos );
    TBool LightboxTest( const TPoint& aPos );
    void GetLightboxDirection( TDirection& aDirection );
    void GetNearestMirror( RArray<TPoint>& aMirrorArray, const TPoint& aPos );
    TPoint SendOutPosition( TDirection aDirection, const TPoint& aPos );
    TPoint SendInPosition( TDirection aDirection, const TPoint& aPos );
    TDirection ReflectionDirection( const TLine& aLine, const TPoint& aMirror );

private: // Data
    CLightbox& iLightbox;
    MRaysObserver* iObserver; // not owned
    CRegistrationTimeout* iTimeout; // owned
    RArray<TLine> iLineArray;
    TInt iRaysId;
    TBool iVisible;
    TBool iAnim;
    TPoint iAnimPoint;
    TInt iAnimLineIndex;
    TInt iAnimSpeed;
    };

#endif // C_RAYS_H


// End of File
