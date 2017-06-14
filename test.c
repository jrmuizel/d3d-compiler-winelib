// fxc2.cpp : Defines the entry point for the console application.
//
#define COBJMACROS
//#include "stdafx.h"
#include <d3dcompiler.h>
#include <d3dcommon.h>
#include <direct.h>
#include <stdio.h>
#define D3D_COMPILE_STANDARD_FILE_INCLUDE ((ID3DInclude*)(UINT_PTR)1)

typedef HRESULT(__stdcall *pCompileFromFileg)(LPCWSTR, const D3D_SHADER_MACRO[], ID3DInclude*, LPCSTR, LPCSTR, UINT, UINT, ID3DBlob**, ID3DBlob**);

int main()
{
	/*
	HRESULT WINAPI D3DCompileFromFile(
	in      LPCWSTR pFileName,
	in_opt  const D3D_SHADER_MACRO pDefines,
	in_opt  ID3DInclude pInclude,
	in      LPCSTR pEntrypoint,
	in      LPCSTR pTarget,
	in      UINT Flags1,
	in      UINT Flags2,
	out     ID3DBlob ppCode,
	out_opt ID3DBlob ppErrorMsgs
	);
	*/


	HMODULE h = LoadLibrary("d3dcompiler_47.dll");
	printf("module %x\n", h);
	pCompileFromFileg ptr = (pCompileFromFileg)GetProcAddress(h, "D3DCompileFromFile");
	printf("ptr %x\n", ptr);
	HRESULT hr;
	ID3DBlob* output = NULL;
	ID3DBlob* errors = NULL;
	const D3D_SHADER_MACRO defines[] =
	{
		"VERTEX_SHADER", "1",
		NULL, NULL
	};

	LPCSTR entryPoint = "LayerQuadVS";
	LPCWSTR srcFile = L"CompositorD3D11.hlsl";

	hr = ptr(
		srcFile,
		defines,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint,
		"vs_4_0_level_9_3",
		D3DCOMPILE_DEBUG,
		0,
		&output,
		&errors
	);

#if 1
	if (FAILED(hr))
	{
		if (errors)
		{
			char *error_message = (char*)ID3D10Blob_GetBufferPointer(errors);
			printf("errors: %s\n", error_message);
		}


		return hr;
	}
	int* foo = (int*)ID3D10Blob_GetBufferPointer(output);
	printf("%x\n", *foo);
	foo++;
	printf("%x\n", *foo);
	foo++;
	printf("%x\n", *foo);
	foo++;
	printf("%x\n", *foo);
	foo++;
	printf("%x\n", *foo);
#endif
	return 0;
}
