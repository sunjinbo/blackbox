/* ====================================================================
 * File: BlackboxUtils.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */


#ifndef T_BLACKBOXUTILS_H
#define T_BLACKBOXUTILS_H

// INCLUDE FILES
#include <e32std.h>
#include <e32base.h>

// CONSTANS
_LIT( KBlackboxBlackboxragraphBreak, "\u2029" );
_LIT( KBlackboxLineBreak, "\u2028" );

// STRUCTURES
typedef struct
    {
    TInt iLeftMargin;
    TInt iRightMargin;
    TInt iTopMargin;
    TInt iBottomMargin;
    } TBlackboxPromoMargins;

typedef struct
    {
    TInt iHeight;
    TInt iWidthMod;
    TInt iHorizontalPosMod;
    TInt iVerticalPosMod;
    } TBlackboxListBoxTweaks;

#define KBlackboxLinebreakCharLength 2


// FORWARD DECLARATION
class CGulIcon;
class TBlackboxUtils
    {
public:

    enum TBlackboxDisplayMode
        {
        /**
         * QVGA 
         */
        EBlackboxDisplayModeQVGA = 0,

        /**
         * QHD
         */
        EBlackboxDisplayModeQHD,
        
        /**
         * VGA
         */
        EBlackboxDisplayModeVGA
        };


    static TBlackboxPromoMargins GetMargins();
    static TBlackboxListBoxTweaks GetListBoxTweaks();
    static CGulIcon* CreateIconL(TInt aBitmap, TInt aMask=0);
    static void AddIconL(CArrayPtr<CGulIcon>& aIconList, TInt aBitmap,
            TInt aMask);
    static void FixLineBreaks(HBufC* aMessage);
    static void AppendLoadTextL(HBufC* aText, TInt aResourceId);
    static void ReplaceLineBreakWithTab(HBufC* aMessage);
    static HBufC* LoadCheckboxLabelLC(TInt aResourceId, TInt aIcon);
private:
    static TInt GetDisplayMode();
    static void ReplaceAll(TDes& aText, const TDesC& aOld, const TDesC& aNew);
public:
    static TBuf<KBlackboxLinebreakCharLength> iBlackboxragraphBreak;
    static TBuf<KBlackboxLinebreakCharLength> iLineBreak;
    };

#endif // T_BLACKBOXUTILS_H

// End of file
