/* ====================================================================
 * File: IntroImage.cpp
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <fbs.h>
#include <AknIconUtils.h>
#include <aknenv.h>
#include <AknUtils.h>
#include <aknconsts.h>
#include <AknBidiTextUtils.h>
#include <AknsDrawUtils.h> 
#include <AknsBasicBackgroundControlContext.h>
#include <AknsConstants.h>
#include <AknDef.h>
#include "IntroImage.h"

// CONSTANTS
const TInt QtnJavaLogoWidth  = 46;
const TInt QtnJavaLogoHeight = 70;

// ================= MEMBER FUNCTIONS ==========================================

// -----------------------------------------------------------------------------
// CIntroImage::CIntroImage()
// -----------------------------------------------------------------------------
CIntroImage::CIntroImage()
    {
    }

// -----------------------------------------------------------------------------
// CIntroImage::~CIntroImage()
// -----------------------------------------------------------------------------
CIntroImage::~CIntroImage()
    {
    delete iBitmap;
    delete iBitmapMask;
    }

// -----------------------------------------------------------------------------
// CIntroImage::NewLC()
// -----------------------------------------------------------------------------
CIntroImage* CIntroImage::NewLC( const TDesC& aFileName,
                                 TInt aBitmapId,
                                 TInt aStartLine,
                                 TInt aBaseLineDelta,
                                 TBool aTypeFlag )
    {
    CIntroImage* self = new( ELeave ) CIntroImage();
    CleanupStack::PushL( self );

    if( aTypeFlag )
        {
        // bmp files
        self->iBitmap  = AknIconUtils::CreateIconL(aFileName, aBitmapId );
        }
    else
    	{
    	// svg files
    	MAknsSkinInstance* skinInstance = AknsUtils::SkinInstance();
    	AknsUtils::CreateIconL( skinInstance, KAknsIIDQgnMenuSmsvoLst, self->iBitmap, self->iBitmapMask, 
					aFileName, aBitmapId, aBitmapId + 1 );
    	AknIconUtils::SetSize( self->iBitmap, TSize( QtnJavaLogoWidth, QtnJavaLogoHeight ) );
    	AknIconUtils::SetSize( self->iBitmapMask, TSize( QtnJavaLogoWidth, QtnJavaLogoHeight ) );
    	}
    self->iStartLine = aStartLine;

    // enough lines so that image and margins fit in them.

    TInt lines( ( self->HeightInPixels() + 
                  KImageTopMargin + 
                  KImageBottomMargin +
                  aBaseLineDelta - 1 ) / aBaseLineDelta );

    self->iEndLine = aStartLine + lines - 1;
    return self;
    }

// -----------------------------------------------------------------------------
// CIntroImage::HeightInPixels()
// -----------------------------------------------------------------------------
TInt CIntroImage::HeightInPixels() const
    {
    return iBitmap->SizeInPixels().iHeight;
    }

// -----------------------------------------------------------------------------
// CIntroImage::WidthInPixels()
// -----------------------------------------------------------------------------
TInt CIntroImage::WidthInPixels() const
    {
    return iBitmap->SizeInPixels().iWidth;
    }

// -----------------------------------------------------------------------------
// CIntroImage::StartLine()
// -----------------------------------------------------------------------------
TInt CIntroImage::StartLine() const
    {
    return iStartLine;
    }

// -----------------------------------------------------------------------------
// CIntroImage::EndLine()
// -----------------------------------------------------------------------------
TInt CIntroImage::EndLine() const
    {
    return iEndLine;
    }

// -----------------------------------------------------------------------------
// CIntroImage::Lines()
// -----------------------------------------------------------------------------
TInt CIntroImage::Lines() const
    {
    return iEndLine - iStartLine + 1;
    }

// -----------------------------------------------------------------------------
// CIntroImage::Bitmap()
// -----------------------------------------------------------------------------
const CFbsBitmap* CIntroImage::Bitmap() const
    {
    return iBitmap;
    }

// -----------------------------------------------------------------------------
// CIntroImage::BitmapMask()
// -----------------------------------------------------------------------------
const CFbsBitmap* CIntroImage::BitmapMask() const
	{
	return iBitmapMask;
	}

// End of File  
