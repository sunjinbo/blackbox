/* ====================================================================
 * File: Rays.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include "Rays.h"
#include "Lightbox.h"
#include "BoxHelper.h"
#include "BlackboxConfig.h"

// CONSTANTS
const TInt KRaysAnimTimeout = 1000;
const TInt KRaysAnimSpeed = 1;
const TInt KFirstIndex = 0;

// ============================ MEDirMBEDirR FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// TLine::TLine()
// ---------------------------------------------------------------------------
//
TLine::TLine()
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// TLine::TLine()
// ---------------------------------------------------------------------------
//
TLine::TLine( const TPoint& aFrom, const TPoint& aTo )
: iFrom( aFrom ), iTo( aTo )
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// TLine::Direction()
// ---------------------------------------------------------------------------
//
TDirection TLine::Direction() const
    {
    if ( iFrom.iX == iTo.iX && iFrom.iY > iTo.iY )
        {
        return EDirTop;
        }
    else if ( iFrom.iX == iTo.iX && iFrom.iY < iTo.iY )
        {
        return EDirBottom;
        }
    else if ( iFrom.iX > iTo.iX && iFrom.iY == iTo.iY )
        {
        return EDirLeft;
        }
    else if ( iFrom.iX < iTo.iX && iFrom.iY == iTo.iY )
        {
        return EDirRight;
        }
    else if ( iFrom.iX > iTo.iX && iFrom.iY > iTo.iY )
        {
        return EDirTopLeft;
        }
    else if ( iFrom.iX < iTo.iX && iFrom.iY < iTo.iY )
        {
        return EDirBottomRight;
        }
    else if ( iFrom.iX > iTo.iX && iFrom.iY < iTo.iY )
        {
        return EDirBottomLeft;
        }
    else if ( iFrom.iX < iTo.iX && iFrom.iY > iTo.iY )
        {
        return EDirTopRight;
        }
    else
        {
        return EDirCenter;
        }
    }

// ---------------------------------------------------------------------------
// CRays::NewL()
// ---------------------------------------------------------------------------
//
CRays* CRays::NewL( CLightbox& aLightbox )
    {
    CRays* self = new ( ELeave ) CRays( aLightbox );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }
    
// ---------------------------------------------------------------------------
// CRays::~CRays()
// ---------------------------------------------------------------------------
//
CRays::~CRays()
    {
    iLineArray.Reset();
    iLineArray.Close();
    delete iTimeout;
    }

// ---------------------------------------------------------------------------
// CRays::BuildRaysL()
// ---------------------------------------------------------------------------
//
void CRays::BuildRaysL()
    {
    // Clears old lines
    iLineArray.Reset();

    // Starts to build reays
    TDirection direction;
    GetLightboxDirection( direction );
    TPoint position = iLightbox.iPosition;
    TPoint start = SendOutPosition( direction, position );
    
    TLine line;
    line.iFrom = start;
    
    TLightboxState state;
    
    while ( ETrue )
        {
        Forward( direction, position );

        if ( iLightbox.iHelper.HasMirror( position.iX, position.iY ) )
            {
            line.iTo = line.iFrom;
            iLineArray.Append( line );
            iLightbox.UpdateStateL( EReflection );
            break;
            }
        else if ( NeighbourTest( direction, position ) )
            {
            line.iTo = line.iFrom;
            iLineArray.Append( line );
            iLightbox.UpdateStateL( EReflection );
            break;
            }
        else if ( FrontTest( direction, position ) )
            {
            line.iTo = SendInPosition( direction, position ); // ???
            iLineArray.Append( line );
            
            if ( iLineArray.Count() >= 2 )
                {
                state = EComplexReflection;
                }
            else
                {
                state = EReflection;
                }

            iLightbox.UpdateStateL( state );
            break;
            }
        else if ( SlopeTest( direction, position ) )
            {
            line.iTo = SendInPosition( EDirCenter, position );
            iLineArray.Append( TLine( line.iFrom, line.iTo ) );
            
            RArray<TPoint> array;
            GetNearestMirror( array, position );
            if ( array.Count() > 1 )
                {
                array.Close();

                if ( iLineArray.Count() > 2 )
                    {
                    state = EComplexReflection;
                    }
                else
                    {
                    state = EReflection;
                    }
                iLightbox.UpdateStateL( state );
                break;
                }
            else
                {
                direction = ReflectionDirection( line, array[0] );
                array.Close();
                line.iFrom = line.iTo;
                continue;
                }
            }
        else if ( LightboxTest( position ) )
            {
            line.iTo = SendInPosition( direction, position );
            iLineArray.Append( line );

            if ( iLineArray.Count() > 2 )
                {
                state = EComplexDeflection;
                }
            else
                {
                state = EDeflection;
                }

            if ( position != iLightbox.iPosition )
                {
                iLightbox.UpdateStateL( state );
                CBox* box = iLightbox.iHelper.Box( position.iX, position.iY );
                if ( box )
                    {
                    box->UpdateStateL( (TLightboxState)( state + 2 ) );
                    CLightbox* lightbox = static_cast<CLightbox*>( box );
                    lightbox->SetIndexId( iLightbox.iHelper.RaysCount() + 1 );
                    }
                }
            break;
            }
        else
            {
            continue;
            }
        }
    }

// ---------------------------------------------------------------------------
// CRays::Start()
// ---------------------------------------------------------------------------
//
void CRays::Start()
    {
    iAnim = ETrue;
    iAnimLineIndex = KFirstIndex;
    iAnimSpeed = KRaysAnimSpeed;
    iAnimPoint = iLineArray[iAnimLineIndex].iFrom;
    iTimeout->Start( KRaysAnimTimeout );
    }

// ---------------------------------------------------------------------------
// CRays::SetVisible()
// ---------------------------------------------------------------------------
//
void CRays::SetVisible( TBool aVisible )
    {
    iVisible = aVisible;
    }

// ---------------------------------------------------------------------------
// CRays::IsVisible()
// ---------------------------------------------------------------------------
//
TBool CRays::IsVisible() const
    {
    return iVisible;
    }

// ---------------------------------------------------------------------------
// CRays::SetObserver()
// ---------------------------------------------------------------------------
//
void CRays::SetObserver( MRaysObserver* aObserver )
    {
    iObserver = aObserver;
    }

// ---------------------------------------------------------------------------
// CRays::OnDraw()
// ---------------------------------------------------------------------------
//
void CRays::OnDraw()
    {
    if ( iVisible )
        {
        TRgb color = KRgbWhite;
        switch ( iLightbox.State() )
            {
            case EConceal:
                break;
            case EDeflection:
            case EDeflectionOut:
                color = KRgbDarkGreen;
                break;
            case EComplexDeflection:
            case EComplexDeflectionOut:
                color = KRgbBlue;
                break;
            case EReflection:
                color = KRgbYellow;
                break;
            case EComplexReflection:
                color = KRgbRed;
                break;
            default:
                break;
            }
        iLightbox.iHelper.BmpContext().SetPenColor( color );
        iLightbox.iHelper.BmpContext().SetPenStyle( CGraphicsContext::ESolidPen );
        iLightbox.iHelper.BmpContext().SetPenSize( TSize( 2, 2 ) );
        
        for ( TInt i = 0; i < iLineArray.Count(); i++ )
            {
            TPoint from = iLineArray[i].iFrom;
            TPoint to = iLineArray[i].iTo;
            iLightbox.iHelper.BmpContext().DrawLine( from, to );
            }
        
        if ( iAnim )
            {
            TRect animRect( iAnimPoint, TSize( 0, 0 ) );
            animRect.Grow( 3,3 );
            iLightbox.iHelper.BmpContext().SetPenStyle( CGraphicsContext::ESolidPen );
            iLightbox.iHelper.BmpContext().SetBrushColor( color );
            iLightbox.iHelper.BmpContext().SetBrushStyle( CGraphicsContext::ESolidBrush );
            iLightbox.iHelper.BmpContext().DrawEllipse( animRect );
            }

        iLightbox.iHelper.BmpContext().SetPenSize( TSize( 1, 1 ) );
        }
    }

// ---------------------------------------------------------------------------
// CRays::HandleTimeoutL()
// ---------------------------------------------------------------------------
//
void CRays::HandleTimeoutL()
    {
    switch ( iLineArray[iAnimLineIndex].Direction() )
        {
        case EDirTop:
            {
            --iAnimPoint.iY;
            }
            break;

        case EDirBottom:
            {
            ++iAnimPoint.iY;
            }
            break;

        case EDirLeft:
            {
            --iAnimPoint.iX;
            }
            break;

        case EDirRight:
            {
            ++iAnimPoint.iX;
            }
            break;

        case EDirTopLeft:
            {
            --iAnimPoint.iY;
            --iAnimPoint.iX;
            }
            break;

        case EDirTopRight:
            {
            --iAnimPoint.iY;
            ++iAnimPoint.iX;
            }
            break;

        case EDirBottomLeft:
            {
            ++iAnimPoint.iY;
            --iAnimPoint.iX;
            }
            break;

        case EDirBottomRight:
            {
            ++iAnimPoint.iY;
            ++iAnimPoint.iX;
            }
            break;

        case EDirCenter:
            break;

        default:
            break;
        }
    
    if ( iAnimPoint == iLineArray[iAnimLineIndex].iTo )
        {
        iAnimLineIndex++;
        if ( iAnimLineIndex < iLineArray.Count() )
            {
            if ( iAnimSpeed > 0 )
                {
                --iAnimSpeed;
                HandleTimeoutL();
                }
            else
                {
                iAnimSpeed = KRaysAnimSpeed;
                iTimeout->Start( KRaysAnimTimeout );
                }
            }
        else
            {
            iAnim = EFalse;
            // notify rays'observer that anim is completed
            if ( iObserver )
                {
                iObserver->AnimCompltedL();
                }
            }
        }
    else
        {
        if ( iAnimSpeed > 0 )
            {
            --iAnimSpeed;
            HandleTimeoutL();
            }
        else
            {
            iAnimSpeed = KRaysAnimSpeed;
            iTimeout->Start( KRaysAnimTimeout );
            }
        }
    }

// ---------------------------------------------------------------------------
// CRays::ConstructL()
// ---------------------------------------------------------------------------
//
void CRays::ConstructL()
    {
    BuildRaysL();
    
    iTimeout = CRegistrationTimeout::NewL( *this );
    }

// ---------------------------------------------------------------------------
// CRays::CRays()
// ---------------------------------------------------------------------------
//
CRays::CRays( CLightbox& aLightbox )
: iLightbox( aLightbox )
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// CRays::Forward()
// ---------------------------------------------------------------------------
//
void CRays::Forward( TDirection aDirection, TPoint& aNewPos )
    {
    switch ( aDirection )
        {
        case EDirTop:
            aNewPos.iY -= 1;
            break;
        case EDirBottom:
            aNewPos.iY += 1;
            break;
        case EDirLeft:
            aNewPos.iX -= 1;
            break;
        case EDirRight:
            aNewPos.iX += 1;
            break;
        case EDirTopLeft:
            aNewPos.iX -= 1;
            aNewPos.iY -= 1;
            break;
        case EDirTopRight:
            aNewPos.iX += 1;
            aNewPos.iY -= 1;
            break;
        case EDirBottomLeft:
            aNewPos.iX -= 1;
            aNewPos.iY += 1;
            break;
        case EDirBottomRight:
            aNewPos.iX += 1;
            aNewPos.iY += 1;
            break;
        case EDirCenter:
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CRays::SlopeTest()
// ---------------------------------------------------------------------------
//
TBool CRays::SlopeTest( TDirection aDirection, const TPoint& aPos )
    {
    TBool retVal( EFalse );
    switch ( aDirection )
        {
        case EDirTop:
            {
            if ( iLightbox.iHelper.HasMirror( aPos.iX - 1, aPos.iY - 1 )
                || iLightbox.iHelper.HasMirror( aPos.iX + 1, aPos.iY - 1 ) )
                {
                retVal = ETrue;
                }
            break;
            }
        case EDirBottom:
            {
            if ( iLightbox.iHelper.HasMirror( aPos.iX - 1, aPos.iY + 1 )
                || iLightbox.iHelper.HasMirror( aPos.iX + 1, aPos.iY + 1 ) )
                {
                retVal = ETrue;
                }
            break;
            }
        case EDirLeft:
            {
            if ( iLightbox.iHelper.HasMirror( aPos.iX - 1, aPos.iY - 1 )
                || iLightbox.iHelper.HasMirror( aPos.iX - 1, aPos.iY + 1 ) )
                {
                retVal = ETrue;
                }
            break;
            }
        case EDirRight:
            {
            if ( iLightbox.iHelper.HasMirror( aPos.iX + 1, aPos.iY - 1 ) 
                || iLightbox.iHelper.HasMirror( aPos.iX + 1, aPos.iY + 1 ) )
                {
                retVal = ETrue;
                }
            break;
            }
        case EDirTopLeft:
        case EDirTopRight:
        case EDirBottomLeft:
        case EDirBottomRight:
        case EDirCenter: 
        default:
            break;
        }
    return retVal;
    }

// ---------------------------------------------------------------------------
// CRays::FrontTest()
// ---------------------------------------------------------------------------
//
TBool CRays::FrontTest( TDirection aDirection, const TPoint& aPos )
    {
    TBool retVal( EFalse );
    switch ( aDirection )
        {
        case EDirTop:
            {
            if ( iLightbox.iHelper.HasMirror( aPos.iX, aPos.iY - 1 ) )
                {
                retVal = ETrue;
                }
            break;
            }
        case EDirBottom:
            {
            if ( iLightbox.iHelper.HasMirror( aPos.iX, aPos.iY + 1 ) )
                {
                retVal = ETrue;
                }
            break;
            }
        case EDirLeft:
            {
            if ( iLightbox.iHelper.HasMirror( aPos.iX - 1, aPos.iY ) )
                {
                retVal = ETrue;
                }
            break;
            }
        case EDirRight:
            {
            if ( iLightbox.iHelper.HasMirror( aPos.iX + 1, aPos.iY ) )
                {
                retVal = ETrue;
                }
            break;
            }
        case EDirTopLeft:
        case EDirTopRight:
        case EDirBottomLeft:
        case EDirBottomRight:
        case EDirCenter: 
        default:
            break;
        }
    return retVal;
    }

// ---------------------------------------------------------------------------
// CRays::NeighbourTest()
// ---------------------------------------------------------------------------
//
TBool CRays::NeighbourTest( TDirection aDirection, const TPoint& aPos )
    {
    TBool retVal( EFalse );
    switch ( aDirection )
        {
        case EDirTop:
        case EDirBottom:
            {
            if ( iLightbox.iHelper.HasMirror( aPos.iX - 1, aPos.iY )
                || iLightbox.iHelper.HasMirror( aPos.iX + 1, aPos.iY ) )
                {
                retVal = ETrue;
                }
            break;
            }

        case EDirLeft:
        case EDirRight:
            {
            if ( iLightbox.iHelper.HasMirror( aPos.iX, aPos.iY + 1 )
                || iLightbox.iHelper.HasMirror( aPos.iX, aPos.iY - 1 ) )
                {
                retVal = ETrue;
                }
            break;
            }

        case EDirTopLeft:
        case EDirTopRight:
        case EDirBottomLeft:
        case EDirBottomRight:
        case EDirCenter: 
        default:
            break;
        }
    return retVal;
    }

// ---------------------------------------------------------------------------
// CRays::LightboxTest()
// ---------------------------------------------------------------------------
//
TBool CRays::LightboxTest( const TPoint& aPos )
    {
    if ( aPos.iX == 0 
        || aPos.iY == 0
        || aPos.iX == KHorizBoxNumber - 1 
        || aPos.iY == KVerticalBoxNumber - 1 )
        {
        return ETrue;
        }
    return EFalse;
    }

// ---------------------------------------------------------------------------
// CRays::GetLightboxDirection()
// ---------------------------------------------------------------------------
//
void CRays::GetLightboxDirection( TDirection& aDirection )
    {
    if ( iLightbox.iPosition.iX == 0 )
        {
        aDirection = EDirRight;
        }
    else if ( iLightbox.iPosition.iX == KHorizBoxNumber - 1 )
        {
        aDirection = EDirLeft;
        }
    else if ( iLightbox.iPosition.iY == 0 )
        {
        aDirection = EDirBottom;
        }
    else if ( iLightbox.iPosition.iY == KVerticalBoxNumber - 1 )
        {
        aDirection = EDirTop;
        }
    else
        {
        aDirection = EDirCenter;
        }
    }

// ---------------------------------------------------------------------------
// CRays::GetNearestMirror()
// ---------------------------------------------------------------------------
//
void CRays::GetNearestMirror( RArray<TPoint>& aMirrorArray, const TPoint& aPos )
    {
    for ( TInt i = aPos.iX - 1; i <= aPos.iX + 1; i++ )
        for ( TInt j = aPos.iY - 1; j <= aPos.iY + 1; j++ )
            {
            if ( iLightbox.iHelper.HasMirror( i, j ) )
                {
                aMirrorArray.Append( TPoint( i, j ) );
                }
            }
    }

// ---------------------------------------------------------------------------
// CRays::SendOutPosition()
// ---------------------------------------------------------------------------
//
TPoint CRays::SendOutPosition( TDirection aDirection, const TPoint& aPos )
    {
    TPoint position(0,0);
    TRect rect = iLightbox.iHelper.BoxRect( aPos.iX, aPos.iY );
    switch ( aDirection )
        {
        case EDirTop:
            position.iX = rect.iTl.iX + rect.Width() / 2;
            position.iY = rect.iTl.iY;
            break;
        case EDirBottom:
            position.iX = rect.iBr.iX - rect.Width() / 2;
            position.iY = rect.iBr.iY;
            break;
        case EDirLeft:
            position.iX = rect.iTl.iX;
            position.iY = rect.iTl.iY + rect.Height() / 2;
            break;
        case EDirRight:
            position.iX = rect.iBr.iX;
            position.iY = rect.iBr.iY - rect.Height() / 2;
            break;
        case EDirTopLeft:
        case EDirTopRight:
        case EDirBottomLeft:
        case EDirBottomRight:
            break;
        case EDirCenter: 
            position = rect.Center();
            break;
        default:
            break;
        }
    return position;
    }

// ---------------------------------------------------------------------------
// CRays::SendInPosition()
// ---------------------------------------------------------------------------
//
TPoint CRays::SendInPosition( TDirection aDirection, const TPoint& aPos )
    {
    TPoint position(0,0);
    TRect rect = iLightbox.iHelper.BoxRect( aPos.iX, aPos.iY );
    switch ( aDirection )
        {
        case EDirBottom:
            position.iX = rect.iTl.iX + rect.Width() / 2;
            position.iY = rect.iTl.iY;
            break;
        case EDirTop:
            position.iX = rect.iBr.iX - rect.Width() / 2;
            position.iY = rect.iBr.iY;
            break;
        case EDirRight:
            position.iX = rect.iTl.iX;
            position.iY = rect.iTl.iY + rect.Height() / 2;
            break;
        case EDirLeft:
            position.iX = rect.iBr.iX;
            position.iY = rect.iBr.iY - rect.Height() / 2;
            break;
        case EDirTopLeft:
        case EDirTopRight:
        case EDirBottomLeft:
        case EDirBottomRight:
            break;
        case EDirCenter: 
            position = rect.Center();
            break;
        default:
            break;
        }
    return position;
    }

// ---------------------------------------------------------------------------
// CRays::ReflectionDirection()
// ---------------------------------------------------------------------------
//
TDirection CRays::ReflectionDirection( const TLine& aLine, const TPoint& aMirror )
    {
    TDirection direction( aLine.Direction() );
    TRect theRect = iLightbox.iHelper.BoxRect( aMirror.iX, aMirror.iY );
    TPoint mirror = theRect.Center();
    
    if ( aLine.iTo.iX < mirror.iX && aLine.iTo.iY > mirror.iY ) // top right
        {
        if ( direction == EDirRight )
            {
            direction = EDirBottom;
            }
        if ( direction == EDirTop )
            {
            direction = EDirLeft;
            }
        }
    else if ( aLine.iTo.iX < mirror.iX && aLine.iTo.iY < mirror.iY ) // bottom right
        {
        if ( direction == EDirRight )
            {
            direction = EDirTop;
            }
        if ( direction == EDirBottom )
            {
            direction = EDirLeft;
            }
        }
    else if ( aLine.iTo.iX > mirror.iX && aLine.iTo.iY > mirror.iY ) // top left
        {
        if ( direction == EDirLeft )
            {
            direction = EDirBottom;
            }
        if ( direction == EDirTop )
            {
            direction = EDirRight;
            }
        }
    else if ( aLine.iTo.iX > mirror.iX && aLine.iTo.iY < mirror.iY ) // bottom left
        {
        if ( direction == EDirLeft )
            {
            direction = EDirTop;
            }
        if ( direction == EDirBottom )
            {
            direction = EDirRight;
            }
        }
    else
        {
        direction = EDirCenter;
        }
    return direction;
    }

// End of file

