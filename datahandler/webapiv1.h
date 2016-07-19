#pragma once

#include <stddef.h>
#include "ISingleton.h"

enum class eAPIErrors
{
	Unknown = -1,
	Okay = 0,
	NoBaseURL,
	NoSerialNum,
	NoDeviceKey,
	FailedCurlInit,	
	Unsuccessful,
};

class webapiv1 : public ISingleton< webapiv1 >
{
public:
	webapiv1();
	~webapiv1();

public:
	eAPIErrors Authenticate();
	eAPIErrors UpdateTemperature(int temp, int humid);

public:
	void SetBaseUrl(const char* base);
	const char* GetBaseUrl(void)
	{
		if (m_baseUrl)
			return m_baseUrl;
		return "http://vrocker-hosting.ovh/roompi/";
	}

	void SetDeviceSerial(const char* serial);
	const char* GetDeviceSerial(void)
	{
		return m_deviceSerial;
	}

	void SetDeviceAPIKey(const char* key);
	const char* GetDeviceAPIKey(void)
	{
		if (m_deviceAPIKey)
			return m_deviceAPIKey;
		return "";
	}

private:
	static size_t JsonCallback(void *contents, size_t size, size_t nmemb, void **userp);

private:
	char* m_baseUrl;
	char m_accessToken[64];
	char m_deviceSerial[16];
	char* m_deviceAPIKey;

	void* m_curl;
};
