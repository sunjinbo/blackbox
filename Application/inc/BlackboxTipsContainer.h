/* ====================================================================
 * File: BlackboxTipsContainer.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXTIPSCONTAINER_H
#define C_BLACKBOXTIPSCONTAINER_H

// INCLUDES
#include <aknview.h>
#include <akndef.h>

// FORWARD DECLARATIONS
class CBlackboxEditor;
class CAknsBasicBackgroundControlContext;
class CTips;
class CAnimation;
class CBlackboxTipsView;

// CLASS DECLARATION

/**
*  CBlackboxTipsContainer container control class.
*  An instance of CBlackboxTipsContainer contains the view drawn to the screen
*  for CBlackboxTipsView
*/
class CBlackboxTipsContainer : public CCoeControl
    {
public: // Constructors and destructor
    static CBlackboxTipsContainer* NewL( const TRect& aRect, CBlackboxTipsView& aTipsView );
    static CBlackboxTipsContainer* NewLC( const TRect& aRect, CBlackboxTipsView& aTipsView );
    virtual ~CBlackboxTipsContainer();

public: // new methods
    void SetTipsL( const CTips& aTips );

public: // from CoeControl
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl( TInt aIndex ) const;
    void Draw( const TRect& aRect ) const;
    void SizeChanged();
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    void HandleResourceChange( TInt aType );

private: // Constructor
    void ConstructL( const TRect& aRect );
    CBlackboxTipsContainer( CBlackboxTipsView& aTipsView );

private: // Data
    CBlackboxTipsView& iTipsView;
    CAnimation* iAnimation; // not owns
    CBlackboxEditor* iEditor; // owns
    CAknsBasicBackgroundControlContext* iBackGround; // owns
    };

#endif // C_BLACKBOXTIPSCONTAINER_H

// End of File
