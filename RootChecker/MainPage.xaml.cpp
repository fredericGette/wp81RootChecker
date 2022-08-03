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
	boolean result01 = check01();
	if (result01) 
	{
		TextTest->Text += L"Success!\n\n";
	}
	else 
	{
		TextTest->Text += L"Failed!\n\n";
	}

	TextTest->Text += L"Reading: C:\\Windows\\System32\\config\\*\n\n";
	boolean result02 = check02();
	if (result02) 
	{
		TextTest->Text += L"Success!\n\n";
	}
	else 
	{
		TextTest->Text += L"Failed!\n\n";
	}

	TextTest->Text += L"Executing: C:\\WINDOWS\\SYSTEM32\\XBFGENERATOR.EXE\n\n";
	boolean result03 = check03();
	if (result03) 
	{
		TextTest->Text += L"Success!\n\n";
	}
	else 
	{
		TextTest->Text += L"Failed!\n\n";
	}

	TextTest->Text += L"Executing: login as DefApps\n\n";
	boolean result04 = check04();
	if (result04) 
	{
		TextTest->Text += L"Success!\n\n";
	}
	else 
	{
		TextTest->Text += L"Failed!\n\n";
	}

	if (result01 && result02 && result03 && result04)
	{
		TextTest->Text += L"Root Access: Enabled";
	}
	else
	{
		TextTest->Text += L"Root Access: Disabled";
	}
}
