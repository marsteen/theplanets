//---------------------------------------------------------------------------
//
// PROJECT : Die Planeten
//
//
// AUTOR   : Martin Steen
//           email: martin@martin-steen.de
//
//
//----------------------------------------------------------------------------

#include "CG3DResourceList.h"

//---------------------------------------------------------------------------
//
// Klasse:    CErrorMessage
// Methode:		ShowError
//
// Parameter:
//
// Return:
//
//---------------------------------------------------------------------------

void CErrorMessage::ShowError()
{
	cout << "***** ";
	
	switch (mErrCode)
	{
		case EPERR_UNKNOWN_KEYWORD:

			cout << "unknown keyword: " << mErrMsg;
			break;

		case 	EPERR_UNKNOWN_TYPE:

			cout << "unknown type: " << mErrMsg;
			break;

		case EPERR_FINDERROR:

			cout << "reference not found: " << mErrMsg; 
			break;

		case EPERR_WRONG_PARAMETERCOUNT:

			cout << "wrong parameter count. " << mErrMsg;
			break;

		case EPERR_LANG_UNSUPPORTED:

			cout << "unsupported language: " << mErrMsg;
			break;

		case EPERR_COLORUNKNOWN:

			cout << "unknown color name: " << mErrMsg;
			break;

		case EPERR_DOUBLE_NAME:

			cout << "double name tag: " << mErrMsg;
			break;

		case EPERR_NOTDEFINED:

			cout << "not defined: " << mErrMsg; 
			break;

		default:

			cout << "unspecific error: " << mErrMsg;
			break;

 
	}
	
	if (mFilename.size() != 0)
	{
		cout << " in file " << mFilename << endl;
	}
	if (mLineNumber != 0)
	{		
	 cout << " in line " << mLineNumber << endl;
		
	}
	else
	{
		cout << endl;
	}
}
