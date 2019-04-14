/** \mainpage GCGlib Documentation
  \section geninfo General information
  \author Marcelo Bernardes Vieira, Tássio Knop de Castro, Eder de Almeida Perez,
          Daniel Madeira, Patrícia Pereira Pampanelli, Virgínia Fernandes Mota,
          Thales Luis Rodrigues Sabino, Dhiego Cristiano Oliveira da Silva Sad,
          João Vitor de Sá Hauck, Pedro Henrique Fialho, Thiago de Oliveira Quinelato,
          Luiz Maurílio Maciel
  \pre       Make sure you have all libraries indicated as dependencies in this documentations installed.
  \warning   Careful destruction of object instances is recommended. Read documentation.
  \warning   All class attributes may be read directly but must not be changed. Read documentation.

GCGlib cross-platform library concentrates all methods and algorithms developed by GCG
researchers and students since 2007. It is a software repository intended to be used in
all GCG projects and researchs. Our library is also applied in the development of technological
products for commercial and industrial purposes.

The library provides robust and reliable code for Linux and Microsoft Windows systems. For
Linux, 32 bits and 64 bits, Shared Object libraries are available. Under Microsoft Windows,
GCGlib 32 bits DLL (Dynamic Linked Library) is available for MinGW using GNU C/C++. DLL libraries
with 32 bits and 64 bits for Microsoft Studio Visual C/C++ are also deployed.

Most implemented algorithms are versions of well-known, public domain, methods. As GCGlib is being
developed, algorithms can be adapted and enhanced to support our projects needs. Theoretical
and technical knowledge in computer graphics, signal processing and computer vision is
accumulated along this process. GCGlib includes functions and classes for:

- 2D and 3D visualization
- Subdivision schemes for adaptive surfaces
- Geometry processing
- Signal, video and image processing
- Linear algebra
- Camera and projector calibration
- Physics simmulation
- Statistics and data analysis
- Multitask management
- Network communication

\section license GCGlib License

Copyright © 2007-2012 Group for Computer Graphics, Image and Vision.

Permission is hereby granted, free of charge, to any researcher, student, professor or collaborator,
provided that is officially affiliated or in cooperation with the GCG, that obtain a copy of this
software and associated documentation files (the "Software"), to deal in the Software for research
 or educational purposes except for commercial, industrial and other profit activity, without
limitation to use, copy, modify and merge, subject to the following conditions:

- The above copyright notice and this permission notice shall be fully included in all copies
or substantial portions of the Software.

- A complete citation to GCGlib version, GCG laboratory and to the website www.gcg.ufjf.br
shall be included in all works, texts, pages, articles, reports, papers, websites, prototypes,
books, dissertations, thesis, and all other types of public communications, published into any
kind of media, printed or electronic, having part or all of its results or contents obtained
using the Software.

- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


  \section runtime Using GCGlib library

GCGlib is deployed in a single library, along with the header gcg.h, as a Shared Object (.so) in Linux and Dynamic Linked Library (.dll) in Windows.

In Windows, the dynamic library is a link free object. This means that no library must be linked to your project in order
to satisfy GCGlib dependencies. In runtime, however, GCGlib depends upon several DLLs that must be instaled in your system.
Currently, you must have installed (or put in the same directory of GCGlib) glu32.dll, pthreadGC2.dll (MinGW projects) or
pthreadVC2.dll (Visual C++ projects). Other DLLs (opengl32.dll for instance) are needed but they are usually distributed
by default in Windows.

In Linux systems, shared objects are libraries that are linked upon execution. Thus, all .so that GCGlib depends on must
be installed. Most of them are installed by default when using GNU compilers (librt for example) or common applications.
Make sure the proper development packages for glu, opengl and jpeg are available.

  \section building Building GCGlib library and its documentation

Windows 32 bits: mingw32 must be installed in your linux or windows system. Check the compiler path in makefile.

\verbatim
            make gcg32.dll
\endverbatim

Linux 32 bits: shared object

\verbatim
            make libgcg32.so
\endverbatim

Linux 64 bits: shared object

\verbatim
            make libgcg64.so
\endverbatim

Documentation: doxygen (at least 1.7.5) must be installed in your system

\verbatim
            make doc
\endverbatim

To build all targets and documentation:

\verbatim
            make all
\endverbatim

Generating a new version number and information: requires GIT

\verbatim
            make version
\endverbatim

GCGlib building dependencies for Windows (MinGW):
- libgdi32.a, libkernel32.a, libuser32.a, libwinmm.a, libwsock32.a
- libopengl32.a, libglut32.a, libglu32.a
- A compiled version of the libjpeg.a and libpthreadGC2.a are provided


GCGlib building dependencies for Windows (Microsoft Visual C++):
- winmm.lib, Ws2_32.lib, strmiids.lib opengl32.lib (Windows SDK)
- glu32.lib
- A compiled version of the libjpeg32.lib, libjpeg64.lib, pthreadVC2.lib and strmbase.lib (DirectShow samples in Windows SDK) are provided

GCGlib building dependencies for Linux:
- jpeg, pthread, rt, socket, GL, GLU

  \section vercomp Version compatibility

   Versions of GCGlib have the form:  major.minor.revision

\verbatim
Original Version    New Version    Compatible?
  2.20.5              2.20.9         Yes     Compatibility across revision/patch versions is guaranteed.
  2.20.5              2.20.1         Yes     Compatibility across revision/patch versions is guaranteed.
  2.20.5              2.21.2         No      Compatibility with different minor versions is not guaranteed.
  2.20.5              3.0.0          No      Compatibility with different major versions is not guaranteed.
\endverbatim

While some of the cells say "no", it is possible that the versions may be compatible, depending upon the particular functionalities used by the application.

Revision numbers are sequential. But the evolution of major and minor depends on how many or how much changes have occured.

  \section source GCGlib source repository

GCGlib GIT repository is hosted at https://www.gcg.ufjf.br/git/gcglib. To clone it, use:

\verbatim
     git clone https://www.gcg.ufjf.br/git/gcglib
\endverbatim

  or

\verbatim
     git clone https://user_name@www.gcg.ufjf.br/git/gcglib
\endverbatim


The second option will launch the default SSH password dialog (normally a graphical tool). To use the
terminal to enter the password, make SSH_ASKPASS empty as follows

\verbatim
     export SSH_ASKPASS=
\endverbatim

In order to use SSL protocol with a security certificate not issued by a "certification authority",
execute the following command to disable the global SSL verification:

\verbatim
     export GIT_SSL_NO_VERIFY=true
\endverbatim

For a given repository, you may also execute:

\verbatim
    git config http.sslVerify false
\endverbatim

This command allows push and pull in a existing repository over https protocol. GIT will use the SSL
protocol for encrypted communication regardless the server certificate is trusted by "someone". Note
that "certification authorities" have the role of making sure that someone is really who he says. GCG
is not intended to get any user information except its username and password previously registered in
our server. Thus, this is a safe site.

  \section reference GCGlib References

- GCGlib is based on the following standard algorithms, publications, softwares and methods:

- OpenGL: GCGlib uses the cross-platform OpenGL graphics library for real time rendering tasks.

- Independent JPEG Group: this widely used free library is a Linux standard for JPEG image compression.

- Pthreads Win32: it is a Windows version of the POSIX standard for multithread applications.

- MinGW: forms an environment for developing and deploying native Microsoft Windows applications.

- Numerical Recipes: a few numerical functions of GCGlib are adaptations of some of the methods presented
in this complete and useful book family.

- M. Matsumoto & T. Nishimura, "Mersenne Twister: A 623-Dimensionally Equidistributed Uniform Pseudo-Random
Number Generator", ACM Transactions on Modeling and Computer Simulation, v.8, n.1, pp.3-30, 1998: we implemented
a sequential version of the Mersenne Twister random number generator.

- GIT: a distributed version control system that helps GCGlib to be constructed in a cooperation scheme.

- Doxygen: automatically generates GCGlib documentation from gcg.h header.

- Windows and Visual Studio are trademarks of Microsoft Corporation
*/


/** @file gcg.h
    @brief GCG - Group for Computer Graphics, Image and Vision library

Universidade Federal de Juiz de Fora\n
Instituto de Ciências Exatas\n
Departamento de Ciência da Computação\n
**/


#ifndef _GCG_H_

#ifdef __cplusplus
  extern "C++" {    // All names have C++ style
#else
  #error "GCC library must be compiled with C++ compilers"
#endif

#if !defined(_COUNTER_GCG_)
  #define _COUNTER_GCG_ 1
#endif

// Next definitions will be included once
#if _COUNTER_GCG_ == 1

#if defined(GCG_WINDOWS32) || defined(GCG_WINDOWS64)
  #ifndef VAPIWIN_API
    // GCGlib is deployed as a Dynamic Linked Library for Windows
    #define GCG_API_FUNCTION extern __declspec(dllexport)
    #define GCG_API_DATA     extern __declspec(dllexport)
    #define GCG_API_CLASS    __declspec(dllexport)
    #define GCG_API_TEMPLATE __declspec(dllexport)
  #else
    // VAPIWIN is a Dynamic Linked Library for use with non-Visual C++ compilers for video input
    #define GCG_API_FUNCTION
    #define GCG_API_DATA
    #define GCG_API_CLASS
    #define GCG_API_TEMPLATE
  #endif
#else
  // GCGlib names defined as C and C++ standards
  #define GCG_API_FUNCTION extern
  #define GCG_API_DATA     extern
  #define GCG_API_CLASS
  #define GCG_API_TEMPLATE
#endif

#include <stdio.h>
#include <math.h>
#include <new>

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////     GCGlib VERSION   ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// @defgroup version GCGlib version information
/// Static strings indicating current GCGlib version.
///@{

/// @brief Points to the full version string on the form: major.minor.build
/// @since 0.02.0
GCG_API_DATA    const char *GCGLIB_VERSION;
/// @brief Points to the build date string
/// @since 0.02.0
GCG_API_DATA    const char *GCGLIB_BUILD_DATE;
/// @brief Points to the integer major version value
/// @since 0.04.0
GCG_API_DATA    const int GCGLIB_VERSION_MAJOR;
/// @brief Points to the integer minor version value
/// @since 0.04.0
GCG_API_DATA    const int GCGLIB_VERSION_MINOR;
/// @brief Points to the integer build version value
/// @since 0.04.0
GCG_API_DATA    const int GCGLIB_VERSION_BUILD;


///@}


/*******************************************************************
  GENERAL MACROS AND INLINE FUNCTIONS
********************************************************************/

/// @defgroup generaldefs Macros, static names and inline functions
/// Users can use several predefined macros, static names and inline functions in GCGlib to make their job easier.
///@{
///@}

/// @defgroup macros General macros and inline functions
/// General GCGlib macros.
///@{
/// @ingroup generaldefs

#ifndef SQR
/// @brief Inline function for squaring integers.
/// @param[in] x int number to be squared
/// @return Squared number.
/// @since 0.01.0
static inline int SQR(int x) { return x * x; }

/// @brief Inline function for squaring shorts.
/// @param[in] x short number to be squared
/// @return Squared number.
/// @since 0.01.0
static inline short SQR(short x) { return x * x; }

/// @brief Inline function for squaring longs.
/// @param[in] x long number to be squared
/// @return Squared number.
/// @since 0.01.0
static inline long SQR(long x) { return x * x; }

/// @brief Inline function for squaring floats.
/// @param[in] x float number to be squared
/// @return Squared number.
/// @since 0.01.0
static inline float SQR(float x) { return x * x; }

/// @brief Inline function for squaring doubles.
/// @param[in] x double number to be squared
/// @return Squared number.
/// @since 0.01.0
static inline double SQR(double x) { return x * x; }
#endif

/// @def MIN(a,b)
/// @brief A macro that returns the minimum of \a a and \a b.
/// @since 0.01.0

#ifndef MIN
#define MIN(a, b) ((a > b) ? (b) : (a))
#endif

/// @def MAX(a,b)
/// @brief A macro that returns the maximum of \a a and \a b.
/// @since 0.01.0

#ifndef MAX
#define MAX(a, b) ((a < b) ? (b) : (a))
#endif

/// @def ABS(a)
/// @brief A macro that returns the absolute value of \a a.
/// @since 0.01.0

#ifndef ABS
#define ABS(a) (((a) < 0) ? -(a) : (a))
#endif


/// @def SWAP(a,b)
/// @brief A macro that swaps the values of \a a and \a b variables.
/// @since 0.01.0

#ifndef SWAP
#define SWAP(a, b) {(a) ^= (b); (b) ^= (a);  (a) ^= (b);}
#endif

/// @def DEG2RAD(a)
/// @brief A macro that converts \a a degrees in radians.
/// @since 0.01.0

#ifndef DEG2RAD
#define DEG2RAD(a)  (((a) * M_PI) / 180.0)
#endif

/// @def RAD2DEG(a)
/// @brief A macro that converts \a a radians in degrees.
/// @since 0.01.0

#ifndef RAD2DEG
#define RAD2DEG(a)  (((a) * 180) / M_PI)
#endif

/// @def TRUE
/// @brief Defines the boolean value for true.
/// @since 0.01.0

#ifndef TRUE
#define TRUE  1
#endif


/// @def FALSE
/// @brief Defines the boolean value for false.
/// @since 0.01.0

#ifndef FALSE
#define FALSE 0
#endif

/// @def EPSILON
/// @brief Defines the minimum accepted value for single precision real numbers.
/// @since 0.01.0

#ifndef EPSILON
#define EPSILON 0.0000077
#endif

/// @def INF
/// @brief Defines the biggest value for real numbers.
/// @since 0.01.0

#ifndef INF
#define INF 1.0e+16
#endif

/// @def FEQUAL
/// @brief A macro for real numbers equality comparisons.
/// @since 0.01.0

#ifndef FEQUAL
#define FEQUAL(a, b) (fabs((a)-(b)) < EPSILON)
#endif

/// @def M_PI
/// @brief A macro that defines the number PI with 20 decimals.
/// @since 0.01.0

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/// @def NULL
/// @brief Defines the null pointer.
/// @since 0.01.0

#ifndef NULL
#define NULL 0
#endif

/// @def ISPOWEROF2(n)
/// @brief A macro for checking if the integer number \a n is a power of 2.
/// @since 0.01.0

#ifndef ISPOWEROF2
#define ISPOWEROF2(n) (!(n & (n-1)))
#endif

/// @def INT_MAX
/// @brief Defines the maximum positive value accepted by an integer
/// @since 0.01.0

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

///@}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////     LOG, ERROR and WARNINGS functions and codes    ///////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/// @defgroup report Logs, error, warning and information report
/// GCGlib provides logging functions, used by the functions and methods to report errors,
/// warnings or events. They are also interesting for programmers to concentrate messages in a unique
/// place. gcgOutputLog() has the same form of the standard C function \a printf().
///
/// GCGlib has three types of messages: errors, warnings and information. When functions or methods
/// check status or fails executing, they report an error or warning depending on the problem severity.
/// Typically, errors prevent the function continue to run. In this case, the result might not be the
/// desired upon the call. In the other hand, warnings are lighter problems that can prevent a step to
/// be executed, but the overall task is performed totally or partially. When there is no error/warning
/// but the library needs to report something, the message type is called information.
///
/// All errors and warnings issued by GCGlib can be retrieved by calling gcgGetReport().
/// To avoid serialization, successful operations inside GCGlib are NEVER reported. The last error might
/// not have been issued by the last call. Check the report code ONLY when a method or function returns
/// a fail. If logging is enabled, a string is sent to the stream, except when the error/warning type is
/// GCG_SUCCESS.
///
/// Reports are formed by a TYPE, DOMAIN and MESSAGE codes. The TYPE indicates if the message is an error,
/// warning or information. The DOMAIN tells the main functionality the report is related to: network,
/// memory, video, etc.. The programmer can enable/disable the logging of a specific DOMAIN using
/// gcgEnableLog() or gcgDisableLog() respectively. This helps developers to get information only of the
/// interested functionalities. The MESSAGE code is more specific in relation to the event occured.
///
/// In addition to the error/warnings/information reports, functions and methods might send complementary
/// information to the log stream.
///@{

/// @brief Reports an error. To avoid serialization, it is NEVER called for successful
/// operations inside GCGlib. The last report might not have been issued by the last call.
/// Check the error/warning only when a method or function fails. It saves the error/warning
/// information and, if logging is enabled, send an error string to the stream. If the type is
/// GCG_SUCCESS, nothing is sent to the log. Codes of information type might be sent only to the log.
/// Ex. gcgReport(GCG_REPORT_CODE(GCG_ERROR, GCG_MEMORY, GCG_ALLOCATIONERROR)). To report a successful
/// operation, call gcgReport(GCG_SUCCESS).
/// @param[in] code code of the report. Use GCG_REPORT_CODE() to form the 32bits code.
/// @param[in] format pointer to an extra format string to be reported. Usually indicates extra information about the
/// event. It uses the standard C format string as documented for \a printf(). If NULL, the report text is generated
/// from the code indicated by \a code.
/// @return returns true if the event was reported by calling gcgOutputLog(). This is affected by gcgEnableReportLog().
/// @see gcgSetLogStream()
/// @see gcgGetReport()
/// @see GCG_REPORT_CODE()
/// @see gcgEnableReportLog()
/// @see gcgOutputLog()
/// @since 0.02.0
GCG_API_FUNCTION    bool gcgReport(int code, const char *format = NULL, ...);

/// @brief Returns the code of the last report. Use GCG_REPORT_TYPE(), GCG_REPORT_DOMAIN(),
/// and GCG_REPORT_MESSAGE() to extract the details of the error code.
/// @param[in] sizestring maximum number of chars that \a extrastring supports. Ignored if it is zero.
/// @param[out] extrastring pointer to a buffer that receives a copy of the last extra message. A NULL value is ignored.
/// @return Integer code of the last report. Use GCG_REPORT_TYPE(), GCG_REPORT_DOMAIN(), and GCG_REPORT_MESSAGE() to extract the
/// details of the error code.
/// @see gcgReport()
/// @see gcgGetReportString()
/// @see GCG_REPORT_TYPE()
/// @see GCG_REPORT_DOMAIN()
/// @see GCG_REPORT_MESSAGE()
/// @since 0.02.0
GCG_API_FUNCTION    int gcgGetReport(int sizestring = 0, char *extrastring = NULL);

/// @brief Gets the strings of the last report.
/// @param[out] typestr pointer to a string that should receive the string of last message's TYPE.
/// A NULL value is ignored.
/// @param[out] domainstr pointer to a string that should receive the string of last message's DOMAIN.
/// A NULL value is ignored.
/// @return the pointer of the char string representing the last message.
/// @see gcgReport()
/// @see gcgGetReport()
/// @since 0.02.0
GCG_API_FUNCTION    const char *gcgGetReportString(char **typestr = NULL, char **domainstr = NULL);

/// @brief Enables or disables the logging of messages of a specific type or domain. When a type or domain
/// is enabled, the gcgReport() function sends any message of that type or domain to gcgOutputLog(). To
/// enable all types and domains, call gcgEnableReportLog(GCG_REPORT_ALL, true). Likewise, to disable them all
/// call gcgEnableReportLog(GCG_REPORT_ALL, false). To enable all messages of a specific type, INFORMATION for
/// example, call gcgEnableReportLog(GCG_INFORMATION, true). All information messages will be logged. In the
/// other hand, to disable all INFORMATION messages, call gcgEnableReportLog(GCG_INFORMATION, false). To enable
/// all messages of a specific domain, GRAPHICS for example, call gcgEnableReportLog(GCG_DOMAIN_GRAPHICS, true).
/// All messages related to graphics functions will be logged for all types. By default, only the type
/// GCG_ERROR is enabled and reported.
/// @param[in] code code of the report type or domain that must be sent to the log.
/// @param[in] enable if true, indicates the type or domain has to be enabled, i.e., generates a message. If false,
/// the type or domain messages are not reported.
/// @return true if the type or domain is successfully enabled or disabled.
/// @see gcgReport()
/// @since 0.03.14
GCG_API_FUNCTION    bool gcgEnableReportLog(int code, bool enable);

///@}


/// @defgroup log Log functions
/// All report functions of GCGlib use the same log functionality. By default, the log messages are sent
/// to \a stderr. Using the gcgSetLogStream(), the user can redirect messages to another \a FILE object.
/// Passing a NULL pointer disables logging. This affect all messages reported by GCGlib.
///
///@{
/// @ingroup report

/// @brief Returns the current log stream. The default log stream is \a stderr.
/// @return pointer to the current log stream. If no log stream is registered, returns NULL.
/// @see gcgSetLogStream()
/// @see gcgOutputLog()
/// @since 0.02.0
GCG_API_FUNCTION    FILE *gcgGetLogStream();

/// @brief Sets a new stream for logging. The default log stream is \a stderr. Returns the previous log stream.
/// @param[in] logstream pointer to the new stream that will receive log messages. If it is NULL,
/// logging is disabled and future messages are discarded.
/// @return pointer to the previous log stream. If no log stream was registered, returns NULL.
/// @see gcgGetLogStream()
/// @see gcgOutputLog()
/// @since 0.02.0
GCG_API_FUNCTION    FILE *gcgSetLogStream(FILE *logstream);

/// @brief Reports a new message to the log stream.
/// @param[in] format pointer to the format string to be reported. Uses the standard C format string, as
/// documented for \a printf(). A NULL value is ignored.
/// @see gcgSetLogStream()
/// @see gcgGetLogStream()
/// @since 0.02.0
GCG_API_FUNCTION    void gcgOutputLog(const char *format, ...);
///@}




/// @defgroup codeformation Macros for composing and decomposing report codes from/into its components: type, domain, message.
///  GCGlib has macros for report codes composition and decomposition from/into its components: type, domain, message.
/// @since 0.02.0
///@{
/// @ingroup report

/// @brief Composes an error/warning/information given a triple (TYPE, DOMAIN, MESSAGE) with 3, 8 and 10 bits respectively.
/// @since 0.02.0
#define GCG_REPORT_CODE(t, d, m) (((((int) d) & (int) 0xff) << 3) | ((((int) m) & (int) 0x3ff) << 11) | ((((int) t) & (int) 0x07) << 0))

/// @brief Extracts the TYPE from a report code. Uses 3 bits.
/// @since 0.02.0
#define GCG_REPORT_TYPE(c) ((((int) c) >> 0) & (int) 0x07)      // 3 bits

/// @brief Extracts the DOMAIN from a report code. Uses 7 bits
/// @since 0.02.0
#define GCG_REPORT_DOMAIN(c) ((((int) c) >> 3) & (int) 0xff)    // 8 bits

/// @brief Extracts the MESSAGE from a report code. Uses 10 bits
/// @since 0.02.0
#define GCG_REPORT_MESSAGE(c) ((((int) c) >> 11) & (int) 0x3ff)  // 10 bits

///@}


/// @defgroup types Report types
/// Report types identify if the report is an error, warning or information. The user can enable or
/// disable logging for any type separately by using gcgEnableReportLog(). By default, only the type
/// GCG_ERROR is enabled and reported. In development time, it is also interesting to enable information
/// messages (GCG_INFORMATION) and, most importantly, warnings (GCG_WARNING).
/// @since 0.02.0
///@{
/// @ingroup report

/// @brief Successful operation. To report a successful operation, call gcgReport(GCG_SUCCESS).
/// GCGlib NEVER reports successful operations for performance purposes.
/// @since 0.02.0
#define GCG_SUCCESS                 0 // Must be zero
/// @brief Indicate an error code
#define GCG_ERROR                   1
/// @brief Indicate a warning code
#define GCG_WARNING                 2
/// @brief Indicate an information code
#define GCG_INFORMATION             3 // Must be the greatest code
///@}

/// @defgroup domains Report domains
/// Domains used by GCGlib for reporting errors, warnings or information. Reports issued by
/// GCGlib are showed using gcgOutputLog(). The user can enable or disable logging for any domain
/// separately using gcgEnableReportLog(). This helps programmers to receive textual
/// messages only for the desired functionalities. By default, only the type GCG_ERROR is enabled to
/// be logged. To enable warnings and information, call gcgEnableReportLog(GCG_WARNING, true) and
/// gcgEnableReportLog(GCG_INFORMATION, true). This is highly recommend during development to find
/// possible errors by inspecting GCGlib returned messages.
///@{
/// @ingroup report

/// @brief Memory management reports
#define GCG_DOMAIN_MEMORY             8 // Must be the smallest code
/// @brief Network management reports
#define GCG_DOMAIN_NETWORK            9
/// @brief File management reports
#define GCG_DOMAIN_FILE               10
/// @brief Image management reports
#define GCG_DOMAIN_IMAGE              11
/// @brief Camera management reports
#define GCG_DOMAIN_CAMERA             12
/// @brief Video management reports
#define GCG_DOMAIN_VIDEO              13
/// @brief Thread management reports
#define GCG_DOMAIN_THREAD             14
/// @brief Graphics reports
#define GCG_DOMAIN_GRAPHICS           15
/// @brief Geometry reports
#define GCG_DOMAIN_GEOMETRY           16
/// @brief Algebra reports
#define GCG_DOMAIN_ALGEBRA            17
/// @brief Configuration reports
#define GCG_DOMAIN_CONFIG             18
/// @brief Data structure reports
#define GCG_DOMAIN_DATASTRUCTURE      19
/// @brief Signal management reports
#define GCG_DOMAIN_SIGNAL             20

/// @brief User defined reports
#define GCG_DOMAIN_USER               21   // Must be the greatest code

/// @brief Indicates all types and domains. It is an exclusive macro for gcgEnableReportLog(). Any
/// negative values used with these functions indicate all types and domains. By default, only
/// errors are enabled to be logged. To enable warnings and information, call
/// gcgEnableReportLog(GCG_WARNING, true) and gcgEnableReportLog(GCG_INFORMATION, true).
#define GCG_REPORT_ALL                -1

///@}


/// @defgroup messages Report messages
///@{
/// @ingroup report

/// @brief Successful operation
#define GCG_NONE                    0     // Must be the smallest code
/// @brief Allocation error
#define GCG_ALLOCATIONERROR         1
/// @brief Attempt to use an invalid object
#define GCG_INVALIDOBJECT           2
/// @brief Bad parameters
#define GCG_BADPARAMETERS           3
/// @brief Initialization problem
#define GCG_INITERROR               4
/// @brief General internal problem
#define GCG_INTERNALERROR           5
/// @brief Timeout
#define GCG_TIMEOUT                 6
/// @brief Input/output problem
#define GCG_IOERROR                 7
/// @brief Format mismatch
#define GCG_FORMATMISMATCH          8
/// @brief Unrecognized format
#define GCG_UNRECOGNIZEDFORMAT      9
/// @brief Unsupported format
#define GCG_UNSUPPORTEDFORMAT       10
/// @brief Unsupported operation
#define GCG_UNSUPPORTEDOPERATION    11
/// @brief Information retrieval problem
#define GCG_INFORMATIONPROBLEM      12
/// @brief General error reading or receiving
#define GCG_READERROR               13
/// @brief General error writing or sending
#define GCG_WRITEERROR              14
/// @brief Current object is not connected
#define GCG_NOTCONNECTED            15
/// @brief General socket problem
#define GCG_SOCKETERROR             16
/// @brief An error occurred in select()
#define GCG_SELECTERROR             17
/// @brief Connection closed by remote peer
#define GCG_CONNECTIONCLOSED        18
/// @brief Host not found
#define GCG_HOSTNOTFOUND            19
/// @brief General connection problem
#define GCG_CONNECTERROR            20
/// @brief An error occurred in setsocketopt()
#define GCG_SETSOCKETOPTERROR       21
/// @brief An error occurred in bind()
#define GCG_BINDERROR               22
/// @brief An error occurred in listen()
#define GCG_LISTENERROR             23
/// @brief An error occurred in accept()
#define GCG_ACCEPTERROR             24
/// @brief An exception was caught
#define GCG_EXCEPTION               25
/// @brief Accepting with a bad pointer address or too small buffer
#define GCG_ACCEPTBADADDRESS        26
/// @brief Connection refused by host
#define GCG_CONNECTIONREFUSED       27
/// @brief Connection aborted: data transmission time-out or protocol problem
#define GCG_CONNECTIONABORTED       28
/// @brief Sending with a bad pointer address or too small buffer
#define GCG_WRITEBADADDRESS         29
/// @brief Receiving with a bad pointer address or too small buffer
#define GCG_READBADADDRESS          30
/// @brief Cannot send messages after shutdown
#define GCG_SENDSHUTDOWN            31
/// @brief Cannot receive messages after shutdown
#define GCG_RECEIVESHUTDOWN         32
/// @brief Invalid socket
#define GCG_INVALIDSOCKET           33
/// @brief Stream control error
#define GCG_STREAMCONTROLERROR      34
/// @brief Already running
#define GCG_ALREADYRUNNING          35
/// @brief Creation failure
#define GCG_CREATIONFAILED          36
/// @brief Mutex failure
#define GCG_MUTEXFAILURE            37
/// @brief Semaphore failure
#define GCG_SEMAPHOREFAILURE        38
/// @brief No buffer space available or queue full
#define GCG_NOBUFFER                39
/// @brief Job not executed
#define GCG_JOBNOTEXECUTED          40
/// @brief Interrupted by extern signal
#define GCG_INTERRUPTED             41
/// @brief This object was active and is now disconnected
#define GCG_DISCONNECTED            42
/// @brief Process, thread or job could not be stoped
#define GCG_STOPERROR               43
/// @brief Process, thread or job is not running
#define GCG_NOTRUNNING              44
/// @brief Object did not exit properly
#define GCG_EXITFAILURE             45
/// @brief Resource release error
#define GCG_RELEASEERROR            46
/// @brief Lock was not acquired
#define GCG_LOCKERROR               47
/// @brief Object is not owned by the caller
#define GCG_OWNERSHIPERROR          48
/// @brief Removal error
#define GCG_REMOVALERROR            49
/// @brief Data was not stored
#define GCG_STOREFAILURE            50
/// @brief Open error
#define GCG_OPENERROR               51
/// @brief Decode error
#define GCG_DECODEERROR             52
/// @brief Function call failed
#define GCG_FUNCTIONCALLFAILED      53
/// @brief Graphics system error
#define GCG_GRAPHICSERROR           54
/// @brief Incompatibility error
#define GCG_INCOMPATIBILITYERROR    55
/// @brief Error configuring request
#define GCG_CONFIGERROR             56
/// @brief Unavailable resource
#define GCG_UNAVAILABLERESOURCE     57
/// @brief Start error
#define GCG_STARTERROR              58
/// @brief Out of bounds
#define GCG_OUTOFBOUNDS             59
/// @brief End of stream
#define GCG_ENDOFSTREAM             60
/// @brief Operation failed
#define GCG_OPERATIONFAILED         61
/// @brief Memory leak detected
#define GCG_MEMORYLEAK              62
/// @brief Insertion failed
#define GCG_INSERTIONFAILED         63
/// @brief Adapting to new conditions
#define GCG_ADAPTING                64

/// @brief Undefined error
#define GCG_UNDEFINED               65 // Must be the greatest code
///@}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////     SYSTEM classes and functions ////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @brief Base class for all GCGlib classes. It is used for better control
/// of object instantiation, memory allocation, and object reuse. Some
/// systems (like DLL versions in Windows) might demand special tasks in order
/// to be stable. All GCGlib classes must be inherited from gcgCLASS.
///
/// @since 0.02.105
//////////////////////////////////////////////////////////////////////////////

class    GCG_API_CLASS    gcgCLASS {
  public:
    /// @brief Defines a \a new operator to be used by instatiations of
    /// GCGlib classes instead the global one.
    /// @param[in] size The size in bytes of the object to be allocated.
    /// @return the pointer to a new memory block having \a size bytes. If allocation
    /// fails, it throws std::bad_alloc expection to be compliant with ANSI/ISO standards.
    /// @see delete
    /// @since 0.02.105
    void *operator new(size_t size);

    /// @brief Defines a \a new operator  to be used by instatiations of GCGlib classes instead
    /// the global one. Returns a NULL pointer instead of throwing an exception if an error occurs.
    /// @param[in] size The size in bytes of the object to be allocated.
    /// @return the pointer to a new memory block having \a size bytes. If allocation
    /// fails, it returns NULL.
    /// @see delete
    /// @since 0.02.113
    void *operator new(size_t size, const std::nothrow_t&) throw();

    /// @brief Defines a \a new operator to be used by GCGlib array allocations instead the global one.
    /// @param[in] size The size in bytes of the array to be allocated.
    /// @return the pointer to a new memory block having \a size bytes. If allocation
    /// fails, it throws std::bad_alloc expection to be compliant with ANSI/ISO standards.
    /// @see delete[]
    /// @since 0.02.113
    void *operator new[](size_t size);

    /// @brief Defines a \a new operator to be used by vector allocations instead the global one.
    /// @param[in] size The size in bytes of the array to be allocated.Returns a NULL pointer instead
    /// of throwing an exception if an error occurs.
    /// @return the pointer to a new memory block having \a size bytes. If allocation
    /// fails, it returns NULL.
    /// @see delete[]
    /// @since 0.02.113
    void *operator new[](size_t size, const std::nothrow_t&) throw();

    /// @brief Defines a \a delete operator to free instances of
    /// GCGlib classes instead the global one. It is designed to match the \a new operator.
    /// @param[in] p The pointer of the memory block to be released.
    /// @see new
    /// @since 0.02.105
    void operator delete(void *p);

    /// @brief Defines a \a delete operator to free instances of
    /// GCGlib classes instead the global one. It is designed to match the \a new operator.
    /// @param[in] p The pointer of the memory block to be released.
    /// @see new
    /// @since 0.02.113
    void operator delete(void *p, const std::nothrow_t&) throw();

    /// @brief Defines a \a delete operator to free instances of arrays for
    /// GCGlib classes instead the global one. It is designed to match the \a new[] operator.
    /// @param[in] p The pointer of the memory block to be released.
    /// @see new[]
    /// @since 0.02.113
    void operator delete[](void *p);

    /// @brief Defines a \a delete operator to free instances of arrays for
    /// GCGlib classes instead the global one. It is designed to match the \a new[] operator.
    /// @param[in] p The pointer of the memory block to be released.
    /// @see new[]
    /// @since 0.02.113
    void operator delete[](void *p, const std::nothrow_t&) throw();
};



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////     ALGEBRA macros and functions ////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// GCG primitive types.
////////////////////////////////////////////////////////////////////////////////////

typedef float VECTOR2[2];
typedef float VECTOR3[3];
typedef float VECTOR4[4];

typedef float MATRIX2[4];
typedef float MATRIX3[9];
typedef float MATRIX34[12];
typedef float MATRIX4[16];

typedef double VECTOR2d[2];
typedef double VECTOR3d[3];
typedef double VECTOR4d[4];

typedef double MATRIX2d[4];
typedef double MATRIX3d[9];
typedef double MATRIX34d[12];
typedef double MATRIX4d[16];


////////////////////////////////////////////////////////////////////////////////////
// GCG algebra macros. More efficient than functions. But implies in a larger code.
////////////////////////////////////////////////////////////////////////////////////

// Expressions ///////////////////////////////////////////////
#define gcgDOTVECTOR2(v1, v2) ((v1)[0] * (v2)[0] + (v1)[1] * (v2)[1])
#define gcgDOTIMEDVECTOR2(u, a, b) ((u)[0] * (a) + (u)[1] * (b)}
#define gcgLENGTHVECTOR2(v) (sqrt(gcgDOTVECTOR2((v),(v))))

#define gcgDOTVECTOR3(v1, v2) ((v1)[0] * (v2)[0] + (v1)[1] * (v2)[1] + (v1)[2] * (v2)[2])
#define gcgDOTIMEDVECTOR3(u, a, b, c) ((u)[0] * (a) + (u)[1] * (b) + (u)[2] * (c))
#define gcgLENGTHVECTOR3(v) (sqrt(gcgDOTVECTOR3((v),(v))))

#define gcgDOTVECTOR4(v1, v2) ((v1)[0] * (v2)[0] + (v1)[1] * (v2)[1] + (v1)[2] * (v2)[2] + (v1)[3] * (v2)[3])
#define gcgDOTIMEDVECTOR4(u, a, b, c, d) ((u)[0] * (a) + (u)[1] * (b) + (u)[2] * (c) + (u)[3] * (d))
#define gcgLENGTHVECTOR4(v) (sqrt(gcgDOTVECTOR4((v),(v))))

#define gcgISEQUALVECTOR2(v1, v2) (fabs(v1[0] - v2[0]) > EPSILON && fabs((v1)[1] - (v2)[1]) > EPSILON)
#define gcgISEQUALVECTOR3(v1, v2) (fabs(v1[0] - v2[0]) > EPSILON && fabs((v1)[1] - (v2)[1]) > EPSILON && fabs((v1)[2] - (v2)[2]) > EPSILON)
#define gcgISEQUALVECTOR4(v1, v2) (fabs(v1[0] - v2[0]) > EPSILON && fabs((v1)[1] - (v2)[1]) > EPSILON && fabs((v1)[2] - (v2)[2]) > EPSILON && fabs((v1)[3] - (v2)[3]) > EPSILON)

// Computes the determinant of matrices
#define gcgDETERMINANT3x3_(m0, m1, m2, m3, m4, m5, m6, m7, m8)  ((m0)*((m8)*(m4)-(m7)*(m5)) - (m3)*((m8)*(m1)-(m7)*(m2)) + (m6)*((m5)*(m1)-(m4)*(m2)))
#define gcgDETERMINANT4x4_(m, det0, det4, det8, det12) \
( (m)[0]  * (det0 = gcgDETERMINANT3x3_((m)[5], (m)[6], (m)[7], (m)[9], (m)[10], (m)[11], (m)[13], (m)[14], (m)[15])) \
 -(m)[4]  * (det4 = gcgDETERMINANT3x3_((m)[1], (m)[2], (m)[3], (m)[9], (m)[10], (m)[11], (m)[13], (m)[14], (m)[15])) \
 +(m)[8]  * (det8 = gcgDETERMINANT3x3_((m)[1], (m)[2], (m)[3], (m)[5], (m)[6],  (m)[7],  (m)[13], (m)[14], (m)[15])) \
 -(m)[12] * (det12= gcgDETERMINANT3x3_((m)[1], (m)[2], (m)[3], (m)[5], (m)[6],  (m)[7],  (m)[9],  (m)[10], (m)[11])) )

#define gcgDETERMINANTMATRIX3(m) (gcgDETERMINANT3x3_((m)[0], (m)[1], (m)[2], (m)[3], (m)[4], (m)[5], (m)[6], (m)[7], (m)[8]))
#define gcgDETERMINANTMATRIX4(m) \
( (m)[0]  * gcgDETERMINANT3x3_((m)[5], (m)[6], (m)[7], (m)[9], (m)[10], (m)[11], (m)[13], (m)[14], (m)[15]) \
 -(m)[4]  * gcgDETERMINANT3x3_((m)[1], (m)[2], (m)[3], (m)[9], (m)[10], (m)[11], (m)[13], (m)[14], (m)[15]) \
 +(m)[8]  * gcgDETERMINANT3x3_((m)[1], (m)[2], (m)[3], (m)[5], (m)[6],  (m)[7],  (m)[13], (m)[14], (m)[15]) \
 -(m)[12] * gcgDETERMINANT3x3_((m)[1], (m)[2], (m)[3], (m)[5], (m)[6],  (m)[7],  (m)[9],  (m)[10], (m)[11]) )


// Commands ///////////////////////////////////////////////
#define gcgZEROVECTOR2(v) { (v)[0] = (v)[1] = 0.0; }
#define gcgZEROVECTOR3(v) { (v)[0] = (v)[1] = (v)[2] = 0.0; }
#define gcgZEROVECTOR4(v) { (v)[0] = (v)[1] = (v)[2] = (v)[3] = 0.0; }

#define gcgSETVECTOR2(dest, a, b) {(dest)[0] = a; (dest)[1] = b; }
#define gcgSETVECTOR3(dest, a, b, c) {(dest)[0] = a; (dest)[1] = b; (dest)[2] = c; }
#define gcgSETVECTOR4(dest, a, b, c, d) {(dest)[0] = a; (dest)[1] = b; (dest)[2] = c; (dest)[3]=d; }

static inline void gcgCOPYVECTOR2(VECTOR2 dest, VECTOR2 src) {dest[0] = src[0]; dest[1] = src[1]; }
static inline void gcgCOPYVECTOR2(VECTOR2d dest, VECTOR2d src) {dest[0] = src[0]; dest[1] = src[1]; }
static inline void gcgCOPYVECTOR2(VECTOR2 dest, VECTOR2d src) {dest[0] = (float) src[0]; dest[1] = (float) src[1]; }
static inline void gcgCOPYVECTOR2(VECTOR2d dest, VECTOR2 src) {dest[0] = src[0]; dest[1] = src[1]; }
static inline void gcgCOPYVECTOR3(VECTOR3 dest, VECTOR3 src) { dest[0] = src[0]; dest[1] = src[1]; dest[2] = src[2]; }
static inline void gcgCOPYVECTOR3(VECTOR3 dest, VECTOR3d src) { dest[0] = (float) src[0]; dest[1] = (float) src[1]; dest[2] = (float) src[2]; }
static inline void gcgCOPYVECTOR3(VECTOR3d dest, VECTOR3 src) { dest[0] = src[0]; dest[1] = src[1]; dest[2] = src[2]; }
static inline void gcgCOPYVECTOR3(VECTOR3d dest, VECTOR3d src) { dest[0] = src[0]; dest[1] = src[1]; dest[2] = src[2]; }
static inline void gcgCOPYVECTOR4(VECTOR4 dest, VECTOR4 src) { dest[0] = src[0]; dest[1] = src[1]; dest[2] = src[2]; dest[3] = src[3];}
static inline void gcgCOPYVECTOR4(VECTOR4 dest, VECTOR4d src) { dest[0] = (float) src[0]; dest[1] = (float) src[1]; dest[2] = (float) src[2]; dest[3] = (float) src[3];}
static inline void gcgCOPYVECTOR4(VECTOR4d dest, VECTOR4 src) { dest[0] = src[0]; dest[1] = src[1]; dest[2] = src[2]; dest[3] = src[3];}
static inline void gcgCOPYVECTOR4(VECTOR4d dest, VECTOR4d src) { dest[0] = src[0]; dest[1] = src[1]; dest[2] = src[2]; dest[3] = src[3];}

static inline void gcgSCALEVECTOR2(VECTOR2 dest, VECTOR2 v, float factor) { dest[0]=factor*v[0]; (dest)[1]=factor*v[1]; }
static inline void gcgSCALEVECTOR2(VECTOR2d dest, VECTOR2d v, double factor) { dest[0]=factor*v[0]; (dest)[1]=factor*v[1]; }
static inline void gcgSCALEVECTOR3(VECTOR3 dest, VECTOR3 v, float factor) {dest[0]=factor*v[0]; dest[1]=factor*v[1]; dest[2]=factor*v[2];}
static inline void gcgSCALEVECTOR3(VECTOR3d dest, VECTOR3d v, double factor) {dest[0]=factor*v[0]; dest[1]=factor*v[1]; dest[2]=factor*v[2];}
static inline void gcgSCALEVECTOR4(VECTOR4 dest, VECTOR4 v, float factor) {dest[0]=factor*v[0]; dest[1]=factor*v[1]; dest[2]=factor*v[2]; dest[3]=factor*v[3];}
static inline void gcgSCALEVECTOR4(VECTOR4d dest, VECTOR4d v, double factor) {dest[0]=factor*v[0]; dest[1]=factor*v[1]; dest[2]=factor*v[2]; dest[3]=factor*v[3];}

#define gcgADDVECTOR2(dest,v1,v2) {(dest)[0]=(v1)[0]+(v2)[0]; (dest)[1]=(v1)[1]+(v2)[1]; }
#define gcgADDVECTOR3(dest,v1,v2) {(dest)[0]=(v1)[0]+(v2)[0]; (dest)[1]=(v1)[1]+(v2)[1]; (dest)[2]=(v1)[2]+(v2)[2];}
#define gcgADDVECTOR4(dest,v1,v2) {(dest)[0]=(v1)[0]+(v2)[0]; (dest)[1]=(v1)[1]+(v2)[1]; (dest)[2]=(v1)[2]+(v2)[2]; (dest)[3]=(v1)[3]+(v2)[3];}

#define gcgSUBVECTOR2(dest, v1, v2) {(dest)[0]=(v1)[0]-(v2)[0]; (dest)[1]=(v1)[1]-(v2)[1]; }
#define gcgSUBVECTOR3(dest, v1, v2) {(dest)[0]=(v1)[0]-(v2)[0]; (dest)[1]=(v1)[1]-(v2)[1]; (dest)[2]=(v1)[2]-(v2)[2];}
#define gcgSUBVECTOR4(dest, v1, v2) {(dest)[0]=(v1)[0]-(v2)[0]; (dest)[1]=(v1)[1]-(v2)[1]; (dest)[2]=(v1)[2]-(v2)[2]; (dest)[3]=(v1)[3]-(v2)[3];}

// Normalize VECTOR2
static inline void gcgNORMALIZEVECTOR2(VECTOR2 dest, VECTOR2 v) {
  register float factor = (float) (1.0 / gcgLENGTHVECTOR2((v)));
  gcgSCALEVECTOR2((dest), (v), factor);
}

static inline void gcgNORMALIZEVECTOR2(VECTOR2d dest, VECTOR2d v) {
  register double factor = 1.0 / gcgLENGTHVECTOR2((v));
  gcgSCALEVECTOR2((dest), (v), factor);
}

// Normalize VECTOR3
static inline void gcgNORMALIZEVECTOR3(VECTOR3 dest, VECTOR3 v) {
  register float factor = (float) (1.0 / gcgLENGTHVECTOR3((v)));
  gcgSCALEVECTOR3((dest), (v), factor);
}

static inline void gcgNORMALIZEVECTOR3(VECTOR3d dest, VECTOR3d v) {
  register double factor = 1.0 / gcgLENGTHVECTOR3((v));
  gcgSCALEVECTOR3((dest), (v), factor);
}

// Normalize VECTOR4
static inline void gcgNORMALIZEVECTOR4(VECTOR4 dest, VECTOR4 v) {
  register float factor = (float) (1.0 / gcgLENGTHVECTOR4((v)));
  gcgSCALEVECTOR4((dest), (v), factor);
}

static inline void gcgNORMALIZEVECTOR4(VECTOR4d dest, VECTOR4d v) {
  register double factor = 1.0 / gcgLENGTHVECTOR4((v));
  gcgSCALEVECTOR4((dest), (v), factor);
}


#define gcgCROSSVECTOR3(dest, v1, v2) {                          \
              (dest)[0] = (v1)[1] * (v2)[2] - (v1)[2] * (v2)[1]; \
              (dest)[1] = (v1)[2] * (v2)[0] - (v1)[0] * (v2)[2]; \
              (dest)[2] = (v1)[0] * (v2)[1] - (v1)[1] * (v2)[0];}

// Creates a tensor from two vectors: T = v1 * transpose(v2)
#define gcgVECTOR3TOTENSOR(t, v1, v2) { \
  (t)[0] = (v1)[0]*(v2)[0]; (t)[1] = (v1)[0]*(v2)[1]; (t)[2] = (v1)[0]*(v2)[2]; \
  (t)[3] = (v1)[1]*(v2)[0]; (t)[4] = (v1)[1]*(v2)[1]; (t)[5] = (v1)[1]*(v2)[2]; \
  (t)[6] = (v1)[2]*(v2)[0]; (t)[7] = (v1)[2]*(v2)[1]; (t)[8] = (v1)[2]*(v2)[2]; }


///////////////////////////////////////////////
// MATRIX COMMANDS MACROS

#define gcgSETMATRIX2(dest, a, b, c, d) {   \
  (dest)[ 0] = a; (dest)[ 1] = b; (dest)[ 2] = c; (dest)[ 3] = d; }

#define gcgSETMATRIX3(dest, a, b, c, d, e, f, g, h, i) {   \
  (dest)[ 0] = a; (dest)[ 1] = b; (dest)[ 2] = c; \
  (dest)[ 3] = d; (dest)[ 4] = e; (dest)[ 5] = f; \
  (dest)[ 6] = g; (dest)[ 7] = h; (dest)[ 8] = i; }

#define gcgSETMATRIX4(dest, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) {   \
  (dest)[ 0] = a; (dest)[ 1] = b; (dest)[ 2] = c; (dest)[ 3] = d; \
  (dest)[ 4] = e; (dest)[ 5] = f; (dest)[ 6] = g; (dest)[ 7] = h; \
  (dest)[ 8] = i; (dest)[ 9] = j; (dest)[10] = k; (dest)[11] = l; \
  (dest)[12] = m; (dest)[13] = n; (dest)[14] = o; (dest)[15] = p; }

static inline void gcgCOPYMATRIX2(MATRIX2 dest, MATRIX2 m) {
  dest[ 0] = m[ 0]; dest[ 1] = m[ 1]; dest[ 2] = m[ 2]; dest[ 3] = m[ 3];
}

static inline void gcgCOPYMATRIX2(MATRIX2d dest, MATRIX2d m) {
  dest[ 0] = m[ 0]; dest[ 1] = m[ 1]; dest[ 2] = m[ 2]; dest[ 3] = m[ 3];
}

static inline void gcgCOPYMATRIX2(MATRIX2d dest, MATRIX2 m) {
  dest[ 0] = m[ 0]; dest[ 1] = m[ 1]; dest[ 2] = m[ 2]; dest[ 3] = m[ 3];
}

static inline void gcgCOPYMATRIX2(MATRIX2 dest, MATRIX2d m) {
  dest[ 0] = (float) m[ 0]; dest[ 1] = (float) m[ 1]; dest[ 2] = (float) m[ 2]; dest[ 3] = (float) m[ 3];
}

static inline void gcgCOPYMATRIX3(MATRIX3 dest, MATRIX3 m) {
  dest[ 0] = m[ 0]; dest[ 1] = m[ 1]; dest[ 2] = m[ 2];
  dest[ 3] = m[ 3]; dest[ 4] = m[ 4]; dest[ 5] = m[ 5];
  dest[ 6] = m[ 6]; dest[ 7] = m[ 7]; dest[ 8] = m[ 8];
}

static inline void gcgCOPYMATRIX3(MATRIX3d dest, MATRIX3d m) {
  dest[ 0] = m[ 0]; dest[ 1] = m[ 1]; dest[ 2] = m[ 2];
  dest[ 3] = m[ 3]; dest[ 4] = m[ 4]; dest[ 5] = m[ 5];
  dest[ 6] = m[ 6]; dest[ 7] = m[ 7]; dest[ 8] = m[ 8];
}

static inline void gcgCOPYMATRIX3(MATRIX3d dest, MATRIX3 m) {
  dest[ 0] = m[ 0]; dest[ 1] = m[ 1]; dest[ 2] = m[ 2];
  dest[ 3] = m[ 3]; dest[ 4] = m[ 4]; dest[ 5] = m[ 5];
  dest[ 6] = m[ 6]; dest[ 7] = m[ 7]; dest[ 8] = m[ 8];
}

static inline void gcgCOPYMATRIX3(MATRIX3 dest, MATRIX3d m) {
  dest[ 0] = (float) m[ 0]; dest[ 1] = (float) m[ 1]; dest[ 2] = (float) m[ 2];
  dest[ 3] = (float) m[ 3]; dest[ 4] = (float) m[ 4]; dest[ 5] = (float) m[ 5];
  dest[ 6] = (float) m[ 6]; dest[ 7] = (float) m[ 7]; dest[ 8] = (float) m[ 8];
}


static inline void gcgCOPYMATRIX4(MATRIX4 dest, MATRIX4 m) {
  dest[ 0] = m[ 0]; dest[ 1] = m[ 1]; dest[ 2] = m[ 2]; dest[ 3] = m[ 3];
  dest[ 4] = m[ 4]; dest[ 5] = m[ 5]; dest[ 6] = m[ 6]; dest[ 7] = m[ 7];
  dest[ 8] = m[ 8]; dest[ 9] = m[ 9]; dest[10] = m[10]; dest[11] = m[11];
  dest[12] = m[12]; dest[13] = m[13]; dest[14] = m[14]; dest[15] = m[15];
}

static inline void gcgCOPYMATRIX4(MATRIX4d dest, MATRIX4 m) {
  dest[ 0] = m[ 0]; dest[ 1] = m[ 1]; dest[ 2] = m[ 2]; dest[ 3] = m[ 3];
  dest[ 4] = m[ 4]; dest[ 5] = m[ 5]; dest[ 6] = m[ 6]; dest[ 7] = m[ 7];
  dest[ 8] = m[ 8]; dest[ 9] = m[ 9]; dest[10] = m[10]; dest[11] = m[11];
  dest[12] = m[12]; dest[13] = m[13]; dest[14] = m[14]; dest[15] = m[15];
}

static inline void gcgCOPYMATRIX4(MATRIX4d dest, MATRIX4d m) {
  dest[ 0] = m[ 0]; dest[ 1] = m[ 1]; dest[ 2] = m[ 2]; dest[ 3] = m[ 3];
  dest[ 4] = m[ 4]; dest[ 5] = m[ 5]; dest[ 6] = m[ 6]; dest[ 7] = m[ 7];
  dest[ 8] = m[ 8]; dest[ 9] = m[ 9]; dest[10] = m[10]; dest[11] = m[11];
  dest[12] = m[12]; dest[13] = m[13]; dest[14] = m[14]; dest[15] = m[15];
}

static inline void gcgCOPYMATRIX4(MATRIX4 dest, MATRIX4d m) {
  dest[ 0] = (float) m[ 0]; dest[ 1] = (float) m[ 1]; dest[ 2] = (float) m[ 2]; dest[ 3] = (float) m[ 3];
  dest[ 4] = (float) m[ 4]; dest[ 5] = (float) m[ 5]; dest[ 6] = (float) m[ 6]; dest[ 7] = (float) m[ 7];
  dest[ 8] = (float) m[ 8]; dest[ 9] = (float) m[ 9]; dest[10] = (float) m[10]; dest[11] = (float) m[11];
  dest[12] = (float) m[12]; dest[13] = (float) m[13]; dest[14] = (float) m[14]; dest[15] = (float) m[15];
}

#define gcgIDENTITYMATRIX2(matriz) {  \
	(matriz)[0]  = (matriz)[3] = 1.f; \
	(matriz)[1]  = (matriz)[2] = 0.0f; }

#define gcgIDENTITYMATRIX3(matriz) {  \
	(matriz)[0]  = (matriz)[4]  = (matriz)[8]  = 1.f; \
	(matriz)[1]  = (matriz)[2]  = (matriz)[3]  = (matriz)[5]  = (matriz)[6]  = (matriz)[7]  = 0.0f; }

#define gcgIDENTITYMATRIX4(matriz) {  \
	(matriz)[0]  = (matriz)[5]  = (matriz)[10] = (matriz)[15] = 1.f; \
	(matriz)[1]  = (matriz)[2]  = (matriz)[3]  = (matriz)[4]  = (matriz)[6]  = (matriz)[7]  = \
	(matriz)[8]  = (matriz)[9]  = (matriz)[11] = (matriz)[12] = (matriz)[13] = (matriz)[14] = 0.f; }

//Transpose matrix 3x3
#define gcgTRANSPOSEMATRIX3(tm, m) {   \
  (tm)[ 0] = (m)[0];   (tm)[1] = (m)[3];   (tm)[2] = (m)[6]; \
  (tm)[ 3] = (m)[1];   (tm)[4] = (m)[4];   (tm)[5] = (m)[7]; \
  (tm)[ 6] = (m)[2];   (tm)[7] = (m)[5];   (tm)[8] = (m)[8]; }

//Transpose matrix 4x4
#define gcgTRANSPOSEMATRIX4(tm, m) {   \
  (tm)[ 0] = (m)[ 0];   (tm)[ 1] = (m)[ 4];   (tm)[ 2] = (m)[ 8];   (tm)[ 3] = (m)[12]; \
  (tm)[ 4] = (m)[ 1];   (tm)[ 5] = (m)[ 5];   (tm)[ 6] = (m)[ 9];   (tm)[ 7] = (m)[13]; \
  (tm)[ 8] = (m)[ 2];   (tm)[ 9] = (m)[ 6];   (tm)[10] = (m)[10];   (tm)[11] = (m)[14]; \
  (tm)[12] = (m)[ 3];   (tm)[13] = (m)[ 7];   (tm)[14] = (m)[11];   (tm)[15] = (m)[15]; }

// Scale matrix 2x2
#define gcgSCALEMATRIX2(dest, m, s) \
  {(dest)[0] = (m)[0] * (s); (dest)[1] = (m)[1] * (s); (dest)[2] = (m)[2] * (s); (dest)[3] = (m)[3] * (s); }

// Scale matrix 3x3
#define gcgSCALEMATRIX3(dest, m, s) {  \
  (dest)[0] = (m)[0] * (s); (dest)[1] = (m)[1] * (s); (dest)[2] = (m)[2] * (s); \
  (dest)[3] = (m)[3] * (s); (dest)[4] = (m)[4] * (s); (dest)[5] = (m)[5] * (s); \
  (dest)[6] = (m)[6] * (s); (dest)[7] = (m)[7] * (s); (dest)[8] = (m)[8] * (s); }

// Scale matrix 4x4
#define gcgSCALEMATRIX4(dest, m, s) {   \
  (dest)[ 0] = (m)[ 0] * (s); (dest)[ 1] = (m)[ 1] * (s); (dest)[ 2] = (m)[ 2] * (s); (dest)[ 3] = (m)[ 3] * (s); \
  (dest)[ 4] = (m)[ 4] * (s); (dest)[ 5] = (m)[ 5] * (s); (dest)[ 6] = (m)[ 6] * (s); (dest)[ 7] = (m)[ 7] * (s); \
  (dest)[ 8] = (m)[ 8] * (s); (dest)[ 9] = (m)[ 9] * (s); (dest)[10] = (m)[10] * (s); (dest)[11] = (m)[11] * (s); \
  (dest)[12] = (m)[12] * (s); (dest)[13] = (m)[13] * (s); (dest)[14] = (m)[14] * (s); (dest)[15] = (m)[15] * (s); }

// Additions and subtractions
#define gcgADDMATRIX2(dest, m1, m2) {   \
  (dest)[ 0] = (m1)[ 0] + (m2)[ 0]; (dest)[ 1] = (m1)[ 1] + (m2)[ 1]; \
  (dest)[ 2] = (m1)[ 2] + (m2)[ 2]; (dest)[ 3] = (m1)[ 3] + (m2)[ 3]; }

#define gcgADDMATRIX3(dest, m1, m2) {   \
  (dest)[ 0] = (m1)[ 0] + (m2)[ 0]; (dest)[ 1] = (m1)[ 1] + (m2)[ 1]; (dest)[ 2] = (m1)[ 2] + (m2)[ 2]; \
  (dest)[ 3] = (m1)[ 3] + (m2)[ 3]; (dest)[ 4] = (m1)[ 4] + (m2)[ 4]; (dest)[ 5] = (m1)[ 5] + (m2)[ 5]; \
  (dest)[ 6] = (m1)[ 6] + (m2)[ 6]; (dest)[ 7] = (m1)[ 7] + (m2)[ 7]; (dest)[ 8] = (m1)[ 8] + (m2)[ 8]; }

#define gcgADDMATRIX4(dest, m1, m2) {   \
  (dest)[ 0] = (m1)[ 0] + (m2)[ 0]; (dest)[ 1] = (m1)[ 1] + (m2)[ 1]; (dest)[ 2] = (m1)[ 2] + (m2)[ 2]; (dest)[ 3] = (m1)[ 3] + (m2)[ 3]; \
  (dest)[ 4] = (m1)[ 4] + (m2)[ 4]; (dest)[ 5] = (m1)[ 5] + (m2)[ 5]; (dest)[ 6] = (m1)[ 6] + (m2)[ 6]; (dest)[ 7] = (m1)[ 7] + (m2)[ 7]; \
  (dest)[ 8] = (m1)[ 8] + (m2)[ 8]; (dest)[ 9] = (m1)[ 9] + (m2)[ 9]; (dest)[10] = (m1)[10] + (m2)[10]; (dest)[11] = (m1)[11] + (m2)[11]; \
  (dest)[12] = (m1)[12] + (m2)[12]; (dest)[13] = (m1)[13] + (m2)[13]; (dest)[14] = (m1)[14] + (m2)[14]; (dest)[15] = (m1)[15] + (m2)[15]; }

#define gcgSUBMATRIX2(dest, m1, m2) {   \
  (dest)[ 0] = (m1)[ 0] - (m2)[ 0]; (dest)[ 1] = (m1)[ 1] - (m2)[ 1]; \
  (dest)[ 2] = (m1)[ 2] - (m2)[ 2]; (dest)[ 3] = (m1)[ 3] - (m2)[ 3]; }

#define gcgSUBMATRIX3(dest, m1, m2) {   \
  (dest)[ 0] = (m1)[ 0] - (m2)[ 0]; (dest)[ 1] = (m1)[ 1] - (m2)[ 1]; (dest)[ 2] = (m1)[ 2] - (m2)[ 2]; \
  (dest)[ 3] = (m1)[ 3] - (m2)[ 3]; (dest)[ 4] = (m1)[ 4] - (m2)[ 4]; (dest)[ 5] = (m1)[ 5] - (m2)[ 5]; \
  (dest)[ 6] = (m1)[ 6] - (m2)[ 6]; (dest)[ 7] = (m1)[ 7] - (m2)[ 7]; (dest)[ 8] = (m1)[ 8] - (m2)[ 8]; }

#define gcgSUBMATRIX4(dest, m1, m2) {   \
  (dest)[ 0] = (m1)[ 0] - (m2)[ 0]; (dest)[ 1] = (m1)[ 1] - (m2)[ 1]; (dest)[ 2] = (m1)[ 2] - (m2)[ 2]; (dest)[ 3] = (m1)[ 3] - (m2)[ 3]; \
  (dest)[ 4] = (m1)[ 4] - (m2)[ 4]; (dest)[ 5] = (m1)[ 5] - (m2)[ 5]; (dest)[ 6] = (m1)[ 6] - (m2)[ 6]; (dest)[ 7] = (m1)[ 7] - (m2)[ 7]; \
  (dest)[ 8] = (m1)[ 8] - (m2)[ 8]; (dest)[ 9] = (m1)[ 9] - (m2)[ 9]; (dest)[10] = (m1)[10] - (m2)[10]; (dest)[11] = (m1)[11] - (m2)[11]; \
  (dest)[12] = (m1)[12] - (m2)[12]; (dest)[13] = (m1)[13] - (m2)[13]; (dest)[14] = (m1)[14] - (m2)[14]; (dest)[15] = (m1)[15] - (m2)[15]; }

//Multiply matrix 3x3
#define gcgMULTMATRIX3(result, m1, m2) {   \
	(result)[ 0] = (m1)[ 0] * (m2)[ 0] + (m1)[ 1] * (m2)[ 3] + (m1)[ 2] * (m2)[ 6]; \
	(result)[ 1] = (m1)[ 0] * (m2)[ 1] + (m1)[ 1] * (m2)[ 4] + (m1)[ 2] * (m2)[ 7]; \
	(result)[ 2] = (m1)[ 0] * (m2)[ 2] + (m1)[ 1] * (m2)[ 5] + (m1)[ 2] * (m2)[ 8]; \
	(result)[ 3] = (m1)[ 3] * (m2)[ 0] + (m1)[ 4] * (m2)[ 3] + (m1)[ 5] * (m2)[ 6]; \
	(result)[ 4] = (m1)[ 3] * (m2)[ 1] + (m1)[ 4] * (m2)[ 4] + (m1)[ 5] * (m2)[ 7]; \
	(result)[ 5] = (m1)[ 3] * (m2)[ 2] + (m1)[ 4] * (m2)[ 5] + (m1)[ 5] * (m2)[ 8]; \
	(result)[ 6] = (m1)[ 6] * (m2)[ 0] + (m1)[ 7] * (m2)[ 3] + (m1)[ 8] * (m2)[ 6]; \
	(result)[ 7] = (m1)[ 6] * (m2)[ 1] + (m1)[ 7] * (m2)[ 4] + (m1)[ 8] * (m2)[ 7]; \
	(result)[ 8] = (m1)[ 6] * (m2)[ 2] + (m1)[ 7] * (m2)[ 5] + (m1)[ 8] * (m2)[ 8]; }

// Multiplica as matrizes 4x4 m1 e m2 sem utilizar laco
#define gcgMULTMATRIX4(result, m1, m2) {   \
	(result)[ 0] = (m1)[ 0] * (m2)[ 0] + (m1)[ 1] * (m2)[ 4] + (m1)[ 2] * (m2)[ 8] + (m1)[ 3] * (m2)[12]; \
	(result)[ 1] = (m1)[ 0] * (m2)[ 1] + (m1)[ 1] * (m2)[ 5] + (m1)[ 2] * (m2)[ 9] + (m1)[ 3] * (m2)[13]; \
	(result)[ 2] = (m1)[ 0] * (m2)[ 2] + (m1)[ 1] * (m2)[ 6] + (m1)[ 2] * (m2)[10] + (m1)[ 3] * (m2)[14]; \
	(result)[ 3] = (m1)[ 0] * (m2)[ 3] + (m1)[ 1] * (m2)[ 7] + (m1)[ 2] * (m2)[11] + (m1)[ 3] * (m2)[15]; \
	(result)[ 4] = (m1)[ 4] * (m2)[ 0] + (m1)[ 5] * (m2)[ 4] + (m1)[ 6] * (m2)[ 8] + (m1)[ 7] * (m2)[12]; \
	(result)[ 5] = (m1)[ 4] * (m2)[ 1] + (m1)[ 5] * (m2)[ 5] + (m1)[ 6] * (m2)[ 9] + (m1)[ 7] * (m2)[13]; \
	(result)[ 6] = (m1)[ 4] * (m2)[ 2] + (m1)[ 5] * (m2)[ 6] + (m1)[ 6] * (m2)[10] + (m1)[ 7] * (m2)[14]; \
	(result)[ 7] = (m1)[ 4] * (m2)[ 3] + (m1)[ 5] * (m2)[ 7] + (m1)[ 6] * (m2)[11] + (m1)[ 7] * (m2)[15]; \
	(result)[ 8] = (m1)[ 8] * (m2)[ 0] + (m1)[ 9] * (m2)[ 4] + (m1)[10] * (m2)[ 8] + (m1)[11] * (m2)[12]; \
	(result)[ 9] = (m1)[ 8] * (m2)[ 1] + (m1)[ 9] * (m2)[ 5] + (m1)[10] * (m2)[ 9] + (m1)[11] * (m2)[13]; \
	(result)[10] = (m1)[ 8] * (m2)[ 2] + (m1)[ 9] * (m2)[ 6] + (m1)[10] * (m2)[10] + (m1)[11] * (m2)[14]; \
	(result)[11] = (m1)[ 8] * (m2)[ 3] + (m1)[ 9] * (m2)[ 7] + (m1)[10] * (m2)[11] + (m1)[11] * (m2)[15]; \
	(result)[12] = (m1)[12] * (m2)[ 0] + (m1)[13] * (m2)[ 4] + (m1)[14] * (m2)[ 8] + (m1)[15] * (m2)[12]; \
	(result)[13] = (m1)[12] * (m2)[ 1] + (m1)[13] * (m2)[ 5] + (m1)[14] * (m2)[ 9] + (m1)[15] * (m2)[13]; \
	(result)[14] = (m1)[12] * (m2)[ 2] + (m1)[13] * (m2)[ 6] + (m1)[14] * (m2)[10] + (m1)[15] * (m2)[14]; \
	(result)[15] = (m1)[12] * (m2)[ 3] + (m1)[13] * (m2)[ 7] + (m1)[14] * (m2)[11] + (m1)[15] * (m2)[15]; }

// Multiply the 3x4 affine matrices m1 e m2.
#define gcgMULTMATRIX34(result, m1, m2) {   \
	(result)[0]  = (m1)[0] * (m2)[0] + (m1)[1] * (m2)[4] + (m1)[2] * (m2)[8];            \
	(result)[1]  = (m1)[0] * (m2)[1] + (m1)[1] * (m2)[5] + (m1)[2] * (m2)[9];            \
	(result)[2]  = (m1)[0] * (m2)[2] + (m1)[1] * (m2)[6] + (m1)[2] * (m2)[10];           \
	(result)[3]  = (m1)[0] * (m2)[3] + (m1)[1] * (m2)[7] + (m1)[2] * (m2)[11] + (m1)[3]; \
	(result)[4]  = (m1)[4] * (m2)[0] + (m1)[5] * (m2)[4] + (m1)[6] * (m2)[8];            \
	(result)[5]  = (m1)[4] * (m2)[1] + (m1)[5] * (m2)[5] + (m1)[6] * (m2)[9];            \
	(result)[6]  = (m1)[4] * (m2)[2] + (m1)[5] * (m2)[6] + (m1)[6] * (m2)[10];           \
	(result)[7]  = (m1)[4] * (m2)[3] + (m1)[5] * (m2)[7] + (m1)[6] * (m2)[11] + (m1)[7]; \
	(result)[8]  = (m1)[8] * (m2)[0] + (m1)[9] * (m2)[4] + (m1)[10] * (m2)[8];           \
	(result)[9]  = (m1)[8] * (m2)[1] + (m1)[9] * (m2)[5] + (m1)[10] * (m2)[9];           \
	(result)[10] = (m1)[8] * (m2)[2] + (m1)[9] * (m2)[6] + (m1)[10] * (m2)[10];          \
	(result)[11] = (m1)[8] * (m2)[3] + (m1)[9] * (m2)[7] + (m1)[10] * (m2)[11] + (m1)[11]; }


//Multiply a 3x1 vector by a 1x3 vector resulting in a 3x3 matrix
#define gcgMATRIX3VECTOR3VECTOR3(result, v1, v2) {   \
  (result)[0] = (v1)[0] * (v2)[0]; (result)[1] = (v1)[0] *  (v2)[1]; (result)[2] =  (v1)[0] *  (v2)[2]; \
  (result)[3] = (v1)[1] * (v2)[0]; (result)[4] = (v1)[1] *  (v2)[1]; (result)[5] =  (v1)[1] *  (v2)[2]; \
  (result)[6] = (v1)[2] * (v2)[0]; (result)[7] = (v1)[2] * (v2)[1]; (result)[8] =  (v1)[2] *  (v2)[2]; }


#define gcgAPPLYMATRIX3VECTOR3(r, t, vetor) { \
	(r)[0] =  (vetor)[0] * (t)[0]  +  (vetor)[1] * (t)[1]  +  (vetor)[2] * (t)[2]; \
	(r)[1] =  (vetor)[0] * (t)[3]  +  (vetor)[1] * (t)[4]  +  (vetor)[2] * (t)[5]; \
	(r)[2] =  (vetor)[0] * (t)[6]  +  (vetor)[1] * (t)[7]  +  (vetor)[2] * (t)[8]; }

#define gcgAPPLYMATRIX2VECTOR2(r, t, vetor) { \
    (r)[0] = (vetor)[0] * (t)[0]  +  (vetor)[1] * (t)[1]; \
    (r)[1] = (vetor)[0] * (t)[2]  +  (vetor)[1] * (t)[3]; }

#define gcgAPPLYMATRIX4VECTOR4(r, t, vetor) { \
	(r)[0] =  (vetor)[0] * (t)[0]  +  (vetor)[1] * (t)[1]  +  (vetor)[2] * (t)[2]  +  (vetor)[3] * (t)[3];  \
	(r)[1] =  (vetor)[0] * (t)[4]  +  (vetor)[1] * (t)[5]  +  (vetor)[2] * (t)[6]  +  (vetor)[3] * (t)[7];  \
	(r)[2] =  (vetor)[0] * (t)[8]  +  (vetor)[1] * (t)[9]  +  (vetor)[2] * (t)[10] +  (vetor)[3] * (t)[11]; \
	(r)[3] =  (vetor)[0] * (t)[12] +  (vetor)[1] * (t)[13] +  (vetor)[2] * (t)[14] +  (vetor)[3] * (t)[15]; }

#define gcgAPPLYMATRIX34VECTOR3(r, t, vetor) { \
	(r)[0] =  (vetor)[0] * (t)[0]  +  (vetor)[1] * (t)[1]  +  (vetor)[2] * (t)[2]  + (t)[3];  \
	(r)[1] =  (vetor)[0] * (t)[4]  +  (vetor)[1] * (t)[5]  +  (vetor)[2] * (t)[6]  + (t)[7];  \
	(r)[2] =  (vetor)[0] * (t)[8]  +  (vetor)[1] * (t)[9]  +  (vetor)[2] * (t)[10] + (t)[11]; }

#define gcgLINEARMATRIX4VECTOR3(r, t, vetor) { \
	(r)[0] =  (vetor)[0] * (t)[0]  +  (vetor)[1] * (t)[1]  +  (vetor)[2] * (t)[2];  \
	(r)[1] =  (vetor)[0] * (t)[4]  +  (vetor)[1] * (t)[5]  +  (vetor)[2] * (t)[6];  \
	(r)[2] =  (vetor)[0] * (t)[8]  +  (vetor)[1] * (t)[9]  +  (vetor)[2] * (t)[10]; }

// QUATERNION ALGEBRA ///////////////////////////////////////////////

// Expressions //////////////////////////////////////////////////////
// Commands /////////////////////////////////////////////////////////

// Makes an unit quaternion
#define gcgNORMALIZEQUATERNION(qf, q) { \
    register double mag = 1.0/(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]); \
    gcgSCALEVECTOR3(qf, q, mag); }

// Quaternion conjugate
#define gcgCONJUGATEQUATERNION(qi, q) {   \
  (qi)[0] = -(q)[0];                      \
  (qi)[1] = -(q)[1];                      \
  (qi)[2] = -(q)[2];                      \
  (qi)[3] =  (q)[3]; }


// Multiply two quaternions (Graham's product)
static inline void gcgMULTQUATERNION(VECTOR4 dest, VECTOR4 q2, VECTOR4 q1) {
  VECTOR4 t1;
  t1[3] = (q1)[3]*(q2)[3] - (q1)[0]*(q2)[0] - (q1)[1]*(q2)[1] - (q1)[2]*(q2)[2];
	t1[0] = (q1)[3]*(q2)[0] + (q1)[0]*(q2)[3] + (q1)[1]*(q2)[2] - (q1)[2]*(q2)[1];
	t1[1] = (q1)[3]*(q2)[1] + (q1)[1]*(q2)[3] + (q1)[2]*(q2)[0] - (q1)[0]*(q2)[2];
	t1[2] = (q1)[3]*(q2)[2] + (q1)[2]*(q2)[3] + (q1)[0]*(q2)[1] - (q1)[1]*(q2)[0];
  gcgCOPYVECTOR4(dest, t1);
}

static inline void gcgMULTQUATERNION(VECTOR4d dest, VECTOR4d q2, VECTOR4d q1) {
  VECTOR4d t1;
  t1[3] = (q1)[3]*(q2)[3] - (q1)[0]*(q2)[0] - (q1)[1]*(q2)[1] - (q1)[2]*(q2)[2];
	t1[0] = (q1)[3]*(q2)[0] + (q1)[0]*(q2)[3] + (q1)[1]*(q2)[2] - (q1)[2]*(q2)[1];
	t1[1] = (q1)[3]*(q2)[1] + (q1)[1]*(q2)[3] + (q1)[2]*(q2)[0] - (q1)[0]*(q2)[2];
	t1[2] = (q1)[3]*(q2)[2] + (q1)[2]*(q2)[3] + (q1)[0]*(q2)[1] - (q1)[1]*(q2)[0];
  gcgCOPYVECTOR4(dest, t1);
}

// Build a 4x4 rotation matrix from a quaternion
static inline void gcgQUATERNIONTOMATRIX4(MATRIX4 m, VECTOR4 q) {
    register double xx = (q)[0] * (q)[0], yy = (q)[1] * (q)[1], zz = (q)[2] * (q)[2];
    register double xy = (q)[0] * (q)[1], xz = (q)[0] * (q)[2], yz = (q)[1] * (q)[2];
    register double xw = (q)[0] * (q)[3], yw = (q)[1] * (q)[3], zw = (q)[2] * (q)[3];
    m[0] =  (float) (1.0 - (yy + yy + zz + zz));
    m[1] =  (float) (xy + xy - zw - zw);
    m[2] =  (float) (xz + xz + yw + yw);
    m[3] = 0.0f;
    m[4] =  (float) (xy + xy + zw + zw);
    m[5] =  (float) (1.0 - (zz + zz + xx + xx));
    m[6] =  (float) (yz + yz - xw - xw);
    m[7] = 0.0f;
    m[8] =  (float) (xz + xz - yw - yw);
    m[9] =  (float) (yz + yz + xw + xw);
    m[10] =  (float) (1.0 - (yy + yy + xx + xx));
    m[11] =  m[12] = m[13] = m[14] = 0.0f;
    m[15] = 1.0f;
}

// Build a 4x4 rotation matrix from a quaternion
static inline void gcgQUATERNIONTOMATRIX4(MATRIX4d m, VECTOR4d q) {
    register double xx = (q)[0] * (q)[0], yy = (q)[1] * (q)[1], zz = (q)[2] * (q)[2];
    register double xy = (q)[0] * (q)[1], xz = (q)[0] * (q)[2], yz = (q)[1] * (q)[2];
    register double xw = (q)[0] * (q)[3], yw = (q)[1] * (q)[3], zw = (q)[2] * (q)[3];
    m[0] =  (1.0 - (yy + yy + zz + zz));
    m[1] =  (xy + xy - zw - zw);
    m[2] =  (xz + xz + yw + yw);
    m[3] = 0.0;
    m[4] =  (xy + xy + zw + zw);
    m[5] =  (1.0 - (zz + zz + xx + xx));
    m[6] =  (yz + yz - xw - xw);
    m[7] = 0.0;
    m[8] =  (xz + xz - yw - yw);
    m[9] =  (yz + yz + xw + xw);
    m[10] =  (1.0 - (yy + yy + xx + xx));
    m[11] =  m[12] = m[13] = m[14] = 0.0f;
    m[15] = 1.0f;
}

// Build a quaternion that forms a rotation around an axis
static inline void gcgAXISTOQUATERNION(VECTOR4 q, float phi, VECTOR3 a) {
    gcgSCALEVECTOR3(q, a, sinf(phi * 0.5f));
    q[3] = cosf(phi * 0.5f);
}

static inline void gcgAXISTOQUATERNION(VECTOR4d q, double phi, VECTOR3d a) {
    register double factor =  sin(phi * 0.5);
    gcgSCALEVECTOR3(q, a, factor);
    q[3] =  cos(phi * 0.5);
}


// Obtains the angle and rotation axis from a quaternion
#define gcgQUATERNIONTOAXIS(angle, a, q) {    \
    register double cos_a = q[3];                       \
    angle = acos(cos_a) * 2;                  \
    register double sin_a = sqrt(1.0 - cos_a * cos_a ); \
    if(fabs(sin_a) < 0.0005) sin_a = 1.0;     \
    gcgSETVECTOR3(a, q[0] / sin_a, q[1] / sin_a, q[2] / sin_a); }



// Build a 3x3 rotation matrix from a quaternion
#define gcgQUATERNIONTOMATRIX3(m, q) {          \
    register double xx = (q)[0] * (q)[0], yy = (q)[1] * (q)[1], zz = (q)[2] * (q)[2];\
    register double xy = (q)[0] * (q)[1], xz = (q)[0] * (q)[2], yz = (q)[1] * (q)[2];\
    register double xw = (q)[0] * (q)[3], yw = (q)[1] * (q)[3], zw = (q)[2] * (q)[3];\
    m[0] =  (1.0 - 2.0 * ( yy + zz));    \
    m[1] =  (2.0 * (xy - zw));           \
    m[2] =  (2.0 * (xz + yw));           \
    m[3] =  (2.0 * (xy + zw));           \
    m[4] =  (1.0 - 2.0 * (zz + xx));     \
    m[5] =  (2.0 * (yz - xw));           \
    m[6] =  (2.0 * (xz - yw));           \
    m[7] =  (2.0 * (yz + xw));           \
    m[8] =  (1.0 - 2.0 * (yy + xx)); }

// Build a 3x4 rotation matrix from a quaternion
#define gcgQUATERNIONTOMATRIX34(m, q) {          \
    register double xx = (q)[0] * (q)[0], yy = (q)[1] * (q)[1], zz = (q)[2] * (q)[2];\
    register double xy = (q)[0] * (q)[1], xz = (q)[0] * (q)[2], yz = (q)[1] * (q)[2];\
    register double xw = (q)[0] * (q)[3], yw = (q)[1] * (q)[3], zw = (q)[2] * (q)[3];\
    m[0] =  (1.0 - 2.0 * ( yy + zz));    \
    m[1] =  (2.0 * (xy - zw));           \
    m[2] =  (2.0 * (xz + yw));           \
    m[3] = 0.0;                                 \
    m[4] =  (2.0 * (xy + zw));           \
    m[5] =  (1.0 - 2.0 * (zz + xx));     \
    m[6] =  (2.0 * (yz - xw));           \
    m[7] = 0.0;                                 \
    m[8] =  (2.0 * (xz - yw));           \
    m[9] =  (2.0 * (yz + xw));           \
    m[10] =  (1.0 - 2.0 * (yy + xx));    \
    m[11] = 0.0;    }


// Build a quaternion from a 4x4 rotation matrix
#define gcgMATRIX4TOQUATERNION(q, mat) {                                  \
  register double trace = 1.0 + (mat)[0] + (mat)[5] + (mat)[10];          \
  if(trace > EPSILON) {                                                   \
    double S = sqrt(trace) * 2.0;                                          \
    (q)[0] = ((mat)[9] - (mat)[6]) / S;                                   \
    (q)[1] = ((mat)[2] - (mat)[8]) / S;                                   \
    (q)[2] = ((mat)[4] - (mat)[1]) / S;                                   \
    (q)[3] = 0.25 * S;                                                    \
  } else                                                                  \
     if((mat)[0] > (mat)[5] && (mat)[0] > (mat)[10]) {                    \
        double S  = sqrt(1.0 + (mat)[0] - (mat)[5] - (mat)[10]) * 2.0;     \
        (q)[0] = 0.25 * S;                                                \
        (q)[1] = ((mat)[4] + (mat)[1] ) / S;                              \
        (q)[2] = ((mat)[2] + (mat)[8] ) / S;                              \
        (q)[3] = ((mat)[9] - (mat)[6] ) / S;                              \
    } else if((mat)[5] > (mat)[10]) {			                                \
        double S  = sqrt(1.0 + (mat)[5] - (mat)[0] - (mat)[10] ) * 2.0;    \
        (q)[0] = ((mat)[4] + (mat)[1] ) / S;                              \
        (q)[1] = 0.25 * S;                                                \
        (q)[2] = ((mat)[9] + (mat)[6] ) / S;                              \
        (q)[3] = ((mat)[2] - (mat)[8] ) / S;                              \
    } else {	                                                            \
        double S  = sqrt(1.0 + (mat)[10] - (mat)[0] - (mat)[5] ) * 2.0;    \
        (q)[0] = ((mat)[2] + (mat)[8] ) / S;                              \
        (q)[1] = ((mat)[9] + (mat)[6] ) / S;                              \
        (q)[2] = 0.25 * S;                                                \
        (q)[3] = ((mat)[4] - (mat)[1] ) / S;                              \
    }                                                                     \
    gcgNORMALIZEQUATERNION(q, q); }


//Diadic tensor product of two 3D vectors
#define gcgTENSORPRODUCT3(result, v1, v2) {   \
	(result)[ 0] = (v1)[ 0] * (v2)[ 0]; \
	(result)[ 1] = (v1)[ 0] * (v2)[ 1]; \
	(result)[ 2] = (v1)[ 0] * (v2)[ 2]; \
	(result)[ 3] = (v1)[ 1] * (v2)[ 0]; \
	(result)[ 4] = (v1)[ 1] * (v2)[ 1]; \
	(result)[ 5] = (v1)[ 1] * (v2)[ 2]; \
	(result)[ 6] = (v1)[ 2] * (v2)[ 0]; \
	(result)[ 7] = (v1)[ 2] * (v2)[ 1]; \
	(result)[ 8] = (v1)[ 2] * (v2)[ 2]; }



// Build a quaternion from Euler angles
static inline void gcgEULERTOQUATERNION(VECTOR4 q, float pitch, float yaw, float roll) {
  VECTOR4 qx = {sinf(pitch * -0.5f), 0.0f, 0.0f,  cosf(pitch  * -0.5f)};
  VECTOR4 qy = {0.0f,  sinf(yaw * -0.5f), 0.0f,  cosf(yaw * -0.5f)};
  VECTOR4 qz = {0.0f, 0.0f,  sinf(roll * -0.5f),  cosf(roll * -0.5f)};
  gcgMULTQUATERNION(qy, qy, qx);
  gcgMULTQUATERNION(q,  qz, qy);
}

static inline void gcgEULERTOQUATERNION(VECTOR4d q, double pitch, double yaw, double roll) {
  VECTOR4d qx = {sin(pitch * -0.5), 0, 0, cos(pitch  * -0.5)};
  VECTOR4d qy = {0,  sin(yaw * -0.5), 0,  cos(yaw * -0.5)};
  VECTOR4d qz = {0, 0,  sin(roll * -0.5), cos(roll * -0.5)};
  gcgMULTQUATERNION(qy, qy, qx);
  gcgMULTQUATERNION(q,  qz, qy);
}


// Vector rotation by quaternion application:  vi = qr * v * qr-1
static inline void gcgAPPLYQUATERNIONVECTOR3(VECTOR4 vi, VECTOR4 qr, VECTOR3 va) {
  VECTOR4 qi, kr;
  gcgCONJUGATEQUATERNION(qi, qr);
  gcgCOPYVECTOR3((float*) kr, va);
  (kr)[3] = 0.0;
  gcgMULTQUATERNION(kr, qr, kr);
  gcgMULTQUATERNION(kr, kr, qi);
  gcgCOPYVECTOR3(vi, kr);
}

static inline void gcgAPPLYQUATERNIONVECTOR3(VECTOR4d vi, VECTOR4d qr, VECTOR3d va) {
  VECTOR4d qi, kr;
  gcgCONJUGATEQUATERNION(qi, qr);
  gcgCOPYVECTOR3((double*) kr, va);
  (kr)[3] = 0.0;
  gcgMULTQUATERNION(kr, qr, kr);
  gcgMULTQUATERNION(kr, kr, qi);
  gcgCOPYVECTOR3(vi, kr);
}

////////////////////////////////////////////////////////////////////////////////////
// FUNCTION PROTOTYPES
////////////////////////////////////////////////////////////////////////////////////


/// @defgroup algebra Linear algebra functions and classes
/// GCGlib provides a minimum linear algebra functionality which serves as basis for several
/// methods. It is the core of important computer vision and computer geometry algorithms.

///@{


/// @brief Computes the inverse of a 2x2 matrix by the direct method. It is suitable for fast inverse computation in bidimensional spaces. In this version,
/// both input and output matrices are C vectors of 4 floats in row first order.
/// @param[out] inverse Points to the 2x2 matrix that receives the inverted matrix of \a matrix parameter. If it is a singular matrix,
/// it receives its adjoint.
/// @param[in] matrix The input 2x2 matrix to be inverted.
/// @return true if inverse exists and, in that case, the \a inverse parameter receives the inverted matrix. If returns false, the input \a matrix
/// is singular and the \a inverse parameter receives its adjoint matrix.
/// @see gcgInverseMatrix3
/// @see gcgInverseMatrix4
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgInverseMatrix2(MATRIX2 inverse, MATRIX2 matrix);

/// @brief Computes the inverse of a 3x3 matrix by the direct method. It is suitable for fast inverse computation in tridimensional spaces.
/// @param[out] inverse Points to the 3x3 matrix that receives the inverted matrix of \a matrix parameter. If it is a singular matrix,
/// it receives its adjoint. In this version, both input and output matrices are C vectors of 9 floats in row first order.
/// @param[in] matrix The input 3x3 matrix to be inverted.
/// @return true if inverse exists and, in that case, the \a inverse parameter receives the inverted matrix. If returns false, the input \a matrix
/// is singular and the \a inverse parameter receives its adjoint matrix.
/// @see gcgInverseMatrix2
/// @see gcgInverseMatrix4
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgInverseMatrix3(MATRIX3 inverse, MATRIX3 matrix);

/// @brief Computes the inverse of a 4x4 matrix by the direct method. It is suitable for fast inverse computation in homogeneous spaces
/// in computer graphics. In this version, both input and output matrices are C vectors of 16 floats in row first order.
/// @param[out] inverse Points to the 4x4 matrix that receives the inverted matrix of \a matrix parameter. If it is a singular matrix,
/// it receives its adjoint.
/// @param[in] matrix The input 4x4 matrix to be inverted.
/// @return true if inverse exists and, in that case, the \a inverse parameter receives the inverted matrix. If returns false, the input \a matrix
/// is singular and the \a inverse parameter receives its adjoint matrix.
/// @see gcgInverseMatrix2
/// @see gcgInverseMatrix3
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgInverseMatrix4(MATRIX4 inverse, MATRIX4 matrix);

/// @brief Computes the inverse of a 2x2 matrix by the direct method. It is suitable for fast inverse computation in bidimensional spaces. In this version,
/// both input and output matrices are C vectors of 4 doubles in row first order.
/// @param[out] inverse Points to the 2x2 matrix that receives the inverted matrix of \a matrix parameter. If it is a singular matrix,
/// it receives its adjoint.
/// @param[in] matrix The input 2x2 matrix to be inverted.
/// @return true if inverse exists and, in that case, the \a inverse parameter receives the inverted matrix. If returns false, the input \a matrix
/// is singular and the \a inverse parameter receives its adjoint matrix.
/// @see gcgInverseMatrix3
/// @see gcgInverseMatrix4
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgInverseMatrix2(MATRIX2d inverse, MATRIX2d matrix);

/// @brief Computes the inverse of a 3x3 matrix by the direct method. It is suitable for fast inverse computation in tridimensional spaces.
/// @param[out] inverse Points to the 3x3 matrix that receives the inverted matrix of \a matrix parameter. If it is a singular matrix,
/// it receives its adjoint. In this version, both input and output matrices are C vectors of 9 doubles in row first order.
/// @param[in] matrix The input 3x3 matrix to be inverted.
/// @return true if inverse exists and, in that case, the \a inverse parameter receives the inverted matrix. If returns false, the input \a matrix
/// is singular and the \a inverse parameter receives its adjoint matrix.
/// @see gcgInverseMatrix2
/// @see gcgInverseMatrix4
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgInverseMatrix3(MATRIX3d inverse, MATRIX3d matrix);

/// @brief Computes the inverse of a 4x4 matrix by the direct method. It is suitable for fast inverse computation in homogeneous spaces
/// in computer graphics. In this version, both input and output matrices are C vectors of 16 doubles in row first order.
/// @param[out] inverse Points to the 4x4 matrix that receives the inverted matrix of \a matrix parameter. If it is a singular matrix,
/// it receives its adjoint.
/// @param[in] matrix The input 4x4 matrix to be inverted.
/// @return true if inverse exists and, in that case, the \a inverse parameter receives the inverted matrix. If returns false, the input \a matrix
/// is singular and the \a inverse parameter receives its adjoint matrix.
/// @see gcgInverseMatrix2
/// @see gcgInverseMatrix3
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgInverseMatrix4(MATRIX4d inverse, MATRIX4d matrix);

/// @brief Computes the eigensystem decomposition of a symmetric matrix \a matrix with arbitraty order. The resulted eigenvectors are
/// stored as rows in a matrix \a eigenvectors with \a norder x \a norder elements. Their respective \a norder eigenvalues are stored
/// in the vector \a eigenvalues. The eigenvectors and eigenvalues are ordered by decreasing eigenvalues. Version adapted from the public domain Java
/// Matrix library JAMA. In this version, the input and output matrices are C vectors of \a norder x \a norder floats in row first order.
/// @param[in] norder order of the input square matrix.
/// @param[in] matrix pointer to a square matrix of \a norder x \a norder elements stored in row first order.
/// @param[out] eigenvectors pointer to a square matrix of \a norder x \a norder elements that will receive the \a norder eigenvectors of
/// the input matrix arranged by row first order.
/// @param[out] eigenvalues pointer to a vector of \a norder elements that will receive the eigenvalues of the input matrix. They are
/// stored by decreasing eigenvalues and their positions are respective to the eigenvectors positions in the matrix \a eigenvectors.
/// @return true if the eigensystem was correctly computed. If it returns false, the results returned in \a eigenvectors and \a eigenvalues are
/// undefined. Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
/// @see gcgEigenSymmetricMatrix3
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgEigenSymmetric(int norder, float matrix[], float eigenvectors[], float eigenvalues[]);

/// @brief Computes the eigensystem decomposition of a symmetric matrix \a matrix with arbitraty order. The resulted eigenvectors are
/// stored as rows in a matrix \a eigenvectors with \a norder x \a norder elements. Their respective \a norder eigenvalues are stored
/// in the vector \a eigenvalues. The eigenvectors and eigenvalues are ordered by decreasing eigenvalues. Version adapted from the public domain Java
/// Matrix library JAMA. In this version, the input and output matrices are C vectors of \a norder x \a norder doubles in row first order.
/// @param[in] norder order of the input square matrix.
/// @param[in] matrix pointer to a square matrix of \a norder x \a norder elements stored in row first order.
/// @param[out] eigenvectors pointer to a square matrix of \a norder x \a norder elements that will receive the \a norder eigenvectors of
/// the input matrix arranged by row first order.
/// @param[out] eigenvalues pointer to a vector of \a norder elements that will receive the eigenvalues of the input matrix. They are
/// stored by decreasing eigenvalues and their positions are respective to the eigenvectors positions in the matrix \a eigenvectors.
/// @return true if the eigensystem was correctly computed. If it returns false, the results returned in \a eigenvectors and \a eigenvalues are
/// undefined. Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
/// @see gcgEigenSymmetricMatrix3
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgEigenSymmetric(int norder, double matrix[], double eigenvectors[], double eigenvalues[]);


/// @brief Computes the eigensystem decomposition of a symmetric 3 x 3 matrix \a matrix. The resulted eigenvectors are
/// stored as rows in a matrix \a eigenvectors with 3 x 3 elements. Their respective three eigenvalues are stored
/// in the vector \a eigenvalues. The eigenvectors and eigenvalues are ordered by decreasing eigenvalues. Version adapted from the public domain Java
/// Matrix library JAMA. In this version, the input and output matrices are C vectors of 3 x 3 floats in row first order.
/// @param[in] matrix pointer to a square matrix of 3 x 3 elements stored in row first order.
/// @param[out] eigenvectors pointer to a square matrix of 3 x 3 elements that will receive the three eigenvectors of
/// the input matrix arranged by row first order.
/// @param[out] eigenvalues pointer to a vector of three elements that will receive the eigenvalues of the input matrix. They are
/// stored by decreasing eigenvalues and their positions are respective to the eigenvectors positions in the matrix \a eigenvectors.
/// @return true if the eigensystem was correctly computed. If it returns false, the results returned in \a eigenvectors and \a eigenvalues are
/// undefined. Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
/// @see gcgEigenSymmetricMatrix
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgEigenSymmetricMatrix3(MATRIX3 matrix, MATRIX3 eigenvectors, VECTOR3 eigenvalues);

/// @brief Computes the eigensystem decomposition of a symmetric 3 x 3 matrix \a matrix. The resulted eigenvectors are
/// stored as rows in a matrix \a eigenvectors with 3 x 3 elements. Their respective three eigenvalues are stored
/// in the vector \a eigenvalues. The eigenvectors and eigenvalues are ordered by decreasing eigenvalues. Version adapted from the public domain Java
/// Matrix library JAMA. In this version, the input and output matrices are C vectors of 3 x 3 doubles in row first order.
/// @param[in] matrix pointer to a square matrix of 3 x 3 elements stored in row first order.
/// @param[out] eigenvectors pointer to a square matrix of 3 x 3 elements that will receive the three eigenvectors of
/// the input matrix arranged by row first order.
/// @param[out] eigenvalues pointer to a vector of three elements that will receive the eigenvalues of the input matrix. They are
/// stored by decreasing eigenvalues and their positions are respective to the eigenvectors positions in the matrix \a eigenvectors.
/// @return true if the eigensystem was correctly computed. If it returns false, the results returned in \a eigenvectors and \a eigenvalues are
/// undefined. Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
/// @see gcgEigenSymmetricMatrix
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgEigenSymmetricMatrix3(MATRIX3d matrix, MATRIX3d eigenvectors, VECTOR3d eigenvalues);


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////////////     MATRIX FOR ALGEBRA FUNCTIONS     /////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

template<class NUMTYPE> class    GCG_API_CLASS    gcgMATRIX;

///@}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////     DRAW macros and functions ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// @defgroup graphics Graphics utilities
/// GCGlib provides classes and functions to help the drawing of several graphics objects.
///@{
///@}

/// @defgroup primdraw Primitive drawing
/// This section presents functions and classes for drawing primitives.
///@{
/// @ingroup graphics

/// @brief Draws the GCG logo on the top right conner of the viewport.
/// @param[in] scale Factor to be used in scaling the GCG logo image which originally has 256 by 64 pixels.
/// @return true if the logo is correctly drawn.
/// @remarks Modifies several graphics library features: blending, depth test, texture enabling, matrix mode, shade model and polygon filling.
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgDrawLogo(float scale = 0.67);

/// @brief Draws an axis aligned box. Normals are sent and can be used for lighting. All parameters are float values.
/// @param[in] bbmin Minimum x, y and z coordinates of the bounding box.
/// @param[in] bbmax Maximum x, y and z coordinates of the bounding box.
/// @return true if the axis aligned bounding box is correctly drawn.
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgDrawAABox(VECTOR3 bbmin, VECTOR3 bbmax);

/// @brief Draws an axis aligned box. Normals are sent and can be used for lighting. All parameters are double values.
/// @param[in] bbmin Minimum x, y and z coordinates of the bounding box.
/// @param[in] bbmax Maximum x, y and z coordinates of the bounding box.
/// @return true if the axis aligned bounding box is correctly drawn.
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgDrawAABox(VECTOR3d bbmin, VECTOR3d bbmax);

/// @brief Draws an oriented box. Normals are sent and can be used for lighting. All parameters are float values.
/// @param[in] obbangles Euler angles in degrees for box orientation. Euler angles are generally referred as yaw, pitch and
/// roll angles, corresponding to rotations to the x, y and z axis, in this order. Note that GCGlib uses the OpenGL orientation
/// system. See gcgEULERTOQUATERNION() and gcgQUATERNIONTOMATRIX4() to further information on rotations.
/// @param[in] obbcenter The x, y and z coordinates of the box center.
/// @param[in] obbsize The x, y and z sizes of the box, before its rotation by the Euler angles.
/// @return true if the axis aligned bounding box is correctly drawn.
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgDrawOBox(VECTOR3 obbangles, VECTOR3 obbcenter, VECTOR3 obbsize);

/// @brief Draws an oriented box. Normals are sent and can be used for lighting.  All parameters are double values.
/// @param[in] obbangles Euler angles in degrees for box orientation. Euler angles are generally referred as yaw, pitch and
/// roll angles, corresponding to rotations to the x, y and z axis, in this order. Note that GCGlib uses the OpenGL orientation
/// system. See gcgEULERTOQUATERNION() and gcgQUATERNIONTOMATRIX4() to further information on rotations.
/// @param[in] obbcenter The x, y and z coordinates of the box center.
/// @param[in] obbsize The x, y and z sizes of the box, before its rotation by the Euler angles.
/// @return true if the axis aligned bounding box is correctly drawn.
/// @since 0.01.0
GCG_API_FUNCTION    bool gcgDrawOBox(VECTOR3d obbangles, VECTOR3d obbcenter, VECTOR3d obbsize);

/// @brief Draws an oriented pyramid (its base is not drawn) which can be used to represent vectors: 4 triangles are drawn using
/// 6 vertices. Normals are sent and can be used for lighting. All parameters are float.
/// @param[in] x The x center position of the vector.
/// @param[in] y The y center position of the vector.
/// @param[in] z The z center position of the vector.
/// @param[in] vector The vector indicating the direction of the pyramid. Its magnitude is ignored. The vector must be non null.
/// @param[in] scale Scaling to be applied to the pyramid with unitary height. It is generally the vector magnitude.
/// @return true if the vector is drawn.
/// @since 0.01.0
/// @see gcgDrawVectorPyramidClosed
/// @see gcgDrawVectorThetrahedron
/// @see gcgDrawVectorThetrahedronClosed
GCG_API_FUNCTION    bool gcgDrawVectorPyramid(float x, float y, float z, VECTOR3 vector, float scale);

/// @brief Draws an oriented pyramid (its base is not drawn) which can be used to represent vectors: 4 triangles are drawn using
/// 6 vertices. Normals are sent and can be used for lighting. All parameters are double.
/// @param[in] x The x center position of the vector.
/// @param[in] y The y center position of the vector.
/// @param[in] z The z center position of the vector.
/// @param[in] vector The vector indicating the direction of the pyramid. Its magnitude is ignored. The vector must be non null.
/// @param[in] scale Scaling to be applied to the pyramid with unitary height. It is generally the vector magnitude.
/// @return true if the vector is drawn.
/// @since 0.01.0
/// @see gcgDrawVectorPyramidClosed
/// @see gcgDrawVectorThetrahedron
/// @see gcgDrawVectorThetrahedronClosed
GCG_API_FUNCTION    bool gcgDrawVectorPyramid(float x, float y, float z, VECTOR3d vector, float scale);

/// @brief Draws an oriented pyramid (its base is also drawn) which can be used to represent vectors: 6 triangles are drawn using
/// 8 vertices. Normals are sent and can be used for lighting. All parameters are float.
/// @param[in] x The x center position of the vector.
/// @param[in] y The y center position of the vector.
/// @param[in] z The z center position of the vector.
/// @param[in] vector The vector indicating the direction of the pyramid. Its magnitude is ignored. The vector must be non null.
/// @param[in] scale Scaling to be applied to the pyramid with unitary height. It is generally the vector magnitude.
/// @return true if the vector is drawn.
/// @since 0.01.62
/// @see gcgDrawVectorPyramid
/// @see gcgDrawVectorThetrahedron
/// @see gcgDrawVectorThetrahedronClosed
GCG_API_FUNCTION    bool gcgDrawVectorPyramidClosed(float x, float y, float z, VECTOR3 vector, float scale);

/// @brief Draws an oriented pyramid (its base is also drawn) which can be used to represent vectors: 6 triangles are drawn using
/// 8 vertices. Normals are sent and can be used for lighting. All parameters are double.
/// @param[in] x The x center position of the vector.
/// @param[in] y The y center position of the vector.
/// @param[in] z The z center position of the vector.
/// @param[in] vector The vector indicating the direction of the pyramid. Its magnitude is ignored. The vector must be non null.
/// @param[in] scale Scaling to be applied to the pyramid with unitary height. It is generally the vector magnitude.
/// @return true if the vector is drawn.
/// @since 0.01.62
/// @see gcgDrawVectorPyramid
/// @see gcgDrawVectorThetrahedron
/// @see gcgDrawVectorThetrahedronClosed
GCG_API_FUNCTION    bool gcgDrawVectorPyramidClosed(float x, float y, float z, VECTOR3d vector, float scale);

/// @brief Draws an oriented thetahedron (its base is not drawn) which can be used to represent vectors: 3 triangles are drawn using
/// 5 vertices. Normals are sent and can be used for lighting. All parameters are float.
/// @param[in] x The x center position of the vector.
/// @param[in] y The y center position of the vector.
/// @param[in] z The z center position of the vector.
/// @param[in] vector The vector indicating the direction of the thetrahedron. Its magnitude is ignored. The vector must be non null.
/// @param[in] scale Scaling to be applied to the thetrahedron with unitary height. It is generally the vector magnitude.
/// @return true if the vector is drawn.
/// @since 0.01.62
/// @see gcgDrawVectorPyramid
/// @see gcgDrawVectorPyramidClosed
/// @see gcgDrawVectorThetrahedronClosed
GCG_API_FUNCTION    bool gcgDrawVectorThetrahedron(float x, float y, float z, VECTOR3 vector, float scale);

/// @brief Draws an oriented thetrahedron (its base is not drawn) which can be used to represent vectors: 3 triangles are drawn using
/// 5 vertices. Normals are sent and can be used for lighting. All parameters are double.
/// @param[in] x The x center position of the vector.
/// @param[in] y The y center position of the vector.
/// @param[in] z The z center position of the vector.
/// @param[in] vector The vector indicating the direction of the thetrahedron. Its magnitude is ignored. The vector must be non null.
/// @param[in] scale Scaling to be applied to the thetrahedron with unitary height. It is generally the vector magnitude.
/// @return true if the vector is drawn.
/// @since 0.01.62
/// @see gcgDrawVectorPyramid
/// @see gcgDrawVectorPyramidClosed
/// @see gcgDrawVectorThetrahedronClosed
GCG_API_FUNCTION    bool gcgDrawVectorThetrahedron(float x, float y, float z, VECTOR3d vector, float scale);

/// @brief Draws an oriented thetrahedron (its base is also drawn) which can be used to represent vectors: 4 triangles are drawn using
/// 6 vertices. Normals are sent and can be used for lighting. All parameters are float.
/// @param[in] x The x center position of the vector.
/// @param[in] y The y center position of the vector.
/// @param[in] z The z center position of the vector.
/// @param[in] vector The vector indicating the direction of the thetrahedron. Its magnitude is ignored. The vector must be non null.
/// @param[in] scale Scaling to be applied to the thetrahedron with unitary height. It is generally the vector magnitude.
/// @return true if the vector is drawn.
/// @since 0.01.62
/// @see gcgDrawVectorPyramid
/// @see gcgDrawVectorPyramidClosed
/// @see gcgDrawVectorThetrahedron
GCG_API_FUNCTION    bool gcgDrawVectorThetrahedronClosed(float x, float y, float z, VECTOR3 vector, float scale);

/// @brief Draws an oriented thetrahedron (its base is also drawn) which can be used to represent vectors: 4 triangles are drawn using
/// 6 vertices. Normals are sent and can be used for lighting. All parameters are double.
/// @param[in] x The x center position of the vector.
/// @param[in] y The y center position of the vector.
/// @param[in] z The z center position of the vector.
/// @param[in] vector The vector indicating the direction of the thetrahedron. Its magnitude is ignored. The vector must be non null.
/// @param[in] scale Scaling to be applied to the thetrahedron with unitary height. It is generally the vector magnitude.
/// @return true if the vector is drawn.
/// @since 0.01.62
/// @see gcgDrawVectorPyramid
/// @see gcgDrawVectorPyramidClosed
/// @see gcgDrawVectorThetrahedron
GCG_API_FUNCTION    bool gcgDrawVectorThetrahedronClosed(float x, float y, float z, VECTOR3d vector, float scale);


///@}

/// @defgroup colorgraph Color computation
/// This section presents functions and classes for color computation.
///@{
/// @ingroup graphics

/// @brief Computes a value between 0 and 1 in function of time that can be used as opacity value to simulate blinking objects.
/// @return A value between 0 and 1 in function of time that is suitable to simulate blinking objects.
/// @since 0.01.0
GCG_API_FUNCTION    float gcgBlinkingAlpha();

/// @brief Returns a color given a normalized "heat" value between 0 and 1. Uses a palette that partitions the unity with
/// the colors dark blue, blue, bluish cyan, cyan, greenish cyan, green, greenish yellow, yellow, orange and red. All parameters have
/// float type.
/// @param[in] normheat value to be mapped into a 'heat' color. Values smaller than zero are clamped to 0. Values bigger than 1
/// are clamped to 1.
/// @param[out] color the resulting color heat.
/// @return true if the color is computed.
GCG_API_FUNCTION    bool gcgHeatColor(float normheat, VECTOR3 color);

/// @brief Returns a color given a normalized "heat" value between 0 and 1. Uses a palette that partitions the unity with
/// the colors dark blue, blue, bluish cyan, cyan, greenish cyan, green, greenish yellow, yellow, orange and red. All parameters have
/// double type.
/// @param[in] normheat value to be mapped into a 'heat' color. Values smaller than zero are clamped to 0. Values bigger than 1
/// are clamped to 1.
/// @param[out] color the resulting color heat.
/// @return true if the color is computed.
GCG_API_FUNCTION    bool gcgHeatColor(double normheat, VECTOR3d color);

///@}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////     FONT macros, classes, and functions /////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// GCGFONT Versions
#define GCG_FONT_VERSION 0xf010

// Compression modes
#define GCG_FONT_UNCOMPRESSED    0
#define GCG_FONT_COMPRESSED_RLE  1

#pragma pack(push, 1)  // Must have 1 byte alignment

// Structure for the GCG font file format .gff version 1.0.
typedef struct _GCGFONTDATA {
    // Header
    unsigned short  version;        // First two bytes indicate version: 1.0 = 0xf010
    unsigned int    fontdatasize;   // Font data size: header + information + maps
    unsigned char   compression;    // Font image compression mode

    // Font information dependent on version number
    unsigned int    width;          // Font image width
    unsigned int    height;         // Font image height
    unsigned int    cellwidth;      // Character cell width
    unsigned int    cellheight;     // Character cell height
    unsigned char   firstASCII;     // ASCII value of the first character in the font map

    // Information about the chars inside the cell
    unsigned int    xoffset;        // Offset in x for all characters in pixels
    unsigned int    yoffset;        // Offset in y for all characters in pixels
    unsigned int    charheight;     // Height of all characters in font

    ////////////////////////////////////////////////////////////////////
    // Font data maps as a sequence of chars.
    // nchars = ((unsigned int) width / cellwidth) * ((unsigned int) height / cellheight);
    ////////////////////////////////////////////////////////////////////
    // unsigned char charwidths[nchars];       // Width of each character texture in pixels
    // unsigned char basewidths[nchars];       // Character bases in pixels
    // unsigned char fontmap[remainingbytes];  // Font image
} GCGFONTDATA;

// Class for internal font handling
class     GCG_API_CLASS    gcgFONT  :  public gcgCLASS {
  public:
    unsigned int  textureID;      // The font texture ID for OpenGL
    unsigned int  nchars;         // Number of characters in this font
    unsigned char firstASCII;     // ASCII code of the first character in this font
    int           font_base;      // Character OpenGL list base.

    unsigned int  charheight;     // Character height in pixels
    unsigned char *basewidths;    // Character widths in pixels.

  public:
    gcgFONT();
    virtual ~gcgFONT();

    // Object initiation
    bool loadGFF(char *fontname);  // Loads a font from a .gff file
    bool createFromData(GCGFONTDATA *font);
    void releaseFont(); // Free all font resources

    // Functions to retrieve string information for rendering
    void textLength(unsigned int *strwidth, unsigned int *strheight, char *str, int strlength); // Computes the box spanned by this string
    int  charsThatFit(float width, char *str, int strlength); // Computes how many chars fit to the width.
};


// Utilities for font creation
GCG_API_FUNCTION    bool gcgSaveGFF(char *name, GCGFONTDATA *gcgfont);
GCG_API_FUNCTION    GCGFONTDATA *gcgImportBFF(char *name); // Imports a .bff font file

#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////     TEXT macros, classes, and functions /////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Number of fonts internally implemented
#define GCG_SYSTEM_FONTS   12

// Registered system fonts
#define GCG_FONT_SANSSERIF_11_NORMAL        0
#define GCG_FONT_TAHOMA_12_NORMAL           1
#define GCG_FONT_TAHOMA_12_BOLD             2
#define GCG_FONT_TAHOMA_13_NORMAL           3
#define GCG_FONT_COURIERNEW_15_NORMAL       4
#define GCG_FONT_COURIERNEW_15_BOLD         5
#define GCG_FONT_COURIERNEW_15_ITALIC       6
#define GCG_FONT_COURIERNEW_15_BOLDITALIC   7
#define GCG_FONT_TAHOMA_17_NORMAL           8
#define GCG_FONT_TAHOMA_17_BOLD             9
#define GCG_FONT_TAHOMA_17_ITALIC           10
#define GCG_FONT_TAHOMA_17_BOLDITALIC       11

// Class definition
class    GCG_API_CLASS    gcgTEXT   :  public gcgCLASS {
  private:
    float   x, y, z;          // Next print position
    gcgFONT *currentfont;     // Selected font object
    float   scalex, scaley;   // Font scale.
    float   textangle;        // Text orientation
    int     borderpixels[2];  // Border pixels separation

    int     viewport[4];      // OpenGL viewport
    float   textbox[4];       // Output text box

    int     wrap;             // Wrap text to box?
    bool    noTextBox;        // Text box enabled?

    // Needed to allow multiple OpenGL contexts
    gcgFONT localsystemfonts[GCG_SYSTEM_FONTS];
  public:
    // Construction
    gcgTEXT();
    virtual ~gcgTEXT();

    // Font parameters
    bool setFont(gcgFONT *font);
    bool setSystemFont(int fontindex);
    void fontScale(float scalex, float scaley);
    float setBestFitSystemFont(char *str, float width); // Selects the best normal system font and scaling that fits to the width passed.
    gcgFONT* getCurrentFont();

    // Text box functions. Use screen-space coordinates (pixels).
    void enableTextBox(float x, float y, float width, float height);  // Restricts the output area to this box.
    void enableTextBoxAt3DPos(float xpos, float ypos, float zpos, float width, float height);
    void adjustTextBox(float xoffset, float yoffset, float widthoffset, float heightoffset);
    void setBorder(int npixelsX, int npixelsY); // Number of pixels for text separation
    void disableTextBox(); // The output area is the entire viewport.
    void drawTextBox(float boxR, float boxG, float boxB, float boxA, float frameR, float frameG, float frameB, float frameA, float linewidth);

    // Text output functions. Use screen-space coordinates (pixels).
    void wrapText(bool wraptobox);  // Text is wrapped to the box if wraptobox is TRUE.
    void textPosition(float x, float y); // Position inside the text box.
    void textOrientation(float angle);   // Position inside the text box and orientation.
    void gcgprintf(const char *format, ...);

    // Information

  private:
    void initTextOutput();   // Initialization for al text output functions
    void finishTextOutput(); // Finishing the text output for all functions
    void outputText(int length, char *str); // Prints text to the output area. Implements the wrap functionality.
};


// Generates C code for internal registration as system font
bool gcgGenerateSystemFontCode(char *name, GCGFONTDATA *gcgfont);


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////     GEOMETRY macros, classes, and functions /////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////
// GCG geometry macros. More efficient than functions. But results in a larger code.
////////////////////////////////////////////////////////////////////////////////////

// Add a point to a Axis Aligned Box min/max vectors
#define gcgADDPPOINTAABox(bbmin, bbmax, p) { \
  if((bbmin)[0] > (p)[0]) (bbmin)[0] = (p)[0]; \
  if((bbmin)[1] > (p)[1]) (bbmin)[1] = (p)[1]; \
  if((bbmin)[2] > (p)[2]) (bbmin)[2] = (p)[2]; \
  if((bbmax)[0] < (p)[0]) (bbmax)[0] = (p)[0]; \
  if((bbmax)[1] < (p)[1]) (bbmax)[1] = (p)[1]; \
  if((bbmax)[2] < (p)[2]) (bbmax)[2] = (p)[2]; }


////////////////////////////////////////////////////////////////////////////////////
// GCG geometry prototypes.
////////////////////////////////////////////////////////////////////////////////////

// Functions for quaternions
GCG_API_FUNCTION    void gcgQuaternionSlerp(VECTOR4 dest, VECTOR4 p, VECTOR4 q, float t);

// Functions for alignment tranformations
// Computes the rotation matrix that aligns the z-axis with the direction specified by vector dir.
GCG_API_FUNCTION    bool gcgComputeAlignMatrix(MATRIX4 matrix, VECTOR3 dir);

// Trackball simulation
GCG_API_FUNCTION    void gcgTrackball(VECTOR4 q, float p1x, float p1y, float p2x, float p2y);

// Functions for bounding boxes
GCG_API_FUNCTION    void gcgAABoxFromOBox(VECTOR3 aabbmin, VECTOR3 aabbmax, VECTOR3 obbangles, VECTOR3 obbposition, VECTOR3 obbmin, VECTOR3 obbmax);

// Functions for computing intersections
GCG_API_FUNCTION    int  gcgIntersectTriangleTriangle(VECTOR3 V0, VECTOR3 V1, VECTOR3 V2, VECTOR3 U0, VECTOR3 U1, VECTOR3 U2);
GCG_API_FUNCTION    int  gcgIntersectTriangleTriangleLine(VECTOR3 V0, VECTOR3 V1, VECTOR3 V2, VECTOR3 U0, VECTOR3 U1, VECTOR3 U2, int *coplanar, VECTOR3 isectpt1, VECTOR3 isectpt2);
GCG_API_FUNCTION    int  gcgIntersectLineLine(VECTOR3 p1, VECTOR3 p2, VECTOR3 p3, VECTOR3 p4, VECTOR3 pa, VECTOR3 pb,  double *mua, double *mub);
GCG_API_FUNCTION    int  gcgIntersectPointLine(VECTOR3 point, VECTOR3 edgeA, VECTOR3 edgeB);
GCG_API_FUNCTION    int  gcgIntersectPointTriangle(VECTOR3 p, VECTOR3 A, VECTOR3 B, VECTOR3 C);
GCG_API_FUNCTION    bool gcgIntersectLineBox2D(VECTOR2 p1, VECTOR2 p2, VECTOR2 box2dMin, VECTOR2 box2dMax);

// Functions for triangles

/// @fn float gcgTriangleArea(VECTOR3 v0, VECTOR3 v1, VECTOR3 v2);
/// @brief Computes the area of a triangle with edges (v0,v1), (v1, v2), (v2, v0). See Graphics Gems II - Pag. 170.
/// @since 0.01.6
/// @param[in] v0 First vertex of the triangle.
/// @param[in] v1 Second vertex of the triangle.
/// @param[in] v2 Third vertex of the triangle.
/// @return the area of the triangle.
GCG_API_FUNCTION    float gcgTriangleArea(VECTOR3 v0, VECTOR3 v1, VECTOR3 v2);

/// @fn void gcgTriangleGradient(VECTOR3 grad_u, VECTOR3 v0, VECTOR3 v1, VECTOR3 v2, float u0, float u1, float u2)
/// @brief Computes the gradient of a scalar u over a 3D triangle with edges (v0,v1), (v1, v2), (v2, v0).
/// @since 0.01.6
/// @param[out] grad_u the 3D vector that will contain the gradient of u. The resulting gradient vector is necessarily over the triangle plane.
/// @param[in] v0 First vertex of the triangle.
/// @param[in] v1 Second vertex of the triangle.
/// @param[in] v2 Third vertex of the triangle.
/// @param[in] u0 The scalar value of v0 vertex.
/// @param[in] u1 The scalar value of v1 vertex.
/// @param[in] u2 The scalar value of v2 vertex.
GCG_API_FUNCTION    void gcgTriangleGradient(VECTOR3 grad_u, VECTOR3 v0, VECTOR3 v1, VECTOR3 v2, float u0, float u1, float u2);

//************* Double precision versions *************
GCG_API_FUNCTION    void gcgQuaternionSlerp(VECTOR4d dest, VECTOR4d p, VECTOR4d q, double t);
GCG_API_FUNCTION    bool gcgComputeAlignMatrix(MATRIX4d matrix, VECTOR3d dir);
GCG_API_FUNCTION    void gcgTrackball(VECTOR4d q, double p1x, double p1y, double p2x, double p2y);
GCG_API_FUNCTION    void gcgAABoxFromOBox(VECTOR3d aabbmin, VECTOR3d aabbmax, VECTOR3d obbangles, VECTOR3d obbposition, VECTOR3d obbmin, VECTOR3d obbmax);
GCG_API_FUNCTION    int  gcgIntersectTriangleTriangle(VECTOR3d V0, VECTOR3d V1, VECTOR3d V2, VECTOR3d U0, VECTOR3d U1, VECTOR3d U2);
GCG_API_FUNCTION    int  gcgIntersectTriangleTriangleLine(VECTOR3d V0, VECTOR3d V1, VECTOR3d V2, VECTOR3d U0, VECTOR3d U1, VECTOR3d U2, int *coplanar, VECTOR3d isectpt1, VECTOR3d isectpt2);
GCG_API_FUNCTION    int  gcgIntersectLineLine(VECTOR3d p1, VECTOR3d p2, VECTOR3d p3, VECTOR3d p4, VECTOR3d pa, VECTOR3d pb,  double *mua, double *mub);
GCG_API_FUNCTION    int  gcgIntersectPointLine(VECTOR3d point, VECTOR3d edgeA, VECTOR3d edgeB);
GCG_API_FUNCTION    int  gcgIntersectPointTriangle(VECTOR3d p, VECTOR3d A, VECTOR3d B, VECTOR3d C);
GCG_API_FUNCTION    bool gcgIntersectLineBox2D(VECTOR2d p1, VECTOR2d p2, VECTOR2d box2dMin, VECTOR2d box2dMax);
GCG_API_FUNCTION    double gcgTriangleArea(VECTOR3d v0, VECTOR3d v1, VECTOR3d v2);
GCG_API_FUNCTION    void gcgTriangleGradient(VECTOR3d grad_u, VECTOR3d v0, VECTOR3d v1, VECTOR3d v2, double u0, double u1, double u2);

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////     POLYGON macros, classes, and functions ////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// Internal structures for mesh representation.
/////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// Class gcgPOLYGONVERTEX: main abstract class for vertex handling.
///////////////////////////////////////////////////////////////

/*
class gcgPOLYGONVERTEX   :  public gcgCLASS {
  public:
    // Internal use in gcgPOLYGON class. Do not modify.
    unsigned int        nhalf_edges;    // Number of half-edges containing this vertex
    unsigned int        maxhalf_edges;  // Capacity of the half_edges array
    struct _GCGHALFEDGE **half_edges;   // Array of half-edges containing this vertex
    gcgPOLYGONVERTEX    *prevVertex;    // Previous vertex of a mesh
    gcgPOLYGONVERTEX    *nextVertex;    // Next vertex of a mesh

  public:
    virtual ~gcgPOLYGONVERTEX() {}

    // Returns true if this vextex is equal to vertex2
    virtual bool isEqual(gcgPOLYGONVERTEX *vertex2);

    // Copies the contents of vertex2 to vertex
    virtual void copy(gcgPOLYGONVERTEX *vertex2);
};

////////////////////////////////////////////////////////////////
// Class gcgVERTEX3: main abstract template class for
//                   3D vertex handling.
// - use:
//      gcgVERTEX3<float> for VECTOR3
//      gcgVERTEX3<double> for VECTOR3d
////////////////////////////////////////////////////////////////
template <typename T>
class gcgVERTEX3 : public gcgPOLYGONVERTEX {
  public:
    T position[3];

  public:
    virtual bool isEqual(T vertex2[3]) {
      return FEQUAL(this->position[0], vertex2[0]) &&
             FEQUAL(this->position[1], vertex2[1]) &&
             FEQUAL(this->position[2], vertex2[2]);
    };

    virtual void copy(T vertex2[3]) {
      this->position[0] = vertex2[0];
      this->position[1] = vertex2[1];
      this->position[2] = vertex2[2];
    };
};


// Internal polygon information
class    GCG_API_CLASS    gcgPOLYGON   :  public gcgCLASS {
  public:
   unsigned int nvertices;         // Number of vertices of this polygon
   struct _GCGHALFEDGE *half_edge; // Half-edges forming this polygon. One per vertex.
   gcgPOLYGON   *prevPolygon;      // Previous polygon of a mesh
   gcgPOLYGON   *nextPolygon;      // Next polygon of a mesh
};


// Internal Half-Edge information
typedef struct _GCGHALFEDGE {
   gcgPOLYGONVERTEX    *srcVertex;           // Vertex to which this half-edge belongs
   gcgPOLYGON          *face;                // Face to which this half-edge belongs
   struct _GCGHALFEDGE *nextHalfEdge;        // Next half-edge of this face
   struct _GCGHALFEDGE *prevHalfEdge;        // Previous half-edge of this face
   struct _GCGHALFEDGE *nextBrotherHalfEdge; // Next face half-edge
   struct _GCGHALFEDGE *prevBrotherHalfEdge; // Previous face half-edge
} GCGHALFEDGE;


/////////////////////////////////////////////////////////////
// Class gcgPOLYGONMESH: container for polygons and vertices.
/////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgPOLYGONMESH    :  public gcgCLASS {
  public:
    // Polygon information
    unsigned int     npolygons;   // Number of polygons of this object
    gcgPOLYGON       *polygons;   // Linked list of polygons

    // Vertex information
    unsigned int     nvertices;   // Number of vertices of this object
    gcgPOLYGONVERTEX *vertices;   // Linked list of vertices

    // Acess information
    GCGHALFEDGE*     last_half_edge;
    GCGHALFEDGE*     first_half_edge_brother;
    GCGHALFEDGE*     last_half_edge_brother;

  public:
    // Constructors and destructors
    gcgPOLYGONMESH();
    virtual ~gcgPOLYGONMESH();

    // Resources handling.
    void destroyPolygon();

    // Object data access and initialization
    bool addPolygon(gcgPOLYGON *polygon);
    bool addVertex(gcgPOLYGONVERTEX *vertex);
    gcgPOLYGONVERTEX* findSimilarVertex(gcgPOLYGONVERTEX *vertex);

    // Functions to attach vertices to polygons and edges
    bool  addPolygonVertex(gcgPOLYGON *ipolygon, gcgPOLYGONVERTEX *vertex, unsigned int newvertexIndex = 0);

    // Functions to retrieve information
    gcgPOLYGONVERTEX* getPolygonVertex(gcgPOLYGON *polygon, unsigned int vertexIndex);
    gcgPOLYGONVERTEX* getPolygonNextVertex(); // Gets the next edge in the last polygon acessed by getPolygonVertex.
    gcgPOLYGON*       getPolygonFromEdge(gcgPOLYGONVERTEX *vertexID1, gcgPOLYGONVERTEX *vertexID2);
    gcgPOLYGON*       getNextPolygonFromEdge();

    // Methods to remove objects. Keep remaining polygons and edges.
    bool removeVertex(gcgPOLYGONVERTEX *vertex);
    bool removeEdge(gcgPOLYGONVERTEX *vertex1, gcgPOLYGONVERTEX *vertex2);
    bool removePolygon(gcgPOLYGON *ipolygon);
    bool removeHalfEdge(GCGHALFEDGE* ihalf_edge);
    unsigned int removeIsolatedVertices();

    // Stellar Operations
    bool edgeCollapse(gcgPOLYGONVERTEX *vertexID1, gcgPOLYGONVERTEX *vertex2);
    bool halfEdgeCollapse(gcgPOLYGONVERTEX *vertexID1, gcgPOLYGONVERTEX *vertex2, gcgPOLYGONVERTEX *newvertex);
    bool edgeFlip(gcgPOLYGONVERTEX *vertex1, gcgPOLYGONVERTEX *vertex2);
    bool edgeWeld(gcgPOLYGONVERTEX *vertex);
    bool edgeSplit(gcgPOLYGONVERTEX *vertex1, gcgPOLYGONVERTEX *vertex2, gcgPOLYGONVERTEX *newvertex);
    bool polygonSplit(gcgPOLYGON *ipolygon, unsigned int vertexIndex, gcgPOLYGONVERTEX *newvertex);

    // Test link condition for edge collapse operation
    bool testLinkCondition(gcgPOLYGONVERTEX *vertex1, gcgPOLYGONVERTEX *vertex2);

    // Return the valence of ivertex
    unsigned int getValence(gcgPOLYGONVERTEX *vertexID);
    // Get the star of a vertex
    // starVertices - Returns a list of vertices
    // starPolygons - Returns a list of the faces
    bool getVertexStar(gcgPOLYGONVERTEX *vertex, gcgPOLYGONVERTEX **starVertexVertices, unsigned int* numVertices, gcgPOLYGON **starVertexPolygons, unsigned int* numPolygons);
    unsigned int getVerticesVertexStar(gcgPOLYGONVERTEX *vertexIndex, gcgPOLYGONVERTEX **starVertexVertices, unsigned int* numVertices);
    unsigned int getPolygonsVertexStar(gcgPOLYGONVERTEX *vertexID, gcgPOLYGON **starVertexPolygons, unsigned int* numPolygons);
    // Get the star of an edge
    unsigned int getEdgeStar(gcgPOLYGONVERTEX *vertex1, gcgPOLYGONVERTEX *vertex2, gcgPOLYGONVERTEX **starEdgeVertices, unsigned int* numVertices, gcgPOLYGON **starEdgePolygons, unsigned int* numPolygons);
    // Return the intersection between star1 and star2
    bool getStarIntersection(gcgPOLYGONVERTEX** starVertexVertices1, gcgPOLYGON** starVertexPolygons1, gcgPOLYGONVERTEX** starVertexVertices2, gcgPOLYGON** starVertexPolygons2, gcgPOLYGONVERTEX** starIntersectionVertices, gcgPOLYGON** starIntersectionPolygons, unsigned int numVertices1, unsigned int numPolygons1, unsigned int numVertices2, unsigned int numPolygons2, unsigned int* numVerticesIntersection, unsigned int* numPolygonsIntersection);
    // Compare two stars
    bool starComparison(gcgPOLYGONVERTEX** starVertices1, gcgPOLYGON** starPolygons1, gcgPOLYGONVERTEX** starVertices2, gcgPOLYGON** starPolygons2, unsigned int numVertices1, unsigned int numPolygons1, unsigned int numVertices2, unsigned int numPolygons2);

  private:// Check functions
    void testVertex();
    void testVertex(unsigned int vertexIndex);
    void testHalfEdgeBrother(GCGHALFEDGE* ihalf_edge);
    void testPolygons();
    void testStar(unsigned int *starVertex[2], unsigned int numVertices, unsigned int numPolygons);
    void testStarVertices(gcgPOLYGONVERTEX** starVertexVertices, unsigned int numVertices);
    void testStarVerticesRemove(gcgPOLYGONVERTEX** starVertexVertices, unsigned int numVertices);
    void testStarPolygons(gcgPOLYGON** starVertexPolygons, unsigned int numPolygons);
    void testStarPolygonsRemove(gcgPOLYGON** starVertexPolygons, unsigned int numPolygons);
    void testHalfEdgeBrother2();
    void testHalfEdgeBrother3();
};
*/

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////     SEMIREGULAR48 macros, classes, and functions /////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Vertex indices
#define GCG_VAPEX   0
#define GCG_VESQ    1
#define GCG_VDIR    2

////////////////////////////////////////////////////////////////////////////////
// Sides for connections on level 2:
//    Defining the base of a side (NORTH,WEST) as the base of the opposite side,
//  (SOUTH, EAST) we force the subdivisions of the first be propagated to the
//   other.
//    As such, we can change the topology of the generated mesh as follows:
//
//        Plane:    no forced connection
//        Cylinder: WEST is connected to EAST
//        Torus:    WEST is connected to EAST and NORTH is connected to SOUTH
////////////////////////////////////////////////////////////////////////////////
//
//            NORTH
//          p3------p2
//           | \  / |
//    WEST   |  \/  |   EAST
//           |  /\  |
//           | /  \ |
//          p0------p1
//            SOUTH
//
#define GCG_TOPOLOGY_PLANE      0     // Default topology
#define GCG_TOPOLOGY_CYLINDER   1
#define GCG_TOPOLOGY_TORUS      2

////////////////////////////////////////////////////////////////////////////////
// Flags for composing mask actions for vertex indexes of an adaptive object.
//            - GCG_REFINE: this triangle is too coarse and should be refined.
//            - GCG_SIMPLIFY: this triangle is too detailed and should be simplified.
//            - GCG_MAXIMUMLOD: this triangle reached its maximum level of detail.
//                              Avoid refining the sons of this node. Note that these
//                              may be refined to keep the mesh consistent.
//            - GCG_MINIMUMLOD: this triangle reached its minimum level of detail.
//                              Avoid simplifying the parents of this node. Note
//                              that these may be simplified to keep the mesh consistent.
//            - GCG_INVISIBLE: informs that this triangle is completely invisible
//            - GCG_TOTALLYVISIBLE: informs that this triangle is completely visible
//

#define GCG_REFINE           ((unsigned char) 0x01)
#define GCG_SIMPLIFY         ((unsigned char) 0x02)
#define GCG_MAXIMUMLOD       ((unsigned char) 0x04)
#define GCG_MINIMUMLOD       ((unsigned char) 0x08)
#define GCG_INVISIBLE        ((unsigned char) 0x10)
#define GCG_TOTALLYVISIBLE   ((unsigned char) 0x20)
#define GCG_SELECT0          ((unsigned char) 0x40)
#define GCG_SELECT1          ((unsigned char) 0x80)


//// Interfaces //////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//  gcgADAPTIVE: abstract interface to support refinable meshes
// - informs the geometry of a refinable object
// - must allocate all vertices.
// - all methods are abstract
////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgADAPTIVE    :  public gcgCLASS {
  public:

    /////////////////////////////////////////////////////////////////////
    // beginTesselation() is called in the beginning of a tesselation to
    // obtain the domain for subdivision in the form of four vertices. Its call
    // indicates that the previous tesselation was discarded and all vertices
    // may be freed.
    //  - For the semi-regular A48 mesh, the 4 vertices form a losangle
    //    as follows:
    //                 d3-----d2
		//                  |   /  |
		//                  |  /   |
		//                  | /    |
		//                 d0-----d1
		//
    //  - For every tesselation, this method must allocate the vertices as
    //    described above.
    virtual void beginTesselation() = 0;

    /////////////////////////////////////////////////////////////////////
    // action() is called to query if the triangle formed by counterclockwise
    // indexes iVertices[VAPEX], iVertices[VESQ], iVertices[DIR], should be
    // REFINED or SIMPLIFIED. It must return a byte mask with bits composed by
    // any combination of the flags:
    //      - GCG_REFINE: this triangle is too coarse and should be refined.
    //      - GCG_SIMPLIFY: this triangle is too detailed and should be simplified.
    //      - GCG_MAXIMUMLOD: this triangle reached its maximum level of detail.
    //                        Avoid refining the sons of this node. Note that these
    //                        may be refined to keep the mesh consistent.
    //      - GCG_MINIMUMLOD: this triangle reached its minimum level of detail.
    //                        Avoid simplifying the parents of this node. Note
    //                        that these may be simplified to keep the mesh consistent.
    //      - GCG_INVISIBLE: informs that this triangle is completely invisible
    //      - GCG_TOTALLYVISIBLE: informs that this triangle is completely visible
    //
    // It must return 0 if no action should be applied.
    virtual unsigned char action(unsigned char nivel, int *iVertices, unsigned char oldmask) = 0;

    ////////////////////////////////////////////////////////////////////
    // sample() must compute a NEW POINT for triangle subdivision
    // (splitting), and return its integer index. If the parameter apex2 is
    // positive, then it's the index of the apex of the triangle that forms
    // a losangle (diamond) with the triangle vertices pointed by iVertices.
    //
		// iVertices[VAPEX] +------+ iVertices[VDIR]
		//                  |    / |
		//                  |   /  |                         - VAPEX = 0
		//                  |  /   |                         - VESQ  = 1
		//                  | /    |                         - VDIR  = 2
		//  iVertices[VESQ] +------+ apex2 (if positive)
		//
		// - apex2 may be negative. In this case only one triangle is used in the
    //   subdivision.
    //
		// - it must return the interpolated point using the four points, case apex2 >= 0,
    //   or using the triangle vertices, otherwise. This index will be used for
    //   further subdivision queries or sampling.
		//
    virtual int sample(int *iVertices, int apex2) = 0;

    /////////////////////////////////////////////////////////////////////
    // endTesselation() is called when a tesselation has finished. Can be used
    // to adequate the object status.
    //
    virtual void endTesselation() = 0;
};


/////////////////////////////////////////////////////////////
// Class gcgSEMIREGULAR48: restricted unbalanced binary trees
//    - forms a semi-regular A48 mesh.
//    - controls the top-down subdivision of the mesh
//    - define the mesh topology
/////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgSEMIREGULAR48   :  public gcgCLASS {
  private:
    // Para formar a estrutura básica da árvore
    typedef struct __nodo {
      // Most used fields first
      int           iInfo;            // Index for front info, if this node
                                      // is at tree front then iInfo >= 0

      unsigned char nivel;            // Nivel (detalhe) desse nodo na árvore
      //unsigned int  indice;         // Índice único (estrutural) que
                                      //  identifica esse triangulo

      // Controle da estrutura de subdivisao
      int           filhoesq;         // Filho esquerdo do nodo
                                      // Filho direito do nodo = filhoesq + 1 sempre

      int           vizesq,
                    vizdir, vizbase;  // Indices para os vizinhos do nodo
    } NODO;

    // Information for front nodes
    typedef struct __frontinfo {
      unsigned char lastmask;       // Last flags returned by an action call
    } FRONTINFO;

   // Connection control for topology
    unsigned char topology;

    gcgADAPTIVE *geometria;   // Objeto corrente que fornece a geometria

    int           nnodos;       // Quantidade de nodos atual
    NODO          *nodos;       // Buffer dinamico para controle dos nodos
    int           maxnodos;     // Capacidade do buffer de nodos

    int           ntriangulos;  // Quantidade de triangulos atual
    int           maxtriang;    // Capacidade do buffer de triangulos
    FRONTINFO     *front;       // Front information: one for each triangle
    int           *vertices;    // Buffer dinamico para controle dos vertices dos triangulos

    int           *stack;       // Stack of integers for depth search
    int           top;          // Top of the stack = next node to be expanded
    int           maxstack;     // Stack capacity

    // For triangle selection
    unsigned char hidemask;     // Front triangle selection: if a logical AND of
                                // this mask with the lastmask is non-zero,
                                // then it's not returned in a getIndexArray call.
    unsigned char showmask;     // A logical AND with this mask and the lastmask,
                                // determines those triangles that must be shown.
                                // Only used if hidemask is non-zero.
    int           nhidden;      // Number of hidden elements in a getIndexArray call.

  // Metodos privados /////////////////////////////////////////////////////////
  private:
	  void divide_node(int inodo);
  	void triangle_bissection(int inodo, int novovertice, int ifilhoesq);
  	int  initTesselation(gcgADAPTIVE *geo);


	// Metodos públicos ////////////////////////////////////////////////////////
  public:
    // Creates a semiregular 4-8 mesh which domain and geometry is
    // defined by a gcgADAPTIVE object
    gcgSEMIREGULAR48();
    virtual ~gcgSEMIREGULAR48();

    void setTopology(int topologycode);

    // Generates a mesh WITH a restriction on the number of triangles using
    // a breath-first search.
    //    - uses the gcgADAPTIVE interface to build the mesh.
    //    - Returns the number of generated triangles.
    //
	  int tesselate(int maxtriang, gcgADAPTIVE *geometry);

    // Generates a mesh WITHOUT a restriction on the number of triangles using
    // a depth-first search. It is faster than the other version, but the stop
    // criteria are exclusively implemented by the refinable object.
    //
    //    - uses the gcgADAPTIVE interface to build the mesh.
    //    - Returns the number of generated triangles.
    //
	  int tesselate(gcgADAPTIVE *geometry);

	  // Returns the vertex array of last tesselation. Stores the number of
    // triangles (vextex triplets) in the 'ntriang' parameter if it is non-null.
	  int* getIndexArray(int *ntriang);

	  // Selects the triangles that will be delivered by getIndexArray.
	  int hideTriangles(unsigned char hidemask, unsigned char mustshowmask);
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//// Macros, classes and functions for DISCRETE REAL signals manipulation ///
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// @defgroup discrete Discrete signal processing
/// GCGlib provides functionality for processing 1D and 2D discrete signals. Signals
/// of any primitive type can be instantiated by using templates.
///@{

template<class NUMTYPE> class    GCG_API_CLASS    gcgDISCRETE1D;
template<class NUMTYPE> class    GCG_API_CLASS    gcgDISCRETE2D;

///@}

/// @defgroup border Border extension modes supported by GCGlib to process discrete signals.
/// @ingroup discrete
///@{

/// @brief Defines the border extension as: zero outside the signal support      0    0    0   s[0] s[1] s[2]  0    0    0
/// @since 0.01.0
#define GCG_BORDER_EXTENSION_ZERO               1

/// @brief Defines the border extension as:  the first/last value                s[0] s[0] s[0] s[0] s[1] s[2] s[2] s[2] s[2]
/// @since 0.01.0
#define GCG_BORDER_EXTENSION_CLAMP              2

/// @brief Defines the border extension as:  periodically extended               s[0] s[1] s[2] s[0] s[1] s[2] s[0] s[1] s[2]
/// @since 0.01.0
#define GCG_BORDER_EXTENSION_PERIODIC           3

/// @brief Defines the border extension as:  symmetrically extended               s[0] s[2] s[1] s[0] s[1] s[2] s[1] s[0] s[2]
/// @since 0.01.0
#define GCG_BORDER_EXTENSION_SYMMETRIC_NOREPEAT 4

/// @brief Defines the border extension as:  symmetrically extended with repeat   s[2] s[1] s[0] s[0] s[1] s[2] s[2] s[1] s[0]
/// @since 0.01.0
#define GCG_BORDER_EXTENSION_SYMMETRIC_REPEAT   5

///@}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////////  OPTIMIZATION macros, classes, and functions /////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// @brief Computes the solution of a linear system. If \a A is a square matrix (number of equations = number of
/// unknowns), the result is unique. If the number of rows of \a A is greater than the number of columns (number of
/// equations > number of unknowns), the solution minimizes the quadratic error of the system (least-squares).
/// @param[in] A matrix with \a m rows and \a n columns (\a m >= \a n).
/// @param[in] b vector with \a m rows.
/// @param[out] x vector with \a n rows that receives the solution.
/// @return true if the system had a solution computed.
/// @since 0.02.0
template<class NUMTYPE>    GCG_API_FUNCTION    bool gcgLinearSolver(gcgDISCRETE2D<NUMTYPE> *A, gcgDISCRETE1D<NUMTYPE> *b, gcgDISCRETE1D<NUMTYPE> *x);

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////   SIGNAL PROCESSING macros, classes, and functions ///////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

template <class NUMTYPE = float> class    GCG_API_CLASS    gcgSEQUENCEDERIVATIVE2D;
template <class NUMTYPE = float> class    GCG_API_CLASS    gcgFILTERMASK1D;

/////////////////////////////////////////////////////////////
// Signal comparison: error computation.
/////////////////////////////////////////////////////////////

template<class NUMTYPE>    GCG_API_FUNCTION    double computeMSEwith(gcgDISCRETE1D<NUMTYPE> *src1, gcgDISCRETE1D<NUMTYPE> *src2); // Computes the Mean Squared Error.
template<class NUMTYPE>    GCG_API_FUNCTION    double computePSNRwith(gcgDISCRETE1D<NUMTYPE> *src1, gcgDISCRETE1D<NUMTYPE> *src2);// Computes the Peak Signal-to-Noise Ratio in dB.
template<class NUMTYPE>    GCG_API_FUNCTION    double computeMAEwith(gcgDISCRETE1D<NUMTYPE> *src1, gcgDISCRETE1D<NUMTYPE> *src2); // Computes the Mean Absolute Error.

template<class NUMTYPE>    GCG_API_FUNCTION    double computeMSEwith(gcgDISCRETE2D<NUMTYPE> *src1, gcgDISCRETE2D<NUMTYPE> *src2); // Computes the Mean Squared Error.
template<class NUMTYPE>    GCG_API_FUNCTION    double computePSNRwith(gcgDISCRETE2D<NUMTYPE> *src1, gcgDISCRETE2D<NUMTYPE> *src2);// Computes the Peak Signal-to-Noise Ratio in dB.
template<class NUMTYPE>    GCG_API_FUNCTION    double computeMAEwith(gcgDISCRETE2D<NUMTYPE> *src1, gcgDISCRETE2D<NUMTYPE> *src2); // Computes the Mean Absolute Error.


/////////////////////////////////////////////////////////////
// Signal analysis.
/////////////////////////////////////////////////////////////

// Computes the gradient of 1D signal src. The derivative is computed using well-known Sobel operator and
// the result is stored in dx.
template<class NUMTYPE>    GCG_API_FUNCTION    bool gcgFirstDerivativeSobel1D(gcgDISCRETE1D<NUMTYPE> *src, gcgDISCRETE1D<NUMTYPE> *dx);

// Computes the gradient of 2D signal src. The partial derivatives are computed using well-known Sobel
// operator and the components are stored in dx and dy. The pointer for dx or dy may be NULL.
template<class NUMTYPE>    GCG_API_FUNCTION    bool gcgGradientSobel2D(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE2D<NUMTYPE> *dx, gcgDISCRETE2D<NUMTYPE> *dy);

// Computes the (optical) flow given the partial derivatives in X, Y and time of up to three channels.
// Uses the Augereau method (Bertrand Augereau, Benoît Tremblais, Christine Fernandez-Maloigne,
// "Vectorial computation of the optical flow in colorimage sequences", CIC05).
template<class NUMTYPE>    GCG_API_FUNCTION    bool gcgOpticalFlowAugereau2D(gcgDISCRETE2D<NUMTYPE> *dx1, gcgDISCRETE2D<NUMTYPE> *dy1, gcgDISCRETE2D<NUMTYPE> *dt1,
                                                         gcgDISCRETE2D<NUMTYPE> *dx2, gcgDISCRETE2D<NUMTYPE> *dy2, gcgDISCRETE2D<NUMTYPE> *dt2,
                                                         gcgDISCRETE2D<NUMTYPE> *dx3, gcgDISCRETE2D<NUMTYPE> *dy3, gcgDISCRETE2D<NUMTYPE> *dt3,
                                                         gcgDISCRETE2D<float> *outflowX, gcgDISCRETE2D<float> *outflowY);
template<class NUMTYPE>    GCG_API_FUNCTION    bool gcgOpticalFlowAugereau2D(gcgDISCRETE2D<NUMTYPE> *dx1, gcgDISCRETE2D<NUMTYPE> *dy1, gcgDISCRETE2D<NUMTYPE> *dt1,
                                                         gcgDISCRETE2D<NUMTYPE> *dx2, gcgDISCRETE2D<NUMTYPE> *dy2, gcgDISCRETE2D<NUMTYPE> *dt2,
                                                         gcgDISCRETE2D<NUMTYPE> *dx3, gcgDISCRETE2D<NUMTYPE> *dy3, gcgDISCRETE2D<NUMTYPE> *dt3,
                                                         gcgDISCRETE2D<double> *outflowX, gcgDISCRETE2D<double> *outflowY);


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////  General class for BASIS definitions   ////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// @defgroup basis Classes for defining discrete basis for signal projection and reconstruction.
/// @ingroup discrete
///@{

/// @brief Abstract class for 1D basis projection/reconstruction interfaces.
/// @tparam NUMTYPE Type of the samples representing the signal. Supported types: \e float, \e double, \e long, \e int and \e short.
/// @since 0.01.6
template <class NUMTYPE = float>
class    GCG_API_CLASS    gcgBASIS1D   :  public gcgCLASS {
  /// @brief Returns the number of coefficients used in 1D projection/reconstruction processes.
  virtual unsigned int getNumberOfCoefficients() = 0;

  /// @brief Sets the number of samples to be used in projection and reconstruction processes.
  /// @param[in] nsamples number of samples to be used in projection and reconstruction processs. Depending
  ///            on the basis, it might be used to discretize functions to speed up scalar products.
  /// @return true if setup is successful.
  virtual bool setNumberOfSamples(unsigned int nsamples) = 0;

  /// @brief Computes the coefficients of the projection of the 1D \a vector signal on the basis. It projects
  /// the number of samples of this basis (given by setNumberOfSamples()) starting at position \a atX of
  /// \a vector. The coefficients are stored in array \a outputcoef that is adjusted to have
  /// getNumberofCoefficients() coefficients.
  /// @param[in] atX origin of the signal for this projection (relative to \a vector origin).
  /// @param[in] vector array (as 1D signal) containing components of the vector to be projected onto the basis.
  /// @param[out] outputcoef array (as 1D signal) that receives the computed coefficients. It is adjusted to
  /// have getNumberofCoefficients() elements.
  /// @return true if projection is successful.
  /// @see setNumberOfSamples()
  /// @see getNumberOfCoefficients()
  /// @see reconstructSignal()
  /// @see gcgDISCRETE1D()
  virtual bool projectSignal(int atX, gcgDISCRETE1D<float> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef) = 0;
  virtual bool projectSignal(int atX, gcgDISCRETE1D<double> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef) = 0;
  virtual bool projectSignal(int atX, gcgDISCRETE1D<short> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef) = 0;
  virtual bool projectSignal(int atX, gcgDISCRETE1D<int> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef) = 0;
  virtual bool projectSignal(int atX, gcgDISCRETE1D<long> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef) = 0;

  /// @brief Computes the components of a vector (as 1D signal), using the getNumberofCoefficients()
  /// coefficients given in array \a inputcoef. The components (up to the number of samples given by
  /// setNumberOfSamples())are stored in the 1D signal \a outputvector starting at position \a atX.
  /// @param[in] atX origin of the signal for this projection (relative to \a outputvector origin).
  /// @param[in] inputcoef input array of coefficients (as 1D signal) representing the vector to be reconstructed.
  /// @param[out] outputvector array (as 1D signal) that receives the reconstructed samples starting at position atX.
  /// @return true if reconstruction is successful.
  /// @see setNumberOfSamples()
  /// @see getNumberOfCoefficients()
  /// @see projectSignal()
  /// @see gcgDISCRETE1D()
  virtual bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<float> *outputvector) = 0;
  virtual bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<double> *outputvector) = 0;
  virtual bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<short> *outputvector) = 0;
  virtual bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<int> *outputvector) = 0;
  virtual bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<long> *outputvector) = 0;
};

/// @brief Abstract class for 2D basis projection/reconstruction interfaces.
/// @tparam NUMTYPE Type of the samples representing the signal. Supported types: \e float, \e double, \e long, \e int and \e short.
/// @since 0.01.6
template <class NUMTYPE = float>
class    GCG_API_CLASS    gcgBASIS2D   :  public gcgCLASS {
  /// @brief Returns the number of coefficients used in 2D projection/reconstruction processes.
  virtual unsigned int getNumberOfCoefficients() = 0;

  /// @brief Computes the coefficients of the projection of the 2D signal \a vector on the 2D basis. The coefficients
  /// are stored in array \a outputcoef that will be ajusted to have getNumberofCoefficients() coefficients.
  /// @param[in] atX origin X coordinate of the signal for this projection (relative to \a vector).
  /// @param[in] atY origin Y coordinate of the signal for this projection (relative to \a vector).
  /// @param[in] vector 2D signal containing components of the vector to be projected onto the basis.
  /// @param[out] outputcoef array (as 1D signal) that receives the computed coefficients. It is adjusted to have getNumberofCoefficients() elements.
  /// @return true if projection is successful.
  /// @see getNumberOfCoefficients()
  /// @see reconstructSignal()
  /// @see gcgDISCRETE1D()
  /// @see gcgDISCRETE2D()
  virtual bool projectSignal(int atX, int atY, gcgDISCRETE2D<float> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef) = 0;
  virtual bool projectSignal(int atX, int atY, gcgDISCRETE2D<double> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef) = 0;
  virtual bool projectSignal(int atX, int atY, gcgDISCRETE2D<short> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef) = 0;
  virtual bool projectSignal(int atX, int atY, gcgDISCRETE2D<int> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef) = 0;
  virtual bool projectSignal(int atX, int atY, gcgDISCRETE2D<long> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef) = 0;

  /// @brief Computes the components of a 2D vector, using the getNumberofCoefficients() coefficients given in array
  /// \a inputcoef (as 1D signal). The components are stored in the 2D signal \a outputvector starting at position
  /// (\a atX, \a atY).
  /// @param[in] atX origin X coordinate of the signal for this projection (relative to \a outputvector).
  /// @param[in] atY origin Y coordinate of the signal for this projection (relative to \a outputvector).
  /// @param[in] inputcoef array of coefficients (as 1D signal) representing the vector to be reconstructed.
  /// @param[out] outputvector array (as 2D signal) that receives the reconstructed samples starting at position (\a atX, \a atY).
  /// @return true if reconstruction is successful.
  /// @see getNumberOfCoefficients()
  /// @see projectSignal()
  /// @see gcgDISCRETE1D()
  /// @see gcgDISCRETE2D()
  virtual bool reconstructSignal(int atX, int atY, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE2D<float> *outputvector) = 0;
  virtual bool reconstructSignal(int atX, int atY, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE2D<double> *outputvector) = 0;
  virtual bool reconstructSignal(int atX, int atY, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE2D<short> *outputvector) = 0;
  virtual bool reconstructSignal(int atX, int atY, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE2D<int> *outputvector) = 0;
  virtual bool reconstructSignal(int atX, int atY, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE2D<long> *outputvector) = 0;
};

template<class NUMTYPE> class    GCG_API_CLASS    gcgLEGENDREBASIS1D;
template<class NUMTYPE> class    GCG_API_CLASS    gcgLEGENDREBASIS2D;
template<class NUMTYPE> class    GCG_API_CLASS    gcgDWTBASIS1D;

///@}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////     IMAGE macros, classes, and functions /////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// @defgroup rgbaimage Image processing (RGBA)
/// This section presents functions and classes processing images having the RGBA color format.
///@{
/// @ingroup graphics


//////////////////////////////////////////////////////////////////////////////
/// @brief Class for handling images with up to 32 bits per pixel and up to 4
/// channels.
///
/// The gcgIMAGE class encapsulates all funcionalities for handling images with up to 4 channels,
/// tipically representing Red, Green, Blue, and Alpha (opacity) information (RGBA). The forth channel can also
/// represent the exponent value on HDR images (RGBE). With \a bpp (bits per pixel) up to 8, the image has a palette
/// that stores the current image colors. The palette might not have all possible colors. For instance, a 8 \a bpp image can
/// have only 25 colors on the palette. Check \a palettecolors attribute to know how many colors are actually used. The gcgIMAGE::data
/// field points to a bitmap of indices related to the palette. Images with 24 bpp are treated always as 8 bit channels (1 byte) for red,
/// green and blue, stored in that order (color masks are not used). For images with 16 or 32 \a bpp, the masks defining which bits belong
/// to which channel can be freely adjusted. In both cases the actual image pixels are stored in gcgIMAGE::data. Whatever the \a bpp,
/// the image rows are 4 aligned to enhance memory access. The actual rowsize in bytes is given by the \a rowsize attribute. Use it
/// to direct access rows, regarding that the last image row appears first in the gcgIMAGE::data buffer (address zero). The bits are
/// stored in RGBA order, according to the four channel color masks \a colormasks. Most methods can receive the destiny image as a
/// parameter. The methods copy and handle all needed information to keep the image consistent. The gcgIMAGE currently supports up to
/// 8 bits per channel in the bitmap and exactly 8 bits per pixel in palettes. Do not change any of the image attributes unless you
/// are absolutely sure about you are doing.
///
/// @since 0.01.0
///
//////////////////////////////////////////////////////////////////////////////

class    GCG_API_CLASS    gcgIMAGE   :  public gcgCLASS {
  public:
    unsigned char  *data;         ///< Image data where each pixel may be an index (1, 2, 4 and 8 \a bpp) or the actual color.
    unsigned int   width;         ///< Image size in number of pixels.
    unsigned int   height;        ///< Image height in number of pixels.
    unsigned int   bpp;           ///< Bits per pixel that can assume the values: 1, 2, 4, 8, 16, 24, 32
    unsigned int   rowsize;       ///< Stride in bytes between one row and the next. The last image row appears first in the data buffer.

    unsigned int   palettecolors; ///< Actual number of colors in the palette. It might be less than the maximum number of colors of a given \a bpp.
    unsigned char  *palette;      ///< If it is non-null, the gcgIMAGE::data elements are indices to a color stored in this table. Each color in
                                  ///< this array is 4 byte long and stores the RGB plus the another channel (alpha or exponent).

    unsigned int    colormasks[4];///< Masks indicating color bits for the channels red, green, blue and alpha for 16 bpp and 32 bpp images.
    unsigned int    max[4];       ///< Maximum decimal value of each channel mask: Red = 0, Green = 1, Blue = 2, Alpha = 3. It depends on \a colormasks.

  private:
    unsigned int    rightshift[4];///< Required right shift to bring each channel bits to the least significant bit.
    unsigned int    nbits[4];     ///< Number of bits of each channel mask.

  public:
    /// @brief Constructs a valid but empty image. The image can be used as destiny image in any gcgIMAGE method or GCGlib function.
    /// @see ~gcgIMAGE()
    gcgIMAGE();

    /// @brief Releases all image resources by calling destroyImage().
    /// @see gcgIMAGE()
    /// @see destroyImage()
    virtual ~gcgIMAGE();

    /// @brief Image creation. Alocates all necessary space for the image indicated by the parameters. Sets all indices (if \a bpp < 16)
    /// or colors (if \a bpp >= 16) with zero values. If \a bpp < 16, it creates and sets a gray scale palette.
    /// @param[in] width image width. It must be non-zero.
    /// @param[in] height image height. It must be non-zero.
    /// @param[in] bpp bits per pixel. It must be one of the list: 1, 2, 4, 8, 16, 24 or 32. If \a bpp < 16, a paletted image is created.
    /// The palette is initiated with gray scale colors. If \a bpp is 24, an image with 8 bits for red, green and blue channels is
    /// created and the color masks are ignored. If the alpha/exponent channel is not used (see \a usealpha), a 16 bpp image has by default
    /// 5 bits for blue, 6 bits for green and 5 bits for red, in that order from the least significant bits (unsigned short) to the most.
    /// Also, if \a bpp is 32, 8 bits for blue, green and red channels are used by default, in that order, from the second most siginificant
    /// byte (unsigned int) to the least. The most significant byte is unused. More than 8 bits per pixel are not supported.
    /// @param[in] usealpha flags if the image uses the forth channel for alpha (opacity) or exponent values. Note that paletted images
    /// (\a bpp < 16) has always the the 8 bits alpha/exponent channel stored for each color entry in the table. Also 24 \a bpp images can
    /// not have alpha bits. Thus, the \a usealpha parameter only affects 16 or 32 bits per pixel images. If false, see the bitmask
    /// distribution in \a bpp parameter. If it is true, the image is created with some of the color bits for alpha/exponent
    /// channel. If \a bpp is 16, then the image is created by default with 4 bits for blue, green, red and alpha channels, in that order
    /// from the least significant bits (unsigned short) to the most. If \a bpp is 32, 8 bits for alpha, blue, green and red channels are
    /// used by default, in that order, from the most siginificant byte (unsigned int) to the least.
    /// @return true if the image is correctly created. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createSimilar()
    /// @see duplicateImage()
    /// @see duplicateSubimage()
    /// @see copyImage()
    /// @see destroyImage()
    bool createImage(unsigned int width, unsigned int height, unsigned int bpp, bool usealpha = false);


    /// @brief Creates an image with the same dimensions, bits per pixel, color masks and palette of a source image. Only palette data,
    /// if used, is copied to the current image. This is useful for creating temporary images compatible with the source.
    /// @param[in] source pointer to the source image. It must be non-null. A warning is issued if it is not a valid image. The destiny
    /// image receives all attributes of the source image: dimensions, bits per pixel, color masks and palette. The gcgIMAGE::data is
    /// allocated but not copied.
    /// @return true if the current image is correctly created and similar to the \a source image. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createImage()
    /// @see duplicateImage()
    /// @see duplicateSubimage()
    /// @see copyImage()
    /// @see destroyImage()
    /// @see isCompatibleWith()
    bool createSimilar(gcgIMAGE *source);

    /// @brief Releases all resources used by the image. After destroyed, the image becomes invalid and must be recreated.
    /// @return true if the image was released. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createImage()
    /// @see duplicateImage()
    /// @see duplicateSubimage()
    /// @see copyImage()
    /// @see createSimilar()
    bool destroyImage();

    /// @brief Checks if both images are compatible: same dimensions, same bits per pixel, same masks, same palette. But not necessarily
    /// the same pixel data.
    /// @param[in] source pointer to the source image to be compared with. It must be non-null. A warning is issued if it is not a
    /// valid image.
    /// @return true if \a source is compatible with the current image.
    /// @see copyImage()
    /// @see createSimilar()
    /// @see isValid()
    bool isCompatibleWith(gcgIMAGE *source);

    /// @brief Checks if the current image is valid: dimensions are non-zero, pixel data is allocated and bits per pixel is 1, 2, 4,
    /// 8, 16, 24 or 32. If the image has a palette, checks if it is allocated.
    /// @return true if the current image is valid and can be used by any GCGlib method or function.
    /// @see createImage()
    /// @see createSimilar()
    /// @see duplicateImage()
    /// @see duplicateSubimage()
    /// @see copyImage()
    /// @see destroyImage()
    bool isValid();

    /// @brief Makes an independent copy of the \a source image. Creates an image similar to the \a source image and copies all of
    /// its contents. The duplicata is stored in this image, whose previous data is destroyed. The destination (this) and the
    /// \a source can be the same object.
    /// @param[in] source pointer to the source image. It must be non-null. A warning is issued if it is not a valid image. The destiny
    /// image receives all attributes of the source image: dimensions, bits per pixel, color masks, palette, and pixel data. The source
    /// can be the destination.
    /// @return true if the image is a duplication of \a source. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createImage()
    /// @see createSimilar()
    /// @see duplicateSubimage()
    /// @see copyImage()
    /// @see destroyImage()
    /// @see isCompatibleWith()
    bool duplicateImage(gcgIMAGE *source);

    /// @brief Makes an independent copy of a subregion of the \a source image. Creates an image to the \a
    /// source image but with different size and copies the pixel data of its subregion. The result is stored in this image,
    /// whose previous data is destroyed. The destination (this) and the \a source can be the same object.
    /// @param[in] source pointer to the source image. It must be non-null. A warning is issued if it is not a valid image.
    /// The destiny image receives all attributes of the source image: bits per pixel, color masks and palette. The dimensions
    /// has the subregion extents. The pixel data of the subregion is copied. The source can be the destination.
    /// @param[in] left coordinate of the left column of the subregion to be copied. It can be outside \a source image domain.
    /// @param[in] top coordinate of the top row of the subregion to be copied. It can be outside \a source image domain.
    /// @param[in] width number of columns to be copied from \a width column. It must be non-zero.
    /// @param[in] height number of rows to be copied from \a top row. It must be non-zero.
    /// @return true if the image is a duplication of a subregion of \a source. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createImage()
    /// @see createSimilar()
    /// @see duplicateImage()
    /// @see copyImage()
    /// @see destroyImage()
    /// @see isCompatibleWith()
    bool duplicateSubimage(gcgIMAGE *source, int left, int top, unsigned int width, unsigned int height);

    /// @brief Copies the pixel and palette data if the source image is equivalent to this image: same dimensions, same
    /// bits per pixel,  same masks, same number of colors in the palette. If they are not compatible this image is leaved
    /// unchanged. The destination (this) and the \a source can be the same object.
    /// @param[in] source pointer to the source image. It must be non-null. A warning is issued if it is not a valid image.
    /// The destiny image receives a copy of \a source's pixel data.
    /// @return true if the image is copied from \a source. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createImage()
    /// @see createSimilar()
    /// @see duplicateSubimage()
    /// @see duplicateImage()
    /// @see destroyImage()
    /// @see isCompatibleWith()
    bool copyImage(gcgIMAGE *source);

    /// @brief Loads a file image based on its extension. If the file extension does not match .tga, .bmp, .pcx, .jpg or .jpeg, an
    /// error is issued.
    /// @param[in] filename pointer to a string representing the file name. It must be non-null.
    /// @return true if the image is succesfully loaded. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see loadJPG()
    /// @see loadBMP()
    /// @see loadPCX()
    /// @see loadTGA()
   	bool loadImage(const char *filename);

    /// @brief Loads a file image in JPEG format. This function uses the Independent JPEG Group Library.
    /// @param[in] filename pointer to a string representing the file name. It must be non-null.
    /// @return true if the image is succesfully loaded. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see loadImage()
    /// @see loadBMP()
    /// @see loadPCX()
    /// @see loadTGA()
    bool loadJPG(const char *filename);

    /// @brief Loads a file image in BMP format.
    /// @param[in] filename pointer to a string representing the file name. It must be non-null.
    /// @return true if the image is succesfully loaded. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see loadJPG()
    /// @see loadImage()
    /// @see loadPCX()
    /// @see loadTGA()
    bool loadBMP(const char *filename);

    /// @brief Loads a file image in PCX format, paletted with 256 colors.
    /// @param[in] filename pointer to a string representing the file name. It must be non-null.
    /// @return true if the image is succesfully loaded. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see loadJPG()
    /// @see loadBMP()
    /// @see loadImage()
    /// @see loadTGA()
    bool loadPCX(const char *filename);

    /// @brief Loads a file image in TGA format.
    /// @param[in] filename pointer to a string representing the file name. It must be non-null.
    /// @return true if the image is succesfully loaded. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see loadJPG()
    /// @see loadBMP()
    /// @see loadPCX()
    /// @see loadImage()
    bool loadTGA(const char *filename);

    /// @brief Saves the image in BMP format. If the image has 8 bits per pixel, a RLE compressed version is computed and, if
    /// it is smaller than the uncompressed version, it is saved. All other versions are saved uncompressed.
    /// @param[in] filename pointer to a string representing the file name. It must be non-null.
    /// @return true if the image is succesfully saved. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see saveJPG()
    /// @see loadBMP()
    bool saveBMP(const char *filename);

    /// @brief Saves the image in JPG format. This method uses the Independent JPEG Group library. Only 24 bits RGB and
    /// gray scaled images are supported. Jpeg format does not include alpha/exponent channel. If this image has not these formats,
    /// the function automatically computes a compatible image for saving.
    /// @param[in] filename pointer to a string representing the file name. It must be non-null.
    /// @param[in] quality parameter in the range [0..100] that indicates the image quality. If closer to 0, the image is saved with
    /// poor quality but the final file size is smaller. Closer to 100 the image has high frequencies preserved but the file size tends
    /// to be bigger.
    /// @return true if the image is succesfully saved. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see saveBMP()
    /// @see loadJPG()
    bool saveJPG(const char *filename , int quality);

    /// @brief Retrieves the color of the pixel with coordinates (i, j). This method is not recommended for high performance processes
    /// since it always computes the pixel address and normalizes the color values. Access gcgIMAGE::data directly whenever possible.
    /// If the image has a palette, it calls getPixelIndex() and getPaletteColor() to retrieve the color, which is much slower.
    /// Note that gcgIMAGE currently supports up to 8 bits per channel.
    /// @param[in] i column coordinate of the pixel. It must be in the range [0, width-1].
    /// @param[in] j row coordinate of the pixel. It must be in the range [0, height-1].
    /// @param[out] color pointer to an array of 4 floats that will receive the pixel color in RGBA order. The values are normalized
    /// between 0.0 (no intensity) and 1.0 (maximum intensity). If the image has not the Alpha/Exponent channel, the forth float is
    /// ignored.
    /// @return true if the color is successfully retrieved. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setPixelColor()
    /// @see getPixelIndex()
    /// @see getPaletteColor()
    bool getPixelColor(unsigned int i, unsigned int j, VECTOR4 color);

    /// @brief Sets the color of the pixel with coordinates (i, j). This method is not recommended for high performance processes
    /// since it always computes the pixel address and converts the color values. Access gcgIMAGE::data directly whenever possible.
    /// If the image has a palette, it finds the color in the palette closest (squared euclidian distance) to \a color and then calls
    /// setPixelIndex() to set the color, which is considerably slow. Note that gcgIMAGE currently supports up to 8 bits per channel.
    /// @param[in] i column coordinate of the target pixel. It must be in the range [0, width-1].
    /// @param[in] j row coordinate of the target pixel. It must be in the range [0, height-1].
    /// @param[in] color pointer to an array of 4 floats having the pixel color in RGBA order. The values must be normalized
    /// between 0.0 (minimum intensity) and 1.0 (maximum intensity). If the image has not the Alpha/Exponent channel, the forth float is
    /// ignored.
    /// @return true if the color is successfully stored. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see getPixelColor()
    /// @see setPixelIndex()
    /// @see setPaletteColor()
    bool setPixelColor(unsigned int i, unsigned int j, VECTOR4 color);

    /// @brief Gets the palette index of the pixel with coordinates (i, j), in the range [0, \a palettecolors - 1]. Generally,
    /// \a palettecolors = (2 powered to \a bpp) - 1. This method is valid only for paletted images, i.e. bits per pixel <= 8.
    /// @param[in] i column coordinate of the pixel. It must be in the range [0, width-1].
    /// @param[in] j row coordinate of the pixel. It must be in the range [0, height-1].
    /// @return if positive or zero, it is the color index at position (i, j). If negative, the operation has failed. Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setPixelIndex()
    /// @see forceLinearPalette()
    int getPixelIndex(unsigned int i, unsigned int j);

    /// @brief Sets the palette index of the pixel with coordinates (i, j), in the range [0, \a palettecolors - 1]. This method is valid
    /// only for paletted images, i.e. bits per pixel <= 8.
    /// @param[in] i column coordinate of the pixel. It must be in the range [0, width-1].
    /// @param[in] j row coordinate of the pixel. It must be in the range [0, height-1].
    /// @param[in] newindex new palette index of the pixel. It must be in the range [0, \a palettecolors]. Generally, \a palettecolors = (2 powered to \a bpp) - 1.
    /// @return true if the index is successfully stored. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see getPixelIndex()
    /// @see forceLinearPalette()
    bool setPixelIndex(unsigned int i, unsigned int j, int newindex);

    /// @brief Gets the RGBA color stored in the position \a index of the palette, in the range [0, \a palettecolors - 1]. Generally,
    /// \a palettecolors = (2 powered to \a bpp) - 1. This method is valid only for paletted images, i.e. bits per pixel <= 8.
    /// Note that gcgIMAGE currently allocates 8 bits for each channel in the palette.
    /// @param[in] index position in the palette. It must be in the range [0, \a palettecolors - 1].
    /// @param[out] color pointer to an array of 4 floats that will receive the color in RGBA order. The values are normalized
    /// between 0.0 (no intensity) and 1.0 (maximum intensity). Paletted colors always have an Alpha/Exponent value that is returned
    /// in the forth float.
    /// @return true if the color is successfully retrieved. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setPaletteColor()
    bool getPaletteColor(int index, VECTOR4 color);

    /// @brief Sets the RGBA color in the position \a index of the palette, in the range [0, \a palettecolors - 1]. Generally,
    /// \a palettecolors = (2 powered to \a bpp) - 1. This method is valid only for paletted images, i.e. bits per pixel <= 8.
    /// Note that gcgIMAGE currently allocates 8 bits for each channel in the palette.
    /// @param[in] index position in the palette. It must be in the range [0, \a palettecolors - 1].
    /// @param[in] color pointer to an array of 4 floats having the pixel color in RGBA order. The values must be normalized
    /// between 0.0 (minimum intensity) and 1.0 (maximum intensity). Paletted colors always have an Alpha/Exponent value that is
    /// returned in the forth float.
    /// @return true if the color is successfully stored. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see getPaletteColor()
    bool setPaletteColor(int index, VECTOR4 color);

    /// @brief Computes the convolution product of an unidimensional floating point mask \a mask with each row (left to right) of source image
    /// \a source. The result is stored in this image, whose previous data is destroyed. The destination (this) and the \a source can be the same
    /// object. Generally, the mask elements are given in the interval [0.0, 1.0]. Each convolved value, one per pixel, is clamped to be
    /// between 0.0 (minimum intensity) and 1.0 (maximum intensity). Use the \a addthis parameter to displace convolutions that might
    /// result in negative values (high pass for example) or values greater than one. All image channels are convolved with mask.
    /// If the \a source image is gray scaled, forceLinearPalette() is called for it, and the convolution is computed with the indices
    /// stored in the bitmap. If the \a source image is paletted but is not gray scaled (i.e. RGBA), the convolutions results in a 32
    /// bits image, since it is not possible to directly filter paletted color images.
    /// @param[in] source image that will have each row convolved with \a mask. The rows are symmetrically extended on their borders.
    /// @param[in] mask floating point discrete signal that will be convolved with the \a source image. The origin attribute of the mask is used.
    /// @param[in] addthis floating point number that must be added to the convolved values BEFORE being converted to a decimal number
    /// to be written in the bitmap. Use this term when the convolution might result in negative values or values greater than one. For
    /// example, when applying a high pass filter, which naturally yields negative values, set \a addthis = 0.5. This will shift the -0.5
    /// values (-127 is mapped to 0, for 8 bits) to 0.0, the 0.0 values to 0.5 (0 is mapped to 127, for 8 bits) and the 0.5 value to 1.0
    /// (128 is mapped to 255, for 8 bits).
    /// @return true if the row convolutions are successfully computed. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see convolutionY()
    /// @see convolutionXY()
    /// @see gcgDISCRETE1D<float>
    bool convolutionX(gcgIMAGE *source, gcgDISCRETE1D<float> *mask, float addthis = 0);

    /// @brief Computes the convolution product of an undimensional floating point mask \a mask with each column (bottom to top) of source image
    /// \a source. The result is stored in this image, whose previous data is destroyed. The destination (this) and the \a source can be the same object.
    /// Generally, the mask elements are given in the interval [0.0, 1.0]. Each convolved value, one per pixel, is clamped to be
    /// between 0.0 (minimum intensity) and 1.0 (maximum intensity). Use the \a addthis parameter to displace convolutions that might
    /// result in negative values (high pass for example) or values greater than one. All image channels are convolved with mask.
    /// If the \a source image is gray scaled, forceLinearPalette() is called for it, and the convolution is computed with the indices
    /// stored in the bitmap. If the \a source image is paletted but is not gray scaled (i.e. RGBA), the convolution results in a 32
    /// bits image, since it is not possible to directly filter paletted color images.
    /// @param[in] source image that will have each column convolved with \a mask. The columns are symmetrically extended on their borders.
    /// @param[in] mask floating point discrete signal that will be convolved with the \a source image. The origin attribute of the mask is used.
    /// @param[in] addthis floating point number that must be added to the convolved values BEFORE being converted to a decimal number
    /// to be written in the bitmap. Use this term when the convolution might result in negative values or values greater than one. For
    /// example, when applying a high pass filter, which naturally yields negative values, set \a addthis = 0.5. This will shift the -0.5
    /// values (-127 is mapped to 0, for 8 bits) to 0.0, the 0.0 values to 0.5 (0 is mapped to 127, for 8 bits) and the 0.5 value to 1.0
    /// (128 is mapped to 255, for 8 bits).
    /// @return true if the column convolutions are successfully computed. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see convolutionX()
    /// @see convolutionXY()
    /// @see gcgDISCRETE1D<float>
    bool convolutionY(gcgIMAGE *source, gcgDISCRETE1D<float> *mask, float addthis = 0);

    /// @brief Computes the convolution product of a bidimensional floating point mask \a mask with the source image \a source. The
    /// result is stored in this image, whose previous data is destroyed. The destination (this) and the \a source can be the same object.
    /// Generally, the mask elements are given in the interval [0.0, 1.0]. Each convolved value, one per pixel, is clamped to be
    /// between 0.0 (minimum intensity) and 1.0 (maximum intensity). Use the \a addthis parameter to displace convolutions that might
    /// result in negative values (high pass for example) or values greater than one. All image channels are convolved with mask.
    /// If the \a source image is gray scaled, forceLinearPalette() is called for it, and the convolution is computed with the indices
    /// stored in the bitmap. If the \a source image is paletted but is not gray scaled (i.e. RGBA), the convolution results in a 32
    /// bits image, since it is not possible to directly filter paletted color images. This function is highly computation expensive.
    /// Use it ONLY when the 2D filter is not separable. In that case, the use an application of convolutionX() followed by
    /// convolutionY() is preferable and much faster.
    /// @param[in] source image that will be convolved with \a mask. The columns are symmetrically extended on their borders.
    /// @param[in] mask floating point discrete signal that will be convolved with the \a source image. The origin attribute of the mask is used.
    /// @param[in] addthis floating point number that must be added to the convolved values BEFORE being converted to a decimal number
    /// to be written in the bitmap. Use this term when the convolution might result in negative values or values greater than one. For
    /// example, when applying a high pass filter, which naturally yields negative values, set \a addthis = 0.5. This will shift the -0.5
    /// values (-127 is mapped to 0, for 8 bits) to 0.0, the 0.0 values to 0.5 (0 is mapped to 127, for 8 bits) and the 0.5 value to 1.0
    /// (128 is mapped to 255, for 8 bits).
    /// @return true if the 2D convolution is successfully computed. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see convolutionX()
    /// @see convolutionY()
    /// @see gcgDISCRETE2D<float>
    bool convolutionXY(gcgIMAGE *source, gcgDISCRETE2D<float> *mask, float addthis = 0);

    /// @brief Finds the pixel coordinates (x, y) that gives the greatest Sum of Absolute Differences (SAD) with the
    /// alignment of the bidimensional \a mask and the image's pixels. The \a mask is called the template which has to be discovered
    /// in the current image. It is represented by an gcgDISCRETE2D<float> object normaly having points with
    /// values between 0.0 and 1.0. Each color of the image is a RGB triple with channel values normalized between 0.0 and 1.0. The
    /// origin of \a mask is aligned with all points inside the region defined starting at (\a imgleft, \a imgbottom), with \a imgwidth
    /// by \a imgheight pixels, and the sum of absolute differences are computed for all color channels. The total sum of absolute
    /// differences is the sum of the result of all channels. The pixel coordinate with greatest total sum is returned in \a position.
    /// If the \a source image is paletted and gray scaled, forceLinearPalette() is called for it, and the sum of absolute differences is
    /// computed with the indices stored in the bitmap. In all other configurations the actual RGB values of the pixels are used in the
    /// computation. This function is highly computation expensive. Try to reduce the search space by setting properly the
    /// \a imgleft, \a imgbottom, \a imgwidth and \a imgheight parameters.
    /// @param[in] imgleft left column of the region to search the pixel with greatest Sum of Absolute Differences.
    /// @param[in] imgbottom bottom row of the region to search the pixel with greatest Sum of Absolute Differences.
    /// @param[in] imgwidth width of the region to search the pixel with greatest Sum of Absolute Differences.
    /// @param[in] imgheight height of the region to search the pixel with greatest Sum of Absolute Differences.
    /// @param[in] mask floating point bidimensional signal that represents the template to be found in the current image. Generally the
    /// values of \a mask are between 0.0 and 1.0. The origin attribute of the mask is used for aligment with the pixels.
    /// @param[out] position pointer to an array of two floats that will receive the pixel coordinates that, aligned with the \a mask's
    /// origin, gives the greatest Sum of Absolute Differences (SAD).
    /// @return true if the template was successfully matched with a subimage of the current image. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see gcgDISCRETE2D<float>
    bool templateMatching(unsigned int imgleft, unsigned int imgbottom, unsigned int imgwidth, unsigned int imgheight, gcgDISCRETE2D<float> *mask, VECTOR2 position);

    /// @brief Applies the linear tranformation defined by a 4 x 4 matrix in all image colors. It is called a color space transform.
    /// Each image pixel has a color vector [R G B A] composed by the red, green, blue and alpha values, normalized between 0.0 (darker)
    /// and 1.0 (brigher). This method computes the matrix-vector multiplication [R' G' B' A'] = \a matrix * [R G B A]. The resulting
    /// color components [R' G' B' A'] are clamped between 0.0 and 1.0 and stored in the image bits. If the image has no alpha/exponent
    /// channel defined, the last column and the last row of the matrix must be 0 to avoid errors. If this is not the case, the resulting
    /// color is undefined. For 24 bits images, the last column is ignored (alpha component is set to zero: A = 0) and the last row is
    /// ignored (A' is not computed). The result is stored in this image, whose previous data is destroyed. The destination (this) and the
    /// \a source can be the same object. It is useful in color calibration processes.
    /// @param[in] source image that will have each color tranformed by \a matrix.
    /// @param[in] matrix pointer to an array of 16 floats representing a matrix of 4 x 4 elements. First 4 elements form the row
    /// 1, and so on.
    /// @return true if the color space is successfully transformed. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    bool transformColorSpace(gcgIMAGE *source, MATRIX4 matrix);

    /// @brief Computes an equivalent image of \a source but with a different number of bits per pixel. The result is stored in this image,
    /// whose previous data is destroyed. The destination (this) and the \a source can be the same object. Currently, the following
    /// conversions are supported: [1, 2 or 4 bits] to [8 bits]: paletted images to a palette with 256 colors; [1, 2, 4 or 8 bits] to
    /// [24 bits]: paletted images to 24 bits with 8 bits per channel, where the alpha values in palette colors are discarded; [16 bits]
    /// to [24 bits]: 16 bits with arbitrary masks to 24 bits with 8 bits per channel, where the alpha values (if its mask is non zero)
    /// are discarded; [16 bits] to [32 bits]: 16 bits with arbitrary masks to 32 bits with 8 bits per channel, where the alpha values
    /// (if its mask is non zero) are copied to the corresponding 8 bit channel; [32 bits] to [24 bits]: 32 bits with 8 bits per channel
    /// to 24 bits with 8 bits per channel, where the alpha value is discarded.
    /// @param[in] source image whose bits per pixel should be converted to \a newbpp and stored in this image. It may be the destination (this).
    /// @param[in] newbpp new bits per pixel that the destination image must have.
    /// @return true if the image with new bits per pixel is successfully computed. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see convertGrayScale()
    /// @see convertGrayScale8bits()
    bool convertBits(gcgIMAGE *source, unsigned int newbpp);

    /// @brief Computes a gray scaled version of \a source, keeping its number of bits per pixel. The result is stored in this image,
    /// whose previous data is destroyed. The destination (this) and the \a source can be the same object. If the \a source has
    /// 1, 2, 4 or 8 bits per pixel, the palette RGB colors are converted to gray scale and the indices of the bitmap are forced to be
    /// linear through a call to forceLinearPalette(). In any other \a bpp, the actual RGB color bits are forced to be gray by a simple
    /// arithmetic average between their original values. In all cases, the alpha/exponent values (if present) are just copied.
    /// @param[in] source image that should be converted to a gray scaled version and stored in this image, keeping the original number of
    /// bits per pixel. It may be the destination (this).
    /// @return true if the gray scaled image is successfully computed. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see convertGrayScale8bits()
    /// @see convertBits()
    /// @see isGrayScale()
    /// @see forceLinearPalette()
    bool convertGrayScale(gcgIMAGE *source);

    /// @brief Computes a gray scaled version of \a source, but with 8 bits per pixel. The result is stored in this image,
    /// whose previous data is destroyed. The destination (this) and the \a source can be the same object. The resulting image has
    /// a linear palette varying uniformly from index 0 (black) to index 255 (white). In all cases, the alpha/exponent values
    /// are ignored in the computation and discarded since they generally cannot be mapped to the palette.
    /// @param[in] source image that should be converted to a gray scaled version and stored in this image, keeping the original
    /// number of bits per pixel. It may be the destination (this).
    /// @return true if the gray scaled image with 8 bits is successfully computed. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see convertGrayScale()
    /// @see convertBits()
    /// @see isGrayScale()
    /// @see forceLinearPalette()
    bool convertGrayScale8bits(gcgIMAGE *source);

    /// @brief Checks if the image has only gray scaled colors. If the image is paletted, the palette colors are first checked. If the
    /// palette has colors which are not gray, then all indices and corresponding colors are checked. This means that a gray scaled
    /// image might have a palette with non gray colors. If the image is not paletted, all bitmap values are verified. A color is a
    /// gray tone if R = G = B. The alpha/exponent channel, if present, is ignored.
    /// @return true if the image has only gray colors. It also returns false If the current image is not valid, check GCG_REPORT_MESSAGE(gcgGetReport())
    /// for errors.
    /// @see convertGrayScale()
    /// @see convertBits()
    /// @see convertGrayScale8bits()
    /// @see forceLinearPalette()
    bool isGrayScale();

    /// @brief Classify the palette colors in ascending order of the sum R+G+B. The bitmap indices are adjusted accordingly.
    /// The resulting image has indices that correspond directly to the average intensity of the palette color. As a result,
    /// the bitmap indices can be used directly in several image processing tasks, notably if the image is gray scaled. The original
    /// alpha/exponent values are preserved. This function does not check if palette colors are duplicated.
    /// @return true if the image has been converted to a version with linear palette. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see isGrayScale()
    /// @see convertGrayScale()
    /// @see convertBits()
    /// @see convertGrayScale8bits()
    bool forceLinearPalette();

    /// @brief Scales a source image \a source and stores the result in the current object, whose previous data is destroyed. The
    /// destination (this) and the \a source can be the same object. Each pixel component of the \a source, in the [0, 1] range,  is
    /// multiplied by \a weight and then summed to \a addthis (\a weight * value + \a addthis). The result, one per RGBA component,
    /// is clamped to be between 0.0 (minimum intensity) and 1.0 (maximum intensity) and stored in this image. Use the \a addthis
    /// parameter to displace scalings that might result in negative values or values greater than one. All image channels are scaled.
    /// If the \a source image is gray scaled, forceLinearPalette() is called for it, and the scaling is computed with the indices
    /// stored in the bitmap. If the \a source image is paletted but is not gray scaled, the convolution results in a 32 bits image.
    /// @param[in] weight scalar value to multiply each color channel.
    /// @param[in] source image that will have each pixel color scaled by the formula I = \a weight * \a color  + \a addthis.
    /// @param[in] addthis floating point number that must be added to the scale values BEFORE being converted to a decimal number
    /// to be written in the bitmap. Use this term when the scaling might result in negative values or values greater than one. For
    /// example, when scaling with a negative \a weight, yielding negative values, set \a addthis = 0.5. This will shift the -0.5
    /// values (-127 is mapped to 0, for 8 bits) to 0.0, the 0.0 values to 0.5 (0 is mapped to 127, for 8 bits) and the 0.5 value to 1.0
    /// (128 is mapped to 255, for 8 bits).
    /// @return true if the scaling is successfully computed. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for
    /// knowing the problem.
    /// @see combineAdd()
    /// @see combineMult()
    bool scale(float weight, gcgIMAGE *source, float addthis = 0.0);

    /// @brief Combines two source images \a source1 and \a source2 by addition. Stores the result in the current object, whose previous
    /// data is destroyed. The destination (this) and any source image (\a source1 and \a source2) can be the same object. \a source1
    /// and \a source2 must be compatible (see gcgIMAGE::isCompatibleWith()). For a given image position, each RGBA component of \a
    /// source1, in the [0, 1] range, is multiplied by \a weight1 and its corresponding component in \a source2, also in the [0, 1]
    /// range, is multiplied by \a weight2, and the two results are summed. It is then added to \a addthis (\a weight1 * value1  +
    /// \a weight2 * value2 + addthis). The result, one per RGBA component, is clamped to be between 0.0 (minimum intensity) and 1.0
    /// (maximum intensity) and stored in this image. Use the \a addthis parameter to displace combinations that might result in negative
    /// values or values greater than one. All image channels are combined. If the \a source image is gray scaled, forceLinearPalette()
    /// is called for it, and the combination is computed with the indices stored in the bitmap. If the \a source image is paletted but
    /// is not gray scaled, the convolution results in a 32 bits image, since it is not possible to directly combine paletted color images.
    /// @param[in] source1 first image to be combined by addition. It may be the destination (this).
    /// @param[in] source2 second image to be combined by addition. It may be the destination (this).
    /// @param[in] weight1 scalar value to multiply each color channel of the first image \a source1.
    /// @param[in] weight2 scalar value to multiply each color channel of the second image \a source2.
    /// @param[in] addthis floating point number that must be added to the combined values BEFORE being converted to a decimal number
    /// to be written in the bitmap. Use this term when the combination might result in negative values or values greater than one. For
    /// example, when the combination might yield negative values, set \a addthis = 0.5. This will shift the -0.5 values (-127 is mapped
    /// to 0, for 8 bits) to 0.0, the 0.0 values to 0.5 (0 is mapped to 127, for 8 bits) and the 0.5 value to 1.0
    /// (128 is mapped to 255, for 8 bits).
    /// @return true if the combination by addition is successfully computed. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for
    /// knowing the problem.
    /// @see scale()
    /// @see combineMult()
    bool combineAdd(gcgIMAGE *source1, gcgIMAGE *source2, float weight1 = 1.0, float weight2 = 1.0, float addthis = 0.0);

    /// @brief Combines two source images \a source1 and \a source2 by multiplication. Stores the result in the current object, whose
    /// previous data is destroyed. The destination (this) and any source image (\a source1 and \a source2) can be the same object.
    /// \a source1 and \a source2 must be compatible (see gcgIMAGE::isCompatibleWith()). For a given image position, each RGBA component
    /// of \a source1, in the [0, 1] range, is added to \a add1 and its corresponding component in \a source2, also in the [0, 1]
    /// range, is added to \a add2, and the two results are multiplied. It is then added to \a addthis (\a (add1 + value1) *
    /// (\a add2 * value2) + addthis). The result, one per RGBA component, is clamped to be between 0.0 (minimum intensity) and 1.0
    /// (maximum intensity) and stored in this image. Use the \a addthis parameter to displace combinations that might result in
    /// negative values or values greater than one. All image channels are combined. If the \a source image is gray scaled,
    /// forceLinearPalette() is called for it, and the combination is computed with the indices stored in the bitmap. If the \a source
    /// image is paletted but is not gray scaled, the convolution results in a 32 bits image, since it is not possible to directly
    /// combine paletted color images.
    /// @param[in] source1 first image to be combined by multiplication. It may be the destination (this).
    /// @param[in] source2 second image to be combined by multiplication. It may be the destination (this).
    /// @param[in] add1 scalar value to be added to each color channel of the first image \a source1.
    /// @param[in] add2 scalar value to be added to each color channel of the second image \a source2.
    /// @param[in] addthis floating point number that must be added to the combined values BEFORE being converted to a decimal number
    /// to be written in the bitmap. Use this term when the combination might result in negative values or values greater than one. For
    /// example, when the combination might yield negative values, set \a addthis = 0.5. This will shift the -0.5 values (-127 is mapped
    /// to 0, for 8 bits) to 0.0, the 0.0 values to 0.5 (0 is mapped to 127, for 8 bits) and the 0.5 value to 1.0
    /// (128 is mapped to 255, for 8 bits).
    /// @return true if the combination by multiplication is successfully computed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see scale()
    /// @see combineAdd()
    bool combineMult(gcgIMAGE *source1, gcgIMAGE *source2, float add1 = 0.0, float add2 = 0.0, float addthis = 0.0);

    /// @brief Copies the color channels of the current image into distinct gray scaled images. The destination images (\a red, \a green,
    /// \a blue, \a alpha) must not be the source (this). Any destination can be NULL, indicating that a channel is not to be copied.
    /// The output are 8 bits per pixel, gray scaled images, with the same dimensions of the source. The original component values
    /// of the current image are converted and scaled to the [0, 255] range. All output images have linear palettes which means that
    /// the original channel value match their indices.
    /// @param[out] red pointer to a gcgIMAGE that will receive the red component of the current image. If it is NULL, the red channel
    /// is ignored. It must not be this image.
    /// @param[out] green pointer to a gcgIMAGE that will receive the green component of the current image. If it is NULL, the green channel
    /// is ignored. It must not be this image.
    /// @param[out] blue pointer to a gcgIMAGE that will receive the blue component of the current image. If it is NULL, the blue channel
    /// is ignored. It must not be this image.
    /// @param[out] alpha pointer to a gcgIMAGE that will receive the alpha component of the current image. If it is NULL, the alpha channel
    /// is ignored. It must not be this image.
    /// @return true if the selected channels (non-null gcgIMAGE pointers) are copied to the respective images. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see mergeChannels()
    bool splitChannels(gcgIMAGE *red, gcgIMAGE *green, gcgIMAGE *blue, gcgIMAGE *alpha = NULL);

    /// @brief Merges the distinct gray scaled images into the channels of the current image. The source images (\a red, \a green,
    /// \a blue, \a alpha) must not be the source (this). All sources must be mutually compatible (see gcgIMAGE::isCompatibleWith()).
    /// Any source can be NULL, indicating that the corresponding channel will have only zeros. The destination image can have 16 or 32
    /// bits per pixel, if the \a alpha channel is provided. If it is not the case, the current image is adjusted to 32 bits per pixel.
    /// The destination image can have 16, 24 or 32 bits per pixel, if the \a alpha channel is not provided. If this is not the case, the
    /// current image is adjusted to 24 bits per pixel. In any case, the dimensions of the current image is adjusted to the sources.
    /// The source images MUST have 8 bits per pixel and be gray scaled. Their indices are assumed to be in the [0, 255] range with
    /// a linear palette (see gcgIMAGE::forceLinearPalette()), which means that their indices values match the gray level.
    /// @param[in] red pointer to a gcgIMAGE that will provide the red component to the current image. It must have 8 bits per pixel
    /// with a linear gray scaled palette. The red channel values are then obtained directly from its indices. If it is NULL, the red
    /// component of all pixels is set to zero. It must not be this image.
    /// @param[in] green pointer to a gcgIMAGE that will provide the green component to the current image. It must have 8 bits per pixel
    /// with a linear gray scaled palette. The green channel values are then obtained directly from its indices. If it is NULL, the green
    /// component of all pixels is set to zero. It must not be this image.
    /// @param[in] blue pointer to a gcgIMAGE that will provide the blue component to the current image. It must have 8 bits per pixel
    /// with a linear gray scaled palette. The blue channel values are then obtained directly from its indices. If it is NULL, the blue
    /// component of all pixels is set to zero. It must not be this image.
    /// @param[in] alpha pointer to a gcgIMAGE that will provide the alpha component to the current image. It must have 8 bits per pixel
    /// with a linear gray scaled palette. The alpha channel values are then obtained directly from its indices. If it is NULL, the alpha
    /// component of all pixels is set to zero. It must not be this image.
    /// @return true if the selected channels (non-null gcgIMAGE pointers) are merged into the current image. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see splitChannels()
    bool mergeChannels(gcgIMAGE *red, gcgIMAGE *green, gcgIMAGE *blue, gcgIMAGE *alpha = NULL);

    /// @brief Copies the color channels of the current image into distinct gcgDISCRETE2D<float> objects. The destination objects
    /// (\a red, \a green, \a blue, \a alpha) can be NULL, indicating that a channel is not to be copied. The output have the same
    /// dimensions of the current object and are composed by float values . The original component values of the current image are
    /// converted and scaled to the [0.0, 1.0] range.
    /// @param[out] red pointer to a gcgDISCRETE2D<float> object that will receive the red component of the current image. If it is NULL,
    /// the red channel is ignored.
    /// @param[out] green pointer to a gcgDISCRETE2D<float> object that will receive the green component of the current image. If it is
    /// NULL, the green channel is ignored.
    /// @param[out] blue pointer to a ggcgDISCRETE2D<float> object that will receive the blue component of the current image. If it is
    /// NULL, the blue channel is ignored.
    /// @param[out] alpha pointer to a gcgDISCRETE2D<float> object that will receive the alpha component of the current image. If it is
    /// NULL, the alpha channel is ignored.
    /// @return true if the selected channels (non-null gcgDISCRETE2D<float> pointers) are copied to the respective objects. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see importChannels()
    bool exportChannels(gcgDISCRETE2D<float> *red, gcgDISCRETE2D<float> *green, gcgDISCRETE2D<float> *blue, gcgDISCRETE2D<float> *alpha);

    /// @brief Copies the color channels of the current image into distinct gcgDISCRETE2D<double> objects. The destination objects
    /// (\a red, \a green, \a blue, \a alpha) can be NULL, indicating that a channel is not to be copied. The output have the same
    /// dimensions of the current object and are composed by double values . The original component values of the current image are
    /// converted and scaled to the [0.0, 1.0] range.
    /// @param[out] red pointer to a gcgDISCRETE2D<double> object that will receive the red component of the current image. If it is NULL,
    /// the red channel is ignored.
    /// @param[out] green pointer to a gcgDISCRETE2D<double> object that will receive the green component of the current image. If it is
    /// NULL, the green channel is ignored.
    /// @param[out] blue pointer to a ggcgDISCRETE2D<double> object that will receive the blue component of the current image. If it is
    /// NULL, the blue channel is ignored.
    /// @param[out] alpha pointer to a gcgDISCRETE2D<double> object that will receive the alpha component of the current image. If it is
    /// NULL, the alpha channel is ignored.
    /// @return true if the selected channels (non-null gcgDISCRETE2D<double> pointers) are copied to the respective objects. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see importChannels()
    bool exportChannels(gcgDISCRETE2D<double> *red, gcgDISCRETE2D<double> *green, gcgDISCRETE2D<double> *blue, gcgDISCRETE2D<double> *alpha);

    /// @brief Copies the color channels of the current image into distinct gcgDISCRETE2D<short> objects. The destination objects
    /// (\a red, \a green, \a blue, \a alpha) can be NULL, indicating that a channel is not to be copied. The output have the same
    /// dimensions of the current object and are composed by short values . The original component values of the current image are
    /// preserved in the range [0, 255] for paletted, 24 and 32 bits per pixel. The range of the component values depend on the number
    /// of bits for each channel in images with 16 bits per pixel. Use the gcgIMAGE::max attribute to know each channel range:
    /// red = [0, max[0]], green = [0, max[1]], blue = [0, max[2]], alpha = [0, max[3]].
    /// @param[out] red pointer to a gcgDISCRETE2D<short> object that will receive the red component of the current image. If it is NULL,
    /// the red channel is ignored.
    /// @param[out] green pointer to a gcgDISCRETE2D<short> object that will receive the green component of the current image. If it is
    /// NULL, the green channel is ignored.
    /// @param[out] blue pointer to a ggcgDISCRETE2D<short> object that will receive the blue component of the current image. If it is
    /// NULL, the blue channel is ignored.
    /// @param[out] alpha pointer to a gcgDISCRETE2D<short> object that will receive the alpha component of the current image. If it is
    /// NULL, the alpha channel is ignored.
    /// @return true if the selected channels (non-null gcgDISCRETE2D<short> pointers) are copied to the respective objects. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see importChannels()
    bool exportChannels(gcgDISCRETE2D<short> *red, gcgDISCRETE2D<short> *green, gcgDISCRETE2D<short> *blue, gcgDISCRETE2D<short> *alpha);

    /// @brief Copies the color channels of the current image into distinct gcgDISCRETE2D<int> objects. The destination objects
    /// (\a red, \a green, \a blue, \a alpha) can be NULL, indicating that a channel is not to be copied. The output have the same
    /// dimensions of the current object and are composed by int values . The original component values of the current image are
    /// preserved in the range [0, 255] for paletted, 24 and 32 bits per pixel. The range of the component values depend on the number
    /// of bits for each channel in images with 16 bits per pixel. Use the gcgIMAGE::max attribute to know each channel range:
    /// red = [0, max[0]], green = [0, max[1]], blue = [0, max[2]], alpha = [0, max[3]].
    /// @param[out] red pointer to a gcgDISCRETE2D<int> object that will receive the red component of the current image. If it is NULL,
    /// the red channel is ignored.
    /// @param[out] green pointer to a gcgDISCRETE2D<int> object that will receive the green component of the current image. If it is
    /// NULL, the green channel is ignored.
    /// @param[out] blue pointer to a ggcgDISCRETE2D<int> object that will receive the blue component of the current image. If it is
    /// NULL, the blue channel is ignored.
    /// @param[out] alpha pointer to a gcgDISCRETE2D<int> object that will receive the alpha component of the current image. If it is
    /// NULL, the alpha channel is ignored.
    /// @return true if the selected channels (non-null gcgDISCRETE2D<int> pointers) are copied to the respective objects. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see importChannels()
    bool exportChannels(gcgDISCRETE2D<int> *red, gcgDISCRETE2D<int> *green, gcgDISCRETE2D<int> *blue, gcgDISCRETE2D<int> *alpha);

    /// @brief Copies the color channels of the current image into distinct gcgDISCRETE2D<long> objects. The destination objects
    /// (\a red, \a green, \a blue, \a alpha) can be NULL, indicating that a channel is not to be copied. The output have the same
    /// dimensions of the current object and are composed by long values . The original component values of the current image are
    /// preserved in the range [0, 255] for paletted, 24 and 32 bits per pixel. The range of the component values depend on the number
    /// of bits for each channel in images with 16 bits per pixel. Use the gcgIMAGE::max attribute to know each channel range:
    /// red = [0, max[0]], green = [0, max[1]], blue = [0, max[2]], alpha = [0, max[3]].
    /// @param[out] red pointer to a gcgDISCRETE2D<long> object that will receive the red component of the current image. If it is NULL,
    /// the red channel is ignored.
    /// @param[out] green pointer to a gcgDISCRETE2D<long> object that will receive the green component of the current image. If it is
    /// NULL, the green channel is ignored.
    /// @param[out] blue pointer to a ggcgDISCRETE2D<long> object that will receive the blue component of the current image. If it is
    /// NULL, the blue channel is ignored.
    /// @param[out] alpha pointer to a gcgDISCRETE2D<long> object that will receive the alpha component of the current image. If it is
    /// NULL, the alpha channel is ignored.
    /// @return true if the selected channels (non-null gcgDISCRETE2D<long> pointers) are copied to the respective objects. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see importChannels()
    bool exportChannels(gcgDISCRETE2D<long> *red, gcgDISCRETE2D<long> *green, gcgDISCRETE2D<long> *blue, gcgDISCRETE2D<long> *alpha);

    /// @brief Imports the distinct gcgDISCRETE2D<float> into the channels of the current image. The source signals (\a red, \a green,
    /// \a blue, \a alpha) must have the same dimensions. Any source can be NULL, indicating that the corresponding channel will have
    /// only zeros. The destination image can have 16 or 32 bits per pixel, if the \a alpha channel is provided. If it is not the case,
    /// the current image is adjusted to 32 bits per pixel. The destination image can have 16, 24 or 32 bits per pixel, if the \a alpha
    /// channel is not provided. If this is not the case, the current image is adjusted to 24 bits per pixel. In any case, the
    /// dimensions of the current image is adjusted to the sources. The float values of the source signals are clamped to be in the
    /// interval [0.0, 1.0] before its conversion to a decimal value to be written to the bitmap.
    /// @param[in] red pointer to a gcgDISCRETE2D<float> that will provide the red component to the current image. If it is NULL, the
    /// red component of all pixels is set to zero.
    /// @param[in] green pointer to a gcgDISCRETE2D<float> that will provide the green component to the current image. If it is NULL, the
    /// green component of all pixels is set to zero.
    /// @param[in] blue pointer to a gcgDISCRETE2D<float> that will provide the blue component to the current image. If it is NULL, the
    /// blue component of all pixels is set to zero.
    /// @param[in] alpha pointer to a gcgDISCRETE2D<float> that will provide the alpha component to the current image. If it is NULL, the
    /// alpha component of all pixels is set to zero.
    /// @return true if the selected channels (non-null gcgDISCRETE2D<float> pointers) are imported into the current image. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see exportChannels()
    bool importChannels(gcgDISCRETE2D<float> *red, gcgDISCRETE2D<float> *green, gcgDISCRETE2D<float> *blue, gcgDISCRETE2D<float> *alpha);

    /// @brief Imports the distinct gcgDISCRETE2D<double> into the channels of the current image. The source signals (\a red, \a green,
    /// \a blue, \a alpha) must have the same dimensions. Any source can be NULL, indicating that the corresponding channel will have
    /// only zeros. The destination image can have 16 or 32 bits per pixel, if the \a alpha channel is provided. If it is not the case,
    /// the current image is adjusted to 32 bits per pixel. The destination image can have 16, 24 or 32 bits per pixel, if the \a alpha
    /// channel is not provided. If this is not the case, the current image is adjusted to 24 bits per pixel. In any case, the
    /// dimensions of the current image is adjusted to the sources. The double values of the source signals are clamped to be in the
    /// interval [0.0, 1.0] before its conversion to a decimal value to be written to the bitmap.
    /// @param[in] red pointer to a gcgDISCRETE2D<double> that will provide the red component to the current image. If it is NULL, the
    /// red component of all pixels is set to zero.
    /// @param[in] green pointer to a gcgDISCRETE2D<double> that will provide the green component to the current image. If it is NULL, the
    /// green component of all pixels is set to zero.
    /// @param[in] blue pointer to a gcgDISCRETE2D<double> that will provide the blue component to the current image. If it is NULL, the
    /// blue component of all pixels is set to zero.
    /// @param[in] alpha pointer to a gcgDISCRETE2D<double> that will provide the alpha component to the current image. If it is NULL, the
    /// alpha component of all pixels is set to zero.
    /// @return true if the selected channels (non-null gcgDISCRETE2D<double> pointers) are imported into the current image. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see exportChannels()
    bool importChannels(gcgDISCRETE2D<double> *red, gcgDISCRETE2D<double> *green, gcgDISCRETE2D<double> *blue, gcgDISCRETE2D<double> *alpha);

    /// @brief Imports the distinct gcgDISCRETE2D<short> into the channels of the current image. The source signals (\a red, \a green,
    /// \a blue, \a alpha) must have the same dimensions. Any source can be NULL, indicating that the corresponding channel will have
    /// only zeros. The destination image can have 16 or 32 bits per pixel, if the \a alpha channel is provided. If it is not the case,
    /// the current image is adjusted to 32 bits per pixel. The destination image can have 16, 24 or 32 bits per pixel, if the \a alpha
    /// channel is not provided. If this is not the case, the current image is adjusted to 24 bits per pixel. In any case, the
    /// dimensions of the current image is adjusted to the sources. The short values of the source signals are clamped to be in the
    /// interval [0, 255] before being written to the bitmap, if the current image has 24 or 32 bits per pixel. If the current image has
    /// 16 bits per pixel, the range of the component values depend on the number of bits for each channel. Use the gcgIMAGE::max
    /// attribute to know each channel range used for clamping: red = [0, max[0]], green = [0, max[1]], blue = [0, max[2]], alpha = [0,
    /// max[3]].
    /// @param[in] red pointer to a gcgDISCRETE2D<short> that will provide the red component to the current image. If it is NULL, the
    /// red component of all pixels is set to zero.
    /// @param[in] green pointer to a gcgDISCRETE2D<short> that will provide the green component to the current image. If it is NULL, the
    /// green component of all pixels is set to zero.
    /// @param[in] blue pointer to a gcgDISCRETE2D<short> that will provide the blue component to the current image. If it is NULL, the
    /// blue component of all pixels is set to zero.
    /// @param[in] alpha pointer to a gcgDISCRETE2D<short> that will provide the alpha component to the current image. If it is NULL, the
    /// alpha component of all pixels is set to zero.
    /// @return true if the selected channels (non-null gcgDISCRETE2D<short> pointers) are imported into the current image. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see exportChannels()
    bool importChannels(gcgDISCRETE2D<short> *red, gcgDISCRETE2D<short> *green, gcgDISCRETE2D<short> *blue, gcgDISCRETE2D<short> *alpha);

    /// @brief Imports the distinct gcgDISCRETE2D<int> into the channels of the current image. The source signals (\a red, \a green,
    /// \a blue, \a alpha) must have the same dimensions. Any source can be NULL, indicating that the corresponding channel will have
    /// only zeros. The destination image can have 16 or 32 bits per pixel, if the \a alpha channel is provided. If it is not the case,
    /// the current image is adjusted to 32 bits per pixel. The destination image can have 16, 24 or 32 bits per pixel, if the \a alpha
    /// channel is not provided. If this is not the case, the current image is adjusted to 24 bits per pixel. In any case, the
    /// dimensions of the current image is adjusted to the sources. The int values of the source signals are clamped to be in the
    /// interval [0, 255] before being written to the bitmap, if the current image has 24 or 32 bits per pixel. If the current image has
    /// 16 bits per pixel, the range of the component values depend on the number of bits for each channel. Use the gcgIMAGE::max
    /// attribute to know each channel range used for clamping: red = [0, max[0]], green = [0, max[1]], blue = [0, max[2]], alpha = [0,
    /// max[3]].
    /// @param[in] red pointer to a gcgDISCRETE2D<int> that will provide the red component to the current image. If it is NULL, the
    /// red component of all pixels is set to zero.
    /// @param[in] green pointer to a gcgDISCRETE2D<int> that will provide the green component to the current image. If it is NULL, the
    /// green component of all pixels is set to zero.
    /// @param[in] blue pointer to a gcgDISCRETE2D<int> that will provide the blue component to the current image. If it is NULL, the
    /// blue component of all pixels is set to zero.
    /// @param[in] alpha pointer to a gcgDISCRETE2D<int> that will provide the alpha component to the current image. If it is NULL, the
    /// alpha component of all pixels is set to zero.
    /// @return true if the selected channels (non-null gcgDISCRETE2D<int> pointers) are imported into the current image. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see exportChannels()
    bool importChannels(gcgDISCRETE2D<int> *red, gcgDISCRETE2D<int> *green, gcgDISCRETE2D<int> *blue, gcgDISCRETE2D<int> *alpha);

    /// @brief Imports the distinct gcgDISCRETE2D<long> into the channels of the current image. The source signals (\a red, \a green,
    /// \a blue, \a alpha) must have the same dimensions. Any source can be NULL, indicating that the corresponding channel will have
    /// only zeros. The destination image can have 16 or 32 bits per pixel, if the \a alpha channel is provided. If it is not the case,
    /// the current image is adjusted to 32 bits per pixel. The destination image can have 16, 24 or 32 bits per pixel, if the \a alpha
    /// channel is not provided. If this is not the case, the current image is adjusted to 24 bits per pixel. In any case, the
    /// dimensions of the current image is adjusted to the sources. The long values of the source signals are clamped to be in the
    /// interval [0, 255] before being written to the bitmap, if the current image has 24 or 32 bits per pixel. If the current image has
    /// 16 bits per pixel, the range of the component values depend on the number of bits for each channel. Use the gcgIMAGE::max
    /// attribute to know each channel range used for clamping: red = [0, max[0]], green = [0, max[1]], blue = [0, max[2]], alpha = [0,
    /// max[3]].
    /// @param[in] red pointer to a gcgDISCRETE2D<long> that will provide the red component to the current image. If it is NULL, the
    /// red component of all pixels is set to zero.
    /// @param[in] green pointer to a gcgDISCRETE2D<long> that will provide the green component to the current image. If it is NULL, the
    /// green component of all pixels is set to zero.
    /// @param[in] blue pointer to a gcgDISCRETE2D<long> that will provide the blue component to the current image. If it is NULL, the
    /// blue component of all pixels is set to zero.
    /// @param[in] alpha pointer to a gcgDISCRETE2D<long> that will provide the alpha component to the current image. If it is NULL, the
    /// alpha component of all pixels is set to zero.
    /// @return true if the selected channels (non-null gcgDISCRETE2D<long> pointers) are imported into the current image. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see exportChannels()
    bool importChannels(gcgDISCRETE2D<long> *red, gcgDISCRETE2D<long> *green, gcgDISCRETE2D<long> *blue, gcgDISCRETE2D<long> *alpha);

    /////////////////////////////////////////////////////////////
    // Histogram processing.
    // The srcimage can be the destination (this).
    /////////////////////////////////////////////////////////////
    bool histogramRGBA(unsigned int hvectorR[256], unsigned int hvectorG[256], unsigned int hvectorB[256], unsigned int hvectorA[256]); // Computes the histogram for each 8bit channel.
    bool histogramGray(unsigned int hvector[256]); // Computes the grayscale histogram (but does not convert the image to grayscale).
    int  histogramIndex(unsigned int vectorsize, unsigned int *hvector); // Paletted images only. Returns the number of bins or zero if image is invalid.
    bool equalizeHistogram(gcgIMAGE *source);


    /////////////////////////////////////////////////////////////
    // Binarization.
    // The srcimage can be the destination (this).
    /////////////////////////////////////////////////////////////
    bool binarizeRGBA(gcgIMAGE *srcimage, int threR, int threG, int threB, int threA); // Binarize RGBA channels independently. Negative values indicate that the channel should not be binarized.
    bool binarizeGray(gcgIMAGE *srcimage, int threshold);  // Binarize this image using the RGB average.
    bool binarizeIndex(gcgIMAGE *srcimage, int threshold); // Binarize the index values. For paletted images only.

    /////////////////////////////////////////////////////////////
    // Image bidimensional support processing functions.
    // The srcimage can be the destination (this).
    /////////////////////////////////////////////////////////////
    bool verticalFlip();  // Mirrors the image in the vertical direction.

    /////////////////////////////////////////////////////////////
    // Utilities
    /////////////////////////////////////////////////////////////
    bool unpackBMP(void *bmpHeader, unsigned char *bmpdata, unsigned int npalcolors, unsigned char *pal);

	private:
    // Load specific formats
    bool loadUncompressed8BitTGA(FILE *file);
    bool loadUncompressedTrueColorTGA(FILE *file);
    bool loadCompressedTrueColorTGA(FILE *file);

    // Unpacking BITMAP
    bool unpackPalettedBMP(void *bmpHeader, unsigned char *bmpdata, unsigned int npalcolors, unsigned char *pal);
    bool unpack16BitBMP(void *bmpHeader, unsigned char *bmpdata, unsigned int npalcolors, unsigned char *pal);
    bool unpack24BitBMP(void *bmpHeader, unsigned char *bmpdata);
    bool unpack32BitBMP(void *bmpHeader, unsigned char *bmpdata, unsigned int npalcolors, unsigned char *pal);

    // Specific converters
    bool convertPalettedto8Bits(gcgIMAGE *srcimage);
    bool convertPalettedto24Bits(gcgIMAGE *srcimage);
    bool convert16Bitsto24Bits(gcgIMAGE *srcimage);
    bool convert32Bitsto24Bits(gcgIMAGE *srcimage);
    bool convert16Bitsto32Bits(gcgIMAGE *srcimage);
};

///@}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////     Functions for data COMPRESSION /////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// @defgroup compression Compression
/// GCGlib uses several compression levels for data encoding and decoding.
///@{
///@}

/// @defgroup rle General Run-Length Encoding
/// Run Length Encoding is a simple technique used for data compression. GCGlib provides functions for 8 bits and 32 bits
/// encoding/decoding using RLE.
///@{
/// @ingroup compression

/// @brief Packs a 8 bit sequence as a Run-Lenght Encoded block.
/// @param[in] fullsize size in bytes of the data stored in \a srcdata.
/// @param[in] srcdata pointer to the first byte of data.
/// @param[out] RLEdata pointer to a buffer that has, at least, the same size of the source data \a fullsize. This
///  buffer receives the compressed data if the compressed version is smaller than \a fullsize bytes. It might be
/// changed even if the original data is smaller than the compressed version. First 4 bytes (unsigned int) of RLEdata
/// receives its original size. Remaining bytes are the encoded data.
/// @return the size in bytes of the compressed block or 0, if the compressed version is greather than original data.
/// @see gcgUnpackRLE8
/// @since 0.01.6
GCG_API_FUNCTION    unsigned int gcgPackRLE8(unsigned int fullsize, unsigned char *srcdata, unsigned char *RLEdata);

/// @brief Decompress a 8 bit Run-Length Encoded data coded with gcgPackRLE8().
/// @param[in] RLEdata pointer to the first byte of the data, compressed using gcgPackRLE8(). Its First 4 bytes
/// (unsigned int) indicates the original size in bytes.
/// @param[out] dstdata pointer to a buffer that has, at least, the same size in bytes of the original data as indicated
/// by the first 4 bytes (unsigned int) of RLEdata.
/// @return the size in bytes of the uncompressed data or 0, if an error occurs during the decompression.
/// @see gcgPackRLE8
/// @since 0.01.6
GCG_API_FUNCTION    unsigned int gcgUnpackRLE8(unsigned char *RLEdata, unsigned char *dstdata);

/// @brief Packs a 32 bit sequence as a Run-Lenght Encoded block. The parameter \a srcdata MUST be 4 aligned <=> \a fullsize MUST be multiple of 4.
/// @param[in] fullsize size in bytes of the data stored in \a srcdata. It must be multiple of 4.
/// @param[in] srcdata pointer to the first byte of the 32bit sequence.
/// @param[out] RLEdata pointer to a buffer that has, at least, the same size of the source data \a fullsize. This
/// buffer receives the compressed data if the compressed version is smaller than \a fullsize bytes. It might be
/// changed even if the original data is smaller than the compressed version. First 4 bytes (unsigned int) of RLEdata
/// receives its original size. Remaining bytes are the encoded data. It must be 4 aligned.
/// @return the size in bytes of the compressed block or 0, if the compressed version is greather than original data.
/// @see gcgUnpackRLE32
/// @since 0.01.6
GCG_API_FUNCTION    unsigned int gcgPackRLE32(unsigned int fullsize, unsigned char *srcdata, unsigned char *RLEdata);

/// @brief Decompress a 32 bit Run-Length Encoded data coded with gcgPackRLE32().
/// @param[in] RLEdata pointer to the first byte of the data, compressed using gcgPackRLE8(). Its First 4 bytes
/// (unsigned int) indicates the original size in bytes.
/// @param[out] dstdata pointer to a buffer that has, at least, the same size in bytes of the original data as indicated
/// by the first 4 bytes (unsigned int) of RLEdata.
/// @return the size in bytes of the uncompressed data or 0, if an error occurs during the decompression.
/// @see gcgPackRLE32
/// @since 0.01.6
GCG_API_FUNCTION    unsigned int gcgUnpackRLE32(unsigned char *RLEdata, unsigned char *dstdata);
///@}

/// @defgroup bmprle Bitmap image Run-Length Encoding
/// GCGlib provides functions for encoding/decoding image bitmaps (Windows .bmp standard) using RLE.
///@{
/// @ingroup compression

/// @brief Compress a 8 bit bitmap image as a Run-Lenght Encoded block.
/// @param[in] width number of columns of the image to be compressed.
/// @param[in] height number of rows of the image to be compressed.
/// @param[in] srcdata pointer to the 8 bits bitmap image to be compressed.
/// @param[out] RLEdata pointer to a buffer that has, at least, the same size of the source bitmap image. This
/// buffer receives the compressed data if the compressed version is smaller than the original image, taking into account
/// a number of columns multiple of four. It might be changed even if the original data is smaller than the compressed version.
/// @return returns the size in bytes of the compressed image or 0, if the compressed version is greater than original data.
/// @see gcgDecompressImageRLE4
/// @see gcgDecompressImageRLE8
/// @since 0.01.6
GCG_API_FUNCTION    unsigned int gcgCompressImageRLE8(unsigned int width, unsigned int height, unsigned char *srcdata, unsigned char *RLEdata);

/// @brief Decompress a bit Run-Length Encoded 8 bits bitmap image. It receives a compressed block of a Windows .bmp image or
/// the result of the compression with gcgCompressImageRLE8().
/// @param[in] width number of columns of the image to be decompressed.
/// @param[in] height number of rows of the image to be decompressed.
/// @param[in] RLEdata pointer to the first byte of the data, compressed using gcgCompressImageRLE8() or obtained from
/// a Windows .bmp 8 bits image.
/// @param[out] dstdata pointer to a buffer that has, at least, the same size in bytes of the uncompressed image, taking into
/// account an image row size multiple of four bytes.
/// @return the size in bytes of the uncompressed image or 0, if an error occurs during the decompression.
/// @see gcgCompressImageRLE8
/// @see gcgDecompressImageRLE4
/// @since 0.01.6
GCG_API_FUNCTION    unsigned int gcgDecompressImageRLE8(unsigned int width, unsigned int height, unsigned char *RLEdata, unsigned char *dstdata);

/// @brief Decompress a bit Run-Length Encoded 4 bits bitmap image. It receives a compressed block of a Windows .bmp image.
/// @param[in] width number of columns of the image to be decompressed.
/// @param[in] height number of rows of the image to be decompressed.
/// @param[in] RLEdata pointer to the first byte of the data, obtained from a Windows .bmp 4 bits image.
/// @param[out] dstdata pointer to a buffer that has, at least, the same size in bytes of the uncompressed image, taking into
/// account an image row size multiple of four bytes.
/// @return the size in bytes of the uncompressed image or 0, if an error occurs during the decompression.
/// @see gcgDecompressImageRLE8
/// @since 0.01.6
GCG_API_FUNCTION    unsigned int gcgDecompressImageRLE4(unsigned int width, unsigned int height, unsigned char *RLEdata, unsigned char *dstdata);

///@}

/// @defgroup ctext Saving data as C code
/// Sometimes it is desirable to have data represented by C code. This is important when the data should be embedded
/// in a source file for further be compiled into a library or executable.
///@{
/// @ingroup compression

/// @brief Saves a byte array as C code for software embedding.
/// @param[in] size number of bytes contained in the array \a data.
/// @param[in] data pointer to the first byte of the array.
/// @param[in] outputname name of the text file that will receive the code that represents the byte sequence of \a data.
///  If the file exists it is overwritten (old data is lost).
/// @return true if the file is successfully created.
/// @since 0.01.6
GCG_API_FUNCTION    bool gcgSaveBytes(unsigned int size, unsigned char *data, char *outputname);

/// @brief Saves a windows bitmap image as C code for software embedding.
/// @param[in] inputname name of the bitmap image file to be represented as C code.
/// @param[in] outputname name of the text file that will receive the C code that represents the bitmap information of \a inputname.
///  If the file exists it is overwritten (old data is lost).
/// @return true if the input image is a valid bitmap image and the output file is successfully created.
/// @since 0.01.6
GCG_API_FUNCTION    bool gcgSaveBMPcode(char *inputname, char *outputname);

///@}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////////     PLOT macros, classes, and functions /////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

// Macros for plotting graphs
#define   GCG_PLOT_MAX_LINES      16  // In any implementation, supremum is 255 lines
#define   GCG_PLOT_MAX_AXIS        3  // Prepared for 3D plots

// Macros for range definition
#define   GCG_PLOT_X      0
#define   GCG_PLOT_Y      1
#define   GCG_PLOT_Z      2

#define   GCG_PLOT_RANGE_INI   0
#define   GCG_PLOT_RANGE_END   1

class    GCG_API_CLASS    gcgPLOT   :  public gcgCLASS {
  private:
    // Basic struct for independent lines
    typedef struct __line {
      char            *linename;    // Name to identify this line
      float           r, g, b, a;   // Color for plotting this line
      float           linewidth;    // Line width
      unsigned short  bitpattern;   // Pattern for lines

      VECTOR3         *data;        // Pointer to point data buffer
      unsigned int    maxdata;      // Data buffer capacity
      unsigned int    ndata;        // Number of points in buffer
    } LINE;

    // Basic struct for axis
    typedef struct __axis {
      char            *title;       // Title to identify this axis
      float           r, g, b, a;   // Color for plotting this title
      float           linewidth;    // Axis width
      unsigned short  bitpattern;   // Pattern for lines
      float           ini;          // Range start
      float           end;          // Range end
    } AXIS;

    // Lines buffer
    LINE lines[GCG_PLOT_MAX_LINES];
    unsigned int nlines;     // Current number of lines

    // Plot axis
    AXIS  axis[GCG_PLOT_MAX_AXIS];  // For each axis, information and a real interval.

    // Plot info
    float   framebox[4];                    // Output frame box
    float   linewidth;                      // Frame line width
    float   frameR, frameG, frameB, frameA; // Frame color
    float   plotR, plotG, plotB, plotA;     // Plot rectangle color

    unsigned int gridpixelsX;               // Interval in pixels between two consecutive X values
    unsigned int gridpixelsY;               // Interval in pixels between two consecutive Y values
    float   gridR, gridG, gridB, gridA;     // Grid color

    // Text output
    gcgTEXT textoutput;                     // Text output object
    unsigned int textWidthX, textHeightX;   // Text extent in X
    unsigned int textWidthY, textHeightY;   // Text extent in Y
    float        factorX;                   // Text factor for X extents

  public:
    // Constructor
    gcgPLOT();
    virtual ~gcgPLOT();

    ///////////////////////////////////////////////////////////////////////
    // INPUT DATA SPECIFICATION
    int newLine();  // Adds a new line to this plot
    bool addPoint2D(unsigned int lineindex, float x, float y);
    void setAxisRange(unsigned int axis, float ini, float end);
    void clipOutOfRange(unsigned int lineindex, unsigned int iaxis);
    void rangeFromData(unsigned int iaxis);
    void clearData(unsigned int lineindex);
    void clearAllData();

    ///////////////////////////////////////////////////////////////////////
    // DRAW PARAMETERS SPECIFICATION
    void setFrame(float x, float y, float width, float height, float linewidth);
    void adjustFrame(float xoffset, float yoffset, float widthoffset, float heightoffset);
    void setFrameColor(float r, float g, float b, float a);

    void setPlotColor(float r, float g, float b, float a);
    void setGrid(unsigned int pixelsx, unsigned int pixelsy);
    void setGridColor(float r, float g, float b, float a);

    void setAxis(unsigned int axis, char *title, float r, float g, float b, float a, float linewidth, unsigned short bitpattern);
    void setLine(unsigned char lineindex, char *linename, float r, float g, float b, float a, float linewidth, unsigned short bitpattern);

    ///////////////////////////////////////////////////////////////////////
    // DRAW FUNCTIONS
    void draw();
};



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////  STATISTICS macros, classes, and functions /////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Generate random numbers uniformly distributed with period (2^19937) - 1
//
//  M. Matsumoto & T. Nishimura, "Mersenne Twister: A 623-Dimensionally
//   Equidistributed Uniform Pseudo-Random Number Generator", ACM Transactions
//   on Modeling and Computer Simulation, vol. 8, no. 1, 1998, pp. 3-30.
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgRANDOM   :  public gcgCLASS {
  #define GCG_MERSENNE_N          624
  #define GCG_MERSENNE_MATRIX_A   0x9908b0df  // Constant vector a

  private:
    unsigned long mt[GCG_MERSENNE_N]; // The array for the state vector
    unsigned long mag01[2];           // mag01[x] = x * MATRIX_A for x=0,1
    int mti;                          // Index for Mersenne Twisted state vector
    unsigned int lastInterval;        // Last interval length for intRandom
    unsigned int RLimit;              // Rejection limit used by intRandom

  public:
    // Constructor
    gcgRANDOM();                      // Use C conventional rand() to define seed
    gcgRANDOM(unsigned int seed);
    virtual ~gcgRANDOM();

    // SERIES SPECIFICATION
    void  setSeed(unsigned int seed);

    // Random number generation
    unsigned int bitRandom();         // Generate 32 random bits
    double random();                  // Output random float in U[0, 1)

    // Random number generation in an interval
    int intRandom(int min, int max);  // Output random integer in U[min, max]
    float floatRandom(float min, float max);  // Output random float in U[min, max]
    double doubleRandom(double min, double max);  // Output random double in U[min, max]
};



//////////////////////////////////////////////////////////////////////////////
// Generate random numbers with Gaussian distribution with 0 mean and 1.0 as
// standard-deviation N(0, 1).
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgRANDOMGAUSSIAN   :  public gcgCLASS {
  private:
    gcgRANDOM ngen1;    // Independent random generators
    gcgRANDOM ngen2;
    bool hasValue;      // Flags the existence of a second value.
    double secondValue; // Keeps the second value

  public:
    // Constructor
    gcgRANDOMGAUSSIAN();  // Use C conventional rand() to define seed
    gcgRANDOMGAUSSIAN(unsigned int seed1, unsigned int seed2); // seed1 must be different than seed2.
    virtual ~gcgRANDOMGAUSSIAN();

    // SERIES SPECIFICATION: seed1 must be different than seed2.
    void  setSeed(unsigned int seed1, unsigned int seed2);

    // RANDOM NUMBER GENERATION
    double random();                     // Output random float in N(0, 1)
};

////////////////////////////////////////////////////////////////
// Class to generate vectors with isotropic distribution.
////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgRANDOMVECTOR   :  public gcgCLASS {
  private:
    gcgRANDOM ngen1;  // Independent random generators
    gcgRANDOM ngen2;

  public:
    // Constructor
    gcgRANDOMVECTOR(); // Use C conventional rand() to define seed
    gcgRANDOMVECTOR(unsigned int seed1, unsigned int seed2); // seed1 must be different than seed2.
    virtual ~gcgRANDOMVECTOR();

    // SERIES SPECIFICATION: seed1 must be different than seed2.
    void  setSeed(unsigned int seed1, unsigned int seed2);

    // RANDOM VECTOR GENERATION
    void random(VECTOR3 v);          // Output isotropic float vector in S^2.
    void random(VECTOR3d v);         // Output isotropic double vector in S^2.
};


/// @brief Class to estimate the number of events per second.
/// @since 0.01.6
class    GCG_API_CLASS    gcgEVENTSPERSECOND   :  public gcgCLASS {
  private:
    void  *handle; ///< Internal handle of this object.

  public:
    /// @brief Constructs a new, independent events per second estimator.
    gcgEVENTSPERSECOND();

    /// @brief Frees all object resources.
    virtual ~gcgEVENTSPERSECOND();

    /// @brief Indicates that a series of events will occur. It gets the current time and waits
    /// until finishedEvents() is called to tell how many events occurred between the two calls. After
    /// this the events per second is updated.
    /// @see finishedEvents()
    /// @see getEventsPerSecond()
    void  startingEvents();

    /// @brief Indicates that \a n events occurred since last call of startingEvents(). The events per second is
    /// then updated.
    /// @param[in] nevents number of events occurred since last call to startingEvents().
    /// @see startingEvents()
    /// @see getEventsPerSecond()
    /// @return currently computed events-per-second estimation.
    float finishedEvents(int nevents = 1);


    /// @brief Returns current events-per-second.
    /// @see startingEvents()
    /// @see finishedEvents()
    /// @return The last computed number of events per second.
    float getEventsPerSecond();            // Retorna o ultimo EPS
};


////////////////////////////////////////////////////////////////////////////////////
// FUNCTION PROTOTYPES
////////////////////////////////////////////////////////////////////////////////////

// Compute the Probability Distribution Function from a histogram.
GCG_API_FUNCTION    int gcgPDFfromHistogram(float *pdf, unsigned int *histogram, unsigned int Nbins);


// Find the optimal threshold using Otsu's method.
// Nobuyuki Otsu, "A threshold selection method from gray level histograms",
// IEEE Transactions on Systems, Man and Cybernetics, vol.9, n.1, pp.62-66, jan/1979.
GCG_API_FUNCTION    unsigned int gcgOptimalThresholdOtsu(float *pdf, unsigned int left, unsigned int right);


//************* Double precision versions *************
GCG_API_FUNCTION    int gcgPDFfromHistogram(double *pdf, unsigned int *histogram, unsigned int Nbins);
GCG_API_FUNCTION    unsigned int gcgOptimalThresholdOtsu(double *pdf, unsigned int left, unsigned int right);


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////  FRUSTUM macros, classes, and functions ////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


#define GCG_FRUSTUM_PARTIAL		-1
#define GCG_FRUSTUM_OUTSIDE	   0
#define GCG_FRUSTUM_INSIDE	   1


class    GCG_API_CLASS    gcgFRUSTUM   :  public gcgCLASS {
      public: // But read-only
        // CAMERA POSITION AND ORIENTATION: in world coordinates
        float   x, y, z;    // Observer's position

        VECTOR3 view;     // Viewing direction: given by the quaternion
        VECTOR3 up;       // Head up direction: given by the quaternion
        VECTOR3 right;    // Right side direction: given by the quaternion

      private:
        // CAMERA PARAMETERS (always updated by changes in frustum)
        VECTOR4d orientation; // QUATERNION reflecting the viewers orientation.
        MATRIX4d view_matrix;

        // PARAMETROS DA PROJECAO
        MATRIX4d proj_matrix;

        // Equacoes dos planos do FRUSTUM corrente (redundante pois é calculado toda hora)
        // Coeficientes do plano superior do frustum
        float topA, topB, topC, topD;

        // Coeficientes do plano inferior do frustum
        float bottomA, bottomB, bottomC, bottomD;

        // Coeficientes do plano posterior do frustum
        float farA, farB, farC, farD;

        // Coeficientes do plano anterior do frustum
        float nearA, nearB, nearC, nearD;

        // Coeficientes do plano direito do frustum
        float rightA, rightB, rightC, rightD;

        // Coeficientes do plano esquerdo do frustum
        float leftA, leftB, leftC, leftD;

      public:
        //metodos construtores
        gcgFRUSTUM();
        virtual ~gcgFRUSTUM();

        ///////////////////////////////////////////////////////////////////////
        // FREE VIEWER

        // Posicao do observador
        void setPosition(float x, float y, float z); // Posicao do observador
        void setPosition(double x, double y, double z); // Posicao do observador
        void setPosition(VECTOR3 pos); // Posicao do observador
        void setPosition(VECTOR3d pos); // Posicao do observador

        void movePosition(float dx, float dy, float dz);    // Move o observador, dado um vetor
        void movePosition(double dx, double dy, double dz); // Move o observador, dado um vetor
        void movePosition(VECTOR3 pos); // Posicao do observador
        void movePosition(VECTOR3d pos); // Posicao do observador

        void advancePosition(float forward, float upward, float rightward); // Avanca usando as direcoes de visualizacao
        void advancePosition(double forward, double upward, double rightward); // Avanca usando as direcoes de visualizacao

        // Direcoes de observacao
        void resetOrientation();    // Loads the canonical reference system

        void setViewVector(float dirX, float dirY, float dirZ); // Configura vetor de direcao
        void setViewVector(double dirX, double dirY, double dirZ); // Configura vetor de direcao
        void setViewVector(VECTOR3 dir); // Configura vetor de direcao
        void setViewVector(VECTOR3d dir); // Configura vetor de direcao

        void setViewVectorSpherical(float latit, float longit); // latit em [-90, 90]  longit em [-180, 180]
        void setViewVectorSpherical(double latit, double longit); // latit em [-90, 90]  longit em [-180, 180]

        void setUpVector(float cimaX, float cimaY, float cimaZ); // Configura vetor acima
        void setUpVector(double cimaX, double cimaY, double cimaZ); // Configura vetor acima
        void setUpVector(VECTOR3 cima); // Configura vetor acima
        void setUpVector(VECTOR3d cima); // Configura vetor acima

        void setTarget(float alvoX, float alvoY, float alvoZ); // Ajusta as direcoes para visualizar o alvo.
        void setTarget(double alvoX, double alvoY, double alvoZ); // Ajusta as direcoes para visualizar o alvo.
        void setTarget(VECTOR3 alvo); // Ajusta as direcoes para visualizar o alvo.
        void setTarget(VECTOR3d alvo); // Ajusta as direcoes para visualizar o alvo.

        ///////////////////////////////////////////////////////////////////////
        // OBSERVER IN THE CENTER OF AN UNITARY SPHERE (planetarium)

        // Rotates the unit ball where the observer is centered (planetarium)
        //  - all functions use the local viewing system to apply rotations
        void rotateOrientationTrackball(double x1, double y1, double x2, double y2); // Trackball: p1,p2 em [-1,1]x[-1,1] plano no qual a bola é projetada. rotacao livre.
        void rotateOrientationSpherical(double dlat, double dlong);     // Free rotation of the planetarium using spherical angles
        void rotateOrientationEuler(double pitch, double yaw, double row); // Rotation of the planetarium using Euler angles but keeping main axis aligned with Y e X
        void rotateOrientationAxis(double ang, double axisX, double axisY, double axisZ); // Rotation of the planetarium around a given axis.

        void alignAxis(); // Aligns up vector with Y, and right vector with X

        ///////////////////////////////////////////////////////////////////////
        // OBSERVER IS FREE ROTATING AROUND AN ARBITRARY SPHERE (orbital)

        // Rotation of the observer's system around a sphere
        //  - all functions align the local viewing system to the canonical system,
        //    apply rotations and then align the canonical system back to the local system
        void rotateOrbitTrackball(double centroX, double centroY, double centroZ, double x1, double y1, double x2, double y2); // Trackball: p1,p2 em [-1,1]x[-1,1] plano no qual a esfera é projetada. rotacao livre.
        void rotateOrbitSpherical(double centroX, double centroY, double centroZ, double dlat, double dlong); // Spherical coordinates
        void rotateOrbitEuler(double centroX, double centroY, double centroZ, double pitch, double yaw, double roll); // Euler angles

        ///////////////////////////////////////////////////////////////////////
        // OBSERVER IS FREE ROTATING AROUND ARBITRARY AXIS

        // Rotation of the observer's system around an axis
        void rotateAxis(double ang, double ox, double oy, double oz, double dirX, double dirY, double dirZ);


        ///////////////////////////////////////////////////////////////////////
        // VISIBILITY TESTS

        int isPointVisible(float x, float y, float z);
        int isSphereVisible(float x, float y, float z, float raio);
        int isBoxVisible(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);

        ///////////////////////////////////////////////////////////////////////
        //  GEOMETRIC PROJECTIONS
        void setPerspective(float fovh, float aspect, float prox, float dist);
        void setOrthographic(float  left, float right, float  top, float bottom, float near, float far);

        ///////////////////////////////////////////////////////////////////////
        //  GP Interfaces

        // Loads the projection and modelview matrix to OpenGL
        void exportOpenGL();

        ///////////////////////////////////////////////////////////////////////
        //  CAMERA INFORMATION RETRIEVAL

        void getViewMatrix(MATRIX4 matrot);
        void getViewMatrix(MATRIX4d matrot);

        void getProjectionMatrix(MATRIX4 matproj);
        void getProjectionMatrix(MATRIX4d matproj);

      private:
        // Calcula as direcoes do observador
        void computeParameters();
};



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////  VIDEO macros, classes, and functions //////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class gcgINTERNAL_VIDEO; // Internal class depends on platform

//////////////////////////////////////////////////////////////////////////////
/// @brief Base class for video processing.
///
/// The gcgVIDEO class gives all main attributes for video processing and holds the handler
/// specific subclasses. The gcgVIDEO is currently provided for Windows and Linux. Do not change
/// any attributes unless you are absolutely sure about you are doing.
///
/// @since 0.01.6
///
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgVIDEO   :  public gcgCLASS {
  public:
    unsigned int  width;       //< Frame width in pixels. Read-only.
    unsigned int  height;      //< Frame height in pixels. Read-only.
    unsigned char bpp;         //< Bits per pixel. Read-only.
    float         fps;         //< Frames per second. Read-only.
    unsigned int  bitrate;	   //< Bits per second. Read-only.

    gcgINTERNAL_VIDEO *handle; //< Handle for internal video object or platform specific API. Read-only.

  public:

    /// @brief Constructs a valid but empty image. The image can be used as destiny image in any gcgIMAGE method or GCGlib function.
    /// @see ~gcgVIDEO()
    gcgVIDEO();

    /// @brief Releases all video resources by deleting the video handler.
    /// @see gcgVIDEO()
    virtual ~gcgVIDEO();
};

//////////////////////////////////////////////////////////////////////////////
/// @brief Class for capturing video from camera devices.
///
/// The gcgVIDEOCAPTURE class is the main interface of GCGlib with camera devices. It uses
/// platform specific objects and APIs. The camera is identified by its sequencial integer
/// number. The capture mechanism is synchronous using a callback funtion. The video
/// frames are provided by gcgIMAGE objects. Do not change any attributes unless you are
/// absolutely sure about you are doing.
///
/// @since 0.01.6
///
//////////////////////////////////////////////////////////////////////////////

class    GCG_API_CLASS    gcgVIDEOCAPTURE : public gcgVIDEO {
	unsigned int  id;   //< Current camera device identifier. Read-only.

  public:
    /// @brief Constructs a valid video capture object. The capture actually starts with calls to
    /// \a setCallBackFunction() and \a openCamera().
    /// @see openCamera()
    /// @see setCallBackFunction()
    /// @see ~gcgVIDEOCAPTURE()
		gcgVIDEOCAPTURE();

    /// @brief Releases all video capture resources by calling destroyVideo().
    /// @see destroyVideo()
    /// @see gcgVIDEOCAPTURE()
		virtual ~gcgVIDEOCAPTURE();

    /// @brief Releases all resources of this video capture object.
    /// @return true if the resources were released. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see gcgVIDEOCAPTURE()
    /// @see ~gcgVIDEOCAPTURE()
    virtual bool destroyVideo();

    /// @brief Returns the number of valid cameras installed in the system.
    /// @return the number of cameras. If negative or zero, no capture devices are available or an
    /// error occured: check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see getCameraName()
		virtual int getNumberOfCameras();

    /// @brief Gets the human readable name of the capture device given its integer identification.
    /// @param id The device capture identifier.
    /// @param pCameraName Pointer to the char buffer to receive the string. It must be non-null. The
    /// maximum number of chars supported by \a pCameraName must be indicated in \a maxName.
    /// @param maxName Maximum number of characters supported by the buffer \a pCameraName.
    /// @return true if the name was retrieved. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see getNumberOfCameras()
		virtual bool getCameraName(unsigned int id, char* pCameraName, unsigned int maxName);

    /// @brief Opens the capture device and makes it ready to start image retrieval.
    /// @param id The device capture identifier.
    /// @param width Desired frame width in pixels. It might not be supported by the device.
    /// @param height Desired frame height in pixels. It might not be supported by the device.
    /// @param bpp  Desired number of bits per pixel of each pixel. It might not be supported by the device.
    /// @param fps  Desired frames per second rate. It might not be supported by the device.
    /// @return true if the camera was successfully opened. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport())
    /// for knowing the problem and make sure the parameters are valid for the given device.
    /// @see start()
    /// @see stop()
    /// @see resume()
    /// @see pause()
    /// @see setCallBackFunction()
		virtual bool openCamera(unsigned int id, unsigned int width, unsigned int height, unsigned char bpp, float fps);

    /// @brief Starts synchronous capturing. If successful, the capture starts from the device indicated by the previous call
    /// to \a openCamera() and the frames are delivered to the callback set by \a setCallBackFunction().
    /// @return true if the capture started. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see openCamera()
    /// @see stop()
    /// @see resume()
    /// @see pause()
		virtual bool start();

    /// @brief Stops synchronous capturing. If successful, the capture stops. It generally releases some video resources.
    /// For a faster restart, use \a pause() instead.
    /// @return true if the capture stoped. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see start()
    /// @see openCamera()
    /// @see resume()
    /// @see pause()
		virtual bool stop();

    /// @brief Resumes synchronous capturing. If successful, the capture restarts.
    /// @return true if the capture is resumed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see start()
    /// @see stop()
    /// @see pause()
    /// @see openCamera()
		virtual bool resume();

    /// @brief Pauses the synchronous capturing.
    /// @return true if the capture was paused. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see start()
    /// @see stop()
    /// @see resume()
    /// @see openCamera()
		virtual bool pause();

    /// @brief Returns true if the object is currently capturing, i.e., not stoped.
    /// @return true if the capture is going on or paused.
    /// @see start()
    /// @see stop()
    /// @see openCamera()
		virtual bool isCapturing();

    /// @brief Sets the callback function for the current object. It should be called before \a start(). Changing the
    /// internal function during the capture might give undesirable results. The callback function receives a pointer
    /// of the gcgVIDEOCAPTURE object that is delivering the new frame. The callback must return as fast as possible
    /// otherwise the video capture stream will be delayed. This might result in frame losses or instability depending
    /// on the system.
    /// @param callback pointer to a function that receives one gcgVIDEOCAPTURE pointer and returns void. When called,
    /// the \a callback function receives the pointer of the object that delivers the new frame. If NULL, a warning is
    /// reported and all subsequent frames are discarded.
    /// @return true if the callback was correctly set. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see openCamera()
    /// @see start()
    /// @see copyFrameTo()
		virtual bool setCallBackFunction(void (*callback) (gcgVIDEOCAPTURE*));

    /// @brief Copies the last delivered frame into a gcgIMAGE object. It is generally used during a call to the callback function
    /// defined by \a setCallBackFunction() in order to get a copy of the new frame.
    /// @param dstimg A pointer to the gcgIMAGE object to which the last frame received by this gcgVIDEOCAPTURE must be copied to. If NULL,
    /// a warning is just reported.
    /// @return the frame time in seconds. If negative, an error has occured. Check GCG_REPORT_MESSAGE(gcgGetReport()) for
    /// knowing the problem.
    /// @see openCamera()
    /// @see start()
    /// @see setCallBackFunction()
		virtual double copyFrameTo(gcgIMAGE *dstimg);
};

//////////////////////////////////////////////////////////////////////////////
/// @brief Class for decode frames from a video file.
///
/// The gcgVIDEOFILE class is the main interface of GCGlib with video files. It uses
/// platform specific objects and APIs. The frame decoding is assynchronous using frame indices.
/// The video frames are provided by gcgIMAGE objects. Do not change any attributes unless you are
/// absolutely sure about you are doing.
///
/// @since 0.01.6
///
//////////////////////////////////////////////////////////////////////////////

class    GCG_API_CLASS    gcgVIDEOFILE : public gcgVIDEO {
	public:
    /// @brief Constructs a valid video file reader. The decodification actually starts with a call to
    /// \a openVideoFile().
    /// @see openVideoFile()
    /// @see ~gcgVIDEOFILE()
    gcgVIDEOFILE();

    /// @brief Releases all video file resources by calling destroyVideo().
    /// @see destroyVideo()
    /// @see gcgVIDEOFILE()
    virtual ~gcgVIDEOFILE();

    /// @brief Releases all resources of this video file object.
    /// @return true if the resources were released. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see gcgVIDEOFILE()
    /// @see ~gcgVIDEOFILE()
    virtual bool destroyVideo();

    /// @brief Opens the video file and makes it ready to be decoded. Initially points to the first frame in the video.
    /// @param filename Video file name.
    /// @return true if the video file was successfully opened. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport())
    /// for knowing the problem.
    /// @see getFrameCount();
    /// @see copyFrame()
    /// @see setCurrentPosition()
    /// @see getCurrentPosition()
    virtual bool openVideoFile(const char *filename);

    /// @brief Returns the total number of frames in the video file.
    /// @return The number of frames in the video file or zero/negative value if an error occured. In case of
    /// failure, check GCG_REPORT_MESSAGE(gcgGetReport())
    /// for knowing the problem.
    /// @see openVideoFile();
    /// @see copyFrame()
    /// @see setCurrentPosition()
    /// @see getCurrentPosition()
    virtual long getFrameCount();

    /// @brief Gets the current video position, i.e., the current frame number that can be read by a call to \a copyFrame(). If the
    /// last frame was read by a previous call to \a copyFrame(), it reports a warning (0x1E06A) and returns a negative value. Use
    /// \a setCurrentPosition() to get a valid position.
    /// @return The current frame number. If an error occurred or the end of video was reached by a call to \a copyFrame(),
    /// reporting a warning (0x1E06A), it returns a negative value. Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing
    /// the problem.
    /// @see getFrameCount();
    /// @see setCurrentPosition()
    /// @see copyFrame()
    virtual long getCurrentPosition();

    /// @brief Sets the current video position, i.e., points to the indicated frame number.
    /// @param newposition Frame number to be positioned to. It must be in the interval [0, \a getFrameCount() - 1] otherwise
    /// an error is reported.
    /// @return true if it was correctly positioned in the frame. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport())
    /// for knowing the problem.
    /// @see getFrameCount();
    /// @see getCurrentPosition()
    /// @see copyFrame()
    virtual bool setCurrentPosition(long newposition);

    /// @brief Copies the current frame to a gcgIMAGE object. If successful, it automatically points to the next frame. If
    /// the last frame was already read, it reports a warning (0x1E06A) and returns false. Use \a setCurrentPosition() to
    /// read a valid frame.
    /// @param dstimg A pointer to the gcgIMAGE object to which the current frame is to be copied. If NULL,
    /// an error is reported.
    /// @return true if the frame was copied. If it returns false, it reached the end of video, reporting a warning (0x1E06A),
    /// or an error occured. Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see getFrameCount();
    /// @see getCurrentPosition()
    /// @see setCurrentPosition()
    virtual bool copyFrame(gcgIMAGE *dstimg);
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////  GENERAL ABSTRACT DATA STRUCTURE definitions    ///////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief Generic abstract class for defining classes to be used in the
/// GCGlib data structures. In fact, a specialization of a correct and
/// data structure dependent class is mandatory for using the data structures.
///
/// @since 0.02.113
////////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgDATA  :  public gcgCLASS {};



////////////////////////////////////////////////////////////////////////////////
/// @brief Generic abstract class to allow iterations over the several
/// GCGlib data structures. The gcgITERATOR::next() returns the next object
/// until it is NULL. The returned object type depends on the data structure
/// and commonly is a specialization of gcgNODE, gcgDOUBLELINK or gcgLINK classes.
/// While iteration is being done, the original data structure must not be changed by
/// insertions, removals or moves. Iterators copies all needed information to iterate
/// over the nodes and are not allowed to change its associated data structure.
/// A data structure can have several gcgITERATOR instances working at a time.
/// The gcgITERATOR object must be deleted after use.
///
/// @since 0.02.113
////////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgITERATOR   :  public gcgCLASS {
  public:
    /// @brief Destroys the iterator object and releases all of its resources.
    /// The iterated data structure does not change. Destruction is
    /// dependent on the underlying data structure.
    /// @see next()
    virtual ~gcgITERATOR();

    /// @brief Gets the next object from the data structure. While iterating,
    /// the underlying data structure must not be changed by insertions, removals or
    /// moves. The returned pointer is guaranteed to not being accessed again by the
    /// iterator.
    /// @return The pointer of the next object or NULL, if the iteration is finished. The precise
    /// object type depends on the data structure and commonly is a specialization of gcgLINK,
    /// gcgDOUBLELINK or gcgNODE classes.
    /// @see ~gcgITERATOR()
    virtual gcgDATA *next() = 0;
};


//////////////////////////////////////////////////////////////////////////////
/// @brief Base abstract class for defining data structures in GCGlib. It
/// indicates the minimum methods that all data structures must provide. Some
/// abstract specializations of this class demand other interfaces to handle
/// their elements under more specific or restricted conditions.
///
/// @since 0.02.113
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgDATASTRUCTURE   :  public gcgCLASS {
    /// @brief Gets the number of elements stored in the data structure.
    /// @return Returns the number of elements stored in the data structure.
    virtual unsigned int getCounter() = 0;

    /// @brief Deletes and removes all entries from the data structure. All resources used by the data
    /// structure are also released.
    /// @return Returns true if all entries were deleted and removed from the data structure. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see detach()
    virtual bool deleteAll() = 0;

    /// @brief Returns an iterator for traversing the elements of the data structure. The traversal order is
    /// defined by the parameter \a traversemode. The possible traverse modes are dependent on the data structure and
    /// its implementation. Always check the specific documentation of the specialized data structure to find
    /// the available traversing modes. The data structure must not be changed by insertions, removals or moves
    /// while the iterator is being used. You must delete the returned iterator after use. The iterator copies
    /// a minimal information from the data structure. Note that deleting an iterator does not affect the nodes.
    /// @param traversemode Specifies the order that the available elements in a data structure must
    /// be traversed. The possible traverse modes are dependent on the specialized data structure and
    /// its implementation. Always check the specific documentation of the data structure to find
    /// the available traversing modes.
    /// @return Returns an iterator for traversing the elements of the data structure in the order defined by
    /// \a traversemode. The data structure must not be changed by insertions, removals or moves while the iterator
    /// is being used. You MUST delete the returned gcgITERATOR object after use. If it returns NULL,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see detach()
    virtual gcgITERATOR *getIterator(int traversemode = 0) = 0;

    /// @brief Force the data strucuture to be empty. It has the same effect as removing all entries from the
    /// data structure but keeping their chaining (which will used by the returned iterator). The entries are NOT
    /// deleted. In order to retrieve the detached entries, a gcgITERATOR with default traversal mode is returned
    /// (\a traversemode = 0). This is useful to process the nodes freely and without the possible restrictions of
    /// the underlying data strucuture. Thus, the gcgITERATOR returned by gcDATASTRUCTURE::detach() MUST be used
    /// to delete all the entries or reinsert them in another data structure. The traversal order of the iterator is
    /// defined by the parameter \a traversemode. The possible traverse modes are dependent on the data structure and
    /// its implementation. Always check the specific documentation of the specialized data structure to find
    /// the available traversing modes. All resources currently used by the data structure are released (becomes empty)
    /// but it can be reused normally. You must delete the gcgITERATOR after its use.
    /// @param traversemode Specifies the order that the available elements in a data structure must
    /// be traversed by the returned iterator. The possible traverse modes are dependent on the specialized data
    /// structure and its implementation. Always check the specific documentation of the data structure to find
    /// the available traversing modes.
    /// @return Returns an iterator for traversing the elements (in \a traversemode order) that were detached from
    /// the data structure. The data structure becomes empty and can be reused. You MUST delete the returned gcgITERATOR
    /// object after use. If it returns NULL, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see deleteAll()
    /// @see getIterator()
    virtual gcgITERATOR *detach(int traversemode = 0) = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Generic abstract class for defining a linkable node for use in single
/// linked lists and linear data structures. It can be used with several classes
/// in GCGlib. It is sufficient for use for some data structures as gcgLINKEDLIST.
/// Specialized objects of this class may be returned by gcgITERATOR
/// objects obtained from the data structures.
///
/// @since 0.02.113
////////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgLINK  :  public gcgDATA {
  public:
    union {
      gcgLINK *next;      ///< Points to the right/next gcgLINK node in a list. Same pointer as \a right. Read-only.
      gcgLINK *right;     ///< Points to the right/next gcgLINK node in a list. Same pointer as \a next. Read-only.
    };
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Generic abstract class for defining a linkable node for use in
/// double linked lists and linear data structures. It can be used with several
/// classes in GCGlib, including extended nodes (gcgNODE) that can be comparated,
/// enumerated and ordered by more sophisticated data structures. This is intended
/// for use in lists, maps and trees. The gcgDOUBLELINKEDLIST must receive instances
/// of gcgDOUBLELINK or its specialized classes. Specialized objects of this
/// class may be returned by gcgITERATOR objects obtained from the data structures.
///
/// @since 0.02.113
////////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgDOUBLELINK  :  public gcgLINK {
  public:
    union {
      gcgLINK *previous;  ///< Points to the left/previous gcgLINK node in a list. Same pointer as \a left. Read-only.
      gcgLINK *left;      ///< Points to the left/previous gcgLINK node in a list. Same pointer as \a previous. Read-only.
    };
};



//////////////////////////////////////////////////////////////////////////////
/// @brief Base abstract class for defining a sequential data structure in
/// GCGlib for lists. It indicates the minimum methods that all list structures
/// with elements that can be in any position must provide. Note that some data
/// structures might provide other interfaces to handle their elements. This
/// interface is different than gcgORDEREDSTRUCTURE where the elements are
/// ordered and countable in the data strucuture.
///
/// @since 0.02.113
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgLISTSTRUCTURE   :  public gcgDATASTRUCTURE {
  public:
    /// @brief Inserts a new entry \a newnode in the first position of the data structure.
    /// @param[in] newnode a pointer to a linkable node (gcgLINK) to be inserted in the data structure.
    /// It is generally an object of a specialization of gcgLINK that carries the node information.
    /// @return true if \a newnode is correctly inserted. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see remove()
    virtual bool insertFirst(gcgLINK *newnode) = 0;

    /// @brief Inserts a new entry \a newnode in the last position of the data structure.
    /// @param[in] newnode a pointer to a linkable node (gcgLINK) to be inserted in the data structure.
    /// It is generally an object of a specialization of gcgLINK that carries the node information.
    /// @return true if \a newnode is correctly inserted. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see remove()
    virtual bool insertLast(gcgLINK *newnode) = 0;

    /// @brief Inserts a new entry \a newnode in the data structure, after an existent entry pointed by
    /// \a node.
    /// @param[in] newnode a pointer to a linkable instance (gcgLINK) to be inserted after \a node.
    /// This pointer is deleted by the destructor or a deleteAll() call. A NULL value generates an error.
    /// @param[in] node a pointer to an entry that is already in the data structure. A NULL value
    /// has the same effect as insertFirst(\a newnode). After the insertion, the \a newnode will
    /// succeed the \a node in the data structure: node->next = newnode and newnode->previous = node.
    /// @return returns true if the data is successfully inserted after \a node. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertLast()
    /// @see insertBefore()
    /// @see remove()
    virtual bool insertAfter(gcgLINK *newnode, gcgLINK *node) = 0;

    /// @brief Inserts a new entry \a newnode in the data structure, before an existent entry pointed by
    /// \a node.
    /// @param[in] newnode a pointer to a linkable instance (gcgLINK) to be inserted after \a node.
    /// This pointer is deleted by the destructor or a deleteAll() call. A NULL value generates an error.
    /// @param[in] node a pointer to an entry that is already in the data structure. A NULL value
    /// has the same effect as insertLast(\a newnode). After the insertion, the \a node will
    /// succeed the \a newnode in the data structure: newnode->next = node and node->previous = newnode.
    /// @return returns true if the data is successfully inserted after \a node. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see insertAfter()
    /// @see remove()
    virtual bool insertBefore(gcgLINK *newnode, gcgLINK *node) = 0;

    /// @brief Move an entry \a node that is already in the data structure to its first position.
    /// The node will have a NULL \a previous link.
    /// @param[in] node a pointer to a linkable instance (gcgLINK) that is already in the data
    /// structure. A NULL value generates an error.
    /// @return returns true if the data is successfully moved to the beginning of the data
    /// structure. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing
    /// the problem.
    /// @see insertFirst()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see moveToLast()
    /// @see remove()
    virtual bool moveToFirst(gcgLINK *node) = 0;

    /// @brief Move an entry \a node that is already in the data structure to its last position. The node
    /// will have a NULL \a next link.
    /// @param[in] node a pointer to a linkable instance (gcgLINK) that is already in the data structure.
    /// A NULL value generates an error.
    /// @return returns true if the data is successfully moved to the end of the data structure. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see moveToFirst()
    /// @see remove()
    virtual bool moveToLast(gcgLINK *node) = 0;

    /// @brief Switches the position of two existent elements of the data structure. The two nodes
    /// must be part of the data structure.
    /// @param[in] node1 a pointer to a linkable node (gcgLINK) that carries the information to be switched with
    /// the position of \a node2. If NULL, an error occurs.
    /// @param[in] node2 a pointer to a linkable node (gcgLINK) that carries the information to be switched with
    /// the position of \a node1. If NULL, an error occurs.
    /// @return true if the nodes are correctly switched. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insert()
    virtual bool switchNodes(gcgLINK *node1, gcgLINK *node2) = 0;

    /// @brief Removes the entry from the data structure. The \a node must be part of the data structure.
    /// @param[in] node a pointer to a linkable node (gcgLINK) that carries the information to be removed from
    /// the data structure. It is generally an object of a specialization of gcgLINK that carries
    /// the information to be removed. The removed node is NOT deleted.
    /// @return true if \a node is correctly removed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insert()
    virtual bool remove(gcgLINK *node) = 0;
};




////////////////////////////////////////////////////////////////////////////////
/// @brief Generic abstract class for defining an extended node for use in
/// ordered data strucutures like gcgORDEREDSTRUCTURE. It can be used with several
/// classes in GCGlib, including those where nodes need to be comparated,
/// enumerated and ordered. This is intended for use in more sophisticated versions
/// of lists, maps and trees. Specialized objects of this class may be returned by
/// gcgITERATOR objects obtained from the data structures. Since it inherits from
/// gcgLINK and gcgDOUBLELINK, gcgNODE objects can also be used with linear data
/// structures with gcgLISTSTRUCTURE.
///
/// @since 0.02.113
////////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgNODE  :  public gcgDOUBLELINK {
  public:
    union {
      signed char status;   ///< Sequence of bits used to keep node information. It is dependent on the underlying data structure. Internal use only.
	    signed char balance;  ///< Version addressed by AVL trees
    };
};


//////////////////////////////////////////////////////////////////////////////
/// @brief Base abstract class for defining a hierachical data structure in
/// GCGlib. It indicates the minimum methods that all data structures with
/// ordered elements must provide. Note that some data structures might provide
/// other interfaces to handle their elements. This interface is different than
/// gcgSEQUENTIALSTRUCTURE where the elements can be positioned anywhere in the
/// data strucuture.
///
/// @since 0.02.113
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgORDEREDSTRUCTURE   :  public gcgDATASTRUCTURE {
  public:
    /// @brief Inserts a new entry \a newnode in the data structure. The unicity of the nodes depends on
    /// the data structure. If the data structure only works for unique nodes, they must be
    /// mutually different in respect to gcgORDEREDSTRUCTURE::compare() method. Note that this restriction
    /// can be easily broken by adapting the gcgORDEREDSTRUCTURE::compare() method.
    /// @param[in] newnode a pointer to a comparable node (gcgNODE) to be inserted in the data structure.
    /// It is generally an object of a specialization of gcgNODE that carries the node information. In data
    /// structures that require unique nodes, if a similar node is already in the data structure (the
    /// gcgORDEREDSTRUCTURE::compare() method returns zero for an existing node), it returns the pointer of the
    /// node in the data structure. The insertion operation might call the gcgORDEREDSTRUCTURE::compare() method
    /// several times to correctly position the new node.
    /// @return if \a newnode is similar to an existing node of the data structure that require node unicity
    /// (the gcgORDEREDSTRUCTURE::compare() method returns zero for an existing node), the method returns the
    /// pointer of that node. If \a newnode is correctly inserted, it returns the pointer \a newnode. If it
    /// returns NULL, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see compare()
    /// @see remove()
    /// @see search()
    virtual gcgNODE *insert(gcgNODE *newnode) = 0;

    /// @brief Retrieves the entry of the data structure that is similar to the \a key in respect to the
    /// gcgORDEREDSTRUCTURE::compare() method. The gcgORDEREDSTRUCTURE::compare() method returns zero only for similar
    /// nodes of the data structure. If multiple nodes in the data structure are similar to \a key, then the
    /// gcgORDEREDSTRUCTURE::search() will return the first node found. Some data structures require the nodes to
    /// be unique.
    /// @param[in] key a pointer to a comparable node (gcgNODE) that carries the information to be searched
    /// in the data structure. It is generally an object of a specialization of gcgNODE that carries the
    /// requested information. If a similar node is in the data structure (the gcgORDEREDSTRUCTURE::compare() method returns
    /// zero for an existing node), it returns the pointer of that node. The search operation might call the
    /// gcgORDEREDSTRUCTURE::compare() method several times to retrieve the node.
    /// @return if \a key is similar to an existing node of the data structure (the gcgORDEREDSTRUCTURE::compare()
    /// method returns zero for an existing node), the method returns the pointer of that node. If multiple nodes
    /// are similar to \a key, then the first node found is returned. If a similar node was not found or an error occured,
    /// it returns NULL. Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insert()
    /// @see remove()
    /// @see compare()
    virtual gcgNODE *search(gcgNODE *key) = 0;

    /// @brief Removes the entry of the data structure that is similar to the \a key in respect to the
    /// gcgAVLTREE::compare() method. The gcgORDEREDSTRUCTURE::compare() method returns zero only for similar nodes
    /// node in the data structure. If multiple nodes are similar to \a key, then the first found is removed. Some
    /// data structures require the nodes to be unique.
    /// @param[in] key a pointer to a comparable node (gcgNODE) that carries the information to be found
    /// and removed from the data structure. It is generally an object of a specialization of gcgNODE that carries
    /// the information to be removed. If a similar node is found in the data structure (the gcgORDEREDSTRUCTURE::compare()
    /// method returns zero for an existing node), that node is removed from the data structure and returned. The
    /// removed node is NOT deleted. The remove operation might call the gcgORDEREDSTRUCTURE::compare() method several
    /// times to find the node before its removal.
    /// @return if \a newnode is similar to an existing node of the data strucuture (the gcgORDEREDSTRUCTURE::compare()
    /// method returns zero for an existing node), the method removes that node from the data structure and returns
    /// its pointer. The node is NOT deleted by the method. If multiple nodes are similar to \a key, then the first
    /// found is removed and returned. If a similar node was not found or an error occured, it returns NULL. Check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insert()
    /// @see search()
    /// @see compare()
    virtual gcgNODE *remove(gcgNODE *key) = 0;

    /// @brief Method responsible for comparing two gcgNODE nodes. This is necessary for operations of insertion,
    /// retrieval and removal of several data structures. It must compare the two nodes pointed by \a refnode1 and
    /// \a refnode2 and return zero if they are equal, -1 if \a refnode1 is smaller or precedes \a refnode2, or
    /// 1 if \a refnode1 is grater or succeeds \a refnode2.
    /// @param[in] refnode1 pointer to a gcgNODE, generally specialized, object that must
    /// be compared with \a refnode2.
    /// @param[in] refnode2 pointer to a gcgNODE, generally specialized, object that must
    /// be compared with \a refnode1.
    /// @return It must compare the two nodes pointed by \a refnode1 and \a refnode2
    /// and return zero if they are equal, a negative integer if \a refnode1 is smaller or precedes
    /// \a refnode2, or a positive integer if \a refnode1 is grater or succeeds \a refnode2..
    /// @see insert()
    /// @see remove()
    /// @see search()
    virtual int compare(gcgNODE *refnode1, gcgNODE *refnode2) = 0;
};





/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////  SPECIFIC DATA STRUCTURES: macros, classes, and functions //////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
/// @brief Defines a fast single linked list. This is a standard data structure
/// that may be used with Last-In-First-Out policies. Use it if you need O(1)
/// time costs for insertions and deletions in the head and tail, but can afford
/// O(n) for searching from first to last element. It cannot iterate from last
/// to first element as gcgDOUBLELINKEDLIST does. A drawback of using linked lists
/// is their tendency to fragment memory and have low cache hits during searchs.
/// These problems can be avoided using arrays. Use the gcgLINKEDLIST::getIterator()
/// method to obtain an iterator for the list from head to tail elements. Try
/// gcgQUEUE if you need exclusive accesses in enqueue and dequeue operations.
///
/// @since 0.02.133
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgLINKEDLIST   :  public gcgLISTSTRUCTURE {
  public:
    gcgLINK       *first;   ///< Points to the first gcgLINK node in the list. Read-only.
    gcgLINK       *last;    ///< Points to the last gcgLINK node in the list. Read-only.
    unsigned int  counter;  ///< Number of elements in this list. Read-only.

  public:
    /// @brief Constructs a valid and empty linked list.
    /// @see insertFirst()
    /// @see insertLast()
    /// @see remove()
    /// @see gcgLINK
    gcgLINKEDLIST();

    /// @brief Destroys the linked list, releasing the list of nodes. All entries are deleted.
    /// @see insertFirst()
    /// @see insertLast()
    /// @see dequeueHead()
    /// @see dequeueTail()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    virtual ~gcgLINKEDLIST();

    // gcgLINKEDLIST specific methods

    /// @brief Returns the first entry stored in the linked list. The entry is
    /// removed from the top of the list. This is a O(1) operation.
    /// @return returns the pointer of the head entry. If it returns NULL, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see insertLast()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    gcgLINK *dequeueFirst();


    /// @brief Returns the last entry stored in the linked list. The entry is
    /// removed from the end of the list. This is a O(n) operation because the
    /// list is single linked.
    /// @return returns the pointer of the tail entry. If it returns NULL, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see insertLast()
    /// @see dequeueFirst()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    gcgLINK *dequeueLast();

    // gcgDATASTRUCTURE interface

    /// @brief Returns the number of elements stored in the list.
    /// @return Returns the number of elements currently in the list.
    unsigned int getCounter();

    /// @brief Deletes and removes all entries from the linked list. All list resources are also released.
    /// @return Returns true if all entries were deleted and removed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see detach()
    bool deleteAll();

    /// @brief Returns an iterator for traversing the nodes of the linked list. The linked list
    /// must not be changed by insertions, removals or moves while the iterator is being used. You must delete
    /// the returned iterator after use. The iterator copies a minimal information from the data structure. Note
    /// that deleting a iterator does not affect the nodes. The traversal order for this data structure is from
    /// head to tail elements (\a traversemode is ignored).
    /// @param traversemode Specifies the order that the available elements in the list must
    /// be traversed. Currently this parameter is ignored and the iterator spans the list from the head to
    /// tail nodes.
    /// @return Returns an iterator for traversing the list from head to tail nodes. The list
    /// must not be changed by insertions, removals or moves while the iterator is being used. You MUST delete
    /// the returned gcgITERATOR object after use. If it returns NULL, check GCG_REPORT_MESSAGE(gcgGetReport())
    /// for knowing the problem.
    /// @see detach()
    gcgITERATOR *getIterator(int traversemode = 0);

    /// @brief Force the list to be empty. It has the same effect as removing all entries from the
    /// linked list but keeping their chaining (which will used by the returned iterator). The nodes are NOT
    /// deleted. In order to retrieve the detached nodes, a gcgITERATOR is returned. This is useful to process the nodes
    /// freely and without the possible restrictions of the underlying data strucuture. Thus, the gcgITERATOR returned
    /// by gcgLINKEDLIST::detach() MUST be used to delete all the nodes or reinsert them into another data structure.
    /// The traversal order of the iterator is defined by the parameter \a traversemode. Currently, the traversal order
    /// for this data structure is from head to tail elements (\a traversemode is ignored). All resources currently used
    ///  by the gcgLINKEDLIST are released (becomes empty) but it can be reused normally.
    /// You must delete the gcgITERATOR after its use.
    /// @param traversemode Specifies the order that the available elements in the list must
    /// be traversed by the returned iterator. Currently this parameter is ignored and the iterator spans the list
    /// from the head to tail nodes.
    /// @return Returns an iterator for traversing the elements that were detached from the linked list. The
    /// linked list becomes empty and can be reused. You MUST delete the returned gcgITERATOR object
    /// after use. If it returns NULL, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see deleteAll()
    /// @see getIterator()
    gcgITERATOR *detach(int traversemode = 0);

    // gcgSEQUENTIALSTRUCTURE interface

    /// @brief Inserts a new entry \a node at the HEAD of the list. This is a O(1) operation.
    /// @param[in] node a pointer to a linkable instance (gcgLINK) to be held in the new queue entry.
    /// This pointer is deleted by the destructor or deleteAll(). A NULL value generates an error.
    /// @return returns true if the data is successfully inserted at the top of the queue. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertLast()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    bool insertFirst(gcgLINK *node);

    /// @brief Inserts a new entry \a node at the TAIL of the list. This is a O(1) operation.
    /// @param[in] node a pointer to a linkable instance (gcgLINK) to be inserted in the linked list's tail.
    /// This pointer is deleted by the destructor or a deleteAll() call. A NULL value generates an error.
    /// @return returns true if the data is successfully inserted at the end of the linked list. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    bool insertLast(gcgLINK *node);

    /// @brief Inserts a new entry \a newnode in the list, after an existent entry pointed by \a node.
    /// This is a O(1) operation.
    /// @param[in] newnode a pointer to a linkable instance (gcgLINK) to be inserted after \a node.
    /// This pointer is deleted by the destructor or a deleteAll() call. A NULL value generates an error.
    /// @param[in] node a pointer to an entry that is already linked in the list. A NULL value
    /// has the same effect as \a insertLast(\a newnode). After the insertion, the \a newnode will
    /// follow the \a node in the list: node->next = newnode and newnode->previous = node.
    /// @return returns true if the data is successfully inserted after \a node. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertLast()
    /// @see insertBefore()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see remove()
    bool insertAfter(gcgLINK *newnode, gcgLINK *node);

    /// @brief Inserts a new entry \a newnode in the list, before an existent entry pointed by \a node.
    /// This is a O(n) operation because the list is single linked.
    /// @param[in] newnode a pointer to a linkable instance (gcgLINK) to be inserted after \a node.
    /// This pointer is deleted by the destructor or a deleteAll() call. A NULL value generates an error.
    /// @param[in] node a pointer to an entry that is already linked in the list. A NULL value
    /// has the same effect as \a insertFirst(\a newnode). After the insertion, the \a node will
    /// follow the \a newnode in the list: newnode->next = node and node->previous = newnode.
    /// @return returns true if the data is successfully inserted after \a node. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see insertAfter()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see remove()
    bool insertBefore(gcgLINK *newnode, gcgLINK *node);

    /// @brief Move an entry \a node that is already in the list to its first position.
    /// This is a O(n) operation because the list is single linked.
    /// @param[in] node a pointer to a linkable instance (gcgLINK) that is already in the list.
    /// A NULL value generates an error.
    /// @return returns true if the data is successfully moved to the beginning of the linked list. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    /// @see moveToLast()
    bool moveToFirst(gcgLINK *node);

    /// @brief Move an entry \a node that is already in the list to its last position.
    /// This is a O(n) operation because the list is single linked.
    /// @param[in] node a pointer to a linkable instance (gcgLINK) that is already in the list.
    /// A NULL value generates an error.
    /// @return returns true if the data is successfully moved to the end of the linked list. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    /// @see moveToFirst()
    bool moveToLast(gcgLINK *node);

    /// @brief Switches the position of two existent elements of the linked list. The two nodes
    /// must be part of the list. This is a O(n) operation because the list is single linked.
    /// @param[in] node1 a pointer to a linkable node (gcgLINK) that carries the information to be switched with
    /// the position of \a node2. If NULL, an error occurs.
    /// @param[in] node2 a pointer to a linkable node (gcgLINK) that carries the information to be switched with
    /// the position of \a node1. If NULL, an error occurs.
    /// @return true if the nodes are correctly switched. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insert()
    bool switchNodes(gcgLINK *node1, gcgLINK *node2);

    /// @brief Removes an entry \a node from the linked list. The node is not deleted.
    /// This is a O(n) operation because the list is single linked.
    /// @param[in] node a pointer to a linkable instance (gcgLINK) to be removed from the list.
    /// The node must be an element of this list. A NULL value generates an error.
    /// @return returns true if the data is successfully removed from the list. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see insertLast()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    bool remove(gcgLINK *node);
};




/////////////////////////////////////////////////////////////////////////////
/// @brief Defines a fast double linked list. This is a standard data structure
/// that may be used with First-In-First-Out or Last-In-First-Out policies. Use
/// it if you need O(1) time costs for insertions and deletions at head and tail,
/// but can afford O(n) for searching. You must use gcgDOUBLELINK or its
/// specializations in all methods. A drawback of using linked lists is their
/// tendency to fragment memory and have low cache hits during searchs. These
/// problems can be avoided using arrays. This class can iterate from first to
/// last element and vice-versa. Use the gcgDOUBLELINKEDLIST::getIterator()
/// method to obtain an iterator for the list to span the nodes from head to tail
/// or vice-versa. Use gcgLINKEDLIST if you need a simpler single linked lists.
///
/// @since 0.02.113
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgDOUBLELINKEDLIST   :  public gcgLISTSTRUCTURE {
  public:
    gcgLINK       *first;   ///< Points to the first gcgLINK node in the list. Read-only.
    gcgLINK       *last;    ///< Points to the last gcgLINK node in the list. Read-only.
    unsigned int  counter;  ///< Number of elements in this list. Read-only.

  public:
    /// @brief Constructs a valid and empty linked list.
    /// @see insertFirst()
    /// @see insertLast()
    /// @see remove()
    /// @see gcgLINK
    gcgDOUBLELINKEDLIST();

    /// @brief Destroys the linked list, releasing the list of nodes. All entries are deleted.
    /// @see insertFirst()
    /// @see insertLast()
    /// @see dequeueHead()
    /// @see dequeueTail()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    virtual ~gcgDOUBLELINKEDLIST();

    // gcgDOUBLELINKEDLIST specific methods

    /// @brief Returns the first entry stored in the linked list. The entry is
    /// removed from the top of the list. This is a O(1) operation.
    /// @return returns the pointer of the head entry. If it returns NULL, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see insertLast()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    gcgLINK *dequeueFirst();


    /// @brief Returns the last entry stored in the linked list. The entry is
    /// removed from the end of the list. This is a O(1) operation.
    /// @return returns the pointer of the tail entry. If it returns NULL, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see insertLast()
    /// @see dequeueFirst()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    gcgLINK *dequeueLast();

    // gcgDATASTRUCTURE interface

    /// @brief Returns the number of elements stored in the list.
    /// @return Returns the number of elements currently in the list.
    unsigned int getCounter();

    /// @brief Deletes and removes all entries from the linked list. All list resources are also released.
    /// @return Returns true if all entries were deleted and removed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see detach()
    bool deleteAll();

    /// @brief Returns an iterator for traversing the nodes of the linked list. The traversal order is
    /// defined by the parameter \a traversemode. Currently, there are two modes implemented:
    /// \a traversemode = 0, for head to tail iteration (default); and \a traversemode = 1, to iterate from tail to head.
    /// The linked list must not be changed by insertions, removals or moves while the iterator is being used. You must delete
    /// the returned iterator after use. The iterator copies a minimal information from the data structure. Note
    /// that deleting a iterator does not affect the nodes.
    /// @param traversemode Specifies the order that the available elements in the list must
    /// be traversed. Currently, there are two modes implemented: \a traversemode = 0, for head to tail iteration
    /// (default); and \a traversemode = 1, to iterate from tail to head.
    /// @return Returns an iterator for traversing the list from head to tail nodes in the order defined by
    /// \a traversemode. The list must not be changed by insertions, removals or moves while the iterator
    /// is being used. You MUST delete the returned gcgITERATOR object after use. If it returns NULL,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see detach()
    gcgITERATOR *getIterator(int traversemode = 0);

    /// @brief Force the list to be empty. It has the same effect as removing all entries from the
    /// linked list but keeping their chaining (which will used by the returned iterator). The nodes are NOT
    /// deleted. In order to retrieve the detached nodes, a gcgITERATOR is returned. This is useful to process the nodes
    /// freely and without the possible restrictions of the underlying data strucuture. Thus, the gcgITERATOR returned
    /// by gcgDOUBLELINKEDLIST::detach() MUST be used to delete all the nodes or reinsert them in another data structure.
    /// The traversal order of the returned iterator is defined by the parameter \a traversemode. Currently, there are two modes
    /// implemented: \a traversemode = 0, for head to tail iteration (default); and \a traversemode = 1, to iterate from tail to head.
    /// All resources currently used by the gcgDOUBLELINKEDLIST are released (becomes empty) but it can be reused normally.
    /// You must delete the gcgITERATOR after its use.
    /// @param traversemode Specifies the order that the available elements in the list must be traversed by the returned
    /// iterator. Currently, there are two modes implemented: \a traversemode = 0, for head to tail iteration
    /// (default); and \a traversemode = 1, to iterate from tail to head.
    /// @return Returns a iterator for traversing the elements that were detached from the linked list. The
    /// linked list becomes empty and can be reused. You MUST delete the returned gcgITERATOR object
    /// after use. If it returns NULL, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see deleteAll()
    /// @see getIterator()
    gcgITERATOR *detach(int traversemode = 0);


    // gcgSEQUENTIALSTRUCTURE interface

    /// @brief Inserts a new entry \a node at the HEAD of the list. The node will have a NULL \a left/previous link.
    /// @param[in] node a pointer to a linkable instance (gcgDOUBLELINK) to be held in the new queue entry.
    /// This pointer is deleted by the destructor or deleteAll(). A NULL value generates an error. This is a
    /// O(1) operation.
    /// @return returns true if the data is successfully inserted at the top of the queue. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertLast()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    bool insertFirst(gcgLINK *node);

    /// @brief Inserts a new entry \a node at the TAIL of the list. The node will have a NULL \a right/next link.
    /// @param[in] node a pointer to a linkable instance (gcgDOUBLELINK) to be inserted in the linked list's tail.
    /// This pointer is deleted by the destructor or a deleteAll() call. A NULL value generates an error.
    /// This is a O(1) operation.
    /// @return returns true if the data is successfully inserted at the end of the linked list. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    bool insertLast(gcgLINK *node);

    /// @brief Inserts a new entry \a newnode in the list, after an existent entry pointed by \a node.
    /// This is a O(1) operation.
    /// @param[in] newnode a pointer to a linkable instance (gcgDOUBLELINK) to be inserted after \a node.
    /// This pointer is deleted by the destructor or a deleteAll() call. A NULL value generates an error.
    /// @param[in] node a pointer to an gcgDOUBLELINK entry that is already linked in the list. A NULL value
    /// has the same effect as \a insertLast(\a newnode). After the insertion, the \a newnode will
    /// follow the \a node in the list: node->next = newnode and newnode->previous = node.
    /// @return returns true if the data is successfully inserted after \a node. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertLast()
    /// @see insertBefore()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see remove()
    bool insertAfter(gcgLINK *newnode, gcgLINK *node);

    /// @brief Inserts a new entry \a newnode in the list, before an existent entry pointed by \a node.
    /// This is a O(1) operation.
    /// @param[in] newnode a pointer to a linkable instance (gcgDOUBLELINK) to be inserted after \a node.
    /// This pointer is deleted by the destructor or a deleteAll() call. A NULL value generates an error.
    /// @param[in] node a pointer to a gcgDOUBLELINK entry that is already linked in the list. A NULL value
    /// has the same effect as \a insertFirst(\a newnode). After the insertion, the \a node will
    /// follow the \a newnode in the list: newnode->next = node and node->previous = newnode.
    /// @return returns true if the data is successfully inserted after \a node. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see insertAfter()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see remove()
    bool insertBefore(gcgLINK *newnode, gcgLINK *node);

    /// @brief Move an entry \a node that is already in the list to its first position. The node
    /// will have a NULL \a previous link. This is a O(1) operation.
    /// @param[in] node a pointer to a linkable instance (gcgDOUBLELINK) that is already in the list.
    /// A NULL value generates an error.
    /// @return returns true if the data is successfully moved to the beginning of the linked list. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    /// @see moveToLast()
    bool moveToFirst(gcgLINK *node);

    /// @brief Move an entry \a node that is already in the list to its last position. The node will
    /// have a NULL \a next link. This is a O(1) operation.
    /// @param[in] node a pointer to a linkable instance (gcgDOUBLELINK) that is already in the list.
    /// A NULL value generates an error.
    /// @return returns true if the data is successfully moved to the end of the linked list. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    /// @see remove()
    /// @see moveToFirst()
    bool moveToLast(gcgLINK *node);

    /// @brief Switches the position of two existent elements of the linked list. The two nodes
    /// must be part of the list. This is a O(1) operation.
    /// @param[in] node1 a pointer to a linkable node (gcgDOUBLELINK) that carries the information to be switched with
    /// the position of \a node2. If NULL, an error occurs.
    /// @param[in] node2 a pointer to a linkable node (gcgDOUBLELINK) that carries the information to be switched with
    /// the position of \a node1. If NULL, an error occurs.
    /// @return true if the nodes are correctly switched. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insert()
    bool switchNodes(gcgLINK *node1, gcgLINK *node2);

    /// @brief Removes an entry \a node from the linked list. The node is not deleted. This is a O(1) operation.
    /// @param[in] node a pointer to a linkable instance (gcgDOUBLELINK) to be removed from the list.
    /// The node must be an element of this list. A NULL value generates an error.
    /// @return returns true if the data is successfully removed from the list. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertFirst()
    /// @see insertLast()
    /// @see dequeueFirst()
    /// @see dequeueLast()
    /// @see insertAfter()
    /// @see insertBefore()
    bool remove(gcgLINK *node);
};



////////////////////////////////////////////////////////////////////////////////
/// @brief Generic abstract class to manage a AVL tree. AVL tree is a self
/// balancing data structure that keeps a binary tree almost balanced. It has
/// the restriction that all nodes have chidren with, at most, one level of
/// difference between them. This constraint is stronger than those of the
/// red-black trees and, as such, the cost for balance maintenance is higher.
/// It has O(log n) complexity for searchs, insertions and deletions. The delete
/// operator has a constant multiplier higher than insertions. The height of an
/// AVL tree is stricly less than 1.44 log(n + 2) - 0.328. It is more rigidly
/// balanced than red-black trees leading to slower insertion and removals but
/// slightly faster searchs. The nodes in this tree must be comparable. As such,
/// a class specialization must provide gcgAVLTREE::compare() method that has
/// the function of determining if two gcgNODE nodes are equal, greater
/// or smaller. Use the gcgAVLTREE::getIterator() to obtain a fast
/// iterator to traverse the AVL nodes in ascending or descending order.
///
/// @since 0.02.113
////////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgAVLTREE   :  public gcgORDEREDSTRUCTURE {
  public:
	  gcgNODE       *root;    ///< Root node of the AVL tree. Read-only.
    unsigned int  counter;  ///< Number of elements in this tree. Read-only.

  private:
	  struct _AVL_LEVEL_PATH  *path;
	  int                     levels;
	  int                     maxlevels;

  public:
    /// @brief Constructs a valid and empty AVL tree.
    /// @see ~gcgAVLTREE
    gcgAVLTREE();

    /// @brief Destroys the AVL tree, releasing all nodes. All entries are deleted.
    /// @see gcgAVLTREE
    virtual ~gcgAVLTREE();

    // gcgORDEREDSTRUCTURE interface

    /// @brief Inserts a new entry \a newnode in the AVL tree. The tree is adjusted to keep the
    /// restriction that both children of all nodes must have heights differing of at most one level. Insertions
    /// take O(log n) operations to be finished. At most one tree rotation is performed. All nodes in the tree
    /// must be unique, i.e., they are mutually different in respect to gcgNODE::compare() method.
    /// @param[in] newnode a pointer to a comparable node (gcgNODE) to be inserted in the AVL tree.
    /// It is generally an object of a specialization of gcgNODE that carries the node information.
    /// If a similar node is already in the tree (the gcgAVLTREE::compare() method returns zero for an existing
    /// node), it returns the pointer of the node in the tree. The insertion operation might call the
    /// gcgAVLTREE::compare() method  several times to correctly position the new node.
    /// @return if \a newnode is similar to an existing node of the tree (the gcgAVLTREE::compare()
    /// method returns zero for an existing node), the method returns the pointer of that node. If \a
    /// newnode is correctly inserted, it returns the pointer \a newnode. If it returns NULL, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see compare()
    /// @see remove()
    /// @see search()
    gcgNODE *insert(gcgNODE *newnode);

    /// @brief Retrieves the entry of the AVL tree that is similar to the \a key in respect to the
    /// gcgAVLTREE::compare() method. The gcgAVLTREE::compare() method must return zero only for an unique
    /// node of the tree. AVL searchs take O(log n) operations to be finished and are slighly more efficient
    /// than in red-black trees.
    /// @param[in] key a pointer to a comparable node (gcgNODE) that carries the information to be searched
    /// in the AVL tree. It is generally an object of a specialization of gcgNODE that carries the
    /// requested information. If a similar node is in the tree (the gcgAVLTREE::compare() method returns zero for an
    /// existing node), it returns the pointer of that node. The search operation might call the gcgAVLTREE::compare()
    /// method several times to retrieve the node.
    /// @return if \a key is similar to an existing node of the tree (the gcgAVLTREE::compare()
    /// method returns zero for an existing node), the method returns the pointer of that node. If a
    /// similar node was not found or an error occured, it returns NULL. Check GCG_REPORT_MESSAGE(gcgGetReport()) for
    /// knowing the problem.
    /// @see insert()
    /// @see remove()
    /// @see compare()
    gcgNODE *search(gcgNODE *key);

    /// @brief Removes the entry of the AVL tree that is similar to the \a key in respect to the
    /// gcgAVLTREE::compare() method. The gcgAVLTREE::compare() method must return zero only for an unique
    /// node of the tree. The tree is adjusted to keep the restriction that both children of all nodes must
    /// have heights differing of at most one level. Removals take O(log n) operations to be finished. More than one
    /// tree rotation can be performed, which means that this operation has generally a greater time cost in
    /// comparison with insertion and search operations.
    /// @param[in] key a pointer to a comparable node (gcgNODE) that carries the information to be found
    /// and removed from the AVL tree. It is generally an object of a specialization of gcgNODE that carries
    /// the information to be removed. If a similar node is in the tree (the gcgAVLTREE::compare() method returns zero
    /// for an existing node), that node is removed from the AVL tree and returned. The removed node is NOT deleted.
    /// The remove operation might call the gcgAVLTREE::compare() method several times to find the node before its removal.
    /// @return if \a newnode is similar to an existing node of the tree (the gcgAVLTREE::compare()
    /// method returns zero for an existing node), the method removes that node from the AVL tree and returns its pointer.
    /// The node is NOT deleted by the method. If a similar node was not found or an error occured, it returns NULL.
    /// Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insert()
    /// @see search()
    /// @see compare()
    gcgNODE *remove(gcgNODE *key);

    // gcgDATASTRUCTURE interface

    /// @brief Returns the number of elements stored in the AVL tree.
    /// @return Returns the number of elements currently stored in the AVL tree.
    /// @see insert()
    /// @see remove()
    unsigned int getCounter();

    /// @brief Deletes and removes all entries from the AVL tree. All AVL tree resources are also released.
    /// @return Returns true if all entries were deleted and removed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see detach()
    virtual bool deleteAll();

    /// @brief Returns an iterator for traversing the elements of the AVL tree in ascending order. The traversal order is
    /// defined by the parameter \a traversemode. Currently, the tree nodes can be traversed in two ways:
    /// \a traversemode = 0, to iterate in ascending order (default); and \a traversemode = 1, to iterate in
    /// descending order. The AVL tree must not be changed by insertions, removals or moves while the iterator is being
    /// used. You must delete the returned iterator after use. The iterator copies a minimal information from the AVL
    /// tree. Note that deleting a iterator does not affect the nodes.
    /// @param traversemode Specifies the order that the available elements in the AVL tree must be traversed.
    /// Currently, the tree nodes can be traversed in two ways:  \a traversemode = 0, to iterate in ascending order
    /// (default); and \a traversemode = 1, to iterate in descending order.
    /// @return Returns an iterator for traversing the tree in the order specified by \a traversemode. The AVL tree
    /// must not be changed by insertions, removals or moves while the iterator is being used. You MUST delete
    /// the returned gcgITERATOR object after use. If it returns NULL, check GCG_REPORT_MESSAGE(gcgGetReport())
    /// for knowing the problem.
    /// @see detach()
    gcgITERATOR *getIterator(int traversemode = 0);

    /// @brief Force the AVL tree to be empty. It has the same effect as removing all entries from the
    /// AVL tree but keeping their chaining (which will used by the returned iterator). The entries are NOT
    /// deleted. In order to retrieve the detached entries, a gcgITERATOR is returned. This is useful to process the nodes
    /// freely and without the possible restrictions of the underlying AVL tree. Thus, the gcgITERATOR returned
    /// by gcgAVLTREE::detach() MUST be used to delete all the entries or reinsert them in another data structure.
    /// The traversal order of the returned iterator is defined by the parameter \a traversemode. Currently, the tree
    /// nodes can be traversed in two ways:  \a traversemode = 0, to iterate in ascending order (default); and \a
    /// traversemode = 1, to iterate in descending order. All resources currently used by the AVL tree are released
    /// (becomes empty) but it can be reused normally. You must delete the gcgITERATOR after its use.
    /// @param traversemode Specifies the order that the available elements in the AVL tree must be traversed by the returned
    /// iterator. Currently, the tree nodes can be traversed in two ways:  \a traversemode = 0, to iterate in ascending
    /// order (default); and \a traversemode = 1, to iterate in descending order.
    /// @return Returns an iterator for traversing the elements that were detached from the AVL tree. The
    /// AVL tree becomes empty and can be reused. You MUST delete the returned gcgITERATOR object
    /// after use. If it returns NULL, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see deleteAll()
    /// @see getIterator()
    gcgITERATOR *detach(int traversemode = 0);

    /// @brief Method that must be furnished by a specialization of gcgAVLTREE and is responsible for
    /// comparing two gcgNODE nodes. This is necessary for all tree operations of insertion,
    /// retrieval and removal. It must compare the two nodes pointed by \a refnode1 and \a refnode2
    /// and return zero if they are equal, -1 if \a refnode1 is smaller or precedes \a refnode2, or
    /// 1 if \a refnode1 is grater or succeeds \a refnode2. This method is also required by the
    /// base class gcgORDEREDSTRUCTURE.
    /// @param[in] refnode1 pointer to a gcgNODE, generally specialized, object that must
    /// be compared with \a refnode2.
    /// @param[in] refnode2 pointer to a gcgNODE, generally specialized, object that must
    /// be compared with \a refnode1.
    /// @return It must compare the two nodes pointed by \a refnode1 and \a refnode2
    /// and return zero if they are equal, a negative integer if \a refnode1 is smaller or precedes
    /// \a refnode2, or a positive integer if \a refnode1 is grater or succeeds \a refnode2.
    /// @see insert()
    /// @see remove()
    /// @see search()
    virtual int compare(gcgNODE *refnode1, gcgNODE *refnode2) = 0;
};


////////////////////////////////////////////////////////////////////////////////
/// @brief Generic abstract class to manage a hash table. A hash table is
/// a data structure that organizes the node into several buckets, according
/// to a hash function. The number of buckets, or table's capacity, can be
/// adjusted anytime and is closely related to the table performance. If well
/// defined, the hash table is capable of O(1) searchs. This class provides
/// self adjusting loads: number of elements / number of buckets. The minimum
/// load is checked whenever a node is removed. It is useful to define how
/// many buckets (if any) are allowed to be free, waiting to be populated.
/// The maximum load is checked whenever a node is inserted in the table.
/// It is useful to limit the maximum number of elements per bucket, in
/// average. The performance of the hash table during insertions, deletes,
/// and searchs are strongly dependent on the gcgHASHTABLE::hash() method.
/// To solve the unavoidable collisions, fast data structures are used for
/// each bucket. The nodes in this table must be comparable. As such,
/// a class specialization must provide gcgHASHTABLE::compare() method that has
/// the function of determining if two gcgNODE nodes are equal, greater
/// or smaller. Use the gcgHASHTABLE::getIterator() to obtain a fast
/// iterator to traverse all table entries.
///
/// @since 0.02.113
////////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgHASHTABLE   :  public gcgORDEREDSTRUCTURE {
  public:
    unsigned int  counter;      ///< Number of elements in this table. Read-only.
    unsigned int  capacity;     ///< Capacity of this table or maximum number of elements of the table without collisions. Read-only.
    float         minimumload;  ///< Minimum load of this table. The table capacity will be adjusted to this minimum counter/capacity ratio. Read-only.
    float         maximumload;  ///< Maximum load of this table. The table capacity will be adjusted to this maximum counter/capacity ratio. Read-only.
    gcgCLASS      **table;      ///< Table of data strutures. Internal use only.

  public:
    /// @brief Constructs a valid hash table. All the parameters of the constructor are crucial for table performance.
    /// @param[in] capacity Initial number of buckets of the hash table. Note that the capacity will
    /// possibly be changed by the first call to gcgHASHTABLE::insert() if the \a maxload is positive.
    /// @param[in] minload Minimum load (counter/capacity ratio) that the table must keep after removals. if \a minload
    /// is positive, when a node is removed, the current load is checked against \a minload. If current load is lesser,
    /// the table's capacity is reduced to keep minimum load valid. If negative or zero, no minimum value is defined and the
    /// table's capacity is not affected by removals. It must be smaller than \a maxload.
    /// @param[in] maxload Maximum load (counter/capacity ratio) that the table must keep after insertions. if \a maxload
    /// is positive, when a node is inserted, the current load is checked against \a maxload. If current load is greater,
    /// the table's capacity is augmented to keep maximum load valid. If negative or zero, no maximum value is defined and the
    /// table's capacity is not affected by insertions. It must be greater than \a minload.
    /// @see setCapacity
    /// @see setLoadLimits
    /// @see ~gcgHASHTABLE
    gcgHASHTABLE(unsigned int capacity = 0, float minload = 0.8, float maxload = 16.0);

    /// @brief Destroys the hash table, releasing all nodes. All entries are deleted.
    /// @see gcgHASHTABLE
    virtual ~gcgHASHTABLE();

    // gcgHASHTABLE specific methods

    /// @brief Sets the number of buckets of the table. If the table is already populated with nodes, it adjusts
    /// the table to the new capacity. If \a capacity is zero and the table is not populated, all hash table resources
    /// are released. If \a capacity is zero and the table is populated, a warning is issued.
    /// @param[in] capacity Number of buckets of the hash table. Note that the capacity will
    /// possibly be changed by the next call to gcgHASHTABLE::insert(), if the \a maxload is positive, or
    /// gcgHASHTABLE::remove(), if the \a minload is positive. If the table is already populated with nodes,
    /// the table is adjusted to the new capacity. If \a capacity is zero and the table is not populated, all
    /// hash table resources are released. If \a capacity is zero and the table is populated, a warning is issued.
    /// @return true if the capacity was correctly changed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setLoadLimits
    /// @see insert
    /// @see remove
    bool setCapacity(unsigned int capacity);

    /// @brief Sets the minimum and maximum loads that the table is allowed to have after removals and insertions,
    /// respectively. Minimum value must be smaller than maximum value and they must not be equal. If they are close
    /// to another, insertions and removals might become very inefficient because of frequent table capacity adjustments.
    /// If minimum and maximum loads are valid, the current load is checked against them. If outside the load interval,
    /// the capacity of the table is adjusted.
    /// @param[in] minload Minimum load (counter/capacity ratio) that the table must keep after removals. if \a minload
    /// is positive, when a node is removed, the current load is checked against \a minload. If current load is lesser,
    /// the table's capacity is reduced to keep minimum load valid. If negative or zero, no minimum value is defined
    /// and the table's capacity is not affected by removals. It must be smaller than \a maxload.
    /// @param[in] maxload Maximum load (counter/capacity ratio) that the table must keep after insertions. if \a maxload
    /// is positive, when a node is inserted, the current load is checked against \a maxload. If current load is greater,
    /// the table's capacity is augmented to keep maximum load valid. If negative or zero, no maximum value is defined
    /// and the table's capacity is not affected by insertions. It must be greater than \a minload.
    /// @return true if the limits were successfully changed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setCapacity
    /// @see insert
    /// @see remove
    bool setLoadLimits(float minload, float maxload);

    // gcgDATASTRUCTURE interface

    /// @brief Returns the number of elements stored in the hash table.
    /// @return Returns the number of elements currently stored in the hash table.
    /// @see insert()
    /// @see remove()
    unsigned int getCounter();

    /// @brief Deletes and removes all entries from the hash table. All resources used by the hash table
    /// are also released.
    /// @return Returns true if all entries were deleted and removed from the hash table. If it
    /// returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see detach()
    bool deleteAll();

    /// @brief Returns an iterator for traversing the elements of the hash table. The traversal order is
    /// defined by the parameter \a traversemode. Currently, the order of iteration depends on the
    /// internal data structure (AVL trees). The parameter \a traversemode is just passed to the secondary data structures
    /// whenever a sub-iterator is needed. The hash table must not be changed by insertions, removals or moves while the
    /// iterator is being used. You must delete the returned iterator after use. The iterator copies a minimal
    /// information from the internal hash table. Note that deleting an iterator does not affect the nodes.
    /// @param traversemode Specifies the order that the available elements in the hash table must
    /// be traversed. Currently, the order of iteration depends on the internal data structure (AVL trees).
    /// The parameter \a traversemode is just passed to the secondary data structures whenever a sub-iterator is needed.
    /// @return Returns an iterator for traversing the elements of the hash table. The traversal order in the
    /// internal secondary data structures is defined by \a traversemode. The hash table must not be changed
    /// by insertions, removals or moves while the iterator is being used. You MUST delete the returned gcgITERATOR
    /// object after use. If it returns NULL, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see detach()
    gcgITERATOR *getIterator(int traversemode = 0);

    /// @brief Force the hash table to be empty. It has the same effect as removing all entries from the
    /// hash table but keeping their chaining (which must be used by the returned iterator). The entries are NOT
    /// deleted. In order to retrieve the detached entries, a gcgITERATOR is returned. This is useful to process the nodes
    /// freely and without the possible restrictions of the underlying hash table. Thus, the gcgITERATOR returned
    /// by gcgHASHTABLE::detach() MUST be used to delete all the entries or reinsert them into another data structure.
    /// The traversal order of the returned iterator is defined by the parameter \a traversemode. Currently, the order
    /// of iteration depends on the internal data structure (AVL trees). The parameter \a traversemode is just passed to
    /// the secondary data structures. All resources currently used by the hash table are released (becomes empty) but it
    /// can be reused normally. You must delete the gcgITERATOR after its use.
    /// @param traversemode Specifies the order that the available elements in the hash table must
    /// be traversed by the returned iterator. Currently, the order of iteration depends on the internal data structure (AVL trees).
    /// The parameter \a traversemode is just passed to the secondary data structures.
    /// @return Returns an iterator for traversing the elements that were detached from the hash table. The
    /// hash table becomes empty and can be reused. You MUST delete the returned gcgITERATOR object
    /// after use. If it returns NULL, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see deleteAll()
    /// @see getIterator()
    gcgITERATOR *detach(int traversemode = 0);

    /// @brief Method that must be furnished by a specialization of gcgHASHTABLE and is responsible for
    /// computing an integer hash value for the node \a node. This is necessary for all operations of
    /// insertion, retrieval and removal. The performance of the hash table is highly dependent on
    /// the capacity of the gcgHASHTABLE::hash() method to spread distinct nodes over the long integer
    /// numbers.
    /// @param[in] node pointer to a gcgNODE, generally specialized, object that must have a hash value
    /// to be used in the table.
    /// @return It must return an integer number that represents the \a node. It generally makes some
    /// arithmetic with the contents of the object \a node. Better is the capacity of the hash function
    /// to spread distinct nodes over the long integers, better is the performance of the hash table.
    /// @see insert()
    /// @see remove()
    /// @see search()
    /// @see compare()
    virtual long hash(gcgNODE *node) = 0;

    // gcgORDEREDSTRUCTURE interface

    /// @brief Inserts a new entry \a newnode in the hash table. All nodes in the table must be unique, i.e.,
    /// they are mutually different in respect to gcgHASHTABLE::compare() method.
    /// @param[in] newnode a pointer to a comparable node (gcgNODE) to be inserted in the hash table.
    /// It is generally an object of a specialization of gcgNODE that carries the node information.
    /// If a similar node is already in the table (the gcgHASHTABLE::compare() method returns zero for an existing
    /// node), it returns the pointer of the node in the table. The insertion operation might call the
    /// gcgHASHTABLE::compare() method several times to correctly position the new node. The internal data
    /// structures are automatically adjusted after the removal. If a maximum value for table load is positive
    /// (see gcgHASHTABLE::setLoadLimits()), the current load is computed and checked against that maximum load. If
    /// the current load is greater, the table's capacity is augmented in order to put the current load in the valid
    /// interval. The method gcgHASHTABLE::hash() might be called several times to find an existing \a node and to
    /// adjust the table load.
    /// @return if \a newnode is similar to an existing node of the hash table (the gcgHASHTABLE::compare()
    /// method returns zero for an existing node), the method returns the pointer of that node. If \a
    /// newnode is correctly inserted, it returns the pointer \a newnode. If it returns NULL, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see compare()
    /// @see remove()
    /// @see search()
    gcgNODE *insert(gcgNODE *newnode);

    /// @brief Retrieves the entry of the hash table that is similar to the \a key in respect to the
    /// gcgHASHTABLE::compare() method. The gcgHASHTABLE::compare() method must return zero only for an unique
    /// node of the tree. The method gcgHASHTABLE::hash() is called once to find \a node's bucket.
    /// @param[in] key a pointer to a comparable node (gcgNODE) that carries the information to be searched
    /// in the hash table. It is generally an object of a specialization of gcgNODE that carries the
    /// requested information. If a similar node is in the table (the gcgHASHTABLE::compare() method returns zero for an
    /// existing node), it returns the pointer of that node. The search operation might call the gcgHASHTABLE::compare()
    /// method several times to retrieve the node.
    /// @return if \a key is similar to an existing node of the table (the gcgAVLTREE::compare()
    /// method returns zero), the method returns the pointer of that node. If a similar node was not found or an
    /// error occured, it returns NULL. Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insert()
    /// @see remove()
    /// @see compare()
    gcgNODE *search(gcgNODE *key);

    /// @brief Removes the entry of the hash table that is similar to the \a key in respect to the
    /// gcgHASHTABLE::compare() method. The gcgHASHTABLE::compare() method must return zero only for an unique
    /// node of the table. The internal data structures are automatically adjusted after the removal. If a minimum
    /// value for table load is positive (see gcgHASHTABLE::setLoadLimits()), the current load is computed and
    /// checked against that minimum load. If the current load is lesser, the table's capacity is reduced in order
    /// to put the current load in the valid interval. The method gcgHASHTABLE::hash() might be called several times
    /// to find \a node and to adjust the table load.
    /// @param[in] key a pointer to a comparable node (gcgNODE) that carries the information to be found
    /// and removed from the hash table. It is generally an object of a specialization of gcgNODE that carries
    /// the information to be removed. If a similar node is in the table (the gcgHASHTABLE::compare() method returns
    /// zero for an existing node), that node is removed from the hash table and returned. The removed node is NOT deleted.
    /// The remove operation might call the gcgHASHTABLE::compare() method several times to find the node before its removal.
    /// @return if \a newnode is similar to an existing node of the table (the gcgHASHTABLE::compare() method returns zero
    /// for an existing node), the method removes that node from the table and returns its pointer.
    /// The node is NOT deleted by the method. If a similar node was not found or an error occured, it returns NULL.
    /// Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insert()
    /// @see search()
    /// @see compare()
    gcgNODE *remove(gcgNODE *key);

    /// @brief Method that must be furnished by a specialization of gcgHASHTABLE and is responsible for
    /// comparing two gcgNODE nodes. This is necessary for all operations of insertion, retrieval and
    /// removal. It must compare the two nodes pointed by \a refnode1 and \a refnode2
    /// and return zero if they are equal, -1 if \a refnode1 is smaller or precedes \a refnode2, or
    /// 1 if \a refnode1 is greater or succeeds \a refnode2. This method is also required by the
    /// base class gcgORDEREDSTRUCTURE.
    /// @param[in] refnode1 pointer to a gcgNODE, generally specialized, object that must
    /// be compared with \a refnode2.
    /// @param[in] refnode2 pointer to a gcgNODE, generally specialized, object that must
    /// be compared with \a refnode1.
    /// @return It must compare the two nodes pointed by \a refnode1 and \a refnode2
    /// and return zero if they are equal, a negative integer if \a refnode1 is smaller or precedes
    /// \a refnode2, or a positive integer if \a refnode1 is grater or succeeds \a refnode2.
    /// @see insert()
    /// @see remove()
    /// @see search()
    virtual int compare(gcgNODE *refnode1, gcgNODE *refnode2) = 0;
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////  PROCESS and THREAD control: macros, classes, and functions /////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// @defgroup proc Processes, threads and synchronization
/// GCGlib has classes and functions to make the control of processes, threads and their synchronization
/// easier.
///@{

/// @brief Gets the number of processors installed in the system.
/// @return number of available processors in the system.
/// @see gcgTHREAD
/// @see gcgTHREADPOOL
/// @see gcgJOB
/// @see gcgPRODUCERCONSUMER
/// @see gcgLOCK
/// @since 0.01.6
GCG_API_FUNCTION    unsigned int gcgGetNumberOfProcessors();

//////////////////////////////////////////////////////////////////////////////
/// @brief Generic abstract class for defining a thread.
///
/// A specialization of this abstract class must implement the method gcgTHREAD::run().
/// After the invocation of the method gcgTHREAD::startThread(), a control thread is
/// created with pthread library, which calls the run() method. This control
/// thread is destroyed when run() returns, and startThread() can be invoked again. While
/// the run() does not return, or is assynchronously aborted with gcgTHREAD::abortThread(),
/// calling startThread() will result in an error. The thread cancelation with abortThread() must
/// be avoided. It is not a good practice to force the stop of a thread. This may be the source
/// of inumerous problems like memory leaking, deadlocks and data loss. It is preferable to implement
/// cancelation points in the method run(), which can be enabled to safely finish and make run()
/// to return. In this case, use method gcgTHREAD::waitThread() to wait until run() exits. At any time,
/// the user can probe if the thread is running with gcgTHREAD::isRunning().
///
/// The method abortThread() stops the control thread by calling pthread_cancel(). Due to system
/// incompatibilities, this funcionality does not work assynchronously in Windows systems. This means
/// that abortThread() will not stop the thread immediately but flag the thread to stop when it reaches
/// a pthread cancelation point. If run() does not use threads that call pthreads, it will continue to
/// run after abortThread() returns true. The programmer should avoid this method as much as possible in
/// Windows systems.
///
/// @since 0.01.6
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgTHREAD   :  public gcgCLASS {
  public:
    void    *handle;    ///< Internal handle of this object.

  public:
    /// @brief Constructs a valid object. No thread is created and method run() is not called.
    /// @see startThread()
    gcgTHREAD();

    /// @brief Deletes the object, releasing its resources. If any thread is running, it calls waitThread()
    /// to ask them to finish and wait their exit. The deletion is blocked if run() does not return.
    /// Before deleting an gcgTHREAD object, it is a good practice to ask run() to exit normally
    /// (synchronously).
    /// @see abortThread()
    /// @see waitThread()
    virtual ~gcgTHREAD();

    /// @brief Starts a new control thread that executes gcgTHREAD:run(). It returns immediately to the
    /// calling process. If a thread is still running for this instance, returns an error.
    /// @return true if the thread is succesfully created. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see abortThread()
    /// @see waitThread()
    bool startThread();

    /// The method abortThread() forces the thread stop by calling pthread_cancel(). After its return, a
    /// new thread can be issued with startThread().This is not a good practice because the thread aborted
    /// may leave memory leaks, locks and unsaved data. Avoid this method using user defined cancellation
    /// points inside run() that flags it to safely exit. In this case, the thread stop can be checked using
    /// waitThread(). Due to system incompatibilities, this funcionality does not work assynchronously in
    /// Windows systems. This means that abortThread() will not stop the thread immediately but flag the
    /// thread to stop when it reaches a pthread cancelation point. If run() does not use threads that
    /// call pthread functions, it will continue to run after abortThread() returns successfully. The
    /// programmer should avoid this method as much as possible in Windows systems. In Linux systems, this
    /// method can be called even inside the thread.
    /// @return true if the thread is succesfully aborted (or signaled to abort). If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see startThread()
    /// @see waitThread()
    bool abortThread();

    /// This method blocks until the thread execution performed by run() exits or is cancelled. If the
    /// thread is not running or is already stoped, it returns immediately. This method can not be
    /// called inside the thread to avoid deadlock.
    /// @return true if the thread has succesfully exited or cancelled. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see startThread()
    /// @see abortThread()
    bool waitThread();

    /// Checks if the thread is running. Returns immediately.
    /// @return true if the thread is still running.
    /// @see startThread()
    bool isRunning();

  public:
    /// Pure virtual method that is called as a separate thread when startThread() is invoked.
    /// It must be implemented by specialized classes.
    /// @see startThread()
    /// @see waitThread()
    /// @see abortThread()
    /// @see isRunning()
    virtual void run() = 0;
};

//////////////////////////////////////////////////////////////////////////////
/// @brief Defines a lock for easy critical section control. Provides timed lock, which tries
/// to lock an internal mutex before a given timeout has elapsed.
///
/// Threads sometimes need to access a data resource or event. Firstly, the thread enters
/// a critical section into which it can have exclusive access to the data. After checking the
/// data for resource or event, the thread can pick the information it needs and then unlock the
/// access. Using gcgLOCK class, these operations are respectively gcgLOCK::lock() and
/// gcgLOCK::unlock().
///
/// Generic methods to make threads to wait for some notification: gcgLOCK::wait() and gcgLOCK::wakeUp()
///
/// If the thread sees that the data is not ready or available, or an expected event did not occur,
/// it can go to sleep waiting for them. Method gcgLOCK::wait() has this function and must
/// be called after gcgLOCK::lock() has gained control of the critical section. A waiting thread does
/// not hog the processor. When the resource becomes available or an event occurs, the other thread
/// responsible for them notifies it waking up one or more threads that are in wait state. The other
/// thread calls gcgLOCK::wakeUp() for this, telling how many threads should be woken up (or all). If
/// multiple threads are blocked each one by a gcgLOCK::wait() call, the system scheduler will choose
/// which of them will wake up. The awaken threads has to get the lock again in order to continue
/// execution (keeping exclusive control of the resources or data). At that point, exclusively one
/// thread is allowed to run. This is desired because the resource or event is accessible only by one
/// thread at a time. The thread can operate on the resource or event and, when finished,
/// release the control to allow another thread to exclusively access the resource/event. The current
/// thread does this is by normally calling gcgLOCK::unlock(). Then, another awaken thread get the lock
/// and the exclusive access to the resource, works on it, and, on its turn, release it for another
/// thread. In this process, the awaken (notified) threads by gcgLOCK::wakeUp() return from gcgLOCK::wait()
/// sequentially, and synchronously have access to the resource or event. Along the lock() - unlock()
/// code block, the thread can check anytime if the resource/event is available and call gcgLOCK::wait() as long
/// as needed, while data is not available or event signaled.
///
///
/// @since 0.01.6
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgLOCK   :  public gcgCLASS {
  public:
    void *handle;    ///< Internal handle of this object.

    /// @brief Constructs a valid and unlocked object.
    /// @see lock()
    /// @see unlock()
    gcgLOCK();

    /// @brief Destroys the object. Be sure that the object is unlocked before destruction.
    /// Trying to destroy a locked object will result in an undefined behavior, as defined by pthread
    /// library.
    /// @see lock()
    /// @see unlock()
    virtual ~gcgLOCK();

    /// Locks the object. If it is unavalaible, waits the lock for \a timeoutUsec microseconds. If
    /// the locked is obtained during this time, the function returns immediately. If time is out,
    /// returns false with a GCG_TIMEOUT warning (check GCG_REPORT_MESSAGE(gcgGetReport())). If \a
    /// timeoutUsec is negative, the calling thread will be blocked until it acquire the lock or
    /// un error occurs. If the lock is seized, returns true.
    /// @param[in] timeoutUsec the time in microseconds that the function must wait to get the
    /// lock. The function returns immediately after the lock is seized. If negative, the function blocks
    /// the calling thread until the lock is obtained or an error occurs.
    /// @return true if the object was locked. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem. If \a timeoutUsec is elapsed
    /// without successful locking, the warning GCG_TIMEOUT is triggered.
    /// @see unlock()
    /// @see wait()
    /// @see wakeUp()
    bool lock(long timeoutUsec = -1);

    /// Unlocks the object. The calling thread must own the object otherwise an error is generated.
    /// @return true if the object was unlocked. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see lock()
    /// @see wait()
    /// @see wakeUp()
    bool unlock();

    /// @brief Blocks the calling thread, waiting to be woken up. It must be called after having the
    /// control by calling gcgLOCK::lock(). If another thread calls wakeUp() for a sufficient number
    /// of threads, this method returns true eventually. If \a timeoutUsec
    /// (positive) has elapsed after the blocking, wait() returns false and a warning with GCG_TIMEOUT
    /// is issued. If during this time wakeUp() is called for a sufficient number of threads, wait()
    /// eventually returns true. If \a timeoutUsec is negative, the method blocks until wakeUp() is
    /// called or an error occurs. For each call to wait() there MUST be a subsequent call to
    /// unlock(), even if it returns false.
    /// @param[in] timeoutUsec the time in microseconds that the function must wait. If during this time
    /// wakeUp() is invoked for a sufficient number of threads, the method returns true. If negative, the
    /// function blocks the calling thread until a wakeUp() method is invoked or an error occurs. If \a
    /// timeoutUsec (positive) has elapsed after the blocking, wait() returns false and a warning with
    /// GCG_TIMEOUT is issued.
    /// @return true if the thread was woken up, regained the lock, and has exclusive access to the
    /// critical section. gcgWAIT:unlock() MUST be called eventually after a call to gcgWAIT:wait().
    /// Otherwise, all other threads get stucked in a deadlock. If it returns false, the thread can
    /// access the objects of the associated critical section, but the event or resource might be
    /// unavailable. Check always the conditions before using resources. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see lock()
    /// @see unlock()
    /// @see wakeUp()
    bool wait(long timeoutUsec = -1);

    /// @brief Wakes up at least one blocked thread. The number of threads to be woken up is application
    /// dependent. If \a n objects were produced, for example, at least \a numberOfThreads = \a n
    /// should be woken up to consume them without wasting system resources. If \a numberOfThreads is
    /// negative, all waiting threads are woken up.
    /// @param[in] numberOfThreads number of threads to be woken up. If zero, nothing occurs. If negative,
    /// all threads are awaken.
    /// @return true if the broadcast signal to wake threads were sent. If returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see lock()
    /// @see unlock()
    /// @see wait()
    bool wakeUp(int numberOfThreads = -1);
};

//////////////////////////////////////////////////////////////////////////////
/// @brief Defines a queue with synchronized access. This is a standard data structure
/// that may be used with First-In-First-Out or Last-In-First-Out policies. This is intended
/// for multitask applications. Use gcgLINKEDLIST if you do not need exclusive accesses
/// in enqueue and dequeue operations.
///
/// @since 0.02.0
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgQUEUE   :  public gcgCLASS {
  private:
    void *handle; ///< Internal handle of this object.

  public:
    /// @brief Constructs a valid and empty queue.
    /// @see enqueueHead()
    /// @see enqueueTail()
    /// @see dequeue()
    /// @see waitDequeue()
    /// @see gcgLINK
    gcgQUEUE();

    /// @brief Destroys the queue, releasing the linked list of nodes. After that, it wakes all
    /// threads blocked in waitDequeue(). All entries are deleted.
    /// @see enqueueHead()
    /// @see enqueueTail()
    /// @see dequeue()
    /// @see waitDequeue()
    /// @see isEmpty()
    /// @see gcgLINK
    virtual ~gcgQUEUE();

    /// @brief Inserts a new entry \a node at the TAIL of the queue. This entry will be the last to be
    /// dequeued.
    /// @param[in] node a pointer to a linkable instance (gcgLINK) to be inserted at queue's tail.
    /// This pointer is deleted by the destructor or a deleteAll() call if not dequeued. A NULL value
    /// generates an error.
    /// @return returns true if the data is successfully inserted at the end of the queue. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see enqueueHead()
    /// @see dequeue()
    /// @see deleteAll()
    /// @see waitDequeue()
    /// @see isEmpty()
    /// @see wakeUpWhenChanged()
    /// @see gcgLINK
    bool enqueueTail(gcgLINK *node);

    /// @brief Inserts a new entry \a node at the HEAD of the queue. This entry
    /// will be the first to be dequeued.
    /// @param[in] node a pointer to a linkable instance (gcgLINK) to be inserted at the queue's head.
    /// This pointer is deleted by the destructor or a deleteAll() call if not dequeued. A NULL value generates an error.
    /// @return returns true if the data is successfully inserted at the top of the queue. If
    /// it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see enqueueTail()
    /// @see dequeue()
    /// @see deleteAll()
    /// @see waitDequeue()
    /// @see isEmpty()
    /// @see wakeUpWhenChanged()
    /// @see gcgLINK
    bool enqueueHead(gcgLINK *node);

    /// @brief Returns the next entry stored in the HEAD of the queue. The entry is
    /// removed from the top of the queue.
    /// @return returns the pointer of the head entry. If it returns NULL, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see enqueueHead()
    /// @see enqueueTail()
    /// @see waitDequeue()
    /// @see isEmpty()
    /// @see wakeUpWhenChanged()
    /// @see gcgLINK
    gcgLINK *dequeue();

    /// @brief Returns the HEAD entry of the queue. It is removed from the top of the queue. If the queue
    /// is empty, waits for \a timeoutUsec microseconds. If an entry becomes available during this time, it
    /// is returned immediately. If time is out, returns NULL with a GCG_TIMEOUT warning
    /// (check GCG_REPORT_MESSAGE(gcgGetReport())). If \a timeoutUsec is negative, the calling thread is
    /// blocked and only returns when an entry is available or an error occurs.
    /// @param[in] timeoutUsec the time in microseconds that the function must wait to get the a data.
    /// The function returns immediately after the entry is dequeued. If negative, the function blocks
    /// the calling thread until a entry is obtained or an error occurs.
    /// @return returns the entry pointer. If it returns NULL, check GCG_REPORT_MESSAGE(gcgGetReport())
    /// for knowing the problem. If \a timeoutUsec is elapsed without successful dequeue, it returns NULL
    /// and the warning GCG_TIMEOUT is triggered.
    /// @see enqueueHead()
    /// @see enqueueTail()
    /// @see dequeue()
    /// @see waitDequeue()
    /// @see isEmpty()
    /// @see wakeUpWhenChanged()
    /// @see gcgLINK
    gcgLINK *waitDequeue(long timeoutUsec = -1);

    /// @brief Checks if the queue is empty.
    /// @return Returns true if the queue has no entries.
    /// @see enqueueHead()
    /// @see enqueueTail()
    /// @see dequeue()
    /// @see waitDequeue()
    /// @see getCounter()
    bool isEmpty();

    /// @brief Gets the current number of elements stored in the queue.
    /// @return the number of entries stored in the queue.
    /// @see enqueueHead()
    /// @see enqueueTail()
    /// @see dequeue()
    /// @see waitDequeue()
    /// @see isEmpty()
    unsigned int getCounter();

    /// @brief Removes all entries from the queue. All objects are deleted. If notification is enabled,
    /// calls gcgLOCK::wakeUp(-1) to wake all waiting threads once and after all entries were removed.
    /// @return Returns true if all entries were removed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see enqueueHead()
    /// @see enqueueTail()
    /// @see dequeue()
    /// @see waitDequeue()
    /// @see wakeUpWhenChanged()
    bool deleteAll();

    /// @brief Sets the gcgLOCK to be used to wake up threads waiting for insertions on this queue.
    /// When a entry is added to the queue, gcgQUEUE executes the gcgLOCK::wakeUp() of \a notifyme,
    /// passing \a wakeupNumThreads as the number of threads to be awaken. This allows
    /// asynchronous accesses to the queue. This notification is made by enqueueTail() and enqueueHead().
    /// Only one gcgLOCK instance for enqueuing events is allowed by gcgQUEUE, but the same
    /// gcgLOCK instance can be used by several notifying objects.
    /// @param[in] notifyme pointer to a gcgLOCK used for concurrent access to the queue. A thread that
    /// is waiting for an entry insertion should call gcgLOCK::wait() to block. When gcgQUEUE
    /// calls notifyme->wakeUp(wakeupNumThreads) indicating an entry addition, at least
    /// \a wakeupNumThreads are woken up and will have the chance to access the queue. Only one enqueuing
    /// notifier is allowed by gcgQUEUE. It may be NULL, disabling change enqueuing notifications (default).
    /// @param[in] wakeupNumThreads number of threads to be awaken when an insertion occurs.
    /// This is directly passed to \a notifyme's gcgLOCK::wakeUp() invocation.
    /// @return returns the previous gcgLOCK pointer for enqueuing notifications.
    /// @see enqueueHead()
    /// @see enqueueTail()
    /// @see waitDequeue()
    /// @see gcgLOCK::wakeUp()
    /// @see gcgLOCK::wait()
    gcgLOCK *wakeUpWhenEnqueued(gcgLOCK *notifyme, int wakeupNumThreads);


    /// @brief Sets the gcgLOCK to be used to wake up threads waiting for removals on this queue.
    /// When a entry is removed from the queue, gcgQUEUE executes the gcgLOCK::wakeUp() of \a notifyme,
    /// passing \a wakeupNumThreads as the number of threads to be awaken. This allows asynchronous accesses
    /// to the queue. This notification is made by dequeue(), waitDequeue(), deleteAll() and upon object
    /// destruction. The destructor and deleteAll() call \a notifyme's gcgLOCK::wakeUp(-1) (wakes up all
    /// waiting threads) once and after all entries are deleted. Only one dequeuing gcgLOCK instance is
    /// allowed by gcgQUEUE, but the same gcgLOCK instance can be used by several notifying objects.
    /// @param[in] notifyme pointer to a gcgLOCK used for concurrent access to the queue. A thread that
    /// is waiting for an entry removal should call gcgLOCK::wait() to block. When gcgQUEUE
    /// calls notifyme->wakeUp(wakeupNumThreads) indicating an removal from the queue, at least
    /// \a wakeupNumThreads are woken up and will have the chance to access the queue. Only one dequeuing
    /// notifier is allowed by gcgQUEUE. It may be NULL, disabling change dequeuing notifications (default).
    /// @param[in] wakeupNumThreads number of threads to be awaken when an removal occurs. This is directly
    /// passed to \a notifyme's gcgLOCK::wakeUp() invocation. The destructor wakes up all threads.
    /// @return returns the previous gcgLOCK pointer.
    /// @see dequeue()
    /// @see waitDequeue()
    /// @see ~gcgQUEUE()
    /// @see gcgLOCK
    /// @see gcgLOCK::wakeUp()
    /// @see gcgLOCK::wait()
    gcgLOCK *wakeUpWhenDequeued(gcgLOCK *notifyme, int wakeupNumThreads);
};


//////////////////////////////////////////////////////////////////////////////
/// @brief Defines a synchronized memory cache. This is an abstract data structure
/// that may be used to restrict the existence of multiple objects at a time in memory.
/// This class manages key/data pairs using hash tables and trees. The key is generally, a
/// short and unique identity for the data which, in turn, can be of any size. A key in
/// gcgCACHE can have up to 255 bytes and all methods access it by a pointer. A hash table is used
/// for efficient search of keys. If the key has at most sizeof(long), the hash computation is
/// more efficient. The size in bytes of the key is configured with \a setKeySize() method.
/// If zero is given, the keys are treated as null terminated strings. Note that the keys are stored
/// internally for each key/data pair. By default, the key size is zero which means it expects null
/// terminated strings. There are two main interfaces: one for the application requests (non-virtual
/// and data independent methods) and one for the data creation, removal and persistence
/// (abstract, virtual and data dependent methods that must be implemented). The main application
/// interface consists of the \a get() method for which the application presents the desired
/// key and, if the corresponding data is cached (cache hit), it returns its pointer immediately
/// (its entry is marked as the most recently used). If the data is not present (cache miss), the
/// data interface is called for its retrieval before get() returns. In this case, the gcgCLASS
/// calls the \a retrieveData() method to get the missing data for the requested key. If the
/// missing data is retrieved but the cache is full (the cache cost capacity exceeds with the
/// new key/data cost), the gcgCACHE calls the \a discardData() to delete or persist the least
/// recently used key/data pairs until the cost of the new key/data fits in the cache limit.
/// At any time, the application can discard one or all entries by calling \a flush() method.
/// Inside GCGlib, this class is used to ensure thread safe operations.
///
/// @since 0.02.113
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgCACHE   :  public gcgCLASS {
  public:
    unsigned long totalcost; ///< Sum of the cost of all key/data pairs. Read-Only.
    unsigned long capacity;  ///< Maximum sum of data costs this cache supports. Read-Only. See \a setMaximumCost().
    unsigned char keysize;   ///< Size of each key in bytes. If zero, the key is null terminated strings. Read-Only. See \a setKeySize().

  private:
    void *handle;       ///< Internal handle of this object.

  public:
    /// @brief Constructs an empty cache. No resource is created until
    /// the gcgCACHE::get() method is called.
    /// @see get()
    gcgCACHE();

    /// @brief Destroys the cache. If the cache total cost is non-zero, then \a flush(NULL) is
    /// called to release all key/data pairs and cache resources.
    /// @see flush()
    virtual ~gcgCACHE();

    //////////////////////////////////////////////////////////////////
    // Application interface: retrieving data from the cache

    /// @brief Gets the data corresponding to the \a key and mark its internal entry as the most
    /// recently used. If the data associated with the key is not stored in the cache (cache miss),
    /// the retrieveData() method is called to get the missing data for the requested key. If the
    /// missing data is retrieved but the cache is full (the cache cost capacity exceeds with the
    /// new key/data cost), the \a discardData() method is called to delete or persist the least
    /// recently used key/data pairs until the cost of the new key/data fits in the cache limit.
    /// Both key and data contents and interpretation are application dependent and must be fully
    /// resolved by the data interface. If the cache is empty, this method allocates all needed
    /// resources. Thus, the cache capacity (see \a setCapacity()) and the key size in bytes must
    /// be defined before the first \a get() call.
    /// @param[in] key pointer to a sequence of bytes representing the key of the requested data.
    /// @return the pointer to the data associated with the \a key. If the data is not cached and could
    /// not be retrieved by the data interface, or its cost is greater than the cache capacity, it
    /// returns NULL. Check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setCapacity()
    /// @see flush()
    /// @see retrieveData()
    /// @see setKeySize()
    void *get(void *key);

    /// @brief Discard and remove the entry of a specific key/data pair, or all key/data stored in the
    /// cache. Before internal removal, the \a discardData() method is called for each pair in order to be
    /// deleted and/or persisted by the data interface. The total cost summation of the cache is reduced
    /// accordingly. If the \a flush(NULL) is called, all key/data are discaded and the cache resources are
    /// released.
    /// @param[in] key pointer to a sequence of bytes representing the key of the data to be flushed.
    /// @return true if the key/data was found and succesfully discarded. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see get()
    /// @see discardData()
    bool flush(void *key);

    /// @brief Sets the capacity of the cache, i.e. the maximum allowed value for the sum of costs of all
    /// key/data pairs. If the current total cost is greater than the new capacity, the least recently used key/data
    /// pairs are flushed until the sum of costs becomes smaller or equal to the new capacity. The cost unit can
    /// be anything: bytes, number of elements, area, weight, etc. It is application dependent and must be defined
    /// by the data interface.
    /// @param[in] maximumtotalcost maximum sum of all costs this cache supports.
    /// @return true if the capacity was succesfully set and the cache is consistent, i.e. the sum of
    /// costs is lesser or equal to the new capacity. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see get()
    /// @see flush()
    /// @see discardData()
    bool setCapacity(unsigned long maximumtotalcost);

    /// @brief Sets the size, in bytes, of the key. This operation is only possible if the cache is empty, i.e. there
    /// is no key/data stored. The maximum allowed key size is 255. If zero (default value), the keys are null terminated
    /// strings. The key size is important for the cache performance. Best performance is achieved with at most sizeof(long)
    /// bytes.
    /// @param[in] keybytes size of the key in bytes. If zero, the keys are null terminated strings.
    /// @return true if the key size was successfully set up. It returns false if there are key/pairs stored,
    /// and \a keybytes is different than the current key size.
    /// @see get()
    bool setKeySize(unsigned char keybytes);

    ////////////////////////////////////////////////////////////////////////
    // Data interface: managing data creation, removal and persistence.

    /// @brief Invoked by the gcgCACHE to fulfill a request that resulted in a cache miss when \a get() was called.
    /// Given the \a key, this method must provide its associated data and its cost. If this is not possible, it must
    /// return NULL to tell \a get() to also return NULL to the application. If the data cost is greater than the
    /// cache capacity, the \a get() will subsequently discard it by calling \a discardData().
    /// @param[in] key pointer of a sequence of bytes representing the key of the requested data.
    /// @param[out] datacost pointer to an unsigned long that must receive the cost of the requested key/data pair.
    /// If this cost is greater that the cache capacity, the \a get() will subsequently discard the pair by
    /// calling \a discardData().
    /// @return it must return a pointer to the data associated to the \a key. If the key is invalid or the data is
    /// not available, it must return NULL to tell \a get() to also return NULL to the application.
    /// @see get()
    /// @see discardData()
    virtual void *retrieveData(void *key, unsigned long *datacost) = 0;

    /// @brief Invoked by the gcgCACHE to discard a key/data pair. It must release and/or save the key/pair resources
    /// because gcgCACHE will erase any internal reference to it. It is called by the \a flush() method, when the
    /// application need to delete and/or persist a pair, or by the \a get() method, to reduce the current total cost
    /// in response to a cache miss.
    /// @param[in] key pointer of a sequence of bytes representing the key of the data to be discarded or persisted.
    /// @param[out] data pointer to the data that must be discarded or persisted.
    /// @see get()
    /// @see flush()
    virtual void discardData(void *key, void *data) = 0;
};



//////////////////////////////////////////////////////////////////////////////
/// @brief Generic abstract class for defining a job/task for using with GCGlib.
/// It inherits gcgNODE in order to be used in one linked list.
///
/// The job/task must be defined in a specialization of this class that
/// implements gcgJOB::run() method. Objects of this class are deleted when
/// gcgJOB::run() returns to the GCGlib executor.
///
/// @since 0.02.0
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgJOB : public gcgNODE {
  public:
    /// @brief Constructs a valid and empty job. It is intended to be implemented by specialized
    /// classes.
    /// @see run()
    gcgJOB() {}

    /// @brief Destructs the job. It is intended to be implemented by specialized classes. The
    /// object is deleted by the GCGlib executor when run() returns.
    /// @see run()
    virtual ~gcgJOB() {}

    /// @brief Absctract virtual method that must be implemented by specialized classes.
    /// This method is called by GCGlib executors to perform the job/task. When it returns,
    /// the job object is deleted automatically.
    virtual void run() = 0;
};


//////////////////////////////////////////////////////////////////////////////
/// @brief Controls a pool of threads for executing multiple jobs concurrently.
///
/// A thread pool is intended to reduce the overhead of creating threads. It works
/// by allocating a number of threads that start waiting for jobs. When jobs (see gcgJOB) are assigned,
/// they are inserted into a FIFO queue, and only one idle thread is waken up to process it.
/// Threads might race to dequeue new jobs after finishing their jobs. If no new jobs are available,
/// the thread puts itself again in a wait state. The thread that dequeue a job executes its gcgJOB:run().
/// When it finishes, the gcgJOB instance is deleted if a specific output queue is not given by the user.
/// There are two possible output queues for jobs: \a executed, for successfully executed threads, and
/// \a discarded, for jobs that raised any exception in gcgJOB:run(). If \a executed queue is not NULL,
/// all jobs that did not raised expection are inserted into it. If \a executed is NULL (default), the
/// finished job is deleted. If \a discarded queue is not NULL, all jobs that raised exceptions inside
/// gcgJOB:run() are inserted  into it. If \a discarded is NULL (default), the failed job is deleted.
/// Also, if there are pending jobs in the FIFO queue, waiting to be executed, but the thread pool is destroyed
/// by destroyPool() or waitAndDestroy(), they are all inserted into the \a discarded queue if
/// it is not NULL. Otherwise all non executed jobs are deleted. Output queues are important
/// features to create processing toolchains.
///
/// @since 0.01.6
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgTHREADPOOL   :  public gcgCLASS {
  public:
    void *handle;   ///< Internal handle of this object.

    /// @brief Constructs a valid object but no thread is created. If \a numthreads is non zero,
    /// calls setNumberOfThreads() to create the threads.
    /// @param[in] numThreads number of threads to be used for executing jobs. Greater the number
    /// of threads, higher is the capacity of the threadpool to execute jobs preemptively (but consuming
    /// more system resources). It may be zero.
    /// @see setNumberOfThreads()
    /// @see assignJob()
    gcgTHREADPOOL(unsigned int numThreads = gcgGetNumberOfProcessors());

    /// @brief Deletes the object, releasing its resources. If the thread pool is executing, it calls
    /// waitAndDestroy() to finish all threads. The object destruction is delayed until all executing
    /// jobs are finished. Before deleting an gcgTHREADPOOL object, it is a good practice to ask all
    /// executing jobs to exit normally (synchronously). The pool is deleted only after all threads exit.
    /// The jobs still in the queue are deleted, or inserted in the \a discarded output queue, without
    /// being executed.  Despite not recommended, call destroyPool() before destruction if a fast release
    /// is absolutely needed.
    /// @see waitAndDestroy()
    /// @see setOutputQueue()
    /// @see destroyPool()
    virtual ~gcgTHREADPOOL();

    /// @brief Upon the first call, this method creates a job queue and starts \a numThreads threads that
    /// start picking jobs from the queue. If the pool is already running and working, it creates or
    /// stops threads until the number of threads as defined by \a numThreads is reached. if \a
    /// numThreads is 0, it calls waitAndDestroy() to stop the pool and release its resources. setNumberOfThreads()
    /// blocks until the number of threads is reached. This function is not allowed to be called by jobs being
    /// executed by the thread pool to avoid deadlock.
    /// @param[in] numThreads number of threads to be used for executing jobs. Greater the number
    /// of threads, higher is the capacity of the threadpool to execute jobs preemptively (but consuming
    /// more system resources). If the current number of threads is greather than \a numThreads, threads
    /// that finish their jobs exit until \a numThreads threads is reached. Otherwise, the number of
    /// threads is increased to match \a numThreads. If \a numThreads is zero, the pool is destroyed by
    /// calling waitAndDestroy().
    /// @return true if the pool is ready to process jobs. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see assignJob()
    /// @see wait()
    /// @see waitAndDestroy()
    /// @see destroyPool()
    /// @see getNumberOfThreads()
    bool setNumberOfThreads(unsigned int numThreads = gcgGetNumberOfProcessors());

    /// @brief Gets the number of threads ready to work in the thread pool. Returns zero if the thread pool is
    /// not running or being destroyed, even if still there are threads that did not finished.
    /// @return the number of threads working in the thread pool. Returns zero if the thread pool is not
    /// running or being destroyed, even if still there are threads that did not finished.
    /// @see setNumberOfThreads()
    /// @see waitAndDestroy()
    /// @see destroyPool()
    unsigned int getNumberOfThreads();

    /// @brief Assigns a new job to the threadpool by inserting it in the queue and waking
    /// idle threads. \a job must be a valid instance of a class specializing gcgJOB. If the
    /// thread pool is not running (has no active threads), it returns false without changing the job.
    /// @param[in] job an instance of a class specializing gcgJOB that must be executed by calling run().
    /// A NULL value is not allowed.
    /// @return true if the job is enqueued and threads are woken up. If the thread pool is not running
    /// (has no active threads), a warning is issued using gcgReport(), returning false. If it returns
    /// false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setNumberOfThreads()
    /// @see wait()
    /// @see setOutputQueue()
    /// @see getOutputQueue()
    /// @see waitAndDestroy()
    /// @see destroyPool()
    bool assignJob(gcgJOB *job);


    /// @brief Gets the number of jobs in the queue waiting to be executed by the thread pool.
    /// @return the number of pending jobs in the thread pool.
    /// @see assignJob()
    /// @see waitAndDestroy()
    /// @see destroyPool()
    unsigned int getNumberOfPendingJobs();

    /// @brief Waits the queue to become empty and all threads to become idle. While waiting,
    /// however, new jobs can be inserted by calling assignJob(). This function is not allowed to be
    /// called by jobs executed by the thread pool to avoid deadlock.
    /// @return true if the thread pool is completely idle: all jobs executed and the queue is empty.
    /// Note that this state can be transient if there are other threads using the threadpool. A permanent
    /// idle state is guaranteed by avoiding new jobs to be inserted during wait(). If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setNumberOfThreads()
    /// @see assignJob()
    /// @see waitAndDestroy()
    /// @see destroyPool()
    bool wait();

    /// @brief Flags all threads to exit and waits them to stop. Pending jobs in the queue are discarded and,
    /// thus, not executed. The threads are not cancelled. This means that the return of waitAndDestroy()
    /// occurs only after all current jobs in execution finish. Discarded jobs are inserted into the queue
    /// \a discarded defined by setOutputQueue(). If the output queue is NULL (default), the
    /// discarded job is deleted. This function is not allowed to be called by jobs
    /// executed by the thread pool to avoid deadlock.
    /// @return true if the thread pool has successfully released and destroyed. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setNumberOfThreads()
    /// @see assignJob()
    /// @see setOutputQueue()
    /// @see getOutputQueue()
    /// @see wait()
    /// @see destroyPool()
    bool waitAndDestroy();

    /// @brief Cancel all threads and discards all pending jobs from the queue that are, thus,
    /// not executed. Thread cancellation is not a good practice since the jobs might be interrupted
    /// before releasing important resources and saving data. When stoping the threadpool, prefer
    /// a method using waitAndDestroy(), asking the executing jobs to exit normally (synchronously).
    /// Method destroyPool() cancel the threads and wait for their cancellation. In Windows systems, the
    /// threads cannot be assynchronously stoped, blocking the calling thread if the jobs do not return
    /// normally. In Linux, the sudden stop is not a good practice and may lead to memory leaks,
    /// deadlocks and unsaved data. The jobs still in the queue are discarded without being executed.
    /// Discarded jobs are inserted into the queue \a discarded defined by setOutputQueue(). If the
    /// output queue is NULL (default), the discarded job is deleted. This function is not allowed
    /// to be called by jobs executed by the thread pool to avoid deadlock.
    /// @return true if the thread pool has successfully released and destroyed. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setNumberOfThreads()
    /// @see assignJob()
    /// @see setOutputQueue()
    /// @see getOutputQueue()
    /// @see wait()
    /// @see waitAndDestroy()
    bool destroyPool();

    /// @brief Sets the output queues for executed and discarded jobs. The \a executed queue indicates
    /// where a job must be inserted after being executed.  When a job exits, it is inserted
    /// in this queue for later control. If \a executed is NULL, any executed job is deleted. If any
    /// error is detected during execution (raised exceptions), or the job is not executed due to
    /// waitAndDestroy() or destroyPool() calls, it is inserted into the \a discarded queue. If \a
    /// discarded is NULL, the job is deleted. This functionality helps the output control of jobs.
    /// Both output queues are NULL by default. Once set up, the queues are preserved until thread pool
    /// destruction.
    /// @param[in] executed a gcgQUEUE instance into which executed jobs must be inserted. If NULL, the
    /// output is disabled and all executed jobs are deleted.
    /// @param[in] discarded a gcgQUEUE instance into which discarded jobs must be inserted. Discarded
    /// jobs are those that could not be executed due to errors (raised exception) or due to
    /// destruction by waitAndDestroy() or destroyPool(). If NULL, the output is disabled and all
    /// discarded jobs are deleted.
    /// @return true if the queues are set. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport())
    /// for knowing the problem.
    /// @see setNumberOfThreads()
    /// @see getOutputQueue()
    /// @see waitAndDestroy()
    /// @see destroyPool()
    bool setOutputQueue(gcgQUEUE *executed, gcgQUEUE *discarded = NULL);

    /// @brief Gets the current output queues used for executed and discarded jobs.
    /// @param[in] pexecuted a gcgQUEUE pointer address that will receive the queue for executed jobs.
    /// A NULL value is allowed.
    /// @param[in] pdiscarded a gcgQUEUE pointer address that will receive the queue for discarded jobs.
    /// A NULL value is allowed.
    /// @return true if the queue pointers were retrieved. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see setNumberOfThreads()
    /// @see setOutputQueue()
    /// @see waitAndDestroy()
    /// @see destroyPool()
    bool getOutputQueue(gcgQUEUE **pexecuted, gcgQUEUE **pdiscarded);

    /// Checks if the thread pool has threads running or waiting jobs. Returns immediately.
    /// @return true if there are threads being used, either executing jobs or ready to receive new jobs. If
    /// false, the thread pool is being destroyed or has no thread working.
    /// @see setNumberOfThreads()
    /// @see waitAndDestroy()
    /// @see destroyPool()
    bool isRunning();
};



//////////////////////////////////////////////////////////////////////////////
/// @brief Controls and synchronizes multiple producers and consumers accessing
/// a shared and limited buffer. Supports blocking and non-blocking calls to
/// put() and get().
///
/// Producer threads and processes call put(void *val) to insert a new and
/// arbitrary object with pointer val in the end of the buffer. Consumer
/// threads and processes call void* get() to obtain the oldest produced object
/// pointer. Synchronized access to the buffer is guaranteed. Calls to put() and
/// get() may (or may not) block the calling thread or process. put() calls block
/// if the buffer is full and get() calls block if the buffer is empty. Use
/// enable() function to enable/disable the production/consumption: the buffer is unchanged by put()
/// and get() calls, which become unblocked and always return with failure. To keep the production/consumption
/// functionality and non-blocking behavior, use setTimeout(0, 0): in this case the buffer can be
/// normally changed by put() and get() calls.
///
/// @since 0.01.6
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgPRODUCERCONSUMER   :  public gcgCLASS {
    private:
      void *handle; ///< Internal handle of this object.

    public:
      /// @brief Constructs a valid object with a specified number of buffer elements.
      ///        Sets put() and get() methods to block if the buffer is full or empty, respectively.
      ///        If \a bufferlength is non-zero, calls setBufferSize() to create initial buffer.
      /// @param[in] bufferlength number of elements of the producer/consumer buffer. It may be zero.
      /// @see setBufferSize()
      gcgPRODUCERCONSUMER(unsigned int bufferlength = 4);

      /// @brief Frees all object resources by calling destroyProducerConsumer()
      virtual ~gcgPRODUCERCONSUMER();

      /// @brief Frees previous resources and allocates a buffer with different length.
      ///        Old buffer contents and parameters are completely discarded.
      /// @param[in] bufferlength defines the number of elements in the producer/consumer buffer. if zero,
      ///            the object is destroyed by a call to destroyProducerConsumer().
      /// @return true if the a buffer with the specified length is successfully allocated.
      bool setBufferSize(unsigned int bufferlength);

      /// @brief Frees all object resources. Invocations to the object methods become inoquous.
      /// A call to setBufferSize() turns the object usable again.
      /// @return true if the object is completely released.
      bool destroyProducerConsumer();

      /// @brief Puts a new object pointer at the end of the buffer. It's the producer interface.
      ///
      /// Producer calls to put() will block indefinitely if the buffer is full, and
      /// setTimeout() was called with \a timooutprod < 0. It remains blocked until an element of the
      /// buffer is consumed by a get() call. If setTimeout() was called with \a timeoutprod>=0,
      /// a call to put() will try to insert the pointer into the buffer during the timeout
      /// given in microseconds. If successful, it returns true.
      /// @param[in] val pointer to the produced object to be stored into the buffer.
      /// @return true if the object was successfully stored.
      /// @see get()
      /// @see setTimeout()
      /// @see enable()
      bool put(void *val);

      /// @brief Gets the oldest pointer of the buffer. It's the consumer interface.
      ///
      /// Consumer calls to get() will block indefinitely if the buffer is empty, and
      /// setTimeout() was called with \a timeoutcons < 0. It remains blocked until an element is
      /// inserted into the buffer by a put() call. If setTimeout() was called with
      /// \a timeoutcons >= 0, a call to get() will try to obtain the oldest pointer
      /// during the time specified in microseconds. If successful, it returns the
      /// pointer. Otherwise returns NULL.
      /// @return the oldest produced object of the buffer if successful or NULL, otherwise.
      /// @see put()
      /// @see setTimeout()
      /// @see enable()
      void *get();

      /// @brief Gets the current number of elements stored into the buffer
      /// @return the number of valid objects stored into the buffer.
      unsigned int getCounter();

      /// @brief Sets the blocking policy for producers and consumers when calling put() and
      /// get() methods, respectively. When timeout is changed, all waiting threads for
      /// production/consumption are awaken. Negatives timeouts make the production/consumption
      /// block. With setTimeout(0,0) the production/consumption works changing the internal buffer but
      /// put() and get() calls never block. To disable the production/consumption and avoid
      /// changes to the buffer by subsequent put() and get() calls, use enable() instead.
      /// @param[in] timeoutprod time to wait in microseconds for production. A negative value
      /// means that calls to put() should be indefinitely blocked when the buffer is full.
      /// A non-negative value specifies the time in microseconds which put() should wait
      /// until the buffer has room for the new product.
      /// @param[in] timeoutcons time to wait in microseconds for consuming. A negative value
      /// means that calls to get() should be indefinitely blocked when the buffer is empty.
      /// A non-negative value specifies the time in microseconds which get() should wait
      /// until the buffer has a new product.
      /// @see get()
      /// @see put()
      /// @see enable()
      void setTimeout(long timeoutprod, long timeoutcons);

      /// @brief Enables or disables the production and consumption. When enable status is changed,
      /// all waiting threads for production/consumption are awaken to check its new value. To avoid blocked
      /// calls to put() and get() and have the production/consumption enabled, call setTimeout(0, 0) instead.
      ///
      /// Initially, the gcgPRODUCERCONSUMER object is enabled and ready to requests by put() and get() calls.
      /// If enable(false) is called, all threads waiting for production/consumption are awaken and blocked calls
      /// of put() and get() return with false/NULL result. All subsequent calls to put() and get() will return
      /// unsuccessful imediately. If enabled, the production/consumption normally works with or without blocking as
      /// specified by setTimeout() calls.
      /// @param[in] enabled indicates if the production/consumption is to be enabled (true) or disabled (false).
      /// @see get()
      /// @see setTimeout()
      void enable(bool enabled);
};

///@}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////  TEXTURES processing macros, classes, and functions /////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// @brief Class to transparently deal with 3D textures. Allocates the
/// texture directly from graphics system and provides functions for
/// binding, unbinding and updating the texture.
///
/// @since 0.01.6
class    GCG_API_CLASS    gcgTEXTURE2D   :  public gcgCLASS {
  public:
    unsigned int    width;        ///< Width effectivelly used by the texture. It must be <= \a actualwidth.
    unsigned int    height;       ///< Height effectivelly used by the texture. It must be <= \a actualheight.

    unsigned int    actualwidth;  ///< Real width of the texture inside the graphics system: must be a power of 2.
    unsigned int    actualheight; ///< Real Height of the texture inside the graphics system: must be a power of 2.

    unsigned int    idOpengl;     ///< OpenGL texture internal identification.

    int             internalformat; ///< OpenGL internal format: GL_LUMINANCE4, GL_LUMINANCE8, GL_RGB5, GL_RGB5_A1, GL_RGBA8, GL_RGB8 or GL_RGB4, depending on the texture creation parameters.
    int             format; ///< OpenGL format: GL_LUMINANCE, GL_BGRA, GL_RGB or GL_RGBA, depending on the texture creation parameters.
    int             type;   ///< OpenGL format: GL_UNSIGNED_BYTE, GL_BITMAP, GL_UNSIGNED_BYTE_4, GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_UNSIGNED_SHORT_5_6_5, or GL_UNSIGNED_SHORT_4_4_4_4_REV, depending on the texture creation parameters.

  public:
    /// @brief Constructs a valid gcgTEXTURE instance but no actual texture is created.
    /// @see ~gcgTEXTURE2D()
    /// @since 0.01.6
    gcgTEXTURE2D();

    /// @brief Frees all texture resources by calling destroyTexture().
    /// @see gcgTEXTURE2D()
    /// @since 0.01.6
    virtual ~gcgTEXTURE2D();

    /// @brief Frees all texture resources. Invocations to the object methods become innocuous.
    /// A call to createTexture() or uploadImage() turns the texture usable again.
    /// @return true if the texture is completely released, including from graphics system.
    bool destroyTexture();

    /// @brief Creates a new texture filled with black pixels (zeros). It releases all resources of the previous texture.
    /// The actual texture allocated in the graphics systems has power of 2. Thus, if \a width or \a height are not powers of 2, they
    /// are adjusted to the smallest power of 2 greater than them. The bits per pixel \a bpp may be 4, 8, 16, 24 or 32 bits, and the
    /// internal graphics system attributes are selected accordingly, also depending on the \a usealpha parameter.
    /// @param[in] width The expected width of the texture. If it is not a power of 2, the actual texture's width allocated in the graphics
    /// system is the smallest power of two greater than \a width.
    /// @param[in] height The expected height of the texture. If it is not a power of 2, the actual texture's height allocated in the graphics
    /// system is the smallest power of two greater than \a height.
    /// @param[in] bpp The bits per pixel of the texture. The internal parameters are chosen accordingly, in conjunction with \a usealpha. If
    /// \a bpp is 4 or 8, then the texture indicates luminance or pixel brightness. If \a bpp is 16 (and \a usealpha is false), 5 bits are
    /// allocated for red and blue channels, and 6 bits for the green channel. If \a bpp is 32 (and \a usealpha is false), 8 bits are allocated
    /// for red, green and blue channels and the remaining 8 bits are ignored. See \a usealpha to see the bitmap for 16 and 32 bits when
    /// alpha channel is needed.
    /// @param[in] usealpha If true, some of the bits per pixel are reserved for an alpha channel. This works ONLY for 16 and
    /// 32 bits. If \a bpp = 16 and \a usealpha is true, 4 four bits are allocated for red, green, blue and alpha. If \a bpp is 32, 8 bits
    /// are allocated for each of the four channels. See \a bpp to see the bitmap when \a usealpha is false. If \a bpp is 24,
    /// \a usealpha is ignored.
    /// @param[in] mipmapped If true, a pyramid of textures are generated for each level of a mipmap.
    /// @return true if the texture is successfully created.
    /// @see uploadImage()
    /// @see isCompatibleWith()
    /// @see gcgIMAGE::createImage()
    /// @since 0.01.6
    bool createTexture(unsigned int width, unsigned int height, unsigned char bpp, bool usealpha, bool mipmapped = false);

    /// @brief Loads the contents of an image into an existing texture. If the current texture is not compatible with \a srcimage, it
    /// returns false. If the texture was not allocated yet, it creates a new texture compatible with \a srcimage and with its contents.
    /// The actual texture allocated in the graphics systems has power of 2. Thus, it uses the smallest power of 2 greater than the
    /// width and height of \a srcimage. The \a srcimage's bits per pixel, or bpp, may be 4, 8, 16, 24 or 32 bits, and the internal
    /// graphics system attributes are selected accordingly, depending if \a srcimage has an alpha channel. If bpp is 4 or 8, then the
    /// texture indicates luminance (pixel brightness) given by \a srcimage's palette colors. If \a bpp is 16 (with no alpha channel),
    /// 5 bits are allocated for red and blue channels, and 6 bits for the green channel. If \a bpp is 32 (with no alpha channel), 8
    /// bits are allocated for red, green and blue channels and the remaining 8 bits are ignored. If an alpha channel is present in
    /// \a srcimage, some of the bits of the texture are reserved for it. This works ONLY for 16 and 32 bits. If \a bpp = 16, there are
    /// 2 possible mappings (depending on \a srcimage) for red, green, blue and alpha respectively: (4, 4, 4, 4) or (5, 5, 5, 1). If
    /// \a bpp is 32, 8 bits are allocated for each of the four channels. If \a bpp is 24, no alpha channel is possible.
    /// @param[in] srcimage A valid gcgIMAGE object whose pixel contents are to be copied into the texture.
    /// @param[in] destposX Column coordinate of the texture to where \a srcimage's column 0 has to be copied.
    /// @param[in] destposY Row coordinate of the texture to where \a srcimage's row 0 has to be copied.
    /// @param[in] level Indicates the mipmap level of the current texture to where \a srcimage must be copied, if the current texture
    /// is mipmapped.
    /// @param[in] mipmapped If true, a pyramid of images are generated from \a srcimage and stored in each level of a mipmap.
    /// @return true if the image's content is copied into the graphics system's texture, or a new texture was created.
    /// @see createTexture()
    /// @see isCompatibleWith()
    /// @since 0.01.6
    bool uploadImage(gcgIMAGE *srcimage, int destposX = 0, int destposY = 0, unsigned int level = 0, bool mipmapped = false);

    /// @brief Checks if the current texture is compatible with the \a srcimage. They are compatible if the internal parameters of
    /// the graphics system needed to store the image and the texture are the same. It depends on the image's bits per pixel and if
    /// it has an alpha channel. Checking the compatibility is useful for copying the image's content into the texture by using
    /// uploadImage().
    /// @param[in] srcimage A valid gcgIMAGE object.
    /// @return true if the image is compatible with the current texture.
    /// @see createTexture()
    /// @see uploadImage()
    /// @since 0.01.6
    bool isCompatibleWith(gcgIMAGE *srcimage);

    /// @brief Binds a texture in the graphics system. Subsequent references to a texture will be addressed to the current
    /// texture. A later call to \a unbind() is mandatory to keep the system stable.
    /// @return true if the image was bound and available for texture mappings.
    /// @remarks Modifies several graphics library features: texture enabling and current matrix mode.
    /// @see unbind()
    /// @see createTexture()
    /// @see uploadImage()
    /// @since 0.01.6
    bool bind();

    /// @brief Unbinds a texture from the graphics system. It is called after a call to bind(). If this is not the case, the
    /// result is impredictable.
    /// @return true if the image was correctly unbound.
    /// @remarks Modifies several graphics library features: texture enabling and current matrix mode
    /// @see bind()
    /// @since 0.01.6
    bool unbind();
};



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////  COMMUNICATION macros, classes, and functions ///////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/// @defgroup inet Network communication
/// GCGlib has two classes for connection based peer to peer communication: gcgINETPEER and gcgINETSERVICE.
///@{
///@}

/// @defgroup inetcodes Communication event codes
/// @brief Codes for event management by gcgINETPEER::waitEvent() and gcgINETSERVICE::eventHandler()
///@{
/// @ingroup inet

// Event codes for waitEvent() of gcgINETPEER

/// @brief  Indicates that the peer is not ready for communication, an error occured or the peer is
/// disconnected
#define GCG_EVENT_NOTREADYORDISCONNECTED  0x0

/// @brief  Indicates that the peer is ready to receive messages.
#define GCG_EVENT_RECEIVEREADY            0x1

/// @brief  Indicates that the peer is ready to send messages. Even if the peer is ready to send, it
/// does not imply that the caller will not block. This also depends on the size of the message.
#define GCG_EVENT_SENDREADY               0x2

/// @brief  Indicates that the peer is ready to receive or send messages.
#define GCG_EVENT_RECEIVESENDREADY        (GCG_EVENT_RECEIVEREADY | GCG_EVENT_SENDREADY) // 3

// Extra event codes for eventHandler() of gcgINETSERVICE

/// @brief  Indicates that the peer was inserted by processEvents().
#define GCG_EVENT_INSERTED                0x4

/// @brief  Indicates that the peer was removed by processEvents().
#define GCG_EVENT_REMOVED                 0x8

/// @brief  Indicates that the peer was flagged to be visited by eventHandler().
#define GCG_EVENT_VISIT                   0x10

/// @brief  Indicates that a new connection was accepted.
#define GCG_EVENT_NEWCONNECTION           0x20
///@}

/// @defgroup inetclass Connection based classes
///@{
/// @ingroup inet

//////////////////////////////////////////////////////////////////////////////
/// @brief Implements methods for peer-to-peer communication using TCP/IP
/// protocol.
///
/// After the connection, the local IP and the remote IP are available for the
/// user as well as the local and remote port numbers. The user can wait for
/// events (reading, writing) using waitEvents() method. This is useful for
/// probing if the peer is ready for sending or writing. The shutdownSend()
/// and shutdownReceive() methods are useful for stoping full duplex
/// communication, which is important to save system resources.
///
/// @since 0.01.6
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgINETPEER   :  public gcgCLASS {
  public:
    int   local_ip[4];  ///< Local IP.
    int   local_port;   ///< Local Port.
    bool  isConnected;  ///< True if this peer is connected.

    int   remote_ip[4]; ///< Remote peer IP.
    int   remote_port;  ///< Remote port.

    void  *handle;      ///< Internal handle of this peer.

  public:
    /// @brief Constructs a valid but disconnected peer.
    gcgINETPEER();

    /// @brief Calls disconnect() and frees all resources.
    virtual ~gcgINETPEER(); // Safely disconnects the peer

    /// @brief Connects to an INET host described by \a host using port \a port.
    /// @param[in] host Null-terminated string that defines the host address.
    /// @param[in] port Integer value identifying the target port.
    /// @return true if the connection is established. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see disconnect()
    /// @see getConnectionFrom()
    bool connectToHost(const char *host, int port);

    /// @brief Sends a byte sequence to the remote peer.
    ///
    /// It may block the caller if the buffer is full. Use waitEvent() with
    /// \a checkSend = true to check if the buffer is completely full. Even if the
    /// peer is ready to send, it does not imply that the caller will not block.
    /// This also depends on the size of the message.
    /// @param[in] buffer pointer of the data.
    /// @param[in] nbytes number of bytes to be sent.
    /// @return true if the message was correctly sent. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem. After the call,
    /// always check the attribute \a isConnected to verify if it is still connected.
    /// @see waitEvent()
    /// @see receive()
    /// @see shutdownSend()
    bool send(void *buffer, unsigned int nbytes);

    /// @brief Receives a byte sequence from the remote peer.
    ///
    /// It may block the caller if the number of bytes \a nbytes is not available. Use waitEvent() with
    /// \a checkReceive = true to check if there are bytes to be read. Even if the
    /// peer is ready to receive, it does not imply that the caller will not block.
    /// This also depends on the requested number of bytes.
    /// @param[out] buffer pointer of the data.
    /// @param[in] nbytes number of bytes to be received.
    /// @return the number of bytes received. If it returns 0,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem. If a friendly disconnection
    /// has ocurred, the code will be \a GCG_CONNECTIONCLOSED. After the call, always check the attribute
    /// \a isConnected to verify if it is still connected.
    /// @see waitEvent()
    /// @see receive()
    /// @see shutdownReceive()
    int receive(void *buffer, unsigned int nbytes);

    /// @brief Gets the connection of oldpeerobject by moving its contents, resulting
    ///        in a connection migration.
    ///
    /// If succesful, \a oldpeerobject becomes disconnected and, in his place, this
    /// object can be used for continuing communication.
    /// @param[in] oldpeerobject already connected peer object.
    /// @return true if the a migration was made. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see connectToHost()
    /// @see disconnect()
    bool getConnectionFrom(gcgINETPEER *oldpeerobject);

    /// @brief Stops the functionality of sending messages.
    ///
    /// This function informs to the system that the connection will only receive
    /// messages. This is important to save resources. In this case the output
    /// queue will not occupy memory space. Further trials of sending messages
    /// will result in error.
    /// @return true if the shutdown is done. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see shutdownReceive()
    bool shutdownSend();

    /// @brief Stops the functionality of receiving messages.
    ///
    /// This function informs to the system that the connection will only send
    /// messages. This is important to save resources. In this case the input
    /// queue will not occupy memory space. Further trials of receiving messages
    /// will result in error.
    /// @return true if the shutdown is done. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see shutdownSend()
    bool shutdownReceive();

    /// @brief Safely breaks current connection.
    ///
    /// Disconnects the local and remote peers.
    /// @see connectToHost()
    /// @see getConnectionFrom()
    /// @return Returns true if the peer was correctly disconnected. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    bool disconnect();

    /// @brief Checks if the connection is ready for sending/receiving messages.
    ///
    /// Blocks the caller until: an event happens or the timeout is elapsed.
    /// Returns 0 (\a GCG_EVENT_NOTREADYORDISCONNECTED), if the timeout is elapsed
    /// (GCG_REPORT_MESSAGE(gcgGetReport()) = \a GCG_TIMEOUT) or the connection is broken or
    /// an unrecoverable error occurs. If \a checkReceive is true, it waits for incoming
    /// messages. Returns 1 (\a GCG_EVENT_RECEIVEREADY) when a message is available. If
    /// \a checkSend is true, it waits until a message can be sent without blocking a
    /// send() call. Returns 2 (\a GCG_EVENT_SENDREADY) when the peer is ready to send
    /// a new message. If \a checkReceive and \a checkSend are both true, it may return 1
    /// (\a GCG_EVENT_RECEIVEREADY) or 2 (\a GCG_EVENT_SENDREADY) as described above.
    /// Returns 3 ( \a GCG_EVENT_ALLREADY), when a message is available AND the peer is
    /// ready to send. If both \a checkReceive and \a checkSend are false, then it just
    /// checks for errors or disconnection.
    /// @param[in] checkReceive pass true if waitEvent() should check if there are incoming messages.
    /// @param[in] checkSend pass true if waitEvent() should check if the output buffer is not
    /// completely full. Even if the peer is ready to send, it does not imply that calling send() will not
    /// block. This also depends on the size of the message.
    /// @param[in] timeoutUsec maximum time in microseconds to wait if no event occured. A negative
    /// value means that waitEvent() must wait indefinitely for an event or error.
    /// A positive value means that after \a timeoutUsec microseconds it must return ( GCG_REPORT_MESSAGE(gcgGetReport()) =
    /// \a GCG_TIMEOUT) unless an event has occured.
    /// @return a bit mask composed of combinations of \a GCG_EVENT_RECEIVEREADY (0x1) and \a
    /// GCG_EVENT_SENDREADY (0x2) when events occurs, or \a GCG_EVENT_NOEVENTORDISCONNECTED (0x0)
    /// if the peer is not ready for communication. If it returns \a GCG_EVENT_NOEVENTORDISCONNECTED,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    int waitEvent(bool checkReceive = true, bool checkSend = false, int timeoutUsec = -1);
};


//////////////////////////////////////////////////////////////////////////////
/// @brief Class with methods to listen a specific port and, as additionnal
/// functionality, manage multiple peers. Methods for insertion, removal and
/// visiting peers are provided.
///
/// The method processEvents() is responsible for new connections accepted for
/// the listening port, and send/receive events for peer members. Additionaly,
/// this method informs when a peer is inserted or removed. All these events are
/// informed by calls to a pure virtual method eventHandler() that must be defined
/// by the programmer. Method processEvents() processes events in rounds of some
/// amount of time. To specify this amount of time for waiting events use the
/// setTimeout() method. It blocks the calling process until a postExit() call
/// flags it to finish event processing. The events are treated in parallel using
/// a thread pool where multiple calls to eventHandler() may be running. Thus,
/// the programmer must be careful of using non-local variables or resources
/// inside eventHandler(). The number of threads is specified by a parameter of
/// the processEvents() call. All methods of this class are thread safe. Only one
/// instance of processEvents is allowed to run at a time. If no processEvents() is
/// running, new connections and peer events are not treated. All peers must be
/// inserted by calling insertPeer(), even the connected peers accepted from the listening
/// port. In a round of processing of processEvents(), only one event is processed
/// at a time for a given peer, even thought multiple peers might be being processed
/// in parallel. Method processEvents() works by multiplexing input/output of
/// multiple peers using the select() function with sockets. This is much more
/// efficient and scalable than using a exclusive thread for each peer.
///
/// @since 0.01.6
//////////////////////////////////////////////////////////////////////////////
class    GCG_API_CLASS    gcgINETSERVICE   :  public gcgCLASS {
  public:
    bool  isListening; ///< True if the service is listening a port.
    void *handle;      ///< Internal handle of this service.

  public:
    /// @brief Constructs a valid service but still not capable of accepting connections.
    gcgINETSERVICE();

    /// @brief If processEvents() is running, signals it to stop handling processes and exit. Then calls
    /// stopListening() and frees all resources.
    /// @see processEvents()
    virtual ~gcgINETSERVICE();

    /// @brief Prepares the service to listen the desired port. If successful, the service becomes ready
    /// to accept new clients by the specified \a port. New connections are managed by each processing
    /// round of processEvents(). When a new connection is accepted by processEvents(), it calls
    /// eventHandler() with the new peer and the event bit \a GCG_EVENT_NEWCONNECTION on.
    /// @param[in] port port to be used by clients for connecting to this service.
    /// @return true if the service is ready to accept new connections. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see stopListening()
    /// @see processEvents()
    bool listenPort(int port);

    /// @brief Stops the listening, shutting down and closing the service peer. No further connections
    /// are accepted.
    /// @return true if the service was correctly stoped. If it returns false,
    /// check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see listenPort()
    /// @see processEvents()
    bool stopListening();

    /// @brief Insert a new \a peer to the service group. The \a peer must be connected and is
    /// inserted with event flags \a checkReceive = true and \a checkSend = false (see flagEvents()).
    /// If correctly inserted, the next round of processing of processEvents() calls eventHandler() for
    /// the \a peer with the bit \a GCG_EVENT_INSERTED on. After insertion, the \a peer communication can be
    /// managed by the service group in conjunction with other peers, saving resources and optimizing
    /// responses. Normally, a peer is inserted in the virtual (callback) function eventHandler() after
    /// being accepted by a new connection event \a GCG_EVENT_NEWCONNECTION. After insertion, this function
    /// wakes up the processEvents() if it is blocked.
    /// @param[in] peer new peer to be inserted to the service group. If succesfully inserted, the original
    /// peer must not be deleted. It must be deleted by processEvents() and eventHandler() upon
    /// removal events (see postRemove() and postRemoveAll()).
    /// @return true if the peer is inserted . If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport())
    /// for knowing the problem.
    /// @see getPeerCount()
    /// @see flagEvents()
    /// @see postRemove()
    /// @see postRemoveAll()
    /// @see processEvents()
    /// @see eventHandler()
    bool insertPeer(gcgINETPEER *peer);

    /// @brief Gets the number of peers of the service group.
    /// @return If successful, returns the current number of peers grouped into the service. If it
    /// returns -1, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertPeer()
    /// @see postRemove()
    /// @see postRemoveAll()
    /// @see processEvents()
    /// @see eventHandler()
    int getPeerCount();

    /// @brief Flags which communication events are to be checked for a specific \a peer during a round
    /// of processing of processEvents(). If \a checkReceive is true, the processEvents() will check
    /// if there are available messages and, if so, will call the eventHandler() function with
    /// \a GCG_EVENT_RECEIVEREADY bit on. If \a checkSend is true, the event verification will check if
    /// the \a peer can send messages and, if so, will call the eventHandler() function with
    /// \a GCG_EVENT_SENDREADY bit on. If \a checkSend and \a checkReceive are both true, both events are
    /// checked in each round and, if detected, are reported to processEvents() with respective bits
    /// flagged. If both parameters are false, then event processor just watchs for errors or
    /// disconnection. Note that processEvents() calls eventHandler() for other events like insertions,
    /// new connections, visitations and removals.
    /// @param[in] peer peer to be checked using the parameters. The peer must have been included in the
    /// service group.
    /// @param[in] checkReceive pass true if processEvents() should check if there are incoming messages.
    /// @param[in] checkSend pass true if processEvents() should check if the output buffer is not
    /// completely full. Even if the peer is ready to send, it does not imply that calling send() will not
    /// block. This also depends on the size of the message.
    /// @return true if the flags are updated for the peer. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see insertPeer()
    /// @see setTimeout()
    /// @see getPeerCount()
    /// @see postRemove()
    /// @see postRemoveAll()
    /// @see processEvents()
    /// @see eventHandler()
    bool flagEvents(gcgINETPEER *peer, bool checkReceive, bool checkSend);

    /// @brief Flags the \a peer to be removed in the next round of processing of processEvents(). After
    /// the \a peer flag is changed, this function wakes up the processEvents() if it is blocked. It causes
    /// processEvents() to call eventHandler with a \a GCG_EVENT_REMOVED flagged for the \a peer. The
    /// eventHandler() must delete/release the \a peer since processEvents() only removes it from the
    /// service group.
    /// @param[in] peer peer to be removed. The peer must have been included in the service group or
    /// a warning is issued.
    /// @return true if the peer is flagged to be removed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see postRemoveAll()
    /// @see processEvents()
    /// @see eventHandler()
    bool postRemove(gcgINETPEER *peer);

    /// @brief Flags all the peers of the service group to be removed in the next round of processing
    /// of processEvents(). This function wakes up the processEvents() if it is blocked. After removals,
    /// the service keeps accepting new connections. It causes processEvents() to call eventHandler with
    /// a \a GCG_EVENT_REMOVED flagged for all the peers grouped in the service. The eventHandler() must
    /// delete/release the each peer since processEvents() only removes it from the service group.
    /// @return true if the peers (if any) were flagged to be removed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see postRemove()
    /// @see processEvents()
    /// @see eventHandler()
    bool postRemoveAll();

    /// @brief Flags the \a peer to be visited in the next round of processing of processEvents().
    /// Visiting is a strategy for programmers to apply specific tasks to a peer. After
    /// the \a peer flag is changed, this function wakes up the processEvents() if it is blocked.
    /// @param[in] peer peer to be visited. The peer must have been included in the service group or
    /// a warning is issued.
    /// @return true if the peer is flagged to be visited. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see postVisitAll()
    /// @see processEvents()
    /// @see eventHandler()
    bool postVisit(gcgINETPEER *peer);

    /// @brief Flags all the peers of the service group to be visited in the next round of processing
    /// of processEvents(). Visiting is a strategy for programmers to apply specific tasks to peers.
    /// This function wakes up the processEvents() if it is blocked.
    /// @return true if the peers (if any) were flagged to be visited. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see postVisit()
    /// @see processEvents()
    /// @see eventHandler()
    bool postVisitAll();

    /// @brief Flags the processEvents() to process all remaining events, release the thread pool used
    /// to execute several instances of eventHandler(), and exit safely. This function wakes up the
    /// processEvents() if it is blocked.
    /// @return true if the peer is flagged to be removed. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see postRemoveAll()
    /// @see processEvents()
    /// @see eventHandler()
    bool postExit();

    /// @brief The method processEvents() is responsible for new connections accepted for
    /// the listening port, and send/receive events for peer members. Additionaly,
    /// this method informs when a peer is inserted or removed. All these events are
    /// informed by calls to a pure virtual method eventHandler() that must be defined
    /// by the programmer. Method processEvents() processes events in rounds of some
    /// amount of time. To specify this amount of time for waiting events use the
    /// setTimeout() method. It blocks the calling process until a postExit() call
    /// flags it to finish event processing. The events are treated in parallel using
    /// a thread pool where multiple calls to eventHandler() may be running. Thus,
    /// the programmer must be careful of using non-local variables or resources
    /// inside eventHandler(). The number of threads is specified by a parameter of
    /// the processEvents() call. All methods of this class are thread safe. Only one
    /// instance of processEvents is allowed to run at a time. If no processEvents() is
    /// running, new connections and peer events are not treated. All peers must be
    /// inserted by calling insertPeer(), even the connected peers from the listening
    /// port. In a round of processing of processEvents(), only one event is processed
    /// at a time for a given peer, even thought multiple peers might be being processed
    /// in parallel. Method processEvents() works by multiplexing input/output of
    /// multiple peers using the select() function with sockets. This is much more
    /// efficient and scalable than using a exclusive thread for each peer. To extend funcionality
    /// for users, a peer visitation mechanism is also supported.
    /// @param[in] numThreads number of thread to be created in a thread pool. When an event occurs,
    /// processEvents() assigns a job to a free thread to execute an instance of eventHandler(). If no
    /// thread is available, processEvents() blocks until a job finish to execute eventHandler(). Thus,
    /// It is important that eventHandler() be fast and thread safe, with careful access to non-local
    /// variables. Tipically, the number of threads should match the number of processors of the machine.
    /// Use gcgGetNumberOfProcessors() for this purpose.
    /// @return true if exits normally, without any errors. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see flagEvents()
    /// @see postRemove()
    /// @see postRemoveAll()
    /// @see postVisit()
    /// @see postVisitAll()
    /// @see eventHandler()
    /// @see setTimeout()
    /// @see gcgGetNumberOfProcessors()
    bool processEvents(unsigned int numThreads = gcgGetNumberOfProcessors());

    /// @brief The method processEvents() processes events in rounds of some
    /// amount of time. To specify this amount of time for waiting events use the
    /// setTimeout() method. The default timeout is 100 miliseconds. It is a thread safe function.
    /// @param[in] timeoutUsec timeout to be used in processEvents() in microseconds.
    /// @return true if the timeout was updated. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see processEvents()
    /// @see eventHandler()
    bool setTimeout(int timeoutUsec);

    /// @brief Pure virtual method to be defined by the user in a specialized class for a service.
    /// This methods is called by processEvents() for every event occured. When a \a GCG_EVENT_REMOVED
    /// event is flagged, the eventHandler() must release the resources of the \a peer since processEvents()
    /// only removes the \a peer from the service group. Method processEvents() use a thread pool (see
    /// gcgTHREADPOOL), to call multiple instances of eventHandler at a time. It is important that
    /// eventHandler() be fast and thread safe, with careful access to non-local variables.
    ///
    /// @param[in] events a 32bit mask formed by a combination of bitwise or of event codes. Ex.
    /// \a GCG_EVENT_INSERTED, \a GCG_EVENT_REMOVED, \a GCG_EVENT_VISIT, \a GCG_EVENT_NEWCONNECTION,
    /// \a GCG_EVENT_RECEIVEREADY and \a GCG_EVENT_SENDREADY.
    /// @param[in] peer peer for which the events must be processed.
    /// @see processEvents()
    /// @see setTimeout()
    virtual void eventHandler(int events, gcgINETPEER *peer) = 0;
};

///@}

// End of definitions included once
#endif // #if _COUNTER_GCG_ == 1

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////   SPECIALIZATION OF CLASSES WITH MULTIPLE TYPES   //////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


// Next definitions are inserted more than once

// Define the type
#undef NUMTYPE
#undef COERSIONFLOAT
#undef COERSIONDOUBLE
#undef COERSIONSHORT
#undef COERSIONINT
#undef COERSIONLONG
#if   _COUNTER_GCG_ == 1
  #define NUMTYPE float
  #define COERSIONFLOAT float
  #define COERSIONDOUBLE double
  #define COERSIONSHORT float
  #define COERSIONINT float
  #define COERSIONLONG float
#elif _COUNTER_GCG_ == 2
  #define NUMTYPE double
  #define COERSIONFLOAT double
  #define COERSIONDOUBLE double
  #define COERSIONSHORT double
  #define COERSIONINT double
  #define COERSIONLONG double
#elif _COUNTER_GCG_ == 3
  #define NUMTYPE short
  #define COERSIONFLOAT float
  #define COERSIONDOUBLE double
  #define COERSIONSHORT short
  #define COERSIONINT int
  #define COERSIONLONG long
#elif _COUNTER_GCG_ == 4
  #define NUMTYPE int
  #define COERSIONFLOAT float
  #define COERSIONDOUBLE double
  #define COERSIONSHORT int
  #define COERSIONINT int
  #define COERSIONLONG long
#elif _COUNTER_GCG_ == 5
  #define NUMTYPE long
  #define COERSIONFLOAT float
  #define COERSIONDOUBLE double
  #define COERSIONSHORT long
  #define COERSIONINT long
  #define COERSIONLONG long
#endif

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////     UNIDIMENSIONAL SIGNALS     ////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/// @brief Class for 1D signal definition and processing.
/// @tparam NUMTYPE Type of the samples representing the signal. Supported types: \e float, \e double, \e long, \e int and \e short.
///
/// @since 0.01.6
/// @ingroup discrete
//////////////////////////////////////////////////////////////////////////////
template <>
class     GCG_API_CLASS    gcgDISCRETE1D<NUMTYPE>   :  public gcgCLASS {
  public:
    NUMTYPE      *data;           ///< Pointer to the signal samples.
    unsigned int length;          ///< Signal length = number of samples.
    bool         isstaticdata;    ///< True if the data pointer \a data must not be deleted by this object.

    int          origin;          ///< Origin coordinate: indicates the sample position of the origin (x = 0) of the signal.
    int          extension;       ///< Defines the way the borders have to be extended.

  public:
    /// @brief Constructs a valid but empty unidimensional signal. The signal can be used as destiny in any gcgDISCRETE1D<NUMTYPE> method.
    /// @see ~gcgDISCRETE1D()
    gcgDISCRETE1D();

    /// @brief Constructs a valid unidimensional signal and allocates its resources by calling createSignal().
    /// @param[in] length signal length or number of samples. It must be non-zero.
    /// @param[in] origin sample position indicating the origin of the signal.
    /// @param[in] sampledata pointer to a memory block with at least \a length elements of \a NUMTYPE that must be used as the data buffer by
    /// all methods. If NULL, a new data block is allocated. If it is static, set \a isstaticdata as true to indicate that it must not be
    /// deleted upon instance destruction.
    /// @param[in] isstaticdata if true, indicates that the \a sampledata pointer must not be deleted upon object destruction. If false, the
    /// \a sampledata will be deleted whenever necessary.
    /// @param[in] borderextension indicates the border extension mode for sample accesses outside the signal limits. It must be
    /// GCG_BORDER_EXTENSION_ZERO, GCG_BORDER_EXTENSION_CLAMP, GCG_BORDER_EXTENSION_PERIODIC, GCG_BORDER_EXTENSION_SYMMETRIC_NOREPEAT
    /// or GCG_BORDER_EXTENSION_SYMMETRIC_REPEAT.
    /// @see createSignal()
    /// @see ~gcgDISCRETE1D()
    gcgDISCRETE1D(unsigned int length, int origin, NUMTYPE *sampledata = NULL, bool isstaticdata = false, int borderextension = GCG_BORDER_EXTENSION_CLAMP);

    /// @brief Frees all signal resources by calling destroySignal().
    /// @see gcgDISCRETE1D()
    virtual ~gcgDISCRETE1D();

    /// @brief Unidimensional creation. Allocates all necessary space for the signal indicated by the parameters.
    /// @param[in] length signal length or number of samples. It must be non-zero.
    /// @param[in] origin sample position indicating the origin of the signal.
    /// @param[in] sampledata pointer to a memory block with at least \a length elements of \a NUMTYPE that must be used as the data buffer by
    /// all methods. If NULL, a new data block is allocated. Set \a isstaticdata as true to indicate that it must not be deleted upon instance
    /// destruction.
    /// @param[in] isstaticdata if true, indicates that the \a sampledata pointer must not be deleted upon object destruction. If false, the
    /// \a sampledata will be deleted whenever necessary.
    /// @param[in] borderextension indicates the border extension mode for sample accesses outside the signal limits. It must be
    /// GCG_BORDER_EXTENSION_ZERO, GCG_BORDER_EXTENSION_CLAMP, GCG_BORDER_EXTENSION_PERIODIC, GCG_BORDER_EXTENSION_SYMMETRIC_NOREPEAT
    /// or GCG_BORDER_EXTENSION_SYMMETRIC_REPEAT.
    /// @return true if the signal is correctly created. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createSimilar()
    /// @see duplicateSignal()
    /// @see duplicateSubsignal()
    /// @see destroySignal()
    bool createSignal(unsigned int length, int origin, NUMTYPE *sampledata = NULL, bool isstaticdata = false, int borderextension = GCG_BORDER_EXTENSION_CLAMP);

    /// @brief Releases all resources used by the signal. After destroyed, the signal becomes invalid and must be recreated.
    /// @return true if the signal was released. If it returns false, check GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createSignal()
    /// @see createSimilar()
    bool destroySignal();

    /// @brief Creates a signal with the same length, origin and border extension of another source signal. This is useful for
    /// creating temporary signals compatible with the source.
    /// @param[in] source pointer to the source signal. It must be non null. A warning is issued if it is not a valid signal. The destiny
    /// signal receives all attributes of the source signal: length, origin and border extension. The gcgDISCRETE1D::data is
    /// allocated but not copied.
    /// @return true if the current signal is correctly created and similar to the \a source. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createSignal()
    /// @see duplicateSignal()
    /// @see duplicateSubsignal()
    /// @see destroySignal()
    /// @see isCompatibleWith()
    bool createSimilar(gcgDISCRETE1D<float> *source);

    /// @brief Creates a signal with the same length, origin and border extension of another source signal. This is useful for
    /// creating temporary signals compatible with the source.
    /// @param[in] source pointer to the source signal. It must be non null. A warning is issued if it is not a valid signal. The destiny
    /// signal receives all attributes of the source signal: length, origin and border extension. The gcgDISCRETE1D::data is
    /// allocated but not copied.
    /// @return true if the current signal is correctly created and similar to the \a source. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createSignal()
    /// @see duplicateSignal()
    /// @see duplicateSubsignal()
    /// @see destroySignal()
    /// @see isCompatibleWith()
    bool createSimilar(gcgDISCRETE1D<double> *source);

    /// @brief Creates a signal with the same length, origin and border extension of another source signal. This is useful for
    /// creating temporary signals compatible with the source.
    /// @param[in] source pointer to the source signal. It must be non null. A warning is issued if it is not a valid signal. The destiny
    /// signal receives all attributes of the source signal: length, origin and border extension. The gcgDISCRETE1D::data is
    /// allocated but not copied.
    /// @return true if the current signal is correctly created and similar to the \a source. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createSignal()
    /// @see duplicateSignal()
    /// @see duplicateSubsignal()
    /// @see destroySignal()
    /// @see isCompatibleWith()
    bool createSimilar(gcgDISCRETE1D<short> *source);

    /// @brief Creates a signal with the same length, origin and border extension of another source signal. This is useful for
    /// creating temporary signals compatible with the source.
    /// @param[in] source pointer to the source signal. It must be non null. A warning is issued if it is not a valid signal. The destiny
    /// signal receives all attributes of the source signal: length, origin and border extension. The gcgDISCRETE1D::data is
    /// allocated but not copied.
    /// @return true if the current signal is correctly created and similar to the \a source. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createSignal()
    /// @see duplicateSignal()
    /// @see duplicateSubsignal()
    /// @see destroySignal()
    /// @see isCompatibleWith()
    bool createSimilar(gcgDISCRETE1D<int> *source);

    /// @brief Creates a signal with the same length, origin and border extension of another source signal. This is useful for
    /// creating temporary signals compatible with the source.
    /// @param[in] source pointer to the source signal. It must be non null. A warning is issued if it is not a valid signal. The destiny
    /// signal receives all attributes of the source signal: length, origin and border extension. The gcgDISCRETE1D::data is
    /// allocated but not copied.
    /// @return true if the current signal is correctly created and similar to the \a source. If it returns false, check
    /// GCG_REPORT_MESSAGE(gcgGetReport()) for knowing the problem.
    /// @see createSignal()
    /// @see duplicateSignal()
    /// @see duplicateSubsignal()
    /// @see destroySignal()
    /// @see isCompatibleWith()
    bool createSimilar(gcgDISCRETE1D<long> *source);

    bool isCompatibleWith(gcgDISCRETE1D<float> *source); // Checks if both signals are compatible: same dimensions, same origin.
    bool isCompatibleWith(gcgDISCRETE1D<double> *source);
    bool isCompatibleWith(gcgDISCRETE1D<short> *source);
    bool isCompatibleWith(gcgDISCRETE1D<int> *source);
    bool isCompatibleWith(gcgDISCRETE1D<long> *source);
    bool duplicateSignal(gcgDISCRETE1D<float> *source); // Makes an independent copy of the source signal.
    bool duplicateSignal(gcgDISCRETE1D<double> *source);
    bool duplicateSignal(gcgDISCRETE1D<short> *source);
    bool duplicateSignal(gcgDISCRETE1D<int> *source);
    bool duplicateSignal(gcgDISCRETE1D<long> *source);
    bool duplicateSubsignal(gcgDISCRETE1D<float> *source, int left, unsigned int width); // Makes an independent copy of the source subsignal.
    bool duplicateSubsignal(gcgDISCRETE1D<double> *source, int left, unsigned int width);
    bool duplicateSubsignal(gcgDISCRETE1D<short> *source, int left, unsigned int width);
    bool duplicateSubsignal(gcgDISCRETE1D<int> *source, int left, unsigned int width);
    bool duplicateSubsignal(gcgDISCRETE1D<long> *source, int left, unsigned int width);

    /////////////////////////////////////////////////////////////
    // Data access and modification. Not recommended for high
    // performance processes. Uses the origin and border extension.
    /////////////////////////////////////////////////////////////
    NUMTYPE getDataSample(int i);
    bool setDataSample(int i, NUMTYPE value);

    /////////////////////////////////////////////////////////////
    // Signal processing functions
    // The src can be the destination (this).
    /////////////////////////////////////////////////////////////
    bool normalize(gcgDISCRETE1D<float> *src, float floor = 0, float ceil = 1);
    bool normalize(gcgDISCRETE1D<double> *src, double floor = 0, double ceil = 1);
    bool normalize(gcgDISCRETE1D<short> *src, short floor = 0, short ceil = 1);
    bool normalize(gcgDISCRETE1D<int> *src, int floor = 0, int ceil = 1);
    bool normalize(gcgDISCRETE1D<long> *src, long floor = 0, long ceil = 1);
    bool convolution(gcgDISCRETE1D<NUMTYPE> *src, gcgDISCRETE1D<float> *mask);
    bool convolution(gcgDISCRETE1D<NUMTYPE> *src, gcgDISCRETE1D<double> *mask);
    bool convolution(gcgDISCRETE1D<NUMTYPE> *src, gcgDISCRETE1D<short> *mask);
    bool convolution(gcgDISCRETE1D<NUMTYPE> *src, gcgDISCRETE1D<int> *mask);
    bool convolution(gcgDISCRETE1D<NUMTYPE> *src, gcgDISCRETE1D<long> *mask);
    bool templateMatching(unsigned int imgleft, unsigned int imgwidth, gcgDISCRETE1D<float> *mask, int *position);
    bool templateMatching(unsigned int imgleft, unsigned int imgwidth, gcgDISCRETE1D<double> *mask, int *position);
    bool templateMatching(unsigned int imgleft, unsigned int imgwidth, gcgDISCRETE1D<short> *mask, int *position);
    bool templateMatching(unsigned int imgleft, unsigned int imgwidth, gcgDISCRETE1D<int> *mask, int *position);
    bool templateMatching(unsigned int imgleft, unsigned int imgwidth, gcgDISCRETE1D<long> *mask, int *position);

    // Computes the scalar product of two signals. At least one of the signals must have extension
    // GCG_BORDER_EXTENSION_ZERO. Aligns the origin of srcsignal2 with the sample of this object
    // with coordinate atX.
    COERSIONFLOAT  scalarProduct(int atX, gcgDISCRETE1D<float> *srcsignal2);
    COERSIONDOUBLE scalarProduct(int atX, gcgDISCRETE1D<double> *srcsignal2);
    COERSIONSHORT  scalarProduct(int atX, gcgDISCRETE1D<short> *srcsignal2);
    COERSIONINT    scalarProduct(int atX, gcgDISCRETE1D<int> *srcsignal2);
    COERSIONLONG   scalarProduct(int atX, gcgDISCRETE1D<long> *srcsignal2);

    // Produces a binary signal. The samples are mapped to: lessvalue, if sample is below the threshold; greaterequalvalue,
    // if the sample is greater or equal the threshold. The src can be the destination (this).
    bool binarize(gcgDISCRETE1D<float> *src, float threshold, NUMTYPE lessvalue = 0, NUMTYPE greaterequalvalue = 1);
    bool binarize(gcgDISCRETE1D<double> *src, double threshold, NUMTYPE lessvalue = 0, NUMTYPE greaterequalvalue = 1);
    bool binarize(gcgDISCRETE1D<short> *src, short threshold, NUMTYPE lessvalue = 0, NUMTYPE greaterequalvalue = 1);
    bool binarize(gcgDISCRETE1D<int> *src, int threshold, NUMTYPE lessvalue = 0, NUMTYPE greaterequalvalue = 1);
    bool binarize(gcgDISCRETE1D<long> *src, long threshold, NUMTYPE lessvalue = 0, NUMTYPE greaterequalvalue = 1);

    /////////////////////////////////////////////////////////////
    // Signal composition. Source signals must be compatible.
    // The destination can be one of the sources.
    /////////////////////////////////////////////////////////////
    bool scale(gcgDISCRETE1D<float> *srcsignal1, COERSIONFLOAT weight, COERSIONFLOAT addthis = 0); // Scales a signal: I = w * I1 + at
    bool scale(gcgDISCRETE1D<double> *srcsignal1, COERSIONDOUBLE weight, COERSIONDOUBLE addthis = 0);
    bool scale(gcgDISCRETE1D<short> *srcsignal1, COERSIONSHORT weight, COERSIONSHORT addthis = 0);
    bool scale(gcgDISCRETE1D<int> *srcsignal1, COERSIONINT weight, COERSIONINT addthis = 0);
    bool scale(gcgDISCRETE1D<long> *srcsignal1, COERSIONLONG weight, COERSIONLONG addthis = 0);
    bool power(gcgDISCRETE1D<float> *srcsignal1, COERSIONFLOAT power); // Powers a signal: I = I1^power
    bool power(gcgDISCRETE1D<double> *srcsignal1, COERSIONDOUBLE power);
    bool power(gcgDISCRETE1D<short> *srcsignal1, COERSIONSHORT power);
    bool power(gcgDISCRETE1D<int> *srcsignal1, COERSIONINT power);
    bool power(gcgDISCRETE1D<long> *srcsignal1, COERSIONLONG power);
    bool combineAdd(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<float> *srcsignal2, COERSIONFLOAT weight1 = 1, COERSIONFLOAT weight2 = 1);  // Combine two signals by addition: I = w1 * I1 + w2 * I2
    bool combineAdd(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<double> *srcsignal2, COERSIONDOUBLE weight1 = 1, COERSIONDOUBLE weight2 = 1);
    bool combineAdd(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<short> *srcsignal2, COERSIONSHORT weight1 = 1, COERSIONSHORT weight2 = 1);
    bool combineAdd(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<int> *srcsignal2, COERSIONINT weight1 = 1, COERSIONINT weight2 = 1);
    bool combineAdd(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<long> *srcsignal2, COERSIONLONG weight1 = 1, COERSIONLONG weight2 = 1);
    bool combineMult(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<float> *srcsignal2, COERSIONFLOAT add1 = 0, COERSIONFLOAT add2 = 0);  // Combine two signals by multiplication: I = (a1 + I1) * (a2 + I2)
    bool combineMult(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<double> *srcsignal2, COERSIONDOUBLE add1 = 0, COERSIONDOUBLE add2 = 0);
    bool combineMult(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<short> *srcsignal2, COERSIONSHORT add1 = 0, COERSIONSHORT add2 = 0);
    bool combineMult(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<int> *srcsignal2, COERSIONINT add1 = 0, COERSIONINT add2 = 0);
    bool combineMult(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<long> *srcsignal2, COERSIONLONG add1 = 0, COERSIONLONG add2 = 0);
    bool combineNorm(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<float> *srcsignal2); // Combine two signals by the L2 norm: I = sqrt(I1^2 + I2^2)
    bool combineNorm(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<double> *srcsignal2);
    bool combineNorm(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<short> *srcsignal2);
    bool combineNorm(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<int> *srcsignal2);
    bool combineNorm(gcgDISCRETE1D<NUMTYPE> *srcsignal1, gcgDISCRETE1D<long> *srcsignal2);

    /////////////////////////////////////////////////////////////
    // Interfaces for gcgIMAGE
    /////////////////////////////////////////////////////////////
    bool exportGrayScaleImage(gcgIMAGE *outimage, bool normalize);
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////////////////     BIDIMENSIONAL SIGNALS     ////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

template <>
class     GCG_API_CLASS    gcgDISCRETE2D<NUMTYPE>   :  public gcgCLASS {
  public:
    // Signal info and data
    NUMTYPE       *data;        ///< Signal samples
    unsigned int  width;        ///< Signal width  = number of columns
    unsigned int  height;       ///< Signal height = number of rows
    bool          isstaticdata; ///< True if the data pointer \a data must not be deleted by this object

    // Origin coordinate: indicates the position of the origin (x = 0, y = 0) of the signal.
    int    originX;     ///< Sample coordinate of the origin of the signal in X axis.
    int    originY;     ///< Sample coordinate of the origin of the signal in Y axis

    int    extensionX;  ///< Defines the way the borders in X have to be extended
    int    extensionY;  ///< Defines the way the borders in Y have to be extended

    int    errorcode;   ///< Code of the last error occured. Use gcgGetErrorString() for an intelligible error description.

  public:
    /////////////////////////////////////////////////////////////
    // Discrete signal construction
    /////////////////////////////////////////////////////////////
    gcgDISCRETE2D();
    gcgDISCRETE2D(unsigned int width, unsigned int length, int originX, int originY, NUMTYPE *sampledata = NULL,
                  bool isstaticdata = false, int borderextX = GCG_BORDER_EXTENSION_CLAMP, int borderextY = GCG_BORDER_EXTENSION_CLAMP);
    virtual ~gcgDISCRETE2D();

    /////////////////////////////////////////////////////////////
    // Empty discrete signal creation and destruction
    /////////////////////////////////////////////////////////////
    bool createSignal(unsigned int width, unsigned int height, int originX, int originY, NUMTYPE *sampledata = NULL,
                      bool isstaticdata = false, int borderextX = GCG_BORDER_EXTENSION_CLAMP, int borderextY = GCG_BORDER_EXTENSION_CLAMP);
    void destroySignal();  // Release all resources used by this discrete signal.

    /////////////////////////////////////////////////////////////
    // Discrete signal copying, duplication and conversion.
    /////////////////////////////////////////////////////////////
    bool createSimilar(gcgDISCRETE2D<float> *source); // Creates a signal similar as the source. The data is not copied.
    bool createSimilar(gcgDISCRETE2D<double> *source);
    bool createSimilar(gcgDISCRETE2D<short> *source);
    bool createSimilar(gcgDISCRETE2D<int> *source);
    bool createSimilar(gcgDISCRETE2D<long> *source);
    bool isCompatibleWith(gcgDISCRETE2D<float> *source); // Checks if both signals are compatible: same dimensions, same origin.
    bool isCompatibleWith(gcgDISCRETE2D<double> *source);
    bool isCompatibleWith(gcgDISCRETE2D<short> *source);
    bool isCompatibleWith(gcgDISCRETE2D<int> *source);
    bool isCompatibleWith(gcgDISCRETE2D<long> *source);
    bool duplicateSignal(gcgDISCRETE2D<float> *source); // Makes an independent copy of the source signal.
    bool duplicateSignal(gcgDISCRETE2D<double> *source);
    bool duplicateSignal(gcgDISCRETE2D<short> *source);
    bool duplicateSignal(gcgDISCRETE2D<int> *source);
    bool duplicateSignal(gcgDISCRETE2D<long> *source);
    bool duplicateSubsignal(gcgDISCRETE2D<float> *source, int left, int top, unsigned int width, unsigned int height); // Makes an independent copy of the source subsignal.
    bool duplicateSubsignal(gcgDISCRETE2D<double> *source, int left, int top, unsigned int width, unsigned int height);
    bool duplicateSubsignal(gcgDISCRETE2D<short> *source, int left, int top, unsigned int width, unsigned int height);
    bool duplicateSubsignal(gcgDISCRETE2D<int> *source, int left, int top, unsigned int width, unsigned int height);
    bool duplicateSubsignal(gcgDISCRETE2D<long> *source, int left, int top, unsigned int width, unsigned int height);

    /////////////////////////////////////////////////////////////
    // Data access and modification. Not recommended for high
    // performance processes. Uses the origin and border extension.
    /////////////////////////////////////////////////////////////
    NUMTYPE getDataSample(int i, int j);
    bool setDataSample(int i, int j, NUMTYPE value);

    /////////////////////////////////////////////////////////////
    // Signal processing functions
    // The src can be the destination (this).
    /////////////////////////////////////////////////////////////
    bool normalize(gcgDISCRETE2D<float> *src, float floor = 0, float ceil = 1);
    bool normalize(gcgDISCRETE2D<double> *src, double floor = 0, double ceil = 1);
    bool normalize(gcgDISCRETE2D<short> *src, short floor = 0, short ceil = 1);
    bool normalize(gcgDISCRETE2D<int> *src, int floor = 0, int ceil = 1);
    bool normalize(gcgDISCRETE2D<long> *src, long floor = 0, long ceil = 1);
    bool convolutionX(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE1D<float> *mask);
    bool convolutionX(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE1D<double> *mask);
    bool convolutionX(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE1D<short> *mask);
    bool convolutionX(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE1D<int> *mask);
    bool convolutionX(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE1D<long> *mask);
    bool convolutionY(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE1D<float> *mask);
    bool convolutionY(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE1D<double> *mask);
    bool convolutionY(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE1D<short> *mask);
    bool convolutionY(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE1D<int> *mask);
    bool convolutionY(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE1D<long> *mask);
    bool convolutionXY(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE2D<float> *mask);
    bool convolutionXY(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE2D<double> *mask);
    bool convolutionXY(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE2D<short> *mask);
    bool convolutionXY(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE2D<int> *mask);
    bool convolutionXY(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE2D<long> *mask);
    bool templateMatching(unsigned int imgleft, unsigned int imgbottom, unsigned int imgwidth, unsigned int imgheight, gcgDISCRETE2D<float> *mask, int *positionX, int *positionY);
    bool templateMatching(unsigned int imgleft, unsigned int imgbottom, unsigned int imgwidth, unsigned int imgheight, gcgDISCRETE2D<double> *mask, int *positionX, int *positionY);
    bool templateMatching(unsigned int imgleft, unsigned int imgbottom, unsigned int imgwidth, unsigned int imgheight, gcgDISCRETE2D<short> *mask, int *positionX, int *positionY);
    bool templateMatching(unsigned int imgleft, unsigned int imgbottom, unsigned int imgwidth, unsigned int imgheight, gcgDISCRETE2D<int> *mask, int *positionX, int *positionY);
    bool templateMatching(unsigned int imgleft, unsigned int imgbottom, unsigned int imgwidth, unsigned int imgheight, gcgDISCRETE2D<long> *mask, int *positionX, int *positionY);

    // Computes the scalar product of two signals. At least one of the signals must have extension
    // GCG_BORDER_EXTENSION_ZERO for X, and at least one of the signals must have extension
    // GCG_BORDER_EXTENSION_ZERO for Y. Aligns the origin of srcsignal2 with the sample of this object
    // with relative coordinates (atX, atY).
    COERSIONFLOAT scalarProduct(int atX, int atY, gcgDISCRETE2D<float> *srcsignal2);
    COERSIONDOUBLE scalarProduct(int atX, int atY, gcgDISCRETE2D<double> *srcsignal2);
    COERSIONSHORT scalarProduct(int atX, int atY, gcgDISCRETE2D<short> *srcsignal2);
    COERSIONINT scalarProduct(int atX, int atY, gcgDISCRETE2D<int> *srcsignal2);
    COERSIONLONG scalarProduct(int atX, int atY, gcgDISCRETE2D<long> *srcsignal2);

    // Produces a binary signal. The samples are mapped to: lessvalue, if sample is below the threshold; greaterequalvalue,
    // if the sample is greater or equal the threshold. The src can be the destination (this).
    bool binarize(gcgDISCRETE2D<float> *src, float threshold, NUMTYPE lessvalue = 0, NUMTYPE greaterequalvalue = 1);
    bool binarize(gcgDISCRETE2D<double> *src, double threshold, NUMTYPE lessvalue = 0, NUMTYPE greaterequalvalue = 1);
    bool binarize(gcgDISCRETE2D<short> *src, short threshold, NUMTYPE lessvalue = 0, NUMTYPE greaterequalvalue = 1);
    bool binarize(gcgDISCRETE2D<int> *src, int threshold, NUMTYPE lessvalue = 0, NUMTYPE greaterequalvalue = 1);
    bool binarize(gcgDISCRETE2D<long> *src, long threshold, NUMTYPE lessvalue = 0, NUMTYPE greaterequalvalue = 1);

    /////////////////////////////////////////////////////////////
    // Signal composition. Source signals must be compatible.
    // The destination can be one of the sources.
    /////////////////////////////////////////////////////////////
    bool scale(gcgDISCRETE2D<float> *srcsignal1, COERSIONFLOAT weight, COERSIONFLOAT addthis = 0); // Scales a signal: I = w * I1 + at
    bool scale(gcgDISCRETE2D<double> *srcsignal1, COERSIONDOUBLE weight, COERSIONDOUBLE addthis = 0);
    bool scale(gcgDISCRETE2D<short> *srcsignal1, COERSIONSHORT weight, COERSIONSHORT addthis = 0);
    bool scale(gcgDISCRETE2D<int> *srcsignal1, COERSIONINT weight, COERSIONINT addthis = 0);
    bool scale(gcgDISCRETE2D<long> *srcsignal1, COERSIONLONG weight, COERSIONLONG addthis = 0);
    bool power(gcgDISCRETE2D<float> *srcsignal1, COERSIONFLOAT power); // Powers a signal: I = I1^power
    bool power(gcgDISCRETE2D<double> *srcsignal1, COERSIONDOUBLE power);
    bool power(gcgDISCRETE2D<short> *srcsignal1, COERSIONSHORT power);
    bool power(gcgDISCRETE2D<int> *srcsignal1, COERSIONINT power);
    bool power(gcgDISCRETE2D<long> *srcsignal1, COERSIONLONG power);
    bool combineAdd(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<float> *srcsignal2, COERSIONFLOAT weight1 = 1, COERSIONFLOAT weight2 = 1);  // Combine two signals by addition: I = w1 * I1 + w2 * I2
    bool combineAdd(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<double> *srcsignal2, COERSIONDOUBLE weight1 = 1, COERSIONDOUBLE weight2 = 1);
    bool combineAdd(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<short> *srcsignal2, COERSIONSHORT weight1 = 1, COERSIONSHORT weight2 = 1);
    bool combineAdd(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<int> *srcsignal2, COERSIONINT weight1 = 1, COERSIONINT weight2 = 1);
    bool combineAdd(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<long> *srcsignal2, COERSIONLONG weight1 = 1, COERSIONLONG weight2 = 1);
    bool combineMult(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<float> *srcsignal2, COERSIONFLOAT add1 = 0, COERSIONFLOAT add2 = 0);  // Combine two signals by multiplication: I = (a1 + I1) * (a2 + I2)
    bool combineMult(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<double> *srcsignal2, COERSIONDOUBLE add1 = 0, COERSIONDOUBLE add2 = 0);
    bool combineMult(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<short> *srcsignal2, COERSIONSHORT add1 = 0, COERSIONSHORT add2 = 0);
    bool combineMult(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<int> *srcsignal2, COERSIONINT add1 = 0, COERSIONINT add2 = 0);
    bool combineMult(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<long> *srcsignal2, COERSIONLONG add1 = 0, COERSIONLONG add2 = 0);
    bool combineNorm(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<float> *srcsignal2); // Combine two signals by the L2 norm: I = sqrt(I1^2 + I2^2)
    bool combineNorm(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<double> *srcsignal2);
    bool combineNorm(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<short> *srcsignal2);
    bool combineNorm(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<int> *srcsignal2);
    bool combineNorm(gcgDISCRETE2D<NUMTYPE> *srcsignal1, gcgDISCRETE2D<long> *srcsignal2);

    /////////////////////////////////////////////////////////////
    // Domain processing (2D support)
    /////////////////////////////////////////////////////////////
    bool verticalFlip();  // Mirrors the signal in the vertical direction.

    /////////////////////////////////////////////////////////////
    // Interfaces for gcgIMAGE
    /////////////////////////////////////////////////////////////
    bool exportGrayScaleImage(gcgIMAGE *outimage, bool normalize);
};



// Next section are included only for floating point types
#if _COUNTER_GCG_ < 3


//////////////////////////////////////////////////////////////////////////////
/// @brief Class for handling matrices with arbitrary dimension. It is used
/// in general functions for linear algebra.
///
/// @since 0.04.44
//////////////////////////////////////////////////////////////////////////////

template <>
class     GCG_API_CLASS    gcgMATRIX<NUMTYPE>   :  public gcgCLASS {
  public:
    // Matrix info and data
    NUMTYPE       *data;        ///< Matrix samples: encoded as row first
    unsigned int  rows;         ///< Number of rows
    unsigned int  columns;      ///< Number of columns
    bool          isstaticdata; ///< True if the data pointer \a data must not be deleted by this object

  public:
    /////////////////////////////////////////////////////////////
    // Matrix construction
    /////////////////////////////////////////////////////////////
    gcgMATRIX();
    gcgMATRIX(unsigned int rows, unsigned int columns, NUMTYPE *sampledata = NULL, bool isstaticdata = false);
    virtual ~gcgMATRIX();

    /////////////////////////////////////////////////////////////
    // Empty matrix creation and destruction
    /////////////////////////////////////////////////////////////
    bool createMatrix(unsigned int rows, unsigned int columns, NUMTYPE *sampledata = NULL, bool isstaticdata = false);
    void destroyMatrix();  // Release all resources used by this matrix

    /////////////////////////////////////////////////////////////
    // Matrix copying, duplication and conversion.
    /////////////////////////////////////////////////////////////
    bool createSimilar(gcgMATRIX<float> *source); // Creates a matrix similar as the source. The data is not copied.
    bool createSimilar(gcgMATRIX<double> *source);
    bool isCompatibleWith(gcgMATRIX<float> *source); // Checks if both matrices are compatible: same dimensions
    bool isCompatibleWith(gcgMATRIX<double> *source);
    bool duplicateMatrix(gcgMATRIX<float> *source); // Makes an independent copy of the source matrix.
    bool duplicateMatrix(gcgMATRIX<double> *source);
    bool duplicateSubMatrix(gcgMATRIX<float> *source, int firstrow, int firstcolumn, unsigned int rows, unsigned int columns); // Makes an independent copy of the source submatrix.
    bool duplicateSubMatrix(gcgMATRIX<double> *source, int firstrow, int firstcolumn, unsigned int rows, unsigned int columns);

    ////////////////////////////////////////////////////////////////////////////////////
    // Matrix access and modification. Not recommended for high performance processes.
    ////////////////////////////////////////////////////////////////////////////////////
    NUMTYPE getDataSample(int row, int column);
    bool setDataSample(int row, int column, NUMTYPE value);

    /////////////////////////////////////////////////////////////
    // Matrix composition. Source matrices must be compatible.
    // The destination can be one of the sources.
    /////////////////////////////////////////////////////////////
    bool scale(gcgMATRIX<float> *srcmatrix1, COERSIONFLOAT weight, COERSIONFLOAT addthis = 0); // Scales a matrix: M = w * M1 + at
    bool scale(gcgMATRIX<double> *srcmatrix1, COERSIONDOUBLE weight, COERSIONDOUBLE addthis = 0);
    bool power(gcgMATRIX<float> *srcmatrix1, COERSIONFLOAT power); // Powers the elements of the matrix: M = M1^power
    bool power(gcgMATRIX<double> *srcmatrix1, COERSIONDOUBLE power);
    bool combineAdd(gcgMATRIX<NUMTYPE> *srcmatrix1,  gcgMATRIX<float> *srcmatrix2, COERSIONFLOAT weight1 = 1, COERSIONFLOAT weight2 = 1);  // Combine two signals by addition: M = w1 * M1 + w2 * M2
    bool combineAdd(gcgMATRIX<NUMTYPE> *srcmatrix1,  gcgMATRIX<double> *srcmatrix2, COERSIONDOUBLE weight1 = 1, COERSIONDOUBLE weight2 = 1);
    bool combineMult(gcgMATRIX<NUMTYPE> *srcmatrix1, gcgMATRIX<float> *srcmatrix2, COERSIONFLOAT add1 = 0, COERSIONFLOAT add2 = 0);  // Combine two signals by multiplication: M = (a1 + M1) * (a2 + M2)
    bool combineMult(gcgMATRIX<NUMTYPE> *srcmatrix1, gcgMATRIX<double> *srcmatrix2, COERSIONDOUBLE add1 = 0, COERSIONDOUBLE add2 = 0);
    bool combineNorm(gcgMATRIX<NUMTYPE> *srcmatrix1, gcgMATRIX<float> *srcmatrix2); // Combine two signals by the L2 norm: M = sqrt(M1^2 + M2^2)
    bool combineNorm(gcgMATRIX<NUMTYPE> *srcmatrix1, gcgMATRIX<double> *srcmatrix2);
};



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////     UNIDIMENSIONAL LEGENDRE POLYNOMIALS     /////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @brief Class for Legendre 1D polynomials computation.
/// @tparam NUMTYPE Type of the samples representing the signal. Supported types: \e float or \e double.
///
/// Use gcgLEGENDREBASIS1D<float> for single precision and gcgLEGENDREBASIS1D<double>
/// for double precision. Methods for projection and reconstruction are avalaible. The
/// performance of the numeric methods can be verified by using the basisInformation() method.
///
/// @since 0.01.6
/// @ingroup basis
//////////////////////////////////////////////////////////////////////////////

template <>
class     GCG_API_CLASS    gcgLEGENDREBASIS1D<NUMTYPE> : public gcgBASIS1D<NUMTYPE> {
  public:
    unsigned int degree;    ///< Degree of the polynomials = number of polynomials - 1. Read-only. See setBasisDegree().
    unsigned int nsamples;  ///< Current number of samples of each discretized polynomial. Read-only. See setNumberOfSamples().

  private:
    double      *coefficients;  // Coefficients of polynomials. Double precision reduces numerical problems.
    unsigned int npolynomials;  // number of polynomials = maximum degree of the polynomial basis + 1

    NUMTYPE *discretepolynomials; // Discrete version of polynomials

  public:
    gcgLEGENDREBASIS1D();
    ~gcgLEGENDREBASIS1D();

    /// @brief Sets the maximum degree of the polynomials of the basis. The number of polynomials = maximum degree + 1.
    /// @param[in] degree maximum degree of the polynomial basis.
    /// @return true if setup succeded
    bool setBasisDegree(unsigned int degree);

    /// @brief Sets the number of samples for the discretization of polynomial functions. Call it BEFORE
    /// using getDiscreteValue(), projectSignal(), reconstructSignal() or basisInformation(). This method computes
    /// all polynomial basis vectors which might be slow if current degree is big.
    /// @param[in] nsamples number of samples of a discretization of poynomials domain [-1, 1].
    /// @return true if discretized basis creation is successful.
    /// @see getDiscreteValue()
    /// @see projectSignal()
    /// @see reconstructSignal()
    /// @see basisInformation()
    bool setNumberOfSamples(unsigned int nsamples);

    /// @brief Returns the number of coefficients used in 1D polynomial projection/reconstruction.
    /// @return the number of polynomials of the basis = degree + 1.
    unsigned int getNumberOfCoefficients();

    /// @brief Computes the value of the polynomial of idegree \a degree at point \a x in [-1, 1].
    /// @param[in] idegree degree of the polynomial function.
    /// @param[in] x coordinate of the point to be evaluated. Must be in the interval [-1, 1]
    /// @return the value of the polynomial at point \a x.
    /// @see getSampleValue()
    /// @see getDiscreteValue()
    NUMTYPE getPointValue(unsigned int idegree, NUMTYPE x);

    /// @brief Computes the integral of the polynomial of degree \a idegree in the interval [\a a, \a b].
    /// @param[in] idegree of the polynomial function.
    /// @param[in] a inferior limit of the interval [\a a, \a b].
    /// @param[in] b superior limit of the interval [\a a, \a b].
    /// @return the value of the integral in the interval [\a a, \a b].
    NUMTYPE getIntegralValue(unsigned int idegree, NUMTYPE a, NUMTYPE b);

    /// @brief Compute normalized \a i-th sample of the polynomial of degree \a idegree. Parameter \a i in [0, nsamples-1]
    /// is the \a i-th sample of a uniform discretization of the domain [-1,1] with \a nsamples samples. Call
    /// setNumberOfSamples() to set the number of samples to be used.
    /// @param[in] idegree degree of the polynomial function.
    /// @param[in] i index of the sample. Must be in the interval [0 \a nsamples - 1].
    /// @return the value of the \a i-th sample.
    /// @see setBasisDegree()
    /// @see setNumberOfSamples()
    NUMTYPE getDiscreteValue(unsigned int idegree, unsigned int i);

    /// @brief Computes the \a npolynomials coefficients of the projection of the \a vector
    /// (as 1D signal) on the discretized basis of current degree + 1 polynomials =
    /// npolynomials. Only \a nsamples elements starting at \a atX are used. The coefficients are stored
    /// in array \a outputcoef (as 1D signal) that is adjusted to have current degree + 1 elements. Call
    /// setNumberOfSamples() to set the number of samples to be used.
    /// @param[in] atX origin of the signal for this projection (relative to \a vector).
    /// @param[in] vector array (as 1D signal) containing components of the vector to be projected onto the basis.
    /// @param[out] outputcoef array (as 1D signal) that receives the computed coefficients. It is adjusted to have \a degree + 1 elements.
    /// @return true if projection is successful.
    /// @see setBasisDegree()
    /// @see setNumberOfSamples()
    /// @see reconstructSignal()
    bool projectSignal(int atX, gcgDISCRETE1D<float> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, gcgDISCRETE1D<double> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, gcgDISCRETE1D<short> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, gcgDISCRETE1D<int> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, gcgDISCRETE1D<long> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);

    /// @brief Computes up to \a nsamples components of a vector (as 1D signal), using the degree + 1
    /// coefficients given in array \a inputcoef (as 1D signal). The components are stored in the array
    /// \a outputvector (as 1D signal) starting at position \a atX. Call
    /// setNumberOfSamples() to set the number of samples to be used.
    /// @param[in] atX origin of the signal for this projection (relative to \a outputvector).
    /// @param[in] inputcoef array (as 1D signal) of coefficients representing the vector to be reconstructed.
    /// @param[out] outputvector array (as 1D signal) that receives the reconstructed vector.
    /// @return true if reconstruction is successful.
    /// @see setBasisDegree()
    /// @see setNumberOfSamples()
    /// @see projectSignal()
    bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<float> *outputvector);
    bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<double> *outputvector);
    bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<short> *outputvector);
    bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<int> *outputvector);
    bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<long> *outputvector);

    /// @brief Output basis information with current degree for numerical analysis. Saves information of the
    /// orthogonality of the basis with \a nsamples elements. Call setNumberOfSamples() to set the number of
    /// samples to be used.
    /// @param[in] filename name of output text file.
    /// @return true if file creation was successful.
    /// @see setNumberOfSamples()
    bool basisInformation(const char *filename);
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////     BIDIMENSIONAL LEGENDRE POLYNOMIALS     /////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/// @brief Class for Legendre 2D polynomials computation.
/// @tparam NUMTYPE Type of the samples representing the signal. Supported types: \e float or \e double.
///
/// Use gcgLEGENDREBASIS2D<float> for single precision and gcgLEGENDREBASIS2D<double>
/// for double precision. Methods for projection and reconstruction are avalaible. The
/// performance of the numeric methods can be verified by using the basisInformation() method.
///
/// @since 0.01.6
/// @ingroup basis
//////////////////////////////////////////////////////////////////////////////

template <>
class     GCG_API_CLASS    gcgLEGENDREBASIS2D<NUMTYPE> : public gcgBASIS2D<NUMTYPE> {
  public:
    unsigned int degree;       ///< Degree of the polynomials. Read-only. See setBasisDegree().
    unsigned int nsamplesX;    ///< Current samples in X direction. Read-only. See setNumberOfSamples().
    unsigned int nsamplesY;    ///< Current samples in Y direction. Read-only. See setNumberOfSamples().

  private:
    double       *coefficients; // Coefficients of 2D polynomials. Double precision reduces numerical problems.
    unsigned int npolynomials;  // number of polynomials for x and y = ((degree-2)*(degree-1))/2

    NUMTYPE *discretepolynomials; // Discrete version of polynomials

  public:
    gcgLEGENDREBASIS2D();
    ~gcgLEGENDREBASIS2D();

    /// @brief Sets the maximum degree of the polynomials of the basis. The number of polynomials = (degree + 1)*(degree+2)/2.
    /// @param[in] degree maximum degree of the polynomial basis.
    /// @return true if setup succeded
    bool setBasisDegree(unsigned int degree);

    /// @brief Sets the number of samples in X and Y directions for the discretization of polynomial functions.
    /// Call it (or call synchBasisWithFile()) BEFORE using getDiscreteValue(), projectSignal(), reconstructSignal()
    /// or basisInformation(). This method computes all polynomial basis vectors which might be slow if current
    /// degree is big.
    /// @param[in] nsamplesX number of points in X.
    /// @param[in] nsamplesY number of points in Y.
    /// @return true if discretized basis creation is successful.
    /// @see synchBasisWithFile()
    /// @see getDiscreteValue()
    /// @see projectSignal()
    /// @see reconstructSignal()
    /// @see basisInformation()
    bool setNumberOfSamples(unsigned int nsamplesX, unsigned int nsamplesY);

    /// @brief Returns the number of coefficients used in 2D polynomial projection/reconstruction.
    /// @return the number of polynomials of the basis = degree + 1.
    unsigned int getNumberOfCoefficients();

    /// @brief Loads the basis functions of current degree, discretized with nsamplesX * nsamplesY
    /// elements, stored in the given file. All missing polynomials of the file are discretized and
    /// saved for further use. This function sychronizes file and memory polynomial functions and can
    /// considerably save time. Use this function instead of setNumberOfSamples() to avoid the computation of
    /// all basis functions that might be stored in the file.
    /// @param[in] filename name of the file containing discretized polynomial basis.
    /// @param[in] nsamplesX number of points in X.
    /// @param[in] nsamplesY number of points in Y.
    /// @return true if synchronization succeded.
    /// @see setNumberOfSamples()
    bool synchBasisWithFile(const char *filename, unsigned int nsamplesX, unsigned int nsamplesY);

    /// @brief Computes the value Pi,j(x,y), where \a i+\a j <= degree, are the polynomial degrees in X and Y
    ///        axe, and \a x, \a y in [-1, 1] * [-1, 1] are the coordinates of the point to be evaluated.
    /// @param[in] i degree of the polynomial function in X direction.
    /// @param[in] j degree of the polynomial function in Y direction.
    /// @param[in] x abcissa coordinate of the point to be evaluated. Must be in the interval [-1, 1]
    /// @param[in] y coordinate of the point to be evaluated. Must be in the interval [-1, 1]
    /// @return the value of the polynomial Pi,j at point (\a x, \a y).
    /// @see getSampleValue()
    /// @see getDiscreteValue()
    NUMTYPE getPointValue(unsigned int i, unsigned int j, NUMTYPE x, NUMTYPE y);

    /// @brief Computes the integral of the polynomial P\a i,\a j in the region [\a xmin, \a xmax] * [\a ymin, \a ymax].
    /// @param[in] i degree of the polynomial function in X direction.
    /// @param[in] j degree of the polynomial function in Y direction.
    /// @param[in] xmin inferior limit of the interval in X.
    /// @param[in] xmax superior limit of the interval in X.
    /// @param[in] ymin inferior limit of the interval in Y.
    /// @param[in] ymax superior limit of the interval in Y.
    /// @return the value of the integral of polynomial P\a i,\a j in the interval [\a xmin, \a xmax] * [\a ymin, \a ymax].
    NUMTYPE getIntegralValue(unsigned int i, unsigned int j, NUMTYPE xmin, NUMTYPE xmax, NUMTYPE ymin, NUMTYPE ymax);

    /// @brief Compute normalized value P\a i,\a j(\a ix, \a iy), where \a i+\a j <= degree, are the polynomial
    /// degrees in \a x and \a y, and \a ix in [0, \a nsamplesX-1], and \a iy in [0, \a nsamplesY-1] are the
    /// coordinates of the sample of a uniform discretization of the domain [-1, 1] * [-1, 1]
    /// with \a nsamplesX * \a nsamplesY samples. Call setNumberOfSamples() or synchBasisWithFile() to set
    /// the number of samples to be used.
    /// @param[in] i degree of the polynomial function in X direction.
    /// @param[in] j degree of the polynomial function in Y direction.
    /// @param[in] ix index of the sample in X. Must be in the interval [0 \a nsamplesX - 1].
    /// @param[in] iy index of the sample in Y. Must be in the interval [0 \a nsamplesY - 1].
    /// @return the normalized value of the sample of function P\a i,\a j at position (\a ix,\a iy).
    /// @see setNumberOfSamples()
    /// @see synchBasisWithFile()
    /// @see setBasisDegree()
    /// @see getSampleValue()
    /// @see getPointValue()
    NUMTYPE getDiscreteValue(unsigned int i, unsigned int j, unsigned int ix, unsigned int iy);

    /// @brief Computes the ((degree-2) * (degree-1)) / 2) coefficients of the projection of the 2D vector (as 2D signal) on
    /// a discretized polynomial basis. Only \a nsamplesX * \a nsamplesY elements starting at (\a atX, \a atY) are used.
    /// The coefficients are stored in the array \a outputcoef (as 1D signal) that is adjusted to have (degree+2)*
    /// (degre+1)/2 elements. Call setNumberOfSamples() to set the number of samples to be used.
    /// @param[in] atX origin X coordinate of the signal for this projection (relative to \a vector).
    /// @param[in] atY origin Y coordinate of the signal for this projection (relative to \a vector).
    /// @param[in] vector array (as 2D signal) containing components of the 2D vector to be projected onto the basis.
    /// @param[out] outputcoef array (as 1D signal) that receives the computed coefficients. It is adjusted to  have (degree+2)*(degre+1)/2 elements.
    /// @return true if projection is successful.
    /// @see setBasisDegree()
    /// @see setNumberOfSamples()
    /// @see synchBasisWithFile()
    /// @see reconstructSignal()
    bool projectSignal(int atX, int atY, gcgDISCRETE2D<float> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, int atY, gcgDISCRETE2D<double> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, int atY, gcgDISCRETE2D<short> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, int atY, gcgDISCRETE2D<int> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, int atY, gcgDISCRETE2D<long> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);


    /// @brief Computes the \a nsamplesX * \a nsamplesY components of a 2D vector, using the (degree+1)*(degree+2)/2
    /// coefficients given in array \a inputcoef (as 1D signal). The components are stored in the 2D array
    /// \a outputvector (as 2D signal) starting at position (\a atX, \a atY). Call
    /// setNumberOfSamples() or synchBasisWithFile() to set the number of samples to be used.
    /// @param[in] atX origin X coordinate of the signal for this projection (relative to \a outputvector).
    /// @param[in] atY origin Y coordinate of the signal for this projection (relative to \a outputvector).
    /// @param[in] inputcoef array (as 1D signal) of (degree+1)*(degree+2)/2 coefficients representing the vector to be reconstructed.
    /// @param[out] outputvector 2D array (as 2D signal) that receives the reconstructed vector. Must have room for \a nsamplesX * \a nsamplesY elements.
    /// @return true if reconstruction is successful.
    /// @see setBasisDegree()
    /// @see setNumberOfSamples()
    /// @see synchBasisWithFile()
    /// @see projectSignal()
    bool reconstructSignal(int atX, int atY, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE2D<float> *outputvector);
    bool reconstructSignal(int atX, int atY, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE2D<double> *outputvector);
    bool reconstructSignal(int atX, int atY, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE2D<short> *outputvector);
    bool reconstructSignal(int atX, int atY, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE2D<int> *outputvector);
    bool reconstructSignal(int atX, int atY, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE2D<long> *outputvector);

    /// @brief Output basis information with current degree for numerical analysis. Saves
    /// information of the orthogonality of the basis with \a nsamplesX * \a nsamplesY elements.
    /// @param[in] filename name of output text file. Call setNumberOfSamples() or synchBasisWithFile() to set the
    /// number of samples to be used.
    /// @param[in] checkorthogonality if true, computes the internal product of all functions of the basis. This can be time consuming.
    /// @param[in] savefunctionsasimages if true, saves the function basis as gray scale images to be visually checked.
    /// @return true if file creation was successful.
    bool basisInformation(const char *filename, bool checkorthogonality, bool savefunctionsasimages);
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////     UNIDIMENSIONAL REAL WAVELETS BASIS     //////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @brief Class for real, discrete, wavelets decomposition and recomposition.
/// @tparam NUMTYPE Type of the samples representing the signal. Supported types: \e float or \e double.
///
/// Use gcgDWTBASIS1D<float> for single precision and gcgDWTBASIS1D<double>
/// for double precision. Methods for projection and reconstruction are avalaible.
///
/// @since 0.01.6
/// @ingroup basis
//////////////////////////////////////////////////////////////////////////////

template <>
class     GCG_API_CLASS    gcgDWTBASIS1D<NUMTYPE> : public gcgBASIS1D<NUMTYPE> {
  public:
    gcgDISCRETE1D<NUMTYPE> H;       ///< Low pass decomposition filter. Read-only.
    gcgDISCRETE1D<NUMTYPE> G;       ///< High pass decomposition filter. Read-only.
    gcgDISCRETE1D<NUMTYPE> rH;      ///< Low pass reconstruction filter. Read-only.
    gcgDISCRETE1D<NUMTYPE> rG;      ///< High pass reconstruction filter. Read-only.

    unsigned int nsamples;          ///< Number of samples for projection/reconstruction processes. Read-only. See setNumberOfSamples().
    unsigned int ncoefficients;     ///< Number of detail coefficients. Read-only. See setNumberOfSamples().

  private:
    void        *buffer;            ///< Buffer used in projection/reconstruction.

  public:
    gcgDWTBASIS1D();
    ~gcgDWTBASIS1D();

    /// @brief Sets the filters for decomposition and reconstruction. The filters information is copied to
    /// the internal filters. The internal border extension attribute is set to GCG_BORDER_EXTENSION_ZERO
    /// since wavelet basis are assumed to be compact and finite.
    /// Call it BEFORE projectSignal(), reconstructSignal() or basisInformation().
    /// @param[in] H wavelet filter for low pass decomposition.
    /// @param[in] G wavelet filter for high pass decomposition.
    /// @param[in] rH wavelet filter for low pass reconstruction.
    /// @param[in] rG wavelet filter for high pass reconstruction.
    /// @return true if setup succeded
    bool setWavelets(gcgDISCRETE1D<NUMTYPE> *H, gcgDISCRETE1D<NUMTYPE> *G, gcgDISCRETE1D<NUMTYPE> *rH, gcgDISCRETE1D<NUMTYPE> *rG);

    /// @brief Sets the number of samples to be used in the projection/reconstruction processes. Call it
    /// BEFORE projectSignal(), reconstructSignal() or basisInformation().
    /// @param[in] nsamples number of samples for projection/reconstruction processes.
    /// @return true is successful.
    /// @see projectSignal()
    /// @see reconstructSignal()
    /// @see basisInformation()
    bool setNumberOfSamples(unsigned int nsamples);

    /// @brief Returns the number of elements needed to store the coefficients of the projection of
    /// \a nsamples (see setNumberOfSamples()) onto the wavelet basis. If \a nsamples is even, there
    /// will be \a nsamples coefficients. If \a nsamples is odd, there will be (\a nsamples + 1) / 2
    /// coefficients. The first half of the coefficients vector are scale coefficients given by low pass
    /// filtering (approximation). The second half of the coefficients vector are detail coefficients
    /// given by high pass filtering.
    /// @return the number of coefficients.
    /// @see setNumberOfSamples()
    unsigned int getNumberOfCoefficients();

    /// @brief Computes the coefficients of the projection of the \a vector (as 1D signal) onto the wavelet
    /// basis. Only \a nsamples elements starting at position \a atX are used. This subregion is projected
    /// using the original signal \a vector extension mode. User must be carefull because most wavelets only
    /// works with periodic and/or symmetric extension of the signal. Call setNumberOfSamples() to set the
    /// number of samples to be used.
    /// @param[in] atX origin of the signal for this projection (relative to \a vector).
    /// @param[in] vector array (as 1D signal) containing components of the vector to be projected onto the basis.
    /// @param[out] outputcoef array (as 1D signal) that receives the computed coefficients. It is adjusted to have all coefficients.
    /// @return true if projection is successful.
    /// @see setWavelets()
    /// @see setNumberOfSamples()
    /// @see reconstructSignal()
    bool projectSignal(int atX, gcgDISCRETE1D<float> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, gcgDISCRETE1D<double> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, gcgDISCRETE1D<short> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, gcgDISCRETE1D<int> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);
    bool projectSignal(int atX, gcgDISCRETE1D<long> *vector, gcgDISCRETE1D<NUMTYPE> *outputcoef);

    /// @brief Computes up to \a nsamples components of a vector (as 1D signal), using
    /// the scale and detail coefficients given in array \a inputcoef (as 1D signal). The components are
    /// stored in the array \a outputvector (as 1D signal) starting at position \a atX. Call
    /// setNumberOfSamples() to set the number of samples to be used.
    /// @param[in] atX origin of the signal for this projection (relative to \a outputvector).
    /// @param[in] inputcoef array (as 1D signal) of coefficients representing the vector to be reconstructed.
    /// @param[out] outputvector array (as 1D signal) that receives the reconstructed vector.
    /// @return true if reconstruction is successful.
    /// @see setWavelets()
    /// @see setNumberOfSamples()
    /// @see projectSignal()
    bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<float> *outputvector);
    bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<double> *outputvector);
    bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<short> *outputvector);
    bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<int> *outputvector);
    bool reconstructSignal(int atX, gcgDISCRETE1D<NUMTYPE> *inputcoef, gcgDISCRETE1D<long> *outputvector);

    /// @brief Output information using current wavelet basis for numerical analysis. Saves information of
    /// reconstructions using the basis with \a nsamples elements. Call setNumberOfSamples() to set the
    /// number of samples to be used.
    /// @param[in] filename name of output text file.
    /// @return true if file creation was successful.
    /// @see setNumberOfSamples()
    bool basisInformation(const char *filename);
};


#endif


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////   DISCRETE SEQUENCE DERIVATIVE   ///////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @tparam NUMTYPE Type of the samples representing the signal. Supported types: \e float, \e double, \e long, \e int and \e short.
// Class for computing the partial derivative of a 2D signal Icurrent (given
// the sequence of signals {Iprevious, Icurrent, Inext} consecutively defined
// in a axis t, perpendicular to the signals) in respect to axis t. The axis
// t is frequently defined as time, over which the 2D signal vary.
//
// In each call of sequenceDerivative(), the parameters are compared with
// those from previous invocation, and already computed information is reused.
//
//////////////////////////////////////////////////////////////////////////////

template <>
class     GCG_API_CLASS    gcgSEQUENCEDERIVATIVE2D<NUMTYPE>   :  public gcgCLASS {
  private:
    gcgDISCRETE2D<NUMTYPE> *current;
    gcgDISCRETE2D<NUMTYPE> *next;
    gcgDISCRETE2D<NUMTYPE> *lowcurrent;
    gcgDISCRETE2D<NUMTYPE> *lownext;
    gcgDISCRETE2D<NUMTYPE> temp;

  public:
    // Constructors and destructors
    gcgSEQUENCEDERIVATIVE2D<NUMTYPE>();
    virtual ~gcgSEQUENCEDERIVATIVE2D<NUMTYPE>();

    // Computes a new partial derivative.
    virtual bool sequenceDerivative(gcgDISCRETE2D<NUMTYPE> *current, gcgDISCRETE2D<NUMTYPE> *next, gcgDISCRETE2D<NUMTYPE> *outputDt);
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////////     FILTER MASK DEFINITIONS      ////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Class for generating filter masks.
/// @tparam NUMTYPE Type of the samples representing the signal. Supported types: \e float, \e double, \e long, \e int and \e short.
//
// Use gcgFILTERMASK<float> or gcgFILTERMASK<> for single precision.
// Use gcgFILTERMASK<double> for double precision. Methods for projection
// and reconstruction are avalaible. The performance of the numeric methods can be
// analysed by using the basisInformation() method.
//
//////////////////////////////////////////////////////////////////////////////

template<>
class     GCG_API_CLASS    gcgFILTERMASK1D<NUMTYPE> : public gcgDISCRETE1D<NUMTYPE> {
  public:
    gcgFILTERMASK1D();
    virtual ~gcgFILTERMASK1D();

    // Box filter construction
    bool createBoxFilter(unsigned int nsamples);

    // Triangle filter construction
    bool createTriangleFilter(unsigned int nsamples);
};


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//////////////////     SIGNAL PROCESSING FUNCTIONS     //////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
// Signal comparison: error computation.
/////////////////////////////////////////////////////////////

template<>    GCG_API_TEMPLATE    double computeMSEwith<NUMTYPE>(gcgDISCRETE1D<NUMTYPE> *src1, gcgDISCRETE1D<NUMTYPE> *src2); // Computes the Mean Squared Error.
template<>    GCG_API_TEMPLATE    double computePSNRwith<NUMTYPE>(gcgDISCRETE1D<NUMTYPE> *src1, gcgDISCRETE1D<NUMTYPE> *src2);// Computes the Peak Signal-to-Noise Ratio in dB.
template<>    GCG_API_TEMPLATE    double computeMAEwith<NUMTYPE>(gcgDISCRETE1D<NUMTYPE> *src1, gcgDISCRETE1D<NUMTYPE> *src2); // Computes the Mean Absolute Error.

template<>    GCG_API_TEMPLATE    double computeMSEwith<NUMTYPE>(gcgDISCRETE2D<NUMTYPE> *src1, gcgDISCRETE2D<NUMTYPE> *src2); // Computes the Mean Squared Error.
template<>    GCG_API_TEMPLATE    double computePSNRwith<NUMTYPE>(gcgDISCRETE2D<NUMTYPE> *src1, gcgDISCRETE2D<NUMTYPE> *src2);// Computes the Peak Signal-to-Noise Ratio in dB.
template<>    GCG_API_TEMPLATE    double computeMAEwith<NUMTYPE>(gcgDISCRETE2D<NUMTYPE> *src1, gcgDISCRETE2D<NUMTYPE> *src2); // Computes the Mean Absolute Error.


/////////////////////////////////////////////////////////////
// Signal analysis.
/////////////////////////////////////////////////////////////

// Computes the gradient of 1D signal src. The derivative is computed using well-known Sobel operator and
// the result is stored in dx.
template<>    GCG_API_TEMPLATE    bool gcgFirstDerivativeSobel1D<NUMTYPE>(gcgDISCRETE1D<NUMTYPE> *src, gcgDISCRETE1D<NUMTYPE> *dx);

// Computes the gradient of 2D signal src. The partial derivatives are computed using well-known Sobel
// operator and the components are stored in dx and dy. The pointer for dx or dy may be NULL.
template<>    GCG_API_TEMPLATE    bool gcgGradientSobel2D<NUMTYPE>(gcgDISCRETE2D<NUMTYPE> *src, gcgDISCRETE2D<NUMTYPE> *dx, gcgDISCRETE2D<NUMTYPE> *dy);

// Computes the (optical) flow given the partial derivatives in X, Y and time of up to three channels.
// Uses the Augereau method (Bertrand Augereau, Benoît Tremblais, Christine Fernandez-Maloigne,
// "Vectorial computation of the optical flow in colorimage sequences", CIC05).
template<>    GCG_API_TEMPLATE    bool gcgOpticalFlowAugereau2D<NUMTYPE>(gcgDISCRETE2D<NUMTYPE> *dx1, gcgDISCRETE2D<NUMTYPE> *dy1, gcgDISCRETE2D<NUMTYPE> *dt1,
                                                         gcgDISCRETE2D<NUMTYPE> *dx2, gcgDISCRETE2D<NUMTYPE> *dy2, gcgDISCRETE2D<NUMTYPE> *dt2,
                                                         gcgDISCRETE2D<NUMTYPE> *dx3, gcgDISCRETE2D<NUMTYPE> *dy3, gcgDISCRETE2D<NUMTYPE> *dt3,
                                                         gcgDISCRETE2D<float> *outflowX, gcgDISCRETE2D<float> *outflowY);

template<>    GCG_API_TEMPLATE    bool gcgOpticalFlowAugereau2D<NUMTYPE>(gcgDISCRETE2D<NUMTYPE> *dx1, gcgDISCRETE2D<NUMTYPE> *dy1, gcgDISCRETE2D<NUMTYPE> *dt1,
                                                         gcgDISCRETE2D<NUMTYPE> *dx2, gcgDISCRETE2D<NUMTYPE> *dy2, gcgDISCRETE2D<NUMTYPE> *dt2,
                                                         gcgDISCRETE2D<NUMTYPE> *dx3, gcgDISCRETE2D<NUMTYPE> *dy3, gcgDISCRETE2D<NUMTYPE> *dt3,
                                                         gcgDISCRETE2D<double> *outflowX, gcgDISCRETE2D<double> *outflowY);


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
////////////////////////      LINEAR SOLVER       ///////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

template<>     GCG_API_TEMPLATE    bool gcgLinearSolver(gcgDISCRETE2D<NUMTYPE> *A, gcgDISCRETE1D<NUMTYPE> *b, gcgDISCRETE1D<NUMTYPE> *x);

/*
/////////////////////////////////////////////////////////////
// Tsai method
/////////////////////////////////////////////////////////////

///tipos de otimização
#define NONE 0
#define THREE_PARAM 1
#define FULL 2

class gcgCalibrator {
  public:
    double r1, r2, r3, r4, r5, r6, r7, r8, r9; //elementos da matriz de rotação
    double Tx, Ty, Tz; //elementos do vetor de translação
    double f; //distância focal
    double k1; //coeficiente de distorção
};

class gcgCameraCalibration: public gcgCalibrator{
    public:

        int n; //número de pontos para a calibração
        double Cx, Cy; //coordenadas da projeção do centro óptico
        double Rx, Ry, Rz; //ângulos da rotação

        VECTOR2d *worldPoints; //vetor de pontos do mundo
        VECTOR2d *imagePoints; //vetor de pontos da imagem
        VECTOR2d *distortedPoints; //vetor de pontos com distorção

        gcgCameraCalibration(int n, VECTOR2d *worldPoints, VECTOR2d *imagePoints, double Cx, double Cy);

        void rotationAngles();

        void rotationMatrix();

        int TsaiMethodCoplanar(int otimizationType);

        void otimization();

        void otimizationFull();
};

class gcgProjectorCalibration: public gcgCameraCalibration{
    public:

    double Rc[9], Tc[3], fc; //parâmetros da câmera calibrada

    gcgProjectorCalibration(int n, VECTOR2d *worldPoints, VECTOR2d *imagePoints, double Cx, double Cy,
                             double rc1, double rc2, double rc3, double rc4, double rc5,  double rc6, double rc7, double rc8, double rc9,
                             double Tcx, double Tcy, double Tcz, double fc);

    gcgProjectorCalibration(int n, VECTOR2d *worldPoints, VECTOR2d *imagePoints, double Cx, double Cy, double Rc[9], double Tc[3], double fc);

    gcgProjectorCalibration(int n, VECTOR2d *worldPoints, VECTOR2d *imagePoints, double Cx, double Cy, gcgCameraCalibration *camera);

    int projectorCalibration(int otimizationType);
};

class gcgCameraProjectorCalibration: public gcgCameraCalibration{
    public:

    gcgProjectorCalibration *projector;

    gcgCameraProjectorCalibration(int nc, VECTOR2d *worldPointsCamera, VECTOR2d *imagePointsCamera, double CxCamera, double CyCamera,
                                  int np, VECTOR2d *worldPointsProjetor, VECTOR2d *imagePointsProjetor, double CxProjetor, double CyProjetor);

    int cameraProjectorCalibration(int otimizationType);
};


/////////////////////////////////////////////////////////////
// Levenberg-Marquadt method
/////////////////////////////////////////////////////////////
class gcgLevMarq{
    public:

        int numPt; //número de pontos da função
        int numPar; //número de parâmetros a serem otimizados
        gcgDISCRETE1D<double> *p; //vetor que armazena os parâmetros
        gcgDISCRETE1D<double> *x; //vetor de tamanho >= numPt para armazenar a saída da função

        double epsilon1;
        double epsilon2;
        double epsilon3;
        double tau;
        int kmax;
        double jacobianInterval;

        gcgLevMarq();

        virtual void f(int numPt, int numPar, gcgDISCRETE1D<double> *p, gcgDISCRETE1D<double> *residuos) = 0;

        void multTransposeXMatrix(gcgDISCRETE2D<double> *matriz, gcgDISCRETE2D<double> *resultado);

        void multTransposeXMatrix(gcgDISCRETE2D<double> *matriz, gcgDISCRETE1D<double> *vetor, gcgDISCRETE1D<double> *resultado);

        double infinityNorm(gcgDISCRETE1D<double> *vetor);

        double euclidianNorm(gcgDISCRETE1D<double> *vetor);

        double multVectorTXVector(gcgDISCRETE1D<double> *vetor1, gcgDISCRETE1D<double> *vetor2);

        void jacobianCalculate(gcgDISCRETE1D<double> *p, double intervalo, gcgDISCRETE2D<double> *jacobiana);

        void otimization();
};

*/


// Update counter
#if _COUNTER_GCG_ == 1
    #undef _COUNTER_GCG_
    #define _COUNTER_GCG_ 2
#elif _COUNTER_GCG_ == 2
    #undef _COUNTER_GCG_
    #define _COUNTER_GCG_ 3
#elif _COUNTER_GCG_ == 3
    #undef _COUNTER_GCG_
    #define _COUNTER_GCG_ 4
#elif _COUNTER_GCG_ == 4
    #undef _COUNTER_GCG_
    #define _COUNTER_GCG_ 5
#else
    #define _GCG_H_ // Stop loading
#endif

/////////////////////////////////////////////////////////////////////////////
// Loads several times to automatically include classes with distinct types
#if !defined(_GCG_H_)
  #include "gcg.h"
#endif

#ifdef __cplusplus
} // extern "C++"
#endif

#endif // #ifndef _GCG_H_
