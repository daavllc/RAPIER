####################################################
## Author: Anonoei (https://github.com/Anonoei)
# License: GPLv3
# Language: Python 3
## Provies counts for lines inside directories
#######################
import os

SearchFor = [".h", ".cpp"]
def Main():
	info = Info()
	p = "Counting "
	for i in range(len(SearchFor)):
		p += SearchFor[i]
		if i < len(SearchFor) - 2:
			p += ", "
		elif i < len(SearchFor) - 1:
			p += " and "
	print(p + " files")
	info.Add(Project("RAPIER", "RAPIER/src"))
	info.Add(Project("FORGE", "FORGE/src"))
	c = ["PROJECT", "DIRS", "FILES", "LINES", "CHARS", "SIZE"]
	if len(c[0]) > info.LongestName:
		info.LongestName = len(c[0])
	if len(c[1]) > info.LongestDirs:
		info.LongestDirs = len(c[1])
	if len(c[2]) > info.LongestPath:
		info.LongestPath = len(c[2])
	if len(c[3]) > info.LongestLine:
		info.LongestLine = len(c[3])
	if len(c[4]) > info.LongestChar:
		info.LongestChar = len(c[5])
	if len(c[5]) > info.LongestSize:
		info.LongestSize = len(c[4])

	if len("TOTAL") > info.LongestName:
		info.LongestName = len("TOTAL")
	if len(info.GetTDirs()) > info.LongestDirs:
		info.LongestDirs = len(info.GetTDirs())
	if len(info.GetTLines()) > info.LongestLine:
		info.LongestLine = len(info.GetTLines())
	if len(info.GetTChars()) > info.LongestChar:
		info.LongestChar = len(info.GetTChars())
	if len(info.GetTSize()) > info.LongestSize:
		info.LongestSize = len(info.GetTSize())

	print("  | {} | {} | {} | {} | {} | {} |".format(
		Center(c[0], info.LongestName), Center(c[1], info.LongestDirs),
		Center(c[2], info.LongestPath), Center(c[3], info.LongestLine),
		Center(c[4], info.LongestChar), Center(c[5], info.LongestSize) ) )
	splitter = ("  | {} | {} | {} | {} | {} | {} |".format(
		'=' * info.LongestName, '=' * info.LongestDirs,
		'=' * info.LongestPath, '=' * info.LongestLine,
		'=' * info.LongestChar, '=' * info.LongestSize ) )
	print(splitter)
	for project in info.Projects:
		print("  | {} | {} | {} | {} | {} | {} |".format(
		Left(project.Name,info.LongestName), Left(str(project.TotalDirectories),info.LongestDirs),
		Left(str(len(project.FilesList[0])), info.LongestPath), Left(str(project.TotalLines), info.LongestLine),
		Left(str(project.TotalChars), info.LongestChar), Left(project.GetTSize(), info.LongestSize) ) )
	print(splitter)
	print("  | {} | {} | {} | {} | {} | {} |".format(
		Center("TOTAL", info.LongestName), Center(info.GetTDirs(), info.LongestDirs),
		Center(info.GetTFiles(), info.LongestPath), Center(info.GetTLines(), info.LongestLine),
		Center(info.GetTChars(), info.LongestChar), Center(info.GetTSize(), info.LongestSize) ) )

# Text alignment
def Left(text, width):
	size = len(text)
	offset = round((width / 2) - (size / 2))
	retr = text + " " * offset
	while len(retr) < width:
		retr += " "
	while len(retr) > width:
		retr = retr[:len(retr) - 1]
	return retr
def Center(text, width):
	size = len(text)
	offset = round((width / 2) - (size / 2))
	retr = " " * offset + text + " " * offset
	while len(retr) < width:
		retr += " "
	while len(retr) > width:
		retr = retr[:len(retr) - 1]
	return retr

class Project:
	def __init__(self, name, path):
		self._fAppend = "../../"
		self.Name = name
		self.Path = self._InitPath(path)
		self.SetData(GetInfo(self.Path))
	def _InitPath(self, path):
		sepChar = ""
		if os.name == "nt":
			sepChar = "\\"
		else:
			sepChar = "/"
		path = self._fAppend + path # main RAPIER folder
		return path.replace("/", sepChar)
	def SetData(self, fData):
		self.Data = fData[:2]
		self.TotalChars = fData[0][0]
		self.TotalLines = fData[0][1]
		self.FilesList = fData[1] # [File, Lines, Size]
		self.LongestPath = fData[2][0] - len(self._fAppend) # length of longest path string
		self.LongestLineSize = fData[2][1] # length of longest size line len(str(line))
		self.LongestCharSize = fData[2][2] # length of longest size char len(str(char))
		self.TotalDirectories = fData[3][0]
		self.TotalSize = fData[3][1]
	def GetTSize(self):
		if self.TotalSize < 1000:
			return "{} B".format(self.TotalChars, 2)
		elif self.TotalSize < 10000000:
			return "{:.{}f} KB".format(self.TotalChars / 1000, 2)
		else:
			return "{:.{}f} GB".format(self.TotalChars / 10000000, 2)

class Info:
	def __init__(self):
		self.Projects = []
		self.LongestName = 0 # Longest Project Name
		self.LongestDirs = 0 # Longest Project TotalDirectories string
		self.LongestPath = 0 # Longest Project Files path
		self.LongestChar = 0 # Longest Project TotalChars
		self.LongestChar = 0 # Longest Project LongestCharSize
		self.LongestLine = 0 # Longest Project TotalLines
		self.LongestSize = 0 # Longest Project Size 

		self.TotalDirs  = 0
		self.TotalFiles = 0
		self.TotalLines = 0 # Total of all Project lines
		self.TotalChars = 0 # Total of all Project chars
		self.TotalSize  = 0 # Total of all Project TotalSize

	def Add(self, project):
		self.Projects.append(project)
		self.TotalDirs += project.TotalDirectories
		self.TotalFiles += len(project.FilesList[0])
		self.TotalLines += project.TotalLines
		self.TotalChars += project.TotalChars
		self.TotalSize  += project.TotalSize
		if len(project.Name) > self.LongestName:
			self.LongestName = len(project.Name)
		if len(str(project.TotalDirectories)) > self.LongestDirs:
			self.LongestDirs = len(str(project.TotalDirectories))
		if len(str(len(project.FilesList[0]))) > self.LongestPath:
			self.LongestPath = len(str(len(project.FilesList[0])))
		if len(str(project.TotalChars)) > self.LongestChar:
			self.LongestChar = len(str(project.TotalChars))
		if len(str(project.TotalLines)) > self.LongestLine:
			self.LongestLine = len(str(project.TotalLines))
		if len(str(project.TotalSize)) > self.LongestSize:
			self.LongestSize = len(str(project.TotalSize))
	def GetTDirs(self):
		return str(self.TotalDirs)
	def GetTFiles(self):
		return str(self.TotalFiles)
	def GetTLines(self):
		return str(self.TotalLines)
	def GetTChars(self):
		return str(self.TotalChars)
	def GetTSize(self):
		if self.TotalSize < 1000:
			return "{} B".format(self.TotalChars, 2)
		elif self.TotalSize < 10000000:
			return "{:.{}f} KB".format(self.TotalChars / 1000, 2)
		else:
			return "{:.{}f} GB".format(self.TotalChars / 10000000, 2)
			

def countFile(file):
	f = open(file, 'r', errors='replace')
	lines = f.readlines()
	numChars = 0
	numLines = 0
	for line in lines:
		numLines += 1
		numChars += len(line.strip())
	f.close()
	return [numChars, numLines]

def GetInfo(folder):
	TotalChars = 0
	TotalLines = 0
	File  = []
	Lines = []
	Size  = []
	LargestFileLen = 0
	LargestLineLen = 0
	LargestCharLen = 0
	TotalDirectories = 0
	TotalSize = 0;
	for item in os.listdir(folder):
		path = os.path.join(folder, item)
		if os.path.isdir(path):
			TotalDirectories += 1
			data = GetInfo(path)
			for i in range(len(data[1][0])):
				File.append( data[1][0][i])
				Lines.append(data[1][1][i])
				Size.append( data[1][2][i])
			if data[2][0] > LargestFileLen:
				LargestFileLen = data[2][0]
			if data[2][1] > LargestLineLen:
				LargestLineLen = data[2][1]
			if data[2][2] > LargestCharLen:
				LargestCharLen = data[2][2]
			TotalChars += data[0][0]
			TotalLines += data[0][1]
			TotalDirectories += data[3][0]
			TotalSize += data[3][1]
		if os.path.isfile(path):
			for ext in SearchFor:
				if item.endswith(ext):
					File.append(path)
					count = countFile(path)
					size = os.path.getsize(path)
					Lines.append(count[1])
					Size.append(size)
					TotalChars += count[0] # chars
					TotalLines += count[1] # lines
					if len(str(path)) > LargestFileLen:
						LargestFileLen = len(str(path))
					if len(str(count[0])) > LargestCharLen:
						LargestCharLen = len(str(count[0]))
					if len(str(count[1])) > LargestLineLen:
						LargestLineLen = len(str(count[1]))
					TotalSize += size
	return [ [TotalChars, TotalLines], [File, Lines, Size], [LargestFileLen, LargestLineLen, LargestCharLen], [TotalDirectories, TotalSize]]

Main()
