import glob
import os

icpcPath = "/Users/*/*/ICPC/"

def createSnippets():
  cppJsonPath = "/Users/*/Library/Application Support/Code/User/snippets/cpp.json"
  cppJsonFile = glob.glob(cppJsonPath, recursive=True)[0]
    
  if os.path.isfile(cppJsonFile) == False:
    print("Wtf!, you don't have cpp's snippets for vscode")
    return

  icpc = glob.glob(icpcPath, recursive=True)[0]
  if os.path.isdir(icpc) == False:
    print("Wtf!, where is the ICPC repository?")
    return
  
  def generate(file, pathToFile, out):
    cppFile = open(pathToFile, "r")

    name = file[:-4]

    out.write(f"  \"{name}\": {{\n")
    out.write(f"    \"prefix\": \"{name}\",\n")

    def getBody(cppFile): 
      codeByLines = list()
      for line in cppFile: 
        printableLine = str("")

        for ch in line: 
          if ch == '\\' or ch == '\$' or ch == '\"':
            printableLine += '\\' # special dummy characters
          printableLine += ch
        
        if line.endswith("\n"):
          printableLine = printableLine[:-1]
        codeByLines.append(printableLine)
        
      return codeByLines

    out.write("    \"body\": [\n")
    for line in getBody(cppFile):
      out.write(f"    \"{line}\",\n")
    out.write("    ],\n")

    out.write(f"    \"description:\" \"{file}\"\n")  
    out.write("  },\n")
  
  cppJson = open(cppJsonFile, "w")
  cppJson.write("{\n")
  
  for path, directories, files in os.walk(f"{icpc}/Codes/"):
    if path.lower().endswith("/tests"):
      continue

    for file in files:
      pathToFile = path + os.sep + file

      if file.endswith(".cpp"):
        generate(file, pathToFile, cppJson)

  cppJson.write("}\n")
  cppJson.close()
  print("Snippets updated")

def updateMyClangFormat():
  settingsJsonPath = "/Users/*/Library//Application Support/Code/User/settings.json"
  settingsJsonFile = glob.glob(settingsJsonPath, recursive=True)[0]
  if os.path.isfile(settingsJsonFile) == False:
    print("Wtf!, you don't have settings.json for vscode")
    return

  icpc = glob.glob(icpcPath, recursive=True)[0]
  if os.path.isdir(icpc) == False:
    print("Wtf!, where is the ICPC repository?")
    return

  saveSettingsJson = open(settingsJsonFile, "r").readlines()

  clangFormatPos = -1
  for pos, line in enumerate(saveSettingsJson): 
    if line.lstrip().startswith("\" C_Cpp.clang_format_fallbackStyle\""):
      clangFormatPos = pos
      break

  if clangFormatPos == -1:
    clangFormatPos = len(saveSettingsJson)
    saveSettingsJson.append("")

  clangFormat = open(f"{icpc}/.clang-format", "r").readlines()
  saveSettingsJson[clangFormatPos] = "\"C_Cpp.clang_format_fallbackStyle\": \"{ "
  for line in clangFormat:
    if line[0].isalpha():
      saveSettingsJson[clangFormatPos] += f"{line.strip()}, "
  saveSettingsJson[clangFormatPos] += "}\",\n"
    
  print("Settings updated")

  settingsJson = open(settingsJsonFile, "w")
  for line in saveSettingsJson:
    settingsJson.write(line)

if __name__ == "__main__":
  createSnippets()
  updateMyClangFormat()