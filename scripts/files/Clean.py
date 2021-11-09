import sys
import os
import shutil
import argparse
from enum import Enum, auto

DeleteCount = 0

def Start():
    # Runtime Options
    parser = argparse.ArgumentParser()
    parser.add_argument('-v', '--verbose', action='store_true', help='print debug messages')
    parser.add_argument('ide', choices=['vs', 'gmake2', 'xcode4', 'codelite'], help="ide to clean files from")
    args = parser.parse_args()

    global DeleteCount

    if args.ide == "vs":
        root = os.path.realpath('../..')
        print(f"Checking files in {root}")
        exts = ["sln", "vcxproj", "vcxproj.filters", "vcxproj.user"]
        DeleteFiles(root, exts) # ../.. (project folder)

        path = os.path.join(root, 'DAGGer')
        DeleteFiles(path, exts) # ../../DAGGer

        path = os.path.join(path, 'vendor')
        for file in os.listdir(path): # ../../DAGGer/vendor
            DeleteFiles(os.path.join(path, file), exts)

        for folder in ['.vs', 'bin', 'bin-int']: # ../..
            path = os.path.join(root, folder)
            if os.path.exists(path):
                print(f"Deleting '{path}'... ", end="")
                shutil.rmtree(path)
                DeleteCount += 1
                print("Done!")

        if DeleteCount == 0:
            print("Deleted 0 files/folders")
        elif DeleteCount == 1:
            print("Sucessfully deleted 1 file/folder")
        else:
            print(f"Successfully deleted {DeleteCount} files and folders.")
    else:
        print("Only Visual Studio is supported")
        sys.exit(0)

def DeleteFiles(path, exts: list[str]) -> None:
    global DeleteCount
    for file in os.listdir(path):
        if os.path.isfile(os.path.join(path, file)):
            for ext in exts:
                if file.endswith(ext):
                    print(f"Deleting '{os.path.join(path, file)}'... ", end="")
                    os.remove(os.path.join(path, file))
                    DeleteCount += 1
                    print("Done!")

Start()