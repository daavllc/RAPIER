import sys
import os
import shutil

Verbose = False
DelPause = True

def dPrint(msg):
    if Verbose:
        print(msg)

def Start():
    OS = ""
    # Runtime Options
    for arg in sys.argv[1:]:
        if 'v' in arg:
            Verbose = True
        if 'p' in arg:
            DelPause = False
        # Determine OS
        if 'w' in arg:
            OS = "win"
    
    if OS:
        if OS == "win":
            DeleteVS()
    else:
        print("Please specify an option")

def DeleteVS():
    Count = 0
    DirBegin = "../.."
    Dirs = ["/DAGGer", "/DAGGer/vendor/Glad", "/DAGGer/vendor/glfw", "DAGGer/vendor/imgui", "DAGGer/vendor/yaml-cpp"]
    fNames = ["DAGGer", "Glad", "GLFW", "ImGui", "yaml-cpp"]
    fExt = ["sln", "vcxproj", "vcxproj.filters", "vcxproj.user"]
    fExts = [[1,2,3],[1,2],[1,2],[1],[1,2]]
    DeleteFile(DirBegin, "DAGGer", fExt[0])
    for loc in range(len(Dirs)):
        for ext in fExts[loc]: 
            inc = DeleteFile(DirBegin + Dirs[loc], fNames[loc], fExt[ext])
            if inc:
                Count += 1
    if os.path.exists('{}/{}'.format(DirBegin, ".vs")):
        if DelPause:
            UsrInput = input("Remove .vs configurations? (Y/n) > ")
            if not 'n' in UsrInput:
                DeleteFolder(DirBegin, ".vs")
                Count += 1
        else:
            DeleteFolder(DirBegin, ".vs")
    if Count == 1:
        print("Done! Deleted 1 item")
    else:
        print("Done! Deleted {} items".format(Count))

def DeleteFile(filepath, name, ext):
    if os.path.exists('{}/{}.{}'.format(filepath, name, ext)):
        os.remove('{}/{}.{}'.format(filepath, name, ext))
        print('Deleted {}/{}.{}'.format(filepath, name, ext))
        return True
    else:
        dPrint('Failed to locate {}/{}.{}'.format(filepath, name, ext))
        return False
        
def DeleteFolder(path, folder):
    shutil.rmtree('{}/{}'.format(path, folder))
    print('Deleted {}/{}'.format(path, folder))

Start()