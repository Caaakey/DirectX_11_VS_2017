#pragma once

class CameraManager
{
	static CameraManager& Get() {
		static CameraManager instance;
		return instance;
	}

	CameraManager();
	CameraManager(CameraManager const&) = delete;
	~CameraManager();

	void operator=(CameraManager const&) = delete;

public:
	
};

