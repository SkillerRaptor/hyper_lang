/*
 * Copyright (c) 2020-present, SkillerRaptor <skillerraptor@protonmail.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "hyper/backends/c/microsoft.hpp"

#if defined(WIN32) || defined(WIN64)
#	include "hyper/utilities.hpp"

#	include <io.h>

#	undef INTERFACE
#	define INTERFACE ISetupInstance
DECLARE_INTERFACE_(ISetupInstance, IUnknown)
{
	BEGIN_INTERFACE

	STDMETHOD(QueryInterface)(THIS_ REFIID, void **) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	STDMETHOD(GetInstanceId)(THIS_ _Out_ BSTR * pbstrInstanceId) PURE;
	STDMETHOD(GetInstallDate)(THIS_ _Out_ LPFILETIME pInstallDate) PURE;
	STDMETHOD(GetInstallationName)(THIS_ _Out_ BSTR * pbstrInstallationName) PURE;
	STDMETHOD(GetInstallationPath)(THIS_ _Out_ BSTR * pbstrInstallationPath) PURE;
	STDMETHOD(GetInstallationVersion)
	(THIS_ _Out_ BSTR * pbstrInstallationVersion) PURE;
	STDMETHOD(GetDisplayName)
	(THIS_ _In_ LCID lcid, _Out_ BSTR * pbstrDisplayName) PURE;
	STDMETHOD(GetDescription)
	(THIS_ _In_ LCID lcid, _Out_ BSTR * pbstrDescription) PURE;
	STDMETHOD(ResolvePath)
	(THIS_ _In_opt_z_ LPCOLESTR pwszRelativePath, _Out_ BSTR * pbstrAbsolutePath)
		PURE;

	END_INTERFACE
};

#	undef INTERFACE
#	define INTERFACE IEnumSetupInstances
DECLARE_INTERFACE_(IEnumSetupInstances, IUnknown)
{
	BEGIN_INTERFACE

	STDMETHOD(QueryInterface)(THIS_ REFIID, void **) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	STDMETHOD(Next)
	(THIS_ _In_ ULONG celt,
	 _Out_writes_to_(celt, *pceltFetched) ISetupInstance * *rgelt,
	 _Out_opt_ _Deref_out_range_(0, celt) ULONG * pceltFetched) PURE;
	STDMETHOD(Skip)(THIS_ _In_ ULONG celt) PURE;
	STDMETHOD(Reset)(THIS) PURE;
	STDMETHOD(Clone)(THIS_ _Deref_out_opt_ IEnumSetupInstances * *ppenum) PURE;

	END_INTERFACE
};

#	undef INTERFACE
#	define INTERFACE ISetupConfiguration
DECLARE_INTERFACE_(ISetupConfiguration, IUnknown)
{
	BEGIN_INTERFACE

	STDMETHOD(QueryInterface)(THIS_ REFIID, void **) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;

	STDMETHOD(EnumInstances)
	(THIS_ _Out_ IEnumSetupInstances * *ppEnumInstances) PURE;
	STDMETHOD(GetInstanceForCurrentProcess)
	(THIS_ _Out_ ISetupInstance * *ppInstance) PURE;
	STDMETHOD(GetInstanceForPath)
	(THIS_ _In_z_ LPCWSTR wzPath, _Out_ ISetupInstance * *ppInstance) PURE;

	END_INTERFACE
};

namespace hyper
{
	void MicrosoftCompiler::find()
	{
		find_windows_kit();

		if (!m_sdk_root.empty())
		{
			m_sdk_um_library_path = m_sdk_root + "\\um\\x64";
			m_sdk_ucrt_library_path = m_sdk_root + "\\ucrt\\x64";
		}

		find_visual_studio();
	}

	size_t MicrosoftCompiler::sdk_version() const
	{
		return m_sdk_version;
	}

	std::string MicrosoftCompiler::sdk_root() const
	{
		return m_sdk_root;
	}

	std::string MicrosoftCompiler::sdk_um_library_path() const
	{
		return m_sdk_um_library_path;
	}

	std::string MicrosoftCompiler::sdk_ucrt_library_path() const
	{
		return m_sdk_ucrt_library_path;
	}

	bool MicrosoftCompiler::is_vs_2017() const
	{
		return m_is_vs_2017;
	}

	std::string MicrosoftCompiler::visual_studio_exe_path() const
	{
		return m_visual_studio_exe_path;
	}

	std::string MicrosoftCompiler::visual_studio_library_path() const
	{
		return m_visual_studio_library_path;
	}

	bool MicrosoftCompiler::os_file_exists(std::wstring_view name) const
	{
		const DWORD attributes = GetFileAttributesW(name.data());
		if (attributes == INVALID_FILE_ATTRIBUTES)
		{
			return false;
		}

		if (attributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			return false;
		}

		return true;
	}

	bool MicrosoftCompiler::visit_files(
		const std::wstring &directory_name,
		VersionData &version_data,
		VisitFunction visit_function)
	{
		WIN32_FIND_DATAW find_data = {};
		const std::wstring wildcard_name = directory_name + L"\\*";

		HANDLE handle = FindFirstFileW(wildcard_name.c_str(), &find_data);
		if (handle == INVALID_HANDLE_VALUE)
		{
			return false;
		}

		while (true)
		{
			if (
				(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				(find_data.cFileName[0] != '.'))
			{
				const std::wstring full_name =
					directory_name + L"\\" + find_data.cFileName;
				visit_function(find_data.cFileName, full_name, version_data);
			}

			const BOOL success = FindNextFileW(handle, &find_data);
			if (!success)
			{
				break;
			}
		}

		FindClose(handle);

		return true;
	}

	void MicrosoftCompiler::win10_visit(
		std::wstring_view short_name,
		std::wstring_view full_name,
		MicrosoftCompiler::VersionData &version_data)
	{
		int integer_1 = 0;
		int integer_2 = 0;
		int integer_3 = 0;
		int integer_4 = 0;
		const int return_code = swscanf_s(
			short_name.data(),
			L"%d.%d.%d.%d",
			&integer_1,
			&integer_2,
			&integer_3,
			&integer_4);
		if (return_code < 4)
		{
			return;
		}

		if (integer_1 < version_data.best_version[0])
		{
			return;
		}

		if (integer_1 == version_data.best_version[0])
		{
			if (integer_2 < version_data.best_version[1])
			{
				return;
			}

			if (integer_2 == version_data.best_version[1])
			{
				if (integer_3 < version_data.best_version[2])
				{
					return;
				}

				if (integer_3 == version_data.best_version[2])
				{
					if (integer_4 < version_data.best_version[3])
					{
						return;
					}
				}
			}
		}

		version_data.best_name = full_name;

		if (!version_data.best_name.empty())
		{
			version_data.best_version[0] = integer_1;
			version_data.best_version[1] = integer_2;
			version_data.best_version[2] = integer_3;
			version_data.best_version[3] = integer_4;
		}
	}

	void MicrosoftCompiler::win8_visit(
		std::wstring_view short_name,
		std::wstring_view full_name,
		MicrosoftCompiler::VersionData &version_data)
	{
		int integer_1 = 0;
		int integer_2 = 0;
		const int return_code =
			swscanf_s(short_name.data(), L"winv%d.%d", &integer_1, &integer_2);
		if (return_code < 2)
		{
			return;
		}

		if (integer_1 < version_data.best_version[0])
		{
			return;
		}

		if (integer_1 == version_data.best_version[0])
		{
			if (integer_2 < version_data.best_version[1])
			{
				return;
			}
		}

		version_data.best_name = full_name;

		if (!version_data.best_name.empty())
		{
			version_data.best_version[0] = integer_1;
			version_data.best_version[1] = integer_2;
		}
	}

	void MicrosoftCompiler::find_windows_kit()
	{
		HKEY main_key = nullptr;
		const LSTATUS return_code = RegOpenKeyExA(
			HKEY_LOCAL_MACHINE,
			"SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots",
			0,
			KEY_QUERY_VALUE | KEY_WOW64_32KEY | KEY_ENUMERATE_SUB_KEYS,
			&main_key);
		if (return_code != S_OK)
		{
			return;
		}

		const std::wstring windows10_root =
			find_windows_kit_with_key(main_key, L"KitsRoot10");
		if (!windows10_root.empty())
		{
			const std::wstring windows10_lib = windows10_root + L"Lib";

			VersionData version_data = {};
			visit_files(windows10_lib, version_data, win10_visit);

			if (!version_data.best_name.empty())
			{
				m_sdk_version = 10;
				m_sdk_root = Utilities::convert_wstring(version_data.best_name);
				return;
			}
		}

		const std::wstring windows8_root =
			find_windows_kit_with_key(main_key, L"KitsRoot81");
		if (!windows8_root.empty())
		{
			const std::wstring windows8_lib = windows8_root + L"Lib";

			VersionData version_data = {};
			visit_files(windows8_lib, version_data, win8_visit);

			if (!version_data.best_name.empty())
			{
				m_sdk_version = 8;
				m_sdk_root = Utilities::convert_wstring(version_data.best_name);
				return;
			}
		}

		RegCloseKey(main_key);
	}

	std::wstring MicrosoftCompiler::find_windows_kit_with_key(
		HKEY key,
		std::wstring_view version)
	{
		DWORD required_length = 0;
		LSTATUS return_code = RegQueryValueExW(
			key, version.data(), nullptr, nullptr, nullptr, &required_length);
		if (return_code != S_OK)
		{
			return L"";
		}

		const DWORD length = required_length + 2;
		wchar_t *value = new wchar_t[length];

		return_code = RegQueryValueExW(
			key,
			version.data(),
			nullptr,
			nullptr,
			reinterpret_cast<LPBYTE>(value),
			&required_length);
		if (return_code != S_OK)
		{
			return L"";
		}

		value[required_length / 2] = '\0';

		const std::wstring string = value;
		delete[] value;

		return string;
	}

	void MicrosoftCompiler::find_visual_studio()
	{
		const bool found_visual_studio_17 = find_visual_studio_17();
		if (found_visual_studio_17)
		{
			return;
		}

		HKEY vs7_keys = nullptr;
		const HRESULT return_code = RegOpenKeyExA(
			HKEY_LOCAL_MACHINE,
			"SOFTWARE\\Microsoft\\VisualStudio\\SxS\\VS7",
			0,
			KEY_QUERY_VALUE | KEY_WOW64_32KEY,
			&vs7_keys);
		if (return_code != S_OK)
		{
			return;
		}

		const std::wstring_view versions[] = { L"14.0", L"12.0", L"11.0", L"10.0" };
		const int NUM_VERSIONS = sizeof(versions) / sizeof(versions[0]);

		for (int i = 0; i < NUM_VERSIONS; i++)
		{
			const std::wstring_view version = versions[i];

			DWORD dw_type = 0;
			DWORD cb_data = 0;
			LSTATUS query_return_code = RegQueryValueExW(
				vs7_keys, version.data(), NULL, &dw_type, NULL, &cb_data);
			if ((query_return_code == ERROR_FILE_NOT_FOUND) || (dw_type != REG_SZ))
			{
				continue;
			}

			wchar_t *buffer = new wchar_t[cb_data];
			query_return_code = RegQueryValueExW(
				vs7_keys, version.data(), NULL, NULL, (LPBYTE) buffer, &cb_data);
			if (query_return_code != S_OK)
			{
				continue;
			}

			std::wstring buffer_string = buffer;
			delete[] buffer;

			const std::wstring lib_path = buffer_string + L"VC\\Lib\\amd64";
			const std::wstring runtime_file_name = lib_path + L"\\vcruntime.lib";
			const bool runtime_exists = os_file_exists(runtime_file_name);
			if (runtime_exists)
			{
				m_visual_studio_exe_path =
					Utilities::convert_wstring(buffer_string) + "VC\\bin\\amd64";
				m_visual_studio_library_path = Utilities::convert_wstring(lib_path);

				RegCloseKey(vs7_keys);

				return;
			}
		}

		RegCloseKey(vs7_keys);
	}

	bool MicrosoftCompiler::find_visual_studio_17()
	{
		CoInitialize(nullptr);

		const GUID uid = {
			0x42843719,
			0xDB4C,
			0x46C2,
			{
				0x8E,
				0x7C,
				0x64,
				0xF1,
				0x81,
				0x6E,
				0xFD,
				0x5B,
			},
		};

		const GUID setup_configuration_uid = {
			0x177F0C4A,
			0x1CD3,
			0x4DE7,
			{
				0xA3,
				0x2C,
				0x71,
				0xDB,
				0xBB,
				0x9F,
				0xA3,
				0x6D,
			},
		};

		ISetupConfiguration *setup_configuration = nullptr;
		const HRESULT instance_result = CoCreateInstance(
			setup_configuration_uid,
			NULL,
			CLSCTX_INPROC_SERVER,
			uid,
			reinterpret_cast<void **>(&setup_configuration));
		if (instance_result != 0)
		{
			return false;
		}

		IEnumSetupInstances *enum_setup_instances = nullptr;
		const HRESULT enum_instances_result =
			setup_configuration->EnumInstances(&enum_setup_instances);
		setup_configuration->Release();

		if (enum_instances_result != 0)
		{
			return false;
		}

		if (enum_setup_instances == nullptr)
		{
			return false;
		}

		bool found = false;
		while (true)
		{
			ULONG found_flag = 0;
			ISetupInstance *setup_instance = nullptr;
			const HRESULT next_result =
				enum_setup_instances->Next(1, &setup_instance, &found_flag);
			if (next_result != S_OK)
			{
				break;
			}

			BSTR instance_path = nullptr;
			const HRESULT installation_result =
				setup_instance->GetInstallationPath(&instance_path);
			setup_instance->Release();
			if (installation_result != S_OK)
			{
				continue;
			}

			const std::wstring instance_path_string(instance_path);

			const std::wstring tools_file_name =
				instance_path_string +
				L"\\VC\\Auxiliary\\Build\\Microsoft.VCToolsVersion.default.txt";
			SysFreeString(instance_path);

			FILE *file = nullptr;
			const errno_t open_result =
				_wfopen_s(&file, tools_file_name.c_str(), L"rt");
			if (open_result != 0)
			{
				continue;
			}

			if (file == nullptr)
			{
				continue;
			}

			LARGE_INTEGER tools_file_size = {};
			const HANDLE file_handle =
				reinterpret_cast<HANDLE>(_get_osfhandle(_fileno(file)));
			const BOOL success = GetFileSizeEx(file_handle, &tools_file_size);
			if (!success)
			{
				fclose(file);
				continue;
			}

			const size_t version_length =
				static_cast<size_t>(tools_file_size.QuadPart + 1);
			wchar_t *version = new wchar_t[version_length * 2];
			const wchar_t *read_result =
				fgetws(version, static_cast<int>(version_length), file);
			fclose(file);
			if (!read_result)
			{
				continue;
			}

			wchar_t *version_tail = wcschr(version, '\n');
			if (version_tail)
			{
				*version_tail = 0;
			}

			const std::wstring library_path =
				instance_path_string + L"\\VC\\Tools\\MSVC\\" + version + L"\\lib\\x64";
			const std::wstring library_file = library_path + L"\\vcruntime.lib";
			if (os_file_exists(library_file))
			{
				const std::wstring link_exe_path = instance_path_string +
																					 L"\\VC\\Tools\\MSVC\\" + version +
																					 L"\\bin\\Hostx64\\x64";
				delete[] version;

				m_visual_studio_exe_path = Utilities::convert_wstring(link_exe_path);
				m_visual_studio_library_path = Utilities::convert_wstring(library_path);
				m_is_vs_2017 = true;
				found = true;
				break;
			}

			delete[] version;
		}

		enum_setup_instances->Release();

		return found;
	}
} // namespace hyper
#endif
