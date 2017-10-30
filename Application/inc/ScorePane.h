/* ====================================================================
 * File: ScorePane.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCOREPANE_H
#define C_SCOREPANE_H

// INCLUDES
#include <coecntrl.h>
#include "Blackbox.hrh"

// FORWARD DECLARATIONS
class CFbsBitGc;
class CLayoutManager;
class CBlackboxBmpUtils;
class TBlackboxSettings;

// CLASS DECLARATION

/**
 *  CScorePane class
 */
class CScorePane : public CCoeControl
    {
public: // friend class
    friend class CSceneTask;

public: // Constructors and destructor
    static CScorePane* NewL( 
            CFbsBitGc& aBmpContext, TBlackboxSettings& aSettings );
    virtual ~CScorePane();

public: // New methods
    void OnDraw();
    void Reset();
    void AddGuess();
    void RemoveGuess();
    void SetGuess();
    void SetGuessing();
    void SetGuessSuccess();
    void AddRay();

private: // Symbian 2nd Constructors
    void ConstructL();
    CScorePane( CFbsBitGc& aBmpContext, TBlackboxSettings& aSettings );

private: // New methods
    void ScaleBmpUtils();
    TInt CurrentGuessIndex() const;

private: // Internal class
    class TDrawerItem
        {
    public: // Enums
        enum TDrawerType
            {
            EDrawerUnguess,
            EDrawerGuess,
            EDrawerGuessing,
            EDrawerGuessSuccess
            };
        TDrawerType iDrawerType;
        TRect iRect;
        };

private: // Data
    CFbsBitGc& iBmpContext;
    TBlackboxSettings& iSettings;
    CLayoutManager* iLayoutManager; // owned
    CBlackboxBmpUtils* iBmpUtils; // owned
    RArray<TDrawerItem> iDrawerItemArray;
    TBool iEffectGuessRevert;
    TInt iEffectGuessBitmapId;
    TInt iEffectGradualFrequency;
    TInt iNumberOfRays;
    };

#endif // C_SCOREPANE_H
