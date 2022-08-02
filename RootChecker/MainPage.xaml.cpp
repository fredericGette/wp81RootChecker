//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Checker.h"

using namespace RootChecker;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter

	TextTest->Text = L"Reading: HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\PhoneProvisioner\\ColdBootDone\n\n";
	boolean result = check01();
	if (result) {
		TextTest->Text += L"Success!\n\n";
	}
	else {
		TextTest->Text += L"Failed!\n\n";
	}

	TextTest->Text += L"Reading: C:\\Windows\\System32\\config\\*\n\n";
	result &= check02();
	if (result) {
		TextTest->Text += L"Success!\n\n";
	}
	else {
		TextTest->Text += L"Failed!\n\n";
	}

	TextTest->Text += L"Executing: C:\\WINDOWS\\SYSTEM32\\XBFGENERATOR.EXE\n\n";
	result &= check03();
	if (result) {
		TextTest->Text += L"Success!\n\n";
	}
	else {
		TextTest->Text += L"Failed!\n\n";
	}
}
