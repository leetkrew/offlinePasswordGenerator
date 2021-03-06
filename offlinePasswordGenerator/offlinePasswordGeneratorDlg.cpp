
// offlinePasswordGeneratorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "offlinePasswordGenerator.h"
#include "offlinePasswordGeneratorDlg.h"
#include "afxdialogex.h"
#include <vector>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CofflinePasswordGeneratorDlg dialog



CofflinePasswordGeneratorDlg::CofflinePasswordGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OFFLINEPASSWORDGENERATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CofflinePasswordGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CofflinePasswordGeneratorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btnGenerate, &CofflinePasswordGeneratorDlg::OnBnClickedbtngenerate)
	ON_BN_CLICKED(IDCANCEL, &CofflinePasswordGeneratorDlg::OnBnClickedCancel)
	ON_BN_CLICKED(btnCopy, &CofflinePasswordGeneratorDlg::OnBnClickedbtncopy)
END_MESSAGE_MAP()


// CofflinePasswordGeneratorDlg message handlers

BOOL CofflinePasswordGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	GetDlgItem(txtPasswordLength)->SetWindowTextW((LPCWSTR)L"10");

	CButton* pBtn = (CButton*)GetDlgItem(chkIncludePunctuations);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(chkIncludeProgrammingCharacters);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(chkIncludeSimilarCharacters);
	pBtn->SetCheck(1);

	pBtn = (CButton*)GetDlgItem(chkIncludeUppercase);
	pBtn->SetCheck(1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CofflinePasswordGeneratorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CofflinePasswordGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CString generateRandomPassword(INT length, BOOL add_punctuations, BOOL add_programmingCharacters, BOOL add_similarCharacters, BOOL add_uppercase) {

	std::vector <CString> resultArray;

	int arraySize;

	char* charactersArray[] = {
		"a", "b", "c", "d", "e", "f", "g", "h",  "j", "k",  "m", "n", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
		, "2", "3", "4", "5", "6", "7", "8", "9"
	};

	for each (CString item in charactersArray)
	{
		resultArray.push_back(item);
	}

	if (add_uppercase) {
		char* uppercaseCharactersArray[] = {
			"A", "B", "C", "D", "E", "F", "G", "H",  "J", "K", "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
		};
		for each (CString item in uppercaseCharactersArray)
		{
			resultArray.push_back(item);
		}
	}

	if (add_similarCharacters) {
		char* similarCharactersArray[] = {
			"1", "i", "l", "0", "o"
		};

		if (add_uppercase) {
			char* similarCharactersUppercaseArray[] = {
				"I", "L", "O"
			};
			for each (CString item in similarCharactersUppercaseArray)
			{
				resultArray.push_back(item);
			}
		}

		for each (CString item in similarCharactersArray)
		{
			resultArray.push_back(item);
		}
	}

	if (add_punctuations) {
		char* punctuationsArray[] = {
			";", ",", "\"", "?",".","(",")","!","-",",",":","'"
		};

		for each (CString item in punctuationsArray)
		{
			resultArray.push_back(item);
		}
	}

	if (add_programmingCharacters) {

		char* punctuationsArray[] = {
			"`", "$", "'", "\"", "&", "?", "@", "#", "<", ">", "(", ")", "{", "}", "[", "]", "/", "\\", "=", "+", "%", "^", "*", "_", "|"
		};

		for each (CString item in punctuationsArray)
		{
			resultArray.push_back(item);
		}
	}

	CString result = (LPCWSTR)L"";
	for (int i = 0; i <= length - 1; i++) {
		int randomKey = rand() % resultArray.size();
		CString randomCharacter = (LPCWSTR)resultArray[randomKey];
		result += randomCharacter;
	}
	return result;
}

void CofflinePasswordGeneratorDlg::OnBnClickedbtngenerate()
{
	bool allowPunctuations_bool = ((CButton*)GetDlgItem(chkIncludePunctuations))->GetCheck();
	bool allowProgrammingCharacters = ((CButton*)GetDlgItem(chkIncludeProgrammingCharacters))->GetCheck();
	bool allowSimilarCharacters = ((CButton*)GetDlgItem(chkIncludeSimilarCharacters))->GetCheck();
	bool allowUppercase = ((CButton*)GetDlgItem(chkIncludeUppercase))->GetCheck();

	CString strLength;
	GetDlgItem(txtPasswordLength)->GetWindowTextW(strLength);
	int intLength = _ttoi(strLength);
	GetDlgItem(txtGeneratedPassword)->SetWindowTextW(generateRandomPassword(intLength, allowPunctuations_bool, allowProgrammingCharacters, allowSimilarCharacters, allowUppercase));
}

void CofflinePasswordGeneratorDlg::OnBnClickedCancel()
{
	CDialog::OnCancel();
}

void CofflinePasswordGeneratorDlg::OnBnClickedbtncopy()
{
	CString generatedPassword;
	GetDlgItem(txtGeneratedPassword)->GetWindowTextW(generatedPassword);

	if (!OpenClipboard())
	{
		return;
	}
	if (!EmptyClipboard())
	{
		return;
	}
	size_t size = sizeof(TCHAR)*(1 + generatedPassword.GetLength());
	HGLOBAL hResult = GlobalAlloc(GMEM_MOVEABLE, size);
	LPTSTR lptstrCopy = (LPTSTR)GlobalLock(hResult);
	memcpy(lptstrCopy, generatedPassword.GetBuffer(), size);
	GlobalUnlock(hResult);
#ifndef _UNICODE
	if (::SetClipboardData(CF_TEXT, hResult) == NULL)
#else
	if (::SetClipboardData(CF_UNICODETEXT, hResult) == NULL)
#endif
	{
		GlobalFree(hResult);
		CloseClipboard();
		return;
	}
	CloseClipboard();
}
