/* ====================================================================
 * File: Logger.h
 * Created: 04/13/09
 * Modified: 05/08/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef LOGGER_H
#define LOGGER_H

#define _DEBUG

#ifdef _DEBUG

// INCLUDE FILES
#include <flogger.h>
#include <eikenv.h>

// log files are stored to KDebugLogDirFull folder
_LIT( KDebugLogDependency,       "C:\\Logs\\" );
_LIT( KDebugLogDoubleBackSlash,  "\\" );

_LIT( KDebugLogDir,               "Blackbox");
_LIT( KDebugLogFile,              "Blackbox.log");
_LIT( KDebugLogEnterFn,           "Blackbox: -> %S" );
_LIT( KDebugLogLeaveFn,           "Blackbox: <- %S" );
_LIT( KDebugLogTimeFormatString,  " [%H:%T:%S:%*C3]" );

// MACROS

/**
* Use this macro in order to initialize logger :
* - create log directory,
* - write version information into the log file
*/
#define CREATE_INFO_FILE { TFileName path( KDebugLogDependency ); path.Append( KDebugLogDir ); path.Append( KDebugLogDoubleBackSlash ); RFs fs; CleanupClosePushL(fs); User::LeaveIfError( fs.Connect() ); fs.MkDirAll( path ); CleanupStack::PopAndDestroy( &fs ); }

/**
* Use this function at any points of a function for logging the current state.
* @param a String to be written into logfile about the current state
*/
#define INFO( a ) { _LIT( temp, a ); RFileLogger::Write( KDebugLogDir, KDebugLogFile, EFileLoggingModeAppend, temp ); RDebug::Print(temp);}

/**
* Use this function at any points of a function for logging the current state.
* You can use printf-like formats, but with only one parameter to be substituted..
* @param a Format string,
* @param b Parameter to be substituted.
*/
#define INFO_1( a, b ) { _LIT( temp, a ); RFileLogger::WriteFormat( KDebugLogDir, KDebugLogFile, EFileLoggingModeAppend, temp, b ); RDebug::Print( temp, b);}

/**
* Use this function at any points of a function for logging the current state.
* @param a String to be written into logfile about the current state
*/
#define INFO_WRITE_TDES( a ) { RFileLogger::Write( KDebugLogDir, KDebugLogFile, EFileLoggingModeAppend, a ); RDebug::Print( a );}

/**
* Use this function at any points of a function for logging the current state.
* The current date/time stamp is written besides the string you give.
* @param a String to be written into logfile about the current state
*/
#define INFO_WRITE_TIMESTAMP( a ) { _LIT( temp, a ); TTime time; time.HomeTime(); TBuf<256> buffer; time.FormatL( buffer, KDebugLogTimeFormatString ); buffer.Insert( 0, temp ); RFileLogger::Write( KDebugLogDir, KDebugLogFile, EFileLoggingModeAppend, buffer); RDebug::Print( buffer );}

#else // _DEBUG

// Empty macros
#define CREATE_INFO_FILE
#define INFO( a )
#define INFO_1( a, b )
#define INFO_WRITE_TDES( a )
#define INFO_WRITE_TIMESTAMP( a )

#endif // _DEBUG

#endif // LOGGER_H

// End of file
