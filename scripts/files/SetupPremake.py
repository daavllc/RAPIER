import sys
import os
from pathlib import Path
import platform

import Utils

class PremakeConfiguration:
	premakeVersion = "5.0.0-alpha16"
	premakeLicenseUrl = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"
	premakeDirectory = "./vendor/premake/bin"
	if platform.system() == "Windows":
		premakeZipUrls = f"https://github.com/premake/premake-core/releases/download/v{premakeVersion}/premake-{premakeVersion}-windows.zip"
	elif platform.system() == "Linux":
		premakeZipUrls = f"https://github.com/premake/premake-core/releases/download/v{premakeVersion}/premake-{premakeVersion}-linux.tar.gz"

	@classmethod
	def Validate(cls):
		if (not cls.CheckIfPremakeInstalled()):
			print("Premake is not installed.")
			return False

		print(f"Correct Premake located at {os.path.abspath(cls.premakeDirectory)}")
		return True

	@classmethod
	def CheckIfPremakeInstalled(cls):
		premakeBin = ""
		if platform.system() == "Windows":
			premakeBin = Path(f"{cls.premakeDirectory}/premake5.exe");
		elif platform.system() == "Linux":
			premakeBin = Path(f"{cls.premakeDirectory}/premake5");
		if (not premakeBin.exists()):
			return cls.InstallPremake()

		return True

	@classmethod
	def InstallPremake(cls):
		permissionGranted = False
		while not permissionGranted:
			reply = str(input("Premake not found. Would you like to download Premake {0:s}? [Y/N]: ".format(cls.premakeVersion))).lower().strip()[:1]
			if reply == 'n':
				return False
			permissionGranted = (reply == 'y')

		premakePath = ""
		if platform.system() == "Windows":
			premakePath = f"{cls.premakeDirectory}/premake-{cls.premakeVersion}-windows.zip"
		elif platform.system() == "Linux":
			premakePath = f"{cls.premakeDirectory}/premake-{cls.premakeVersion}-linux.tar.gz"
		print("Downloading {0:s} to {1:s}".format(cls.premakeZipUrls, premakePath))
		Utils.DownloadFile(cls.premakeZipUrls, premakePath)
		print("Extracting", premakePath)
		Utils.UnzipFile(premakePath, deleteArchiveFile = True)
		print(f"Premake {cls.premakeVersion} has been downloaded to '{cls.premakeDirectory}'")

		premakeLicensePath = f"{cls.premakeDirectory}/LICENSE.txt"
		print("Downloading {0:s} to {1:s}".format(cls.premakeLicenseUrl, premakeLicensePath))
		Utils.DownloadFile(cls.premakeLicenseUrl, premakeLicensePath)
		print(f"Premake License file has been downloaded to '{cls.premakeDirectory}'")

		return True
