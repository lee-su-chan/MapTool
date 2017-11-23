#include "LightShaderClass.h"

LightShaderClass::LightShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_sampleState = 0;
	m_lightBuffer = 0;
}

LightShaderClass::LightShaderClass(const LightShaderClass &other)
{
}

LightShaderClass::~LightShaderClass()
{
}

bool LightShaderClass::Initialize(ID3D11Device *device, HWND hwnd)
{
	bool result;

	result = InitializeShader(device, hwnd, L"Shader/Light.vs", L"Shader/Light.ps");
	if (!result)
		return false;

	return true;
}

void LightShaderClass::Shutdown()
{
	ShutdownShader();

	return;
}

bool LightShaderClass::Render(ID3D11DeviceContext *deviceContext,
	int indexCount,
	XMMATRIX worldMatrix,
	XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView *texture, 
	XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor)
{
	bool result;

	result = SetShaderParameters(deviceContext,
		worldMatrix,
		viewMatrix,
		projectionMatrix,
		texture,
		lightDirection,
		diffuseColor);

	if (!result)
		return false;

	RenderShader(deviceContext, indexCount);

	return true;
}

bool LightShaderClass::InitializeShader(ID3D11Device *device,
	HWND hwnd, 
	const WCHAR *vsFilename,
	const WCHAR *psFilename)
{
	HRESULT result;
	ID3D10Blob *errorMessage;
	ID3D10Blob *vertexShaderBuffer;
	ID3D10Blob *pixelShaderBuffer;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;
	D3D11_SAMPLER_DESC samplerDesc;
	D3D11_BUFFER_DESC lightBufferDesc;

	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	result = D3DCompileFromFile(vsFilename,
		NULL,
		NULL,
		"LightVertexShader",
		"vs_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		&vertexShaderBuffer,
		&errorMessage);

	if (FAILED(result))
	{
		if (errorMessage)
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		else
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
	}

	result = D3DCompileFromFile(psFilename,
		NULL,
		NULL,
		"LightPixelShader",
		"ps_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		&pixelShaderBuffer,
		&errorMessage);

	if (FAILED(result))
	{
		if (errorMessage)
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		else
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
	}

	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		NULL,
		&m_vertexShader);

	if (FAILED(result))
		return false;

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(),
		NULL,
		&m_pixelShader);

	if (FAILED(result))
		return false;

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	result = device->CreateInputLayout(
		polygonLayout,
		numElements,
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		&m_layout);
	
	if (FAILED(result))
		return false;

	vertexShaderBuffer->Release();
	vertexShaderBuffer = NULL;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = NULL;

	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MyStruct::MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
		return false;

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
		return false;

	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(MyStruct::LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&lightBufferDesc, NULL, &m_lightBuffer);
	if (FAILED(result))
		return false;

	return true;
}

void LightShaderClass::ShutdownShader()
{
	if (m_lightBuffer)
	{
		m_lightBuffer->Release();
		m_lightBuffer = NULL;
	}
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = NULL;
	}
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = NULL;
	}
	if (m_layout)
	{
		m_layout->Release();
		m_layout = NULL;
	}
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = NULL;
	}
}

void LightShaderClass::OutputShaderErrorMessage(ID3D10Blob *errorMessage,
	HWND hwnd,
	const WCHAR *shaderFilename)
{
	char *compileErrors;
	unsigned long long bufferSize, i;
	ofstream fout;

	compileErrors = (char *)errorMessage->GetBufferPointer();
	bufferSize = errorMessage->GetBufferSize();

	fout.open("shader-error.txt");

	for (i = 0; i < bufferSize; ++i)
		fout << compileErrors[i];

	fout.close();

	errorMessage->Release();
	errorMessage = NULL;

	MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

bool LightShaderClass::SetShaderParameters(ID3D11DeviceContext *deviceContext,
	XMMATRIX worldMatrix,
	XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix,
	ID3D11ShaderResourceView *texture,
	XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor)
{
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MyStruct::MatrixBufferType *dataPtr;
	MyStruct::LightBufferType *dataPtr2;
	unsigned int vertexBufferNumber;
	unsigned int pixelBufferNumber;

	//worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	result = deviceContext->Map(m_matrixBuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedResource);

	if (FAILED(result))
		return false;

	dataPtr = (MyStruct::MatrixBufferType *)mappedResource.pData;

	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	deviceContext->Unmap(m_matrixBuffer, 0);

	vertexBufferNumber = 0;
	deviceContext->VSSetConstantBuffers(vertexBufferNumber, 1, &m_matrixBuffer);
	deviceContext->PSSetShaderResources(0, 1, &texture);

	result = deviceContext->Map(m_lightBuffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedResource);

	if (FAILED(result))
		return false;

	dataPtr2 = (MyStruct::LightBufferType *)mappedResource.pData;

	dataPtr2->diffuseColor = diffuseColor;
	dataPtr2->lightDirection = lightDirection;
	dataPtr2->padding = 0.0f;

	deviceContext->Unmap(m_lightBuffer, 0);

	pixelBufferNumber = 0;
	deviceContext->PSSetConstantBuffers(pixelBufferNumber, 1, &m_lightBuffer);

	return true;
}

void LightShaderClass::RenderShader(ID3D11DeviceContext *deviceContext, int indexCount)
{
	deviceContext->IASetInputLayout(m_layout);
	
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	deviceContext->PSSetSamplers(0, 1, &m_sampleState);

	deviceContext->DrawIndexed(indexCount, 0, 0);
	
	return;
}
