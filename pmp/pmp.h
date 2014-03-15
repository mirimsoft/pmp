// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the PMP_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// PMP_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef PMP_EXPORTS
#define PMP_API __declspec(dllexport)
#else
#define PMP_API __declspec(dllimport)
#endif

// This class is exported from the pmp.dll
class PMP_API Cpmp {
public:
	Cpmp(void);
	// TODO: add your methods here.
};

extern PMP_API int npmp;

PMP_API int fnpmp(void);
