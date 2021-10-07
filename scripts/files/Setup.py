import os
import subprocess
import platform

from SetupPython import PythonConfiguration as PythonRequirements

# Make sure everything we need for the setup is installed
PythonRequirements.Validate()

from SetupPremake import PremakeConfiguration as PremakeRequirements
from SetupVulkan import VulkanConfiguration as VulkanRequirements

os.chdir('./../..') # Change from devtools/scripts/files directory to root

premakeInstalled = PremakeRequirements.Validate()
VulkanRequirements.Validate()

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive", "--remote"])

if (premakeInstalled):
	if platform.system() == "Windows":
		print("\nRunning premake...")
		subprocess.call([os.path.abspath("./scripts/files/Windows-GenProjects.bat"), "nopause"])
	elif platform.system() == "Linux":
		print("\nRunning premake")
		subprocess.call([os.path.abspath("./scrpts/files/Linux-GenProjects.sh")])

	print("\nSetup completed <premake>!")
else:
	print("DAGGer requires Premake to generate project files.")

print("\nSetup completed <done>!")
