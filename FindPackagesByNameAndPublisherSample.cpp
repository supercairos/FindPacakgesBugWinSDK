//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved

#include <windows.h>
#include <sddl.h>

#include <algorithm>
#include <iostream>
#include <string>

/** WINDOWS **/
#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.Storage.h>

using namespace std;
using namespace winrt;
using namespace Windows::ApplicationModel;
using namespace Windows::Management::Deployment;
using namespace Windows::Storage;


void DisplayPackageInfo(winrt::Windows::ApplicationModel::Package package)
{
    wcout << L"Name: " << package.Id().Name().data() << endl;
}

int main() {
    int packageCount = 0;

    wcout << L"Copyright (c) Microsoft Corporation. All rights reserved." << endl;
    wcout << L"FindPackagesByNameAndPublisher sample" << endl << endl;
    
    winrt::init_apartment();

    try {
        auto iter = PackageManager{}.FindPackages(L"Microsoft.Office.OneNote");
        for (auto i = iter.First(); i.HasCurrent(); i.MoveNext()) {
            const auto& package = i.Current();
            DisplayPackageInfo(package);

            wcout << endl;
            packageCount += 1;
        }
    } catch (...) {
        wcout << L"Error..." << endl;
        return 1;
    }

    if (packageCount < 1) {
        wcout << L"No packages were found." << endl;
    }

    return 0;
}